//
// Created by Stepan Dergachev on 06.07.18.
//

#include "OList.h"
bool gMaxCompare1(const Node &lhs, const Node &rhs)
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

OList::OList() : IOpenContainer()
{
    Lst = std::list <Node>();
    dupl = 0;
}

OList::OList(bool breakingties) : IOpenContainer(breakingties)
{
    Lst = std::list <Node>();
    dupl = 0;
    if(this->breakingties)
    {
        this->compare = &gMaxCompare1;
    }
    else
    {
        this->compare = gMaxCompare1;
    }
}

OList::OList(OList const &a) : IOpenContainer(a)
{
    this->dupl = a.dupl;
    this->Lst = a.Lst;
}

OList::~OList()
{

}

void OList::Add(Node elem)
{
    bool placefound = false, oldfound = false;

    std::list<Node>::const_iterator placetoinsert = Lst.end(), old;
    std::list<Node>::iterator iterator, ending = std::prev(Lst.end(), 1);

    for (iterator = Lst.begin(); iterator != Lst.end(); ++iterator)
    {
        if ((*compare)(elem, (*iterator)) && !placefound)
        {
            placetoinsert = iterator;
            placefound = true;
            if (dupl) break;
        }
        if ((*iterator) == elem)
        {
            if (elem.F > (*iterator).F)
            {
                return;
            }
            else if (!dupl)
            {
                old = iterator;
                oldfound = true;
            }
        }
    }

    Lst.insert(placetoinsert, elem);
    size += 1;

    if (oldfound && !dupl)
    {
        Lst.erase(old);
        size -= 1;
    }
    return;
}

Node OList::GetOptimal()
{
    Node result = Lst.front();
    Lst.pop_front();
    size -= 1;
    return result;
}






