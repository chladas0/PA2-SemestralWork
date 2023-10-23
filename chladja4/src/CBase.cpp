//
// Created by chladas on 4/7/23.
//

#include "CBase.h"


//----------------------------------------------------------------------------------------------------------------------
void CBase::display() const
{
    std::cout << "Base: " << m_Completeness << " (lose=" << m_LoseBound << ", win=" << m_WinBound << ")" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
bool CBase::isCompleted() const
{
    return m_Completeness >= m_WinBound;
}
//----------------------------------------------------------------------------------------------------------------------
bool CBase::isDestroyed() const
{
    return m_Completeness <= m_LoseBound;
}
//----------------------------------------------------------------------------------------------------------------------
void CBase::modifyCompleteness(int amount)
{
    m_Completeness += amount;
}
//----------------------------------------------------------------------------------------------------------------------
bool CBase::shouldPlayDefenseCard() const
{
    return (m_Completeness > m_WinBound - BASE_THRESHOLD) || ( m_Completeness < m_LoseBound + BASE_THRESHOLD);
}
//----------------------------------------------------------------------------------------------------------------------
void CBase::initFromFile(std::ifstream & configFile)
{
    if (!configFile.is_open())
        throw std::ios_base::failure("Failed to open config file");

    std::string line;
    char indent;

    getline(configFile, line);
    std::istringstream iss(line);

    if(line.empty() || !getline(configFile, line) || !line.empty())
        throw std::runtime_error("Invalid CSV format in config file");

    if(!(iss >> m_Completeness && iss >> indent && indent == ',' &&
         iss >> m_LoseBound    && iss >> indent && indent == ',' &&
         iss >> m_WinBound     && iss.eof()))
        throw std::runtime_error("Invalid base information (completeness, lose, win)");
}
//----------------------------------------------------------------------------------------------------------------------
void CBase::Serialize(std::ofstream & saveFile) const
{
    saveFile << m_Completeness << "," << m_LoseBound << "," << m_WinBound << "\n\n";
}
//----------------------------------------------------------------------------------------------------------------------