/*Greedy*DP*SuffixArray*/
#ifndef _LONGEST_PALINDROME_SUBSTR_H
#define _LONGEST_PALINDROME_SUBSTR_H
#include <iostream>
#include <sstream>
#include <vector>
#include <string>//strlen
#include <cctype>//ispunct, isspace
#include <algorithm>
#include "Debug.h"
#include "../TrieSuffixArray/SuffixArray.h"
/*
Elements of programming interview, Strings: Test palindromicity
http://stackoverflow.com/questions/2033903/algorithm-to-find-palindromes
http://www.technicalypto.com/2010/02/find-all-possible-palindromes-in-string.html
http://www.geeksforgeeks.org/longest-palindrome-substring-set-1/
http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html
http://tristan-interview.blogspot.com/2011/11/longest-palindrome-substring-manachers.html
// Given a string S, find the longest palindromic substring in S. You may
// assume that the maximum length of S is 1000, and there exists one unique
// longest palindromic substring.
*/
class LongestPalindromeSubstr
{
	/*
	1. check for a palindrome string:
	二個指針從頭尾開始比較，只要頭尾指針保持前後順位且不重疉，頭指針往前尾針往後各移一位。
	一但頭尾指針指到的字元不同，則return false。跑完全部return true。
	*/
public:
	bool IsPalindrome(const std::string & s)
	{
		int N = s.size();
		int curBegin = 0;
		int curEnd = N - 1;
		while (curBegin < curEnd)
		{
			//ignore punct or space
			while (std::ispunct(s[curBegin]) || std::isspace(s[curBegin]))
				++curBegin;
			while (std::ispunct(s[curEnd]) || std::isspace(s[curEnd]))
				--curEnd;

			//if not symmetric, stop while loop
			if (std::tolower(s[curBegin]) != std::tolower(s[curEnd]))
			{
				std::cout << "LongestPalindromeSubstr IsPalindrome for \"" << s << "\": False." << std::endl;
				return false;
			}
			++curBegin;
			--curEnd;
		}
		std::cout << "LongestPalindromeSubstr IsPalindrome for \"" << s << "\": True." << std::endl;
		return true;
	}
	bool IsPalindrome(const char A[])
	{
		if (A == 0)
		{
			std::cout << "LongestPalindromeSubstr IsPalindrome for \"" << A << "\": False." << std::endl;
			return false;
		}

		const char * curBegin = A;
		const char * curEnd = curBegin + std::strlen(A) - 1;
		while (curBegin < curEnd)
		{
			//ignore punct or space
			while (std::ispunct(*curBegin) || std::isspace(*curBegin))
				++curBegin;
			while (std::ispunct(*curEnd) || std::isspace(*curEnd))
				--curEnd;

			//if not symmetric, stop while loop
			if (std::tolower(*curBegin) != std::tolower(*curEnd))
			{
				std::cout << "LongestPalindromeSubstr IsPalindrome for \"" << A << "\": False." << std::endl;
				return false;
			}
			++curBegin;
			--curEnd;
		}
		std::cout << "LongestPalindromeSubstr IsPalindrome for \"" << A << "\": True." << std::endl;
		return true;
	}

	/*
	2. find the longest palindrome substr
	2.1
	brute force: O(N^3) time
	*/
	void BruteForce(const std::string & s)
	{
		int N = s.length();
		int maxLen = 0;
		int maxBegin = 0;
		std::vector<std::string> res;

		//enumerate all possible substrs in s
		for (int curBegin = 0; curBegin < N - 1; ++curBegin)
		{
			for (int curEnd = curBegin + 1; curEnd < N; ++curEnd)
			{
				int _begin = curBegin;
				int _end = curEnd;
				bool isPalindrome = true;
				while (_begin < _end)
				{
					if (s[_begin] == s[_end])
					{
						++_begin;
						--_end;
					}
					else
					{
						isPalindrome = false;
						break;
					}
				}
				if (isPalindrome)
				{
					res.push_back(s.substr(curBegin, curEnd - curBegin + 1));
					if (curEnd - curBegin + 1 > maxLen)
					{
						maxLen = curEnd - curBegin + 1;
						maxBegin = curBegin;
					}
				}
			}
		}
		std::cout << "LongestPalindromeSubstr BruteForce for \"" << s << "\": " << s.substr(maxBegin, maxLen) << " (" << Debug::ToStr1D<std::string>()(res) << ")" << std::endl;
	}



