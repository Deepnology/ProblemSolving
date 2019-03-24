#ifndef _MIN_COST_HIRE_K_WORKERS_H
#define _MIN_COST_HIRE_K_WORKERS_H
#include "Debug.h"
/*
Leetcode: Minimum Cost To Hire K Workers
There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].
Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:
Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum wage expectation.
Return the least amount of money needed to form a paid group satisfying the above conditions.
Example 1:
Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
Example 2:
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.
 */
class MinCostHireKWorkers
{
public:
    MinCostHireKWorkers(){}
    ~MinCostHireKWorkers(){}

    //brute force: enumerate all possible combinations of K workers, O(N!) time

    double SortAndMaxHeap(std::vector<int> && quality, std::vector<int> && wage, int K)//sort and maxHeap: O(NlogN) time
    {
        int N = quality.size();
        std::vector<std::pair<double, int>> rateQual;//<rate,quality>
        for (int i = 0; i < N; ++i)
            rateQual.push_back({(double)wage[i]/(double)quality[i], quality[i]});
        std::sort(rateQual.begin(), rateQual.end(), [](const auto & p1, const auto & p2) ->bool const
        {
            return p1.first < p2.first;
        });//sort by wage/quality rate in incr order (lowest wage per unit quality first): O(NlogN) time
        std::priority_queue<int, std::vector<int>, std::less<int>> qualMaxHeap;
        double sumWage;
        int sumQuality = 0;
        for (int i = 0; i < N; ++i)//O(NlogK) time
        {
            qualMaxHeap.push(rateQual[i].second);
            sumQuality += rateQual[i].second;

            if (qualMaxHeap.size() == K) //first K lowest rates
                sumWage = rateQual[i].first * (double)sumQuality; //use the highest rate to pay all K workers
            else if (qualMaxHeap.size() > K) //try to accommodate worker w/ higher rate and lower quality
            {
                sumQuality -= qualMaxHeap.top(); //kick out worker w/ lower rate and highest quality
                qualMaxHeap.pop();
                sumWage = std::min(sumWage, rateQual[i].first * (double)sumQuality);
            }
        }
        std::cout << "MinCostHireKWorkers SortAndMaxHeap for quality=[" << Debug::ToStr1D<int>()(quality) << "], wage=[" << Debug::ToStr1D<int>()(wage) << "], K=" << K << ": " << sumWage << std::endl;
        return sumWage;
    }
};
/*
MinCostHireKWorkers SortAndMaxHeap for quality=[10, 20, 5], wage=[70, 50, 30], K=2: 105
 */
#endif
