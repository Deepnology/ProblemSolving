#ifndef PATCHING_ARRAY_H
#define PATCHING_ARRAY_H
#include "Debug.h"
/*
Leetcode: Patching Array
Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array.
Return the minimum number of patches required.
Example 1:
nums = [1, 3], n = 6
Return 1.
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.

Example 2:
nums = [1, 5, 10], n = 20
Return 2.
The two patches can be [2, 4].
Example 3:
nums = [1, 2, 2], n = 5
Return 0.

Assume the combination sum of first k numbers in nums can reach any number in [1,total),
if we add a nextNum where nextNum<=total, the combination sum of the k+1 numbers can reach any number in [1,total+nextNum).
The special case is when nextNum==total, then the combination sum of the k+1 numbers can reach any number in [1,total*2).
So if the (k+1)th num in nums is <= total, it goes to the above case.
Otherwise, if the (k+1)th num in nums is > total, or there is no (k+1)th num, we need to add a new number such that the new combination sum can reach any number in [1,total+newNum).
The max new number to add that can minimize total new numbers is "total" itself, so the new combination sum can reach any number in [1,total*2).

see also MinNonSubsetSumSortedArray.h
*/
class PatchingArray
{
public:
	PatchingArray() {}
	~PatchingArray() {}

	int CountMinPatches(const std::vector<int> & nums, int n)//greedy algorithm
	{
		int N = nums.size();
		int res = 0;
		long total = 1;//the range in [1,total) can always be reached
		int idx = 0;
		while (total <= n)
		{
			if (idx < N && nums[idx] <= total)//if nums[idx]<=total: including nums[idx] can reach [1,total+nums[idx]). special case when nums[idx]==total: including nums[idx] can reach [1,total*2)
			{
				std::cout << nums[idx] << "<=" << total << ": include \"" << nums[idx] << "\": [1," << total + nums[idx] << ")" << std::endl;

				total += nums[idx];
				++idx;
			}
			else//if nums[idx]>total: need to add in a new number "total" (which is the max num we can add) to nums, and then we can reach [1,total*2)
			{
				if (idx < N)
					std::cout << nums[idx] << ">" << total << ": add a new \"" << total << "\": [1," << total * 2 << ")" << std::endl;
				else
					std::cout << "empty: add a new \"" << total << "\": [1," << total * 2 << ")" << std::endl;

				total *= 2;
				++res;
			}
		}

		std::cout << "PatchingArray CountMinPatches for \"" << Debug::ToStr1D<int>()(nums) << "\", n=\"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
1<=1: include "1": [1,2)
4>2: add a new "2": [1,4)
4<=4: include "4": [1,8)
10>8: add a new "8": [1,16)
10<=16: include "10": [1,26)
empty: add a new "26": [1,52)
PatchingArray CountMinPatches for "1, 4, 10", n="50": 3
1<=1: include "1": [1,2)
4>2: add a new "2": [1,4)
4<=4: include "4": [1,8)
10>8: add a new "8": [1,16)
10<=16: include "10": [1,26)
empty: add a new "26": [1,52)
empty: add a new "52": [1,104)
PatchingArray CountMinPatches for "1, 4, 10", n="52": 4
1<=1: include "1": [1,2)
2<=2: include "2": [1,4)
5>4: add a new "4": [1,8)
5<=8: include "5": [1,13)
6<=13: include "6": [1,19)
20>19: add a new "19": [1,38)
20<=38: include "20": [1,58)
PatchingArray CountMinPatches for "1, 2, 5, 6, 20", n="50": 2
1<=1: include "1": [1,2)
2<=2: include "2": [1,4)
4<=4: include "4": [1,8)
11>8: add a new "8": [1,16)
11<=16: include "11": [1,27)
30>27: add a new "27": [1,54)
PatchingArray CountMinPatches for "1, 2, 4, 11, 30", n="50": 2
empty: add a new "1": [1,2)
empty: add a new "2": [1,4)
empty: add a new "4": [1,8)
empty: add a new "8": [1,16)
empty: add a new "16": [1,32)
empty: add a new "32": [1,64)
PatchingArray CountMinPatches for "", n="50": 6
*/
#endif
