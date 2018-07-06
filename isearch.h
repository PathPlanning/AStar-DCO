#ifndef ISEARCH_H
#define ISEARCH_H
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include "OConteiner.h"
#include "IOpenContainer.h"
#include "OList.h"
#include <list>
#include <vector>
#include <set>
#include <math.h>
#include <limits>
#include <chrono>

class ISearch
{
    public:
        ISearch();
        virtual ~ISearch(void);
        virtual SearchResult startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options, const int opentype, const int duplicate);

    protected:
        virtual std::list<Node> findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options);
        virtual double computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options) = 0;
        bool isClosed(int i, int j);

        double Cost(Node fst, Node scn);

        SearchResult sresult;
        std::list<Node> lppath, hppath;
        double hweight;
        bool breakingties;

        std::unordered_map <int, Node> Close;
        IOpenContainer *Open;
        Node goal;
        Node start;
        int width;
        int contType;
        bool dupl;
};
#endif



