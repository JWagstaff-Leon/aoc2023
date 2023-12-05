#pragma once

#include <cstdint>

class Range
{
    public:
        Range(int64_t source, int64_t destination, uint64_t range);
        
        bool coversSource(int64_t source) const;
        bool coversDestination(int64_t destination) const;
        
        int64_t sourceToDestination(int64_t source) const;
        int64_t destinationToSource(int64_t destination) const;

    private:
        int64_t source_, destination_;
        uint64_t range_;
};