#pragma once
#include "Building/Node.h"
#include "Building/Building.h"
class myComparator
{
public:
    int operator() (const Building::value* p1, const Building::value* p2)
    {
        return p1->w > p2->w;
    }
};
