#include <list>
#include <vector>
#include <set>
#include "node.h"
#include "map.h"

#ifndef ASEARCH_OCONTEINER_H
#define ASEARCH_OCONTEINER_H


class OConteiner
{
public:
    OConteiner();
    OConteiner(int ctype, bool brts, const Map &map);
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
    std::vector <std::list <Node>> VctLst;                          // contType = 0
    std::list <Node> Lst;                                           // contType = 1
    std::set<Node, decltype(compare)> St;                           // contType = 2

};


#endif //ASEARCH_OCONTEINER_H
