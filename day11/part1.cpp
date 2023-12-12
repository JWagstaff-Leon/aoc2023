#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

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

    std::vector<std::string> input;
    std::set<int> emptyRows, emptyColumns;
    while(!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        if(currentLine.length() < 1)
            continue;

        input.push_back(currentLine);
    }
    fin.close();

    for(int row = 0; row < input.size(); row++)
    {
        if(input[row].find("#") == std::string::npos)
        {
            emptyRows.insert(row);
        }
    }

    for(int col = 0; col < input[0].length(); col++)
    {
        std::string currentColumn;
        for(int row = 0; row < input.size(); row++)
        {
            currentColumn += input[row][col];
        }

        if(currentColumn.find("#") == std::string::npos)
        {
            emptyColumns.insert(col);
        }
    }

    std::vector<std::string> expandedInput;
    for(int row = 0; row < input.size(); row++)
    {
        std::string currentRow;
        for(int col = 0; col < input[row].length(); col++)
        {
            currentRow += input[row][col];
            if(emptyColumns.find(col) != emptyColumns.end())
                currentRow += input[row][col];
        }
        expandedInput.push_back(currentRow);
        if(emptyRows.find(row) != emptyRows.end())
            expandedInput.push_back(currentRow);
    }

    std::vector<std::pair<int, int>> galaxies;
    for(int y = 0; y < expandedInput.size(); y++)
        for(int x = 0; x < expandedInput[y].length(); x++)
            if(expandedInput[y][x] == '#')
                galaxies.push_back(std::make_pair(y, x));

    uint32_t answer = 0;
    for(int i = 0; i < galaxies.size() - 1; i++)
    {
        for(int j = i + 1; j < galaxies.size(); j++)
        {
            if(galaxies[j].first > galaxies[i].first)
                answer += galaxies[j].first - galaxies[i].first;
            else
                answer += galaxies[i].first - galaxies[j].first;

            if(galaxies[j].second > galaxies[i].second)
                answer += galaxies[j].second - galaxies[i].second;
            else
                answer += galaxies[i].second - galaxies[j].second;
        }
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
};