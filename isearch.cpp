#include "isearch.h"
#include <cfloat>

ISearch::ISearch()
{
    hweight = 1;
    breakingties = CN_SP_BT_GMAX;

}

ISearch::~ISearch(void)
{
    Close.clear();
}

/*bool ISearch::cmp(const Node& lhs, const Node& rhs)
{
    return lhs.F < rhs.F;
}*/


bool ISearch::isOpened(int i, int j)
{

    bool result = false;
    for (int c = 0; c < Open.size() && !result; c++)
    {
        result = (Open[c].i == i) && (Open[c].j == j);
    }
    return result;
}

bool ISearch::isClosed(int i, int j)
{
    bool result = false;
    for (int c = 0; c < Close.size() && !result; c++)
    {
        result = (Close[c]->i == i) && (Close[c]->j == j);
    }
    return result;
}


bool ISearch::goalIsExpended()
{
    for(int i = 0; i < Close.size(); i++)
    {
        if(*Close[i] == goal)
        {
            goal = *Close[i];
            return true;
        }
    }
    return false;
}

double ISearch::Cost(Node fst, Node scn)
{
    if(fst.i == scn.i || fst.j == scn.j )
    {
        return 1;
    }
    else
    {
        return sqrt(2);
    }
}

std::list<Node> ISearch::findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options)
{
    std::list<Node> successors;

    Node tmp;
    tmp.g = DBL_MAX;
    tmp.H = 0;
    tmp.F = DBL_MAX;
    tmp.parent = NULL;
    int y = curNode->i;
    int x = curNode->j;
    if (map.CellOnGrid(y + 1, x) && !map.CellIsObstacle(y + 1, x) && !isClosed(y + 1, x))
    {
        tmp.i = y + 1;
        tmp.j = x;

        if (!isOpened(tmp.i, tmp.j))
        {
            successors.push_back(tmp);
        }
    }
    if (map.CellOnGrid(y, x + 1) && !map.CellIsObstacle(y , x + 1) && !isClosed(y, x + 1))
    {

        tmp.i = y;
        tmp.j = x + 1;

        if (!isOpened(tmp.i, tmp.j))
        {
            successors.push_back(tmp);
        }
    }
    if (map.CellOnGrid(y - 1, x) && !map.CellIsObstacle(y - 1, x) && !isClosed(y - 1, x))
    {

        tmp.i = y - 1;
        tmp.j = x;

        if (!isOpened(tmp.i, tmp.j))
        {
            successors.push_back(tmp);
        }
    }
    if (map.CellOnGrid(y, x - 1) && !map.CellIsObstacle(y, x - 1) && !isClosed(y , x - 1))
    {

        tmp.i = y;
        tmp.j = x - 1;

        if (!isOpened(tmp.i, tmp.j))
        {
            successors.push_back(tmp);
        }
    }
    if(options.allowdiagonal)
    {
        if(map.CellOnGrid(y + 1, x + 1) && !map.CellIsObstacle(y + 1, x + 1) && !isClosed(y + 1 , x + 1))
        {
            if((!map.CellIsObstacle(y, x + 1) && !map.CellIsObstacle(y + 1, x)) || options.allowsqueeze)
            {
                if (((!map.CellIsObstacle(y, x + 1) || !map.CellIsObstacle(y + 1, x)) || options.allowsqueeze) &&
                        ((!map.CellIsObstacle(y, x + 1) && !map.CellIsObstacle(y + 1, x)) || options.cutcorners))
                {
                    tmp.i = y + 1;
                    tmp.j = x + 1;

                    if (!isOpened(tmp.i, tmp.j)) {
                        successors.push_back(tmp);
                    }
                }
            }
        }

        if(map.CellOnGrid(y - 1, x - 1) && !map.CellIsObstacle(y - 1, x - 1) && !isClosed(y - 1, x - 1))
        {
            if(((!map.CellIsObstacle(y, x - 1) || !map.CellIsObstacle(y - 1, x)) || options.allowsqueeze) &&
                    ((!map.CellIsObstacle(y, x - 1) && !map.CellIsObstacle(y - 1, x)) || options.cutcorners))
            {
                tmp.i = y - 1;
                tmp.j = x - 1;

                if (!isOpened(tmp.i, tmp.j))
                {
                    successors.push_back(tmp);
                }
            }
        }
        if(map.CellOnGrid(y + 1, x - 1) && !map.CellIsObstacle(y + 1, x - 1) && !isClosed(y + 1, x - 1))
        {
            if(((!map.CellIsObstacle(y, x - 1) || !map.CellIsObstacle(y + 1, x)) || options.allowsqueeze) &&
                    ((!map.CellIsObstacle(y, x - 1) && !map.CellIsObstacle(y + 1, x)) || options.cutcorners))
            {
                tmp.i = y + 1;
                tmp.j = x - 1;

                if (!isOpened(tmp.i, tmp.j))
                {
                    successors.push_back(tmp);
                }
            }
        }
        if(map.CellOnGrid(y - 1, x + 1) && !map.CellIsObstacle(y - 1, x + 1) && !isClosed(y - 1, x + 1))
        {
            if(((!map.CellIsObstacle(y, x + 1) || !map.CellIsObstacle(y - 1, x)) || options.allowsqueeze) &&
                    ((!map.CellIsObstacle(y, x + 1) && !map.CellIsObstacle(y - 1, x)) || options.cutcorners))
            {
                tmp.i = y - 1;
                tmp.j = x + 1;

                if (!isOpened(tmp.i, tmp.j))
                {
                    successors.push_back(tmp);
                }
            }
        }
    }

    //need to implement
    return successors;
}

/*void ISearch::makePrimaryPath(Node curNode)
{
    //need to implement
}*/

/*void ISearch::makeSecondaryPath()
{
    //need to implement
}*/
