#ifndef _MIN_COST_SCHEDULE_HALF_HALF_TO_2_CITIES_H
#define _MIN_COST_SCHEDULE_HALF_HALF_TO_2_CITIES_H
#include "Debug.h"
/*
Leetcode: Two Cities Scheduling
There are 2N people a company is planning to interview.
The cost of flying the i-th person to city A is costs[i][0], and the cost of flying the i-th person to city B is costs[i][1].
Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.
Example 1:
Input: [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation:
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.
The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
Note:
1 <= costs.length <= 100
It is guaranteed that costs.length is even.
1 <= costs[i][0], costs[i][1] <= 1000
 */
class MinCostScheduleHalfHalfTo2Cities
{
public:
    int SortBySavings(std::vector<std::vector<int>> && costs)
    {
        /*
        std::sort(costs.begin(), costs.end(),
                  [](const std::vector<int> & a, const std::vector<int> & b)
                  {
                      return (a[0]-a[1]) < (b[0]-b[1]);
                  });
        */
        int N = costs.size();
        std::nth_element(costs.begin(), costs.begin() + N/2, costs.end(),
                         [](const std::vector<int> & a, const std::vector<int> & b)
                         {
                             return (a[0]-a[1]) < (b[0]-b[1]);
                         });
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            if (i < N/2)
                res += costs[i][0];
            else
                res += costs[i][1];
        }

        std::cout << "MinCostScheduleHalfHalfTo2Cities SortBySavings for [" << Debug::ToStr1D<int>()(costs) << "]: " << res << std::endl;
        return res;
    }
};
/*
 MinCostScheduleHalfHalfTo2Cities SortBySavings for [[30,200], [10,20], [30,20], [400,50]]: 110
 */
#endif
