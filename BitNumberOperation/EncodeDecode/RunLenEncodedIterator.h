#ifndef _RUN_LEN_ENCODED_ITERATOR_H
#define _RUN_LEN_ENCODED_ITERATOR_H
#include "Debug.h"
/*
Leetcode: RLE Iterator
Write an iterator that iterates through a run-length encoded sequence.
The iterator is initialized by RLEIterator(int[] A), where A is a run-length encoding of some sequence.
More specifically, for all even i, A[i] tells us the number of times that the non-negative integer value A[i+1] is repeated in the sequence.
The iterator supports one function: next(int n), which exhausts the next n elements (n >= 1) and returns the last element exhausted in this way.
If there is no element left to exhaust, next returns -1 instead.
For example, we start with A = [3,8,0,9,2,5], which is a run-length encoding of the sequence [8,8,8,5,5].
This is because the sequence can be read as "three eights, zero nines, two fives".
Example 1:
Input: ["RLEIterator","next","next","next","next"], [[[3,8,0,9,2,5]],[2],[1],[1],[2]]
Output: [null,8,8,5,-1]
Explanation:
RLEIterator is initialized with RLEIterator([3,8,0,9,2,5]).
This maps to the sequence [8,8,8,5,5].
RLEIterator.next is then called 4 times:
.next(2) exhausts 2 terms of the sequence, returning 8.  The remaining sequence is now [8, 5, 5].
.next(1) exhausts 1 term of the sequence, returning 8.  The remaining sequence is now [5, 5].
.next(1) exhausts 1 term of the sequence, returning 5.  The remaining sequence is now [5].
.next(2) exhausts 2 terms, returning -1.  This is because the first term exhausted was 5,
but the second term did not exist.  Since the last term exhausted does not exist, we return -1.
 */
class RunLenEncodedIterator
{
    std::vector<int> v;
    int curIdx;
    int curCount;
public:
    //A is a run-length encoded sequence
    RunLenEncodedIterator(const std::vector<int> & A) : v(A.begin(), A.end()), curIdx(0), curCount(0)
    {
        std::cout << "RunLenEncodedIterator for [" << Debug::ToStr1D<int>()(A) << "]: " << std::endl;
    }
    ~RunLenEncodedIterator(){}

    //exhaust the next n elements (n>=1) and return the last element exhausted
    int Next(int n)
    {
        while (curIdx < (int)v.size())
        {
            if ((curCount + n) > v[curIdx])
            {
                n -= (v[curIdx] - curCount);
                curCount = 0;
                curIdx += 2;
            }
            else
            {
                curCount += n;
                std::cout << "Next: " << v[curIdx+1] << std::endl;
                return v[curIdx+1];
            }
        }
        std::cout << "Next: " << -1 << std::endl;
        return -1;
        /*
        alternate solution:
        use a prefixSum array to save the count
        then when each time calling next(), accumulate total sum
        then binary search the total sum in the prefixSum array
        */
    }
};
/*
RunLenEncodedIterator for [3, 8, 0, 9, 2, 5]:
Next: 8
Next: 8
Next: 5
Next: -1
 */
#endif
