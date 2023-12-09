#include "NumberRun.h"

#include <cstdint>
#include <memory>
#include <vector>

NumberRun::NumberRun(std::vector<int32_t> numbers)
: numbers_(numbers)
{
    if(!isAllZero())
    {
        std::vector<int32_t> differences;
        for(int i = 0; i < numbers_.size() - 1; i++)
        {
            differences.push_back(numbers[i + 1] - numbers[i]);
        }
        differences_ = std::make_unique<NumberRun>(differences);
    }
};



void NumberRun::addNumber(int32_t number)
{
    numbers_.push_back(number);
};



bool NumberRun::isAllZero() const
{
    for(auto number : numbers_)
        if(number != 0)
            return false;
    
    return true;
};



int32_t NumberRun::getNext() const
{
    if(isAllZero())
        return 0;
    
    return (*numbers_.rbegin()) + differences_->getNext();
};