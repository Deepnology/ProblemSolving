#ifndef _RANDOM_PICK_NUMS_IN_RANGE_WO_REPEAT_H
#define _RANDOM_PICK_NUMS_IN_RANGE_WO_REPEAT_H
#include "Debug.h"
/*
Two Sigma
Similar to RandomSubset.h
 */
class RandomPickNumsInRangeWoRepeat
{
    std::unordered_map<int,int> map;
    int low;
    int high;
    int offset;
    int N;
    int i;
public:
    RandomPickNumsInRangeWoRepeat(int low_, int high_): low(low_), high(high_),
                                                                offset(low_ - 0), N(high-low+1), i(0){}

    int Pick() //O(1) time
    {
        int j = rand() % (N-i) + i; //rand in [i:N-1]
        auto ptr1 = map.find(j);
        auto ptr2 = map.find(i);
        if (ptr1 == map.end() && ptr2 == map.end())
        {
            map[j] = i;//add
            map[i] = j;//add
        }
        else if (ptr1 == map.end() && ptr2 != map.end())
        {
            map[j] = ptr2->second;//add before update
            ptr2->second = j;//update
        }
        else if (ptr1 != map.end() && ptr2 == map.end())
        {
            map[i] = ptr1->second;//add before update
            ptr1->second = i;//update
        }
        else
            std::swap(ptr1->second, ptr2->second);
        //now map[i]
        int res = map[i];
        ++i;

        std::cout << Debug::ToStr1D<int,int>()(map) << std::endl;
        std::cout << "RandomPickNumsInRangeWoRepeat for [" << low << "," << high << "]: " << offset + res << std::endl;
        return offset + res;
    }

    void Test()
    {
        int count = N;
        while (count-- > 0)
            Pick();
    }
};
/*
[0,1], [1,0]
RandomPickNumsInRangeWoRepeat for [15,20]: 16
[4,0], [0,1], [1,4]
RandomPickNumsInRangeWoRepeat for [15,20]: 19
[2,3], [3,2], [4,0], [0,1], [1,4]
RandomPickNumsInRangeWoRepeat for [15,20]: 18
[2,3], [3,2], [4,0], [0,1], [1,4]
RandomPickNumsInRangeWoRepeat for [15,20]: 17
[5,0], [2,3], [3,2], [4,5], [0,1], [1,4]
RandomPickNumsInRangeWoRepeat for [15,20]: 20
[5,0], [2,3], [3,2], [4,5], [0,1], [1,4]
RandomPickNumsInRangeWoRepeat for [15,20]: 15

[0,10], [10,0]
RandomPickNumsInRangeWoRepeat for [-5,5]: 5
[1,8], [8,1], [0,10], [10,0]
RandomPickNumsInRangeWoRepeat for [-5,5]: 3
[2,0], [1,8], [8,1], [0,10], [10,2]
RandomPickNumsInRangeWoRepeat for [-5,5]: -5
[3,2], [2,0], [1,8], [8,1], [0,10], [10,3]
RandomPickNumsInRangeWoRepeat for [-5,5]: -3
[4,5], [5,4], [3,2], [2,0], [1,8], [8,1], [0,10], [10,3]
RandomPickNumsInRangeWoRepeat for [-5,5]: 0
[4,5], [5,3], [3,2], [2,0], [1,8], [8,1], [0,10], [10,4]
RandomPickNumsInRangeWoRepeat for [-5,5]: -2
[6,1], [4,5], [5,3], [3,2], [2,0], [1,8], [8,6], [0,10], [10,4]
RandomPickNumsInRangeWoRepeat for [-5,5]: -4
[7,9], [9,7], [6,1], [4,5], [5,3], [3,2], [2,0], [1,8], [8,6], [0,10], [10,4]
RandomPickNumsInRangeWoRepeat for [-5,5]: 4
[7,9], [9,7], [6,1], [4,5], [5,3], [3,2], [2,0], [1,8], [8,6], [0,10], [10,4]
RandomPickNumsInRangeWoRepeat for [-5,5]: 1
[7,9], [9,7], [6,1], [4,5], [5,3], [3,2], [2,0], [1,8], [8,6], [0,10], [10,4]
RandomPickNumsInRangeWoRepeat for [-5,5]: 2
[7,9], [9,7], [6,1], [4,5], [5,3], [3,2], [2,0], [1,8], [8,6], [0,10], [10,4]
RandomPickNumsInRangeWoRepeat for [-5,5]: -1
 */
#endif
