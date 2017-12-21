#ifndef RECONSTRUCT_ORIGINAL_DIGITS_FROM_ENGLISH_H
#define RECONSTRUCT_ORIGINAL_DIGITS_FROM_ENGLISH_H
#include "Debug.h"
/*
Leetcode: Reconstruct Original Digits From English
Given a non-empty string containing an out-of-order English representation of digits 0-9, output the digits in ascending order.
Note:
Input contains only lowercase English letters.
Input is guaranteed to be valid and can be transformed to its original digits.
That means invalid inputs such as "abc" or "zerone" are not permitted.
Input length is less than 50,000.
Example 1:
Input: "owoztneoer"
Output: "012"
Example 2:
Input: "fviefuro"
Output: "45"
*/
class ReconstructOriginalDigitsFromEnglish
{
public:
	ReconstructOriginalDigitsFromEnglish() {}

	std::string HashMap(std::string s)
	{
		int N = s.size();
		std::vector<int> count(26, 0);
		for (int i = 0; i < N; ++i)
		{
			++count[s[i] - 'a'];
		}
		/*
		zero, one, two, three, four, five, six, seven, eight, nine
		^           ^            ^           ^           ^
		*/
		std::string res;
		std::vector<int> digitCount(10, 0);
		digitCount[0] = count['z' - 'a'];
		digitCount[2] = count['w' - 'a'];
		digitCount[4] = count['u' - 'a'];
		digitCount[6] = count['x' - 'a'];
		digitCount[8] = count['g' - 'a'];
		digitCount[1] = count['o' - 'a'] - digitCount[0] - digitCount[2] - digitCount[4];
		digitCount[3] = count['r' - 'a'] - digitCount[0] - digitCount[4];
		digitCount[7] = count['s' - 'a'] - digitCount[6];
		digitCount[5] = count['v' - 'a'] - digitCount[7];
		digitCount[9] = count['i' - 'a'] - digitCount[5] - digitCount[6] - digitCount[8];
		for (int i = 0; i < 10; ++i)
		{
			//std::cout << digitCount[i] << std::endl;
			res += std::string(digitCount[i], i + '0');
		}

		std::cout << "ReconstructOriginalDigitsFromEnglish HashMap for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
ReconstructOriginalDigitsFromEnglish HashMap for "owoztneoer": 012
ReconstructOriginalDigitsFromEnglish HashMap for "fviefuro": 45
*/
#endif
