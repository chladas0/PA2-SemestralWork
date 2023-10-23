//
// Created by chladas on 4/25/23.
//
#pragma once

#include "CChangeEffect.h"
#include "set"

/**
 *      Class representing unit change. It inherits from CEffect and overrides its virtual methods.
 *      Unit change has the unit that will be changed and the type of change inherited from CEffect.
 */

class CUnitChange : public CChangeEffect
{
public:
    /**
     *  Constructor
     * @param knownUnits - global known units to validate m_Unit
     */
    explicit CUnitChange(const std::set<std::string> & knownUnits);
    /**
     *  Method that applies the effect. It changes the amount of m_Unit. It's used on
     *  player, enemy or both based on m_ChangeType
     * @param player - information about the current player
     * @param enemy - information about the enemy player
    */
    void Apply(CPlayerInfo & player, CPlayerInfo & enemy) const override;
    /**
     *  Method that reads units change from file. Calls CEffect::Read as well.
     * @param iss - line to be read from
     */
    void Read(std::istringstream & iss) override;
    /**
     *  Method that serializes the resource change into file. Calls CEffect::Serialize as well.
     * @param saveFile
    */
    void Serialize(std::ofstream & saveFile) const override;
    /**
     *  Method that prints the resource effect. Calls CEffect::Print as well.
     */
    void Print() const override;
    /**
     *  Method to Clone, used when copying
     * @return - cloned effect
     */
    std::shared_ptr<CEffect> Clone() const override;

private:
    /// reference to the global known resources
    const std::set<std::string> & m_KnownUnits;
    /// type of resource that will be the effect used on
    std::string                   m_Unit;
};
