//
// Created by chladas on 5/7/23.
//

#pragma once

#include <memory>
#include "CEffect.h"

/**
 *      Class that represents additional resource refilling. After each loop the resources
 *      refill automatically. This card can refill resources when played, so the refill happens
 *      multiple times.
 */

class CRefillEffect : public CEffect
{
public:
    /**
     *  Method that applies the effect. It adds resources, based on refill map and number
     *  of units for each resource.
     * @param player - information about the current player
     * @param enemy - information about the enemy player
    */
    void Apply(CPlayerInfo &player, CPlayerInfo &enemy) const override;
    /**
     *  Method that reads refill effect from file as EEffectType
     * @param iss - line to be read from
     */
    void Read(std::istringstream &iss) override;
    /**
      *  Method that serializes the refill effect into file as EEffectType.
      * @param saveFile
      */
    void Serialize(std::ofstream &saveFile) const override;
    /**
     *  Method that prints the refill effect and how many times it will be applied.
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
    ~CRefillEffect() override = default;
private:
    size_t     m_Times;
};
