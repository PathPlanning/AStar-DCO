

#include "OConteiner.h"

bool gMaxCompare(const Node &lhs, const Node &rhs)
{
    if (lhs.F == rhs.F)
    {
        if (lhs.g == rhs.g)
        {
            return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
        }
        else
        {
            return lhs.g > rhs.g;
        }
    }
    return lhs.F < rhs.F;
}

inline bool gMinCompare(const Node &lhs, const Node &rhs)
{
    if (lhs.F == rhs.F)
    {
        if (lhs.g == rhs.g)
        {
            return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
        }
        else
        {
            return lhs.g < rhs.g;
        }
    }
    return lhs.F < rhs.F;
}

bool gMaxComparePQ(const Node &lhs, const Node &rhs)
{
    return !gMaxCompare(lhs, rhs);
}

bool gMinComparePQ(const Node &lhs, const Node &rhs)
{
    return !gMinCompare(lhs, rhs);
}


OConteiner::OConteiner()
{
    dupl = 0;
    breakingties = 0;
    type = 0;
    vlminindex = 0;
    size = 0;
    compare = NULL;
}

OConteiner::~OConteiner()
{

}

OConteiner::OConteiner(int ctype, bool brts,bool endupl ,const Map &map)
{
    size = 0;
    type = ctype;
    breakingties = brts;
    dupl = endupl;
    if(breakingties)
    {
        compare = &gMaxCompare;
    }
    else
    {
        compare = &gMinCompare;
    }

    switch(ctype)
    {
        case 0:
        {
            VctLst.resize(map.getMapHeight());
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            St = std::set<Node, bool(*)(const Node&, const Node&)>(compare);
            break;
        }
        case 3:
        {
            if(breakingties)
            {
                compare = &gMaxComparePQ;
            }
            else
            {
                compare = &gMinComparePQ;
            }
            Pq = std::priority_queue<Node, std::vector<Node>, bool(*)(const Node&, const Node&)>(compare);
            break;
        }
        case 4:
        {
            if(breakingties)
            {
                compare = &gMaxComparePQ;
            }
            else
            {
                compare = &gMinComparePQ;
            }
            VctPq.resize(map.getMapHeight());
            for(int i = 0; i < VctPq.size(); i++)
            {
                VctPq[i]= std::priority_queue<Node, std::vector<Node>, bool(*)(const Node&, const Node&)>(compare);
            }

        }
        case 5:
        {
            VctSt.resize(map.getMapHeight());
            for(int i = 0; i < VctSt.size(); i++)
            {
                VctSt[i]= std::set<Node, bool(*)(const Node&, const Node&)>(compare);
            }

        }
    }

}

OConteiner::OConteiner(OConteiner const &a)
{
    dupl = a.dupl;
    breakingties = a.breakingties;
    type = a.type;
    vlminindex = a.vlminindex;
    size = a.size;
    compare = a.compare;
    VctLst = a.VctLst;
    Lst = a.Lst;
    St = a.St;
}



