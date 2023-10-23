//
// Created by chladas on 4/7/23.
//

#include "CCard.h"
#include "CRefillEffect.h"

//----------------------------------------------------------------------------------------------------------------------
void CCard::Display()
{
    std::cout << m_Name << std::endl << "Effects: {";
    for(const auto & effect : m_Effects)
    {
        std::cout << (effect == m_Effects.front() ? "" : ", ");
        effect->Print();
    }
    std::cout << "} " << "Costs: {";

    for(const auto & [resource, amount] : m_Cost)
        std::cout << (resource == m_Cost.begin()->first ? "" : ", ") << resource << " -> " << amount;

    std::cout << "}" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
const std::map<std::string, int> & CCard::getCost() const
{
    return m_Cost;
}
//----------------------------------------------------------------------------------------------------------------------
int CCard::getDefense() const
{
    return m_Defense;
}
//----------------------------------------------------------------------------------------------------------------------
int CCard::getAttack() const
{
    return m_Attack;
}
//----------------------------------------------------------------------------------------------------------------------
const std::vector<std::shared_ptr<CEffect>> & CCard::getEffects() const
{
    return m_Effects;
}
//----------------------------------------------------------------------------------------------------------------------
bool CCard::isOverPowered() const
{
    return m_Attack > STRONG_CARD || m_Defense > STRONG_CARD;
}
// init methods --------------------------------------------------------------------------------------------------------
bool CCard::initFromFile(std::ifstream & configFile, const std::set<std::string> & knownUnits,
                                                     const std::set<std::string> & knownResources)
{
    std::string line;
    if(std::getline(configFile, line) && line.empty())
        return false;

    std::istringstream iss(line);

    if(!getline(iss, m_Name, ',') || m_Name.empty())
        throw std::runtime_error("Invalid card name in examples file");

    readCosts(iss, knownResources);
    readAIValues(iss);
    readEffects(iss, knownUnits, knownResources);
    return true;
}
//----------------------------------------------------------------------------------------------------------------------
void CCard::readEffects(std::istringstream & iss, const std::set<std::string> & knownUnits,
                                                  const std::set<std::string> & knownResources)
{
    char type, indent;
    std::shared_ptr<CEffect> newEffect;

    while(iss >> type)
    {
        switch (type)
        {
            case EEffectType::resource:
                newEffect = std::make_shared<CResourceChange>(knownResources);
                break;
            case EEffectType::base:
                newEffect = std::make_shared<CBaseChange>();
                break;
            case EEffectType::unit:
                newEffect = std::make_shared<CUnitChange>(knownUnits);
                break;
            case EEffectType::swapCards:
                newEffect = std::make_shared<CCardSwap>();
                break;
            case EEffectType::refill:
                newEffect = std::make_shared<CRefillEffect>();
                break;
            default:
                throw std::runtime_error("Unknown effect type");
        }
        newEffect->Read(iss);
        m_Effects.emplace_back(std::move(newEffect));

        if(!(iss >> indent && indent == ',') && !iss.eof())
            throw std::runtime_error("Missing indent");
    }

    if(m_Effects.empty())
        throw std::runtime_error("Card cant have empty effects");
}
//----------------------------------------------------------------------------------------------------------------------
void CCard::readCosts(std::istringstream & iss, const std::set<std::string> & knownResources)
{
    std::string resource;
    size_t amount;
    char indent;

    while(getline(iss, resource, ',') && !resource.empty())
    {
        if(!(iss >> amount) || knownResources.count(resource) == 0)
            throw std::runtime_error("Invalid resource in config file");
        else
            m_Cost[resource] = amount;

        if(!iss.eof() && !(iss >> indent) && indent != ',' && indent != ';')
            throw std::runtime_error("Invalid indent in config file");
        else if(indent == '|')
            return;
    }
    throw std::runtime_error("Missing indent in config file");
}
//----------------------------------------------------------------------------------------------------------------------
void CCard::readAIValues(std::istringstream &iss)
{
    char indent;
    if(! (iss >> m_Attack && iss >> indent && indent == ',' && iss >> m_Defense && iss >> indent && indent == '|'))
        throw std::runtime_error("Failed read card values for AI");
}
//----------------------------------------------------------------------------------------------------------------------
void CCard::Serialize(std::ofstream &saveFile)
{
    saveFile << m_Name;

    for(const auto & cost : m_Cost)
        saveFile << "," << cost.first << "," << cost.second;

    saveFile << "|" << m_Attack << "," << m_Defense << "|";

    for(auto it = m_Effects.begin(); it != m_Effects.end(); it++)
    {
        if (it != m_Effects.begin())
            saveFile << ",";
        (*it)->Serialize(saveFile);
    }

    saveFile << std::endl;
}

CCard::CCard(const CCard & other)
{
    m_Name    = other.m_Name;
    m_Cost    = other.m_Cost;
    m_Defense = other.m_Defense;
    m_Attack  = other.m_Attack;

    for(const auto & effect : other.m_Effects)
        m_Effects.push_back(effect->Clone());
}

CCard &CCard::operator=(CCard other)
{
    std::swap(m_Name, other.m_Name);
    std::swap(m_Cost, other.m_Cost);
    std::swap(m_Defense, other.m_Defense);
    std::swap(m_Attack, other.m_Attack);
    std::swap(m_Effects, other.m_Effects);
    return *this;
}

std::vector<std::shared_ptr<CEffect>> &CCard::getEffects()
{
    return m_Effects;
}