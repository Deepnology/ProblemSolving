#ifndef _MAX_PROFIT_ASSIGN_WORK_H
#define _MAX_PROFIT_ASSIGN_WORK_H
#include "Debug.h"
/*
leetcode: Most Profit Assigning Work
We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job.
Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i].
Every worker can be assigned at most one job, but one job can be completed multiple times.
For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.
If a worker cannot complete any job, his profit is $0.
What is the most profit we can make?
Example 1:
Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.
 */
class MaxProfitAssignWork
{
public:
    MaxProfitAssignWork(){}
    ~MaxProfitAssignWork(){}

    int SortplusTwoPtrs(std::vector<int> && difficulty, std::vector<int> && profit, std::vector<int> && worker)
    {
        //O(NlogN + MlogM) time
        std::vector<std::pair<int,int>> diffProf;
        int N = difficulty.size();
        for (int i = 0; i < N; ++i)
            diffProf.push_back({difficulty[i],profit[i]});
        std::sort(diffProf.begin(), diffProf.end());
        std::sort(worker.begin(), worker.end());
        int maxProf = 0;
        int totalProf = 0;
        int i = 0;
        for (auto & w : worker)
        {
            while (i < N && w >= diffProf[i].first)
            {
                maxProf = std::max(maxProf, diffProf[i].second);
                ++i;
            }
            totalProf += maxProf;
        }
        std::cout << "MaxProfitAssignWork for difficulty=[" << Debug::ToStr1D<int>()(difficulty) << "], profit=[" << Debug::ToStr1D<int>()(profit) << "], worker=[" << Debug::ToStr1D<int>()(worker) << "]: " << totalProf << std::endl;
        return totalProf;
    }
};
/*
MaxProfitAssignWork for difficulty=[2, 4, 6, 8, 10], profit=[10, 20, 30, 40, 50], worker=[4, 5, 6, 7]: 100
 */
#endif
