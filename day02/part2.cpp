#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "CubeCounts.h"
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

    CubeCounts maxCubes;
    maxCubes.red = 12;
    maxCubes.green = 13;
    maxCubes.blue = 14;

    uint32_t answer = 0;
    while(!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        std::vector<std::string> game = helpers::splitString(currentLine, {": ", "; "});
        uint32_t gameId = 0;
        if(game.size() > 0)
            sscanf(game[0].c_str(), "Game %u", &gameId);
    
        CubeCounts gameCounts;
        gameCounts.red = 0;
        gameCounts.green = 0;
        gameCounts.blue = 0;
        for(int i = 1; i < game.size(); i++)
        {
            std::vector<std::string> cubes = helpers::splitString(game[i], {", "});

            CubeCounts setCounts;
            setCounts.red = 0;
            setCounts.green = 0;
            setCounts.blue = 0;

            for(auto cube : cubes)
            {
                uint32_t count;
                std::string color;
                color.reserve(6);
                sscanf(cube.c_str(), "%u", &count);
                int colorPosition = cube.find(' ') + 1;
                color = cube.substr(colorPosition, cube.length() - colorPosition);

                if(color == "red")
                    setCounts.red += count;

                if(color == "green")
                    setCounts.green += count;

                if(color == "blue")
                    setCounts.blue += count;
            }

            if(setCounts.red > gameCounts.red)
                gameCounts.red = setCounts.red;

            if(setCounts.green > gameCounts.green)
                gameCounts.green = setCounts.green;

            if(setCounts.blue > gameCounts.blue)
                gameCounts.blue = setCounts.blue;
            
        }

        answer += (gameCounts.red * gameCounts.green * gameCounts.blue);
    }
    fin.close();

    std::cout << "Answer: " << answer << std::endl;
    return 0;
}