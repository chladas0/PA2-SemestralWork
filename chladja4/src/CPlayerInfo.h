//
// Created by chladas on 4/13/23.
//
#pragma once

#include <map>
#include <set>
#include "CBase.h"
#include "vector"


/**
 *      Class that stores information about player and provides methods to manipulate
 *      with with his resources and units.
 */

class CPlayerInfo
{
public:
    /**
     *  Method that adds amount to the player's resources of type resource
     * @param resource - type of the resource
     * @param amount - amount to be added can be negative to subtract
     */
    void modifyResources(const std::string & resource, int amount);
    /**
     *  Method that add amount to the player's unit of type unit
     * @param unit - the type of unit
     * @param amount - amount to be added can be negative to subtract
     */
    void modifyUnits(const std::string & unit, int amount);
    /**
     *  Method that refiles resources based on m_ResourceUnitMap. For example if in resources map
     *  is {Soldier, Weapon} than the amount of the soldiers will be add to Weapon resource
     */
    void refillResources();
    /**
     *  Method to find out how much of given resource does player have
     * @param resource - the resource we ask for
     * @return - the amount of resource player has
     */
    int getResourceAmount(const std::string & resource);
    /**
     *  get the player's base
     */
    CBase & getBase();
    /**
     *  get the player's card deck
     */
    const std::vector<size_t> & getCardDeck() const;
    /**
     *  get the player's card deck
     */
    std::vector<size_t> & getCardDeck();
    /**
     *  get the player's card deck
     */
    std::vector<size_t> & getCards();
    /**
     *  Display's information like resources, units
     */
    void DisplayInfo() const;
    /**
     *  Method that serializes player info into file.
     * @param saveFile - file to be saved into
     */
    void Serialize(std::ofstream & saveFile);
    /**
     *  Method that read player info from file. Calls CBase::initFromFile
     * @param configFile - file to read from
     * @param knownUnits - global known units used to validation
     * @param knownResources - global known resources used to validation
     */
    void initFromFile (std::ifstream & configFile, const std::set<std::string> & knownUnits,
                       const std::set<std::string> & knownResources);

private:
    /// function to read refill map as {resource,unit}
    void readRefillMap(std::ifstream & configFile, const std::set<std::string> & knownUnits,
                       const std::set<std::string> & knownResources);
    /// function to read resources as string and amount
    void readResources(std::ifstream & configFile);
    /// function to read units as string and amount
    void readUnits    (std::ifstream & configFile);
    /// function to read cards, using CCard::initFromFile

    /// players resource to buy cards
    std::map<std::string, size_t>                                                 m_Resources;
    /// players units to refill resources
    std::map<std::string, size_t>                                                 m_Units;
    /// map the says which units refill which resources
    std::map<std::string, std::string>                                            m_ResourceUnitMap;
    /// player's base stores information about it's current state
    CBase                                                                         m_Base;
    /// player's card deck as indexes into global card deck
    std::vector<size_t>                                                           m_CardDeck;
};