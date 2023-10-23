//
// Created by chladas on 4/7/23.
//

#include "CGame.h"

using namespace std::filesystem;

CGame::CGame()
    : m_Winner(nullptr),
    m_Interface(std::make_shared<CInterface>(std::cin, std::cout))
{}
//----------------------------------------------------------------------------------------------------------------------
void CGame::GameInit()
{
    m_GameType = m_Interface->GameTypeMenu();
    LoadGameFromFile(m_GameType == SavedGame ? m_Interface->PromptFileNameForLoad() : CONFIG_FILE);
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::run()
{
    GameInit();
    int move = 0;

    while(this->m_IsRunning)
    {
        m_Interface->DisplayGame(move, m_CurrentPlayer, m_OtherPlayer);

            move = m_CurrentPlayer->MakeMove([&](int pos) {
                if (static_cast<int>(m_CurrentPlayer->getCards().size()) > pos && pos >= 0) {
                    auto card = m_Cards.getCardFromPos(m_CurrentPlayer->getCards()[pos]);
                    if (card && CanBuyCard(card, m_CurrentPlayer))
                        return true;
                }
                return false;
            });

        if(move < 0)
            HandleCommand(move);
        else
        {
            HandleMove(move);
            CheckEndGame();
            swap(m_CurrentPlayer, m_OtherPlayer);
        }
    }

    if(m_Winner)
        m_Interface->DisplayWinner(m_Winner->m_Name);

    m_Interface->DisplayAfterGame();
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::HandleMove(int move)
{
    auto cardToPlay = m_Cards.getCardFromPos(m_CurrentPlayer->getCards()[move]);

    m_Interface->DisplayMove(cardToPlay);

    BuyCard(cardToPlay, m_CurrentPlayer);

    m_CurrentPlayer->getCards().erase(m_CurrentPlayer->getCards().begin() + move);

    m_CurrentPlayer->getCards().push_back(m_Cards.getRandomCardPos());

    for(const auto & effect : cardToPlay->getEffects())
        effect->Apply(m_CurrentPlayer->m_Info, m_OtherPlayer->m_Info);

    m_CurrentPlayer->m_Info.refillResources();

    sleep(3);
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::HandleCommand(int command)
{
    if (command == m_Commands.ConvertCommand("quit")){
        m_IsRunning = false;
        m_Winner = m_OtherPlayer;
    }

    if (command == m_Commands.ConvertCommand("save")){
        SerializeIntoFile();
        m_IsRunning = false;
    }

    if(command == m_Commands.ConvertCommand("help"))
        m_Interface->DisplayHelp();
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::BuyCard(const std::shared_ptr<CCard>& card, const std::shared_ptr<CPlayer> & player)
{
    for(const auto & [resource, amount] : card->getCost())
        player->getPlayerInfo().modifyResources(resource, -amount);
}
//----------------------------------------------------------------------------------------------------------------------
bool CGame::CanBuyCard(const std::shared_ptr<CCard>& card, const std::shared_ptr<CPlayer> & player)
{
    for(const auto & [resource, amount] : card->getCost())
        if(player->getPlayerInfo().getResourceAmount(resource) < amount)
            return false;

    return true;
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::RandomizeCards(std::shared_ptr<CPlayer> & player)
{
    player->getCards().clear();

    for(size_t i = 0; i < DECK_SIZE; i++)
        player->getCards().push_back(m_Cards.getRandomCardPos());
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::CheckEndGame()
{
    auto currBase = m_CurrentPlayer->getPlayerInfo().getBase();
    auto enemyBase  = m_OtherPlayer->getPlayerInfo().getBase();

    if(currBase.isCompleted() || enemyBase.isDestroyed())
    {
        m_IsRunning = false;
        m_Winner = m_CurrentPlayer;
    }
    else if(currBase.isDestroyed() || enemyBase.isCompleted())
    {
        m_IsRunning = false;
        m_Winner = m_OtherPlayer;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::SetPlayerType()
{
    m_CurrentPlayer = std::make_unique<CLocalPlayer>(m_Cards, m_Interface);

    m_GameType == NewVsPlayer ? m_OtherPlayer = std::make_unique<CLocalPlayer>(m_Cards, m_Interface) :
                                m_OtherPlayer = std::make_unique<CAIPlayer>(m_Cards);
}
// loading from file methods --------------------------------------------------------------------------------------------
void CGame::LoadGameFromFile(const std::string &filename)
{
    std::ifstream configFile(filename);
    std::string line;
    bool loadingSavedGame = (m_GameType == SavedGame);

    if(!configFile.is_open())
        throw std::runtime_error("Can not open the default config file.");

    if(loadingSavedGame)
    {
        getline(configFile, line);
        std::istringstream iss(line);

        if(!(iss >> m_GameType && iss.eof() && (m_GameType == NewVsPlayer || m_GameType == NewVsAI)))
            throw std::runtime_error("Invalid game type in config file.");

        if(!getline(configFile, line) || !line.empty())
            throw std::runtime_error("Missing empty line.");
    }

    this->ResourcesInit(configFile);

    this->UnitsInit(configFile);

    m_Cards.InitFromFile(configFile, m_Units, m_Resources);

    this->SetPlayerType();

    m_CurrentPlayer->InitFromFile(configFile, m_Units, m_Resources);
    m_OtherPlayer->InitFromFile(configFile, m_Units, m_Resources);

    if(!loadingSavedGame)
    {
        RandomizeCards(m_CurrentPlayer);
        RandomizeCards(m_OtherPlayer);
        m_CurrentPlayer->SetName();
        m_OtherPlayer->SetName();
    }
    m_Interface->DisplayLoading();
    m_IsRunning = true;
    m_Interface->ClearOutput();

    while(getline(configFile, line) && line.empty());
    if(!configFile.eof())
        throw std::runtime_error("Failed reading from file");
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::ResourcesInit(std::ifstream & configFile)
{
    std::string line, resource;
    while(getline(configFile, line) && !line.empty())
    {
        std::istringstream iss(line);

        while (getline(iss, resource, ','))
        {
            if(m_Resources.count(resource) == 0)
                m_Resources.insert(resource);
            else
                throw std::runtime_error("Duplicate resource found.");
        }

        if (m_Resources.empty())
            throw std::runtime_error("Failed reading the global resources");
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CGame::UnitsInit(std::ifstream & configFile)
{
    std::string line, unit;
    while(getline(configFile, line) && !line.empty())
    {
        std::istringstream iss(line);

        while (getline(iss, unit, ','))
        {
            if(m_Units.count(unit) == 0)
                m_Units.insert(unit);
            else
                throw std::runtime_error("Duplicate unit found.");
        }

        if (m_Units.empty() || !iss.eof())
            throw std::runtime_error("Failed reading the global units.");
    }
}
// saving into file method ---------------------------------------------------------------------------------------------
void CGame::SerializeIntoFile()
{
    std::string filepath = m_Interface->PromptFileNameForSave();
    std::ofstream saveFile;
    saveFile.exceptions(std::ofstream::failbit);

    try {
        saveFile.open(filepath);

        saveFile << m_GameType << "\n\n";

        for (auto it = m_Resources.begin(); it != m_Resources.end();)
            saveFile << *it << (++it != m_Resources.end() ? "," : "\n\n");

        for (auto it = m_Units.begin(); it != m_Units.end();)
            saveFile << *it << (++it != m_Units.end() ? "," : "\n\n");

        m_Cards.Serialize(saveFile);
        m_CurrentPlayer->Serialize(saveFile);
        m_OtherPlayer->Serialize(saveFile);
        m_Interface->PrintLine("Saved into file" + filepath);
    }
    catch (const std::ofstream::failure & e)
    {
        throw std::runtime_error("Failed writing into the file");
    }
}


CGame::CGame(const CGame & other)
: m_Cards(other.m_Cards),
  m_Resources(other.m_Resources),
  m_Units(other.m_Units),
  m_CurrentPlayer(other.m_CurrentPlayer->Clone()),
  m_OtherPlayer(other.m_OtherPlayer->Clone()),
  m_Winner(other.m_Winner),
  m_Interface(other.m_Interface),
  m_IsRunning(other.m_IsRunning),
  m_GameType(other.m_GameType),
  m_Commands(other.m_Commands)
{
}

CGame &CGame::operator=(CGame other)
{
    std::swap(m_GameType, other.m_GameType);
    std::swap(m_Interface, other.m_Interface);
    std::swap(m_IsRunning, other.m_IsRunning);
    std::swap(m_OtherPlayer, other.m_OtherPlayer);
    std::swap(m_CurrentPlayer, other.m_CurrentPlayer);
    std::swap(m_Commands, other.m_Commands);
    std::swap(m_Winner, other.m_Winner);
    std::swap(m_Resources, other.m_Resources);
    std::swap(m_Units, other.m_Units);
    std::swap(m_Cards, other.m_Cards);
    return *this;
}


