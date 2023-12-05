#include "RangeMap.h"

#include <cstdint>

void RangeMap::addRange(int64_t source, int64_t destination, uint64_t range)
{
    ranges_.push_back(Range(source, destination, range));
};



int64_t RangeMap::sourceToDestination(int64_t source) const
{
    for(auto range : ranges_)
        if(range.coversSource(source))
            return range.sourceToDestination(source);

    return source;
};



int64_t RangeMap::destinationToSource(int64_t destination) const
{
    for(auto range : ranges_)
        if(range.coversDestination(destination))
            return range.destinationToSource(destination);

    return destination;
};