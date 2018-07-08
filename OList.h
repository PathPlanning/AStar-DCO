//
// Created by Stepan Dergachev on 06.07.18.
//

#ifndef ASEARCH_OLIST_H
#define ASEARCH_OLIST_H

#include "IOpenContainer.h"
#include "Compare.h"
#include <list>

class OList : public IOpenContainer
{
    public:
        OList();
        OList(bool breakingties, bool allowduplicates);
        OList(OList const &a);
        ~OList() override;
        void Add(Node elem) override;
        Node GetOptimal() override;

    private:
        std::list <Node> Lst;
        bool dupl;
};


#endif //ASEARCH_OLIST_H
