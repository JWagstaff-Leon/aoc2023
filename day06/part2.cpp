#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

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

    uint64_t time = 0, distance = 0;
    std::string currentInput;

    // consume "Times:"
    fin >> currentInput;

    // read time line
    std::getline(fin, currentInput);
    for(auto character : currentInput)
    {
        if(isdigit(character))
        {
            time *= 10;
            time += character - '0';
        }
    }

    // consume "Distances:"
    fin >> currentInput;
    // read distances line
    std::getline(fin, currentInput);
    for(auto character : currentInput)
    {
        if(isdigit(character))
        {
            distance *= 10;
            distance += character - '0';
        }
    }

    fin.close();

    uint64_t answer = (timeDistToZero(time, distance, true) - timeDistToZero(time, distance, false)) + 1;
    std::cout << "Answer: " << answer << "\n";
    return 0;
}