//
// Created by Stepan Dergachev on 06.07.18.
//

#ifndef ASEARCH_IOPENCONTAINER_H
#define ASEARCH_IOPENCONTAINER_H

#include "node.h"
#include "map.h"

class IOpenContainer
{
    public:
        IOpenContainer();
        explicit IOpenContainer(bool breakingties);
        IOpenContainer(IOpenContainer const &a);
        virtual ~IOpenContainer(void);
        virtual void Add(Node elem) = 0;
        virtual Node GetOptimal() = 0;
        long int Size() const;

    protected:
        long int size;
        bool breakingties;
        bool (*compare)(const Node&, const Node &);


};


#endif //ASEARCH_IOPENCONTAINER_H
