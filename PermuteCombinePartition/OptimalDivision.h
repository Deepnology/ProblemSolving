#ifndef OPTIMAL_DIVISION_H
#define OPTIMAL_DIVISION_H
#include "Debug.h"
/*
Leetcode: Optimal Division
Given a list of positive integers, the adjacent integers will perform the float division.
For example, [2,3,4] -> 2 / 3 / 4.
However, you can add any number of parenthesis at any position to change the priority of operations.
You should find out how to add parenthesis to get the maximum result, and return the corresponding expression in string format.
Your expression should NOT contain redundant parenthesis.
Example:
Input: [1000,100,10,2]
Output: "1000/(100/10/2)"
Explanation:
1000/(100/10/2) = 1000/((100/10)/2) = 200
However, the bold parenthesis in "1000/((100/10)/2)" are redundant,
since they don't influence the operation priority. So you should return "1000/(100/10/2)".
Other cases:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2

By math:
ex: a/b/c/d, we want to minimize (b/c/d):
2 options: b/(c/d) or (b/c)/d
           (b*d)/c    b/(c*d)
		   d/c        1/(c*d)
since d/c > 1/(c*d), the minimum one is (b/c)/d = b/c/d, so maximum of a/b/c/d should be a/((b/c)/d) = a/(b/c/d)
*/
class OptimalDivision
{
public:
	OptimalDivision() {}
	struct data
	{
		data() :minVal(INT_MAX), maxVal(INT_MIN), minStr(""), maxStr("") {}
		double minVal;
		double maxVal;
		std::string minStr;
		std::string maxStr;
	};
	std::string RecurDP(const std::vector<int> & nums)
	{
		int N = nums.size();
		std::vector<std::vector<data>> dp(N, std::vector<data>(N));
		data res = recur(nums, 0, N - 1, dp);
		std::cout << "OptimalDivision RecurDP for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res.maxStr << std::endl;
		return res.maxStr;
	}
private:
	data recur(const std::vector<int> & nums, int left, int right, std::vector<std::vector<data>> & dp)
	{
		if (dp[left][right].maxVal != INT_MIN || dp[left][right].minVal != INT_MAX) return dp[left][right];
		data res;
		if (left == right)
		{
			res.minVal = nums[left];
			res.maxVal = nums[right];
			res.minStr = std::to_string(nums[left]);
			res.maxStr = std::to_string(nums[left]);
			return dp[left][right] = res;
		}
		for (int mid = left; mid < right; ++mid)
		{
			data leftRes = recur(nums, left, mid, dp);
			data rightRes = recur(nums, mid + 1, right, dp);
			//postorder update min and max values of leftRes/rightRes (need to keep track of both min and max values)
			if (leftRes.maxVal / rightRes.minVal > res.maxVal)
			{
				res.maxVal = leftRes.maxVal / rightRes.minVal;
				//add parentheses to wrap rightRes (just need to skip adding parenthese to wrap last single num will skip all redundum)
				res.maxStr = leftRes.maxStr + "/" + (mid == right - 1 ? "" : "(") + rightRes.minStr + (mid == right - 1 ? "" : ")");

				std::cout << nums[left] << "," << nums[right] << " max:" << leftRes.maxStr << ";" << rightRes.minStr << std::endl;
			}
			if (leftRes.minVal / rightRes.maxVal < res.minVal)
			{
				res.minVal = leftRes.minVal / rightRes.maxVal;
				//add parentheses to wrap rightRes (just need to skip adding parenthese to wrap last single num will skip all redundum)
				res.minStr = leftRes.minStr + "/" + (mid == right - 1 ? "" : "(") + rightRes.maxStr + (mid == right - 1 ? "" : ")");

				std::cout << nums[left] << "," << nums[right] << " min:" << leftRes.minStr << ";" << rightRes.maxStr << std::endl;
			}
		}
		return dp[left][right] = res;
	}

public:
	std::string Math(const std::vector<int> & nums)
	{
		//a -> a
		//a/b -> a/b
		//a/b/c -> a/(b/c)
		//a/b/c/d -> a/(b/c/d)
		int N = nums.size();
		if (N == 0)
			return "";
		if (N == 1)
			return std::to_string(nums[0]);
		if (N == 2)
			return std::to_string(nums[0]) + "/" + std::to_string(nums[1]);
		std::string res = std::to_string(nums[0]) + "/(";
		for (int i = 1; i < N; ++i)
		{
			res += std::to_string(nums[i]);
			if (i != N - 1)
				res += "/";
			else
				res += ")";
		}
		std::cout << "OptimalDivision Math for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
};
/*
3,4 max:3;4
3,4 min:3;4
2,4 max:2;3/4
2,4 min:2;3/4
2,3 max:2;3
2,3 min:2;3
2,4 min:2/3;4
OptimalDivision RecurDP for "2, 3, 4": 2/(3/4)
OptimalDivision Math for "2, 3, 4": 2/(3/4)
10,2 max:10;2
10,2 min:10;2
100,2 max:100;10/2
100,2 min:100;10/2
100,10 max:100;10
100,10 min:100;10
100,2 min:100/10;2
1000,2 max:1000;100/10/2
1000,2 min:1000;100/(10/2)
1000,100 max:1000;100
1000,100 min:1000;100
1000,2 min:1000/100;10/2
1000,10 max:1000;100/10
1000,10 min:1000;100/10
1000,10 min:1000/100;10
1000,2 min:1000/100/10;2
OptimalDivision RecurDP for "1000, 100, 10, 2": 1000/(100/10/2)
OptimalDivision Math for "1000, 100, 10, 2": 1000/(100/10/2)
*/
#endif
