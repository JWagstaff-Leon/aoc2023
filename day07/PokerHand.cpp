#include "PokerHand.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

PokerHand::PokerHand(CardType card1, CardType card2, CardType card3, CardType card4, CardType card5)
{
    std::vector<CardType> hand;
    hand.push_back(card1);
    hand.push_back(card2);
    hand.push_back(card3);
    hand.push_back(card4);
    hand.push_back(card5);

    std::map<CardType, int> cards;
    for(auto card : hand)
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
            rankedCards_.push_back(cards.begin()->first);
            break;
        
        case 2:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card;

            if(card1->second == 4)
            {
                type_ = PokerHandType::FourPair;
                rankedCards_.push_back(card1->first);
                rankedCards_.push_back(card2->first);
            }
            else if(card2->second == 4)
            {
                type_ = PokerHandType::FourPair;
                rankedCards_.push_back(card2->first);
                rankedCards_.push_back(card1->first);
            }
            else
            {
                type_ = PokerHandType::FullHouse;
                if(card1->second == 3)
                {
                    rankedCards_.push_back(card1->first);
                    rankedCards_.push_back(card2->first);
                }
                else
                {
                    rankedCards_.push_back(card2->first);
                    rankedCards_.push_back(card1->first);
                }
            }
        }
            break;

        case 3:
        {
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card++;
            auto card3 = card;

            if(card1->second == 3)
            {
                type_ = PokerHandType::ThreePair;
                rankedCards_.push_back(card1->first);
                if(card2->first > card3->first)
                {
                    rankedCards_.push_back(card2->first);
                    rankedCards_.push_back(card3->first);
                }
                else
                {
                    rankedCards_.push_back(card3->first);
                    rankedCards_.push_back(card2->first);
                }
            }
            else if(card2->second == 3)
            {
                type_ = PokerHandType::ThreePair;
                rankedCards_.push_back(card2->first);
                if(card1->first > card3->first)
                {
                    rankedCards_.push_back(card1->first);
                    rankedCards_.push_back(card3->first);
                }
                else
                {
                    rankedCards_.push_back(card3->first);
                    rankedCards_.push_back(card1->first);
                }
            }
            else if(card3->second == 3)
            {
                type_ = PokerHandType::ThreePair;
                rankedCards_.push_back(card3->first);
                if(card1->first > card2->first)
                {
                    rankedCards_.push_back(card1->first);
                    rankedCards_.push_back(card2->first);
                }
                else
                {
                    rankedCards_.push_back(card2->first);
                    rankedCards_.push_back(card1->first);
                }
            }
            else
            {
                type_ = PokerHandType::TwoPair;
                if(card1->second == 1)
                {
                    if(card2->first > card3->first)
                    {
                        rankedCards_.push_back(card2->first);
                        rankedCards_.push_back(card3->first);
                    }
                    else
                    {
                        rankedCards_.push_back(card3->first);
                        rankedCards_.push_back(card2->first);
                    }
                    rankedCards_.push_back(card1->first);
                }
                else if(card2->second == 1)
                {
                    if(card1->first > card3->first)
                    {
                        rankedCards_.push_back(card1->first);
                        rankedCards_.push_back(card3->first);
                    }
                    else
                    {
                        rankedCards_.push_back(card3->first);
                        rankedCards_.push_back(card1->first);
                    }
                    rankedCards_.push_back(card2->first);
                }
                else if(card3->second == 1)
                {
                    if(card1->first > card2->first)
                    {
                        rankedCards_.push_back(card1->first);
                        rankedCards_.push_back(card2->first);
                    }
                    else
                    {
                        rankedCards_.push_back(card2->first);
                        rankedCards_.push_back(card1->first);
                    }
                    rankedCards_.push_back(card3->first);
                }
            }
        }
            break;

        case 4:
        {
            type_ = PokerHandType::OnePair;
            
            auto card = cards.cbegin();
            auto card1 = card++;
            auto card2 = card++;
            auto card3 = card++;
            auto card4 = card;

            std::vector<CardType> lowCards;

            if(card1->second == 2)
            {
                rankedCards_.push_back(card1->first);
                lowCards.push_back(card2->first);
                lowCards.push_back(card3->first);
                lowCards.push_back(card4->first);
            }
            else if(card2->second == 2)
            {
                rankedCards_.push_back(card2->first);
                lowCards.push_back(card1->first);
                lowCards.push_back(card3->first);
                lowCards.push_back(card4->first);
            }
            else if(card2->second == 2)
            {
                rankedCards_.push_back(card3->first);
                lowCards.push_back(card1->first);
                lowCards.push_back(card2->first);
                lowCards.push_back(card4->first);
            }
            else
            {
                rankedCards_.push_back(card4->first);
                lowCards.push_back(card1->first);
                lowCards.push_back(card2->first);
                lowCards.push_back(card3->first);
            }

            std::sort(lowCards.begin(), lowCards.end(), [](CardType l, CardType r) { return l > r; });
            for(auto lowCard : lowCards)
                rankedCards_.push_back(lowCard);
        }
            break;

        case 5:
            type_ = PokerHandType::HighCard;
            std::sort(hand.begin(), hand.end(), [](CardType l, CardType r) { return l > r; });
            for(auto card : hand)
                rankedCards_.push_back(card);
            break;
    };
};



