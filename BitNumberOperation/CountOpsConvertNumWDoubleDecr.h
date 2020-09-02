#ifndef _COUNT_OPS_CONVERT_NUM_W_DOUBLE_DECR_H
#define _COUNT_OPS_CONVERT_NUM_W_DOUBLE_DECR_H
#include "Debug.h"
/*
Leetcode: Broken Calculator
On a broken calculator that has a number showing on its display, we can perform two operations:
Double: Multiply the number on the display by 2, or;
Decrement: Subtract 1 from the number on the display.
Initially, the calculator is displaying the number X.
Return the minimum number of operations needed to display the number Y.
Example 1:
Input: X = 2, Y = 3
Output: 2
Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.
Example 2:
Input: X = 5, Y = 8
Output: 2
Explanation: Use decrement and then double {5 -> 4 -> 8}.
Example 3:
Input: X = 3, Y = 10
Output: 3
Explanation:  Use double, decrement and double {3 -> 6 -> 5 -> 10}.
Example 4:
Input: X = 1024, Y = 1
Output: 1023
Explanation: Use decrement operations 1023 times.
Note:
1 <= X <= 10^9
1 <= Y <= 10^9
 */
class CountOpsConvertNumWDoubleDecr
{
public:
    int Forward(int X, int Y)
    {
        //forward solution: O(log(Y/X)) time
        if (X >= Y) return X-Y; //can only decrement X until Y
        int numOps = 0;
        int mul = 1;
        while (X < Y)
        {
            X *= 2;
            mul *= 2;
            ++numOps;
        }
        int diff = X-Y;
        while (diff != 0)
        {
            if (diff < mul)
            {
                mul /= 2;
            }
            else
            {
                diff -= mul;//applying decrement of X before applying double of X
                ++numOps;
            }
        }
        return numOps;
    }

    int Backward(int X, int Y)
    {
        //backward solution: O(log(Y/X)) time
        return recur(X, Y);
    }
private:
    int recur(int X, int Y)
    {
        if (X >= Y) return X-Y;
        if (Y % 2 == 0) return 1 + recur(X, Y/2); //reverse operation
        else return 1 + recur(X, Y+1); //reverse operation
    }
};
#endif
