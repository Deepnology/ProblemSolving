#ifndef _MINIMIZE_MAX_DIST_TO_GAS_STATION_H
#define _MINIMIZE_MAX_DIST_TO_GAS_STATION_H
#include "Debug.h"
/*
Leetcode: Minimize max distance to gas station
On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.
Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.
Return the smallest possible value of D.
Example:
Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
 */
class MinimizeMaxDistToGasStation
{
public:
    MinimizeMaxDistToGasStation(){}

    struct Interval
    {
        int left;
        int right;
        int numInsertions;

        Interval(int l, int r, int ins):left(l), right(r), numInsertions(ins)
        {}
        double distance() const
        {
            return double(right - left) / double(numInsertions + 1);
        }
        bool operator<(const Interval & rhs) const
        {
            return distance() < rhs.distance();
        }
    };

    double MaxHeapGreedyAssign(std::vector<int> && stations, int K)
    {
        std::sort(stations.begin(), stations.end());
        std::priority_queue<Interval> maxHeap;
        int N = stations.size();
        int totalDist = stations[N-1] - stations[0];
        int remaining = K;
        for (int i = 0; i < N-1; ++i)
        {
            int numInsertions = K * (double(stations[i+1]-stations[i]) / double(totalDist));
            maxHeap.push({stations[i],stations[i+1],numInsertions});
            remaining -= numInsertions;
        }
        while (remaining-- > 0)
        {
            Interval cur = maxHeap.top();
            maxHeap.pop();
            ++cur.numInsertions;
            maxHeap.push(cur);
        }

        std::cout << "MinimizeMaxDistToGasStation MaxHeapGreedyAssign for " << K << " in [" << Debug::ToStr1D<int>()(stations) << "]: " << maxHeap.top().distance() << std::endl;
        return maxHeap.top().distance();
    }

    double BinarySearch(std::vector<int> && stations, int K)
    {
        std::sort(stations.begin(), stations.end());
        int N = stations.size();
        double left = 0;//min dist
        double right = stations.back() - stations.front();//max dist
        while (right - left >= 1e-6)
        {
            double mid = (left + right) / 2;
            int numInsertions = 0;
            for (int i = 0; i < N-1; ++i)
                numInsertions += ceil(double(stations[i+1]-stations[i])/mid) - 1;
            if (numInsertions <= K)//mid dist is too large
                right = mid;
            else
                left = mid;
        }

        std::cout << "MinimizeMaxDistToGasStation BinarySearch for " << K << " in [" << Debug::ToStr1D<int>()(stations) << "]: " << left << std::endl;
        return left;
    }
};
/*
MinimizeMaxDistToGasStation MaxHeapGreedyAssign for 9 in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]: 0.5
MinimizeMaxDistToGasStation BinarySearch for 9 in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]: 0.5
 */
#endif
