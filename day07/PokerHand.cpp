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

    int jokerCount = 0;
    auto foundJokers = cards.find(CardType::Joker);
    if(foundJokers != cards.end())
        jokerCount = foundJokers->second;

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

            if(
                card1->first != CardType::Joker && card1->second + jokerCount == 5 ||
                card2->first != CardType::Joker && card2->second + jokerCount == 5
            )
            {
                type_ = PokerHandType::FivePair;
            }
            else if(
                card1->first != CardType::Joker && card1->second + jokerCount == 4 ||
                card2->first != CardType::Joker && card2->second + jokerCount == 4
            )
            {
                type_ = PokerHandType::FourPair;
            }
            else
            {
                type_ = PokerHandType::FullHouse;
            }
        }
            break;

        case 3:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card++;
            auto card3 = card;

            if(
                card1->first != CardType::Joker && card1->second + jokerCount == 4 ||
                card2->first != CardType::Joker && card2->second + jokerCount == 4 ||
                card3->first != CardType::Joker && card3->second + jokerCount == 4
            )
            {
                type_ = PokerHandType::FourPair;
            }
            else if(
                card1->first != CardType::Joker && card2->first != CardType::Joker &&
                (
                    card1->second == 3 && card2->second + jokerCount == 2 ||
                    card2->second == 3 && card1->second + jokerCount == 2 ||
                    card1->second == 2 && card2->second + jokerCount == 3 ||
                    card2->second == 2 && card1->second + jokerCount == 3
                )
                ||
                card1->first != CardType::Joker && card3->first != CardType::Joker &&
                (
                    card1->second == 3 && card3->second + jokerCount == 2 ||
                    card3->second == 3 && card1->second + jokerCount == 2 ||
                    card1->second == 2 && card3->second + jokerCount == 3 ||
                    card3->second == 2 && card1->second + jokerCount == 3
                )
                ||
                card2->first != CardType::Joker && card3->first != CardType::Joker &&
                (
                    card2->second == 3 && card3->second + jokerCount == 2 ||
                    card3->second == 3 && card2->second + jokerCount == 2 ||
                    card2->second == 2 && card3->second + jokerCount == 3 ||
                    card3->second == 2 && card2->second + jokerCount == 3
                )
            )
            {
                type_ = PokerHandType::FullHouse;
            }
            else if(
                card1->first != CardType::Joker && card1->second + jokerCount == 3 ||
                card2->first != CardType::Joker && card2->second + jokerCount == 3 ||
                card3->first != CardType::Joker && card3->second + jokerCount == 3
            )
            {
                type_ = PokerHandType::ThreePair;
            }
            else
            {
                type_ = PokerHandType::TwoPair;
            }
        }
            break;

        case 4:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card++;
            auto card3 = card++;
            auto card4 = card;

           if(
                card1->first != CardType::Joker && card1->second + jokerCount == 3 ||
                card2->first != CardType::Joker && card2->second + jokerCount == 3 ||
                card3->first != CardType::Joker && card3->second + jokerCount == 3 ||
                card4->first != CardType::Joker && card4->second + jokerCount == 3
            )
            {
                type_ = PokerHandType::ThreePair;
            }
            else if(
                card1->first != CardType::Joker && card2->first != CardType::Joker &&
                (
                    card1->second == 2 && card2->second + jokerCount == 2 ||
                    card2->second == 2 && card1->second + jokerCount == 2 
                )
                ||
                card1->first != CardType::Joker && card3->first != CardType::Joker &&
                (
                    card1->second == 2 && card3->second + jokerCount == 2 ||
                    card3->second == 2 && card1->second + jokerCount == 2
                )
                ||
                card1->first != CardType::Joker && card4->first != CardType::Joker &&
                (
                    card1->second == 2 && card4->second + jokerCount == 2 ||
                    card4->second == 2 && card1->second + jokerCount == 2
                )
                ||
                card2->first != CardType::Joker && card3->first != CardType::Joker &&
                (
                    card2->second == 2 && card3->second + jokerCount == 2 ||
                    card3->second == 2 && card2->second + jokerCount == 2
                )
                ||
                card2->first != CardType::Joker && card4->first != CardType::Joker &&
                (
                    card2->second == 2 && card4->second + jokerCount == 2 ||
                    card4->second == 2 && card2->second + jokerCount == 2
                )
                ||
                card3->first != CardType::Joker && card4->first != CardType::Joker &&
                (
                    card3->second == 2 && card4->second + jokerCount == 2 ||
                    card4->second == 2 && card3->second + jokerCount == 2
                )
            )
            {
                type_ = PokerHandType::TwoPair;
            }
            else
            {
                type_ = PokerHandType::OnePair;
            }
        }
            break;

        case 5:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card++;
            auto card3 = card++;
            auto card4 = card++;
            auto card5 = card;

            if(
                card1->first != CardType::Joker && card1->second + jokerCount == 2 ||
                card2->first != CardType::Joker && card2->second + jokerCount == 2 ||
                card3->first != CardType::Joker && card3->second + jokerCount == 2 ||
                card4->first != CardType::Joker && card4->second + jokerCount == 2 ||
                card5->first != CardType::Joker && card5->second + jokerCount == 2
            )
            {
                type_ = PokerHandType::OnePair;
            }
            else
            {
                type_ = PokerHandType::HighCard;
            }
        }
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