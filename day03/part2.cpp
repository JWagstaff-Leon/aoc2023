#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class SearchDirection
{
    FORWARDS,
    BACKWARDS
};



uint32_t findStringNumberInDirection(std::string str, int position, SearchDirection direction)
{
    int offset = (direction == SearchDirection::FORWARDS ? 1 : -1);
    
    int numberStart;
    switch(direction)
    {
        case SearchDirection::BACKWARDS:
            for(numberStart = position;
                numberStart >= 0 && isdigit(str[numberStart]);
                numberStart--)
            ;
            numberStart++; // to get it back to 0 or digit
            break;
        
        case SearchDirection::FORWARDS:
            numberStart = position;
            break;
    }

    uint32_t number = 0;
    for(int x = numberStart; isdigit(str[x]) && x < str.length(); x++)
    {
        number *= 10;
        number += str[x] - '0';
    }

    return number;
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

    std::vector<std::string> lines;
    while(!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        if(currentLine.length() > 0)
            lines.push_back(currentLine);
    }
    fin.close();

    uint32_t answer = 0;
    for(int y = 0; y < lines.size(); y++)
    {
        std::string line = lines[y];
        for(int x = 0; x < line.length(); x++)
        {
            char character = line[x];
            if(character == '*')
            {
                std::vector<uint32_t> ratios;
                if(y > 0) // check above
                {
                    if(lines[y - 1][x] == '.') // only check both corners
                    {
                        if(x > 0 && isdigit(lines[y - 1][x - 1])) // there is a number to the top left
                        {
                            ratios.push_back(findStringNumberInDirection(lines[y - 1], x - 1, SearchDirection::BACKWARDS));
                        }
                        if(x < line.length() - 1 && isdigit(lines[y - 1][x + 1])) // there is a number to the top right
                        {
                            ratios.push_back(findStringNumberInDirection(lines[y - 1], x + 1, SearchDirection::FORWARDS));
                        }
                    }
                    else if(isdigit(lines[y - 1][x]))// there is a number across the top
                    {
                        ratios.push_back(findStringNumberInDirection(lines[y - 1], x, SearchDirection::BACKWARDS));
                    }
                }

                if(x > 0 && isdigit(line[x - 1])) // check left
                {
                    ratios.push_back(findStringNumberInDirection(line, x - 1, SearchDirection::BACKWARDS));
                }

                if(x < line.length() && isdigit(line[x + 1])) // check right
                {
                    ratios.push_back(findStringNumberInDirection(line, x + 1, SearchDirection::FORWARDS));
                }

                if(y < lines.size()) // check below
                {
                    if(lines[y + 1][x] == '.') // only check both corners
                    {
                        if(x > 0 && isdigit(lines[y + 1][x - 1])) // there is a number to the bottom left
                        {
                            ratios.push_back(findStringNumberInDirection(lines[y + 1], x - 1, SearchDirection::BACKWARDS));
                        }
                        if(x < line.length() - 1 && isdigit(lines[y + 1][x + 1])) // there is a number to the bottom right
                        {
                            ratios.push_back(findStringNumberInDirection(lines[y + 1], x + 1, SearchDirection::FORWARDS));
                        }
                    }
                    else if(isdigit(lines[y + 1][x]))// there is a number across the bottom
                    {
                        ratios.push_back(findStringNumberInDirection(lines[y + 1], x, SearchDirection::BACKWARDS));
                    }
                }

                if(ratios.size() == 2)
                    answer += ratios[0] * ratios[1];
            }
        }
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
}