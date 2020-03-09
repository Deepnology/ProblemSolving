#ifndef _MIN_NUM_BOATS_TO_SAVE_PEOPLE_H
#define _MIN_NUM_BOATS_TO_SAVE_PEOPLE_H
#include "Debug.h"
/*
Leetcode: Boats To Save People
The i-th person has weight people[i], and each boat can carry a maximum weight of limit.
Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit.
Return the minimum number of boats to carry every given person.  (It is guaranteed each person can be carried by a boat.)
Example 1:
Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
Example 2:
Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
Example 3:
Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
 */
class MinNumBoatsToSavePeople
{
public:
    MinNumBoatsToSavePeople(){}

    int SortGreedy(std::vector<int> && people, int limit)
    {
        //use bucket sort instead of quick sort: O(N+limit) time, O(limit) space
        std::vector<int> count(limit+1,0);
        for (auto & i : people)
            ++count[i];
        people.clear();
        for (int i = 0; i < limit+1; ++i)
            while (count[i]-- > 0)
                people.push_back(i);

        int res = 0;
        int N = people.size();
        int i = 0, j = N-1;
        while (i < j)//greedy
        {
            if (people[i]+people[j] <= limit)
            {
                ++i; --j; ++res;
            }
            else
            {
                --j; ++res;
            }
        }
        if (i == j) ++res;

        std::cout << "MinNumBoatsToSavePeople SortGreedy for [" << Debug::ToStr1D<int>()(people) << "], limit=" << limit << ": " << res << std::endl;
        return res;
    }
};
/*
MinNumBoatsToSavePeople SortGreedy for [1, 2, 2, 3], limit=3: 3
 */
#endif
