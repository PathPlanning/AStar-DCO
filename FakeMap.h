//
// Created by Stepan Dergachev on 28.05.18.
//

#ifndef ASEARCH_FAKEMAP_H
#define ASEARCH_FAKEMAP_H

#include "map.h"


class FakeMap : public Map
{
    public:
        FakeMap();
        ~FakeMap() override ;

        bool getMap(const char *FileName) override ;
        bool CellIsObstacle(int i, int j) const override;
        int getValue(int i, int j) const override ;

};


#endif //ASEARCH_FAKEMAP_H
