#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "isearch.h"

class Dijkstra : public ISearch
{
    public:
        Dijkstra();
        SearchResult startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options) override;
    private:

};
#endif
