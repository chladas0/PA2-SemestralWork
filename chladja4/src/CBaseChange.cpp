//
// Created by chladas on 4/14/23.
//

#include "CBaseChange.h"


//----------------------------------------------------------------------------------------------------------------------
void CBaseChange::Apply(CPlayerInfo & player, CPlayerInfo & enemy) const
{
    if(m_Power > 0 )
        player.getBase().modifyCompleteness(m_Power);
    else
        enemy.getBase().modifyCompleteness(m_Power);
}
//----------------------------------------------------------------------------------------------------------------------
void CBaseChange::Print() const
{
    std::cout << "Base";
    CChangeEffect::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void CBaseChange::Serialize(std::ofstream &saveFile) const
{
    saveFile << "b";
    CChangeEffect::Serialize(saveFile);
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CEffect> CBaseChange::Clone() const
{
    return std::make_shared<CBaseChange>(*this);
}