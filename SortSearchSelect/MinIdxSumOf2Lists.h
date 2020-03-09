#ifndef MIN_IDX_SUM_OF_2_LISTS_H
#define MIN_IDX_SUM_OF_2_LISTS_H
#include "Debug.h"
/*
Leetcode: Minimum Index Sum Of 2 Lists
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.
You need to help them find out their common interest with the least list index sum.
If there is a choice tie between answers, output all of them with no order requirement.
You could assume there always exists an answer.
Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
*/
class MinIdxSumOf2Lists
{
public:
	MinIdxSumOf2Lists() {}

	std::vector<std::string> UseHashMap(std::vector<std::string> & list1, std::vector<std::string> & list2)
	{
		std::vector<std::string> res;
		std::unordered_map<std::string, int> toIdx;//<key, idx>
		
		int N = list1.size();
		for (int i = 0; i < N; ++i)
			toIdx.insert({ list1[i], i });

		int M = list2.size();
		int minSum = INT_MAX;
		for (int i = 0; i < M; ++i)
		{
			if (toIdx.count(list2[i]))//find a common
			{
				int sum = i + toIdx[list2[i]];
				if (sum < minSum)
				{
					minSum = sum;
					res.clear();
					res.push_back(list2[i]);
				}
				else if (sum == minSum)
					res.push_back(list2[i]);
			}
		}
		return res;
	}
};
#endif
