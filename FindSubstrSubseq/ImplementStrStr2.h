/*SuffixArray*/
#ifndef IMPLEMENT_STR_STR_2_H
#define IMPLEMENT_STR_STR_2_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Implement StrStr
// Returns a pointer to the first occurrence of needle in haystack,
// or null if needle is not part of haystack.
// Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
// Complexity:
// brute force, O(n*m) time, O(1) space
// Boyer Moore, O(n*m) time in worst case, O(n/m) time in best case, O(1) space
// Rabin-Karp (RK), O(n+m) average and O(n*m) worst case time, O(1) space
// Knuth-Morris-Pratt Algorithm (KMP), O(n+m) time, O(n) space

Refer to PatternSearching.h

N: length of haystack
M: length of needle
i: idx of haystack
j: idx of needle
*/
class ImplementStrStr2
{
public:
	ImplementStrStr2(){}
	~ImplementStrStr2(){}

	//1. Brute Force: can pass online judge
	int BruteForce(const std::string & haystack, const std::string & needle)
	{
		int N = haystack.size();
		int M = needle.size();

		if (N < M)
			return -1;
		if (M == 0)
			return 0;

		int res = -1;
		for (int i = 0; i < N - M + 1; ++i)
		{
			int j;
			for (j = 0; j < M; ++j)
			{
				if (haystack[i + j] != needle[j])
				{
					break;
				}
			}
			if (j == M)
			{
				res = i;
				break;
			}
		}

		std::cout << "ImplementStrStr2 BruteForce for \"" << needle << "\" in \"" << haystack << "\": " << res << std::endl;
		return res;
	}

	//2. Boyer Moore
	int BoyerMoore(const std::string & haystack, const std::string & needle)
	{
		int N = haystack.size();
		int M = needle.size();

		if (N < M)
			return -1;
		if (M == 0)
			return 0;

		std::vector<int> lastIdx(256, -1);//bad character skip array (init w/ -1 so that minus -1 becomes plus 1)
		for (int i = 0; i < M; ++i)
			lastIdx[needle[i]] = i;

		int skip;
		int res = -1;
		for (int i = 0; i < N - M + 1; i += skip)
		{
			skip = 0;
			for (int j = M - 1; j >= 0; --j)
			{
				if (needle[j] != haystack[i + j])
				{
					skip = std::max(1, j - lastIdx[haystack[i + j]]);
					std::cout << "skip=max(1, " << j << "-" << lastIdx[haystack[i + j]] << ") at i=" << i << std::endl;
					break;
				}
			}
			if (skip == 0)//found
			{
				res = i;
				//break;

				std::string tmp = (i + M < N) ? std::to_string(M) + "-" + std::to_string(lastIdx[haystack[i + M]]) : "1";
				std::cout << "found " << needle << " at i=" << i << ", skip=" << tmp << std::endl;
				skip = i + M < N ? M - lastIdx[haystack[i + M]] : 1;
			}
		}

		std::cout << "ImplementStrStr2 BoyerMoore for \"" << needle << "\" in \"" << haystack << "\": " << res << std::endl;
		return res;
	}

#define ALPHABET 256//size of the alphabet
#define PRIME 29989//a large enough prime number to cover different hash numbers of all possible substrs with length of needle.size() in haystack (otherwise will cause hash collision)

	//3. Rabin Karp
	int RabinKarp(const std::string & haystack, const std::string & needle)
	{
		int N = haystack.size();
		int M = needle.size();

		if (N < M)
			return -1;
		if (M == 0)
			return 0;

		int msbHashTerm = 1;//the most significant bit hash term = pow(ALPHABET, M-1) % PRIME
		int hHash = 0;//haystack hash
		int nHash = 0;//needle hash, which is a constant

		//the value of msbHashTerm is pow(ALPHABET, M-1) % PRIME
		for (int i = 0; i < M - 1; ++i)
			msbHashTerm = (msbHashTerm * ALPHABET) % PRIME;// 256^(M-1) % PRIME

		//calculate the hash value of needle and first window of haystack
		for (int i = 0; i < M; ++i)
		{
			nHash = (nHash * ALPHABET + needle[i]) % PRIME;// (n[0] * 256^(M-1) + n[1] * 256^(M-2) + ... + n[M-1] * 256^0) % PRIME
			hHash = (hHash * ALPHABET + haystack[i]) % PRIME;// (h[0] * 256^(M-1) + h[1] * 256^(M-2) + ... + h[M-1] * 256^0) % PRIME
		}
		//nHash will be a constant
		//hHash will be the 1st window hash value of haystack

		int res = -1;
		for (int i = 0; i <= N - M; ++i)
		{
			//compare the hHash of current window and nHash
			if (hHash == nHash)
			{
				//compare chars one by one in case of hash collision
				int j;
				for (j = 0; j < M; ++j)
				{
					if (haystack[i + j] != needle[j])
						break;
				}
				if (j == M)
				{
					res = i;
					break;
				}
			}

			//calculate hHash for next window of haystack: Remove leading digit, add trailing digit (this is the heart of this algorithm)
			if (i < N - M)
			{
				hHash = ((hHash - haystack[i] * msbHashTerm) * ALPHABET + haystack[i + M]) % PRIME;// ((hHash - h[i] * 256^(M-1)) * 256^1 + h[i+M] * 256^0) % PRIME

				//we might get negative value of hHash, converting it to positive
				if (hHash < 0)
					hHash += PRIME;
			}
		}

		std::cout << "ImplementStrStr2 RabinKarp for \"" << needle << "\" in \"" << haystack << "\": " << res << std::endl;
		return res;
	}