	/*
	2.2 greedy: O(N^2) time, O(1) space
	鎖定每一個字元，向左遞減向右遞增比較字元，相同繼續直到左邊或右邊走到底，不同就停止換下一個字元。
	奇數palindrome的從每個字元左右二邊的字元比較起，偶數的從自己和右邊第一個字元比較起。
	Leetcode: Longest Palindrome Substring
	*/
public:
	std::string Greedy(const std::string & s)
	{
		int N = s.size();
		int maxLen = 0;
		int maxBegin = 0;
		std::vector<std::string> res;
		for (int curCenter = 0; curCenter < N; ++curCenter)
		{
			this->expand(s, curCenter, curCenter, maxBegin, maxLen, res);//for odd palindromes centered at curCenter
			this->expand(s, curCenter, curCenter + 1, maxBegin, maxLen, res);//for even palindromes centered at curCenter
		}
		std::cout << "LongestPalindromeSubstr Greedy for \"" << s << "\": " << s.substr(maxBegin, maxLen) << " (" << Debug::ToStr1D<std::string>()(res) << ")" << std::endl;
		return s.substr(maxBegin, maxLen);
	}
private:
	void expand(const std::string & s, int curBegin, int curEnd, int & maxBegin, int & maxLen, std::vector<std::string> & res)
	{
		int N = s.size();
		while (curBegin >= 0 && curEnd < N && s[curBegin] == s[curEnd])
		{
			if (curEnd - curBegin + 1 > 1)//avoid 1-char palindrome substrs
				res.push_back(s.substr(curBegin, curEnd - curBegin + 1));
			--curBegin;
			++curEnd;
		}
		++curBegin;
		--curEnd;
		
		if (curEnd - curBegin + 1 > maxLen)
		{
			maxLen = curEnd - curBegin + 1;
			maxBegin = curBegin;
		}
	}

public:
	void Greedy2(const std::string & s)//O(n^2) time, O(1) space
	{
		int N = s.size();
		int maxLen = 0;
		int maxBegin = 0;
		std::vector<std::string> res;
		//Odd palindrome substrs: center char doesn't have a symmetric char to match
		for(int curCenter = 1; curCenter < N - 1; ++curCenter)
		{
			for(int left = curCenter - 1, right = curCenter + 1; left >= 0 && right < N; --left, ++right)
			{
				if(s[left] == s[right])
				{
					res.push_back(s.substr(left, right - left + 1));
					if (right - left + 1 > maxLen)
					{
						maxLen = right - left + 1;
						maxBegin = left;
					}
				}
				else 
					break;
			}
		}
		//Even palindrome substrs: no center char, every char must have a symmetric to match
		for(int curCenter = 0; curCenter < N - 1; ++curCenter)
		{
			for(int left = curCenter, right = curCenter + 1; left >= 0 && right < N; --left, ++right)
			{
				if(s[left] == s[right])
				{
					res.push_back(s.substr(left, right - left + 1));
					if (right - left + 1 > maxLen)
					{
						maxLen = right - left + 1;
						maxBegin = left;
					}
				}
				else
					break;
			}
		}
		std::cout << "PalindromeSubstr Greedy2 for \"" << s << "\": " << s.substr(maxBegin, maxLen) << " (" << Debug::ToStr1D<std::string>()(res) << ")" << std::endl;
	}

