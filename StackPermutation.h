#ifndef _STACK_PERMUTATION_H
#define _STACK_PERMUTATION_H
#include "Debug.h"
/*
https://www.geeksforgeeks.org/stack-permutations-check-if-an-array-is-stack-permutation-of-other/
Given two integer arrays with unique numbers in each array,
where one array represents the input order to a stack, and the other represents the output order out of the stack.
Determine if the output array order is a valid order.
 */
class StackPermutation
{
public:
    StackPermutation(){}

    bool Validate(const std::vector<int> & input, const std::vector<int> & output)
    {
        std::queue<int> inQue;
        for (const auto i : input)
            inQue.push(i);
        std::queue<int> outQue;
        for (const auto i : output)
            outQue.push(i);
        std::stack<int> stk;
        while (!inQue.empty())
        {
            int cur = inQue.front();
            inQue.pop();
            if (cur == outQue.front())//1. cancel out inQue.front() and outQue.front()
            {
                outQue.pop();
                while (!stk.empty())
                {
                    if (stk.top() == outQue.front())//2. cancel out stk.top() and outQue.front()
                    {
                        stk.pop();
                        outQue.pop();
                    }
                    else
                        break;
                }
            }
            else
                stk.push(cur);
        }
        bool res = inQue.empty() && stk.empty();

        std::cout << "StackPermutation Validate for [" << Debug::ToStr1D<int>()(input) << "], [" << Debug::ToStr1D<int>()(output) << "]: " << res << std::endl;
        return res;
    }
};
/*
StackPermutation Validate for [1, 2, 3, 4, 5], [5, 4, 3, 2, 1]: 1
StackPermutation Validate for [1, 2, 3, 4, 5], [1, 2, 3, 4, 5]: 1
StackPermutation Validate for [5, 7, 8, 4, 6], [6, 8, 4, 7, 5]: 0
StackPermutation Validate for [5, 7, 8, 4, 6], [6, 4, 5, 7, 8]: 0
StackPermutation Validate for [5, 7, 8, 4, 6], [6, 4, 7, 8, 5]: 0
StackPermutation Validate for [5, 7, 8, 4, 6], [7, 8, 4, 6, 5]: 1
 */
#endif
