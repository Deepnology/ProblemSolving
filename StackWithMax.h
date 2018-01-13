/*StackQueue*/
#ifndef _STACK_WITH_MAX_H
#define _STACK_WITH_MAX_H
#include "Debug.h"
/*
Leetcode: Max Stack
Design a max stack that supports push, pop, top, peekMax and popMax.
push(x) -- Push element x onto stack.
pop() -- Remove the element on top of the stack and return it.
top() -- Get the element on the top.
peekMax() -- Retrieve the maximum element in the stack.
popMax() -- Retrieve the maximum element in the stack, and remove it. If you find more than one maximum elements, only remove the top-most one.
Example 1:
MaxStack stack = new MaxStack();
stack.push(5);
stack.push(1);
stack.push(5);
stack.top(); -> 5
stack.popMax(); -> 5
stack.top(); -> 1
stack.peekMax(); -> 5
stack.pop(); -> 1
stack.top(); -> 5
 */
class StackWithMax
{
    std::list<int> stk;
    std::map<int, std::list<std::list<int>::iterator>> sorted;
public:
    StackWithMax(){}

    void push(int x)
    {
        stk.push_back(x);
        sorted[x].push_back(std::prev(stk.end()));

        std::cout << "StackWithMax push: " << x << std::endl;
    }

    int pop()
    {
        int top = stk.back();
        stk.pop_back();
        sorted[top].pop_back();
        if (sorted[top].empty()) sorted.erase(top);

        std::cout << "StackWithMax pop: " << top << std::endl;
        return top;
    }

    int top()
    {
        std::cout << "StackWithMax top: " << stk.back() << std::endl;
        return stk.back();
    }

    int peekMax()
    {
        std::cout << "StackWithMax peekMax: " << sorted.rbegin()->first << std::endl;
        return sorted.rbegin()->first;
    }

    int popMax()
    {
        int max = sorted.rbegin()->first;
        std::list<int>::iterator itr = *std::prev(sorted.rbegin()->second.end());
        stk.erase(itr);
        sorted.rbegin()->second.pop_back();
        if (sorted.rbegin()->second.empty())
            sorted.erase(max);

        std::cout << "StackWithMax popMax: " << max << std::endl;
        return max;
    }
};
/*
StackWithMax push: 5
StackWithMax push: 1
StackWithMax push: 5
StackWithMax top: 5
StackWithMax popMax: 5
StackWithMax top: 1
StackWithMax peekMax: 5
StackWithMax pop: 1
StackWithMax top: 5
 */
#endif
