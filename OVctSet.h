//
// Created by Stepan Dergachev on 08.07.18.
//

#ifndef ASEARCH_OVCTSET_H
#define ASEARCH_OVCTSET_H

#include "node.h"
#include "Compare.h"
#include "IOpenContainer.h"
#include <vector>
#include <Set>

class OVctSet : public  IOpenContainer
{
    public:
        OVctSet();
        OVctSet(bool breakingties, bool allowduplicates, int mapheight);
        OVctSet(OVctSet const &a);
        ~OVctSet() override;
        void Add(Node elem) override;
        Node GetOptimal() override;

    private:
        std::vector<std::set <Node, decltype(compare)>> VctSt;
        int vsminindex;
        bool dupl;
};


#endif //ASEARCH_OVCTSET_H
