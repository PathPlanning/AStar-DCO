//
// Created by Stepan Dergachev on 08.07.18.
//

#ifndef ASEARCH_OVCTLIST_H
#define ASEARCH_OVCTLIST_H

#include "node.h"
#include "Compare.h"
#include "IOpenContainer.h"
#include <vector>
#include <list>


class OVctList : public IOpenContainer
{
    public:
        OVctList();
        OVctList(bool breakingties, bool allowduplicates, int mapheight);
        OVctList(OVctList const &a);
        ~OVctList() override;
        void Add(Node elem) override;
        Node GetOptimal() override;

    private:
        int vlminindex;
        std::vector <std::list <Node>> VctLst;
        bool dupl;
};



#endif //ASEARCH_OVCTLIST_H
