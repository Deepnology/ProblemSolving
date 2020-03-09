/*SuffixArray*/
#ifndef K_MISMATCH_H
#define K_MISMATCH_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
#include "../TrieSuffixArray/SuffixArray.h"
/*
Kmismatch
Given a text, txt, with length N, a pattern, pat, with length M, and a mismatching threshold k.
Find all substrings of txt with length M matching pat with k maximal number of mismatches.
http://www.rosshemsley.co.uk/2011/01/a-light-introduction-to-k-mismatches-2/

LongestCommonExtension
http://www.csie.ntnu.edu.tw/~u91029/LongestCommonSubstring.html#5
s1 = aabbccc
s2 = aabbbccc
LCE(0, 0) = aabb
LCE(2, 2) = bb
LCE(3, 4) = bccc
LCE(i, j) = LongestCommonPrefix(s1.substr(i, s1.length()), s2.substr(j, s2.length())

http://cs.stackexchange.com/questions/4797/fast-k-mismatch-string-matching-algorithm
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.72.5421&rep=rep1&type=pdf
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lowestCommonAncestor

Brute Force: O(NM) time
Kangaroo: O(Nk) time if LongestCommonPrefix(i, j) is O(1)
O(Nklog(N+M)) time if LongestCommonPrefix(i, j) is O(log(N+M))
*/
class Kmismatch
{
public:
	Kmismatch(){}
	~Kmismatch(){}


public:
	void BruteForce(std::string pat, std::string txt, int k)
	{
		int patLen = pat.size();
		int txtLen = txt.size();
		std::vector<std::string> kmismatches;
		for (int txtItr = 0; txtItr < txtLen - patLen + 1; ++txtItr)
		{
			int misCount = 0;
			int patItr = 0;
			std::string kmismatch;
			while (misCount <= k && patItr < patLen)
			{
				std::string LCE = this->LongestCommonExtension(pat, txt.substr(txtItr, patLen), patItr, patItr);
				kmismatch.append(LCE);
				patItr += LCE.length() + 1;//advance patItr to next position
				if (patItr <= patLen)//patItr haven't exceed patLen
				{
					++misCount;
					if (misCount <= k)//append a mismatch char
						//kmismatch.append("*");
						kmismatch += txt[txtItr + patItr - 1];
				}
			}
			//std::cout << "=> " << kmismatch << std::endl;
			if (kmismatch.size() == patLen)
				kmismatches.push_back(kmismatch);
		}
		std::cout << "Kmismatch BruteForce for \"" << pat << "\" in \"" << txt << "\", " << k << ":" << std::endl;
		this->PrintStringVector(kmismatches);
	}

	//to utilize fast LongestCommonPrefix function
	void Kangaroo_SuffixArray(std::string pat, std::string txt, int k)
	{
		int N1 = pat.size();
		int N2 = txt.size();
		std::string concat(pat + '#' + txt);//pat#txt
		int N = concat.size();

		SuffixArraySimple suffixes(concat);

		std::vector<std::string> kmismatches;
		for (int i = 0; i < N2 - N1 + 1; ++i)//txt idx starting from N1+1+i
		{
			// check if concat[0 : N1-1] and concat[N1+1+i : N1+1+i + N1-1] are k mismatches
			int misCount = 0;
			int j = 0;//pat idx starting from 0
			std::string kmismatch;
			while (misCount <= k && j < N1)
			{
				int lcpLen = suffixes.LongestCommonPrefix(j, N1 + 1 + i + j);//LCP Len of concat[j] and concat[N1+1+i+j]. O(log(N1+N2)) time
				std::string LCP = concat.substr(j, lcpLen);//LCP of concat[j] and concat[N1+1+i+j]
				kmismatch.append(LCP);
				j += LCP.length() + 1;
				
				if (j <= N1)//haven't reach pat end
				{
					++misCount;
					if (misCount <= k)//append a mismatch char
						//kmismatch.append("*");
						kmismatch += concat[N1 + 1 + i + j - 1];
				}
			}
			//std::cout << "-> " << kmismatch << std::endl;
			if (kmismatch.size() == N1)
				kmismatches.push_back(kmismatch);
		}

		std::cout << "Kmismatch Kangaroo_SuffixArray for \"" << pat << "\" in \"" << txt << "\", " << k << ":" << std::endl;
		this->PrintStringVector(kmismatches);
	}

	std::string LongestCommonExtension(const std::string & s, const std::string & t, int i, int j)
	{
		int N = s.size();
		int M = t.size();
		if (i >= N || j >= M)
			return "";
		return this->LongestCommonPrefix(s.substr(i), t.substr(j));
	}
	std::string LongestCommonPrefix(const std::string & s, const std::string & t)
	{
		int N = std::min(s.length(), t.length());
		for (int i = 0; i < N; ++i)
			if (s[i] != t[i])
				return s.substr(0, i);
		return s.substr(0, N);
	}
private:
	void PrintStringVector(std::vector<std::string> & v)
	{
		for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i)
			std::cout << *i << std::endl;
	}
};
/*
Kmismatch BruteForce for "ABCD" in "ABCCBDCDCD", 2:
ABCC
BDCD
CDCD
SuffixArraySimple for "ABCD#ABCCBDCDCD":
0:	#ABCCBDCDCD
1:	ABCCBDCDCD
2:	ABCD#ABCCBDCDCD
3:	BCCBDCDCD
4:	BCD#ABCCBDCDCD
5:	BDCDCD
6:	CBDCDCD
7:	CCBDCDCD
8:	CD
9:	CD#ABCCBDCDCD
10:	CDCD
11:	D
12:	D#ABCCBDCDCD
13:	DCD
14:	DCDCD
Kmismatch Kangaroo_SuffixArray for "ABCD" in "ABCCBDCDCD", 2:
ABCC
BDCD
CDCD
Kmismatch BruteForce for "AABA" in "AABAACAADAABAAABAA", 2:
AABA
ABAA
AACA
ACAA
AADA
ADAA
AABA
ABAA
BAAA
AAAB
AABA
ABAA
SuffixArraySimple for "AABA#AABAACAADAABAAABAA":
0:	#AABAACAADAABAAABAA
1:	A
2:	A#AABAACAADAABAAABAA
3:	AA
4:	AAABAA
5:	AABA#AABAACAADAABAAABAA
6:	AABAA
7:	AABAAABAA
8:	AABAACAADAABAAABAA
9:	AACAADAABAAABAA
10:	AADAABAAABAA
11:	ABA#AABAACAADAABAAABAA
12:	ABAA
13:	ABAAABAA
14:	ABAACAADAABAAABAA
15:	ACAADAABAAABAA
16:	ADAABAAABAA
17:	BA#AABAACAADAABAAABAA
18:	BAA
19:	BAAABAA
20:	BAACAADAABAAABAA
21:	CAADAABAAABAA
22:	DAABAAABAA
Kmismatch Kangaroo_SuffixArray for "AABA" in "AABAACAADAABAAABAA", 2:
AABA
ABAA
AACA
ACAA
AADA
ADAA
AABA
ABAA
BAAA
AAAB
AABA
ABAA
*/
#endif