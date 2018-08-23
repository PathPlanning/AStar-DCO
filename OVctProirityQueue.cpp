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
    Node currOpt;

    for (int i = 0; i < VctPq.size(); i++)
    {

        if (VctPq[i].size() && !this->compare(VctPq[i].top(), currOpt))
        {
            vpqminindex = i;
            currOpt.F  = VctPq[i].top().F;
            currOpt.g = VctPq[i].top().g;
        }

    }
    
    Node result = VctPq[vpqminindex].top();
    VctPq[vpqminindex].pop();
    size -= 1;
    return result;
}




