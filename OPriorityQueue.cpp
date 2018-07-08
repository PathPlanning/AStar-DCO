//
// Created by Stepan Dergachev on 07.07.18.
//

#include "OPriorityQueue.h"


OPriorityQueue::OPriorityQueue() : IOpenContainer()
{
    Pq = std::priority_queue<Node, std::vector<Node>, bool(*)(const Node&, const Node&)>(compare);
}

OPriorityQueue::OPriorityQueue(bool breakingties) : IOpenContainer(breakingties)
{
    if(this->breakingties)
    {
        compare = &gMaxComparePQ;
    }
    else
    {
        compare = &gMinComparePQ;
    }

    Pq = std::priority_queue<Node, std::vector<Node>, bool(*)(const Node&, const Node&)>(compare);
}

OPriorityQueue::OPriorityQueue(OPriorityQueue const &a) : IOpenContainer(a)
{
    this->Pq = a.Pq;
}

OPriorityQueue::~OPriorityQueue()
{
    while(Pq.size())
    {
        Pq.pop();
    }

}

void OPriorityQueue::Add(Node elem)
{
    Pq.push(elem);
    size += 1;
    return;
}

Node OPriorityQueue::GetOptimal()
{
    Node result = Pq.top();
    Pq.pop();
    size -= 1;
    return result;
}

