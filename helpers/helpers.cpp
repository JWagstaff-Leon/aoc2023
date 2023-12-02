#include "helpers.h"

#include <vector>
#include <string>

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
                c += delimiter.length();
                lastSplit = c;
                break;
            }
        }
    }

    if(c > lastSplit)
        result.push_back(string.substr(lastSplit, c - lastSplit));

    return result;
};