//
// Created by Stepan Dergachev on 08.07.18.
//

#ifndef ASEARCH_OVCTPROIRITYQUEUE_H
#define ASEARCH_OVCTPROIRITYQUEUE_H

#include "node.h"
#include "Compare.h"
#include "IOpenContainer.h"
#include <vector>
#include <queue>

class OVctProirityQueue : public IOpenContainer
{
public:
    OVctProirityQueue();
    OVctProirityQueue(bool breakingties, int mapheight);
    OVctProirityQueue(OVctProirityQueue const &a);
    ~OVctProirityQueue() override;
    void Add(Node elem) override;
    Node GetOptimal() override;

private:
    std::vector<std::priority_queue <Node, std::vector<Node>, decltype(compare)>> VctPq;
    int vpqminindex;

};


#endif //ASEARCH_OVCTPROIRITYQUEUE_H
