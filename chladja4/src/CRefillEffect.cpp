//
// Created by chladas on 5/7/23.
//

#include "CRefillEffect.h"


//----------------------------------------------------------------------------------------------------------------------
void CRefillEffect::Apply(CPlayerInfo &player, CPlayerInfo &enemy) const
{
    for(size_t i = 0; i < m_Times; i++)
        player.refillResources();
}
//----------------------------------------------------------------------------------------------------------------------
void CRefillEffect::Read(std::istringstream &iss)
{
    char indent;
    if(!(iss >> indent && indent == ',' && iss >> m_Times) || m_Times == 0)
        throw std::runtime_error("Failed reading effect");
}
//----------------------------------------------------------------------------------------------------------------------
void CRefillEffect::Serialize(std::ofstream &saveFile) const
{
    saveFile << "f" << "," << m_Times;
}
//----------------------------------------------------------------------------------------------------------------------
void CRefillEffect::Print() const
{
    std::cout << m_Times <<"x resource refill";
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CEffect> CRefillEffect::Clone() const
{
    return std::make_shared<CRefillEffect>(*this);
}
//----------------------------------------------------------------------------------------------------------------------