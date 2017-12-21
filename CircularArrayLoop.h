#ifndef CIRCULAR_ARRAY_LOOP_H
#define CIRCULAR_ARRAY_LOOP_H
#include "Debug.h"
/*
Leetcode: Circular Array Loop
You are given an array of positive and negative integers.
If a number n at an index is positive, then move forward n steps.
Conversely, if it's negative (-n), move backward n steps.
Assume the first element of the array is forward next to the last element, and the last element is backward next to the first element.
Determine if there is a loop in this array.
A loop starts and ends at a particular index with more than 1 element along the loop.
The loop must be "forward" or "backward'.
Example 1: Given the array [2, -1, 1, 2, 2], there is a loop, from index 0 -> 2 -> 3 -> 0.
Example 2: Given the array [-1, 2], there is no loop.
Note: The given array is guaranteed to contain no element "0".
Can you do it in O(n) time complexity and O(1) space complexity?

Leetcode: Array Nesting
A zero-indexed array A consisting of N different integers is given.
The array contains all integers in the range [0, N - 1].
Sets S[K] for 0 <= K < N are defined as follows:
S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.
Sets S[K] are finite for each K and should NOT contain duplicates.
Write a function that given an array A consisting of N integers, return the size of the largest set S[K] for this array.
Example 1:
Input: A = [5,4,0,3,1,6,2]
Output: 4
Explanation:
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.
One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
*/
class CircularArrayLoop
{
public:
	CircularArrayLoop() {}

	bool HasLoop(std::vector<int> & nums)
	{
		std::string before = Debug::ToStr1D<int>()(nums);

		int N = nums.size();
		for (int i = 0; i < N; ++i)
		{
			int slow = i;
			int fast = nxtIdx(i, nums);
			while (nums[slow] * nums[nxtIdx(slow, nums)] > 0 && nums[fast] * nums[nxtIdx(nxtIdx(fast, nums), nums)] > 0)//>0: same dir && != 0
			{
				if (slow == nxtIdx(slow, nums))
					break;
				if (slow == fast)
				{
					std::cout << "CircularArrayLoop HasLoop for \"" << before << "\": 1" << std::endl;
					return true;
				}
				slow = nxtIdx(slow, nums);
				fast = nxtIdx(nxtIdx(fast, nums), nums);
			}

			//mark this path 0s to skip recomputation
			slow = i;
			while (nums[slow] * nums[nxtIdx(slow, nums)] > 0)
			{
				nums[slow] = 0;
				slow = nxtIdx(slow, nums);
			}
		}

		std::cout << "CircularArrayLoop HasLoop for \"" << before << "\": 0" << std::endl;
		return false;
	}
private:
	int nxtIdx(int i, std::vector<int> & nums)
	{
		int N = nums.size();
		int nxt = i + nums[i];
		return nxt < 0 ? nxt + N : nxt%N;
	}

public:
	//Leetcode: Array Nesting
	int LongestLoopLen(std::vector<int>& nums)//nums is a idx-seq array w/ nums in [0:N-1] w/o duplicates. Find a circular loop w/ longest length.
	{
		int N = nums.size();
		int maxLen = 0;
		for (int i = 0; i < N; ++i)
		{
			int begin = i;
			int curLen = 0;
			while (true)
			{
				int tgt = nums[begin];
				++curLen;
				if (tgt < 0)
					break;
				if (tgt == i)
				{
					maxLen = std::max(maxLen, curLen);
					break;
				}

				nums[begin] = -nums[begin];
				begin = tgt;
			}
		}
		return maxLen;
	}
};
/*
CircularArrayLoop HasLoop for "2, -1, 1, 2, 2": 1
CircularArrayLoop HasLoop for "-1, 2": 0
*/
#endif
