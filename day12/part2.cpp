#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "helpers.h"

uint64_t countCombinationsOfSprings(const std::pair<std::string, std::vector<int>>& springsDescription)
{
    uint64_t combinations = 0;
    std::string springs = springsDescription.first;

    int damageCount = springsDescription.second[0];
    uint64_t nextStart = 0;
    while(springs[nextStart] == '.')
        nextStart++;

    for(; nextStart < springs.length() && (nextStart == 0 || springs[nextStart - 1] != '#'); nextStart++)
    {
        for(int offset = 0; offset < damageCount; offset++)
        {
            if(nextStart + offset >= springs.length())
                break;

            if(springs[nextStart + offset] == '.')
                break;
            
            if(offset + 1 == damageCount)
            {
                if(springs[nextStart + offset + 1] == '#')
                {
                    break;
                }
                else if(springsDescription.second.size() > 1)
                {
                    std::string possibleRemaining = 
                        springs.substr(
                            nextStart + damageCount,
                            springs.length() - (nextStart + damageCount)
                        );
                    possibleRemaining[0] = '.';
                    std::vector<int> remainingDamages;
                    for(int i = 1; i < springsDescription.second.size(); i++)
                    {
                        remainingDamages.push_back(springsDescription.second[i]);
                    }
                    uint64_t newCombinations = countCombinationsOfSprings(std::make_pair(possibleRemaining, remainingDamages));
                    if(newCombinations == 0)
                        return combinations;
                    combinations += newCombinations;
                }
                else if(springs.substr(nextStart + damageCount, springs.length() - (nextStart + damageCount)).find('#') == std::string::npos)
                {
                    combinations += 1;
                }
            } 
        }
    }

    return combinations;
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

    std::vector<std::pair<std::string, std::vector<int>>> damagedSprings;
    while(!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        if(currentLine.length() < 1)
            continue;

        std::vector<std::string> splitInput = helpers::splitString(currentLine, {" "});
        std::vector<int> damageCounts;
        for(auto numberString : helpers::splitString(splitInput[1], {","}))
            damageCounts.push_back(stoi(numberString));
        
        damagedSprings.push_back(std::make_pair(splitInput[0], damageCounts));
    }
    fin.close();

    uint64_t answer = 0;
uint64_t count = 0;
    for(auto springLine : damagedSprings)
    {
std::cout << "Line: " << ++count << "\n";
        std::string quintupledString;
        std::vector<int> quintupledDamages;
        for(int i = 0; i < 5; i++)
        {
            quintupledString += springLine.first;
            for(auto damage : springLine.second)
                quintupledDamages.push_back(damage);
        }
        answer += countCombinationsOfSprings(std::make_pair(quintupledString, quintupledDamages));
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
};