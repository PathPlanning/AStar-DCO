//
// Created by Stepan Dergachev on 07.07.18.
//

#ifndef ASEARCH_COMPARE_H
#define ASEARCH_COMPARE_H



#include "node.h"

static bool gMaxCompare(const Node &lhs, const Node &rhs)
{
    if (lhs.F == rhs.F)
    {
        if (lhs.g == rhs.g)
        {
            return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
        }
        else
        {
            return lhs.g > rhs.g;
        }
    }
    return lhs.F < rhs.F;
}

static bool gMinCompare(const Node &lhs, const Node &rhs)
{
    if (lhs.F == rhs.F)
    {
        if (lhs.g == rhs.g)
        {
            return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
        }
        else
        {
            return lhs.g < rhs.g;
        }
    }
    return lhs.F < rhs.F;
}

static bool inline gMaxComparePQ(const Node &lhs, const Node &rhs)
{
    return !gMaxCompare(lhs, rhs);
}

static bool inline gMinComparePQ(const Node &lhs, const Node &rhs)
{
    return !gMinCompare(lhs, rhs);
}

#endif //ASEARCH_COMPARE_H