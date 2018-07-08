//
// Created by Stepan Dergachev on 08.07.18.
//

#ifndef ASEARCH_OSET_H
#define ASEARCH_OSET_H

#include "node.h"
#include "IOpenContainer.h"
#include "Compare.h"
#include <set>

class OSet : public IOpenContainer
{
    public:
        OSet();
        OSet(bool breakingties, bool allowduplicates);
        OSet(OSet const &a);
        ~OSet() override;
        void Add(Node elem) override;
        Node GetOptimal() override;

    private:
    std::set <Node, decltype(compare)> St;
    bool dupl;
};


#endif //ASEARCH_OSET_H
