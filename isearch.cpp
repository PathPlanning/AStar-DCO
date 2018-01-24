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


int ISearch::isOpened(int i, int j)
{

    int result = -1;

    for (int c = 0; c < Open.size() && result == -1; c++)
    {
        if ((Open[c].i == i) && (Open[c].j == j))
        {
            result = c;
        }
    }
    return result;
}

int ISearch::isClosed(int i, int j)
{
    int result = -1;

    for (int c = 0; c < Close.size() && result == -1; c++)
    {
        if ((Close[c]->i == i) && (Close[c]->j == j))
        {
            result = c;
        }
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
        return 1.41421356237;
    }
}

std::list<Node> ISearch::findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options)
{
    std::list<Node> successors;

    Node tmp;
    std::vector<Node>::iterator tmpit;
    tmp.g = DBL_MAX;
    tmp.H = 0;
    tmp.F = DBL_MAX;
    tmp.parent = NULL;
    int y = curNode->i;
    int x = curNode->j;
    if (map.CellOnGrid(y + 1, x) && !map.CellIsObstacle(y + 1, x) && isClosed(y + 1, x) == -1)
    {
        tmp.i = y + 1;
        tmp.j = x;
        successors.push_back(tmp);

    }
    if (map.CellOnGrid(y, x + 1) && !map.CellIsObstacle(y , x + 1) && isClosed(y, x + 1) == -1)
    {

        tmp.i = y;
        tmp.j = x + 1;
        successors.push_back(tmp);

    }
    if (map.CellOnGrid(y - 1, x) && !map.CellIsObstacle(y - 1, x) && isClosed(y - 1, x) == -1)
    {

        tmp.i = y - 1;
        tmp.j = x;
        successors.push_back(tmp);

    }
    if (map.CellOnGrid(y, x - 1) && !map.CellIsObstacle(y, x - 1) && isClosed(y , x - 1) == -1)
    {

        tmp.i = y;
        tmp.j = x - 1;
        successors.push_back(tmp);
    }
    if(options.allowdiagonal)
    {
        if(map.CellOnGrid(y + 1, x + 1) && !map.CellIsObstacle(y + 1, x + 1) && isClosed(y + 1 , x + 1) == -1)
        {
            if((!map.CellIsObstacle(y, x + 1) && !map.CellIsObstacle(y + 1, x)) || options.allowsqueeze)
            {
                if (((!map.CellIsObstacle(y, x + 1) || !map.CellIsObstacle(y + 1, x)) || options.allowsqueeze) &&
                        ((!map.CellIsObstacle(y, x + 1) && !map.CellIsObstacle(y + 1, x)) || options.cutcorners))
                {
                    tmp.i = y + 1;
                    tmp.j = x + 1;
                    successors.push_back(tmp);

                }
            }
        }

        if(map.CellOnGrid(y - 1, x - 1) && !map.CellIsObstacle(y - 1, x - 1) && isClosed(y - 1, x - 1) == -1)
        {
            if(((!map.CellIsObstacle(y, x - 1) || !map.CellIsObstacle(y - 1, x)) || options.allowsqueeze) &&
                    ((!map.CellIsObstacle(y, x - 1) && !map.CellIsObstacle(y - 1, x)) || options.cutcorners))
            {
                tmp.i = y - 1;
                tmp.j = x - 1;
                successors.push_back(tmp);

            }
        }
        if(map.CellOnGrid(y + 1, x - 1) && !map.CellIsObstacle(y + 1, x - 1) && isClosed(y + 1, x - 1) == -1)
        {
            if(((!map.CellIsObstacle(y, x - 1) || !map.CellIsObstacle(y + 1, x)) || options.allowsqueeze) &&
                    ((!map.CellIsObstacle(y, x - 1) && !map.CellIsObstacle(y + 1, x)) || options.cutcorners))
            {
                tmp.i = y + 1;
                tmp.j = x - 1;
                successors.push_back(tmp);

            }
        }
        if(map.CellOnGrid(y - 1, x + 1) && !map.CellIsObstacle(y - 1, x + 1) && isClosed(y - 1, x + 1) == -1)
        {
            if(((!map.CellIsObstacle(y, x + 1) || !map.CellIsObstacle(y - 1, x)) || options.allowsqueeze) &&
                    ((!map.CellIsObstacle(y, x + 1) && !map.CellIsObstacle(y - 1, x)) || options.cutcorners))
            {
                tmp.i = y - 1;
                tmp.j = x + 1;
                successors.push_back(tmp);
            }
        }
    }

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
