#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "helpers.h"
#include "NumberRun.h"

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

    int32_t answer = 0;
    while(!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        if(currentLine.length() > 0)
        {
            std::vector<std::string> numberStrings = helpers::splitString(currentLine, {" "});
            std::vector<int32_t> numbers;
            for(auto numberString : numberStrings)
            {
                numbers.push_back(stoi(numberString));
            }
            NumberRun run(numbers);
            answer += run.getNext();
        }
    }
    fin.close();

    std::cout << "Answer: "<< answer << "\n";
    return 0;
}