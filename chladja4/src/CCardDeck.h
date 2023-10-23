//
// Created by chladas on 4/9/23.
//

#pragma once

#include "CCard.h"
#include <random>

/**
 *      Function that represents the card deck. The card deck can be initialized from file and
 *      serialized as well. It holds pack of cards in vector.
 */

class CCardDeck
{
public:
    CCardDeck() = default;
    CCardDeck(const CCardDeck &);
    CCardDeck & operator = (CCardDeck);

    /// get card from given position in card deck
    [[nodiscard]] std::shared_ptr<CCard> getCardFromPos(size_t pos) const;
    /// get random card position
    [[nodiscard]] int getRandomCardPos() const;
    /// get size of the card deck
    size_t Size();
    /**
     *  Method that serializes the card deck into file by call Serialize method on
     *  each CCard.
     * @param saveFile - file to save the card in
     */
    void Serialize(std::ofstream & saveFile);
    /**
     *  Method that initializes card deck from file. It validates the card resources and units
     *  by comparing the with the global resources and units.
     * @param loadFile - file to load the game from
     * @param knownUnits - set of global units represented as string
     * @param knownResources - set of global resources represented as string
     */
    void InitFromFile(std::ifstream & loadFile, const std::set<std::string>& knownUnits, const std::set<std::string>& knownResources);

private:
    /// vector that holds cards using shared pointer to keep the dynamic binding
    std::vector<std::shared_ptr<CCard>> m_Data;
};

// TODO COPY OPERATOR =
