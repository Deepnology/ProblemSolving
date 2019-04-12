#ifndef _STACK_PERMUTATION_H
#define _STACK_PERMUTATION_H
#include "Debug.h"
/*
https://www.geeksforgeeks.org/stack-permutations-check-if-an-array-is-stack-permutation-of-other/
Given two integer arrays with unique numbers in each array,
where one array represents the input order to a stack, and the other represents the output order out of the stack.
Determine if the output array order is a valid order.
Leetcode: Validate Stack Sequences
Given two sequences pushed and popped with distinct values, return true if and only if
 this could have been the result of a sequence of push and pop operations on an initially empty stack.
Example 1:
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
Example 2:
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.
 */
class StackPermutation
{
public:
    StackPermutation(){}

    bool Validate1(const std::vector<int> & pushed, const std::vector<int> & popped)
    {
        std::stack<int> stk;
        int i = 0;
        for (const int & x : pushed)
        {
            stk.push(x);
            while (!stk.empty() && stk.top() == popped[i])
            {
                stk.pop();
                ++i;
            }
        }
        bool res = i == popped.size();
        std::cout << "StackPermutation Validate1 for [" << Debug::ToStr1D<int>()(pushed) << "], [" << Debug::ToStr1D<int>()(popped) << "]: " << res << std::endl;
        return res;
    }

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
StackPermutation Validate1 for [1, 2, 3, 4, 5], [4, 5, 3, 2, 1]: 1
StackPermutation Validate for [1, 2, 3, 4, 5], [4, 5, 3, 2, 1]: 1
 */
#endif
