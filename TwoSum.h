#ifndef TWO_SUM_H
#define TWO_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
Leetcode: Two Sum
// Given an array of integers, find two numbers such that they add up to a
// specific target number.
//
// The function twoSum should return indices of the two numbers such that they
// add up to the target,
// where index1 must be less than index2.
// Please note that your returned answers (both index1 and index2) are not
// zero-based.
//
// You may assume that each input would have exactly one solution.
//
// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2
//
// Complexity:
// Hash table, O(n) time, O(n) space
// Greedy (Sort and Scan), O(nlogn) time, O(n) space

TwoSum II
Given an array of integers that is already sorted in ascending order
, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target
, where index1 must be less than index2. 
Please note that your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution.
Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
Greedy: O(n) time, O(1) space

Two Sum III
http://betterpoetrythancode.blogspot.tw/2014/12/two-sum-iii-data-structure-design.html
Design and implement a TwoSum class. It should support the following operations: add and find.
add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

Add: O(1) time
Find: O(n) time
Space: O(d), where d is the number of distinct entries
*/

class TwoSum
{
public:
	TwoSum(){}
	~TwoSum(){}
	//enumerate all possible pairs: O(n^2) time, time limit exceeded
	std::vector<int> FindPairIndex_BruteForce(const std::vector<int> & nums, int target)
	{
		int N = nums.size();
		std::vector<int> res(2, -1);
		bool found = false;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (nums[i] + nums[j] == target)
				{
					res[0] = i + 1;
					res[1] = j + 1;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}

		std::cout << "TwoSum FindPair_BruteForce for \"" << target << "\" from \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> FindPairIndex_HashTable(const std::vector<int> & numbers, int target)
	{
		int N = numbers.size();
		std::unordered_map<int, int> table;//key: entry, value: index
		std::vector<int> res(2, -1);
		for (int i = 0; i < N; ++i)
		{
			if (table.find(target - numbers[i]) == table.end())
			{
				table[numbers[i]] = i + 1;
			}
			else
			{
				res[0] = std::min(i + 1, table[target - numbers[i]]);
				res[1] = std::max(i + 1, table[target - numbers[i]]);
				break;
			}
		}

		std::cout << "TwoSum FindPair_HashTable for \"" << target << "\" from \"" << Debug::ToStr1D<int>()(numbers) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> FindPairIndex_HashTable2(const std::vector<int> & numbers, int target)
	{
		int N = numbers.size();
		std::unordered_map<int, int> table;//key: entry, value: index
		for (int i = 0; i < N; ++i)
			table[numbers[i]] = i;
		std::vector<int> res(2, -1);
		for (int i = 0; i < N; ++i)
		{
			int num = target - numbers[i];//find the corresponding num of numbers[i]
			if (table.count(num) && i != table[num])//if "num exists in table" and "num is not itself"
			{
				res[0] = i + 1;//index + 1 for the special requirement
				res[1] = table[num] + 1;//index + 1 for the special requirement
				if (res[0] > res[1])
					std::swap(res[0], res[1]);
				break;
			}
		}

		std::cout << "TwoSum FindPair_HashTable2 for \"" << target << "\" from \"" << Debug::ToStr1D<int>()(numbers) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> FindPairIndex_Sort_Greedy(const std::vector<int> & numbers, int target)
	{
		int N = numbers.size();
		std::vector<int> numIndex;//use a sorted numbers' index vector to avoid sorting on numbers directly
		for (int i = 0; i < N; ++i)
			numIndex.push_back(i);
		std::sort(std::begin(numIndex), std::end(numIndex)
			, [&numbers](const int i, const int j){return numbers[i] < numbers[j]; });

		std::vector<int> res(2, -1);
		int start = 0;
		int end = N - 1;
		while (start < end)
		{
			int sum = numbers[numIndex[start]] + numbers[numIndex[end]];
			if (sum < target)
				++start;
			else if (sum > target)
				--end;
			else
			{
				res[0] = numIndex[start] + 1;//index + 1 for the special requirement
				res[1] = numIndex[end] + 1;//index + 1 for the special requirement
				if (res[0] > res[1])
					std::swap(res[0], res[1]);
				break;
			}
		}

		std::cout << "TwoSum FindPair_Sort_Greedy for \"" << target << "\" from \"" << Debug::ToStr1D<int>()(numbers) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	bool ExistPairSumTo0_Sort_Greedy(std::vector<int> v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		std::sort(v.begin(), v.end(), std::less<int>());
		//std::cout << "TwoSum Sorted: " << Debug::ToStr1D<int>()(v) << std::endl;

		int start = 0;
		int end = v.size() - 1;
		bool res = false;
		while (start < end)
		{
			int sum = v[start] + v[end];

			if (sum > 0)
				--end;//sum is too big => shift end ptr to left
			else if (sum < 0)
				++start;//sum is too small => shift start ptr to right
			else//sum == 0
			{
				res = true;
				break;
			}
		}

		std::ostringstream oss;
		if (res)
			oss << "[" << v[start] << "," << v[end] << "]";
		else
			oss << "N/A";
		std::cout << "TwoSum ExistPairSumTo0_Sort_Greedy for \"" << before << "\": " << res << " " << oss.str() << std::endl;
		return res;
	}
};

class TwoSumIII
{
	std::unordered_map<int, int> m_map;//first: entry, second: count
public:
	TwoSumIII(){}
	~TwoSumIII(){}

	void Add(const std::vector<int> & v)
	{
		for (const int & i : v)
			this->Add(i);
	}

	void Add(int num)
	{
		if (m_map.find(num) == m_map.end())
		{
			m_map.insert({ num, 1 });
		}
		else
		{
			++m_map[num];
		}
	}

	bool Find(int aSum)
	{
		for (const auto & p : m_map)
		{
			int needed = aSum - p.first;
			if (m_map.find(needed) != m_map.end())
			{
				if (needed == p.first && m_map[needed] < 2)
					continue;

				std::cout << "TwoSumIII Find \"" << aSum << "\": " << true << std::endl;
				return true;
			}
		}

		std::cout << "TwoSumIII Find \"" << aSum << "\": " << false << std::endl;
		return false;
	}

	void Print()
	{
		std::cout << "TwoSumIII: " << Debug::ToStr1D<int>()(m_map) << std::endl;
	}
};

//given an integer array, count number of pairs whose sum equal to k.
//pairs with same values but from different index are counted separated
//{1,1,1}, k=2: there are 3 pairs not 1 pair
class CountPairWSumEqualK
{
public:
	CountPairWSumEqualK(){}

	int HashMap(const std::vector<int> & v, int k)
	{
		int N = v.size();
		std::unordered_map<int, int> count;//<entry, count>
		for (int i = 0; i < N; ++i)
			++count[v[i]];
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			if (count.count(k-v[i]))
				res += count[k-v[i]];
			if (v[i]+v[i] == k)
				--res;
		}
		//now res is twice count
		res /= 2;

		std::cout << "TwoSum CountPairSumEqualK HashMap for \"" << Debug::ToStr1D<int>()(v) << "\", k=" << k << ": " << res << std::endl;
		return res;
	}
};
/*
TwoSum ExistPairSumTo0_Sort_Greedy for "3, -6, -4, 2, -7, 9, 4, 1, 2": 1 [-4,4]
TwoSum FindPair_BruteForce for "7" from "6, 4, -3, 0, 3, 7": 2, 5
TwoSum FindPair_HashTable for "7" from "6, 4, -3, 0, 3, 7": 2, 5
TwoSum FindPair_HashTable2 for "7" from "6, 4, -3, 0, 3, 7": 2, 5
TwoSum FindPair_Sort_Greedy for "7" from "6, 4, -3, 0, 3, 7": 4, 6
TwoSumIII: [4,1], [8,2], [3,2], [5,2], [2,1], [10,2]
TwoSumIII Find "5": 1
TwoSumIII Find "18": 1
TwoSum CountPairSumEqualK HashMap for "1, 1, 1", k=2: 3
*/
#endif