//
// Created by chladas on 4/14/23.
//

#include "CResourceChange.h"


//----------------------------------------------------------------------------------------------------------------------
CResourceChange::CResourceChange(const std::set<std::string> &knownResources)
        : m_KnownResources(knownResources)
{}
//----------------------------------------------------------------------------------------------------------------------
void CResourceChange::Apply(CPlayerInfo & player, CPlayerInfo & enemy) const
{
    if(m_Power > 0)
        player.modifyResources(m_Resource, m_Power);
    else
        enemy.modifyResources(m_Resource, m_Power);
}
//----------------------------------------------------------------------------------------------------------------------
void CResourceChange::Read(std::istringstream & iss)
{
    CChangeEffect::Read(iss);

    char indent;
    if ((iss >> indent && indent == ',' && getline(iss, m_Resource, ';'))){
        if (m_KnownResources.count(m_Resource) == 0)
            throw std::runtime_error("Unknown resource");
    }
    else
        throw std::runtime_error("Failed reading effect.");
}
//----------------------------------------------------------------------------------------------------------------------
void CResourceChange::Print() const
{
    std::cout << m_Resource;
    CChangeEffect::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void CResourceChange::Serialize(std::ofstream &saveFile) const
{
    saveFile << 'r';
    CChangeEffect::Serialize(saveFile);
    saveFile << "," << m_Resource << ";";
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CEffect> CResourceChange::Clone() const
{
    return std::make_shared<CResourceChange>(*this);
}
//----------------------------------------------------------------------------------------------------------------------
