#include "astar.h"

Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
}

double Astar::computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options, const Map &map)
{
    int dx, dy, d1 = map.getCellSize();
    double d2;
    dx = abs(i1 - i2);
    dy = abs(j1 - j2);

    switch (options.metrictype)
    {
        case 0: //Диагональ
            d2 = sqrt(d1 * d1 + d1 * d1);
            return d1 * (dx + dy) + (d2 - 2 * d1) * std::min(dx, dy);

        case 1: //Манхеттен 
            return d1 * (dx + dy);

        case 2://Евклидово расстояние
            return d1 * sqrt(dx * dx + dy * dy);

        case 3://Расстояние Чебышёва

            return d1 * (dx + dy) + (d1 - 2 * d1) * std::min(dx, dy);
        default:

            return 0;

    }
}

bool Astar::Acmp(const Node& lhs, const Node& rhs)
{
    if(lhs.F != rhs.F)
    {
        return lhs.F < rhs.F;
    }
    if(lhs.br)
    {
        return lhs.g > rhs.g; // g-max
    }
    else
    {
        return lhs.g < rhs.g; //g-min
    }
}



SearchResult Astar::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{

    goal = map.getFinishNode();
    start = map.getStartNode();
    int tmpx = -1, tmpy = -1;
    double sum = 0;
    unsigned int step = 0;
    Node succ;
    Node *curr;
    std::vector<Node>::iterator currit;
    std::list<Node> succs;

    auto startpnt = std::chrono::high_resolution_clock::now();
    start.H = computeHFromCellToCell(start.i, start.j, goal.i, goal.j, options, map);
    start.F = start.g + hweight * start.H;
    start.br = breakingties;
    goal.br = breakingties;
    Open.push_back(start);


    do
    {
        currit = std::min_element(Open.begin(), Open.end(), Acmp);
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
                succ.H = computeHFromCellToCell(succ.i, succ.j, goal.i, goal.j, options, map);
                succ.F = succ.g + hweight * succ.H;
                succ.br = breakingties;
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
        sresult.pathlength = sum * map.getCellSize();
        sresult.numberofsteps = step;
        sresult.time = res;
        sresult.nodescreated = (unsigned int)(Open.size() + Close.size());

    }

    return sresult;
}