#ifndef MIN_MOVES_TO_EQUAL_ARRAY_ELEMENTS_H
#define MIN_MOVES_TO_EQUAL_ARRAY_ELEMENTS_H
#include "Debug.h"
/*
Leetcode: Minimum Moves To Equal Array Elements
Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.
Example:
Input:
[1,2,3]
Output:
3
Explanation:
Only three moves are needed (remember each move increments two elements):
[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

Leetcode: Minimum Moves To Equal Array Elements II
Given a non-empty integer array, find the minimum number of moves required to make all array elements equal
, where a move is incrementing a selected element by 1 or decrementing a selected element by 1.
You may assume the array's length is at most 10,000.
Example:
Input:
[1,2,3]
Output:
2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
*/
class MinMovesToEqualArrayElements
{
public:
	int MinMovesI_IncrNminus1Nums(std::vector<int> & nums)
	{
		//equivalent to subtract 1 from only 1 element at a time until all elements are equal
		//=> all elements will be equal when all elements are equal to the min element
		//=> total subtractions = sum - min * N
		//OR (min+moves)*N = sum+moves*(N-1)
		//=> moves = sum-min*N
		std::string before = Debug::ToStr1D<int>()(nums);
		int N = nums.size();
		int sum = std::accumulate(nums.begin(), nums.end(), 0);
		int min = *std::min_element(nums.begin(), nums.end());

		std::cout << "MinMovesToEqualArrayElements IncrNminus1Nums for \"" << before << "\": " << (sum - min * N) << std::endl;
		return sum - min * N;
	}

	int MinMovesII_IncrDecr1Num_UseMedian(std::vector<int> & nums)
	{
		std::string before = Debug::ToStr1D<int>()(nums);
		int N = nums.size();
		std::nth_element(nums.begin(), nums.begin() + N/2, nums.end());
		int median = nums[N/2];
		int res = 0;
		for (const auto & i : nums)
			res += std::abs(i - median);

		std::cout << "MinMovesToEqualArrayElements IncrDecr1Num UseMedian for \"" << before << "\": " << res << std::endl;
		return res;
	}
	int MinMovesII_IncrDecr1Num_UseSort(std::vector<int> & nums)
	{
		std::string before = Debug::ToStr1D<int>()(nums);
		int N = nums.size();
		std::sort(nums.begin(), nums.end());
		int i = 0;
		int j = N - 1;
		int res = 0;
		while (i < j)
		{
			res += (nums[j--] - nums[i++]);
		}

		std::cout << "MinMovesToEqualArrayElements IncrDecr1Num UseSort for \"" << before << "\": " << res << std::endl;
		return res;
	}
};
/*
MinMovesToEqualArrayElements IncrNminus1Nums for "1, 2, 3": 3
MinMovesToEqualArrayElements IncrDecr1Num UseMedian for "1, 2, 3": 2
MinMovesToEqualArrayElements IncrDecr1Num UseSort for "1, 2, 3": 2
*/
#endif
