#ifndef TWO_DIFFERENCE_H
#define TWO_DIFFERENCE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
http://www.careercup.com/question?id=9307474
http://stackoverflow.com/questions/10450462/find-pair-of-numbers-whose-difference-is-an-input-value-k-in-an-unsorted-array
http://stackoverflow.com/questions/20171856/best-way-to-find-the-number-of-pairs-in-an-array-whose-difference-is-k
http://www.geeksforgeeks.org/count-pairs-difference-equal-k/
Given an array of DISTINCT integers and an integer K, find all pair of integers such that their difference equals to K.

Sort and Greedy: O(nlogn) time, O(1) space
See also MinPairDiff2SortedArrays.h, TwoClosestPoints.h, ClosestSubArraySum.h

Leetcode: K-diff pairs in an array
Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array.
Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.
Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).


Leetcode: Find K-th Smallest Pair Distance
Given an integer array, return the k-th smallest distance among all the pairs.
The distance of a pair (A, B) is defined as the absolute difference between A and B.
Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.

*/
class TwoDifference
{
public:
	TwoDifference(){}
	~TwoDifference(){}

	std::vector<std::pair<int, int>> Sort_Greedy(std::vector<int> v, int K)//best
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::sort(v.begin(), v.end(), std::less<int>());
		std::vector<std::pair<int, int>> res;

		int first = 0;
		int second = 1;
		while (second < N)
		{
			if (v[second] - v[first] == K)
			{
				res.push_back({ v[first], v[second] });
				++first;
				++second;
			}
			else if (v[second] - v[first] > K)
			{
				++first;
				if (first == second)
					++second;
			}
			else
			{
				++second;
			}
		}

