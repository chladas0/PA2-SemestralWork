//
// Created by chladas on 4/14/23.
//
#pragma once

#include "CPlayer.h"
#include "CCommandHandler.h"
#include "unistd.h"

/**
 *      This class represents simple AI player. The AI only acts based on its own internal state
 *      and does not take into account the status of the opposing player. The strategy is simple,
 *      first check if there is any overpowered card, if so, play it. If the player has low health
 *      or high health he plays defensive card -> trying to save himself or finish base. Otherwise
 *      he plays offensive card.
 */

class CAIPlayer : public CPlayer
{
public:
    /**
     * Creates instance of CPlayer with reference to global card deck
     */
    explicit CAIPlayer(CCardDeck & cardDeck) : CPlayer(cardDeck){};
    /**
     * Method that returns validated move by validMove function based on simple AI described in class comment
     * @param validMove - function that validates move
     * @return index in player's card deck representing the desired move, or negative value for commands
     */
    int MakeMove(const std::function<bool(int)> & validMove) override;
    /**
     * Method that returns the most defensive move based on defense number of the card
     * @param possibleMoves - vector of valid moves represented by indexes into card deck
     * @return the most defensive move, it's recognized by having the highest defensive number,
     * move is represented by index into player's card deck
     */
    [[nodiscard]] int DefensiveMove(const std::vector<int> & possibleMoves) const;
    /**
     * Method that returns the most offensive move based on offense number of the card
     * @param possibleMoves vector of valid moves represented by indexes into card deck
     * @return the most defensive move, it's recognized by having the highest offensive number,
     * move is represented by index into player's card deck
     */
    [[nodiscard]] int OffensiveMove(const std::vector<int> & possibleMoves) const;
    /**
     *  Method that displays info about the player. It prints colorized padded name and calls parent DisplayInfo
     */
    void DisplayInfo() const override;
    /**
     *  Polymorphic method that sets name to ULTIMATE AI
     */
    void SetName() override;
    /**
     *  Method to Clone, used when copying
     * @return - cloned player
     */
    std::shared_ptr<CPlayer> Clone() const override;
};
