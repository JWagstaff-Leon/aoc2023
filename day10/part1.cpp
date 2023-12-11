#include <assert.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Coordinate = std::pair<uint32_t, uint32_t>;

std::pair<Coordinate, Coordinate> getNextPipesCoords(std::vector<std::string> pipes, Coordinate currentPipe)
{
    assert(currentPipe.second < pipes.size());
    assert(currentPipe.first < pipes[currentPipe.second].length());

    switch(pipes[currentPipe.second][currentPipe.first])
    {
        case '-':
            return std::make_pair(
                std::make_pair(currentPipe.first + 1, currentPipe.second),
                std::make_pair(currentPipe.first - 1, currentPipe.second)
            );

        case '|':
            return std::make_pair(
                std::make_pair(currentPipe.first, currentPipe.second - 1),
                std::make_pair(currentPipe.first, currentPipe.second + 1)
            );

        case 'L':
            return std::make_pair(
                std::make_pair(currentPipe.first, currentPipe.second - 1),
                std::make_pair(currentPipe.first + 1, currentPipe.second)
            );

        case 'J':
            return std::make_pair(
                std::make_pair(currentPipe.first, currentPipe.second - 1),
                std::make_pair(currentPipe.first - 1, currentPipe.second)
            );

        case '7':
            return std::make_pair(
                std::make_pair(currentPipe.first, currentPipe.second + 1),
                std::make_pair(currentPipe.first - 1, currentPipe.second)
            );

        case 'F':
            return std::make_pair(
                std::make_pair(currentPipe.first, currentPipe.second + 1),
                std::make_pair(currentPipe.first + 1, currentPipe.second)
            );

        case '.':
            return std::make_pair(currentPipe, currentPipe);

        default:
            assert(false);
    }

    assert(false);
    return std::make_pair(currentPipe, currentPipe);
};



bool locationAcceptsFromCoords(std::vector<std::string> pipes, Coordinate target, Coordinate source)
{
    assert(target.second < pipes.size());
    assert(target.first < pipes[target.second].length());

    switch(pipes[target.second][target.first])
    {
        case '-':
            return source == std::make_pair(target.first + 1, target.second) ||
                   source == std::make_pair(target.first - 1, target.second);

        case '|':
            return source == std::make_pair(target.first, target.second - 1) ||
                   source == std::make_pair(target.first, target.second + 1);

        case 'L':
            return source == std::make_pair(target.first, target.second - 1) ||
                   source == std::make_pair(target.first + 1, target.second);

        case 'J':
            return source == std::make_pair(target.first, target.second - 1) ||
                   source == std::make_pair(target.first - 1, target.second);

        case '7':
            return source == std::make_pair(target.first, target.second + 1) ||
                   source == std::make_pair(target.first - 1, target.second);

        case 'F':
            return source == std::make_pair(target.first, target.second + 1) ||
                   source == std::make_pair(target.first + 1, target.second);
        
        default:
            return false;
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

    std::vector<std::string> pipes;
    while(!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);
        if(currentLine.length() < 1)
            continue;

        pipes.push_back(currentLine);
    }
    fin.close();

    Coordinate startingPosition = Coordinate(-1, -1);
    for(int y = 0; y < pipes.size(); y++)
    {
        std::string currentLine = pipes[y];
        for(int x = 0; x < currentLine.length(); x++)
        if(currentLine[x] == 'S')
        {
            startingPosition = Coordinate(x, y);
        }
    }
    assert(startingPosition.first != -1 && startingPosition.second != -1);

    uint32_t answer = 0;
    char possiblePipes[] = {'|', '-', 'L', 'J', '7', 'F'};
    for(int i = 0; i < 6 && answer == 0; i++)
    {
        pipes[startingPosition.second][startingPosition.first] = possiblePipes[i];

        Coordinate currentCoordinate = startingPosition, nextCoordinate, previousCoordinate;
        auto adjacentCoords = getNextPipesCoords(pipes, currentCoordinate);
        nextCoordinate = adjacentCoords.first;

        int steps = 0;
        while(nextCoordinate != startingPosition)
        {
            if(
                nextCoordinate.second < 0 || nextCoordinate.second > pipes.size() ||
                nextCoordinate.first < 0 || nextCoordinate.first > pipes[nextCoordinate.second].length() ||
                !locationAcceptsFromCoords(pipes, nextCoordinate, currentCoordinate)
            )
            {
                break;
            }
            
            previousCoordinate = currentCoordinate;
            currentCoordinate = nextCoordinate;
            steps += 1;
            auto adjacentCoords = getNextPipesCoords(pipes, currentCoordinate);
            if(previousCoordinate == adjacentCoords.second)
                nextCoordinate = adjacentCoords.first;
            else
                nextCoordinate = adjacentCoords.second;
            
            if(nextCoordinate == startingPosition)
                answer = (steps + 1) / 2;
        }
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
};