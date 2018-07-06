//
// Created by Stepan Dergachev on 06.07.18.
//

#include "IOpenContainer.h"

IOpenContainer::IOpenContainer()
{
    size = 0;
}

IOpenContainer::IOpenContainer(bool breakingties)
{
    size = 0;
    this->breakingties = breakingties;
}

IOpenContainer::IOpenContainer(IOpenContainer const &a)
{
    this->size = a.size;
    this->compare = a.compare;
    this->breakingties = breakingties;
}

IOpenContainer::~IOpenContainer(void)
{

}

long IOpenContainer::Size() const
{
    return size;
}
