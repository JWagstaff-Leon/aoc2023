#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

const char* digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

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
        for(int c = 0; c < currentLine.length(); c++)
        {
            int found = -1;
            switch(currentLine[c])
            {
                case 'o':
                    if(c < currentLine.length() - 2 &&
                        currentLine[c + 1] == 'n' && currentLine[c + 2] == 'e') // one
                    {
                        found = 1;
                        break;
                    }

                    break;

                case 't':
                    if(c < currentLine.length() - 2 &&
                        currentLine[c + 1] == 'w' && currentLine[c + 2] == 'o') // two
                    {
                        found = 2;
                        break;
                    }

                    if(c < currentLine.length() - 4 &&
                        currentLine[c + 1] == 'h' && currentLine[c + 2] == 'r' &&
                        currentLine[c + 3] == 'e' && currentLine[c + 4] == 'e') // three
                    {
                        found = 3;
                        break;
                    }

                    break;

                case 'f':
                    if(c < currentLine.length() - 3 &&
                        currentLine[c + 1] == 'o' && currentLine[c + 2] == 'u' &&
                        currentLine[c + 3] == 'r') // four
                    {
                        found = 4;
                        break;
                    }

                    if(c < currentLine.length() - 3 &&
                        currentLine[c + 1] == 'i' && currentLine[c + 2] == 'v' &&
                        currentLine[c + 3] == 'e') // five
                    {
                        found = 5;
                        break;
                    }

                    break;

                case 's':
                    if(c < currentLine.length() - 2 &&
                        currentLine[c + 1] == 'i' && currentLine[c + 2] == 'x') // six
                    {
                        found = 6;
                        break;
                    }

                    if(c < currentLine.length() - 4 &&
                        currentLine[c + 1] == 'e' && currentLine[c + 2] == 'v' &&
                        currentLine[c + 3] == 'e' && currentLine[c + 4] == 'n') // seven
                    {
                        found = 7;
                        break;
                    }

                    break;

                case 'e':
                    if(c < currentLine.length() - 4 &&
                        currentLine[c + 1] == 'i' && currentLine[c + 2] == 'g' &&
                        currentLine[c + 3] == 'h' && currentLine[c + 4] == 't') // eight
                    {
                        found = 8;
                        break;
                    }

                    break;

                case 'n':
                    if(c < currentLine.length() - 3 &&
                        currentLine[c + 1] == 'i' && currentLine[c + 2] == 'n' &&
                        currentLine[c + 3] == 'e') // nine
                    {
                        found = 9;
                        break;
                    }

                    break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    found = currentLine[c] - '0';
                    break;
            }

            if(found >= 0)
            {
                if(first < 0)
                    first = found;

                last = found;
            }
        }

        if(first > 0)
            answer += first * 10 + last;
    }
    fin.close();

    std::cout << "Answer: " << answer << std::endl;
    return 0;
}