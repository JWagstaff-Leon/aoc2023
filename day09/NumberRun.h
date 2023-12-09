#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class NumberRun
{
    public:
        NumberRun(std::vector<int32_t> numbers);
        void addNumber(int32_t number);

        bool isAllZero() const;
        int32_t getNext() const;
        int32_t getPrevious() const;
    
    private:
        std::vector<int32_t> numbers_;
        std::unique_ptr<NumberRun> differences_;
};