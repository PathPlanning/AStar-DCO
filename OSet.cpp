//
// Created by Stepan Dergachev on 08.07.18.
//

#include "OSet.h"

OSet::OSet() : IOpenContainer()
{
    St = std::set<Node, bool(*)(const Node&, const Node&)>(compare);
    dupl = false;
}

OSet::OSet (bool breakingties, bool allowduplicates) : IOpenContainer(breakingties)
{

    dupl = allowduplicates;
    if(this->breakingties)
    {
        this->compare = &gMaxCompare;
    }
    else
    {
        this->compare = &gMinCompare;
    }

    St = std::set<Node, bool(*)(const Node&, const Node&)>(compare);
}

OSet::OSet(OSet const &a) : IOpenContainer(a)
{
    this->dupl = a.dupl;
    this->St = a.St;
}

OSet::~OSet()
{
    St.clear();
}

void OSet::Add(Node elem)
{
    if(!dupl)
    {
        auto a = std::find(St.begin(), St.end(), elem);
        if (a != St.end())
        {
            if (a->F > elem.F)
            {
                St.erase(a);
                size -= 1;
            }
            else
            {
                return;
            }
        }
    }
    if(St.insert(elem).second)
    {
        size += 1;
    }
    return;
}

Node OSet::GetOptimal()
{
    auto resit = St.begin();
    Node result = *resit;
    St.erase(resit);
    size -= 1;
    return result;
}