//
// Created by Stepan Dergachev on 08.07.18.
//

#include "OVctProirityQueue.h"

OVctProirityQueue::OVctProirityQueue() : IOpenContainer()
{
    vpqminindex = 0;
    VctPq.resize(0);
}

OVctProirityQueue::OVctProirityQueue(bool breakingties, int mapheight) : IOpenContainer(breakingties)
{
    vpqminindex = 0;
    if(this->breakingties)
    {
        this->compare = &gMaxComparePQ;
    }
    else
    {
        this->compare = &gMinComparePQ;
    }

    VctPq.resize(mapheight);
    for(int i = 0; i < VctPq.size(); i++)
    {
        VctPq[i]= std::priority_queue<Node, std::vector<Node>, bool(*)(const Node&, const Node&)>(compare);
    }
}

OVctProirityQueue::OVctProirityQueue(OVctProirityQueue const &a) : IOpenContainer(a)
{
    this->vpqminindex = a.vpqminindex;
    this->VctPq = a.VctPq;
}

OVctProirityQueue::~OVctProirityQueue()
{
    for(auto it = VctPq.begin(); it != VctPq.end(); ++it)
    {
        while(it->size())
        {
            it->pop();
        }
    }
}

void OVctProirityQueue::Add(Node elem)
{
    VctPq[elem.i].push(elem);
    size += 1;
    return;
}

Node OVctProirityQueue::GetOptimal()
{
    double currFMin = DBL_MAX;
    double currG;
    for (int i = 0; i < VctPq.size(); i++)
    {
        if (VctPq[i].size() && currFMin >= VctPq[i].top().F)
        {
            if (currFMin != VctPq[i].top().F || ((breakingties && VctPq[i].top().g > currG) || (!breakingties && VctPq[i].top().g < currG)))
            {
                vpqminindex = i;
                currFMin = VctPq[i].top().F;
                currG = VctPq[i].top().g;
            }

        }

    }
    Node result = VctPq[vpqminindex].top();
    VctPq[vpqminindex].pop();
    size -= 1;
    return result;
}




