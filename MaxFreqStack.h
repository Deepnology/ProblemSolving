#ifndef _MAX_FREQ_STACK_H
#define _MAX_FREQ_STACK_H
#include "Debug.h"
/*
Leetcode: Maximum Frequency Stack
Implement FreqStack, a class which simulates the operation of a stack-like data structure.
FreqStack has two functions:
push(int x), which pushes an integer x onto the stack.
pop(), which removes and returns the most frequent element in the stack.
If there is a tie for most frequent element, the element closest to the top of the stack is removed and returned.
Example 1:
Input:
["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
Output: [null,null,null,null,null,null,null,5,7,5,4]
Explanation:
After making six .push operations, the stack is [5,7,5,7,4,5] from bottom to top.  Then:

pop() -> returns 5, as 5 is the most frequent.
The stack becomes [5,7,5,7,4].

pop() -> returns 7, as 5 and 7 is the most frequent, but 7 is closest to the top.
The stack becomes [5,7,5,4].

pop() -> returns 5.
The stack becomes [5,7,4].

pop() -> returns 4.
The stack becomes [5,7].
 */
class MaxFreqStack
{
    std::unordered_map<int, int> numFreq;//<num, freq>
    //keep a list of stacks for each freq ranging from maxFreq to 1 (head to tail)
    std::unordered_map<int, std::stack<int>> freqStk;//<freq, stk>, where freq must be continuously ranged from maxFreq to 1
    int maxFreq;//head of list
public:
    MaxFreqStack() : maxFreq(0)
    {}
    ~MaxFreqStack(){}

    void Push(int x) //push x to its cur freq mapped stk
    {
        int freq = ++numFreq[x];
        freqStk[freq].push(x);
        maxFreq = std::max(maxFreq, freq);
        std::cout << "MaxFreqStack::Push(" << x << "):" << std::endl;
        Print();
    }
    int Pop() //pop the stack with maxFreq (head of list)
    {
        int res = freqStk[maxFreq].top();
        freqStk[maxFreq].pop();
        --numFreq[res];
        if (freqStk[maxFreq].empty())
            --maxFreq;//advance head of list

        std::cout << "MaxFreqStack::Pop(): " << res << std::endl;
        Print();
        return res;
    }
private:
    void Print()
    {
        Debug::Print2D<int>()(freqStk);
        std::cout << "[Num,Freq]: " << Debug::ToStr1D<int>()(numFreq) << std::endl;
        std::cout << "MaxFreq: " << maxFreq << std::endl;

    }
};
/*
MaxFreqStack::Push(5):
Row#0	= 1: 5

[Num,Freq]: [5,1]
MaxFreq: 1
MaxFreqStack::Push(7):
Row#0	= 1: 5, 7

[Num,Freq]: [7,1], [5,1]
MaxFreq: 1
MaxFreqStack::Push(5):
Row#0	= 2: 5
Row#1	= 1: 5, 7

[Num,Freq]: [7,1], [5,2]
MaxFreq: 2
MaxFreqStack::Push(7):
Row#0	= 2: 5, 7
Row#1	= 1: 5, 7

[Num,Freq]: [7,2], [5,2]
MaxFreq: 2
MaxFreqStack::Push(4):
Row#0	= 2: 5, 7
Row#1	= 1: 5, 7, 4

[Num,Freq]: [4,1], [7,2], [5,2]
MaxFreq: 2
MaxFreqStack::Push(5):
Row#0	= 3: 5
Row#1	= 2: 5, 7
Row#2	= 1: 5, 7, 4

[Num,Freq]: [4,1], [7,2], [5,3]
MaxFreq: 3
MaxFreqStack::Pop(): 5
Row#0	= 3:
Row#1	= 2: 5, 7
Row#2	= 1: 5, 7, 4

[Num,Freq]: [4,1], [7,2], [5,2]
MaxFreq: 2
MaxFreqStack::Pop(): 7
Row#0	= 3:
Row#1	= 2: 5
Row#2	= 1: 5, 7, 4

[Num,Freq]: [4,1], [7,1], [5,2]
MaxFreq: 2
MaxFreqStack::Pop(): 5
Row#0	= 3:
Row#1	= 2:
Row#2	= 1: 5, 7, 4

[Num,Freq]: [4,1], [7,1], [5,1]
MaxFreq: 1
MaxFreqStack::Pop(): 4
Row#0	= 3:
Row#1	= 2:
Row#2	= 1: 5, 7

[Num,Freq]: [4,0], [7,1], [5,1]
MaxFreq: 1
 */
#endif
