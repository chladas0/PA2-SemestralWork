//
// Created by chladas on 5/7/23.
//

#pragma once

#include <memory>
#include "CEffect.h"
#include "algorithm"


/**
 *      Class that represents card swap. When used, it will be erased from card deck, replaced with
 *      new one and then the card decks will be swapped.
 */
class CCardSwap : public CEffect
{
public:
    /**
     *  Method that applies the effect, swaps the card decks.
     * @param player - information about the current player
     * @param enemy - information about the enemy player
    */
    void Apply(CPlayerInfo &player, CPlayerInfo &enemy) const override;
    /**
     *  Does not need to read additional info
     * @param iss - stream for additional info, not used
     */
    void Read(std::istringstream &iss) override;
    /**
        *  Method that serializes the card swap effect into file as EEffectType.
        * @param saveFile
       */
    void Serialize(std::ofstream &saveFile) const override;
    /**
     *  Method that prints the card swap effect.
     */
    void Print() const override;
    /**
     *  Method to Clone, used when copying
     * @return - cloned effect
     */
    std::shared_ptr<CEffect> Clone() const override;
};

