#include "CPlayer.h"


//----------------------------------------------------------------------------------------------------------------------
void CPlayer::DisplayCards() const
{
    for(size_t i = 0; i < m_Info.getCardDeck().size(); i++)
    {
        std::cout << "Card(" << i << ") ";
        m_GlobalCardDeck.getCardFromPos(m_Info.getCardDeck()[i])->Display();
        std::cout << std::endl;
    }
    std::cout << CColorizer::Grey(std::string(PADDING, '=')) << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayer::DisplayInfo() const
{
    m_Info.DisplayInfo();
}
//----------------------------------------------------------------------------------------------------------------------
std::string CPlayer::getPaddedName(const std::string & name) const
{
    std::string padding = CColorizer::Grey(std::string((PADDING - m_Name.size() - 2) / 2, '='));

    return padding + " " + name + " " + padding + (m_Name.size() % 2 == 1 ? CColorizer::Grey("=") : "");
}
//----------------------------------------------------------------------------------------------------------------------
CPlayerInfo & CPlayer::getPlayerInfo()
{
    return m_Info;
}
//----------------------------------------------------------------------------------------------------------------------
std::vector<size_t> &CPlayer::getCards()
{
    return m_Info.getCards();
}
// init from file methods ----------------------------------------------------------------------------------------------
void CPlayer::InitFromFile(std::ifstream & configFile, const std::set<std::string> & knownUnits,
                           const std::set<std::string> & knownResources)
{
    if(!configFile.is_open())
        throw std::ios_base::failure("Failed to open examples file ");

    this->ReadName(configFile);

    this->readCards(configFile);

    m_Info.initFromFile(configFile, knownUnits, knownResources);
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayer::ReadName(std::ifstream & configFile)
{
    std::string line, name;
    getline(configFile, line);
    std::istringstream iss(line);

    if(!line.empty() && iss >> name && iss.eof())
        m_Name = name;
    else
        throw std::runtime_error("Invalid player name in examples file");

    if(!getline(configFile, line) || !line.empty())
        throw std::runtime_error("Missing newLine after player in examples file");
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayer::readCards(std::ifstream &configFile)
{
    std::string line;
    size_t index;
    char indent;
    while(getline(configFile, line) && line.empty());

    std::istringstream iss(line);

    while(iss >> index)
    {
        if(index >= m_GlobalCardDeck.Size())
            throw std::runtime_error("Invalid card index.");
        if((!iss.eof() && !(iss >> indent)) || indent != ',')
            throw std::runtime_error("Missing indent after index.");
        m_Info.getCardDeck().push_back(index);
    }

    if(!getline(configFile, line) && line.empty())
        throw std::runtime_error("Missing empty line after player's cards.");
}
// serialize into file methods -----------------------------------------------------------------------------------------
void CPlayer::Serialize(std::ofstream &saveFile)
{
    saveFile << m_Name << "\n\n";

    for(size_t i = 0; i < m_Info.getCards().size(); i++)
        saveFile << m_Info.getCards()[i] << (i != m_Info.getCards().size() - 1 ? "," : "\n\n");

    m_Info.Serialize(saveFile);
}
//----------------------------------------------------------------------------------------------------------------------