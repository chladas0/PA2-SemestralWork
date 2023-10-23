//
// Created by chladas on 4/13/23.
//
#include "CPlayerInfo.h"


//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::modifyResources(const std::string &resource, int amount)
{
    if(amount < 0 && m_Resources[resource] < abs(amount))
        m_Resources[resource] = 0;
    else
        m_Resources[resource] += amount;
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::modifyUnits(const std::string &unit, int amount)
{
    if(amount < 0 && m_Units[unit] < abs(amount))
        m_Units[unit] = 0;
    else
        m_Units[unit] += amount;
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::refillResources()
{
    for(auto & [name, amount] : m_Resources)
        amount += m_Units[m_ResourceUnitMap[name]];
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::DisplayInfo() const
{
    m_Base.display();

    for(const auto & [unit, amount] : m_Units)
        std::cout << unit << ": " << amount << " ";
    std::cout <<  std::endl;

    for(const auto & current : m_Resources)
        std::cout << current.first << ": " << current.second << " ";
    std::cout << "\n\n";
}
//----------------------------------------------------------------------------------------------------------------------
int CPlayerInfo::getResourceAmount(const std::string &resource)
{
    return m_Resources[resource];
}
//----------------------------------------------------------------------------------------------------------------------
CBase & CPlayerInfo::getBase()
{
    return m_Base;
}
//----------------------------------------------------------------------------------------------------------------------
const std::vector<size_t> & CPlayerInfo::getCardDeck () const
{
    return m_CardDeck;
}
//----------------------------------------------------------------------------------------------------------------------
std::vector<size_t> & CPlayerInfo::getCards()
{
    return m_CardDeck;
}
//----------------------------------------------------------------------------------------------------------------------
std::vector<size_t> &CPlayerInfo::getCardDeck()
{
    return m_CardDeck;
}
// file saving methods -------------------------------------------------------------------------------------------------
void CPlayerInfo::Serialize(std::ofstream &saveFile)
{
    m_Base.Serialize(saveFile);

    for (const auto &[resource, unit]: m_ResourceUnitMap)
        saveFile << resource << "," << unit << std::endl;

    saveFile << std::endl;

    for (const auto &[resource, amount]: m_Resources)
        saveFile << resource << "," << amount << std::endl;

    saveFile << std::endl;

    for (const auto &[unit, amount]: m_Units)
        saveFile << unit << "," << amount << std::endl;

    saveFile << std::endl;
}
// file init methods ---------------------------------------------------------------------------------------------------
void CPlayerInfo::initFromFile(std::ifstream &configFile, const std::set<std::string> & knownUnits,
                               const std::set<std::string> & knownResources)
{
    this->m_Base.initFromFile(configFile);

    this->readRefillMap(configFile, knownUnits, knownResources);

    this->readResources(configFile);

    this->readUnits(configFile);

    if(m_Resources.empty() || m_ResourceUnitMap.empty() || m_Units.empty())
        throw std::runtime_error("Missing configuration of resources, refill map or units.");
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::readRefillMap(std::ifstream &configFile, const std::set<std::string> & knownUnits,
                                const std::set<std::string> & knownResources)
{
    std::string line, resource, unit;

    while(getline(configFile, line) && !line.empty())
    {
        std::istringstream iss(line);
        if(getline(iss, resource, ',') && iss >> unit && knownUnits.count(unit) != 0 && knownResources.count(resource) != 0)
            m_ResourceUnitMap[resource] = unit;
        else
            throw std::runtime_error("Invalid CSV format in examples file -> invalid resource or unit");
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::readResources(std::ifstream &configFile)
{
    std::string line, type;
    size_t amount;

    while(std::getline(configFile, line) && !line.empty())
    {
        std::istringstream iss(line);

        if(!(getline(iss, type, ',') && (iss >> amount && iss.eof())))
            throw std::runtime_error("Failed reading resources invalid resource or amount");

        if(m_ResourceUnitMap.count(type) == 0)
            throw std::runtime_error("Failed reading resource -> Only resources defined in refill map are allowed.");

        m_Resources[type] = amount;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CPlayerInfo::readUnits(std::ifstream &configFile)
{
    std::string line, unit;
    size_t amount;

    while(std::getline(configFile, line) && !line.empty())
    {
        std::istringstream iss(line);

        if(!(getline(iss, unit, ',') && (iss >> amount && iss.eof())))
            throw std::runtime_error("Failed reading unit invalid unit or amount.");

        for(const auto & current : m_ResourceUnitMap)
            if(current.second == unit)
                m_Units[unit] = amount;

        if(m_Units.count(unit) == 0)
            throw std::runtime_error("Failed reading unit -> Only units defined in refill map are allowed.");
    }
}
//----------------------------------------------------------------------------------------------------------------------