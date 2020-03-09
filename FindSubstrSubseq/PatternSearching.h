/*SuffixArray*/
#ifndef _PATTERN_SEARCHING_H_
#define _PATTERN_SEARCHING_H_
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Debug.h"
/*
Elements of programming interview, Strings: Find the first occurrence of a substring (Rabin-Karp)
http://algs4.cs.princeton.edu/63suffix/KWIK.java.html
http://www.inf.fh-flensburg.de/lang/algorithmen/pattern/kmpen.htm
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=stringSearching
http://www-igm.univ-mlv.fr/~lecroq/string/
*/
class PatternSearching
{
public:
	PatternSearching(){}
	~PatternSearching(){}

	/*
	Slide the pattern over text one by one and check for a match. If a match is found, then slides by 1 again to check for subsequent matches
	best case: O(N)
	worst case: O(M*(N-M+1))
	*/
	void BruteForce(const char * pat, const char * txt)
	{
		int patLength = strlen(pat);//M
		int txtLength = strlen(txt);//N

		//2 nested loops
		for (int txtItr = 0; txtItr <= txtLength - patLength; ++txtItr)
		{
			int patItr;
			for (patItr = 0; patItr < patLength; ++patItr)
			{
				if (txt[txtItr + patItr] != pat[patItr])
					break;
			}

			//now pat[0]~pat[patItr-1] matches txt[txtItr]~txt[txtItr+patItr-1]

			if (patItr == patLength)
			{
				std::cout << "PatternSearch BruteForce: Found \"" << pat << "\" in \"" << txt << "\" at " << txtItr << std::endl;
			}
		}
	}
	void BruteForceModified(const char * pat, const char * txt)
	{
		int patLength = strlen(pat);//M
		int txtLength = strlen(txt);//N
		int txtItr = 0;
		while (txtItr <= txtLength - patLength)
		{
			int patItr;
			for (patItr = 0; patItr < patLength; ++patItr)
			{
				if (txt[txtItr+patItr] != pat[patItr])
					break;
			}

			//now pat[0]~pat[patItr-1] matches txt[txtItr]~txt[txtItr+patItr-1]

			if (patItr == patLength)
			{
				std::cout << "PatternSearch BruteForceModified: Found \"" << pat << "\" in \"" << txt << "\" at " << txtItr << std::endl;
				txtItr += patLength;//jump txtItr by patLength where txt[txtItr]~txt[txtItr+patLength-1] was already matched
			}
			else if (patItr == 0)
			{
				++txtItr;//advance the txtItr by 1
			}
			else
			{
				txtItr += patItr;//jump the txtItr by patItr where txt[txtItr]~txt[txtItr+patItr-1] was already matched
			}
		}
	}

	//O(patLen+txtLen) time, O(patLen) space
	void KMP(const char * pat, const char * txt)
	{
		int patLength = strlen(pat);
		int txtLength = strlen(txt);

		std::vector<int> LPS = this->getLPSVector(pat, patLength);//this is the heart of this algorithm
		std::cout << "LPS of KMP of \"" << pat << "\": " << Debug::ToStr1D<int>()(LPS) << std::endl;

		int patItr = 0;
		int txtItr = 0;

		while (txtItr < txtLength)
		{
			if (pat[patItr] == txt[txtItr])
			{
				++patItr;//now patItr points to next
				++txtItr;//not txtItr points to next
			}

			//now pat[0]~pat[patItr-1] matches txt[txtItr-1-patItr+1]~txt[txtItr-1]

			if (patItr == patLength)//found a match
			{
				std::cout << "PatternSearch KMP: Found \"" << pat << "\" in \"" << txt << "\" at " << txtItr - patItr << std::endl;
				patItr = LPS[patItr-1];//reset patItr (txtItr already points to the next one)
				//jump the patItr to skip the pat prefix pat[0]~pat[LPS[patItr-1]-1] which already matches txt[txtItr-1-LPS[patItr-1]+1]~txt[txtItr-1]
				//next compare pat[LPS[patItr-1]] and txt[txtItr]
			}

			//already matches pat[0]~pat[patItr-1] with txt[txtItr-1-patItr+1]~txt[txtItr-1], but next one char doesn't match
			else if (pat[patItr] != txt[txtItr])
			{
				if (patItr != 0)//means already matched pat[0]~pat[patItr-1]
					patItr = LPS[patItr-1];//reset patItr (txtItr already points to the next one)
					//jump the patItr to skip the pat prefix pat[0]~pat[LPS[ptItr-1]-1] which already matches txt[txtItr-1-LPS[patItr-1]+1]~txt[txtItr-1]
					//next compare pat[LPS[patItr-1]] and txt[txtItr]
				else
					++txtItr;//advance txtItr when no char was matched (patItr == 0)
			}
			//else if (pat[patItr] == txt[txtItr]) => ++patItr, ++txtItr
		}
	}


