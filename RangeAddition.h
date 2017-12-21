#ifndef RANGE_ADDITION_H
#define RANGE_ADDITION_H
#include "Debug.h"
/*
Leetcode: Range Addition
Assume you have an array of length n initialized with all 0's and are given k update operations.
Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.
Return the modified array after all k operations were executed.

Example:
Given:
length = 5,
updates = [
[1,  3,  2],
[2,  4,  3],
[0,  2, -2]
]
Output:
[-2, 0, 3, 5, 3]

Explanation:
Initial state:
[ 0, 0, 0, 0, 0 ]
After applying operation [1, 3, 2]:
[ 0, 2, 2, 2, 0 ]
After applying operation [2, 4, 3]:
[ 0, 2, 5, 5, 3 ]
After applying operation [0, 2, -2]:
[-2, 0, 3, 5, 3 ]

Hint:
1. Thinking of using advanced data structures? You are thinking it too complicated.
2. For each update operation, do you really need to update all elements between i and j?
3. Update only the first and end element is sufficient.
4. The optimal time complexity is O(k + n) and uses O(1) extra space.

Init an res array with all 0s.
For each range increment, add the increment to res[start] and -increment to res[end+1].
For each num in res, replace it with its prefixSum.

see also RangeSumQueryWPrefixSums.h (RangeSumQueryWPrefixSums1DMutable)

Leetcode: Range Addition II
Given an m * n matrix M initialized with all 0's and several update operations.
Operations are represented by a 2D array, and each operation is represented by an array with two positive integers a and b, which means M[i][j] should be added by one for all 0 <= i < a and 0 <= j < b.
You need to count and return the number of maximum integers in the matrix after performing all the operations.
Example 1:
Input:
m = 3, n = 3
operations = [[2,2],[3,3]]
Output: 4
Explanation:
Initially, M =
[[0, 0, 0],
[0, 0, 0],
[0, 0, 0]]
After performing [2,2], M =
[[1, 1, 0],
[1, 1, 0],
[0, 0, 0]]
After performing [3,3], M =
[[2, 2, 1],
[2, 2, 1],
[1, 1, 1]]
So the maximum integer in M is 2, and there are four of it in M. So return 4.
*/
class RangeAddition
{
public:
	RangeAddition() {}
	~RangeAddition() {}

	std::vector<int> getModifiedArray(int length, const std::vector<std::vector<int>> & updates)
	{
		std::vector<int> res(length, 0);
		int k = updates.size();
		for (int i = 0; i < k; ++i)
		{
			res[updates[i][0]] += updates[i][2]; //incr at start
			if (updates[i][1] + 1 < length)
				res[updates[i][1] + 1] -= updates[i][2];//decr at end+1
		}


		//compute prefixSum
		for (int i = 1; i < length; ++i)
			res[i] += res[i - 1];

		Debug::Print2D<int>()(updates, false);
		std::cout << "RangeAddition for length=\"" << length << "\" and above updates: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//Range Addition II
	int FindCountOfMaxNum(int m, int n, std::vector<std::vector<int>> & ops)
	{
		//the max number must be matrix[0][0]
		//find the smallest upper left rectangle that is overlapped by all operations
		int M = m;
		int N = n;
		for (auto & v : ops)
		{
			M = std::min(M, v[0]);
			N = std::min(N, v[1]);
		}
		return M*N;
	}
};
/*
[rY][cX]
Row#0	= 1, 3, 2
Row#1	= 2, 4, 3
Row#2	= 0, 2, -2

RangeAddition for length="5" and above updates: -2, 0, 3, 5, 3
*/
#endif
