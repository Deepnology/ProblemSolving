#ifndef _TWO_SUM_LESS_EQUAL_CLOSEST_K_H
#define _TWO_SUM_LESS_EQUAL_CLOSEST_K_H
#include "Debug.h"
/*
Leetcode: Two Sum Less Than K
Given an array A of integers and integer K, return the maximum S such that there exists i < j with A[i] + A[j] = S and S < K.
If no i, j exist satisfying this equation, return -1.
Example 1:
Input: A = [34,23,1,24,75,33,54,8], K = 60
Output: 58
Explanation:
We can use 34 and 24 to sum 58 which is less than 60.
Example 2:
Input: A = [10,20,30], K = 15
Output: -1
Explanation:
In this case it's not possible to get a pair sum less that 15.
 */
class TwoSumLessEqualClosestK
{
public:
    TwoSumLessEqualClosestK(){}
    int Sort(std::vector<int> && A, int K)
    {
        std::sort(A.begin(), A.end());
        int N = A.size();
        int left = 0;
        int right = N-1;
        int res = INT_MIN;
        while (left < right)
        {
            int sum = A[left] + A[right];
            if (sum < K)
            {
                res = std::max(res, sum);
                ++left;
            }
            else
                --right;
        }
        res = res == INT_MIN ? -1 : res;

        std::cout << "TwoSumLessEqualClosestK for " << K << " from [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
};
/*
TwoSumLessEqualClosestK for 60 from [1, 8, 23, 24, 33, 34, 54, 75]: 58
 */
/*
Amazon OA
Your task is to write an algorithm to optimize the sets of forward/return shipping route pairs that allow the aircraft to be optimally utilized, given a list a of forward routes and a list of return shipping routes.
INPUT
The input to the function/method consisits of three arguments:
maxTravelDist, an integer representing the maximum operating travel distance of the given aircraft;
forwardRouteList, a list of pairs of integers where the first integer represents the unique identifier of a forward shipping
route and the second integer represents the amount of travel distance required bu this shipping route;
returnRouteList, a list of pairs of integers where the first integer represents the unique identifer of a return shipping route
and the second integer represents the amount of travel distance required by this shipping route.
OUTPUT
Return a list of pairs of integers representing the pairs of IDs of forward and return shipping routes that optimally utilize the given aircraft. If no route is possible, return a list with empty pair.
Example 1:
Input:
maxTravelDist = 7000
forwardRouteList = [[1,2000],[2,4000],[3,6000]]
returnRouteList = [[1,2000]]
Output:
[[2,1]]
Explanation:
There are only three combinations [1,1],[2,1],and [3,1], which have a total of 4000, 6000, and 8000 miles, respectively. Since 6000 is the largest use that does tnot exceed 7000, [2,1] is the optimal pair.
Example 2:
Input:
maxTravelDist = 10,000
forwardRouteList = [[1,3000],[2,5000],[3,7000],[4,10000]]
returnRouteList = [[1,2000],[2,3000],[3,4000],[4,5000]]
Output:
[[2,4],[3,2]]
Explanation:
There are two pairs of forward and return shipping routes possible that optimally utilizes the given aircraft. Shipping Route ID#2 from the forwardShippingRouteList, required 5000 miles travelled, and Shipping Route ID#4 from returnShippingRouteList also required 5000 miles travelled. Combined, they add up to 10000 miles travelled. Similarily, Shipping Route ID#3 from forwardShippingRouteList requires 7000 miles travelled, and Shippping Route ID#2 from returnShippingRouteList requires 3000 miles travelled. These also add up to 10000 miles travelled. Therefore, the pairs of forward and return shipping routes that optimally utilize the aircraft are [2,4] and [3,2].
 */
class TwoSumLessEqualClosestKFrom2Arr
{
public:
    TwoSumLessEqualClosestKFrom2Arr(){}

    std::vector<std::vector<int>> FindAll(int maxTravelDist, std::vector<std::vector<int>> && Forward, std::vector<std::vector<int>> && Return) //O(N*logN+M*logN) time
    {
        std::sort(Return.begin(), Return.end(), [](const std::vector<int> & a, const std::vector<int> & b)
        {
            return a[1] < b[1];
        });

        std::unordered_map<int, std::vector<std::vector<int>>> distToPairs;
        int maxDist = INT_MIN;
        for (auto & p : Forward)
        {
            if (p[1] >= maxTravelDist) continue;
            auto itr = std::upper_bound(Return.begin(), Return.end(), maxTravelDist-p[1],
                    [](const int & b, const std::vector<int> & a)
                    {
                        return a[1] > b;
                        //find the first element in range such that it is greater than target
                    });
            if (itr != Return.begin())
            {
                --itr;
                int rDist = itr->operator[](1);
                int sum = p[1] + rDist;
                auto beginItr = std::lower_bound(Return.begin(), Return.end(), rDist,
                        [](const std::vector<int> & a, const int & b)
                        {
                            return a[1] < b;
                            //find the first element in range such that it is greater equal to target
                        });
                ++itr;
                while (beginItr != itr) //collect all pairs with equal sum
                {
                    distToPairs[sum].push_back({p[0], beginItr->operator[](0)});
                    ++beginItr;
                }
                maxDist = std::max(maxDist, sum);
            }
        }

        std::vector<std::vector<int>> res = distToPairs[maxDist];
        std::cout << "TwoSumLessEqualClosestKFrom2Arr FindAll for " << maxTravelDist << " from [" << Debug::ToStr1D<int>()(Forward) << "], [" << Debug::ToStr1D<int>()(Return) << "]: " << Debug::ToStr1D<int>()(res) << ", maxDist=" << maxDist << std::endl;
        return res;
    }
};
/*
[1,3000],[4,5000]:8000
[2,5000],[4,5000]:10000
[3,7000],[2,3000]:10000
TwoSumLessEqualClosestKFrom2Arr FindAll for 10000 from [[1,3000], [2,5000], [3,7000], [4,10000]], [[1,2000], [2,3000], [3,4000], [4,5000]]: [2,4], [3,2], maxDist=10000
[1,2000],[1,2000]:4000
[2,4000],[1,2000]:6000
TwoSumLessEqualClosestKFrom2Arr FindAll for 7000 from [[1,2000], [2,4000], [3,6000]], [[1,2000]]: [2,1], maxDist=6000
 */
#endif
