#include <list>
#include <vector>
#include <set>
#include <queue>
#include "node.h"
#include "map.h"

#ifndef ASEARCH_OCONTEINER_H
#define ASEARCH_OCONTEINER_H


class OConteiner
{
public:
    OConteiner();
    OConteiner(int ctype, bool brts, bool endupl, const Map &map);
    OConteiner(OConteiner const &a);
    ~OConteiner(void);
    void Add(Node elem);
    Node GetOptimal();
    //bool Check(Node elem);
    long int Size() const;


protected:
    bool dupl;
    bool breakingties;
    int type;
    int vlminindex;
    long int size;
    bool (*compare)(const Node&, const Node &);
    std::vector <std::list <Node>> VctLst;                                  // contType = 0
    std::list <Node> Lst;                                                   // contType = 1
    std::set <Node, decltype(compare)> St;                                  // contType = 2
    std::priority_queue <Node, std::vector<Node>, decltype(compare)> Pq;    // contType = 3
    std::vector<std::priority_queue <Node, std::vector<Node>, decltype(compare)>> VctPq; // contType = 4
    std::vector<std::set <Node, decltype(compare)>> VctSt; // contType = 5
};


#endif //ASEARCH_OCONTEINER_H
