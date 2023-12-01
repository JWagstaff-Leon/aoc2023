#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

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
    uint32_t answer = 0;
    while(!fin.eof())
    {
        int8_t first = -1, last;
        std::getline(fin, currentLine);
        for(const char character : currentLine)
        {
            if(isdigit(character))
            {
                if(first < 0)
                    first = character - '0';
                
                last = character - '0';
            }
        }
        if(first > 0)
            answer += first * 10 + last;
    }
    fin.close();

    std::cout << "Answer: " << answer << std::endl;
    return 0;
}