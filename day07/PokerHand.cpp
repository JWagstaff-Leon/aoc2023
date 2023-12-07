#include "PokerHand.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

PokerHand::PokerHand(CardType card1, CardType card2, CardType card3, CardType card4, CardType card5)
{
    hand_.push_back(card1);
    hand_.push_back(card2);
    hand_.push_back(card3);
    hand_.push_back(card4);
    hand_.push_back(card5);

    std::map<CardType, int> cards;
    for(auto card : hand_)
    {
        auto foundCard = cards.find(card);
        if(foundCard == cards.end())
            cards.insert(std::pair<CardType, int>(card, 1));
        else
            foundCard->second += 1;
    }

    switch(cards.size())
    {
        case 1:
            type_ = PokerHandType::FivePair;
            break;
        
        case 2:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card;

            if(card1->second == 4 ||card2->second == 4)
                type_ = PokerHandType::FourPair;
            else
                type_ = PokerHandType::FullHouse;
        }
            break;

        case 3:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card++;
            auto card3 = card;

            if(card1->second == 3 || card2->second == 3 || card3->second == 3)
                type_ = PokerHandType::ThreePair;
            else
                type_ = PokerHandType::TwoPair;
                
        }
            break;

        case 4:
            type_ = PokerHandType::OnePair;
            break;

        case 5:
            type_ = PokerHandType::HighCard;
            break;
    };
};



PokerHandType PokerHand::getType() const
{
    return type_;
};



CardType PokerHand::getCard(int index) const
{
    if(index < 0 || hand_.size() <= index)
        return CardType::Invalid;

    return hand_[index];
};



bool PokerHand::isLessThan(const PokerHand& rhs) const
{
    if(this->getType() != rhs.getType())
        return this->getType() < rhs.getType();
    
    for(int i = 0; i < hand_.size(); i++)
    {
        if(this->getCard(i) != rhs.getCard(i))
            return this->getCard(i) < rhs.getCard(i);
    }
    return false;
};





std::ostream& operator<< (std::ostream& sout, const PokerHand pokerHand)
{
    switch(pokerHand.type_)
    {
        case PokerHandType::FivePair :
            sout << "FivePair | ";
            break;
        case PokerHandType::FourPair :
            sout << "FourPair | ";
            break;
        case PokerHandType::FullHouse :
            sout << "FullHouse | ";
            break;
        case PokerHandType::ThreePair :
            sout << "ThreePair | ";
            break;
        case PokerHandType::TwoPair :
            sout << "TwoPair | ";
            break;
        case PokerHandType::OnePair :
            sout << "OnePair | ";
            break;
        case PokerHandType::HighCard :
            sout << "HighCard | ";
            break;
    }
    for(auto card : pokerHand.hand_)
    {
        switch(card)
        {
            case CardType::A:
                sout << "A";
                break;
            case CardType::K:
                sout << "K";
                break;
            case CardType::Q:
                sout << "Q";
                break;
            case CardType::J:
                sout << "J";
                break;
            case CardType::Ten:
                sout << "T";
                break;
            case CardType::Nine:
                sout << "9";
                break;
            case CardType::Eight:
                sout << "8";
                break;
            case CardType::Seven:
                sout << "7";
                break;
            case CardType::Six:
                sout << "6";
                break;
            case CardType::Five:
                sout << "5";
                break;
            case CardType::Four:
                sout << "4";
                break;
            case CardType::Three:
                sout << "3";
                break;
            case CardType::Two:
                sout << "2";
                break;
        }
    }
    return sout;
};