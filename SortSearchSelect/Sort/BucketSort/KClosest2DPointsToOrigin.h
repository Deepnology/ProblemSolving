#ifndef _K_CLOSEST_2D_POINTS_TO_ORIGIN_H
#define _K_CLOSEST_2D_POINTS_TO_ORIGIN_H
#include "Debug.h"
/*
Leetcode: K Closest Points to Origin
We have a list of points on the plane.  Find the K closest points to the origin (0, 0).
(Here, the distance between two points on a plane is the Euclidean distance.)
You may return the answer in any order.
The answer is guaranteed to be unique (except for the order that it is in.)
Example 1:
Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)
 */
class KClosest2DPointsToOrigin
{
public:
    KClosest2DPointsToOrigin(){}
    ~KClosest2DPointsToOrigin(){}
private:
    struct Less
    {
        double dist(const std::vector<int> & a, const std::vector<int> & b) const
        {
            double deltaX = a[0]-b[0];
            double deltaY = a[1]-b[1];
            return sqrt(deltaX*deltaX + deltaY*deltaY);
        }
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            return dist(a,{0,0}) < dist(b,{0,0});
        }
    };
    double dist(const std::vector<int> & a, const std::vector<int> & b) const
    {
        double deltaX = a[0]-b[0];
        double deltaY = a[1]-b[1];
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }
    int SmallerThanPivot(std::vector<std::vector<int>> & points, int first, int last, int pivot)
    {
        auto pivotVal = points[pivot];
        std::swap(points[pivot], points[last]);
        int i = first; int j = last;
        while (i <= j)
        {
            if (dist(points[i],{0,0}) < dist(pivotVal,{0,0}))
                ++i;
            else if (dist(points[j],{0,0}) >= dist(pivotVal,{0,0}))
                --j;
            else
                std::swap(points[i++], points[j--]);
        }
        std::swap(points[i], points[last]);
        return i;
    }
public:
    //1. sort: O(NlogN) time
    //2. maxHeap: O(NlogK) time
    std::vector<std::vector<int>> UseMaxHeap(std::vector<std::vector<int>> && points, int K)
    {
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Less> maxHeap;
        std::vector<std::vector<int>> res;
        for (auto & p : points)
        {
            maxHeap.push(p);
            if (maxHeap.size() > K)
                maxHeap.pop();
        }
        while (!maxHeap.empty())
            res.push_back(maxHeap.top()), maxHeap.pop();
        return res;
    }
    //3. quick select: O(N) time in avg, O(N^2) time in worst case
    std::vector<std::vector<int>> UseQuickSelect(std::vector<std::vector<int>> && points, int K)
    {
        int N = points.size(); int K2 = K;
        int left = 0; int right = N-1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            int pivot = SmallerThanPivot(points, left, right, mid);
            if (K < pivot - left + 1)
                right = pivot - 1;
            else if (K > pivot - left + 1)
            {
                K -= (pivot - left + 1);
                left = pivot + 1;
            }
            else
                break;
        }
        std::vector<std::vector<int>> res;
        for (int i = 0; i < K2; ++i)
            res.push_back(points[i]);
        return res;
    }
    //4. bucket sort, map<dist,list of points>: O(N) time
    std::vector<std::vector<int>> UseBucketSort(std::vector<std::vector<int>> && points, int K)
    {
        std::map<double, std::vector<std::vector<int>>> map;
        int N = points.size();
        for (int i = 0; i < N; ++i)
        {
            map[dist(points[i],{0,0})].push_back(points[i]);
        }
        std::vector<std::vector<int>> res;
        for (auto itr = map.begin(); itr != map.end() && res.size() < K; ++itr)
            for (auto itr2 = itr->second.begin(); itr2 != itr->second.end() && res.size() < K; ++itr2)
                res.push_back(*itr2);
        return res;
    }

    std::vector<std::vector<int>> Test(std::vector<std::vector<int>> && points, int K)
    {
        std::vector<std::vector<int>> res1 = UseMaxHeap(std::vector<std::vector<int>>(points), K);
        std::vector<std::vector<int>> res2 = UseQuickSelect(std::vector<std::vector<int>>(points), K);
        std::vector<std::vector<int>> res3 = UseBucketSort(std::vector<std::vector<int>>(points), K);
        std::cout << "KClosest2DPointsToOrigin for [" << Debug::ToStr1D<int>()(points) << "], k=" << K << ": MaxHeap, QuickSelect, BucketSort" << std::endl;
        std::cout << Debug::ToStr1D<int>()(res1) << std::endl;
        std::cout << Debug::ToStr1D<int>()(res2) << std::endl;
        std::cout << Debug::ToStr1D<int>()(res3) << std::endl;
        return res1;
    }
};
/*
KClosest2DPointsToOrigin for [[3,3], [5,-1], [-2,4]], k=2: MaxHeap, QuickSelect, BucketSort
[-2,4], [3,3]
[3,3], [-2,4]
[3,3], [-2,4]
 */
#endif
