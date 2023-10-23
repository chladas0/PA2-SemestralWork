//
// Created by chladas on 4/9/23.
//

#include "CCardDeck.h"


//----------------------------------------------------------------------------------------------------------------------
int CCardDeck::getRandomCardPos() const
{
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> dis(0, m_Data.size());
    return dis(gen) % m_Data.size();
}
//----------------------------------------------------------------------------------------------------------------------
std::shared_ptr<CCard> CCardDeck::getCardFromPos(size_t pos) const
{
    return pos < m_Data.size() ? m_Data[pos] : nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
size_t CCardDeck::Size()
{
    return m_Data.size();
}
//----------------------------------------------------------------------------------------------------------------------
void CCardDeck::Serialize(std::ofstream &saveFile)
{
    for(const auto & card : m_Data)
        card->Serialize(saveFile);

    saveFile << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void CCardDeck::InitFromFile(std::ifstream & loadFile,  const std::set<std::string>& knownUnits,
                             const std::set<std::string>& knownResources)
{
    auto newCard = std::make_shared<CCard>();

    while(newCard->initFromFile(loadFile, knownUnits, knownResources))
    {
        m_Data.push_back(newCard);
        newCard = std::make_shared<CCard>();
    }
}
//----------------------------------------------------------------------------------------------------------------------
CCardDeck::CCardDeck(const CCardDeck & other)
{
    for(const auto & card : other.m_Data)
        m_Data.push_back(std::make_shared<CCard>(*card));
}
//----------------------------------------------------------------------------------------------------------------------
CCardDeck &CCardDeck::operator=(CCardDeck other)
{
    std::swap(m_Data, other.m_Data);
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------