//
// Created by chladas on 4/14/23.
//

#pragma once
#include "CChangeEffect.h"
#include "set"

/**
 *      Class representing resource change. Based on it's power inherited from CChangeEffect
 *      it either ads resource to the player for power > 0 or subtract resources for power < 0
 */
class CResourceChange : public CChangeEffect
{
public:
    /**
     *  Constructor
     * @param knownResources - global known resources to validate the m_Resource
     */
    explicit CResourceChange(const std::set<std::string> & knownResources);
    /**
     *  Method that applies the effect. It changes the amount of m_Resource. It's used on
     *  player, enemy or both based on m_ChangeType
     * @param player - information about the current player
     * @param enemy - information about the enemy player
     */
    void Apply(CPlayerInfo & player, CPlayerInfo & enemy) const override;
    /**
     *  Method that reads resource change from file. Calls CEffect::Read as well.
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
    /**
     *  Virtual destructor
     */
    ~CResourceChange() override = default;
private:
    /// reference to the global known resources
    const std::set<std::string>  &  m_KnownResources;
    /// type of resource that will be the effect used on
    std::string                     m_Resource;
};