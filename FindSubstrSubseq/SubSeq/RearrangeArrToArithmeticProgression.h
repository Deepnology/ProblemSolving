#ifndef _REARRANGE_ARR_TO_ARITHMETIC_PROGRESSION_H
#define _REARRANGE_ARR_TO_ARITHMETIC_PROGRESSION_H
#include "Debug.h"
/*
Leetcode: Can Make Arithmetic Progression From Sequence
Given an array of numbers arr.
 A sequence of numbers is called an arithmetic progression if the difference between any two consecutive elements is the same.
Return true if the array can be rearranged to form an arithmetic progression, otherwise, return false.
Example 1:
Input: arr = [3,5,1]
Output: true
Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively, between each consecutive elements.
Example 2:
Input: arr = [1,2,4]
Output: false
Explanation: There is no way to reorder the elements to obtain an arithmetic progression.
 */
class RearrangeArrToArithmeticProgression
{
public:
    bool Valid_UseHashMap(std::vector<int> & arr)
    {
        if (arr.size() < 2) return true;
        std::unordered_map<int,int> toCount;
        for (auto & num : arr)
            toCount[num]++;
        int first = INT_MAX; int second = INT_MAX;
        for (auto & num : arr)
        {
            if (num < first)
            {
                second = first;
                first = num;
            }
            else if (num < second)
            {
                second = num;
            }
        }
        int count = 2;
        int diff = second - first;
        toCount[first]--; toCount[second]--;
        //std::cout << first << "," << second << "," << diff << std::endl;
        while (count < arr.size())
        {
            if (toCount[second+diff] == 0) return false;
            toCount[second+diff]--;
            first = second;
            second = second+diff;
            ++count;
        }
        return true;
    }

    bool Valid_InPlace(std::vector<int> & arr)
    {
        if (arr.size() < 2) return true;
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        for (auto & num : arr)
        {
            minVal = std::min(minVal, num);
            maxVal = std::max(maxVal, num);
        }
        int N = arr.size();
        if ((maxVal-minVal)%(N-1) != 0) return false;
        int diff = (maxVal-minVal)/(N-1);
        int i = 0;
        while (i < N)
        {
            if (arr[i] == minVal + i*diff)
                ++i;
            else
            {
                if ((arr[i]-minVal)%diff != 0) return false;
                int idx = (arr[i]-minVal)/diff; //idx: the correct index for arr[i]
                if (arr[i] == arr[idx]) return false;
                std::swap(arr[i], arr[idx]);
            }
        }
        return true;
    }
};
#endif
