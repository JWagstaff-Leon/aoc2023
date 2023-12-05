#include "Range.h"

Range::Range(int64_t source, int64_t destination, uint64_t range)
: source_(source), destination_(destination), range_(range)
{ /* Intentionally empty */ };



bool Range::coversSource(int64_t source) const
{
    int64_t offset = source - source_;
    return offset < range_ && offset >= 0;
};



bool Range::coversDestination(int64_t destination) const
{
    int64_t offset = destination - destination_;
    return offset < range_ && offset >= 0;
};



int64_t Range::sourceToDestination(int64_t source) const
{
    int64_t offset = source - source_;
    if(offset < range_ && offset >= 0)
        return destination_ + offset;
    return source;
};



int64_t Range::destinationToSource(int64_t destination) const
{
    int64_t offset = destination - destination_;
    if(offset < range_ && offset >= 0)
        return source_ + offset;
    return destination;
};