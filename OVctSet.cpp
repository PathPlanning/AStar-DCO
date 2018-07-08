//
// Created by Stepan Dergachev on 08.07.18.
//

#include "OVctSet.h"

OVctSet::OVctSet() : IOpenContainer()
{
    dupl = false;
    vsminindex = 0;
    VctSt.resize(0);
}

OVctSet::OVctSet(bool breakingties, bool allowduplicates, int mapheight) : IOpenContainer(breakingties)
{
    dupl = allowduplicates;
    vsminindex = 0;
    if(this->breakingties)
    {
        this->compare = &gMaxCompare;
    }
    else
    {
        this->compare = &gMinCompare;
    }

    VctSt.resize(mapheight);
    for(int i = 0; i < VctSt.size(); i++)
    {
        VctSt[i]= std::set<Node, bool(*)(const Node&, const Node&)>(compare);
    }
}

OVctSet::OVctSet(OVctSet const &a) : IOpenContainer(a)
{
    this->dupl = a.dupl;
    this->vsminindex = a.vsminindex;
    this->VctSt = a.VctSt;
}


OVctSet::~OVctSet()
{
    for(auto it = VctSt.begin(); it != VctSt.end(); ++it)
    {
        it->clear();
    }
}

void OVctSet::Add(Node elem)
{
    if(!dupl)
    {
        auto a = std::find(VctSt[elem.i].begin(), VctSt[elem.i].end(), elem);
        if (a != VctSt[elem.i].end())
        {
            if (a->F > elem.F)
            {
                VctSt[elem.i].erase(a);
                size -= 1;
            } else
            {
                return;
            }
        }
    }
    if(VctSt[elem.i].insert(elem).second)
    {
        size += 1;
    }
    return;
}

Node OVctSet::GetOptimal()
{
    double currFMin = DBL_MAX;
    double currG;
    for (int i = 0; i < VctSt.size(); i++)
    {
        if (VctSt[i].size() && currFMin >= VctSt[i].begin()->F)
        {
            if (currFMin != VctSt[i].begin()->F || ((breakingties && VctSt[i].begin()->g > currG) || (!breakingties && VctSt[i].begin()->g < currG)))
            {
                vsminindex = i;
                currFMin = VctSt[i].begin()->F;
                currG = VctSt[i].begin()->g;
            }

        }

    }
    auto a = VctSt[vsminindex].begin();
    Node result = *a;
    VctSt[vsminindex].erase(a);
    size -= 1;
    return result;
}



