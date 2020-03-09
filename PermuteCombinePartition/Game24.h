#ifndef _GAME_24_H
#define _GAME_24_H
#include "Debug.h"
/*
Leetcode: 24 Game
You have 4 cards each containing a number from 1 to 9.
You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.
Example 1:
Input: [4, 1, 8, 7]
Output: True
Explanation: (8-4) * (7-1) = 24
Example 2:
Input: [1, 2, 1, 2]
Output: False
Note:
The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
Every operation done is between two numbers. In particular, we cannot use - as a unary operator. For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.
 */
class Game24
{
public:
    Game24(){}

    bool DFS(const std::vector<int> & nums)
    {
        std::vector<double> nums2;
        for (auto i : nums)
            nums2.push_back(i*1.0);
        bool res = recur(nums2);
        std::cout << "Game24 DFS for [" << Debug::ToStr1D<int>()(nums) << "]: " << res << std::endl;
        return res;
    }
private:
    bool recur(std::vector<double> & nums)
    {
        if (nums.size() == 1)
        {
            return std::abs(nums[0] - 24.0) < 0.0001;
        }
        int N = nums.size();
        for (int i = 0; i < N-1; ++i)
            for (int j = i+1; j < N; ++j)
            {
                std::vector<double> nxtNums(nums);
                double a = nxtNums[i];
                double b = nxtNums[j];
                nxtNums.erase(nxtNums.begin()+j);

                nxtNums[i] = a + b; if (recur(nxtNums)) return true;
                nxtNums[i] = a * b; if (recur(nxtNums)) return true;

                nxtNums[i] = a - b; if (recur(nxtNums)) return true;
                nxtNums[i] = b - a; if (recur(nxtNums)) return true;

                if (b != 0) { nxtNums[i] = a / b; if (recur(nxtNums)) return true; }
                if (a != 0) { nxtNums[i] = b / a; if (recur(nxtNums)) return true; }
            }
        return false;
    }
};
/*
Game24 DFS for [4, 1, 8, 7]: 1
 */
#endif
