//
// Created by chladas on 4/14/23.
//

#pragma once

#include <functional>
#include "CPlayerInfo.h"
#include "CColorizer.h"
#include "CCardDeck.h"

/// constant used when printing player's name
constexpr size_t PADDING = 80;

/**
 *      Abstract class that represents player. It defines methods that need to be
 *      implemented in its descendant and some methods that are same for every derived
 *      class as read methods, init, serialize. Player does not have the actual card but
 *      only indexes into the global card deck.
 */

class CPlayer
{
public:
    /**
     *  Constructor that creates CPlayer, having the global card deck as parameter
     */
    explicit CPlayer(CCardDeck & cardDeck) : m_GlobalCardDeck(cardDeck){}
    virtual ~CPlayer() = default;
    /**
     *  Method that return move or command desired by player. It prompts the player
     *  for input using CInterface and validate it.
     * @param validMove - function that determines if the move is valid
     * @return - The desired move (index into m_CardDeck) or negative value for command
     */
    virtual int MakeMove(const std::function<bool(int)> & validMove) = 0;
    /**
     *  prompts the player for name and sets it
     */
    virtual void SetName() = 0;
    /**
     * gets information about player, his resources, base, units
     */
    CPlayerInfo & getPlayerInfo();
    /**
     * getter for players card deck
     * @return - player's card deck
     */
    std::vector<size_t> & getCards();
    /**
     * Method that adds padding to the name based on it's name
     */

    [[nodiscard]] std::string getPaddedName(const std::string & name) const;
    /**
     * Method that prints m_CardDeck
     */
    void DisplayCards() const;
    /**
     * Method that displays information about player as resources, units
     */
    virtual void DisplayInfo() const;
    /**
     *  Method that saves Player into file, saving his name and calling CPlayerInfo::Serialize
     * @param saveFile - file to be serialized into
     */
    void Serialize(std::ofstream & saveFile);
    /**
     *  Method that read player from file. Reading name, card deck and calling CPlayerInfo::initFromFile
     * @param configFile - file to read from
     * @param knownUnits - global known units used to validation
     * @param knownResources - global known resources used to validation
     */
    void InitFromFile(std::ifstream & configFile, const std::set<std::string> & knownUnits,
                      const std::set<std::string> & knownResources);
    /**
     *  Method to Clone, used when copying
     * @return - cloned player
     */
    virtual std::shared_ptr<CPlayer> Clone() const = 0;

    friend class CGame;

private:
    /// Method that read cards as indexes to global card deck
    void readCards(std::ifstream & configFile);
    /// Method that reads name of the player as string
    void ReadName(std::ifstream & configFile);

protected:
    /// name of the player, derived classes sets it themselves
    std::string                                                          m_Name = "Unknown Player";
    /// variables that stores information about player. His resources, units, base.
    CPlayerInfo                                                          m_Info;
    /// reference to the global card deck
    CCardDeck &                                                          m_GlobalCardDeck;
};
