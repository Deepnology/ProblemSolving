#ifndef CREATE_MAX_NUMBER_FROM_2_ARRAYS_H
#define CREATE_MAX_NUMBER_FROM_2_ARRAYS_H
#include "Debug.h"
/*
Leetcode: Create Maximum Number
Given two arrays of length m and n with digits 0-9 representing two numbers.
Create the maximum number of length k <= m + n from digits of the two.
The relative order of the digits from the same array must be preserved.
Return an array of the k digits.
You should try to optimize your time and space complexity.
Example 1:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]
Example 2:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]
Example 3:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]

Enumerate all possible cases to split k into nums1 and nums2: k1 in [max(0,k-len2),min(k,len1)], k2=k-k1. (see also KthSmallestElement2SortedArrays.h)
Compute 2 sorted stacks in decending order (max number) from nums1 with k1 and nums2 with k2.
Merge the 2 sorted stacks in decending order with greedy algorithm.
Keep track of the max decending order number of the merged sorted stacks.
Be careful on the greedy merge routine where the comparison to get next large element is based on the comparison of the nums array from current index to end.
*/
class CreateMaxNumberFrom2Arrays
{
public:
	CreateMaxNumberFrom2Arrays() {}
	~CreateMaxNumberFrom2Arrays() {}

	std::vector<int> UseSortedStkAndMerge(const std::vector<int> & nums1, const std::vector<int> & nums2, int k)
	{
		int len1 = nums1.size();
		int len2 = nums2.size();
		std::vector<int> res;

		//enumerate all possible cases to split k into nums1 and nums2
		//len is the length in nums1
		for (int len = std::max(0, k - len2); len <= k && len <= len1; ++len)
		{
			std::vector<int> maxNum1 = this->GetSortedStk(nums1, len);//get max number from nums1 with len
			std::vector<int> maxNum2 = this->GetSortedStk(nums2, k - len);//get max number from nums2 with k-len
			std::vector<int> curRes = this->Merge(maxNum1, maxNum2);//merge the above 2
			std::cout << "Merge above 2 arrays: " << Debug::ToStr1D<int>()(curRes) << std::endl;
			if (res.empty())
				res.swap(curRes);
			else if (this->isGreater(curRes, 0, res, 0))
				res.swap(curRes);
		}

		std::cout << "CreateMaxNumberFrom2Arrays UseSortedStkAndMerge for \"" << Debug::ToStr1D<int>()(nums1) << "\", \"" << Debug::ToStr1D<int>()(nums2) << "\", len=\"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	std::vector<int> GetSortedStk(const std::vector<int> & v, int len)
	{
		int N = v.size();
		std::vector<int> sortedStk;//sorted in decreasing order
		
		for (int i = 0; i < N; ++i)
		{
			//pop out all elements from back as long as we can add enough elements later to reach len
			while (!sortedStk.empty() && (int)sortedStk.size() - 1 + N - i >= len  && sortedStk.back() < v[i])
			{
				sortedStk.pop_back();
			}
			if ((int)sortedStk.size() < len)
				sortedStk.push_back(v[i]);
		}
		std::cout << "GetSortedStk for \"" << Debug::ToStr1D<int>()(v) << "\", len=\"" << len << "\": " << Debug::ToStr1D<int>()(sortedStk) << std::endl;
		return sortedStk;
	}
	std::vector<int> Merge(const std::vector<int> & v1, const std::vector<int> & v2)//must be very cautious on equality cases
	{
		int N1 = v1.size();
		int N2 = v2.size();
		int i = 0;
		int j = 0;
		std::vector<int> res;
		while (i < N1 && j < N2)
		{
			if (this->isGreater(v1, i, v2, j))//pay attention to the equality cases
			{
				res.push_back(v1[i++]);
			}
			else
			{
				res.push_back(v2[j++]);
			}
		}
		while (i < N1)
			res.push_back(v1[i++]);
		while (j < N2)
			res.push_back(v2[j++]);
		return res;
	}
	bool isGreater(const std::vector<int> & v1, int i, const std::vector<int> & v2, int j)//compare if v1[i:N-1] is greater than v2[j:M-1]
	{
		int N1 = v1.size();
		int N2 = v2.size();
		while (i < N1 && j < N2 && v1[i] == v2[j])
			++i, ++j;
		if (j == N2)//v2 reaches end: v1 is greater
			return true;
		if (i == N1)//v1 reaches end: v2 is greater
			return false;
		return v1[i] > v2[j];
	}
};
/*
GetSortedStk for "3, 4, 6, 5", len="0":
GetSortedStk for "9, 1, 2, 5, 8, 3", len="5": 9, 2, 5, 8, 3
Merge above 2 arrays: 9, 2, 5, 8, 3
GetSortedStk for "3, 4, 6, 5", len="1": 6
GetSortedStk for "9, 1, 2, 5, 8, 3", len="4": 9, 5, 8, 3
Merge above 2 arrays: 9, 6, 5, 8, 3
GetSortedStk for "3, 4, 6, 5", len="2": 6, 5
GetSortedStk for "9, 1, 2, 5, 8, 3", len="3": 9, 8, 3
Merge above 2 arrays: 9, 8, 6, 5, 3
GetSortedStk for "3, 4, 6, 5", len="3": 4, 6, 5
GetSortedStk for "9, 1, 2, 5, 8, 3", len="2": 9, 8
Merge above 2 arrays: 9, 8, 4, 6, 5
GetSortedStk for "3, 4, 6, 5", len="4": 3, 4, 6, 5
GetSortedStk for "9, 1, 2, 5, 8, 3", len="1": 9
Merge above 2 arrays: 9, 3, 4, 6, 5
CreateMaxNumberFrom2Arrays UseSortedStkAndMerge for "3, 4, 6, 5", "9, 1, 2, 5, 8, 3", len="5": 9, 8, 6, 5, 3
GetSortedStk for "2, 5, 6, 4, 4, 0", len="6": 2, 5, 6, 4, 4, 0
GetSortedStk for "7, 3, 8, 0, 6, 5, 7, 6, 2", len="9": 7, 3, 8, 0, 6, 5, 7, 6, 2
Merge above 2 arrays: 7, 3, 8, 2, 5, 6, 4, 4, 0, 6, 5, 7, 6, 2, 0
CreateMaxNumberFrom2Arrays UseSortedStkAndMerge for "2, 5, 6, 4, 4, 0", "7, 3, 8, 0, 6, 5, 7, 6, 2", len="15": 7, 3, 8, 2, 5, 6, 4, 4, 0, 6, 5, 7, 6, 2, 0
*/
#endif
