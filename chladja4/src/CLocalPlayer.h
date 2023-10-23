//
// Created by chladas on 4/7/23.
//

#pragma once

#include "CPlayer.h"
#include "CInterface.h"

/**
 *      Class that represent local player. When local player is making move
 *      he will be prompted to enter card number he want's to play.
 */

class CLocalPlayer : public CPlayer
{
public:
    /// creates instance with reference to global card deck an interface to communicate with the player
    CLocalPlayer(CCardDeck & cardDeck, std::shared_ptr<CInterface> & interface);
    /**
     *  Method that prompts player for input -> card or command to be player
     * @param validMove - function that validates move played
     * @return - the index of card to be player or the command represented by negative integer
     */
    int MakeMove(const std::function<bool(int)> & validMove) override;
    /// prompts the player using interface to enter the name and sets it
    void SetName() override;
    /// Displays info about the player;
    void DisplayInfo() const override;
    /**
     *  Method to Clone, used when copying
     * @return - cloned player
     */
    std::shared_ptr<CPlayer> Clone() const override;

private:
    /// interface to communicate with the player
    std::shared_ptr<CInterface>    m_Interface;
};