//
// Created by chladas on 4/7/23.
//

#pragma once

#include "set"
#include "memory"
#include "CBaseChange.h"
#include "CResourceChange.h"
#include "CUnitChange.h"
#include "EEffectType.h"
#include "CCardSwap.h"


/// if defense or attack number is over that value its considered overpowered
constexpr int STRONG_CARD = 8;

/**
 *      Class that represents card. One card can have multiple effects, which are
 *      represented by class represented by classes that inherit from CEffect. Attribute
 *      m_Cost are validate with global known costs.
 */
class CCard
{
public:
    CCard() = default;
    CCard(const CCard &);
    CCard & operator = (CCard);
    /**
     *  Method that displays Card. It displays name, all of it's costs and effects
     */
    virtual void Display();

    /// get the map of costs
    [[nodiscard]] const std::map<std::string, int> & getCost() const;
    /// get the vector of effects
    [[nodiscard]] const std::vector<std::shared_ptr<CEffect>> & getEffects() const;
    /// get Effects used for testing copy constructor
    [[nodiscard]] std::vector<std::shared_ptr<CEffect>> & getEffects();
    /// get defense number for AI
    [[nodiscard]] int getDefense() const;
    /// get attack number for AI
    [[nodiscard]] int getAttack() const;

    /// checks if defense or attack is over STRONG_CARD
    [[nodiscard]] bool isOverPowered() const;
    /**
     *  Method that serializes CCard into file. Card is serialized as name,
     *  all of it's costs and for each effect is called CEffect::Serialize.
     * @param saveFile - file to be serialized into
     */
    void Serialize(std::ofstream & saveFile);
    /**
     *  Method that initializes card from file. Name and costs are read directly and
     *  for each effect is called CEffect::Read.
     * @param configFile
     * @param knownUnits
     * @param knownResources
     * @return
     */
    bool initFromFile(std::ifstream & configFile, const std::set<std::string> & knownUnits,
                      const std::set<std::string> & knownResources);

private:
    /**
     *  Method that reads comma separated effects from file. Each effects needs to be validated
     *  against global resources and units.
     * @param iss - line to read the effects from
     * @param knownUnits - global known units used for validation
     * @param knownResources - global known units used for validation
     */
    void readEffects(std::istringstream & iss, const std::set<std::string> & knownUnits,
                                               const std::set<std::string> & knownResources);
    /**
     *  Method that reads comma separated costs from file. Each cost is read as
     *  {resource,amount}.
     * @param iss - the line to read costs from
     */
    void readCosts(std::istringstream & iss, const std::set<std::string> & knownResources);
    /**
     *  Method that read the values for AI (m_Defense, m_Attack).
     * @param iss the line to read values from
     */
    void readAIValues(std::istringstream & iss);

    /// name of the card
    std::string                           m_Name;
    /// costs of the card as {resource, amount} which are subtracted when buying the card
    std::map<std::string, int>            m_Cost;
    /// effects that can be applied on player
    std::vector<std::shared_ptr<CEffect>> m_Effects;
    /// value for AI representing how much is card defensive
    int                                   m_Defense;
    /// value for AI representing how much is card defensive
    int                                   m_Attack;
};
