#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "helpers.h"
#include "RangeMap.h"

void addRangeStringToRangeMap(const std::string& str, RangeMap* rangeMap)
{
    std::vector<std::string> range = helpers::splitString(str, {" "}); // "<dest> <source> <range>" 
    rangeMap->addRange(
        helpers::stoi64(range[1].c_str()), // source
        helpers::stoi64(range[0].c_str()), // destination
        helpers::stoi64(range[2].c_str())  // range
    );
};



void readInAllMaps(std::ifstream& fin, std::vector<RangeMap*> maps)
{
    std::string currentLine;
    for(auto map : maps)
    {
        // consume header line
        std::getline(fin, currentLine);

        // get map
        std::getline(fin, currentLine);
        while(currentLine.length() > 0 && !fin.eof())
        {
            addRangeStringToRangeMap(currentLine, map);
            std::getline(fin, currentLine);
        }
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

    std::string currentLine;
    std::vector<int64_t> seeds;
    RangeMap seedToSoilMap, soilToFertilizerMap, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation;
    while(!fin.eof())
    {
        // Read seeds
        std::getline(fin, currentLine);
        std::string seedsString = helpers::splitString(currentLine, {": "})[1]; // split "seeds: # # # ..." and take only the numbers;
        std::vector<std::string> seedStrings = helpers::splitString(seedsString, {" "}); // split between numbers
        for(auto seedString : seedStrings)
        {
            seeds.push_back(helpers::stoi64(seedString.c_str()));
        }

        // consume new line
        std::getline(fin, currentLine);
        readInAllMaps(fin, {&seedToSoilMap, &soilToFertilizerMap, &fertilizerToWater, &waterToLight, &lightToTemperature, &temperatureToHumidity, &humidityToLocation});
    }
    fin.close();

    return 0;
}