PokerHandType PokerHand::getType() const
{
    return type_;
};



CardType PokerHand::getCardOfRank(int rank) const
{
    if(rankedCards_.size() < rank || rank < 1)
        return CardType::Invalid;

    return rankedCards_[rank - 1];
};



bool PokerHand::isGreaterThan(const PokerHand& rhs) const
{
    if(this->getType() != rhs.getType())
        return this->getType() > rhs.getType();
    
    switch(this->getType())
    {
        case PokerHandType::FivePair :
            return this->getCardOfRank(1) > rhs.getCardOfRank(1);
        
        case PokerHandType::FourPair :
        case PokerHandType::FullHouse :
            if(this->getCardOfRank(1) == rhs.getCardOfRank(1))
                return this->getCardOfRank(2) > rhs.getCardOfRank(2);

            return this->getCardOfRank(1) > rhs.getCardOfRank(1);
        
        case PokerHandType::ThreePair :
        case PokerHandType::TwoPair :
            if(this->getCardOfRank(1) == rhs.getCardOfRank(1))
            {
                if(this->getCardOfRank(2) == rhs.getCardOfRank(2))
                {
                    return this->getCardOfRank(3) > rhs.getCardOfRank(3);
                }
                return this->getCardOfRank(2) > rhs.getCardOfRank(2);
            }
            return this->getCardOfRank(1) > rhs.getCardOfRank(1);
            
        case PokerHandType::OnePair :
            if(this->getCardOfRank(1) == rhs.getCardOfRank(1))
            {
                if(this->getCardOfRank(2) == rhs.getCardOfRank(2))
                {
                    if(this->getCardOfRank(3) == rhs.getCardOfRank(3))
                    {
                        return this->getCardOfRank(4) > rhs.getCardOfRank(4);
                    }
                    return this->getCardOfRank(3) > rhs.getCardOfRank(3);
                }
                return this->getCardOfRank(2) > rhs.getCardOfRank(2);
            }
            return this->getCardOfRank(1) > rhs.getCardOfRank(1);

        case PokerHandType::HighCard :
            if(this->getCardOfRank(1) == rhs.getCardOfRank(1))
            {
                if(this->getCardOfRank(2) == rhs.getCardOfRank(2))
                {
                    if(this->getCardOfRank(3) == rhs.getCardOfRank(3))
                    {
                        if(this->getCardOfRank(4) == rhs.getCardOfRank(4))
                        {
                            return this->getCardOfRank(5) > rhs.getCardOfRank(5);
                        }
                        return this->getCardOfRank(4) > rhs.getCardOfRank(4);
                    }
                    return this->getCardOfRank(3) > rhs.getCardOfRank(3);
                }
                return this->getCardOfRank(2) > rhs.getCardOfRank(2);
            }
            return this->getCardOfRank(1) > rhs.getCardOfRank(1);
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
    for(auto card : pokerHand.rankedCards_)
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