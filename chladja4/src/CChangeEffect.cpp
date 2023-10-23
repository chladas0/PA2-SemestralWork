//
// Created by chladas on 5/7/23.
//

#include "CChangeEffect.h"


//----------------------------------------------------------------------------------------------------------------------
void CChangeEffect::Read(std::istringstream &iss)
{
    char indent;

    if(!(iss >> indent && indent == ',' && iss >> m_Power && m_Power != 0))
        throw std::runtime_error("Failed reading effect");
}
//----------------------------------------------------------------------------------------------------------------------
void CChangeEffect::Print() const
{
    if(m_Power > 0)
        std::cout << CColorizer::Green(" +") << abs(m_Power);
    else
        std::cout << CColorizer::Red(" -")    << abs(m_Power);
}
//----------------------------------------------------------------------------------------------------------------------
void CChangeEffect::Serialize(std::ofstream &saveFile) const
{
    saveFile << "," << m_Power;
}
//----------------------------------------------------------------------------------------------------------------------