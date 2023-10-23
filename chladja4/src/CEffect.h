//
// Created by chladas on 4/14/23.
//

#pragma once

#include "CPlayerInfo.h"
#include "CColorizer.h"

/**
 *      Abstract class that defines common interface for working with effects.
 */
class CEffect
{
public:
    /**
     *  Virtual method that applies effect on player based on m_ChangeType.
     * @param player - information about the current player
     * @param enemy - information about the enemy player
     */
    virtual void Apply(CPlayerInfo & player, CPlayerInfo & enemy) const = 0;
    /**
     *  Method that reads the CBaseChange from file. It uses the parent read method
     *  to read the abstract effect.
     * @param iss - line to read the base change from
     */
    virtual void Read(std::istringstream & iss) = 0;
    /**
     *  Method that serializes the base change into file
     * @param saveFile - file to be saved into
     */
    virtual void Serialize(std::ofstream & saveFile) const = 0;
    /**
     *  Method that prints the base change. It uses the parent method.
     */
    virtual void Print() const = 0;
    /**
     *  Method to Clone, used when copying
     * @return - cloned effect
     */
    virtual std::shared_ptr<CEffect> Clone() const = 0;
    /**
     *  Virtual destructor
     */
    virtual ~CEffect() = default;
};
