#ifndef ISEARCH_H
#define ISEARCH_H
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include <list>
#include <vector>
#include <set>
#include <math.h>
#include <limits>
#include <chrono>

struct comp
{
    inline bool operator()(const Node& left,const Node& right)
    {
        return !(left.F > right.F);
    }
};

class ISearch
{
    public:
        ISearch();
        virtual ~ISearch(void);
        virtual SearchResult startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options);

    protected:
        virtual std::list<Node> findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options);
        virtual double computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options) = 0;
        bool isClosed(int i, int j);

        double Cost(Node fst, Node scn);
        void addToOpen(Node elem);
        Node GetFromOpen();
        void RefreshOpen();

        SearchResult sresult;
        std::list<Node> lppath, hppath;
        double hweight;
        bool breakingties;
        std::vector <std::list <Node>> VLOpen; // contType = 0
        std::list <Node> LOpen;                // contType = 1
        std::set<Node, comp> SOpen;                  // contType = 2
        std::unordered_map <int, Node> Close;
        Node goal;
        Node start;
        int width;
        int openSize;
        int currMinIndex;
        int contType;
};
#endif



