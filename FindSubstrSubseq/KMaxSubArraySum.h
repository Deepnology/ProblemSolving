#ifndef K_MAX_SUB_ARRAY_SUM_H
#define K_MAX_SUB_ARRAY_SUM_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Top 20 coding interview problems 4.6
Given an integer array.
Find the first K largest sub-array sums.
When K == 1, this problem reduces to the normal MaxSubArraySum.h

Algorithm - Use PrefixSum[]:
keep a sortedKMinPrefixSum[] in ascending order.
for i in [1:N-1], prefixSum[i]=prefixSum[i-1]+v[i],
for j in [0:K-1] {curSortedKSubArrSum[j]=prefixSum[i]-sortedKMinPrefixSum[j]},
merge curSortedKSubArrSum[] with resSortedKSubArrSum[] to get first K max SubArrSums and save to resSortedKSubArrSum[],
insert prefixSum[i] to sortedKMinPrefixSum[],
return resSortedKSubArrSum[].

UseSortedKMinPrefixSums: O(K*n) time, O(n) space
*/
class KMaxSubArraySum
{
public:
	KMaxSubArraySum(){}
	~KMaxSubArraySum(){}

	void UseSortedKMinPrefixSums(const std::vector<int> & v, int K)
	{
		int N = v.size();

		//the first k max sums in descending order. <sum<begin,end>>
		std::vector<std::pair<int, std::pair<int, int>>> sortedKMaxSums(K, { INT_MIN, {0, 0} });

		//the first k min prefix sums so far in ascending order. <sum,index>
		std::vector<std::pair<int, int>> sortedKMinPrefixSums(K, { INT_MAX, 0 });

		//the prefix sums
		std::vector<int> prefixSum(N);

		prefixSum[0] = v[0];
		sortedKMinPrefixSums[0].first = prefixSum[0];
		sortedKMinPrefixSums[0].second = 0;
		sortedKMaxSums[0].first = v[0];
		sortedKMaxSums[0].second.first = 0;
		sortedKMaxSums[0].second.second = 0;
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i] = prefixSum[i - 1] + v[i];

			//1. find the first k max subarray sums so far in descending order. <sum<begin,end>>. O(K) time
			std::vector<std::pair<int, std::pair<int, int>>> curSortedKMaxSums(K);
			for (int j = 0; j < K; ++j)
			{
				if (sortedKMinPrefixSums[j].first == INT_MAX)
				{
					curSortedKMaxSums[j].first = INT_MIN;
				}
				else
				{
					curSortedKMaxSums[j].first = prefixSum[i] - sortedKMinPrefixSums[j].first;//max subarray sum
					curSortedKMaxSums[j].second.first = sortedKMinPrefixSums[j].second + 1;//begin
					curSortedKMaxSums[j].second.second = i;//end
				}
			}

			//2. merge 2 sorted array curSortedKMaxSums and sortedKMaxSums: pick the first k max numbers from begin of the two arrays. O(K) time
			int x = 0;
			int y = 0;
			std::vector<std::pair<int, std::pair<int, int>>> mergedKMax(K);
			while (x + y < K)
			{
				if (curSortedKMaxSums[x].first >= sortedKMaxSums[y].first)
				{
					mergedKMax[x + y] = curSortedKMaxSums[x];
					++x;
				}
				else
				{
					mergedKMax[x + y] = sortedKMaxSums[y];
					++y;
				}
			}
			mergedKMax.swap(sortedKMaxSums);

			//3. insert current prefix sum into sortedKMinPrefixSums. O(logK) time
			std::vector<std::pair<int, int>>::iterator itr = std::lower_bound(sortedKMinPrefixSums.begin(), sortedKMinPrefixSums.end(), prefixSum[i]
				, [](const std::pair<int, int> & a, const int & b)->bool
			{
				return a.first < b;
			});
			//std::cout << "lower bound for \"" << prefixSum[i] << "\" in \"" << Debug::ToStr1D<int>()(sortedKMinPrefixSums) << "\": " << itr - sortedKMinPrefixSums.begin() << std::endl;
			sortedKMinPrefixSums.insert(itr, { prefixSum[i], i });
			if ((int)sortedKMinPrefixSums.size() > K)
				sortedKMinPrefixSums.pop_back();
		}

		std::cout << "KMaxSubArraySum UseSortedKMinPrefixSums for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(sortedKMaxSums) << std::endl;
	}
};
/*
KMaxSubArraySum UseSortedKMinPrefixSums for "17" in "-2, 1, -3, 4, -1, 2, 1, -5, 4": [6,(3,6)], [5,(3,8)], [5,(3,5)], [4,(8,8)], [4,(1,6)], [4,(3,3)], [3,(1,8)], [3,(5,6)], [3,(2,6)], [3,(1,5)], [3,(3,4)], [2,(5,8)], [2,(2,8)], [2,(4,6)], [2,(5,5)], [2,(2,5)], [2,(1,3)]
KMaxSubArraySum UseSortedKMinPrefixSums for "17" in "-2, -10, -3, -4, -7, -9, -1, -8, -5": [-1,(6,6)], [-2,(0,0)], [-3,(2,2)], [-4,(3,3)], [-5,(8,8)], [-7,(4,4)], [-7,(2,3)], [-8,(7,7)], [-9,(6,7)], [-9,(5,5)], [-10,(5,6)], [-10,(1,1)], [-11,(3,4)], [-13,(7,8)], [-13,(1,2)], [-14,(6,8)], [-14,(2,4)]
*/
#endif