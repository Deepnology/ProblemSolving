#ifndef SUB_ARR_W_LESS_PRODUCT_H
#define SUB_ARR_W_LESS_PRODUCT_H
#include "Debug.h"
/*
Leetcode: Subarray Product Less Than K
Your are given an array of positive integers nums.
Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.
Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Note:
0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.
*/
class SubArrWLessProduct
{
public:
	SubArrWLessProduct() {}

	int NumOfSubArr_SlidingWindow(std::vector<int> & v, int k)
	{
		if (k < 2) return 0;
		//sliding window
		int N = v.size();
		int left = 0;
		int product = 1;
		int res = 0;
		for (int right = 0; right < N; ++right)
		{
			product *= v[right];
			while (left <= right && product >= k)
			{
				product /= v[left];
				++left;
			}
			if (left <= right)
				res += right - left + 1;
		}
		return res;
	}
};
#endif