	/*
	LPS: Length of Longest Prefix and Suffix in common.
	LPS[i] = the longest proper prefix of pat[0..i] 
              which is also a suffix of pat[0..i].
	 (By definition, the longest prefix must leave at least one character in the back end of string.
	 The longest suffix must leave at least one character in the front end of string.)

		 0  1  2  3  4  5  6  7  8  9  10 11 12
	pat: A  A  B  A  A  C  A  A  B  A  A  A  A
	LPS:[0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5, 2, 2]

	pat[0]: always 0
	pat[1]: AA, the common longest prefix and suffix is A, so the length is 1
	pat[2]: AAB, the common longest prefix and suffix is nothing, so the length is 0
	pat[3]: AABA, the common longest prefix and suffix is A, so the the length is 1
	pat[4]: AABAA, the common longest prefix and suffix is AA, so the length is 2
	pat[5]: AABAAC, the common longest prefix and suffix is nothing, so the length is 0
	pat[6]: AABAACA, the common longest prefix and suffix is A, so the length is 1
	pat[7]: AABAACAA, the common longest prefix and suffix is AA, so the length is 2
	pat[8]: AABAACAAB, the common longest prefix and suffix is AAB, so the length is 3
	pat[9]: AABAACAABA, the common longest prefix and suffix is AABA, so the length is 4
	pat[10]: AABAACAABAA, the common longest prefix and suffix is AABAA, so the length is 5
	pat[11]: AABAACAABAAA, the common longest prefix and suffix is AA, so the length is 2
	pat[12]: AABAACAABAAAA, the common longest prefix and suffix is AA, so the length is 2
	*/
private:
	std::vector<int> getLPSVector(const char * pat, int patLength)
	{
		std::vector<int> LPS(patLength);

		int prefixEnd = 0;
		int index = 1;

		LPS[0] = 0;//init
		

		while (index < patLength)
		{
			if (pat[index] == pat[prefixEnd])//if (suffix of pat[0...i])[lastCharacter] == (prefix of pat[0...i])[lastCharacter]
			{
				++prefixEnd;//increment length of common prefix/suffix
				LPS[index] = prefixEnd;//update length of common prefix/suffix
				++index;//move ahead
			}
			else//if suffix's last Character != prefix's last Character
			{
				if (prefixEnd != 0)
				{
					prefixEnd = LPS[prefixEnd-1];//jump prefixEnd to skip pat[0]~pat[LPS[prefixEnd-1]-1]
				}
				else//prefixEnd == 0, no common characters
				{
					LPS[index] = 0;//update length of common prefix/suffix
					++index;//move ahead
				}
			}
		}

		return LPS;
	}

public:
	//O(patLen + txtLen) average and O(patLen*txtLen) worst case time, O(1) space
	void RabinKarp(const char * pat, const char * txt, const int q)
	{
		int patLength = strlen(pat);
		int txtLength = strlen(txt);
		int patHash = 0;
		int txtHash = 0;
		int hash = 1;
		int d = 256;//the number of characters in input alphabet

		//the value of hash would be pow(d, patLength-1)%q
		for (int patItr = 0; patItr < patLength - 1; ++patItr)
			hash = (hash*d)%q;
		//hash will be a constant

		//calculate the hash value of pattern and first window of text
		for (int patItr = 0; patItr < patLength; ++patItr)
		{
			patHash = (d*patHash + pat[patItr])%q;
			txtHash = (d*txtHash + txt[patItr])%q;
		}
		//patHash will be a constant
		//txtHash will be the 1st window hash value of txt

		std::cout << "RabinKarp hash = " << hash << ", patHash = " << patHash << ", txtHash = " << txtHash << ", " << (int)(pow(256.0,patLength-1))%q << std::endl;

		//slide the pattern over text one by one
		for (int txtItr = 0; txtItr <= txtLength - patLength; ++txtItr)
		{
			//check the hash values of current window of text and pattern
			//if the hash values match then only check for characters one by one
			if (patHash == txtHash)
			{
				std::cout << "hash collision at index: " << txtItr << std::endl;

				//check for characters one by one
				int patItr = 0;
				for (patItr = 0; patItr < patLength; ++patItr)
				{
					if (txt[txtItr + patItr] != pat[patItr])
						break;
				}
				if (patItr == patLength)
				{
					std::cout << "PatternSearch RabinKarp: Found \"" << pat << "\" in \"" << txt << "\" at " << txtItr << std::endl;
				}
			}

			//calculate hash value for next window of text: Remove leading digit, add trailing digit (this is the heart of this algorithm)
			if (txtItr < txtLength - patLength)
			{
				txtHash = (d*(txtHash - txt[txtItr]*hash) + txt[txtItr+patLength])%q;

				//we might get negative value of txtHash, converting it to positive
				if (txtHash < 0)
					txtHash += q;
			}
		}
	}

