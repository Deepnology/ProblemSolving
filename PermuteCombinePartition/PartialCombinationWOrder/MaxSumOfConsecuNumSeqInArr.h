#ifndef _MAX_SUM_OF_CONSECU_NUM_SEQ_IN_ARR_H
#define _MAX_SUM_OF_CONSECU_NUM_SEQ_IN_ARR_H
#include "Debug.h"
/*
Leetcode: Delete And Earn
Given an array nums of integers, you can perform operations on the array.
In each operation, you pick any nums[i] and delete it to earn nums[i] points.
After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.
You start with 0 points.
Return the maximum number of points you can earn by applying such operations.
Example 1:
Input: nums = [3, 4, 2]
Output: 6
Explanation:
Delete 4 to earn 4 points, consequently 3 is also deleted.
Then, delete 2 to earn 2 points. 6 total points are earned.
Example 2:
Input: nums = [2, 2, 3, 3, 3, 4]
Output: 9
Explanation:
Delete 3 to earn 3 points, deleting both 2's and the 4.
Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
9 total points are earned.
Note:
The length of nums is at most 20000.
Each element nums[i] is an integer in the range [1, 10000].
 */
class MaxSumOfConsecuNumSeqInArr
{
public:
    MaxSumOfConsecuNumSeqInArr(){}

    int DP(const std::vector<int> & nums) //nums[i] are in [1:10000]
    {
        int N = nums.size();
        if (N == 0) return 0;
        std::vector<int> count(10001, 0);
        for (auto i : nums)
            ++count[i];

        std::vector<int> dp(10001, 0);
        dp[1] = count[1] * 1;//count * num
        for (int i = 2; i <= 10000; ++i)
            dp[i] = std::max(dp[i-1], count[i]*i + dp[i-2]);//max(exclude cur, include cur)

        std::cout << "MaxSumOfConsecuNumSeqInArr DP for [" << Debug::ToStr1D<int>()(nums) << "]: " << dp[10000] << std::endl;
        return dp[10000];
    }
};
/*
MaxSumOfConsecuNumSeqInArr DP for [2, 2, 3, 3, 3, 4]: 9
 */
#endif
