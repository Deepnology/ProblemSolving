#ifndef _STACK_WITH_INCR_BOTTOM_K_ELEMENTS_H
#define _STACK_WITH_INCR_BOTTOM_K_ELEMENTS_H
#include "Debug.h"
/*
Leetcode: Design a Stack With Increment Operation
Design a stack which supports the following operations.
Implement the CustomStack class:
CustomStack(int maxSize) Initializes the object with maxSize which is the maximum number of elements in the stack or do nothing if the stack reached the maxSize.
void push(int x) Adds x to the top of the stack if the stack hasn't reached the maxSize.
int pop() Pops and returns the top of stack or -1 if the stack is empty.
void inc(int k, int val) Increments the bottom k elements of the stack by val. If there are less than k elements in the stack, just increment all the elements in the stack.
 */
class StackWithIncrBottomKElements
{
    std::stack<int> stk;
    std::vector<int> v;
    int N;
public:
    StackWithIncrBottomKElements(int maxSize)
    {
        N = maxSize;
        v.resize(N, 0);
    }
    void push(int x)
    {
        if (stk.size() == N)
            return;
        stk.push(x);
    }
    int pop()
    {
        if (stk.empty())
            return -1;
        int topIdx = stk.size() - 1;
        int topVal = stk.top() + v[topIdx];
        stk.pop();
        if (topIdx-1 >= 0)
            v[topIdx-1] += v[topIdx];
        v[topIdx] = 0;
        return topVal;
    }
    void increment(int k, int val)
    {
        int incrIdx = std::min(k-1, (int)stk.size()-1);
        if (incrIdx >= 0)
            v[incrIdx] += val;
    }
};
#endif
