#ifndef ENCODE_SHORTEST_NESTED_STRING_H
#define ENCODE_SHORTEST_NESTED_STRING_H
#include "Debug.h"
/*
Leetcode: Encode string with shortest length
Given a non-empty string, encode the string such that its encoded length is the shortest.
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
Note:
k will be a positive integer and encoded string will not be empty or have extra space.
You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
Example 1:
Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
Example 2:
Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
Example 3:
Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
Example 4:
Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
Example 5:
Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
*/
class EncodeShortestNestedString
{
public:
	EncodeShortestNestedString() {}

	std::string DP2D(std::string s)
	{
		int N = s.size();
		std::vector<std::vector<std::string>> dp(N, std::vector<std::string>(N, ""));
		for (int len = 1; len <= N; ++len)
		{
			for (int i = 0; i + len - 1 < N; ++i)
			{
				int j = i + len - 1;
				dp[i][j] = s.substr(i, len);
				for (int mid = i; mid < j; ++mid)
				{
					std::string left = dp[i][mid];
					std::string right = dp[mid + 1][j];
					if (left.size() + right.size() < dp[i][j].size())
						dp[i][j] = left + right;
				}

				std::string zip = compress(s, i, j, dp);
				if (zip.size() < dp[i][j].size())
					dp[i][j] = zip;
			}
		}

		Debug::Print2D<std::string>()(dp, false);
		std::cout << "EncodeShortestNestedString DP2D for \"" << s << "\": " << dp[0][N - 1] << std::endl;
		return dp[0][N - 1];
	}
private:
	std::string compress(const std::string & s, int i, int j, const std::vector<std::vector<std::string>> & dp)
	{
		std::string str = s.substr(i, j - i + 1);
		auto pos = (str + str).find(str, 1);
		//now pos points to the first repeat of "str" (excluding the "str" starting from begin)
		if (pos == str.size())//found no repeat
			return str;
		//std::cout << "->" << str << "=" << (std::to_string(str.size() / pos) + "[" + dp[i][i + pos - 1] + "]") << std::endl;
		return std::to_string(str.size() / pos) + "[" + dp[i][i + pos - 1] + "]";
		//now s[i:i+pos-1] is the smallest repeating unit
		//dp[i][i+pos-1] is the encoded string of that smallest repeating unit
		//count of smallest repeating units in str = str.size()/((i+pos-1)-i+1) = str.size()/pos
	}
	/*
	a: a|a	=> a
		 ^
	aa: aa|aa => 2[a]
		 ^
	aaa: aaa|aaa => 3[a]
		  ^
	aaaa: aaaa|aaaa => 4[a]
		   ^
	ab: ab|ab => ab
		   ^
	aba: aba|aba => aba
			 ^
	abab: abab|abab => 2[ab]
	        ^
	abcabc: abcabc|abcabc => 2[abc]
			   ^
	aaabaaab: aaabaaab|aaabaaab => 2[aaab]
				  ^
	abababab: abababab|abababab => 4[ab]
				^
	abbbabbbcabbbabbbc: abbbabbbcabbbabbbc|abbbabbbcabbbabbbc => 2[abbbabbbc] = 2[2[abbb]c]
								 ^
	*/
};
/*
[rY][cX]
Row#0	= a

EncodeShortestNestedString DP2D for "a": a
[rY][cX]
Row#0	= a, aa, aaa, aaaa
Row#1	= , a, aa, aaa
Row#2	= , , a, aa
Row#3	= , , , a

EncodeShortestNestedString DP2D for "aaaa": aaaa
[rY][cX]
Row#0	= a, aa, aaa, aaaa, 5[a]
Row#1	= , a, aa, aaa, aaaa
Row#2	= , , a, aa, aaa
Row#3	= , , , a, aa
Row#4	= , , , , a

EncodeShortestNestedString DP2D for "aaaaa": 5[a]
[rY][cX]
Row#0	= a, ab, abb, abbb, abbba, abbbab, abbbabb, 2[abbb], 2[abbb]c
Row#1	= , b, bb, bbb, bbba, bbbab, bbbabb, bbbabbb, bbbabbbc
Row#2	= , , b, bb, bba, bbab, bbabb, bbabbb, bbabbbc
Row#3	= , , , b, ba, bab, babb, babbb, babbbc
Row#4	= , , , , a, ab, abb, abbb, abbbc
Row#5	= , , , , , b, bb, bbb, bbbc
Row#6	= , , , , , , b, bb, bbc
Row#7	= , , , , , , , b, bc
Row#8	= , , , , , , , , c

EncodeShortestNestedString DP2D for "abbbabbbc": 2[abbb]c
[rY][cX]
Row#0	= a, ab, abb, abbb, abbba, abbbab, abbbabb, 2[abbb], 2[abbb]c, 2[abbb]ca, 2[abbb]cab, 2[abbb]cabb, 2[abbb]cabbb, 2[abbb]cabbba, 2[abbb]cabbbab, 2[abbb]cabbbabb, 2[abbb]c2[abbb], 2[2[abbb]c]
Row#1	= , b, bb, bbb, bbba, bbbab, bbbabb, bbbabbb, bbbabbbc, bbbabbbca, bbbabbbcab, bbbabbbcabb, bbbabbbcabbb, bbbabbbcabbba, bbbabbbcabbbab, bbbabbbcabbbabb, bbbabbbc2[abbb], bbbabbbc2[abbb]c
Row#2	= , , b, bb, bba, bbab, bbabb, bbabbb, bbabbbc, bbabbbca, bbabbbcab, bbabbbcabb, bbabbbcabbb, bbabbbcabbba, bbabbbcabbbab, bbabbbcabbbabb, bbabbbc2[abbb], bbabbbc2[abbb]c
Row#3	= , , , b, ba, bab, babb, babbb, babbbc, babbbca, babbbcab, babbbcabb, babbbcabbb, babbbcabbba, babbbcabbbab, babbbcabbbabb, babbbc2[abbb], babbbc2[abbb]c
Row#4	= , , , , a, ab, abb, abbb, abbbc, abbbca, abbbcab, abbbcabb, abbbcabbb, abbbcabbba, abbbcabbbab, abbbcabbbabb, abbbc2[abbb], abbbc2[abbb]c
Row#5	= , , , , , b, bb, bbb, bbbc, bbbca, bbbcab, bbbcabb, bbbcabbb, bbbcabbba, bbbcabbbab, bbbcabbbabb, bbbc2[abbb], bbbc2[abbb]c
Row#6	= , , , , , , b, bb, bbc, bbca, bbcab, bbcabb, bbcabbb, bbcabbba, bbcabbbab, bbcabbbabb, bbc2[abbb], bbc2[abbb]c
Row#7	= , , , , , , , b, bc, bca, bcab, bcabb, bcabbb, bcabbba, bcabbbab, bcabbbabb, bc2[abbb], bc2[abbb]c
Row#8	= , , , , , , , , c, ca, cab, cabb, cabbb, cabbba, cabbbab, cabbbabb, c2[abbb], c2[abbb]c
Row#9	= , , , , , , , , , a, ab, abb, abbb, abbba, abbbab, abbbabb, 2[abbb], 2[abbb]c
Row#10	= , , , , , , , , , , b, bb, bbb, bbba, bbbab, bbbabb, bbbabbb, bbbabbbc
Row#11	= , , , , , , , , , , , b, bb, bba, bbab, bbabb, bbabbb, bbabbbc
Row#12	= , , , , , , , , , , , , b, ba, bab, babb, babbb, babbbc
Row#13	= , , , , , , , , , , , , , a, ab, abb, abbb, abbbc
Row#14	= , , , , , , , , , , , , , , b, bb, bbb, bbbc
Row#15	= , , , , , , , , , , , , , , , b, bb, bbc
Row#16	= , , , , , , , , , , , , , , , , b, bc
Row#17	= , , , , , , , , , , , , , , , , , c

EncodeShortestNestedString DP2D for "abbbabbbcabbbabbbc": 2[2[abbb]c]
*/
#endif
