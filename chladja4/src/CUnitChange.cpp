//
// Created by chladas on 4/25/23.
//

#include "CUnitChange.h"


//----------------------------------------------------------------------------------------------------------------------
CUnitChange::CUnitChange(const std::set<std::string> &knownUnits)
        : m_KnownUnits(knownUnits)
{
}
//----------------------------------------------------------------------------------------------------------------------
void CUnitChange::Apply(CPlayerInfo & player, CPlayerInfo & enemy) const
{
    if(m_Power > 0)
        player.modifyUnits(m_Unit, m_Power);
    else
        enemy.modifyUnits(m_Unit, m_Power);
}
//----------------------------------------------------------------------------------------------------------------------
void CUnitChange::Read(std::istringstream &iss)
{
    CChangeEffect::Read(iss);

    char indent;
    if ((iss >> indent && indent == ',' && getline(iss, m_Unit, ';'))) {
        if (m_KnownUnits.count(m_Unit) == 0)
            throw std::runtime_error("Unknown resource");
    }
    else
        throw std::runtime_error("Failed reading effect.");
}
//----------------------------------------------------------------------------------------------------------------------
void CUnitChange::Print() const
{
    std::cout << m_Unit;
    CChangeEffect::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void CUnitChange::Serialize(std::ofstream &saveFile) const
{
    saveFile << "u";
    CChangeEffect::Serialize(saveFile);
    saveFile << "," << m_Unit << ";";
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CEffect> CUnitChange::Clone() const
{
    return std::make_shared<CUnitChange>(*this);
}
//----------------------------------------------------------------------------------------------------------------------