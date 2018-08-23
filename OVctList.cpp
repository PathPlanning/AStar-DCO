//
// Created by Stepan Dergachev on 08.07.18.
//

#include "OVctList.h"

OVctList::OVctList() : IOpenContainer()
{
    vlminindex = 0;
    dupl = false;
    VctLst = std::vector <std::list <Node>>();
}

OVctList::OVctList(bool breakingties, bool allowduplicates, int mapheight) : IOpenContainer(breakingties)
{
    dupl = allowduplicates;
    vlminindex = 0;
    if(this->breakingties)
    {
        this->compare = &gMaxCompare;
    }
    else
    {
        this->compare = &gMinCompare;
    }

    VctLst.resize(mapheight);
}

OVctList::OVctList(OVctList const &a) : IOpenContainer(a)
{
    this->dupl = a.dupl;
    this->vlminindex = a.vlminindex;
    this->VctLst = a.VctLst;
}

OVctList::~OVctList()
{
    for(auto it = VctLst.begin(); it != VctLst.end(); ++it)
    {
        it->clear();
    }
}

void OVctList::Add(Node elem)
{
    bool placefound = false, oldfound = false;
    std::list<Node>::const_iterator placetoinsert = VctLst[elem.i].end(), old;
    std::list<Node>::const_iterator iterator, ending = std::prev(VctLst[elem.i].end(), 1);


    for (iterator = VctLst[elem.i].begin(); iterator != VctLst[elem.i].end(); ++iterator)
    {

        if(!(*compare)((*iterator), elem) && !placefound)
        {
            placetoinsert = iterator;
            placefound = true;
            if(dupl) break;

        }

        if ((*iterator) == elem)
        {
            if (elem.F > (*iterator).F)
            {
                return;
            }
            else if(!dupl)
            {
                old = iterator;
                oldfound = true;
            }
        }
    }
    VctLst[elem.i].insert(placetoinsert, elem);
    size += 1;
    if (oldfound && !dupl)
    {
        VctLst[elem.i].erase(old);
        size -= 1;
    }
    return;
}

Node OVctList::GetOptimal()
{ Node currOpt;

    for (int i = 0; i < VctLst.size(); i++)
    {
        if (VctLst[i].size() && this->compare(VctLst[i].front(), currOpt))
        {
            vlminindex = i;
            currOpt.F  = VctLst[i].front().F;
            currOpt.g = VctLst[i].front().g;
        }
    }

    Node result = VctLst[vlminindex].front();
    VctLst[vlminindex].pop_front();
    size -= 1;
    return result;
}