	/*
	2.3 Manacher algorithm: linear time O(N) finding longest palindrome substring

	T =			^ # b # a # b # c # b # a # b # c # b # a # c # c # b # a # $
	L =			0 0 1 0 3 0 1 0 7 0 1 0 9 0 1 0 5 0 1 0 1 0 1 2 1 0 1 0 1 0 0
	right_ =	  1 2 3 4 5 6 7 8 9 1011121314151617181920212223242526272829

	T: transformed string that was inserted "#" to represent center of even palindrome substr
	#: even palindrome center
	non-#: odd palindrome center

	L: palindrome substr length centered at each char in T

	right_: index of each char in T
	*/
public:
	std::string Manacher(const std::string & s)//O(N)
	{
		std::cout << "LongestPalindromeSubstr Manacher for \"" << s << "\":" << std::endl;

		std::string T = this->_transformString(s);
		int N = T.length();
		std::vector<int> L(N);

		int C = 0;//center index
		int R = 0;//right bound index of C

		this->_printManacherArray(T, L, C, R, 1);

		for (int right_ = 1; right_ < N - 1; ++right_)//loop through all the elements on the right side of C
		{
			int left_mirror = C - (right_ - C);//i' is the symmetric right_ on the left side of C

			std::cout << "1=> left_, C, right_(L[right_]), R = " << left_mirror << ", " << C << ", " << right_ << "(" << L[right_] << "), " << R << "."<< std::endl;

			L[right_] = (right_ < R) ? std::min(R - right_, L[left_mirror]) : 0;
			/*
			L[left_mirror] (length of palindrome substr centered at left_mirror) tells us the possible palindrome length centered at right_
			only if
			1. right_ is inside the right bound index R of center C
			2. the palindrome substr centered at left_mirror doesn't exceed the left bound of C
			, because palindrome substr centered at left_mirror and palindrome substr centered at right_ must be symmetric to C.
			So we can copy L[left_mirror] to L[right_] when the two conditions above are met.
			Then we can skip L[right_] length of elements comparison from right_'s left and right side, and just compare elements with index right_-1-L[right_] on the left and right_+1+L[right_] on the right.

			if right_ is inside the right bound R of center C, but the palindrome substr centered at left_mirror exceeds the left bound of C,
			then L[right_] can be assigned with the length from index left_mirror to left bound index, which is equal to R - right_
			, because the part of palindrome centered at right_ that is located within the right bound R of center C must be symmetric to the part of palindrome centered at left_mirror.
			Then we can skip L[right_] length of elements comparison from right_'s left and right side, and just compare elements with index right_-1-L[right_] on the left and right_+1+L[right_] on the right.

			if right_ is outside the right bound R of center C, just assign L[right_] to 0, which means we need to compare one by one from the first left and frist right of center C.
			*/

			std::cout << "2=> left_, C, right_(L[right_]), R = " << left_mirror << ", " << C << ", " << right_ << "(" << L[right_] << "), " << R << "." << std::endl;

			/*
			attemp to expand palindrome centered at right_
			the comparison skips the known symmetric characters on the left and right centered at right_ from L[left_mirror] if applicable, that's why it is O(N)
			*/
			std::cout << L[right_] << " ~ T[" << right_ << "] ~ " << L[right_] << std::endl;
			std::cout << "T[" << right_ + 1 + L[right_] << "] ?? T[" << right_ - 1 - L[right_] << "]" << std::endl;
			while (T[right_ + 1 + L[right_]] == T[right_ - 1 - L[right_]])//compare elements with index right_-1-L[right_] on the left and right_+1+L[right_] on the right of center T[right_]
			{
				std::cout << "T[" << right_ + 1 + L[right_] << "] == T[" << right_ - 1 - L[right_] << "]" << std::endl;
				++L[right_];
			}
			
			std::cout << "3=> left_, C, right_(L[right_]), R = " << left_mirror << ", " << C << ", " << right_ << "(" << L[right_] << "), " << R << "." << std::endl;

			//if palindrome centered at right_ expand past R, adjust center based on expanded palindrome
			if (right_ + L[right_] > R)
			{
				C = right_;
				R = right_ + L[right_];
			}

			std::cout << "4=> left_, C, right_(L[right_]), R = " << left_mirror << ", " << C << ", " << right_ << "(" << L[right_] << "), " << R << ". <= jump C, R" << std::endl;
			this->_printManacherArray(T, L, C, R, right_);
		}

		//find the max element in L
		int maxLen = 0;
		int centerIndex = 0;
		for (int i = 1; i < N-1; ++i)
		{
			if (L[i] > maxLen)
			{
				maxLen = L[i];
				centerIndex = i;
			}
		}

		std::cout << "LongestPalindromeSubstr Manacher for \"" << s << "\": " << s.substr((centerIndex - 1 - maxLen) / 2, maxLen) << std::endl;
		return s.substr((centerIndex - 1 - maxLen) / 2, maxLen);
	}
private:
	std::string _transformString(const std::string & s)//transform "abba" to "^#a#b#b#a#$"
	{
		int N = s.length();
		if (N == 0)
			return "^$";

		std::string res("^");
		for (int i = 0; i < N; ++i)
			res += "#" + s.substr(i, 1);
		res += "#$";
		return res;
	}
	void _printManacherArray(std::string & t, std::vector<int> & p, int c, int r, int i)
	{
		std::ostringstream oss;
		oss << "I = ";
		for (std::string::iterator itr = t.begin(); itr != t.end(); ++itr)
		{
			oss << (itr - t.begin())%10;
			if (itr != t.end() - 1)
				oss << ",";
		}
		oss << " <= Index\n";

		oss << "T = ";
		for (std::string::iterator itr = t.begin(); itr != t.end(); ++itr)
		{
			oss << *itr;
			if (itr != t.end() - 1)
				oss << ",";
		}
		oss << "\n";
		oss << "L = ";
		for (std::vector<int>::iterator itr = p.begin(); itr != p.end(); ++itr)
		{
			oss << *itr;
			if (itr != p.end() - 1)
				oss << ",";
		}
		oss << "\n";
		oss << "C = ";

		int itr = 0;
		while (itr < static_cast<int>(p.size()))
		{
			if (itr == c)
				oss << "C";
			else if (itr == r)
				oss << "R";
			else if (itr == i)
				oss << "r";
			else if (itr == c - (i-c))
				oss << "^";
			else
				oss << " ";
			if (itr != p.size() - 1)
				oss << ",";
			++itr;
		}

		std::cout << oss.str() << std::endl;
	}



