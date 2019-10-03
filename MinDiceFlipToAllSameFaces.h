#ifndef _MIN_DICE_FLIP_TO_ALL_SAME_FACES_H
#define _MIN_DICE_FLIP_TO_ALL_SAME_FACES_H
#include "Debug.h"
/*
Amazon OA
A six-sided die is a small cube with a different number of pips on each face (side), ranging from 1 to 6.
On any two opposite side of the cube, the number of pips adds up to 7; that is, there are three pairs of opposite sides: 1 and 6, 2 and 5, and 3 and 4.
There are N dice lying on a table, each showing the pips on its top face. In one move, you can take one die and rotate it to an adjacent face.
For example, you can rotate a die that shows 1 s that it shows 2, 3, 4 or 5.
However, it cannot show 6 in a single move, because the faces with one pip and six pips visible are opposite sides rather than adjacent.
You want to show the same number of pips on the top face of all N dice.
Given that each of the dice can be moved multiple times, count the minimum number of moves needed to get equal faces.
Write a function that, given an array A consisting of N integers describing the number of pips (from 1 to 6) shown on each die's top face, returns the minimum number of moves necessary for each die show the same number of pips.
Example 1:
Input: A = [1, 2, 3]
Output: 2
Explanation: You can pick the first two dice and rotate each of them in one move so that they all show three pips on the top face.
Notice that you can also pick any other pair of dice in this case.
Example 2:
Input: A = [1, 1, 6]
Output: 2
Explanation: The only optimal answer is to rotate the last die so that it shows one pip. It is necessary to use two rotations to achieve this.
Example 3:
Input: A = [1, 6, 2, 3]
Output: 3
Explanation: For instance, you can make all dice show 2: just rotate each die which is not showing 2.
Notice that for each die you can do this in one move.
Assume that:
N is an integer within the range [1..100];
each element of the array A is an integer within the range [1..6].
 */
class MinDiceFlipToAllSameFaces
{
public:
    MinDiceFlipToAllSameFaces(){}

    int Naive(std::vector<int> && dices) //O(N*6) time
    {
        int minCount = INT_MAX;

        for (int i = 1; i < 7; ++i)
        {
            int count = 0;
            for (auto & d : dices)
            {
                if (d == i) continue; //no need to flip
                if (d == 7-i) count += 2; //need to flip 2 times to reach opposite
                else ++count; //need to flip 1 time to reach neighbor face
            }
            minCount = std::min(minCount, count);
        }

        std::cout << "MinDiceFlipToAllSameFaces Naive for [" << Debug::ToStr1D<int>()(dices) << "]: " << minCount << std::endl;
        return minCount;
    }

    int Better(std::vector<int> && dices) //O(N+6) time, O(6) space
    {
        int N = dices.size();
        int minCount = INT_MAX;
        std::vector<int> count(7, 0);//use only count[1:6]
        for (auto & d : dices)
            ++count[d];

        for (int i = 1; i < 7; ++i)
        {
            int curCount = 0;
            curCount += 2*count[7-i]; //7-i is the face that needs to flip 2 times
            curCount += N-count[i]-count[7-i]; //the faces except 7-i and i need to flip 1 time
            minCount = std::min(minCount, curCount);
        }

        std::cout << "MinDiceFlipToAllSameFaces Better for [" << Debug::ToStr1D<int>()(dices) << "]: " << minCount << std::endl;
        return minCount;
    }
};
/*
MinDiceFlipToAllSameFaces Naive for [1, 1, 6]: 2
MinDiceFlipToAllSameFaces Better for [1, 1, 6]: 2
MinDiceFlipToAllSameFaces Naive for [1, 6, 2, 3]: 3
MinDiceFlipToAllSameFaces Better for [1, 6, 2, 3]: 3
 */
/*
Leetcode: Minimum Domino Rotations For Equal Row
In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.
(A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
We may rotate the i-th domino, so that A[i] and B[i] swap values.
Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.
If it cannot be done, return -1.
Example 1:
Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
Example 2:
Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of values equal.
 */
class MinDiceFlipToAllSameFaces2
{
public:
    int Naive(std::vector<int> && A, std::vector<int> && B)
    {
        int N = A.size();
        int maxCount = 0;
        int maxCountFace;
        for (int f = 1; f <= 6; ++f)
        {
            int count = 0;
            for (int i = 0; i < N; ++i)
            {
                if (A[i]==f || B[i]==f)
                    ++count;
            }
            if (maxCount < count)
            {
                maxCount = count;
                maxCountFace = f;
            }
        }
        if (maxCount == N)
        {
            int aFlip = 0;
            int bFlip = 0;
            for (int i = 0; i < N; ++i)
            {
                if (A[i]!=maxCountFace) ++aFlip;
                if (B[i]!=maxCountFace) ++bFlip;
            }
            return std::min(aFlip,bFlip);
        }
        return -1;
    }
    int Better(std::vector<int> && A, std::vector<int> && B)
    {
        //only need to try A[0] and B[0]
        int N = A.size();
        int aFlip = 0;
        int bFlip = 0;
        int i = 0;
        for (; i < N && (A[i]==A[0]||B[i]==A[0]); ++i)
        {
            if(A[i] != A[0]) ++aFlip;
            if(B[i] != A[0]) ++bFlip;
        }
        if (i==N) return std::min(aFlip, bFlip);
        aFlip = 0;
        bFlip = 0;
        i = 0;
        for (; i < N && (A[i]==B[0]||B[i]==B[0]); ++i)
        {
            if (A[i] != B[0]) ++aFlip;
            if (B[i] != B[0]) ++bFlip;
        }
        if (i==N) return std::min(aFlip, bFlip);
        return -1;
    }
};
#endif
