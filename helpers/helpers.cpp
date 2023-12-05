#include "helpers.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

std::vector<std::string> helpers::splitString(const std::string& string, const std::vector<std::string>& delimiters)
{
    std::vector<std::string> result;

    int c, lastSplit = 0;
    for(c = 0; c < string.length(); c++)
    {
        for(auto delimiter : delimiters)
        {
            if(string.substr(c, delimiter.length()) == delimiter)
            {
                result.push_back(string.substr(lastSplit, c - lastSplit));
                c += delimiter.length() - 1;
                lastSplit = c + 1;
                break;
            }
        }
    }

    if(c > lastSplit)
        result.push_back(string.substr(lastSplit, c - lastSplit));

    return result;
};



int64_t helpers::stoi64(std::string string)
{
    if(string.length() < 1)
        return 0;

    bool negative = string[0] == '-';
    int64_t number = 0;

    for(int i = (negative ? 1 : 0); i < string.length() && isdigit(string[i]); i++)
    {
        number *= 10;
        number += string[i] - '0';
    }

    number *= (negative ? -1 : 1);
    return number;
};