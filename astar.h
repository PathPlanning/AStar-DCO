#ifndef ASTAR_H
#define ASTAR_H
#include "isearch.h"

//A* search.
class Astar : public ISearch
{
    public:
        Astar(double HW, bool BT);
        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options) override;

        protected:
                double computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options, const Map &map);
                static bool Acmp(const Node& lhs, const Node& rhs) ;

};

#endif
