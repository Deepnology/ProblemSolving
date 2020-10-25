#ifndef _COMPUTE_TIMESTAMP_CUSTOMER_PASS_TURNSTILE_H
#define _COMPUTE_TIMESTAMP_CUSTOMER_PASS_TURNSTILE_H
#include "Debug.h"
/*
Amazon OA
Imagine a small Amazon Go store that has exactly one turnstile.
It can be used by customers either as an entrance or an exit.
Sometimes multiple customers want to pass through the turnstile and their directions can be different.
The ith customer comes to the turnstile at time[i] and wants to either exit the store if direction [i] = 1 or enter the store if direction[i] = 0.
Customers form 2 queues, one to exit and one to enter. They are ordered by the time when they came to the turnstile and, if the times are equal, by their indices.
If one customer wants to enter the store and another customer wants to exit at the same moment, there are three cases:
If in the previous second the turnstile was not used (maybe it was used before, but not at the previous second), then the customer who wants to exit goes first.
If in the previous second the turnstile was used as an exit, then the customer who wants to leave goes first.
If in the previous second the turnstile was used as an entrance, then the customer who wants to enter goes first.
Passing through the turnstile takes 1 second.
Write an algorithm to find the time for each customer when they will pass through the turnstile.
Input
The function/method consists of three arguments:
numcustomers, an integer representing the number of customers (n);
arrTime, a list of integers where the value at indexi is the time in seconds when the ith customer will come to the turnstile;
direction, a list of integers where the value at indexi is the direction of the ith customer.
Output
Return a list of integers where the value at index i is the time when the ith customer will pass the turnstile.
Constraints
1 <= numCustomers <= 10^5
0 <= arrTime[i] <= arrTime[i + 1] <= 10^9
0 <= i <= numCustomers - 2
0 <= direction[i] <= 1
0 <= j <= numCustomers - 1
Examples
Example 1:
Input:
numCustomers = 4
arrTime = [0, 0, 1,5]
direction = [0, 1, 1, 0]
Output:
[2,0,1,5]
Explanation:
At time 0, customer 0 and 1 want to pass through the turnstile. Customer 0 wants to enter the store and customer 1 wants to leave the store. The turnstile was not used in the previous second, so the priority is on the side of the customer 1
At time 1, customers 0 and 2 want to pass through the turnstile. Customer 2 wants to leave the store and at the previous second the turnstile was used as an exit, so the customer 2 passes through the turnstile.
At time 2, customer 0 passes through the turnstile.
At time 5, customer 3 passes through the turnstile.
Example 2
Input:
numCustomers = 5
arrTime = [0,1,1,3,3]
direction = [0, 1, 0, 0, 1]
Output: [0, 2, 1, 4, 3]
Explanation:
At time 0, customer 0 passes through the turnstile (enters).
At time 1, customers 1 (exit) and 2 (enter) want to pass through the turnstile, and customer 2 passes through the turnstile because their direction is equal to the direction at the previous second.
At time 2. customer 1 passes through the turnstile (exit).
At time 3, customers 3 (enter) and 4 (exit) want to pass through the turnstile. Customer 4 passes through the turnstile because at the previous second the turnstile was used to exit.
At time 4, customer 3 passes through the turnstile.
 */
