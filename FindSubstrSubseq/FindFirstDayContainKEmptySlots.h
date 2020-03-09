#ifndef _FIND_FIRST_DAY_CONTAIN_K_EMPTY_SLOTS_H
#define _FIND_FIRST_DAY_CONTAIN_K_EMPTY_SLOTS_H
#include "Debug.h"
/*
Leetcode: K Empty Slots
There is a garden with N slots. In each slot, there is a flower.
The N flowers will bloom one by one in N days.
In each day, there will be exactly one flower blooming and it will be in the status of blooming since then.
Given an array flowers consists of number from 1 to N.
Each number in the array represents the place where the flower will open in that day.
For example, flowers[i] = x means that the unique flower that blooms at day i will be at position x, where i and x will be in the range from 1 to N.
Also given an integer k, you need to output in which day there exists two flowers in the status of blooming,
 and also the number of flowers between them is k and these flowers are not blooming.
If there isn't such day, output -1.
Example 1:
Input:
flowers: [1,3,2]
k: 1
Output: 2
Explanation: In the second day, the first and the third flower have become blooming.
Example 2:
Input:
flowers: [1,2,3]
k: 1
Output: -1
 */
class FindFirstDayContainKEmptySlots
{
public:
    FindFirstDayContainKEmptySlots(){}

    int UseSet(const std::vector<int> & flowers, int k)
    {
        //find the first day such that there exists k unbloomed flowers in between 2 bloomed flowers
        //ex: [1,5,2,4,3], k=2
        //day1: [B,0,0,0,0]
        //day2: [B,0,0,0,B]
        //day3: [B,B,0,0,B], found 1st "k unbloombed flower between 2 bloomberd flowers"
        //day4: [B,B,0,B,B]
        //day5: [B,B,B,B,B]
        std::set<int> positions;//1-based positions
        int N = flowers.size();
        int res = -1;
        for (int i = 0; i < N; ++i)//iterate from first day to last day
        {
            int curPos = flowers[i];
            auto nxtItr = positions.lower_bound(curPos);
            if (nxtItr != positions.end() && *nxtItr-curPos-1==k)
            {
                res = i + 1;//to 1-based day
                break;
            }
            if (nxtItr != positions.begin() && curPos-*std::prev(nxtItr)-1==k)
            {
                res = i + 1;//to 1-based day
                break;
            }
            positions.insert(curPos);
        }

        std::cout << "FindFirstDayContainKEmptySlots for \"" << Debug::ToStr1D<int>()(flowers) << "\": " << res << std::endl;
        return res;
    }
};
/*
FindFirstDayContainKEmptySlots for "1, 5, 2, 4, 3": 3
 */
#endif
