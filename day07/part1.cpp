#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "PokerHand.h"

CardType charToCard(char input)
{
    switch(input)
    {
        case 'A':
            return CardType::A;
        case 'K':
            return CardType::K;
        case 'Q':
            return CardType::Q;
        case 'J':
            return CardType::J;
        case 'T':
            return CardType::Ten;
        case '9':
            return CardType::Nine;
        case '8':
            return CardType::Eight;
        case '7':
            return CardType::Seven;
        case '6':
            return CardType::Six;
        case '5':
            return CardType::Five;
        case '4':
            return CardType::Four;
        case '3':
            return CardType::Three;
        case '2':
            return CardType::Two;
        default:
            return CardType::Invalid;
    }
};



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input filename>" << std::endl;
        return 0;
    }

    std::ifstream fin(argv[1]);
    if (fin.fail())
    {
        std::cout << "Could not open file " << argv[1] << std::endl;
        return 0;
    }

    std::vector<std::pair<PokerHand, int>> handsAndBets;
    while(!fin.eof())
    {
        std::string cards, bet;
        fin >> cards >> bet;

        if(cards.length() == 0 || bet.length() == 0)
            continue;

        CardType card1 = charToCard(cards[0]);
        CardType card2 = charToCard(cards[1]);
        CardType card3 = charToCard(cards[2]);
        CardType card4 = charToCard(cards[3]);
        CardType card5 = charToCard(cards[4]);
        PokerHand hand(card1, card2, card3, card4, card5);
        handsAndBets.push_back(std::make_pair(hand, stoi(bet)));
    }
    fin.close();

// std::cout << "Unsorted hands and bets:\n";
// for(auto hnb : handsAndBets)
// std::cout << hnb.first << " | " << hnb.second << "\n";
// char temp;
// std::cin >> temp;
    std::sort(handsAndBets.begin(), handsAndBets.end(), [](std::pair<PokerHand, int> l, std::pair<PokerHand, int> r) { return l.first.isLessThan(r.first); });
// std::cout << "Sorted hands and bets:\n";
// for(auto hnb : handsAndBets)
// std::cout << hnb.first << " | " << hnb.second << "\n";
    uint64_t answer = 0;
    for(int i = 0; i < handsAndBets.size(); i++)
        answer += handsAndBets[i].second * (i + 1);
    std::cout << "Answer: " << answer << "\n";
    return 0;
}