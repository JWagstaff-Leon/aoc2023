#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "helpers.h"

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

    uint32_t cardNumber = 1;
    std::map <uint32_t, uint32_t> cardCounts;
    while(!fin.eof())
    {
        std::string input;
        std::getline(fin, input);
        if(input.length() < 1)
            continue;

        std::vector<std::string> splitInput = helpers::splitString(input, {": ", " | "}); // becomes "Card #", <winning numbers>, <your numbers>
        std::vector<std::string> winningString = helpers::splitString(splitInput[1], {" "});
        std::vector<std::string> yourString = helpers::splitString(splitInput[2], {" "});

        std::set<uint32_t> winningNumbers, yourNumbers;
        for(auto numberString : winningString)
        {
            if(numberString.length() > 0)
            {
                uint32_t number = 0;
                for(auto character : numberString)
                {
                    number *= 10;
                    number += character - '0';
                }
                winningNumbers.insert(number);
            }
        }
        for(auto numberString : yourString)
        {
            if(numberString.length() > 0)
            {
                uint32_t number = 0;
                for(auto character : numberString)
                {
                    number *= 10;
                    number += character - '0';
                }
                yourNumbers.insert(number);
            }
        }

        uint32_t winningCount = 0;
        for(auto winNum : winningNumbers)
            for(auto yourNum : yourNumbers)
                if(winNum == yourNum)
                    winningCount += 1;
        
        auto thisCard = cardCounts.find(cardNumber);
        uint32_t thisCardCount;
        if(thisCard != cardCounts.end())
        {
            thisCardCount = thisCard->second;
        }
        else
        {
            cardCounts.insert(std::pair<uint32_t, uint32_t>(cardNumber, 1));
            thisCardCount = 1;
        }

        for(uint32_t i = 1; i <= winningCount; i++)
        {
            auto thatCard = cardCounts.find(cardNumber + i);
            if(thatCard != cardCounts.end())
                cardCounts[cardNumber + i] += thisCardCount;
            else
                cardCounts.insert(std::pair<uint32_t, uint32_t>(cardNumber + i, thisCardCount + 1));
        }
        
        cardNumber += 1;
    }
    fin.close();

    uint64_t answer = 0;
    for(auto it = cardCounts.cbegin(); it != cardCounts.cend(); it++)
        answer += it->second;
    std::cout << "Answer: " << answer << "\n";
    return 0;
}