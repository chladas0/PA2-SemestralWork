//
// Created by chladas on 4/7/23.
//

#include "CLocalPlayer.h"


//----------------------------------------------------------------------------------------------------------------------
CLocalPlayer::CLocalPlayer(CCardDeck &cardDeck, std::shared_ptr<CInterface> & interface)
        :   CPlayer(cardDeck),
            m_Interface(interface)
{
}
//----------------------------------------------------------------------------------------------------------------------
int CLocalPlayer::MakeMove(const std::function<bool(int)> & validMove)
{
    return m_Interface->PromptMoveOrCommand(validMove, m_Name);
}
//----------------------------------------------------------------------------------------------------------------------
void CLocalPlayer::SetName()
{
    m_Name = m_Interface->PromptPlayerName();
}
//----------------------------------------------------------------------------------------------------------------------
void CLocalPlayer::DisplayInfo() const
{
   std::cout << CPlayer::getPaddedName(CColorizer::Green(m_Name)) << std::endl;
   CPlayer::DisplayInfo();
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CPlayer> CLocalPlayer::Clone() const
{
    return std::make_shared<CLocalPlayer>(*this);
}
//----------------------------------------------------------------------------------------------------------------------