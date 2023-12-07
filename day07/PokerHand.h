#pragma once

#include <vector>

enum class CardType : int
{
    A     = 14,
    K     = 13,
    Q     = 12,
    J     = 11,
    Ten   = 10,
    Nine  =  9,
    Eight =  8,
    Seven =  7,
    Six   =  6,
    Five  =  5,
    Four  =  4,
    Three =  3,
    Two   =  2,

    Invalid = -1
};



enum class PokerHandType
{
    FivePair = 6,
    FourPair = 5,
    FullHouse = 4,
    ThreePair = 3,
    TwoPair = 2,
    OnePair = 1,
    HighCard = 0
};



#include <iostream>
class PokerHand
{
    public:
        PokerHand(CardType card1, CardType card2, CardType card3, CardType card4, CardType card5);

        PokerHandType getType() const;
        CardType getCardOfRank(int rank) const;
        bool isGreaterThan(const PokerHand& rhs) const;

        friend std::ostream& operator<< (std::ostream& sout, const PokerHand pokerHand);

    private:
        std::vector<CardType> rankedCards_;
        PokerHandType type_;
};