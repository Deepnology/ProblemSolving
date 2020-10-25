#ifndef _LARGEST_ITEM_ASSOCIATION_H
#define _LARGEST_ITEM_ASSOCIATION_H
#include "Debug.h"
/*
Amazon OA
Given a list of item (string) pairs, find the largest item (string) association and sort it lexicographically.
 */
class LargestItemAssociation
{
public:
    std::vector<std::string> UseUnionFind(const std::vector<std::vector<std::string>> & pairs)
    {
        std::unordered_map<std::string, std::string> chdToP;
        std::unordered_map<std::string, std::unordered_set<std::string>> rootToChds;

        //init: O(N) time
        for (auto & p : pairs)
        {
            chdToP[p[0]] = p[0];
            chdToP[p[1]] = p[1];
        }
        //UnionFind: O(NlogN) time
        for (auto & p : pairs)
        {
            std::string root1 = Find(chdToP, p[0]);
            std::string root2 = Find(chdToP, p[1]);
            if (root1 != root2)
                chdToP[root2] = root1;
        }
        //Merge: O(NlogN) time
        for (auto & p : chdToP)
            rootToChds[Find(chdToP, p.second)].insert(p.first);

        std::string maxRoot;
        int maxCount = 0;
        for (auto & p : rootToChds)
        {
            if (p.second.size() > maxCount)
            {
                maxCount = p.second.size();
                maxRoot = p.first;
            }
        }
        std::vector<std::string> res;
        for (auto & s : rootToChds[maxRoot])
            res.push_back(s);
        std::sort(res.begin(), res.end());

        std::cout << "LargestItemAssociation for [" << Debug::ToStr1D<std::string>()(pairs) << "]: " << Debug::ToStr1D<std::string>()(res) << std::endl;
        return res;
    }
    std::string Find(std::unordered_map<std::string,std::string> & chdToP, const std::string & s)
    {
        std::string cur = s;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
LargestItemAssociation for [[item1,item2], [item3,item4], [item4,item5]]: item3, item4, item5
 */
#endif
