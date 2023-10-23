//
// Created by chladas on 4/20/23.
//

#pragma once
#include "filesystem"
#include "CPlayer.h"
#include "CCommandHandler.h"
#include "unistd.h"

/**
 *      Class that handles communication with the player. Prompts input if needed,
 *      displays information about the game.
 */

class CInterface
{
public:
    CInterface(std::istream & in, std::ostream & out);
    /**
     *  Method that reads input from the player and validates it. If the input is
     *  not valid, it asks again. Card number or known command can be entered.
     * @param validMove - function that checks if the move is valid
     * @param name - name of the prompted player
     * @return validated move as positive value or negative as command
     */
    int PromptMoveOrCommand(const std::function<bool(int)> & validMove, std::string & name);
    /**
     *  Method that ask player for filename to save game. Calls ShowSavedGames and presentFile
     * @return - name of the file
     */
    std::string PromptFileNameForSave();
    /**
     *  Method that ask player for filename to load game. Calls ShowSavedGames and presentFile
     * @return - name of the file
     */
    std::string PromptFileNameForLoad();
    /**
     * Method that asks player for his name
     * @return - players name
     */
    std::string PromptPlayerName();
    /**
     *  Method that displays current game state. For current player is displayed everything,
     *  for the enemy only player info as resources, units and base. If the prev move was
     *  help we don't need to display anything because there are still valid information on
     *  the screen from the previous displaying
     * @param prevMove - previous move made
     * @param curr - current player
     * @param other - other player
     */
    void DisplayGame(int prevMove, std::shared_ptr<CPlayer> & curr, std::shared_ptr<CPlayer> & other);
    /**
     *  Method that simulates loading the game
     */
    void DisplayLoading();
    /**
      *  Method that displays the winner
      * @param winnerName - name to be displayed
      */
    void DisplayWinner(const std::string & winnerName);
    /**
     *  Displays the farewell text
     */
    void DisplayAfterGame();
    /**
     *  Displays the card that was played
     * @param card - card to display
     */
    void DisplayMove(std::shared_ptr<CCard> & card);
    /**
     *  Prints the line ended with new line
     * @param line - line to be printed
     */
    void PrintLine(const std::string & line);
    /**
     * Displays the commands that can be entered
     */
    void DisplayHelp();
    /** Method that iterated through examples directory and shows
     * files present. Making files ending .csv green.
     */
    void ShowSavedGames();
    /**
     * Displays the menu to chose which type of game we want to play
     * @return
     */
    int GameTypeMenu();
    /**
     * Clears the input stream
     */
    void ClearInput();
    /**
     * Clears the output stream using newline
     */
    void ClearOutput();
    /**
     *  Check for error, throws std::logic_error
     */
    void CheckEof();
private:
    /// input stream used to load data from
    std::istream &      m_In;
    /// output stream used to display
    std::ostream &      m_Out;
    /// commands that can be entered
    CCommandHandler     m_Commands;
    /// function that check if file is present in dir examples/
    static bool presentFile(const std::string &filename);
};