	/*
	2.4 dp
	O(n^2) time, O(n^2) space, memory limit exceeded
	Leetcode: Longest Palindromic Substring
	*/
public:
	std::string DP2D(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N, 0));
		//dp[i][j]: 1 means s[i:j] substr is a palindrome
		int maxBegin = 0;
		int maxLen = 1;

		for (int len = 1; len <= N; ++len)
		{
			for (int i = 0; i < N - len + 1; ++i)
			{
				int j = i + len - 1;

				if (len == 1)
					dp[i][j] = 1;
				else if (len == 2)
				{
					if (s[i] == s[j])
						dp[i][j] = 1;
				}
				else
				{
					if (s[i] == s[j] && dp[i + 1][j - 1])
						dp[i][j] = 1;
				}

				if (dp[i][j] && len > maxLen)
				{
					maxLen = len;
					maxBegin = i;
				}
			}
		}

		std::cout << "LongestPalindromeSubstr DP2D for \"" << s << "\": " << s.substr(maxBegin, maxLen) << std::endl;
		return s.substr(maxBegin, maxLen);
	}


	/*
	reverse the text, then it will be a LCSubstr problem.
	*/
	std::string SuffixArray(std::string s)
	{
		std::string reversed(s);
		std::reverse(reversed.begin(), reversed.end());
		int N1 = s.size();
		int N2 = reversed.size();
		std::string text(s + '#' + reversed);
		int N = text.size();
		std::vector<std::string> suffixes(N);
		for (int i = 0; i < N; ++i)
			suffixes[i] = text.substr(i, N);

		std::sort(suffixes.begin(), suffixes.end());

		std::cout << "suffixes for " << text << ":" << std::endl;
		this->PrintStringVector(suffixes);

		std::string LCS;
		for (int i = 0; i < N - 1; ++i)//O(n^2) with the SuffixArrayNaive approach or O(nlogn) with the SuffixArraySimple approach
		{
			// adjacent suffixes both from second text string
			if (((int)suffixes[i].size() <= N2 + 1) && ((int)suffixes[i + 1].size() <= N2 + 1))
				continue;

			// adjacent suffixes both from first text string
			if (((int)suffixes[i].size() > N2 + 1) && ((int)suffixes[i + 1].size() > N2 + 1))
				continue;

			//std::cout << "=>" << suffixes[i] << "  " << suffixes[i + 1] << std::endl;

			// check if adjacent suffixes longer common substring
			std::string LCP = this->LongestCommonPrefix(suffixes[i], suffixes[i + 1]);//O(n) with the SuffixArrayNaive approach or O(logn) with the SuffixArraySimple approach
			if (LCP.length() > LCS.length())
				LCS = LCP;
		}

		std::cout << "LongestPalindromeSubstr SuffixArray for \"" << s << "\": " << LCS.length() << " (" << LCS << ")" << std::endl;
		return LCS;
	}
