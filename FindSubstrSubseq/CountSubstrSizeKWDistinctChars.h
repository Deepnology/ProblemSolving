#ifndef _COUNT_SUBSTR_SIZE_K_W_DISTINCT_CHARS_H
#define _COUNT_SUBSTR_SIZE_K_W_DISTINCT_CHARS_H
#include "Debug.h"
/*
Leetcode: Find K-Length Substrings With No Repeated Characters
Given a string S, return the number of substrings of length K with no repeated characters.
Example 1:
Input: S = "havefunonleetcode", K = 5
Output: 6
Explanation:
There are 6 substrings they are : 'havef','avefu','vefun','efuno','etcod','tcode'.
Example 2:
Input: S = "home", K = 5
Output: 0
Explanation:
Notice K can be larger than the length of S. In this case is not possible to find any substring.
 */
class CountSubstrSizeKWDistinctChars
{
public:
    int SlideWindow(std::string S, int K)
    {
        int N = S.size();
        std::unordered_map<char, int> charCount;
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            ++charCount[S[i]];
            if (i-K+1>=0)//window begin=i-K+1
            {
                if (charCount.size() == K)
                    ++res;
                --charCount[S[i-K+1]];
                if (charCount[S[i-K+1]]==0)
                    charCount.erase(S[i-K+1]);
            }
        }
        std::cout << "CountSubstrSizeKWDistinctChars SlideWindow for [" << S << "], K=" << K << ": " << res << std::endl;
        return res;
    }
};
/*
CountSubstrSizeKWDistinctChars SlideWindow for [havefunonleetcode], K=5: 6
 */
/*
Leetcode: Diet Plan Performance
A dieter consumes calories[i] calories on the i-th day.
Given an integer k, for every consecutive sequence of k days (calories[i], calories[i+1], ..., calories[i+k-1] for all 0 <= i <= n-k), they look at T, the total calories consumed during that sequence of k days (calories[i] + calories[i+1] + ... + calories[i+k-1]):
If T < lower, they performed poorly on their diet and lose 1 point;
If T > upper, they performed well on their diet and gain 1 point;
Otherwise, they performed normally and there is no change in points.
Initially, the dieter has zero points. Return the total number of points the dieter has after dieting for calories.length days.
Note that the total points can be negative.
Example 1:
Input: calories = [1,2,3,4,5], k = 1, lower = 3, upper = 3
Output: 0
Explanation: Since k = 1, we consider each element of the array separately and compare it to lower and upper.
calories[0] and calories[1] are less than lower so 2 points are lost.
calories[3] and calories[4] are greater than upper so 2 points are gained.
Example 2:
Input: calories = [3,2], k = 2, lower = 0, upper = 1
Output: 1
Explanation: Since k = 2, we consider subarrays of length 2.
calories[0] + calories[1] > upper so 1 point is gained.
Example 3:
Input: calories = [6,5,0,0], k = 2, lower = 1, upper = 5
Output: 0
Explanation:
calories[0] + calories[1] > upper so 1 point is gained.
lower <= calories[1] + calories[2] <= upper so no change in points.
calories[2] + calories[3] < lower so 1 point is lost.
 */
class DietPlanPerformance
{
public:
    int SlideWindow(std::vector<int> && v, int k, int lower, int upper)
    {
        int N = v.size();
        int res = 0;
        int sum = 0;
        for (int i = 0; i < N; ++i)
        {
            sum += v[i];
            if (i-k+1>=0)
            {
                if (sum < lower)
                    --res;
                else if (sum > upper)
                    ++res;
                sum -= v[i-k+1];
            }
        }
        return res;
    }
};
#endif
