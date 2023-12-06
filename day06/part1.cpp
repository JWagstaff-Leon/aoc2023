#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "helpers.h"

int64_t timeDistToZero(uint64_t time, uint64_t dist, bool plusCase)
{
    // quadratic equation solving the zeros of x^2 - time * x + distance (where x is the time spent charging)
    double sqrtPart = (plusCase ? 1 : -1) * std::sqrt((time * time) - (4 * dist));
    double numerator = time + sqrtPart;
    double doubleResult = numerator / 2;
    int64_t result = (plusCase ? std::floor(doubleResult) : std::ceil(doubleResult)); // round towards the center
    return result;
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

    std::vector<uint64_t> times, distances;
    std::string currentInput;

    // consume "Times:"
    fin >> currentInput;

    // read times line
    std::getline(fin, currentInput);
    std::vector<std::string> timeStrings = helpers::splitString(currentInput, {" "});
    for(auto timeString : timeStrings)
        if(timeString.length() > 0)
            times.push_back(helpers::stoi64(timeString));

    // consume "Distances:"
    fin >> currentInput;
    // read distances line
    std::getline(fin, currentInput);
    std::vector<std::string> distanceStrings = helpers::splitString(currentInput, {" "});
    for(auto distanceString : distanceStrings)
        if(distanceString.length() > 0)
            distances.push_back(helpers::stoi64(distanceString));

    fin.close();

    uint64_t answer = 1;
    for(int i = 0; i < times.size() && i < distances.size(); i++)
    {
        uint64_t successCases = (timeDistToZero(times[i], distances[i], true) - timeDistToZero(times[i], distances[i], false)) + 1;
        answer *= successCases;
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
}