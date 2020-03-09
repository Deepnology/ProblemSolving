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
    bool Exist_NonAxisAlignedRect_UseDiagonalIntersection(const std::vector<std::vector<int>> & points) //O(N^2) time
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
                    if (p.second[i].center[0] == p.second[j].center[0] && p.second[i].center[1] == p.second[j].center[1])
                        return true;
        }
        return false;
    }
};
/*
Leetcode: Minimum Area Rectangle
Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, with sides parallel to the x and y axes.
If there isn't any rectangle, return 0.
Example 1:
Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4
Example 2:
Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2

Leetcode: Minimum Area Rectangle II
Given a set of points in the xy-plane, determine the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the x and y axes.
If there isn't any rectangle, return 0.
Input: [[1,2],[2,1],[1,0],[0,1]]
Output: 2.00000
Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
Input: [[0,1],[2,1],[1,1],[1,0],[2,0]]
Output: 1.00000
Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0], with an area of 1.
Input: [[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
Output: 2.00000
Explanation: The minimum area rectangle occurs at [2,1],[2,3],[3,3],[3,1], with an area of 2.
 */
class Find4PointsFormRectangle_MinArea
{
public:
    Find4PointsFormRectangle_MinArea(){}
    ~Find4PointsFormRectangle_MinArea(){}

    //BruteForce: enumerate all possible 4 points, O(N^4) time
    int AxisAligned_xToYsHashMap(std::vector<std::vector<int>> && points) //O(N^2) time
    {
        int res = INT_MAX;
        std::unordered_map<int, std::set<int>> xToYs;
        for (auto & p : points)
            xToYs[p[0]].insert(p[1]);
        for (auto i = xToYs.begin(); i != xToYs.end(); ++i)
            for (auto j = std::next(i); j != xToYs.end(); ++j)
            {
                std::vector<int> commonY;//sorted in incr order
                auto p = i->second.begin();
                auto q = j->second.begin();
                while (p != i->second.end() && q != j->second.end())
                {
                    if (*p == *q)
                    {
                        commonY.push_back(*p);
                        ++p; ++q;
                    }
                    else if (*p < *q)
                        ++p;
                    else
                        ++q;
                }
                if (commonY.size() < 2) continue;
                int diffX = std::abs(i->first - j->first);
                int diffY = INT_MAX;
                int N = commonY.size();
                for (int k = 0; k+1 < N; ++k)
                    diffY = std::min(diffY, commonY[k+1]-commonY[k]);
                res = std::min(res, diffX * diffY);
            }
        res = res == INT_MAX ? 0 : res;
        std::cout << "Find4PointsFormRectangle_MinArea AxisAligned_xToYsHashMap for [" << Debug::ToStr1D<int>()(points) << "]: " << res << std::endl;
        return res;
    }
    int AxisAligned_CheckDiagonalPairs(std::vector<std::vector<int>> && points) //O(N^2) time
    {
        //use hashSet to store all points, then enumerate all pairs of points and
        //check if that pair satisfies diagonal property and if so,
        //check if the pair of points form the other diagonal exist in the hashSet, O(N^2) time
        int res = INT_MAX;
        std::unordered_set<int> ptSet;
        constexpr int LEN = 40001;
        for (auto & p : points)
            ptSet.insert(p[0]*LEN+p[1]);
        int N = points.size();
        for (int i = 0; i < N; ++i)
            for (int j = i+1; j < N; ++j)
                if (points[i][0] != points[j][0] && points[i][1] != points[j][1])
                    //x1 != x2 && y1 != y2, eliminate vertical line and horizontal line
                {
                    if (ptSet.count(points[i][0]*LEN+points[j][1]) && ptSet.count(points[j][0]*LEN+points[i][1]))
                        //check if both (x1,y2) and (x2,y1) exist
                    {
                        int diffX = std::abs(points[i][0]-points[j][0]);
                        int diffY = std::abs(points[i][1]-points[j][1]);
                        res = std::min(res, diffX * diffY);
                    }
                }
        res = res == INT_MAX ? 0 : res;
        std::cout << "Find4PointsFormRectangle_MinArea AxisAligned_CheckDiagonalPairs for [" << Debug::ToStr1D<int>()(points) << "]: " << res << std::endl;
        return res;
    }

    struct PointPairLine
    {
        PointPairLine(const std::vector<int> & a_, const std::vector<int> & b_):a(a_), b(b_), dist(Dist(a,b)), center(Center(a,b)){}
        std::vector<int> a;
        std::vector<int> b;
        double dist;
        std::vector<double> center;
        double Dist(const std::vector<int> & a, const std::vector<int> & b)
        {
            int deltaX = a[0]-b[0];
            int deltaY = a[1]-b[1];
            return std::sqrt(deltaX*deltaX + deltaY*deltaY);
        }
        std::vector<double> Center(const std::vector<int> & a, const std::vector<int> & b)
        {
            return {((double)a[0]+(double)b[0])/2.0, ((double)a[1]+(double)b[1])/2.0};
        }
        double RectArea(const std::vector<int> & otherPoint)
        {
            double len1 = Dist(a, otherPoint);
            double len2 = Dist(b, otherPoint);
            return len1*len2;
        }
    };
    double NonAxisAligned_CheckDiagonalPairs(std::vector<std::vector<int>> && points) //O(N^2) time
    {
        std::vector<PointPairLine> allPairs;
        int N = points.size();

        //enumerate all point pairs
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
            {
                allPairs.push_back(PointPairLine(points[i], points[j]));
            }

        std::unordered_map<double, std::vector<PointPairLine>> distToPairs;
        int M = allPairs.size();
        for (int i = 0; i < M; ++i)
            distToPairs[allPairs[i].dist].push_back(allPairs[i]);

        double minArea = std::numeric_limits<double>::max();
        //compare all pairs with same dists, if both dist and center are equal, we found a rectangle
        for (auto & p : distToPairs)
        {
            int L = p.second.size();
            for (int i = 0; i < L-1; ++i)
                for (int j = i+1; j < L; ++j)
                    if (p.second[i].center[0] == p.second[j].center[0] && p.second[i].center[1] == p.second[j].center[1])
                    {
                        double curArea = p.second[i].RectArea(p.second[j].a);
                        minArea = std::min(minArea, curArea);
                    }
        }
        minArea = minArea == std::numeric_limits<double>::max() ? 0 : minArea;
        std::cout << "Find4PointsFormRectangle_MinArea NonAxisAligned_CheckDiagonalPairs for [" << Debug::ToStr1D<int>()(points) << "]: " << minArea << std::endl;
        return minArea;
    }
};
/*
Find4PointsFormRectangle_MinArea AxisAligned_xToYsHashMap for [[1,1], [1,3], [3,1], [3,3], [4,1], [4,3]]: 2
Find4PointsFormRectangle_MinArea AxisAligned_CheckDiagonalPairs for [[1,1], [1,3], [3,1], [3,3], [4,1], [4,3]]: 2
Find4PointsFormRectangle_MinArea NonAxisAligned_CheckDiagonalPairs for [[1,2], [2,1], [1,0], [0,1]]: 2
 */
#endif