	//4. KMP
	int KMP(const std::string & haystack, const std::string & needle)
	{
		int N = haystack.size();
		int M = needle.size();

		if (N < M)
			return -1;
		if (M == 0)
			return 0;

		std::vector<int> LPS = this->getLPSVector(needle, M);

		int i = 0;
		int j = 0;
		int res = -1;

		for (; i < N;)
		{
			if (haystack[i] == needle[j])
			{
				++i;//advance i
				++j;//now j points to next
				if (j == M)//found a match
				{
					res = i - M;
					break;
				}
			}
			else
			{
				if (j != 0)//means already matched needle[0]~needle[j-1]
					j = LPS[j - 1];//reset j to previous commonPrefixEnd to skip matched suffix of needle[j-1] with length of LPS[j-1]
				else
					++i;//advance i when no char was matched (j == 0)			    
			}
		}

		std::cout << "ImplementStrStr2 KMP for \"" << needle << "\" in \"" << haystack << "\": " << res << std::endl;
		return res;
	}
	/*
	LPS: Length of Longest Prefix and Suffix in common.
	LPS[i] = the longest proper prefix of needle[0..i] 
              which is also a suffix of needle[0..i].
	 (By definition, the longest prefix must leave at least one character in the back end of string.
	 The longest suffix must leave at least one character in the front end of string.)

		    0  1  2  3  4  5  6  7  8  9  10 11 12
	needle: A  A  B  A  A  C  A  A  B  A  A  A  A
	LPS:   [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5, 2, 2]

	needle[0]: always 0
	needle[1]: AA, the common longest prefix and suffix is A, so the length is 1
	needle[2]: AAB, the common longest prefix and suffix is nothing, so the length is 0
	needle[3]: AABA, the common longest prefix and suffix is A, so the the length is 1
	needle[4]: AABAA, the common longest prefix and suffix is AA, so the length is 2
	needle[5]: AABAAC, the common longest prefix and suffix is nothing, so the length is 0
	needle[6]: AABAACA, the common longest prefix and suffix is A, so the length is 1
	needle[7]: AABAACAA, the common longest prefix and suffix is AA, so the length is 2
	needle[8]: AABAACAAB, the common longest prefix and suffix is AAB, so the length is 3
	needle[9]: AABAACAABA, the common longest prefix and suffix is AABA, so the length is 4
	needle[10]: AABAACAABAA, the common longest prefix and suffix is AABAA, so the length is 5
	needle[11]: AABAACAABAAA, the common longest prefix and suffix is AA, so the length is 2
	needle[12]: AABAACAABAAAA, the common longest prefix and suffix is AA, so the length is 2
	*/
private:
	std::vector<int> getLPSVector(const std::string & needle, int M)
	{
		std::vector<int> LPS(M);

		int commonPrefixEnd = 0;
		int suffixEnd = 1;

		LPS[0] = 0;//init (prefix and suffix cannot overlap)
		
		for (; suffixEnd < M;)
		{
			if (needle[suffixEnd] == needle[commonPrefixEnd])
			{
				++commonPrefixEnd;
				LPS[suffixEnd] = commonPrefixEnd;
				++suffixEnd;
			}
			else
			{
				if (commonPrefixEnd != 0)
				{
					commonPrefixEnd = LPS[commonPrefixEnd - 1];//jump to previous commonPrefixEnd
				}
				else//commonPrefixEnd == 0, no common characters
				{
					LPS[suffixEnd] = 0;
					++suffixEnd;
				}
			}
		}
		return LPS;
	}
public:
	std::vector<int> getLPS(const std::string & s)
	{
		int N = s.size();
		std::vector<int> LPS(N, 0);
		int i = 1;
		int j = 0;
		while (i < N)
		{
			if (s[i] == s[j]) LPS[i++] = ++j;
			else if (j != 0) j = LPS[j - 1];
			else ++i;
		}
		return LPS;
	}
	std::vector<int> GetLPS(const std::string & s)
	{
		std::vector<int> res = getLPS(s);
		std::cout << "GetLPS for \"" << s << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};

/*
ImplementStrStr2 BruteForce for "AABA" in "AABAACAADAABAAABAA": 0
found AABA at i=0, skip=4-3
skip=max(1, 2-3) at i=1
skip=max(1, 3--1) at i=2
skip=max(1, 2--1) at i=6
found AABA at i=9, skip=4-3
skip=max(1, 2-3) at i=10
skip=max(1, 2-3) at i=11
skip=max(1, 3-2) at i=12
found AABA at i=13, skip=4-3
skip=max(1, 2-3) at i=14
ImplementStrStr2 BoyerMoore for "AABA" in "AABAACAADAABAAABAA": 13
ImplementStrStr2 RabinKarp for "AABA" in "AABAACAADAABAAABAA": 0
ImplementStrStr2 KMP for "AABA" in "AABAACAADAABAAABAA": 0
GetLPS for "ABCABC": 0, 0, 0, 1, 2, 3
GetLPS for "ABCABCABC": 0, 0, 0, 1, 2, 3, 4, 5, 6
GetLPS for "AAAAAA": 0, 1, 2, 3, 4, 5
GetLPS for "ABCXABC": 0, 0, 0, 0, 1, 2, 3
*/

#endif