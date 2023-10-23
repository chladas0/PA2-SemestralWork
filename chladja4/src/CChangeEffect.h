//
// Created by chladas on 5/7/23.
//

#pragma once

#include <memory>
#include "CPlayerInfo.h"
#include "CColorizer.h"
#include "CEffect.h"

/**
 *      Abstract class that represents effect that causes some change in player's info. If
 *      the power is less than zero it's applied on enemy, otherwise on the player.
 */
class CChangeEffect : public CEffect
{
public:
    /**
     *  Virtual method that applies effect on player based on m_ChangeType.
     * @param player - information about the current player
     * @param enemy - information about the enemy player
     */
    void Apply(CPlayerInfo & player, CPlayerInfo & enemy) const override = 0;
    /**
     *  Method that reads the CBaseChange from file. It uses the parent read method
     *  to read the abstract effect.
     * @param iss - line to read the base change from
     */
    void Read(std::istringstream & iss) override;
    /**
     *  Method that serializes the base change into file
     * @param saveFile - file to be saved into
     */
    void Serialize(std::ofstream & saveFile) const override;
    /**
     *  Method that prints the base change. It uses the parent method.
     */
    void Print() const override;
    /**
     *  Virtual destructor
     */
    ~CChangeEffect() override = default;
protected:
    /// determines strength of the attack and on whom it's applied
    int m_Power;
};
