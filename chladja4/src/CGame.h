//
// Created by chladas on 4/7/23.
//

#pragma once

#include "CLocalPlayer.h"
#include "CAIPlayer.h"
#include "CInterface.h"
#include "EGameType.h"

/**
 *      Class that represents game. It handles all the commands and moves desired by players.
 *      It holds 2 players, global resources, units.When initializing the game it calls init
 *      on all of its variables.
 */

const std::string CONFIG_FILE = "examples/defaults";
constexpr size_t DECK_SIZE = 5;

class CGame
{
public:
    /// default constructor setting winner to null and interface to std::in std::out, copy, =
    CGame();
    CGame(const CGame &);
    CGame & operator = (CGame);
    /// function where the main game loop runs
    void run();
private:
    /**
     *  Method that asks player for game type and base on that calls init
     */
    void GameInit();
    /**
     *  Check if players have destroyed or completed bases
     */
    void CheckEndGame();
    /**
     *  Sets the abstract player variables to derived CLocalPlayer or CAIPlayer
     */
    void SetPlayerType();
    /**
     * Handles the move for the current player. Buys the card, erases it, gets new one.
     * @param move - move to be player
     */
    void HandleMove(int move);
    /**
     * Handles command desired by player, changes isRunning if the game should end.
     * @param command - command to be executed
     */
    void HandleCommand(int command);
    /**
     * Check if the player has enough resources to buy the card
     * @param card - card player want to buy
     * @param player - player that wants to by
     * @return - if has enough resources true, else false
     */
    static bool CanBuyCard(const std::shared_ptr<CCard>& card, const std::shared_ptr<CPlayer> & player);
    /**
     * Buys the card, subtracts costs as {resource, amount} from players resources
     * @param card - card to be bought
     * @param player - player that buys
     */
    static void BuyCard(const std::shared_ptr<CCard>& card, const std::shared_ptr<CPlayer> & player);
    /**
     * Method called when initializing game from default config file to
     * randomize the card that players start with
     * @param player
     */
    void RandomizeCards(std::shared_ptr<CPlayer> & player);
    /**
     *  Method that serializes the whole game into file. calls CPlayer::Serialize()
     */
    void SerializeIntoFile();
    /**
     * Loads the game from give file, calls CPlayer::initFromFile
     * @param filename
     */
    void LoadGameFromFile(const std::string & filename);
    /**
     *  Reads the global units from the given file
     */
    void UnitsInit(std::ifstream & );
    /**
     * Reads the global resource from the file.
     */
    void ResourcesInit(std::ifstream & );
    // -----------------------------------------------------------------------------------------------------------------
    /// The global card deck used by player for indexation
    CCardDeck                                                   m_Cards;
    /// The global known resources used for validation
    std::set<std::string>                                       m_Resources;
    /// The global known units used for validation
    std::set<std::string>                                       m_Units;
    /// Player that is on the move
    std::shared_ptr<CPlayer>                                    m_CurrentPlayer;
    /// Player that is not on the move
    std::shared_ptr<CPlayer>                                    m_OtherPlayer;
    /// Signalizes that the game has a winner
    std::shared_ptr<CPlayer>                                    m_Winner;
    /// interface to communicate with player
    std::shared_ptr<CInterface>                                 m_Interface;
    /// Signalizes that the game is running
    bool                                                        m_IsRunning;
    /// Game type for saving into the file (vs AI, vs Player)
    int                                                         m_GameType;
    /// Known commands that can player use
    CCommandHandler                                             m_Commands;
};