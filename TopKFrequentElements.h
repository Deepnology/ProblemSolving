#ifndef TOP_K_FREQUENT_ELEMENTS_H
#define TOP_K_FREQUENT_ELEMENTS_H
#include "Debug.h"
/*
Leetcode: Top K Frequent Elements
Given a non-empty array of integers, return the k most frequent elements.
For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].
Note:
You may assume k is always valid, 1 <= k <= number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.


Heap: O(nlogk) time, O(n) space
Use a map<entry,count> to keep track of frequency of each entry.
Use a maxHeap<count,entry> to insert all pairs from map.
Return the top k pairs from maxHeap.

Selection: O(n) ~ O(n^2) time, O(n) time on average. O(n) space
Use a map<entry,count> to keep track of frequency of each entry.
Copy all pairs into an array<count,entry>, then use nth_element to move the (k-1)th count to its correct position after sorted based on count. (k: 1-based, k-1: 0-based)
Return the first k pairs from the array.

BucketSort: O(n) time, O(n) space
*/
class TopKFrequentElements
{
public:
	TopKFrequentElements() {}
	~TopKFrequentElements() {}

	std::vector<int> UseMaxHeap(const std::vector<int> & nums, int k)
	{
		int N = nums.size();
		std::unordered_map<int, int> count;
		for (int i = 0; i < N; ++i)
		{
			++count[nums[i]];
		}
		std::vector<int> res;

		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<std::pair<int, int>>> maxHeap;
		for (const auto & p : count)
		{
			maxHeap.push({p.second, p.first});
		}
		for (int i = 0; i < k; ++i)
		{
			res.push_back(maxHeap.top().second);
			maxHeap.pop();
		}

		std::cout << "TopKFrequentElements UseMaxHeap for \"" << Debug::ToStr1D<int>()(nums) << "\", k=\"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> UseSelection(const std::vector<int> & nums, int k)
	{
		int N = nums.size();
		std::unordered_map<int, int> count;
		for (int i = 0; i < N; ++i)
		{
			++count[nums[i]];
		}
		std::vector<int> res;
		
		std::vector<std::pair<int, int>> select;
		for (const auto & p : count)
			select.push_back({ p.second, p.first });
		std::nth_element(select.begin(), select.begin() + k - 1, select.end(), std::greater<std::pair<int, int>>());
		for (int i = 0; i < k; ++i)
			res.push_back(select[i].second);

		std::cout << "TopKFrequentElements UseSelection for \"" << Debug::ToStr1D<int>()(nums) << "\", k=\"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> UseBucketSort(const std::vector<int> & nums, int k)
	{
		int N = nums.size();
		std::unordered_map<int, int> count;
		for (int i = 0; i < N; ++i)
		{
			++count[nums[i]];
		}
		std::vector<int> res;

		std::vector<std::vector<int>> buckets(N + 1, std::vector<int>());
		for (auto & p : count)
			buckets[p.second].push_back(p.first);
		for (int i = N; i > 0 && (int)res.size() < k; --i)
		{
			int M = buckets[i].size();
			for (int j = 0; j < M && (int)res.size() < k; ++j)
				res.push_back(buckets[i][j]);
		}

		std::cout << "TopKFrequentElements UseBucketSort for \"" << Debug::ToStr1D<int>()(nums) << "\", k=\"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
TopKFrequentElements UseMaxHeap for "1, 1, 1, 2, 2, 3", k="2": 1, 2
TopKFrequentElements UseSelection for "1, 1, 1, 2, 2, 3", k="2": 1, 2
TopKFrequentElements UseBucketSort for "1, 1, 1, 2, 2, 3", k="2": 1, 2
*/
#endif
