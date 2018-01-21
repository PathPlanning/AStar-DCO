#include "dijkstra.h"


Dijkstra::Dijkstra() : ISearch()
{

}


bool Dcmp(const Node& lhs, const Node& rhs)
{
    return lhs.g < rhs.g;
}



SearchResult Dijkstra::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{


    goal = map.getFinishNode();
    start = map.getStartNode();
    int tmpx = -1, tmpy = -1;
    double sum = 0;
    unsigned int step = 0;
    Node  succ;
    Node *curr;
    std::vector<Node>::iterator currit;
    std::list<Node> succs;

    auto startpnt = std::chrono::high_resolution_clock::now();
    Open.push_back(start);

    do
    {
        currit = (std::min_element(Open.begin(), Open.end(), Dcmp));
        curr = new Node(*currit);
        Close.push_back(curr);
        Open.erase(currit);

        step++;
        succs = findSuccessors(Close.back(), map, options);
        int n = succs.size();
        for(int i = 0; i < n; i++)
        {
            succ = succs.front();
            succs.pop_front();
            double cost = map.getCellSize() * Cost(*curr, succ);
            if(succ.g > curr->g + cost)
            {
                succ.g = curr->g + cost;
                succ.parent = curr;
                Open.push_back(succ);
            }
        }
    }
    while(Open.size() && !goalIsExpended());

    if(!goalIsExpended())
    {
        sresult.pathfound = false;
    }
    else
    {
        sresult.pathfound = true;
        curr = &goal;



        while (curr != NULL)
        {
            lppath.push_front(*curr);
            if (curr->parent == NULL || curr->parent->i != tmpy && curr->parent->j != tmpx)
            {
                tmpx = curr->j;
                tmpy = curr->i;
                hppath.push_front(*curr);
            }

            if(curr->parent != NULL)
            {
                sum += Cost(*curr, *(curr->parent));
            }
            curr = curr->parent;

        }
        auto endpnt = std::chrono::high_resolution_clock::now();
        auto res  = std::chrono::duration_cast<std::chrono::microseconds>(endpnt - startpnt).count();
        sresult.lppath = &lppath;
        sresult.hppath = &hppath;
        sresult.pathlength = (float)(sum * map.getCellSize());
        sresult.numberofsteps = step;
        sresult.time = res;
        sresult.nodescreated = (unsigned int)(Open.size() + Close.size());

    }

    return sresult;
}
