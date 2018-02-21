#include "isearch.h"
#include <cfloat>

ISearch::ISearch()
{
    hweight = 1;
    breakingties = CN_SP_BT_GMAX;
    start.g = 0;
    start.H = 0;
    start.F = DBL_MAX;
    goal.g = DBL_MAX;
    goal.H = 0;
    goal.F = DBL_MAX;
    openSize = 0;

}

ISearch::~ISearch(void)
{

}

void ISearch::addToOpen(Node elem)
{
    std::list<Node>::const_iterator placetoinsert = Open[elem.i].end(), old;
    std::list<Node>::const_iterator iterator;

    bool placefound = false, oldfound = false;
    for (iterator = Open[elem.i].begin(); iterator != Open[elem.i].end(); ++iterator)
    {
        if((*iterator).F > elem.F and !placefound)
        {
            int tmpf = (*iterator).F;
            while((*iterator).F == tmpf && ((breakingties && (*iterator).g > elem.g) || (!breakingties && (*iterator).g < elem.g))) ++iterator;
            placetoinsert = iterator;
            placefound = true;

        }
        if((*iterator) == elem)
        {
            if(elem.F > (*iterator).F)
            {
                return;
            }
            else
            {
                old = iterator;
                oldfound = true;
                if(placefound)
                    break;
            }
        }
    }
    Open[elem.i].insert(placetoinsert, elem);
    openSize += 1;
    if(oldfound)
    {
        Open[elem.i].erase(old);
        openSize -= 1;
    }


}

SearchResult ISearch::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{

    width = map.getMapWidth();
    goal.i = map.getFinishI();
    goal.j = map.getFinishJ();
    start.i = map.getStartI();
    start.j = map.getStartJ();
    Open.resize(map.getMapHeight());
    int tmpx = -1, tmpy = -1;
    std::vector<Node>::iterator currit,  tmpit;
    double sum = 0, cost = 0;
    unsigned int step = 0;
    Node succ;
    Node curr;
    std::list<Node> succs;

    auto startpnt = std::chrono::high_resolution_clock::now();
    start.H = computeHFromCellToCell(start.i, start.j, goal.i, goal.j, options);
    start.F = start.g + hweight * start.H;
    start.br = breakingties;
    goal.br = breakingties;
    addToOpen(start);
    currMinIndex = start.i;


    do
    {
        curr = Open[currMinIndex].front();
        Close.insert({curr.i *  width + curr.j, curr});
        Open[currMinIndex].pop_front();
        openSize -= 1;

        if(curr == goal)
        {
            goal = Close.at(goal.i * width + goal.j);
            break;
        }

        step++;
        succs = findSuccessors(&curr, map, options);
        int n = succs.size();
        for(int i = 0; i < n; i++)
        {
            succ = succs.front();
            succs.pop_front();
            cost = Cost(curr, succ);
            if(succ.g > curr.g + cost)
            {
                succ.g = curr.g + cost;
                succ.H = computeHFromCellToCell(succ.i, succ.j, goal.i, goal.j, options);
                succ.F = succ.g + hweight * succ.H;
                succ.br = breakingties;
                succ.parent = &Close.at(curr.i * width + curr.j);
                addToOpen(succ);
            }
        }
        searchMin();
    }
    while(openSize);

    if(!isClosed(goal.i, goal.j))
    {
        sresult.pathfound = false;
    }
    else
    {
        sresult.pathfound = true;

        Node *curr1 = &goal;


        while (curr1 != NULL)
        {
            lppath.push_front(*curr1);
            if (curr1->parent == NULL || curr1->parent->i != tmpy && curr1->parent->j != tmpx)
            {
                tmpx = curr1->j;
                tmpy = curr1->i;
                hppath.push_front(*curr1);
            }
            if(curr1->parent != NULL)
            {
                sum += Cost(*curr1, *(curr1->parent));
            }
            curr1 = curr1->parent;

        }
        auto endpnt = std::chrono::high_resolution_clock::now();
        long long int res  = std::chrono::duration_cast<std::chrono::milliseconds>(endpnt - startpnt).count();
        sresult.lppath = &lppath;
        sresult.hppath = &hppath;
        sresult.pathlength = (float)sum;
        sresult.numberofsteps = step;
        sresult.time = ((double)res)/1000;
        sresult.nodescreated = (unsigned int)(openSize + Close.size());

    }

    return sresult;
}

double ISearch::Cost(Node fst, Node scn)
{
    if(fst.i == scn.i || fst.j == scn.j )
    {
        return 1;
    }
    else
    {
        return 1.41421356237;
    }
}

std::list<Node> ISearch::findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options)
{
    int y = curNode->i;
    int x = curNode->j;
    std::list<Node> successors;

    Node tmp;
    std::vector<Node>::iterator tmpit;



    for(int i = y - 1; i <= y + 1; i++)
    {
        for(int j = x - 1; j <= x + 1; j++)
        {
            if(map.CellOnGrid(i, j) && !map.CellIsObstacle(i, j) && !isClosed(i, j))
            {
                if(i != y || j != x)
                {
                    if((abs(i - y) - abs(j - x)))
                    {
                        tmp.i = i;
                        tmp.j = j;
                        successors.push_back(tmp);
                    }
                    else if(options.allowdiagonal)
                    {
                        if(!(map.CellIsObstacle(y, j) || map.CellIsObstacle(i, x)))
                        {
                            tmp.i = i;
                            tmp.j = j;
                            successors.push_back(tmp);
                        }
                        else if(options.cutcorners)
                        {
                            if(!(map.CellIsObstacle(y, j) && map.CellIsObstacle(i, x)))
                            {
                                tmp.i = i;
                                tmp.j = j;
                                successors.push_back(tmp);
                            }
                            else if(options.allowsqueeze)
                            {
                                tmp.i = i;
                                tmp.j = j;
                                successors.push_back(tmp);
                            }

                        }
                    }
                }
            }
        }
    }

    return successors;
}

bool ISearch::isClosed(int i, int j)
{

    return (Close.find(i * width + j) != Close.end());

}

void ISearch::searchMin()
{
    double currFMin = DBL_MAX;
    double currG;
    for (int i = 0; i < Open.size(); i++)
    {
        if (Open[i].size() && currFMin >= Open[i].front().F)
        {
            if(currFMin != Open[i].front().F || ((breakingties && Open[i].front().g > currG) || (!breakingties && Open[i].front().g < currG)))
            {
                currMinIndex = i;
                currFMin = Open[i].front().F;
                currG = Open[i].front().g;
            }

        }

    }
}

/*void ISearch::makePrimaryPath(Node curNode)
{
    //need to implement
}*/

/*void ISearch::makeSecondaryPath()
{
    //need to implement
}*/
