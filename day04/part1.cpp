#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
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

    uint32_t answer = 0;
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

        uint32_t cardScore = 0;
        for(auto winNum : winningNumbers)
        {
            for(auto yourNum : yourNumbers)
            {
                if(winNum == yourNum)
                {
                    if(cardScore == 0)
                        cardScore = 1;
                    else
                        cardScore *= 2;
                }
            }
        }
        answer += cardScore;
    }
    fin.close();

    std::cout << "Answer: " << answer << "\n";
    return 0;
}