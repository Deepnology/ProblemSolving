#ifndef LONGEST_SUBARR_W_SAME_CHARS__AT_MOST_K_REPLACE_H
#define LONGEST_SUBARR_W_SAME_CHARS__AT_MOST_K_REPLACE_H
#include "Debug.h"
/*
Leetcode: Longest Repeating Character Replacement
Given a string that consists of only uppercase English letters, you can replace any letter in the string with another letter at most k times.
Find the length of a longest substring containing all repeating letters you can get after performing the above operations.
Note:
Both the string's length and k will not exceed 10^4.
Example 1:
Input:
s = "ABAB", k = 2
Output:
4
Explanation:
Replace the two 'A's with two 'B's or vice versa.
Example 2:
Input:
s = "AABABBA", k = 1
Output:
4
Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
*/
class LongestSubArrWSameChars_AtMostKReplace
{
public:
	LongestSubArrWSameChars_AtMostKReplace() {}

	int SlideWindow(std::string s, int k)
	{
		int N = s.size();
		if (N <= 1) return N;

		std::vector<int> count(26, 0);//count of chars in window
		int maxCount = 1;//max same char count in window
		++count[s[0] - 'A'];
		int begin = 0;
		int res = 0;
		for (int i = 1; i < N; ++i)
		{
			++count[s[i] - 'A'];
			maxCount = std::max(maxCount, count[s[i] - 'A']);

			if ((i - begin + 1) - maxCount > k)//the situation to shrink window: too long to accommodate k replacements
			{
				--count[s[begin++] - 'A'];
			}
			res = std::max(res, i - begin + 1);
		}

		std::cout << "LongestSubArrWSameChars_AtMostKReplace SlideWindow for \"" << s << "\", \"" << k << "\": " << res << std::endl;
		return res;
	}
};
/*
LongestSubArrWSameChars_AtMostKReplace SlideWindow for "ABAB", "2": 4
LongestSubArrWSameChars_AtMostKReplace SlideWindow for "AABABBA", "1": 4
*/

/*
Leetcode: Max Consecutive Ones II
Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.
Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory.
Could you solve it efficiently?
*/
class LongestConsecu1s_AtMost1Replace
{
public:
	LongestConsecu1s_AtMost1Replace() {}

	int SlideWindow(std::vector<int> & nums)
	{
		int N = nums.size();
		if (N == 0) return 0;
		int begin = 0;
		int count1 = nums[0] == 1 ? 1 : 0;
		int res = 1;
		for (int i = 1; i < N; ++i)
		{
			if (nums[i] == 1) ++count1;

			if (i - begin + 1 - count1 > 1)
			{
				if (nums[begin] == 1)
					--count1;
				++begin;
			}
			res = std::max(res, i - begin + 1);
		}

		std::cout << "LongestConsecu1s_AtMost1Replace SlideWindow for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}

	int FromStream(std::vector<int> & nums)
	{
		int N = nums.size();
		if (N == 0) return 0;
		int begin = 0;//the leftmost 1's idx in window
		int prevZeroIdx = -1;//prev zero idx of i
		int res = 1;
		for (int i = 0; i < N; ++i)
		{
			if (nums[i] == 0)
			{
				if (prevZeroIdx != -1)
					begin = prevZeroIdx + 1;
				prevZeroIdx = i;
			}
			//[1,1,1,..,0] or [1,1,1,...,1]
			res = std::max(res, i - begin + 1);
		}

		std::cout << "LongestConsecu1s_AtMost1Replace FromStream for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
};
/*
LongestConsecu1s_AtMost1Replace SlideWindow for "1, 0, 1, 1, 0": 4
LongestConsecu1s_AtMost1Replace FromStream for "1, 0, 1, 1, 0": 4
*/
#endif
