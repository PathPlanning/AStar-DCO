//
// Created by Stepan Dergachev on 07.07.18.
//

#ifndef ASEARCH_OPRIORITYQUEUE_H
#define ASEARCH_OPRIORITYQUEUE_H

#include "node.h"
#include "IOpenContainer.h"
#include <vector>
#include <queue>
#include "Compare.h"

class OPriorityQueue : public IOpenContainer
{
    public:
        OPriorityQueue();
        explicit OPriorityQueue(bool breakingties);
        OPriorityQueue(OPriorityQueue const &a);
        ~OPriorityQueue() override;
        void Add(Node elem) override;
        Node GetOptimal() override;

    private:
        std::priority_queue <Node, std::vector<Node>, decltype(compare)> Pq;

};


#endif //ASEARCH_OPRIORITYQUEUE_H