	//Memory is linear. Search is O(K log N) where K is the length of the string you are searching for
	void SuffixArray(const std::string & pat, const std::string & txt)
	{
		int patLen = pat.length();
		int txtLen = txt.length();

		std::vector<std::pair<std::string, int> > suffixes(txtLen);
		for (int i = 0; i < txtLen; ++i)
		{
			suffixes[i] = std::make_pair(txt.substr(i, txtLen), i);
		}
		std::sort(suffixes.begin(), suffixes.end(), 
			[](const std::pair<std::string, int> & a, const std::pair<std::string, int> & b)->bool{return a.first < b.first; });
		this->PrintStringVector(suffixes);

		//find the rank of pat in suffix array using "Binary Search"
		int rank;
		int lo = 0;
		int hi = suffixes.size() - 1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;
			int cmp = this->Compare(pat, suffixes[mid].first);
			if (cmp < 0) 
				hi = mid - 1;
			else if (cmp > 0)
				lo = mid + 1;
			else
			{
				lo = mid;
				break;
			}
		}
		rank = lo;

		for (int i = rank; i < txtLen; ++i)
		{
			int from1 = suffixes[i].second;
			if (pat.compare(txt.substr(from1, patLen)) == 0)
				std::cout << "PatternSearch SuffixArray: Found \"" << pat << "\" in \"" << txt << "\" at " << from1 << std::endl;
		}
	}
private:
	void PrintStringVector(std::vector<std::pair<std::string, int> > & v)
	{
		for (std::vector<std::pair<std::string, int> >::const_iterator i = v.begin(); i != v.end(); ++i)
			std::cout << i->second << ":	" << i->first << std::endl;
	}
	int Compare(const std::string & query, const std::string & suffix) const
	{
		int N = std::min(query.size(), suffix.size());
		for (int i = 0; i < N; ++i)
		{
			if (query[i] < suffix[i]) return -1;
			if (query[i] > suffix[i]) return 1;
		}
		return query.size() - suffix.size();
	}


