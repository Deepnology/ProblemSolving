#ifndef _ORTHOGONAL_RECTANGLE_INTERSECTION_2_H
#define _ORTHOGONAL_RECTANGLE_INTERSECTION_2_H
#include "Debug.h"
/*
Leetcode: Rectangle Area II
We are given a list of (axis-aligned) rectangles.
Each rectangle[i] = [x1, y1, x2, y2] , where (x1, y1) are the coordinates of the bottom-left corner
, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.
Find the total area covered by all rectangles in the plane.
Since the answer may be too large, return it modulo 10^9 + 7.
Example 1:
Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: As illustrated in the picture.
Example 2:
Input: [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.
 */
class OrthogonalRectangleIntersection2
{
public:
    OrthogonalRectangleIntersection2(){}
    ~OrthogonalRectangleIntersection2(){}
    bool valid(const std::vector<std::vector<int>> & rects, int left, int right, int bottom, int top)
    {
        for (auto & rect : rects)
            if (rect[0] <= left && right <= rect[2] && rect[1] <= bottom && top <= rect[3])
                //rectangle [left,right,bottom,top] is covered by rect
                return true;
        return false;
    }
    int BruteForce(std::vector<std::vector<int>> && rects)
    {
        //brute force: sum up all small areas that are within any given rectangle O(N^3) time
        std::vector<int> Xs;
        std::vector<int> Ys;
        for (auto & rect : rects)
        {
            Xs.push_back(rect[0]);
            Xs.push_back(rect[2]);
            Ys.push_back(rect[1]);
            Ys.push_back(rect[3]);
        }
        std::sort(Xs.begin(), Xs.end());
        std::sort(Ys.begin(), Ys.end());
        long res = 0;
        for (int i = 0; i < Xs.size()-1; ++i)
            for (int j = 0; j < Ys.size()-1; ++j)
            {
                int left = Xs[i];
                int right = Xs[i+1];
                int bottom = Ys[j];
                int top = Ys[j+1];
                if (valid(rects, left, right, bottom, top))
                    res += (long)(right-left) * (long)(top-bottom);
                res %= 1000000007;
            }

        std::cout << "OrthogonalRectangleIntersection2 BruteForce for [" << Debug::ToStr1D<int>()(rects) << "]: " << res << std::endl;
        return res;
    }
    int SweepLine(std::vector<std::vector<int>> && rects)
    {
        //sweep line: O(N^2logN) time
        std::vector<std::vector<int>> yToXItvls;//<y,bottomORtop,xLeft,xRight> where y is sorted in incr order
        for (auto & v : rects)
        {
            yToXItvls.push_back({v[1],0,v[0],v[2]});
            yToXItvls.push_back({v[3],1,v[0],v[2]});
        }
        std::sort(yToXItvls.begin(), yToXItvls.end(),[](auto & v1, auto & v2)->bool const
        {
            return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1];
        });

        long res = 0;
        int preY = yToXItvls[0][0];
        std::vector<std::vector<int>> curXItvls;//<xLeft,xRight> where xLeft is sorted in incr order
        for (auto & v : yToXItvls)
        {
            //compute the length of all x intervals after merge (but without merge)
            long lenX = 0;
            int curX = INT_MIN;
            for (auto & itvl : curXItvls)
            {
                curX = std::max(curX, itvl[0]);
                lenX += std::max(itvl[1]-curX, 0);
                curX = std::max(curX, itvl[1]);
            }

            res += lenX * (v[0] - preY);
            res %= 1000000007;

            if (v[1] == 0)//yBottom: insert a new x interval (v[2],v[3])
            {
                auto lb = std::lower_bound(curXItvls.begin(), curXItvls.end(), v[2],
                                           [](auto & itvlVec, int xLeft)->bool const
                                           {
                                               return itvlVec[0] < xLeft;
                                           });
                curXItvls.insert(lb, {v[2],v[3]});
            }
            else//yTop: remove an old x interval (v[2],v[3])
            {
                auto lb = std::lower_bound(curXItvls.begin(), curXItvls.end(), v[2],
                                           [](auto & itvlVec, int xLeft)->bool const
                                           {
                                               return itvlVec[0] < xLeft;
                                           });
                curXItvls.erase(lb);
            }

            preY = v[0];
        }

        std::cout << "OrthogonalRectangleIntersection2 SweepLine for [" << Debug::ToStr1D<int>()(rects) << "]: " << res << std::endl;
        return res;
    }
};
/*
OrthogonalRectangleIntersection2 BruteForce for [[0,0,2,2], [1,0,2,3], [1,0,3,1]]: 6
OrthogonalRectangleIntersection2 SweepLine for [[0,0,2,2], [1,0,2,3], [1,0,3,1]]: 6
 */
#endif