private:
	std::string LongestCommonPrefix(std::string s, std::string t)
	{
		int N = std::min(s.length(), t.length());
		for (int i = 0; i < N; ++i)
			if (s[i] != t[i])
				return s.substr(0, i);
		return s.substr(0, N);
	}
	void PrintStringVector(std::vector<std::string> & v)
	{
		for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i)
			std::cout << *i << std::endl;
	}


};
/*
LongestPalindromeSubstr IsPalindrome for "a b c d c b   a": True.
LongestPalindromeSubstr IsPalindrome for "A man, a plan, a canal, Panama.": True.
LongestPalindromeSubstr IsPalindrome for "Able was I, ere I saw Elba!": True.
LongestPalindromeSubstr IsPalindrome for "a b c d c b   a": True.
LongestPalindromeSubstr IsPalindrome for "A man, a plan, a canal, Panama.": True.
LongestPalindromeSubstr IsPalindrome for "Able was I, ere I saw Elba!": True.
LongestPalindromeSubstr BruteForce for "babcbabcbaccba": abcbabcba (bab, babcbab, abcba, abcbabcba, bcb, bcbabcb, cbabc, bab, abcba, bcb, cc)
LongestPalindromeSubstr Greedy for "babcbabcbaccba": abcbabcba (bab, bcb, abcba, babcbab, bab, cbabc, bcbabcb, abcbabcba, bcb, abcba, cc)
PalindromeSubstr Greedy2 for "babcbabcbaccba": abcbabcba (bab, bcb, abcba, babcbab, bab, cbabc, bcbabcb, abcbabcba, bcb, abcba, cc)
LongestPalindromeSubstr Manacher for "babcbabcbaccba":
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C = C,r, , , , , , , , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = -1, 0, 1(0), 0.
2=> left_, C, right_(L[right_]), R = -1, 0, 1(0), 0.
0 ~ T[1] ~ 0
T[2] ?? T[0]
3=> left_, C, right_(L[right_]), R = -1, 0, 1(0), 0.
4=> left_, C, right_(L[right_]), R = -1, 1, 1(0), 1. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  ,C, , , , , , , , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 0, 1, 2(0), 1.
2=> left_, C, right_(L[right_]), R = 0, 1, 2(0), 1.
0 ~ T[2] ~ 0
T[3] ?? T[1]
T[3] == T[1]
3=> left_, C, right_(L[right_]), R = 0, 1, 2(1), 1.
4=> left_, C, right_(L[right_]), R = 0, 2, 2(1), 3. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , ,C,R, , , , , , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 1, 2, 3(0), 3.
2=> left_, C, right_(L[right_]), R = 1, 2, 3(0), 3.
0 ~ T[3] ~ 0
T[4] ?? T[2]
3=> left_, C, right_(L[right_]), R = 1, 2, 3(0), 3.
4=> left_, C, right_(L[right_]), R = 1, 2, 3(0), 3. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  ,^,C,R, , , , , , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 0, 2, 4(0), 3.
2=> left_, C, right_(L[right_]), R = 0, 2, 4(0), 3.
0 ~ T[4] ~ 0
T[5] ?? T[3]
T[5] == T[3]
T[6] == T[2]
T[7] == T[1]
3=> left_, C, right_(L[right_]), R = 0, 2, 4(3), 3.
4=> left_, C, right_(L[right_]), R = 0, 4, 4(3), 7. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , ,C, , ,R, , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 3, 4, 5(0), 7.
2=> left_, C, right_(L[right_]), R = 3, 4, 5(0), 7.
0 ~ T[5] ~ 0
T[6] ?? T[4]
3=> left_, C, right_(L[right_]), R = 3, 4, 5(0), 7.
4=> left_, C, right_(L[right_]), R = 3, 4, 5(0), 7. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , ,^,C,r, ,R, , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 2, 4, 6(0), 7.
2=> left_, C, right_(L[right_]), R = 2, 4, 6(1), 7.
1 ~ T[6] ~ 1
T[8] ?? T[4]
3=> left_, C, right_(L[right_]), R = 2, 4, 6(1), 7.
4=> left_, C, right_(L[right_]), R = 2, 4, 6(1), 7. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , ,^, ,C, ,r,R, , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 1, 4, 7(0), 7.
2=> left_, C, right_(L[right_]), R = 1, 4, 7(0), 7.
0 ~ T[7] ~ 0
T[8] ?? T[6]
3=> left_, C, right_(L[right_]), R = 1, 4, 7(0), 7.
4=> left_, C, right_(L[right_]), R = 1, 4, 7(0), 7. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  ,^, , ,C, , ,R, , , , , , , , , , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 0, 4, 8(0), 7.
2=> left_, C, right_(L[right_]), R = 0, 4, 8(0), 7.
0 ~ T[8] ~ 0
T[9] ?? T[7]
T[9] == T[7]
T[10] == T[6]
T[11] == T[5]
T[12] == T[4]
T[13] == T[3]
T[14] == T[2]
T[15] == T[1]
3=> left_, C, right_(L[right_]), R = 0, 4, 8(7), 7.
4=> left_, C, right_(L[right_]), R = 0, 8, 8(7), 15. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , , ,C, , , , , , ,R, , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 7, 8, 9(0), 15.
2=> left_, C, right_(L[right_]), R = 7, 8, 9(0), 15.
0 ~ T[9] ~ 0
T[10] ?? T[8]
3=> left_, C, right_(L[right_]), R = 7, 8, 9(0), 15.
4=> left_, C, right_(L[right_]), R = 7, 8, 9(0), 15. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , ,^,C,r, , , , , ,R, , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 6, 8, 10(0), 15.
2=> left_, C, right_(L[right_]), R = 6, 8, 10(1), 15.
1 ~ T[10] ~ 1
T[12] ?? T[8]
3=> left_, C, right_(L[right_]), R = 6, 8, 10(1), 15.
4=> left_, C, right_(L[right_]), R = 6, 8, 10(1), 15. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , ,^, ,C, ,r, , , , ,R, , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 5, 8, 11(0), 15.
2=> left_, C, right_(L[right_]), R = 5, 8, 11(0), 15.
0 ~ T[11] ~ 0
T[12] ?? T[10]
3=> left_, C, right_(L[right_]), R = 5, 8, 11(0), 15.
4=> left_, C, right_(L[right_]), R = 5, 8, 11(0), 15. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , ,^, , ,C, , ,r, , , ,R, , , , , , , , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 4, 8, 12(0), 15.
2=> left_, C, right_(L[right_]), R = 4, 8, 12(3), 15.
3 ~ T[12] ~ 3
T[16] ?? T[8]
T[16] == T[8]
T[17] == T[7]
T[18] == T[6]
T[19] == T[5]
T[20] == T[4]
T[21] == T[3]
3=> left_, C, right_(L[right_]), R = 4, 8, 12(9), 15.
4=> left_, C, right_(L[right_]), R = 4, 12, 12(9), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , , , , , , ,C, , , , , , , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 11, 12, 13(0), 21.
2=> left_, C, right_(L[right_]), R = 11, 12, 13(0), 21.
0 ~ T[13] ~ 0
T[14] ?? T[12]
3=> left_, C, right_(L[right_]), R = 11, 12, 13(0), 21.
4=> left_, C, right_(L[right_]), R = 11, 12, 13(0), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , , , , , ,^,C,r, , , , , , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 10, 12, 14(0), 21.
2=> left_, C, right_(L[right_]), R = 10, 12, 14(1), 21.
1 ~ T[14] ~ 1
T[16] ?? T[12]
3=> left_, C, right_(L[right_]), R = 10, 12, 14(1), 21.
4=> left_, C, right_(L[right_]), R = 10, 12, 14(1), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , , , , ,^, ,C, ,r, , , , , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 9, 12, 15(0), 21.
2=> left_, C, right_(L[right_]), R = 9, 12, 15(0), 21.
0 ~ T[15] ~ 0
T[16] ?? T[14]
3=> left_, C, right_(L[right_]), R = 9, 12, 15(0), 21.
4=> left_, C, right_(L[right_]), R = 9, 12, 15(0), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , , , ,^, , ,C, , ,r, , , , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 8, 12, 16(0), 21.
2=> left_, C, right_(L[right_]), R = 8, 12, 16(5), 21.
5 ~ T[16] ~ 5
T[22] ?? T[10]
3=> left_, C, right_(L[right_]), R = 8, 12, 16(5), 21.
4=> left_, C, right_(L[right_]), R = 8, 12, 16(5), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , , ,^, , , ,C, , , ,r, , , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 7, 12, 17(0), 21.
2=> left_, C, right_(L[right_]), R = 7, 12, 17(0), 21.
0 ~ T[17] ~ 0
T[18] ?? T[16]
3=> left_, C, right_(L[right_]), R = 7, 12, 17(0), 21.
4=> left_, C, right_(L[right_]), R = 7, 12, 17(0), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , , ,^, , , , ,C, , , , ,r, , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 6, 12, 18(0), 21.
2=> left_, C, right_(L[right_]), R = 6, 12, 18(1), 21.
1 ~ T[18] ~ 1
T[20] ?? T[16]
3=> left_, C, right_(L[right_]), R = 6, 12, 18(1), 21.
4=> left_, C, right_(L[right_]), R = 6, 12, 18(1), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , , ,^, , , , , ,C, , , , , ,r, , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 5, 12, 19(0), 21.
2=> left_, C, right_(L[right_]), R = 5, 12, 19(0), 21.
0 ~ T[19] ~ 0
T[20] ?? T[18]
3=> left_, C, right_(L[right_]), R = 5, 12, 19(0), 21.
4=> left_, C, right_(L[right_]), R = 5, 12, 19(0), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0
C =  , , , , ,^, , , , , , ,C, , , , , , ,r, ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 4, 12, 20(0), 21.
2=> left_, C, right_(L[right_]), R = 4, 12, 20(1), 21.
1 ~ T[20] ~ 1
T[22] ?? T[18]
3=> left_, C, right_(L[right_]), R = 4, 12, 20(1), 21.
4=> left_, C, right_(L[right_]), R = 4, 12, 20(1), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,0,0,0,0,0,0,0,0,0
C =  , , , ,^, , , , , , , ,C, , , , , , , ,r,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 3, 12, 21(0), 21.
2=> left_, C, right_(L[right_]), R = 3, 12, 21(0), 21.
0 ~ T[21] ~ 0
T[22] ?? T[20]
3=> left_, C, right_(L[right_]), R = 3, 12, 21(0), 21.
4=> left_, C, right_(L[right_]), R = 3, 12, 21(0), 21. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,0,0,0,0,0,0,0,0,0
C =  , , ,^, , , , , , , , ,C, , , , , , , , ,R, , , , , , , , ,
1=> left_, C, right_(L[right_]), R = 2, 12, 22(0), 21.
2=> left_, C, right_(L[right_]), R = 2, 12, 22(0), 21.
0 ~ T[22] ~ 0
T[23] ?? T[21]
T[23] == T[21]
3=> left_, C, right_(L[right_]), R = 2, 12, 22(1), 21.
4=> left_, C, right_(L[right_]), R = 2, 22, 22(1), 23. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,0,0,0,0,0,0,0,0
C =  , , , , , , , , , , , , , , , , , , , , , ,C,R, , , , , , ,
1=> left_, C, right_(L[right_]), R = 21, 22, 23(0), 23.
2=> left_, C, right_(L[right_]), R = 21, 22, 23(0), 23.
0 ~ T[23] ~ 0
T[24] ?? T[22]
T[24] == T[22]
T[25] == T[21]
3=> left_, C, right_(L[right_]), R = 21, 22, 23(2), 23.
4=> left_, C, right_(L[right_]), R = 21, 23, 23(2), 25. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,0,0,0,0,0,0,0
C =  , , , , , , , , , , , , , , , , , , , , , , ,C, ,R, , , , ,
1=> left_, C, right_(L[right_]), R = 22, 23, 24(0), 25.
2=> left_, C, right_(L[right_]), R = 22, 23, 24(1), 25.
1 ~ T[24] ~ 1
T[26] ?? T[22]
3=> left_, C, right_(L[right_]), R = 22, 23, 24(1), 25.
4=> left_, C, right_(L[right_]), R = 22, 23, 24(1), 25. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,1,0,0,0,0,0,0
C =  , , , , , , , , , , , , , , , , , , , , , ,^,C,r,R, , , , ,
1=> left_, C, right_(L[right_]), R = 21, 23, 25(0), 25.
2=> left_, C, right_(L[right_]), R = 21, 23, 25(0), 25.
0 ~ T[25] ~ 0
T[26] ?? T[24]
3=> left_, C, right_(L[right_]), R = 21, 23, 25(0), 25.
4=> left_, C, right_(L[right_]), R = 21, 23, 25(0), 25. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,1,0,0,0,0,0,0
C =  , , , , , , , , , , , , , , , , , , , , ,^, ,C, ,R, , , , ,
1=> left_, C, right_(L[right_]), R = 20, 23, 26(0), 25.
2=> left_, C, right_(L[right_]), R = 20, 23, 26(0), 25.
0 ~ T[26] ~ 0
T[27] ?? T[25]
T[27] == T[25]
3=> left_, C, right_(L[right_]), R = 20, 23, 26(1), 25.
4=> left_, C, right_(L[right_]), R = 20, 26, 26(1), 27. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,1,0,1,0,0,0,0
C =  , , , , , , , , , , , , , , , , , , , , , , , , , ,C,R, , ,
1=> left_, C, right_(L[right_]), R = 25, 26, 27(0), 27.
2=> left_, C, right_(L[right_]), R = 25, 26, 27(0), 27.
0 ~ T[27] ~ 0
T[28] ?? T[26]
3=> left_, C, right_(L[right_]), R = 25, 26, 27(0), 27.
4=> left_, C, right_(L[right_]), R = 25, 26, 27(0), 27. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,1,0,1,0,0,0,0
C =  , , , , , , , , , , , , , , , , , , , , , , , , ,^,C,R, , ,
1=> left_, C, right_(L[right_]), R = 24, 26, 28(0), 27.
2=> left_, C, right_(L[right_]), R = 24, 26, 28(0), 27.
0 ~ T[28] ~ 0
T[29] ?? T[27]
T[29] == T[27]
3=> left_, C, right_(L[right_]), R = 24, 26, 28(1), 27.
4=> left_, C, right_(L[right_]), R = 24, 28, 28(1), 29. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,1,0,1,0,1,0,0
C =  , , , , , , , , , , , , , , , , , , , , , , , , , , , ,C,R,
1=> left_, C, right_(L[right_]), R = 27, 28, 29(0), 29.
2=> left_, C, right_(L[right_]), R = 27, 28, 29(0), 29.
0 ~ T[29] ~ 0
T[30] ?? T[28]
3=> left_, C, right_(L[right_]), R = 27, 28, 29(0), 29.
4=> left_, C, right_(L[right_]), R = 27, 28, 29(0), 29. <= jump C, R
I = 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 <= Index
T = ^,#,b,#,a,#,b,#,c,#,b,#,a,#,b,#,c,#,b,#,a,#,c,#,c,#,b,#,a,#,$
L = 0,0,1,0,3,0,1,0,7,0,1,0,9,0,1,0,5,0,1,0,1,0,1,2,1,0,1,0,1,0,0
C =  , , , , , , , , , , , , , , , , , , , , , , , , , , ,^,C,R,
LongestPalindromeSubstr Manacher for "babcbabcbaccba": abcbabcba
LongestPalindromeSubstr DP2D for "babcbabcbaccba": abcbabcba
suffixes for babcbabcbaccba#abccabcbabcbab:
#abccabcbabcbab
a#abccabcbabcbab
ab
abcbab
abcbabcbab
abcbabcbaccba#abccabcbabcbab
abcbaccba#abccabcbabcbab
abccabcbabcbab
accba#abccabcbabcbab
b
ba#abccabcbabcbab
bab
babcbab
babcbabcbaccba#abccabcbabcbab
babcbaccba#abccabcbabcbab
baccba#abccabcbabcbab
bcbab
bcbabcbab
bcbabcbaccba#abccabcbabcbab
bcbaccba#abccabcbabcbab
bccabcbabcbab
cabcbabcbab
cba#abccabcbabcbab
cbab
cbabcbab
cbabcbaccba#abccabcbabcbab
cbaccba#abccabcbabcbab
ccabcbabcbab
ccba#abccabcbabcbab
LongestPalindromeSubstr SuffixArray for "babcbabcbaccba": 9 (abcbabcba)
*/
#endif

/*
ispunct:
Checks if the given character is a punctuation character in the current C locale.
The default C locale classifies the characters !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ as punctuation.
Return value
Non-zero value (true) if the character is a punctuation character, 0 (false) otherwise.

isspace:
Checks if the given character is classified as a whitespace character by the currently installed C locale.
In the default locale, the whitespace characters are space (0x20), form feed (0x0c), line feed (0x0a), carriage return (0x0d), horizontal tab (0x09) and vertical tab (0x0b).
Return value
Non-zero value (true) if the character is a whitespace character, 0 (false) otherwise.
*/