class ComputeTimestampCustomerPassTurnstile
{
public:
    std::vector<int> Solve(const std::vector<int> & arrTime, const std::vector<int> & dir)
    {
        int N = arrTime.size();
        std::queue<std::vector<int>> queEnter;
        std::queue<std::vector<int>> queExit;
        for (int i = 0; i < N; ++i)
            if (dir[i] == 0)
                queEnter.push({arrTime[i],i});
            else
                queExit.push({arrTime[i],i});
        std::vector<int> res(N, -1);
        int preTime = -1;
        int preDir = 1;//0: enter, 1: exit
        while (!queEnter.empty() || !queExit.empty())
        {
            //now: curTime = preTime+1
            if (!queExit.empty() &&
            (queEnter.empty() ||
            !((queEnter.front()[0]<=preTime+1)&&!preDir) &&
            ((queExit.front()[0]<=preTime+1)&&preDir || (preTime+1<std::min(queExit.front()[0], queEnter.front()[0])) || (queExit.front()[0]<queEnter.front()[0]) || (queExit.front()[1]<queEnter.front()[1]))) )
            {
                auto v = queExit.front();
                queExit.pop();
                int curTime = std::max(preTime+1, v[0]);
                res[v[1]] = curTime;
                preTime = curTime;
                preDir = 1;
            }
            else
            {
                auto v = queEnter.front();
                queEnter.pop();
                int curTime = std::max(preTime+1, v[0]);
                res[v[1]] = curTime;
                preTime = curTime;
                preDir = 0;
            }
        }

        std::cout << "ComputeTimestampCustomerPassTurnstile for arrTime=[" << Debug::ToStr1D<int>()(arrTime) << "], dir=[" << Debug::ToStr1D<int>()(dir) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }



    //O(NlogT) time, where N=numCustomers, T=numDistinctTimestamps
    std::vector<int> Solve_Incorrect(const std::vector<int> & arrTime, const std::vector<int> & dir)
    {
        int numCustomers = arrTime.size();
        std::map<int, std::vector<std::vector<int>>> timeMap;//<time, <idx, dir>>
        for (int i = 0; i < numCustomers; ++i)
            timeMap[arrTime[i]].push_back({i, dir[i]});

        int curTime = arrTime[0];
        int preDir = -1;//-1: not used, 0: enter, 1: exit
        std::vector<int> res(numCustomers, -1);
        for (auto & itr : timeMap)
        {
            if (itr.first - curTime > 1)
                preDir = -1;
            curTime = std::max(curTime, itr.first);
            std::queue<int> queEnter;
            std::queue<int> queExit;
            for (auto & v : itr.second)
            {
                if (v[1] == 0)
                    queEnter.push(v[0]);
                else
                    queExit.push(v[0]);
            }
            while (!queEnter.empty() && !queExit.empty())
            {
                if (preDir)//choose exit
                {
                    auto idx = queExit.front();
                    queExit.pop();
                    res[idx] = curTime++;
                    preDir = 1;
                }
                else
                {
                    auto idx = queEnter.front();
                    queEnter.pop();
                    res[idx] = curTime++;
                    preDir = 0;
                }
            }
            while (!queEnter.empty())
            {
                auto idx = queEnter.front();
                queEnter.pop();
                res[idx] = curTime++;
                preDir = 0;
            }
            while (!queExit.empty())
            {
                auto idx = queExit.front();
                queExit.pop();
                res[idx] = curTime++;
                preDir = 1;
            }
        }

        std::cout << "ComputeTimestampCustomerPassTurnstile for arrTime=[" << Debug::ToStr1D<int>()(arrTime) << "], dir=[" << Debug::ToStr1D<int>()(dir) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
ComputeTimestampCustomerPassTurnstile for arrTime=[0, 0, 1, 5], dir=[0, 1, 1, 0]: 2, 0, 1, 5
ComputeTimestampCustomerPassTurnstile for arrTime=[0, 1, 1, 3, 3], dir=[0, 1, 0, 0, 1]: 0, 2, 1, 4, 3
ComputeTimestampCustomerPassTurnstile for arrTime=[0, 1, 1, 4, 4], dir=[1, 0, 1, 0, 1]: 0, 2, 1, 5, 4
ComputeTimestampCustomerPassTurnstile for arrTime=[0, 1, 1, 4, 4], dir=[1, 0, 1, 0, 0]: 0, 2, 1, 4, 5
ComputeTimestampCustomerPassTurnstile for arrTime=[0, 0, 0, 0, 1, 1, 1], dir=[0, 1, 1, 0, 1, 0, 1]: 4, 0, 1, 5, 2, 6, 3
 */
#endif
