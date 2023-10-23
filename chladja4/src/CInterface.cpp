//
// Created by chladas on 4/20/23.
//

#include "CInterface.h"

using namespace std::filesystem;


//----------------------------------------------------------------------------------------------------------------------
CInterface::CInterface(std::istream &in, std::ostream &out)
        : m_In(in), m_Out(out), m_Commands(CCommandHandler())
{}
//----------------------------------------------------------------------------------------------------------------------
int CInterface::GameTypeMenu()
{
    ClearOutput();
    int gameType;
    m_Out << "Welcome to the Ant game" << "\n\n"
    << "(0) New game -> " << CColorizer::Green("player") << " vs " << CColorizer::Green("player") << std::endl
    << "(1) New game -> " << CColorizer::Green("player") << " vs " << CColorizer::Red("AI ")      << std::endl
    << "(2) Saved game -> Load from a file" << std::endl << "Choose the type of game: ";

    while(!(m_In >> gameType) || gameType < 0 || gameType > 2)
    {
        ClearInput();
        CheckEof();
        m_Out << "Valid options are only 0, 1, 2" << std::endl;
    }
    return gameType;
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::ShowSavedGames()
{
    for (const auto & entry : directory_iterator(current_path() / path("examples")))
    {
        std::string file = entry.path().filename();

        m_Out << (file.size() > 4 && file.substr(file.size() - 4) == ".csv" ?
        CColorizer::Green("-> " + file) : "-> " + file) << std::endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::PrintLine(const std::string &line)
{
    m_Out << line << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::DisplayWinner(const std::string & winnerName)
{
    m_Out << "Congratulations player: " << winnerName << " You've won!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::DisplayAfterGame()
{
    m_Out << "The game will now end, come back soon!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::DisplayHelp()
{
    PrintLine("\nValid commands are " + CColorizer::Green("\nquit") + " -> surrender"
              + CColorizer::Green("\nsave") + " -> save game\n");
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::DisplayMove(std::shared_ptr<CCard> &card)
{
    m_Out << "Playing card: ";
    card->Display();
    m_Out <<  std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
std::string CInterface::PromptFileNameForSave()
{
    std::string fileName, command;
    while(true)
    {
        m_Out << "Enter the name of the file where you want to save the game." << std::endl;
        ShowSavedGames();

        if(m_In >> fileName)
        {
            if(presentFile(fileName))
            {
                m_Out << "Do you really want to overwrite the file: " << fileName << "?  (" <<
                CColorizer::Green("yes") << ", " << CColorizer::Red("no")    << ")" << std::endl;
                while(true)
                {
                    if(m_In >> command)
                    {
                        if(command == "yes")
                            return current_path() / path("examples") / path(fileName);
                        else if (command == "no")
                            break;
                    }
                    m_Out << "Failed to read " << CColorizer::Green("yes") << " or "
                                                      << CColorizer::Red("no") << std::endl;
                    ClearInput();
                    CheckEof();
                }
            }
            else
                return current_path() / path("examples") / path(fileName);
        }
        else
            m_Out << "Failed to read the file name" << std::endl;
        CheckEof();
        ClearInput();
    }
}
//----------------------------------------------------------------------------------------------------------------------
std::string CInterface::PromptPlayerName()
{
    while(true)
    {
        std::string name;
        m_Out << "Enter name:  ";

        if(m_In >> name)
            return name;
        else
            m_Out << "You entered an invalid name" << std::endl;
        CheckEof();
        ClearInput();
    }
}
//----------------------------------------------------------------------------------------------------------------------
int CInterface::PromptMoveOrCommand(const std::function<bool(int)> & validMove, std::string & name)
{
    int move;
    std::string command;
    while(true)
    {
        m_Out << "Player on turn: " << CColorizer::Green(name) << std::endl << std::endl;
        m_Out << "Enter the number of the card you want to play or \"help\" for instructions : ";

        if(m_In >> move)
        {
            if(validMove(move))
                return move;
            else
            {
                m_Out << "This move is not valid" << std::endl;
                ClearInput();
                continue;
            }
        }
        else
            m_In.clear();

        if(m_In >> command)
        {
            if(m_Commands.ValidCommand(command))
                return m_Commands.ConvertCommand(command);
            else
                m_Out << "This move is not valid" << std::endl;
        }
        CheckEof();
        ClearInput();
    }
}
//----------------------------------------------------------------------------------------------------------------------
std::string CInterface::PromptFileNameForLoad()
{
    std::string fileName;
    while(true)
    {
        m_Out << "Enter the filename from which you want to load the game: " << std::endl;

        ShowSavedGames();

        if(m_In >> fileName)
        {
            if(presentFile(fileName))
                return current_path() / path("examples") / path(fileName);
            else
                m_Out << "This file is not in the /examples directory" << std::endl;
        }
        else
            m_Out << "Failed to read the file name" << std::endl;
        CheckEof();
        ClearInput();
    }
}
//----------------------------------------------------------------------------------------------------------------------
bool CInterface::presentFile(const std::string & filename)
{
    for (const auto &entry: directory_iterator(current_path() / path("examples")))
        if (entry.path().filename() == filename)
            return true;
    return false;
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::CheckEof()
{
    m_In.eof() ? throw std::logic_error("Unexpected EOF (ctrl + d) detected, the game will now end.") : void();
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::ClearInput()
{
    m_In . clear();
    m_In . ignore ( INT32_MAX, '\n' );
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::ClearOutput()
{
    m_Out << std::string(100, '\n');
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::DisplayGame(int prevMove, std::shared_ptr<CPlayer> & curr, std::shared_ptr<CPlayer> & other)
{
    if(prevMove != m_Commands.ConvertCommand("help")){
        ClearOutput();
        other->DisplayInfo();
        curr->DisplayInfo();
        curr->DisplayCards();
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CInterface::DisplayLoading()
{
    PrintLine("Loading the game...");
    sleep(1);
    PrintLine("Global resources loaded | " + CColorizer::Green("Done"));
    sleep(1);
    PrintLine("Global card deck loaded | "  + CColorizer::Green("Done"));
    sleep(1);
    PrintLine("Players initialized | "  + CColorizer::Green("Done"));
    sleep(1);
    PrintLine(CColorizer::Green("Game loaded successfully"));
    sleep(2);
}
//----------------------------------------------------------------------------------------------------------------------
