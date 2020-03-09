#ifndef _NUM_OF_FRIEND_REQUESTS_H
#define _NUM_OF_FRIEND_REQUESTS_H
#include "Debug.h"
/*
Leetcode: Friends Of Appropriate Ages
Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person.
Person A will NOT friend request person B (B != A) if any of the following conditions are true:
age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.
Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.
How many total friend requests are made?
Example 1:
Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:
Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:
Input: [20,30,100,110,120]
Output:
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
1 <= ages[i] <= 120
 */
class NumOfFriendRequests
{
public:
    NumOfFriendRequests(){}
    ~NumOfFriendRequests(){}

    //person w/ age A will friend person w/ age B if
    //B is in (0.5*A+7, A]
    int BruteForce(std::vector<int> & ages)
    {
        int N = ages.size();
        int res = 0;
        for (int i = 0; i < N; ++i)
            for (int j = i+1; j < N; ++j)
            {
                if (request(ages[i], ages[j]))
                    ++res;
                if (request(ages[j], ages[i]))
                    ++res;
            }
        return res;
    }
    int UseBuckets(std::vector<int> & ages)
    {
        std::vector<int> buckets(121, 0);
        for (const auto & i : ages)
            ++buckets[i];
        int res = 0;
        for (int i = 15; i <= 120; ++i)
        {
            int lb = 0.5*i + 8;
            int ub = i;
            for (int j = lb; j <= ub; ++j)
                res += buckets[j] * (buckets[i] - (i==j));
        }
        return res;
    }
    int UseBucketPrefixSums(std::vector<int> & ages)
    {
        std::vector<int> buckets(121, 0);
        for (const auto & i : ages)
            ++buckets[i];
        std::vector<int> prefixSum(121, 0);
        for (int i = 1; i <= 120; ++i)
            prefixSum[i] = prefixSum[i-1] + buckets[i];
        int res = 0;
        for (int i = 15; i <= 120; ++i)
        {
            if (buckets[i] == 0) continue;
            int count = prefixSum[i] - prefixSum[0.5*i+7];//count of people in (0.5*i+7, i]
            res += count * buckets[i] - buckets[i];
        }
        return res;
    }
    void Test(std::vector<int> && ages)
    {
        int res1 = BruteForce(ages);
        int res2 = UseBuckets(ages);
        int res3 = UseBucketPrefixSums(ages);
        std::cout << "NumOfFriendRequests for [" << Debug::ToStr1D<int>()(ages) << "], BruteForce, UseBuckets, UseBucketPrefixSums: " << res1 << "," << res2 << "," << res3 << std::endl;
    }

private:
    bool request(int A, int B)
    {
        if (B <= 0.5*A + 7 || B > A)// B > 100 && A < 100 is redundant
            return false;
        return true;
    }
};
/*
NumOfFriendRequests for [20, 30, 100, 110, 120], BruteForce, UseBuckets, UseBucketPrefixSums: 3,3,3
 */
#endif
