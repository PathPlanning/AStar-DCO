#ifndef ISEARCH_H
#define ISEARCH_H
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include <list>
#include <vector>
#include <math.h>
#include <limits>
#include <chrono>

class ISearch
{
    public:
        ISearch();
        virtual ~ISearch(void);
        virtual SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options) = 0;

    protected:
        virtual std::list<Node> findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options);
        bool isOpened(int i, int j);
        bool isClosed(int i, int j);
        bool goalIsExpended();
        double Cost(Node fst, Node scn);

        //bool cmp(const Node& lhs, const Node& rhs);

        SearchResult sresult;
        std::list<Node> lppath, hppath;
        double hweight; //weight of h-value
        bool breakingties;//flag that sets the priority of nodes in addOpen function when their F-values is equal
        std::vector<Node> Open;
        std::vector<Node*> Close;
        Node goal;
        Node start;
    //need to define open, close;

    //CODE HERE
    //Try to split class functionality to the methods that can be re-used in successors classes,
    //e.g. classes that realize A*, JPS, Theta* algorithms

    //Hint 1. You definetely need class variables for OPEN and CLOSE

    //Hint 2. It's a good idea to define a heuristic calculation function, that will simply return 0
    //for non-heuristic search methods like Dijkstra

    //Hint 3. It's a good idea to define function that given a node (and other stuff needed)
    //will return it's sucessors, e.g. unordered list of nodes

    //Hint 4. It's a good idea to define a resetParent function that will be extensively used for Theta*
    //and for A*/Dijkstra/JPS will exhibit "default" behaviour

    //Hint 5. The last but not the least: working with OPEN and CLOSE is the core
    //so think of the data structures that needed to be used, about the wrap-up classes (if needed)
    //Start with very simple (and ineffective) structures like list or vector and make it work first
    //and only then begin enhancement!



    //
    //
    //void makePrimaryPath(Node curNode);//Makes path using back pointers
    //void makeSecondaryPath();//Makes another type of path(sections or points)
    //Node resetParent(Node current, Node parent, const Map &map, const EnvironmentOptions &options) {return current;}//need for Theta*


};
#endif
