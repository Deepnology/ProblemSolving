#ifndef RANGE_SUM_COUNT_H
#define RANGE_SUM_COUNT_H
#include <iostream>
#include <vector>
#include <set>
#include "Debug.h"
/*
Leetcode: Count of Range Sum
Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i <= j), inclusive.
Note:
A naive algorithm of O(n^2) is trivial. You MUST do better than that.
Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.

see also CountSubArrWSumEqualK.h, ClosestSubArraySum.h, MaxSubMatrixSumNoGreaterThanK.h (SortedPrefixSums)
*/
class RangeSumCount
{
public:
	RangeSumCount() {}
	~RangeSumCount() {}

	int Naive(const std::vector<int> & v, int lower, int upper)//O(n^2) time
	{
		int N = v.size();
		std::vector<long long> prefixSums(N, 0);
		for (int i = 0; i < N; ++i)
			prefixSums[i] = v[i] + (i == 0 ? 0 : prefixSums[i - 1]);

		//enumerate all possible range pairs
		int count = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i; j < N; ++j)
			{
				long long subarrSum = prefixSums[j] - (i == 0 ? 0 : prefixSums[i - 1]);
				if ((long long)lower <= subarrSum && subarrSum <= (long long)upper)
					++count;
			}
		}

		std::cout << "RangeSumCount Naive for \"" << Debug::ToStr1D<int>()(v) << "\", \"[" << lower << ", " << upper << "]\": " << count << std::endl;
		return count;
	}

	int SortedPrefixSums(const std::vector<int> & v, int lower, int upper)
	{
		int N = v.size();
		std::multiset<long long> prefixSums;//sorted prefixSums allowing duplicates
		prefixSums.insert(0);//add an extra 0 in case of searching for a negative value or a value equal to lower or upper will return a lb or ub pointing to it
		long long prefixSum = 0;
		int count = 0;
		for (int i = 0; i < N; ++i)//O(nlogn) time
		{
			prefixSum += v[i];
			count += std::distance(prefixSums.lower_bound(prefixSum - upper), prefixSums.upper_bound(prefixSum - lower));//count num of prefixSums that are in the range of [curPrefixSum-upper, curPrefixSum-lower) and accumulate
			prefixSums.insert(prefixSum);
		}

		std::cout << "RangeSumCount SortedPrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\", \"[" << lower << ", " << upper << "]\": " << count << std::endl;
		return count;
	}

	int ModifiedMergeSort(const std::vector<int> & v, int lower, int upper)
	{
		return 0;
	}

	//special case to count number of subarray sums that are equal to a tgtSum
	int SortedPrefixSums(const std::vector<int> & v, int tgtSum)
	{
		int N = v.size();
		std::multiset<long long> prefixSums;//sorted prefixSums allowing duplicates
		prefixSums.insert(0);//add an extra 0 in case of searching for a negative value or a value equal to tgtSum will return a lb or ub pointing to it
		long long prefixSum = 0;
		int count = 0;
		for (int i = 0; i < N; ++i)//O(nlogn) time
		{
			prefixSum += v[i];//include v[i] to curPrefixSum
			count += std::distance(prefixSums.lower_bound(prefixSum - tgtSum), prefixSums.upper_bound(prefixSum - tgtSum));//count num of prefixSums that are equal to curPrefixSum-tgtSum (num of subarray sums equal to tgtSum including v[i]) and accumulate
			
			std::cout << i << ": add " << std::distance(prefixSums.lower_bound(prefixSum - tgtSum), prefixSums.upper_bound(prefixSum - tgtSum)) << std::endl;

			prefixSums.insert(prefixSum);
		}

		std::cout << "RangeSumCount SpecialCaseForSingleTgtSum SortedPrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\", \"[" << tgtSum << "]\": " << count << std::endl;
		return count;
	}
	struct Less
	{
		bool operator()(const std::pair<long long, int> & a, const std::pair<long long, int> & b) const
		{
			return a.first == b.first ? a.second < b.second : a.first < b.first;
		}
	};
	std::vector<std::pair<int, int>> FindAll_SortedPrefixSums(const std::vector<int> & v, int tgtSum)
	{
		int N = v.size();
		std::multiset<std::pair<long long, int>, Less> prefixSums;//first: sorted prefixSums allowing duplicates, second: indices
		prefixSums.insert({ 0,-1 });//add an extra 0
		long long prefixSum = 0;
		std::vector<std::pair<int, int>> res;//<startIdx, endIdx>
		for (int i = 0; i < N; ++i)//O(nlogn) time
		{
			prefixSum += v[i];//include v[i] to curPrefixSum
			auto lb = prefixSums.lower_bound({ prefixSum - tgtSum, 0 });
			auto ub = prefixSums.upper_bound({ prefixSum - tgtSum, 0 });
			for (auto itr = lb; itr != ub; ++itr)
				res.push_back({ itr->second + 1, i });//<startIdx, endIdx>

			std::string ubstr = ub == prefixSums.end() ? "end" : std::to_string(ub->first) + "," + std::to_string(ub->second);
			std::cout << this->MultisetToStr(prefixSums) << " => " << std::distance(lb, ub) << "     (" << prefixSum << "-" << tgtSum << "'s lb=[" << lb->first << "," << lb->second << "] ub=[" << ubstr << "])" << std::endl;

			prefixSums.insert({ prefixSum, i });
		}

		std::cout << "RangeSumCount SpecialCaseForSingleTgtSum FindAll_SortedPrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\", \"[" << tgtSum << "]\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	std::string MultisetToStr(const std::multiset<std::pair<long long, int>, Less> & s)
	{
		std::ostringstream oss;
		if (s.empty())
			return oss.str();
		std::multiset<std::pair<long long, int>>::const_iterator last = s.end();
		--last;
		for (std::multiset<std::pair<long long, int>>::const_iterator i = s.begin(); i != s.end(); ++i)
		{
			oss << "[" << i->first << "," << i->second << "]";
			if (i != last)
				oss << ", ";
		}
		return oss.str();
	}
};
/*
RangeSumCount Naive for "-2, 5, -1", "[-2, 2]": 3
RangeSumCount SortedPrefixSums for "-2, 5, -1", "[-2, 2]": 3
0: add 0
1: add 2
2: add 2
3: add 0
4: add 2
5: add 3
6: add 3
7: add 3
8: add 1
RangeSumCount SpecialCaseForSingleTgtSum SortedPrefixSums for "0, 1, 0, -2, 2, 1, 0, 0, -2", "[1]": 16
[0,-1] => 0     (0-1's lb=[0,-1] ub=[0,-1])
[0,-1], [0,0] => 2     (1-1's lb=[0,-1] ub=[end])
[0,-1], [0,0], [1,1] => 2     (1-1's lb=[0,-1] ub=[1,1])
[0,-1], [0,0], [1,1], [1,2] => 0     (-1-1's lb=[0,-1] ub=[0,-1])
[-1,3], [0,-1], [0,0], [1,1], [1,2] => 2     (1-1's lb=[0,-1] ub=[1,1])
[-1,3], [0,-1], [0,0], [1,1], [1,2], [1,4] => 3     (2-1's lb=[1,1] ub=[end])
[-1,3], [0,-1], [0,0], [1,1], [1,2], [1,4], [2,5] => 3     (2-1's lb=[1,1] ub=[2,5])
[-1,3], [0,-1], [0,0], [1,1], [1,2], [1,4], [2,5], [2,6] => 3     (2-1's lb=[1,1] ub=[2,5])
[-1,3], [0,-1], [0,0], [1,1], [1,2], [1,4], [2,5], [2,6], [2,7] => 1     (0-1's lb=[-1,3] ub=[0,-1])
RangeSumCount SpecialCaseForSingleTgtSum FindAll_SortedPrefixSums for "0, 1, 0, -2, 2, 1, 0, 0, -2", "[1]": [0,1], [1,1], [0,2], [1,2], [0,4], [1,4], [2,5], [3,5], [5,5], [2,6], [3,6], [5,6], [2,7], [3,7], [5,7], [4,8]
*/
#endif
