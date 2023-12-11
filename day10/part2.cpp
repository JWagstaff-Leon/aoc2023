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



enum class LoopType
{
    OUTSIDE,
    INSIDE,
    LOOP
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

    // Find starting position
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

    // Find the loop of the starting position
    bool loopFound = false;
    char possiblePipes[] = {'|', '-', 'L', 'J', '7', 'F'};
    for(int i = 0; i < 6 && !loopFound; i++)
    {
        pipes[startingPosition.second][startingPosition.first] = possiblePipes[i];

        Coordinate currentCoordinate = startingPosition, nextCoordinate, previousCoordinate;
        auto adjacentCoords = getNextPipesCoords(pipes, currentCoordinate);
        nextCoordinate = adjacentCoords.first;

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
            auto adjacentCoords = getNextPipesCoords(pipes, currentCoordinate);

            if(previousCoordinate == adjacentCoords.second)
                nextCoordinate = adjacentCoords.first;
            else
                nextCoordinate = adjacentCoords.second;
            
            if(nextCoordinate == startingPosition)
                loopFound = true;
        }
    }

    // Make a sub-grid of possible paths with pipe-squeezing
    std::vector<std::vector<LoopType>> loopTypes;
    for(int y = 0; y < pipes.size() * 2 - 1; y++)
    {
        std::vector<LoopType> loopTypeLine;
        for(int x = 0; x < pipes[0].length() * 2 - 1; x++)
        {
            loopTypeLine.push_back(LoopType::INSIDE);            
        }
        loopTypes.push_back(loopTypeLine);
    }

    // Mark the loop on the sub-grid with where it is
    Coordinate currentCoordinate = startingPosition, nextCoordinate, previousCoordinate;
    auto adjacentCoords = getNextPipesCoords(pipes, currentCoordinate);
    nextCoordinate = adjacentCoords.first;
    do
    {
        auto adjacentPipes = getNextPipesCoords(pipes, currentCoordinate);
        loopTypes[currentCoordinate.second * 2][currentCoordinate.first * 2] = LoopType::LOOP;

        auto betweenFirst = std::make_pair(adjacentPipes.first.first - currentCoordinate.first, adjacentPipes.first.second - currentCoordinate.second);
        auto betweenSecond = std::make_pair(adjacentPipes.second.first - currentCoordinate.first, adjacentPipes.second.second - currentCoordinate.second);

        int32_t subGridYFirst = currentCoordinate.second * 2 + betweenFirst.second;
        int32_t subGridXFirst = currentCoordinate.first * 2 + betweenFirst.first;
        int32_t subGridYSecond = currentCoordinate.second * 2 + betweenSecond.second;
        int32_t subGridXSecond = currentCoordinate.first * 2 + betweenSecond.first;
        if(subGridYFirst >= 0 && subGridYFirst < loopTypes.size() && subGridXFirst >= 0 && subGridXFirst < loopTypes[subGridYFirst].size())
            loopTypes[currentCoordinate.second * 2 + betweenFirst.second][currentCoordinate.first * 2 + betweenFirst.first] = LoopType::LOOP;
        if(subGridYSecond >= 0 && subGridYSecond < loopTypes.size() && subGridXSecond >= 0 && subGridXSecond < loopTypes[subGridYSecond].size())
            loopTypes[currentCoordinate.second * 2 + betweenSecond.second][currentCoordinate.first * 2 + betweenSecond.first] = LoopType::LOOP;

        previousCoordinate = currentCoordinate;
        currentCoordinate = nextCoordinate;
        auto adjacentCoords = getNextPipesCoords(pipes, currentCoordinate);

        if(previousCoordinate == adjacentCoords.second)
            nextCoordinate = adjacentCoords.first;
        else
            nextCoordinate = adjacentCoords.second;

    } while(currentCoordinate != startingPosition);

    // Make the outer ring (of non-loops) count as the outside
    for(int x = 0; x < loopTypes[0].size(); x++)
        if(loopTypes[0][x] != LoopType::LOOP)
            loopTypes[0][x] = LoopType::OUTSIDE;
    
    int bottom = loopTypes.size() - 1;
    int bottomSize = loopTypes[bottom].size();
    for(int x = 0; x < bottomSize; x++)
        if(loopTypes[bottom][x] != LoopType::LOOP)
            loopTypes[bottom][x] = LoopType::OUTSIDE;

    for(int y = 0; y < loopTypes.size(); y++)
        if(loopTypes[y][0] != LoopType::LOOP)
            loopTypes[y][0] = LoopType::OUTSIDE;

    for(int y = 0; y < loopTypes.size(); y++)
        if(loopTypes[y][loopTypes[y].size() - 1] != LoopType::LOOP)
            loopTypes[y][loopTypes[y].size() - 1] = LoopType::OUTSIDE;

    // Flood fill the outside
    uint32_t changed = 0;
    do
    {
        changed = 0;
        for(int y = 0; y < loopTypes.size(); y++)
        {
            std::vector<LoopType> currentLine = loopTypes[y];
            for(int x = 0; x < currentLine.size(); x++)
            {
                if(currentLine[x] == LoopType::OUTSIDE)
                {
                    // Top
                    if(y > 0)
                    {
                        // Top left
                        if(x > 0 && x - 1 < loopTypes[y - 1].size() && loopTypes[y - 1][x - 1] == LoopType::INSIDE)
                        {
                            changed += 1;
                            loopTypes[y - 1][x - 1] = LoopType::OUTSIDE;
                        }
                        // Top middle
                        if(x < loopTypes[y - 1].size() && loopTypes[y - 1][x] == LoopType::INSIDE)
                        {
                            changed += 1;
                            loopTypes[y - 1][x] = LoopType::OUTSIDE;
                        }
                        // Top right
                        if(x + 1 < loopTypes[y - 1].size() && loopTypes[y - 1][x + 1] == LoopType::INSIDE)
                        {
                            changed += 1;
                            loopTypes[y - 1][x + 1] = LoopType::OUTSIDE;
                        }
                    }
                    // Bottom
                    if(y < loopTypes.size() - 1)
                    {
                        // Bottom left
                        if(x > 0 && x - 1 < loopTypes[y + 1].size() && loopTypes[y + 1][x - 1] == LoopType::INSIDE)
                        {
                            changed += 1;
                            loopTypes[y + 1][x - 1] = LoopType::OUTSIDE;
                        }
                        // Bottom middle
                        if(x < loopTypes[y + 1].size() && loopTypes[y + 1][x] == LoopType::INSIDE)
                        {
                            changed += 1;
                            loopTypes[y + 1][x] = LoopType::OUTSIDE;
                        }
                        // Bottom right
                        if(x + 1 < loopTypes[y + 1].size() && loopTypes[y + 1][x + 1] == LoopType::INSIDE)
                        {
                            changed += 1;
                            loopTypes[y + 1][x + 1] = LoopType::OUTSIDE;
                        }
                    }
                    // Middle left
                    if(x > 0 && loopTypes[y][x - 1] == LoopType::INSIDE)
                    {
                        changed += 1;
                        loopTypes[y][x - 1] = LoopType::OUTSIDE;
                    }
                    // Middle right
                    if(x + 1 < loopTypes[y].size() && loopTypes[y][x + 1] == LoopType::INSIDE)
                    {
                        changed += 1;
                        loopTypes[y][x + 1] = LoopType::OUTSIDE;
                    }
                }
            }
        }
    } while (changed != 0);

    // Count the inside tiles
    std::ofstream fout("temp.txt");
    uint32_t answer = 0;
    for(int y = 0; y < loopTypes.size(); y += 2)
    {
        std::vector<LoopType> currentLine = loopTypes[y];
        for(int x = 0; x < currentLine.size(); x += 2)
        {
            switch(currentLine[x])
            {
                case LoopType::INSIDE:
                    fout << "X";
                    break;
                case LoopType::OUTSIDE:
                    fout << " ";
                    break;
                case LoopType::LOOP:
                    switch(pipes[y / 2][x / 2])
                    {
                        case '-':
                            fout << "─";
                            break;
                            
                        case '|':
                            fout << "│";
                            break;
                        
                        case 'L':
                            fout << "└";
                            break;
                        
                        case 'J':
                            fout << "┘";
                            break;

                        case '7':
                            fout << "┐";
                            break;

                        case 'F':
                            fout << "┌";
                            break;
                    }
            }
            if(currentLine[x] == LoopType::INSIDE)
            {
                answer += 1;
            }
        }
        fout << "\n";
    }
    fout.close();

    std::cout << "Answer: " << answer << "\n";
    return 0;
};