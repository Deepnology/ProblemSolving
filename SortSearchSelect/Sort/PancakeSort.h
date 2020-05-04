#ifndef _PANCAKE_SORT_H
#define _PANCAKE_SORT_H
#include "Debug.h"
/*
Leetcode: Pancake sorting
Given an array A, we can perform a pancake flip: We choose some positive integer k <= A.length, then reverse the order of the first k elements of A.
We want to perform zero or more pancake flips (doing them one after another in succession) to sort the array A.
Return the k-values corresponding to a sequence of pancake flips that sort A.
Any valid answer that sorts the array within 10 * A.length flips will be judged as correct.
Example 1:
Input: [3,2,4,1]
Output: [4,2,4,3]
Explanation:
We perform 4 pancake flips, with k values 4, 2, 4, and 3.
Starting state: A = [3, 2, 4, 1]
After 1st flip (k=4): A = [1, 4, 2, 3]
After 2nd flip (k=2): A = [4, 1, 2, 3]
After 3rd flip (k=4): A = [3, 2, 1, 4]
After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted.
Example 2:
Input: [1,2,3]
Output: []
Explanation: The input is already sorted, so there is no need to flip anything.
Note that other answers, such as [3, 3], would also be accepted.
 */
class PancakeSort
{
public:
    PancakeSort(){}

    std::vector<int> FindRevFrontArrSizeSeq(std::vector<int> && A)
    {
        int N = A.size();
        std::vector<int> res;
        for (int frontLen = N; frontLen > 0; --frontLen)
        {
            auto maxItr = std::max_element(A.begin(), A.begin() + frontLen);
            std::reverse(A.begin(), maxItr + 1);//reverse A[0:maxItr] to move maxNum to front
            res.push_back(maxItr - A.begin() + 1);//+1 is to transform to size
            std::reverse(A.begin(), A.begin() + frontLen);//reverse A[0:frontLen) to move maxNum to prev of back
            res.push_back(frontLen);
        }

        std::cout << "PancakeSort FindRevFrontArrSizeSeq for [" << Debug::ToStr1D<int>()(A) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
PancakeSort FindRevFrontArrSizeSeq for [1, 2, 3, 4]: 3, 4, 2, 3, 1, 2, 1, 1
 */
#endif
