#ifndef _MIN_NUM_PER_HR_TO_EAT_ALL_PILES_IN_GIVEN_HRS_H
#define _MIN_NUM_PER_HR_TO_EAT_ALL_PILES_IN_GIVEN_HRS_H
#include "Debug.h"
/*
Leetcode: Koko Eating Bananas
Koko loves to eat bananas.
There are N piles of bananas, the i-th pile has piles[i] bananas.
The guards have gone and will come back in H hours.
Koko can decide her bananas-per-hour eating speed of K.
Each hour, she chooses some pile of bananas, and eats K bananas from that pile.
If the pile has less than K bananas, she eats all of them instead, and won't eat any more bananas during this hour.
Koko likes to eat slowly, but still wants to finish eating all the bananas before the guards come back.
Return the minimum integer K such that she can eat all the bananas within H hours.
Example 1:
Input: piles = [3,6,7,11], H = 8
Output: 4
Example 2:
Input: piles = [30,11,23,4,20], H = 5
Output: 30
Example 3:
Input: piles = [30,11,23,4,20], H = 6
Output: 23
 */
class MinNumPerHrToEatAllPilesInGivenHrs
{
public:
    int BinarySearch(std::vector<int> & piles, int H)
    {
        int lo = 1;//LB num of bananas in a pile that can be eaten in an hour (eg, speed)
        int hi = 0;//UB num of bananas in a pile that can be eaten in an hour (eg, speed)
        int N = piles.size();
        for (int i = 0; i < N; ++i)
            hi = std::max(hi, piles[i]);
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            int totalHr = totalHours(piles, mid);
            if (totalHr <= H)//since we want to find min speed, when equal, search left
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        return lo;
    }
private:
    int totalHours(std::vector<int> & piles, int speed)
    {
        int hr = 0; int N = piles.size();
        for (int i = 0; i < N; ++i)
            hr += (int)ceil((double)piles[i]/(double)speed);
        return hr;
    }
};
#endif
