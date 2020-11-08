#ifndef _COUNT_STEPS_REDUCE_BINARY_NUM_STR_TO_1_H
#define _COUNT_STEPS_REDUCE_BINARY_NUM_STR_TO_1_H
#include "Debug.h"
/*
Leetcode: Number of Steps to Reduce a Number in Binary Representation to One
Given a number s in their binary representation.
Return the number of steps to reduce it to 1 under the following rules:
If the current number is even, you have to divide it by 2.
If the current number is odd, you have to add 1 to it.
It's guaranteed that you can always reach to one for all testcases.
Example 1:
Input: s = "1101"
Output: 6
Explanation: "1101" corressponds to number 13 in their decimal representation.
Step 1) 13 is odd, add 1 and obtain 14.
Step 2) 14 is even, divide by 2 and obtain 7.
Step 3) 7 is odd, add 1 and obtain 8.
Step 4) 8 is even, divide by 2 and obtain 4.
Step 5) 4 is even, divide by 2 and obtain 2.
Step 6) 2 is even, divide by 2 and obtain 1.
Example 2:
Input: s = "10"
Output: 1
Explanation: "10" corressponds to number 2 in their decimal representation.
Step 1) 2 is even, divide by 2 and obtain 1.
 */
class CountStepsReduceBinaryNumStrTo1
{
public:
    int Count(std::string s)
    {
        int steps = 0;
        while (1)
        {
            while (!s.empty() && s.back() == '0')
            {
                s.pop_back();
                ++steps;
            }
            if (s == "1") return steps;
            bool carry = false;
            while (!s.empty() && s.back() == '1')
            {
                carry = true;
                s.pop_back();
                ++steps;//count for removing 0s
            }
            if (carry)
            {
                if (s.empty()) s.push_back('1');
                else s.back() = '1';
                ++steps;//count for adding 1
            }
            if (s == "1") return steps;
            //std::cout << s << std::endl;
        }
        return steps;
    }
};
#endif
