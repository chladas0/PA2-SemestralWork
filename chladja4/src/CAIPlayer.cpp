//
// Created by chladas on 4/7/23.
//

#include "CAIPlayer.h"


//----------------------------------------------------------------------------------------------------------------------
int CAIPlayer::MakeMove(const std::function<bool(int)> & validMove)
{
    sleep(3);
    std::vector<int> possibleMoves;

    for(size_t i = 0; i < m_Info.getCards().size(); i++)
        if(validMove(i))
            possibleMoves.push_back(i);

    if(possibleMoves.empty())
        return CCommandHandler().ConvertCommand("quit");

    for(auto index : possibleMoves)
        if(m_GlobalCardDeck.getCardFromPos(m_Info.getCardDeck()[index])->isOverPowered())
            return index;

    return m_Info.getBase().shouldPlayDefenseCard() ? DefensiveMove(possibleMoves) : OffensiveMove(possibleMoves);
}
//----------------------------------------------------------------------------------------------------------------------
void CAIPlayer::SetName()
{
    m_Name = "UltimateAI";
}
//----------------------------------------------------------------------------------------------------------------------
int CAIPlayer::DefensiveMove(const std::vector<int> & possibleMoves) const
{
    int bestMove = possibleMoves.front();

    for(auto index : possibleMoves)
    {
        int currentDefense = m_GlobalCardDeck.getCardFromPos(m_Info.getCardDeck()[index])->getDefense();

        if(currentDefense > m_GlobalCardDeck.getCardFromPos(m_Info.getCardDeck()[bestMove])->getDefense())
            bestMove = index;
    }
    return bestMove;
}
//----------------------------------------------------------------------------------------------------------------------
int CAIPlayer::OffensiveMove(const std::vector<int> & possibleMoves) const
{
    int bestMove = possibleMoves.front();

    for(auto index : possibleMoves)
    {
        int currentAttack = m_GlobalCardDeck.getCardFromPos(m_Info.getCardDeck()[index])->getAttack();

        if(currentAttack > m_GlobalCardDeck.getCardFromPos(m_Info.getCardDeck()[bestMove])->getAttack())
            bestMove = index;
    }
    return bestMove;
}
//----------------------------------------------------------------------------------------------------------------------
void CAIPlayer::DisplayInfo() const
{
    std::cout << CPlayer::getPaddedName(CColorizer::Red(m_Name)) << std::endl;
    CPlayer::DisplayInfo();
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CPlayer> CAIPlayer::Clone() const
{
    return std::make_shared<CAIPlayer>(*this);
}
//----------------------------------------------------------------------------------------------------------------------