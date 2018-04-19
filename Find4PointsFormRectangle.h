/*Facebook*/
#ifndef _FIND_4_POINTS_FORM_RECTANGLE_H
#define _FIND_4_POINTS_FORM_RECTANGLE_H
#include "Debug.h"
/*
https://www.quora.com/From-a-given-set-of-points-how-would-you-find-the-set-of-4-points-forming-a-rectangle
 */
class Find4PointsFormRectangle
{
public:
    Find4PointsFormRectangle(){}

    bool Exist_AxisAlignedRect_HashMap(const std::vector<std::vector<int>> & points)//<x,y>, O(N^2) time
    {
        std::unordered_map<int, std::multiset<int>> xToYs;
        for (auto & p : points)
            xToYs[p[0]].insert(p[1]);
        for (auto i = xToYs.begin(); i != xToYs.end(); ++i)
            for (auto j = std::next(i); j != xToYs.end(); ++j)
            {
                //check if there are 2 pairs of same values from i->second and j->second
                int count = 0;
                auto p = i->second.begin();
                auto q = j->second.begin();
                while (p != i->second.end() && q != j->second.end())
                {
                    if (*p == *q)
                    {
                        ++p; ++q;
                        ++count;
                        if (count == 2) return true;
                    }
                    else if (*p < *q)
                        ++p;
                    else
                        ++q;
                }
            }
        return false;
    }

    bool Exit_NonAxisAlignedRect_BruteForce(const std::vector<std::vector<int>> & points)//O(N^4) time
    {
        int N = points.size();
        for (int i = 0; i < N; ++i)
        {
            for (int j = i + 1; j < N; ++j)
            {
                for (int k = j + 1; k < N; ++k)
                {
                    for (int l = k + 1; l < N; ++l)
                    {
                        //enumerate all 4 points, then enumerate all pair length of the 4 points (6 lengths)
                        //3 cases:
                        //1). all 6 lengths are the same
                        //2). 4 lengths are the same, 2 lenths are the same
                        //3). 2 lengths are the same, 2 lengths are the same, 2 lengths are the same
                        return true;
                    }
                }
            }
        }
        return false;
    }

    struct PointPairLine
    {
        PointPairLine(double d, const std::vector<int> & c):dist(d), center(c){}
        double dist;
        std::vector<int> center;
    };
    bool Exist_NonAxisAlignedRect_UseDiagonalIntersection(const std::vector<std::vector<int>> & points) //O(N^2) time avg, O(N^4) time worst case
    {
        std::vector<PointPairLine> allPairs;
        int N = points.size();

        //enumerate all point pairs
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
            {
                double dist = (points[i][0]-points[j][0])*(points[i][0]-points[j][0]) + (points[i][1]-points[j][1])*(points[i][1]-points[j][1]);
                std::vector<int> center({(points[i][0]+points[j][0])/2, (points[i][1]+points[j][1])/2});
                allPairs.push_back(PointPairLine(dist, center));
            }

        std::unordered_map<double, std::vector<PointPairLine>> distToPairs;
        int M = allPairs.size();
        for (int i = 0; i < M; ++i)
            distToPairs[allPairs[i].dist].push_back(allPairs[i]);

        //compare all pairs with same dists, if both dist and center are equal, we found a rectangle
        for (auto & p : distToPairs)
        {
            int L = p.second.size();
            for (int i = 0; i < L-1; ++i)
                for (int j = i+1; j < L; ++j)
                    if (p.second[i].center[0] == p.second[j].center[1] && p.second[i].center[1] == p.second[j].center[1])
                        return true;
        }
        return false;
    }
};
#endif
