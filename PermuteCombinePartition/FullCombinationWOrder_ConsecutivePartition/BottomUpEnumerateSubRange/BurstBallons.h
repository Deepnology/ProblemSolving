#ifndef BURST_BALLONS_H
#define BURST_BALLONS_H
#include "Debug.h"
/*
Given n balloons, indexed from 0 to n-1.
Each balloon is painted with a number on it represented by array nums.
You are asked to burst all the balloons.
If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
Here left and right are adjacent indices of i.
After the burst, the left and right then becomes adjacent.
Find the maximum coins you can collect by bursting the balloons wisely.

Note:
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 <= n <= 500, 0 <= nums[i] <= 100

Example:
Given [3, 1, 5, 8]
Return 167

nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

formula (insert a 1 at begin and end of nums):

for (int k = left; k <= right; ++k)
{
	dp[left][right] = std::max(dp[left][right], nums[left-1]*nums[k]*nums[right+1] + dp[left][k-1] + dp[k+1][right]);
}

for (int k = left; k <= right; ++k)
{
	dp[left][right] = std::max(dp[left][right], nums[left-1]*nums[k]*nums[right+1] + this->recur(nums, dp, left, k-1) + this->recur(nums, dp, k+1, right));
}

        _dp(recur)_    ____dp(recur)___
       |           |  |                |
      left       k-1 k+1             right
	  ^            ^ ^                   ^
-----||------------|||-------------------||------
     v              v                     v
left-1              k                     right+1
   |_______*________|__________*_____________|


*/
class BurstBallons
{
public:
	BurstBallons() {}
	~BurstBallons() {}

	int DP2D(std::vector<int> && nums)
	{
		int N = nums.size();
		nums.insert(nums.begin(), 1);
		nums.push_back(1);
		std::vector<std::vector<int>> dp(N + 2, std::vector<int>(N + 2, 0));

		for (int len = 1; len <= N; ++len)
		{
			for (int left = 1; left <= N - len + 1; ++left)
			{
				int right = left + len - 1;
				for (int k = left; k <= right; ++k)
				{
					dp[left][right] = std::max(dp[left][right], nums[left - 1] * nums[k] * nums[right + 1] + dp[left][k - 1] + dp[k + 1][right]);
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "BurstBallons DP2D for \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[1][N] << std::endl;
		return dp[1][N];
	}

	int Recur(std::vector<int> && nums)
	{
		int N = nums.size();
		nums.insert(nums.begin(), 1);
		nums.push_back(1);
		std::vector<std::vector<int>> dp(N + 2, std::vector<int>(N + 2, 0));

		int res = this->recur(nums, dp, 1, N);//now begin=1, end=N

		std::cout << "BurstBallons Recur for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(const std::vector<int> & nums, std::vector<std::vector<int>> & dp, int left, int right)
	{
		if (left > right)
			return 0;
		if (dp[left][right] != 0)
			return dp[left][right];

		int res = 0;
		for (int k = left; k <= right; ++k)
		{
			res = std::max(res, nums[left - 1] * nums[k] * nums[right + 1] + this->recur(nums, dp, left, k - 1) + this->recur(nums, dp, k + 1, right));
		}
		return dp[left][right] = res;
	}
};
/*
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 30, 159, 167, 0
Row#2	= 0, 0, 15, 135, 159, 0
Row#3	= 0, 0, 0, 40, 48, 0
Row#4	= 0, 0, 0, 0, 40, 0
Row#5	= 0, 0, 0, 0, 0, 0

BurstBallons DP2D for "1, 3, 1, 5, 8, 1": 167
BurstBallons Recur for "1, 3, 1, 5, 8, 1": 167
*/
/*
Leetcode: Minimum Cost to Merge Stones
There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.
A move consists of merging exactly K consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these K piles.
Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1.
Example 1:
Input: stones = [3,2,4,1], K = 2
Output: 20
Explanation:
We start with [3, 2, 4, 1].
We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
We merge [4, 1] for a cost of 5, and we are left with [5, 5].
We merge [5, 5] for a cost of 10, and we are left with [10].
The total cost was 20, and this is the minimum possible.
Example 2:
Input: stones = [3,2,4,1], K = 3
Output: -1
Explanation: After any merge operation, there are 2 piles left, and we can't merge anymore.  So the task is impossible.
Example 3:
Input: stones = [3,5,1,2,6], K = 3
Output: 25
Explanation:
We start with [3, 5, 1, 2, 6].
We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
We merge [3, 8, 6] for a cost of 17, and we are left with [17].
The total cost was 25, and this is the minimum possible.
 */
class MergeStones
{
public:
	MergeStones(){}

	//can merge any number of consecutive piles
	int DP2D(std::vector<int> && stones) //O(N^3) time
	{
		int N = stones.size();
		std::vector<int> prefixSum(N+1, 0);
		for (int i = 1; i <= N; ++i)
			prefixSum[i] = prefixSum[i-1] + stones[i-1];

		std::vector<std::vector<int>> dp(N+1, std::vector<int>(N+1, INT_MAX));
		for (int i = 1; i <= N; ++i)
			dp[i][i] = 0;

		for (int len = 2; len <= N; ++len)
		{
			for (int left = 1; left+len-1 <= N; ++left)
			{
				int right = left+len-1;

				int sum = prefixSum[right] - prefixSum[left-1];
				for (int mid = left; mid < right; ++mid)
				{
					if (dp[left][mid]==INT_MAX || dp[mid+1][right]==INT_MAX)
						continue;
					dp[left][right] = std::min(dp[left][right], dp[left][mid]+dp[mid+1][right] + sum);
				}
			}
		}

		return dp[1][N];
	}

	//can only merge K consecutive piles
	int DP3D(std::vector<int> && stones, int K) //O(N^3*K) time
	{
		int N = stones.size();
		if ((N-1)%(K-1) != 0)
			return -1;

		std::vector<int> prefixSum(N+1, 0);
		for (int i = 1; i <= N; ++i)
			prefixSum[i] = prefixSum[i-1] + stones[i-1];

		//dp[i][j][k]: min cost to pile stones[i:j] into k piles
		std::vector<std::vector<std::vector<int>>> dp(N+1, std::vector<std::vector<int>>(N+1, std::vector<int>(K+1, INT_MAX)));
		for (int i = 1; i <= N; ++i)
			dp[i][i][1] = 0;

		for (int len = 2; len <= N; ++len)
		{
			for (int left = 1; left+len-1 <= N; ++left)
			{
				int right = left+len-1;

				//====
				for (int k = 2; k <= K; ++k)
				{
					for (int mid = left; mid < right; ++mid)
					{
						if (dp[left][mid][k-1]==INT_MAX || dp[mid+1][right][1]==INT_MAX)
							continue;
						dp[left][right][k] = std::min(dp[left][right][k], dp[left][mid][k-1]+dp[mid+1][right][1]);
					}
				}
				//===

				if (dp[left][right][K]==INT_MAX)
					continue;
				dp[left][right][1] = dp[left][right][K] + prefixSum[right]-prefixSum[left-1];
			}
		}

		return dp[1][N][1];
	}
};
#endif
