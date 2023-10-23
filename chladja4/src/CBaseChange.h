//
// Created by chladas on 4/14/23.
//

#pragma once

#include "CChangeEffect.h"


/**
 *      This class represents the base change effect. It's polymorphic class that inherits from CChangeEffect.
 *      Read method is not overridden, there is no need to read additional data
 */
class CBaseChange : public CChangeEffect
{
public:
    /**
     *  Method that modifies the base of current player or the enemy
     * @param player - information about the current player
     * @param enemy - information about the enemy player
     */
    void Apply(CPlayerInfo & player, CPlayerInfo & enemy) const override;
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
     *  Method to Clone, used when copying
     * @return - cloned effect
     */
    std::shared_ptr<CEffect> Clone() const override;
    /**
     *  Virtual destructor
     */
    ~CBaseChange() override = default;
};

