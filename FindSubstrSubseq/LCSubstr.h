/*SuffixArray*DP*/
#ifndef _LCSUBSTR_H_
#define _LCSUBSTR_H_
//Longest Common Substring
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
#include "SuffixArray.h"
/*
Leetcode: Maximum Length of Repeated Subarray
DP:
http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Longest_common_substring
http://www.geeksforgeeks.org/longest-common-substring/
Suffix Array:
http://algs4.cs.princeton.edu/63suffix/LongestCommonSubstring.java.html
http://algs4.cs.princeton.edu/63suffix/
http://www.stanford.edu/class/cs97si/suffix-array.pdf

See also LongestPalindromeSubstr.h
*/

class LCSubstr
{
public:
	LCSubstr(){}
	~LCSubstr(){}
private:
	/*
	struct Trie
	{
		Trie(): word(), kids(38, NULL) {}
		std::string word;
		std::vector<Trie *> kids;
	};
	static void DeleteSuffixTree(Trie * t)
	{

	}
	*/
public:
	int Len_SuffixTree(std::string x, std::string y)
	{
		return 0;
	}
	int Len_SuffixArray(std::string x, std::string y)
	{
		int N1 = x.size();
		int N2 = y.size();
		std::string text(x + '#' + y);
		int N = text.size();
		std::vector<std::string> suffixes(N);
		for (int i = 0; i < N; ++i)
			suffixes[i] = text.substr(i, N);

		std::sort(suffixes.begin(), suffixes.end());

		std::cout << "suffixes for " << text << ":" << std::endl;
		this->PrintStringVector(suffixes);

		std::string LCS;
		for (int i = 0; i < N - 1; ++i)//O(n)
		{
			// adjacent suffixes both from second text string (compare suffix length from end of x#y)
			if (((int)suffixes[i].size() <= N2 + 1) && ((int)suffixes[i + 1].size() <= N2 + 1))
				continue;

			// adjacent suffixes both from first text string (compare suffix length from end of x#y)
			if (((int)suffixes[i].size() > N2 + 1) && ((int)suffixes[i + 1].size() > N2 + 1))
				continue;

			//std::cout << "=>" << suffixes[i] << "  " << suffixes[i + 1] << std::endl;

			// check if adjacent suffixes longer common substring
			std::string LCP = this->LongestCommonPrefix(suffixes[i], suffixes[i + 1]);
			if (LCP.length() > LCS.length())
				LCS = LCP;
		}

		std::cout << "LCSubstr SuffixArray for \"" << x << "\" and \"" << y << "\": " << LCS.length() << " (" << LCS << ")" << std::endl;
		return LCS.length();
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

public:
	int Len_DP2D(std::string x, std::string y)//length of longest common substring
	{
		int M = x.size();
		int N = y.size();
		std::vector<std::vector<int> > dp(M + 1, std::vector<int>(N + 1, 0));
		//dp[i][j]: LCSubstr Len from x[0]~x[i-1] and y[0]~y[j-1]
		int maxLen = 0;
		int maxEnd_i = 0;
		int maxEnd_j = 0;
		/*
		std::string LCSubstr;
		int lastSubsBegin = 0;
		*/
		for (int i = 0; i <= M; ++i)//O(n^2)
		{
			for (int j = 0; j <= N; ++j)
			{
				if (i == 0 || j == 0)//first row || first column
					dp[i][j] = 0;

				else if (x[i - 1] == y[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;

					if (dp[i][j] > maxLen)
					{
						maxLen = dp[i][j];
						maxEnd_i = i - 1;
						maxEnd_j = j - 1;
						/*
						int thisSubsBegin = (i - 1) - dp[i][j] + 1;
						if (lastSubsBegin == thisSubsBegin)
							LCSubstr.push_back(x[i - 1]);
						else
						{
							lastSubsBegin = thisSubsBegin;
							LCSubstr.clear();
							LCSubstr.append(x.substr(lastSubsBegin, (i - 1) - lastSubsBegin + 1));
						}
						*/
					}
				}
				else
					dp[i][j] = 0;
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "LCSubstr DP2D for \"" << x << "\" and \"" << y << "\": " << x.substr(maxEnd_i - maxLen + 1, maxLen) << " (" << maxLen << ")" << std::endl;
		return maxLen;
	}

	int Len_3Str_SuffixArray(const std::string & x, const std::string & y, const std::string & z)
	{
		int N1 = x.size();
		int N2 = y.size();
		int N3 = z.size();
		std::string text(x + '#' + y + '$' + z);
		int N = text.size();
		SuffixArraySimple suffixes(text);

		std::string lcsubstr;
		for (int i = 0; i < N - 2; ++i)//O(n)
		{
			int n1 = text.substr(suffixes[i]).size();
			int n2 = text.substr(suffixes[i + 1]).size();
			int n3 = text.substr(suffixes[i + 2]).size();

			if (n1 <= N3 + 1)//suffix1 is from z (compare suffix length from end of x#y#z)
			{
				if (!((n2 > N3 + 1 && n2 <= N3 + N2 + 2) && (n3 > N2 + N3 + 2) ||
					(n3 > N3 + 1 && n3 <= N3 + N2 + 2) && (n2 > N2 + N3 + 2)))
					continue;
			}
			else if (n1 <= N3 + N2 + 2)//suffix1 is from y
			{
				if (!((n2 > N3 + N2 + 2) && (n3 <= N3 + 1) ||
					(n3 > N3 + N2 + 2) && (n2 <= N3 + 1)))
					continue;
			}
			else//suffix1 is from x
			{
				if (!((n2 > N3 + 1 && n2 <= N3 + N2 + 2) && (n3 > N2 + N3 + 2) ||
					(n3 > N3 + 1 && n3 <= N3 + N2 + 2) && (n2 > N2 + N3 + 2)))
					continue;
			}

			int lcs1 = suffixes.LongestCommonPrefix(suffixes[i], suffixes[i + 1]);
			int lcs2 = suffixes.LongestCommonPrefix(suffixes[i + 1], suffixes[i + 2]);
			int lcs3 = suffixes.LongestCommonPrefix(suffixes[i], suffixes[i + 2]);
			int lcs = std::min(std::min(lcs1, lcs2), lcs3);
			std::cout << text.substr(suffixes[i], lcs) << std::endl;
			if (lcs > (int)lcsubstr.size())
				lcsubstr = text.substr(suffixes[i], lcs);
		}

		std::cout << "LCSubstr Len_3Str_SuffixArray for \"" << x << "\",\"" << y << "\",\"" << z << "\": " << lcsubstr.size() << " \"" << lcsubstr << "\"" << std::endl;
		return lcsubstr.size();
	}

	int Len_MultiStr_SuffixArray(const std::vector<std::string> & v)
	{
		//generate suffixes for each str from v
		//merge all suffixes
		//for each suffix i = 0; i < N-2; ++i
		//find next n suffiexes that are from different strs in v
		//determine their min LCP
		//O(n^2)
		return 0;
	}
};

/*
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 1, 0, 0, 0
Row#2	= 0, 1, 0, 0, 0, 1, 0
Row#3	= 0, 0, 2, 1, 0, 0, 0
Row#4	= 0, 0, 0, 0, 2, 0, 0
Row#5	= 0, 1, 0, 0, 0, 3, 0
Row#6	= 0, 0, 0, 0, 0, 0, 4

LCSubstr DP2D for "acabcd" and "caabcd": abcd (4)
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 1
Row#2	= 0, 0, 0, 1, 0, 0, 0
Row#3	= 0, 0, 0, 0, 2, 0, 0
Row#4	= 0, 0, 0, 0, 0, 3, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0

LCSubstr DP2D for "wgekaaa" and "vlgekw": gek (3)
suffixes for wgekaaa#vlgekw:
#vlgekw
a#vlgekw
aa#vlgekw
aaa#vlgekw
ekaaa#vlgekw
ekw
gekaaa#vlgekw
gekw
kaaa#vlgekw
kw
lgekw
vlgekw
w
wgekaaa#vlgekw
LCSubstr SuffixArray for "wgekaaa" and "vlgekw": 3 (gek)
suffixes for aabcy#abab:
#abab
aabcy#abab
ab
abab
abcy#abab
b
bab
bcy#abab
cy#abab
y#abab
LCSubstr SuffixArray for "aabcy" and "abab": 2 (ab)
SuffixArraySimple for "abababca#aababc$aaababca":
0:	#aababc$aaababca
1:	$aaababca
2:	a
3:	a#aababc$aaababca
4:	aaababca
5:	aababc$aaababca
6:	aababca
7:	abababca#aababc$aaababca
8:	ababc$aaababca
9:	ababca
10:	ababca#aababc$aaababca
11:	abc$aaababca
12:	abca
13:	abca#aababc$aaababca
14:	bababca#aababc$aaababca
15:	babc$aaababca
16:	babca
17:	babca#aababc$aaababca
18:	bc$aaababca
19:	bca
20:	bca#aababc$aaababca
21:	c$aaababca
22:	ca
23:	ca#aababc$aaababca
a
a
ababc
ab
abc

babc
b
bc

c
LCSubstr Len_3Str_SuffixArray for "abababca","aababc","aaababca": 5 "ababc"
*/



#endif

