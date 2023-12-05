#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

#include "Range.h"

class RangeMap
{
    public:
        void addRange(int64_t source, int64_t destination, uint64_t range);

        int64_t sourceToDestination(int64_t source) const;
        int64_t destinationToSource(int64_t dest) const;

    private:
        std::vector<Range> ranges_;
};