#ifndef _ARRAY_OF_STACKS_H
#define _ARRAY_OF_STACKS_H
#include "Debug.h"
/*
Leetcode: Dinner Plate Stacks
You have an infinite number of stacks arranged in a row and numbered (left to right) from 0, each of the stacks has the same maximum capacity.
Implement the DinnerPlates class:
DinnerPlates(int capacity) Initializes the object with the maximum capacity of the stacks.
void push(int val) pushes the given positive integer val into the leftmost stack with size less than capacity.
int pop() returns the value at the top of the rightmost non-empty stack and removes it from that stack, and returns -1 if all stacks are empty.
int popAtStack(int index) returns the value at the top of the stack with the given index and removes it from that stack, and returns -1 if the stack with that given index is empty.
Example:
Input:
["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
[[2],[1],[2],[3],[4],[5],[0],[20],[21],[0],[2],[],[],[],[],[]]
Output:
[null,null,null,null,null,null,2,null,null,20,21,5,4,3,1,-1]
Explanation:
DinnerPlates D = DinnerPlates(2);  // Initialize with capacity = 2
D.push(1);
D.push(2);
D.push(3);
D.push(4);
D.push(5);         // The stacks are now:  2  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 2.  The stacks are now:     4
                                                       1  3  5
                                                       ﹈ ﹈ ﹈
D.push(20);        // The stacks are now: 20  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.push(21);        // The stacks are now: 20  4 21
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 20.  The stacks are now:     4 21
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.popAtStack(2);   // Returns 21.  The stacks are now:     4
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.pop()            // Returns 5.  The stacks are now:      4
                                                        1  3
                                                        ﹈ ﹈
D.pop()            // Returns 4.  The stacks are now:   1  3
                                                        ﹈ ﹈
D.pop()            // Returns 3.  The stacks are now:   1
                                                        ﹈
D.pop()            // Returns 1.  There are no stacks.
D.pop()            // Returns -1.  There are still no stacks.
 */
class ArrayOfStacks
{
    int stkSize;
    std::vector<std::stack<int>> stkV;
    std::set<int> nonFullStkIdx;
public:
    ArrayOfStacks(int capacity)
    {
        stkSize = capacity;
    }
    void push(int val)
    {
        if (!nonFullStkIdx.empty())
        {
            stkV[*nonFullStkIdx.begin()].push(val);
            if (stkV[*nonFullStkIdx.begin()].size() == stkSize)
                nonFullStkIdx.erase(nonFullStkIdx.begin());
        }
        else
        {
            stkV.push_back(std::stack<int>({val}));
            if (stkV.back().size() < stkSize)
                nonFullStkIdx.insert(stkV.size()-1);
        }
    }
    int pop()
    {
        if (stkV.empty()) return -1;
        int res = stkV.back().top();
        stkV.back().pop();
        if (stkV.back().empty())
        {
            while (!stkV.empty() && stkV.back().empty())
            {
                nonFullStkIdx.erase(stkV.size()-1);
                stkV.pop_back();
            }
        }
        else
            nonFullStkIdx.insert(stkV.size()-1);
        return res;
    }
    int popAtStack(int index)
    {
        if (stkV.size() < index+1) return -1;
        if (stkV[index].empty()) return -1;
        int res = stkV[index].top();
        stkV[index].pop();
        if (stkV.size()==index+1 && stkV[index].empty())
        {
            while (!stkV.empty() && stkV.back().empty())
            {
                nonFullStkIdx.erase(stkV.size()-1);
                stkV.pop_back();
            }
        }
        else
            nonFullStkIdx.insert(index);
        return res;
    }
};
#endif