public:
	//O(txtLen * patLen) time ?
	int BoyerMoore(const std::string & pat, const std::string & txt)
	{
		int patLen = pat.size();
		int txtLen = txt.size();
		std::vector<int> right(256, -1);//bad character skip array
		for (int i = 0; i < patLen; ++i)
			right[pat[i]] = i;

		int skip;
		int lastFoundIndex = -1;
		for (int i = 0; i < txtLen - patLen + 1; i += skip)
		{
			skip = 0;
			for (int j = patLen - 1; j >= 0; --j)
			{
				if (pat[j] != txt[i + j])
				{
					skip = std::max(1, j - right[txt[i + j]]);
					break;
				}
			}
			if (skip == 0)//found
			{
				std::cout << "PatternSearch BoyerMoore: Found \"" << pat << "\" in \"" << txt << "\" at " << i << std::endl;
				lastFoundIndex = i;
				skip = patLen;
			}
		}

		if (lastFoundIndex == -1)
		{
			std::cout << "PatternSearch BoyerMoore: Not Found \"" << pat << "\" in \"" << txt << "\"." << std::endl;
			return txtLen;//not found
		}
		else
			return lastFoundIndex;//found
	}

public:
	void FiniteAutomation(const std::string & pat, const std::string & txt)
	{

	}
};
/*
PatternSearch BruteForce: Found "AABA" in "AABAACAADAABAAABAA" at 0
PatternSearch BruteForce: Found "AABA" in "AABAACAADAABAAABAA" at 9
PatternSearch BruteForce: Found "AABA" in "AABAACAADAABAAABAA" at 13
PatternSearch BruteForceModified: Found "AABA" in "AABAACAADAABAAABAA" at 0
PatternSearch BruteForceModified: Found "AABA" in "AABAACAADAABAAABAA" at 9
PatternSearch BruteForceModified: Found "AABA" in "AABAACAADAABAAABAA" at 13
LPS of KMP of "AABA": 0, 1, 0, 1
PatternSearch KMP: Found "AABA" in "AABAACAADAABAAABAA" at 0
PatternSearch KMP: Found "AABA" in "AABAACAADAABAAABAA" at 9
PatternSearch KMP: Found "AABA" in "AABAACAADAABAAABAA" at 13
RabinKarp hash = 5, patHash = 79, txtHash = 79, 5
hash collision at index: 0
PatternSearch RabinKarp: Found "AABA" in "AABAACAADAABAAABAA" at 0
hash collision at index: 9
PatternSearch RabinKarp: Found "AABA" in "AABAACAADAABAAABAA" at 9
hash collision at index: 13
PatternSearch RabinKarp: Found "AABA" in "AABAACAADAABAAABAA" at 13
17:	A
16:	AA
12:	AAABAA
13:	AABAA
9:	AABAAABAA
0:	AABAACAADAABAAABAA
3:	AACAADAABAAABAA
6:	AADAABAAABAA
14:	ABAA
10:	ABAAABAA
1:	ABAACAADAABAAABAA
4:	ACAADAABAAABAA
7:	ADAABAAABAA
15:	BAA
11:	BAAABAA
2:	BAACAADAABAAABAA
5:	CAADAABAAABAA
8:	DAABAAABAA
PatternSearch SuffixArray: Found "AABA" in "AABAACAADAABAAABAA" at 13
PatternSearch SuffixArray: Found "AABA" in "AABAACAADAABAAABAA" at 9
PatternSearch SuffixArray: Found "AABA" in "AABAACAADAABAAABAA" at 0
PatternSearch BoyerMoore: Found "AABA" in "AABAACAADAABAAABAA" at 0
PatternSearch BoyerMoore: Found "AABA" in "AABAACAADAABAAABAA" at 9
PatternSearch BoyerMoore: Found "AABA" in "AABAACAADAABAAABAA" at 13
*/

#endif