void OConteiner::Add(Node elem)
{
  bool placefound = false, oldfound = false;
    switch (type)
    {
        case 0:
        {
            std::list<Node>::const_iterator placetoinsert = VctLst[elem.i].end(), old;
            std::list<Node>::const_iterator iterator, ending = std::prev(VctLst[elem.i].end(), 1);


            for (iterator = VctLst[elem.i].begin(); iterator != VctLst[elem.i].end(); ++iterator)
            {

                if(!(*compare)((*iterator), elem) && !placefound)
                {
                    placetoinsert = iterator;
                    placefound = true;
                    if(dupl) break;

                }

                if ((*iterator) == elem)
                {
                    if (elem.F > (*iterator).F)
                    {
                        return;
                    }
                    else if(!dupl)
                    {
                        old = iterator;
                        oldfound = true;
                    }
                }
            }
            VctLst[elem.i].insert(placetoinsert, elem);
            size += 1;
            if (oldfound && !dupl)
            {
                VctLst[elem.i].erase(old);
                size -= 1;
            }
            return;
        }
        case 1:
        {
            std::list<Node>::const_iterator placetoinsert = Lst.end(), old;
            std::list<Node>::iterator iterator, ending = std::prev(Lst.end(), 1);

            for (iterator = Lst.begin(); iterator != Lst.end(); ++iterator)
            {
                if((*compare)(elem, (*iterator)) && !placefound)
                {
                    placetoinsert = iterator;
                    placefound = true;
                    if(dupl) break;
                }
                if ((*iterator) == elem )
                {
                    if (elem.F > (*iterator).F)
                    {
                        return;
                    }
                    else if(!dupl)
                    {
                        old = iterator;
                        oldfound = true;
                    }
                }
            }

            Lst.insert(placetoinsert, elem);
            size += 1;



            if (oldfound && !dupl)
            {
                Lst.erase(old);
                size -= 1;
            }
            return;
        }
        case 2:
        {
            if(!dupl)
            {
                auto a = std::find(St.begin(), St.end(), elem);
                if (a != St.end())
                {
                    if (a->F > elem.F)
                    {
                        St.erase(a);
                        size -= 1;
                    } else
                    {
                        return;
                    }
                }
            }
            if(St.insert(elem).second)
            {
                size += 1;
            }
            return;

        }
        case 3:
        {

            Pq.push(elem);
            size += 1;
            return;

        }
        case 4:
        {

            VctPq[elem.i].push(elem);
            size += 1;
            return;

        }
        case 5:
        {

            if(!dupl)
            {
                auto a = std::find(VctSt[elem.i].begin(), VctSt[elem.i].end(), elem);
                if (a != VctSt[elem.i].end())
                {
                    if (a->F > elem.F)
                    {
                        VctSt[elem.i].erase(a);
                        size -= 1;
                    } else
                    {
                        return;
                    }
                }
            }
            if(VctSt[elem.i].insert(elem).second)
            {
                size += 1;
            }
            return;

        }
    }
}



Node OConteiner::GetOptimal()
{
   Node result;
    switch (type)
    {

        case 0:
        {

            double currFMin = DBL_MAX;
            double currG;
            for (int i = 0; i < VctLst.size(); i++)
            {
                if (VctLst[i].size() && currFMin >= VctLst[i].front().F)
                {
                    if (currFMin != VctLst[i].front().F || ((breakingties && VctLst[i].front().g > currG) || (!breakingties && VctLst[i].front().g < currG)))
                    {
                        vlminindex = i;
                        currFMin = VctLst[i].front().F;
                        currG = VctLst[i].front().g;
                    }

                }

            }


            result = VctLst[vlminindex].front();
            VctLst[vlminindex].pop_front();
            size -= 1;
            return result;
        }
        case 1:
        {
            result = Lst.front();
            Lst.pop_front();
            size -= 1;
            return result;

        }
        case 2:
        {
            auto a = St.begin();
            result = *a;
            St.erase(a);
            size -= 1;
            return result;

        }
        case 3:
        {
            auto a = Pq.top();
            result = a;
            Pq.pop();
            size -= 1;
            return result;
        }
        case 4:
        {
            double currFMin = DBL_MAX;
            double currG;
            for (int i = 0; i < VctPq.size(); i++)
            {
                if (VctPq[i].size() && currFMin >= VctPq[i].top().F)
                {
                    if (currFMin != VctPq[i].top().F || ((breakingties && VctPq[i].top().g > currG) || (!breakingties && VctPq[i].top().g < currG)))
                    {
                        vlminindex = i;
                        currFMin = VctPq[i].top().F;
                        currG = VctPq[i].top().g;
                    }

                }

            }
            result = VctPq[vlminindex].top();
            VctPq[vlminindex].pop();
            size -= 1;
            return result;
        }
        case 5:
        {
            double currFMin = DBL_MAX;
            double currG;
            for (int i = 0; i < VctSt.size(); i++)
            {
                if (VctSt[i].size() && currFMin >= VctSt[i].begin()->F)
                {
                    if (currFMin != VctSt[i].begin()->F || ((breakingties && VctSt[i].begin()->g > currG) || (!breakingties && VctSt[i].begin()->g < currG)))
                    {
                        vlminindex = i;
                        currFMin = VctSt[i].begin()->F;
                        currG = VctSt[i].begin()->g;
                    }

                }

            }
            auto a = VctSt[vlminindex].begin();
            result = *a;
            VctSt[vlminindex].erase(a);
            size -= 1;
            return result;
        }
    }
}

long int OConteiner::Size() const
{
    return size;
}
