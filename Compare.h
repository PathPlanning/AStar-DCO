//
// Created by Stepan Dergachev on 07.07.18.
//

#ifndef ASEARCH_COMPARE_H
#define ASEARCH_COMPARE_H


#include "node.h"
#include <cmath>
#include <limits>
#include "gl_const.h"

static bool isEqual(double left, double right)
{
    return std::fabs(left - right) < D_EPS;
}


static bool gMaxCompare(const Node &lhs, const Node &rhs)
{
    if (isEqual(lhs.F, rhs.F))
    {
        if (isEqual(lhs.g, rhs.g))
        {
            return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
        }
        else
        {
            return  lhs.g - rhs.g > D_EPS;
        }
    }
    return lhs.F - rhs.F < D_EPS;
}

static bool gMinCompare(const Node &lhs, const Node &rhs)
{
    if (isEqual(lhs.F, rhs.F))
    {
        if (isEqual(lhs.g, rhs.g))
        {
            return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
        }
        else
        {
            return lhs.g - rhs.g < D_EPS;
        }
    }
    return lhs.F - rhs.F < D_EPS;
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