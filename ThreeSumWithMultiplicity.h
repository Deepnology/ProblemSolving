#ifndef _THREE_SUM_WITH_MULTIPLICITY_H
#define _THREE_SUM_WITH_MULTIPLICITY_H
#include "Debug.h"
/*
Leetcode: 3Sum with Multiplicity
Given an integer array A, and an integer target, return the number of tuples i, j, k  such that i < j < k and A[i] + A[j] + A[k] == target.
As the answer can be very large, return it modulo 10^9 + 7.
Example 1:
Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation:
Enumerating by the values (A[i], A[j], A[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.
Example 2:
Input: A = [1,1,2,2,2,2], target = 5
Output: 12
Explanation:
A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
We choose one 1 from [1,1] in 2 ways,
and two 2s from [2,2,2,2] in 6 ways.
 */
class ThreeSumWithMultiplicity
{
public:
    ThreeSumWithMultiplicity(){}
    ~ThreeSumWithMultiplicity(){}

    int UseSort(std::vector<int> && num, int target)
    {
        //O(N^2) time
        int N = num.size();
        std::sort(num.begin(), num.end());
        long res = 0;
        for (int i = 0; i+2 < N; ++i)
        {
            int start = i + 1;
            int end = N - 1;
            while (start < end)
            {
                int sum = num[i] + num[start] + num[end];
                if (sum < target)
                    ++start;
                else if (sum > target)
                    --end;
                else if (num[start] != num[end])
                {
                    int oldStart = start;
                    int oldEnd = end;
                    do
                    {
                        ++start;
                    } while (start < oldEnd && num[start - 1] == num[start]);
                    do
                    {
                        --end;
                    } while (oldStart < end && num[end] == num[end + 1]);
                    //std::cout << num[i] << "," << num[oldStart] << "," << num[oldEnd] << ":" << start-oldStart << "*" << oldEnd-end << std::endl;
                    res += (start-oldStart) * (oldEnd-end);
                    res %= 1000000007;
                }
                else//num[start]==num[end]
                {
                    int count = end - start + 1;
                    //std::cout << num[i] << "," << num[start] << "," << num[end] << ":" << count << "*" << count-1 << "/2" << std::endl;
                    res += count * (count-1) / 2;//number of pairs w/o repeat
                    res %= 1000000007;
                    break;
                }
            }
        }
        std::cout << "ThreeSumWithMultiplicity UseSort for [" << Debug::ToStr1D<int>()(num) << "], " << target << ": " << res << std::endl;
        return res;
    }
    int DP(std::vector<int> && num, int target)
    {
        //DP: O(N*target) time
        int N = num.size();
        std::vector<std::vector<int>> dp(target+1,std::vector<int>(4,0));
        dp[0][0] = 1;
        for (int i = 0; i < N; ++i)
            for (int curSum = target; curSum >= num[i]; --curSum)
                for (int k = 3; k >= 1; --k)
                {
                    dp[curSum][k] += dp[curSum-num[i]][k-1];
                    dp[curSum][k] %= 1000000007;
                }
        std::cout << "ThreeSumWithMultiplicity DP for [" << Debug::ToStr1D<int>()(num) << "], " << target << ": " << dp[target][3] << std::endl;
        return dp[target][3];
    }
    int UseHashMap(std::vector<int> && num, int target)
    {
        //O(N+maxNum*maxNum) time
        int N = num.size();
        std::unordered_map<int,long> count;
        for (auto & n : num)
            ++count[n];
        long res = 0;
        for (auto & itr : count)
            for (auto & itr2 : count)
            {
                int i = itr.first;
                int j = itr2.first;
                int k = target - i - j;
                if (!count.count(k)) continue;
                if (i==j && j==k)
                    res += count[i]*(count[i]-1)*(count[i]-2)/6;
                else if (i==j && j!=k)
                    res += count[i]*(count[i]-1)/2*count[k];
                else if (i < j && j < k)
                    res += count[i]*count[j]*count[k];
                res %= 1000000007;
            }
        std::cout << "ThreeSumWithMultiplicity UseHashMap for [" << Debug::ToStr1D<int>()(num) << "], " << target << ": " << res << std::endl;
        return res;
    }
};
/*
ThreeSumWithMultiplicity UseSort for [1, 1, 2, 2, 3, 3, 4, 4, 5, 5], 8: 20
ThreeSumWithMultiplicity DP for [1, 1, 2, 2, 3, 3, 4, 4, 5, 5], 8: 20
ThreeSumWithMultiplicity UseHashMap for [1, 1, 2, 2, 3, 3, 4, 4, 5, 5], 8: 20
 */
#endif
