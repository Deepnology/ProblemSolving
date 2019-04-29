#ifndef _PUSH_DOMINO_1D_ARRAY_H
#define _PUSH_DOMINO_1D_ARRAY_H
#include "Debug.h"
/*
Leetcode: Push Dominoes
There are N dominoes in a line, and we place each domino vertically upright.
In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
After each second, each domino that is falling to the left pushes the adjacent domino on the left.
Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
Given a string "S" representing the initial state. S[i] = 'L', if the i-th domino has been pushed to the left;
 S[i] = 'R', if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.
Return a string representing the final state.
Example 1:
Input: ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."
Example 2:
Input: "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.
 */
class PushDomino1DArray
{
public:
    PushDomino1DArray(){}

    std::string Solve(std::string dominoes)
    {
        std::string before = dominoes;

        int N = dominoes.size();
        std::vector<int> toRight(N, 0);
        std::vector<int> toLeft(N, 0);
        int last = 0;
        for (int i = 0; i < N; ++i)
        {
            if (dominoes[i] == 'R')
                last = 1;
            else if (dominoes[i] == 'L')
                last = -1;
            else if (last == 1)//'.' && last == 'R'
                toRight[i] = i==0 ? 0 : (toRight[i-1] + 1);
        }
        last = 0;
        for (int i = N-1; i >= 0; --i)
        {
            if (dominoes[i] == 'L')
                last = -1;
            else if (dominoes[i] == 'R')
                last = 1;
            else if (last == -1)
                toLeft[i] = i==N-1 ? 0 : (toLeft[i+1] + 1);
        }

        for (int i = 0; i < N; ++i)
        {
            if (dominoes[i] == '.')//only need to update '.'
            {
                if (toRight[i] == toLeft[i]) continue;
                if (!toRight[i] && toLeft[i])
                    dominoes[i] = 'L';
                else if (!toLeft[i] && toRight[i])
                    dominoes[i] = 'R';
                else if (toRight[i] > toLeft[i])
                    dominoes[i] = 'L';
                else// if (toLeft[i] > toRight[i])
                    dominoes[i] = 'R';
            }
        }

        std::cout << Debug::ToStr1D<int>()(toRight) << std::endl;
        std::cout << Debug::ToStr1D<int>()(toLeft) << std::endl;
        std::cout << "PushDomino1DArray for [" << before << "]: " << dominoes << std::endl;
        return dominoes;
    }
};
/*
0, 0, 0, 0, 1, 2, 3, 0, 0, 1, 2, 0, 0, 0
1, 0, 0, 0, 3, 2, 1, 0, 0, 2, 1, 0, 0, 0
PushDomino1DArray for [.L.R...LR..L..]: LL.RR.LLRRLL..
 */
#endif