		std::cout << "TwoDifference Sort_Greedy for \"" << K << ", From " << before << "\": " << Debug::ToStr1D<int>()(res) << ". In total: " << res.size() << std::endl;
		return res;
	}

	std::vector<std::pair<int, int>> Sort_BinarySearch(std::vector<int> v, int K)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::sort(v.begin(), v.end(), std::less<int>());
		std::vector<std::pair<int, int>> res;
		
		for (int i = 0; i < N; ++i)
		{
			auto itr = std::lower_bound(v.begin() + i + 1, v.end(), v[i] + K);
			if (itr != v.end() && *itr == v[i] + K)
				res.push_back({ v[i], *itr });
		}

		std::cout << "TwoDifference Sort_BinarySearch for \"" << K << ", From " << before << "\": " << Debug::ToStr1D<int>()(res) << ". In total: " << res.size() << std::endl;
		return res;
	}

	std::vector<std::pair<int, int>> HashTable(std::vector<int> v, int K)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::unordered_set<int> set;
		for (const int & i : v)
			set.insert(i);
		std::vector<std::pair<int, int>> res;
		
		for (const int & i : v)
		{
			if (set.find(i) != set.end())
			{
				if (set.find(i - K) != set.end())
					res.push_back({ i - K, i });
				if (set.find(i + K) != set.end())
					res.push_back({ i, i + K });
				set.erase(i);
			}
		}

		std::cout << "TwoDifference HashTable for \"" << K << ", From " << before << "\": " << Debug::ToStr1D<int>()(res) << ". In total: " << res.size() << std::endl;
		return res;
	}


	//Leetcode: K-diff pairs in array: count number of unique k-diff pairs
	int CountUniqueKDiffPairs_SortGreedy(std::vector<int> & nums, int k)
	{
		std::sort(nums.begin(), nums.end());
		int N = nums.size();
		int i = 0;
		int j = 1;
		int res = 0;
		while (j < N)
		{
			int diff = nums[j] - nums[i];
			if (diff == k)
			{
				++res;
				++i;
				while (i < N && nums[i - 1] == nums[i])//skip duplicates
					++i;
				j = std::max(j + 1, i + 1);
			}
			else if (diff < k)
			{
				++j;
			}
			else
			{
				++i;
				if (i == j)
					++j;
			}
		}
		return res;
	}
	int CountUniqueKDiffPairs_HashSet(std::vector<int> & nums, int k)
	{
		if (k < 0) return 0;
		std::unordered_set<int> visit;
		std::unordered_set<int> pairBegin;
		int N = nums.size();
		for (int i = 0; i < N; ++i)
		{
			if (visit.count(nums[i] - k))
				pairBegin.insert(nums[i] - k);
			if (visit.count(nums[i] + k))
				pairBegin.insert(nums[i]);
			visit.insert(nums[i]);
		}
		return pairBegin.size();
	}


	//Leetcode: Find K-th Smallest Pair Distance
	int KthSmallestPairDifference_SortBinarySearch(std::vector<int>& nums, int k)
	{
		int N = nums.size();
		std::sort(nums.begin(), nums.end());
		int loDiff = 0;//min diff must be 0
		int hiDiff = nums.back() - nums.front();//max diff must be "last - first" in a sorted array
		//now binary search (lower bound) the k-th smallest diff in between loDiff and hiDiff
		while (loDiff <= hiDiff)
		{
			int midDiff = (loDiff + hiDiff) / 2;
			//now count number of pairs whose diff is <= midDiff
			int count = 0;
			for (int i = 0; i < N; ++i)
			{
				int j = i + 1;
				while (j < N && nums[j] - nums[i] <= midDiff)
					++j;
				count += j - i - 1;
			}
			if (count >= k)
				hiDiff = midDiff - 1;
			else
			{
				loDiff = midDiff + 1;
			}
		}
		return loDiff;
	}
};
/*
TwoDifference Sort_Greedy for "18, From 59, 14, 5, 8, 54, 45, 46, 30, 41, 47, 57, 60, 23, 1, 9, 12, 33, 18, 11, 3, 17, 38, 24, 19, 56, 40, 15, 49, 16, 13, 26, 10, 37, 28, 4": [1,19], [5,23], [8,26], [10,28], [12,30], [15,33], [19,37], [23,41], [28,46], [38,56], [41,59]. In total: 11
TwoDifference Sort_BinarySearch for "18, From 59, 14, 5, 8, 54, 45, 46, 30, 41, 47, 57, 60, 23, 1, 9, 12, 33, 18, 11, 3, 17, 38, 24, 19, 56, 40, 15, 49, 16, 13, 26, 10, 37, 28, 4": [1,19], [5,23], [8,26], [10,28], [12,30], [15,33], [19,37], [23,41], [28,46], [38,56], [41,59]. In total: 11
TwoDifference HashTable for "18, From 59, 14, 5, 8, 54, 45, 46, 30, 41, 47, 57, 60, 23, 1, 9, 12, 33, 18, 11, 3, 17, 38, 24, 19, 56, 40, 15, 49, 16, 13, 26, 10, 37, 28, 4": [41,59], [5,23], [8,26], [28,46], [12,30], [23,41], [1,19], [15,33], [38,56], [19,37], [10,28]. In total: 11
TwoDifference Sort_Greedy for "14, From 4, 47, 20, 9, 50, 37, 45, 51, 18, 16, 19, 17, 28, 24, 15, 6, 29, 36, 33, 52, 34, 7, 43, 54, 11, 40, 3, 32, 26, 1, 13, 5, 58, 59, 53": [1,15], [3,17], [4,18], [5,19], [6,20], [15,29], [18,32], [19,33], [20,34], [26,40], [29,43], [33,47], [36,50], [37,51], [40,54], [45,59]. In total: 16
TwoDifference Sort_BinarySearch for "14, From 4, 47, 20, 9, 50, 37, 45, 51, 18, 16, 19, 17, 28, 24, 15, 6, 29, 36, 33, 52, 34, 7, 43, 54, 11, 40, 3, 32, 26, 1, 13, 5, 58, 59, 53": [1,15], [3,17], [4,18], [5,19], [6,20], [15,29], [18,32], [19,33], [20,34], [26,40], [29,43], [33,47], [36,50], [37,51], [40,54], [45,59]. In total: 16
TwoDifference HashTable for "14, From 4, 47, 20, 9, 50, 37, 45, 51, 18, 16, 19, 17, 28, 24, 15, 6, 29, 36, 33, 52, 34, 7, 43, 54, 11, 40, 3, 32, 26, 1, 13, 5, 58, 59, 53": [4,18], [33,47], [6,20], [20,34], [36,50], [37,51], [45,59], [18,32], [5,19], [19,33], [3,17], [1,15], [15,29], [29,43], [40,54], [26,40]. In total: 16
TwoDifference Sort_Greedy for "8, From 51, 36, 27, 48, 19, 46, 33, 37, 30, 57, 1, 59, 7, 47, 22, 14, 26, 24, 21, 50, 41, 17, 42, 16, 31, 55, 60, 18, 20, 53, 12, 39, 32, 35, 2": [12,20], [14,22], [16,24], [18,26], [19,27], [22,30], [24,32], [27,35], [31,39], [33,41], [39,47], [42,50], [47,55], [51,59]. In total: 14
TwoDifference Sort_BinarySearch for "8, From 51, 36, 27, 48, 19, 46, 33, 37, 30, 57, 1, 59, 7, 47, 22, 14, 26, 24, 21, 50, 41, 17, 42, 16, 31, 55, 60, 18, 20, 53, 12, 39, 32, 35, 2": [12,20], [14,22], [16,24], [18,26], [19,27], [22,30], [24,32], [27,35], [31,39], [33,41], [39,47], [42,50], [47,55], [51,59]. In total: 14
TwoDifference HashTable for "8, From 51, 36, 27, 48, 19, 46, 33, 37, 30, 57, 1, 59, 7, 47, 22, 14, 26, 24, 21, 50, 41, 17, 42, 16, 31, 55, 60, 18, 20, 53, 12, 39, 32, 35, 2": [51,59], [19,27], [27,35], [33,41], [22,30], [39,47], [47,55], [14,22], [18,26], [16,24], [24,32], [42,50], [31,39], [12,20]. In total: 14
TwoDifference Sort_Greedy for "16, From 33, 44, 60, 4, 53, 57, 59, 52, 42, 16, 43, 46, 31, 29, 8, 50, 34, 54, 9, 27, 6, 1, 48, 55, 40, 20, 15, 13, 19, 22, 26, 2, 7, 37, 36": [4,20], [6,22], [13,29], [15,31], [20,36], [26,42], [27,43], [34,50], [36,52], [37,53], [43,59], [44,60]. In total: 12
TwoDifference Sort_BinarySearch for "16, From 33, 44, 60, 4, 53, 57, 59, 52, 42, 16, 43, 46, 31, 29, 8, 50, 34, 54, 9, 27, 6, 1, 48, 55, 40, 20, 15, 13, 19, 22, 26, 2, 7, 37, 36": [4,20], [6,22], [13,29], [15,31], [20,36], [26,42], [27,43], [34,50], [36,52], [37,53], [43,59], [44,60]. In total: 12
TwoDifference HashTable for "16, From 33, 44, 60, 4, 53, 57, 59, 52, 42, 16, 43, 46, 31, 29, 8, 50, 34, 54, 9, 27, 6, 1, 48, 55, 40, 20, 15, 13, 19, 22, 26, 2, 7, 37, 36": [44,60], [4,20], [37,53], [43,59], [36,52], [26,42], [27,43], [15,31], [13,29], [34,50], [6,22], [20,36]. In total: 12
*/
#endif