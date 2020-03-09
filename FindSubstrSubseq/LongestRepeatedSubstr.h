/*SuffixArray*HashTable*/
#ifndef LONGEST_REPEATED_SUBSTR_H
#define LONGEST_REPEATED_SUBSTR_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
#include "SuffixArray.h"
/*
Leetcode: Longest Repeating Substring, Longest Duplicate Substring
suffix array
http://introcs.cs.princeton.edu/java/42sort/LRS.java.html
The longest repeated substring problem is the problem of finding the longest substring of a string that occurs at least twice. 
This problem can be solved in linear time and space by building a suffix tree for the string, and finding the "deepest internal node" in the tree.
Depth is measured by the number of characters traversed from the root. 
The string spelled by the edges from the root to such a node is a longest repeated substring.

I. At least one repeat
1. suffix array
Build suffix array.
For each adj suffix pair, compute LCP
, then the "longest repeated substr between the 2" will be the "current suffix with length of LCP".
The overall longest repeated substr will be the longest one of all "longest repeated substr between the 2".

2. hash table (key: substr, value: count)

II. At least k repeats
1. suffix array
Build suffix array.
For each k adj suffix group, compute LCP of the first suffix and last suffix
, then the "longest k repeated substr between the k" will be the "first suffix with length of LCP".
The overall longest k repeated substr will be the longest one of all "longest repeated substr between the k".

2. hash table (key: substr, value: count)

*/

class LongestRepeatedSubstr
{
public:
	LongestRepeatedSubstr(){}
	~LongestRepeatedSubstr(){}

	std::string SuffixArray(const std::string & s)
	{
		int N = s.length();

		//1. build suffix array
		std::vector<std::string> suffixes(N);
		for (int i = 0; i < N; ++i)
			suffixes[i] = s.substr(i, N);
		std::sort(suffixes.begin(), suffixes.end());
		std::cout << "SuffixArray for \"" << s << "\": " << std::endl;
		this->PrintStringVector(suffixes);

		//2. build adjacent longest-common-prefix array (the longest common prefix between adjacent suffixes)
		std::vector<std::string> LCPs(N - 1);
		for (int i = 0; i < N - 1; ++i)
		{
			int LCP = this->LongestCommonPrefix(suffixes[i], suffixes[i + 1]).size();
			LCPs[i] = suffixes[i].substr(0, LCP);
		}
		std::cout << "Adjacent LongestCommonPrefix Array for \"" << s << "\": " << std::endl;
		this->PrintStringVector(LCPs);

		//3. find the longest one from adjacent longest-common-prefix array
		std::string LRS;
		for (int i = 0; i < N - 1; ++i)
		{
			if (!LCPs[i].empty())
			{
				if (LRS.empty())
					LRS = LCPs[i];
				else if (LRS.size() <= LCPs[i].size())
					LRS = LCPs[i];
			}
		}

		std::cout << "LongestRepeatedSubstr SuffixArray for \"" << s << "\": " << LRS << std::endl;
		return LRS;
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
	int AtLeastKRepeats_SuffixArray(const std::string & s, int K)
	{
		//1. build suffix array
		SuffixArraySimple suffixes(s);

		//2. find the longest one from K-adjacent longest-common-prefix array
		std::cout << "K-Adjacent LongestCommonPrefix Array for \"" << s << "\": " << std::endl;
		int maxLCP = 0;
		std::string maxLCPSubstr;
		for (int i = 0; i < suffixes.Size() - K + 1; ++i)
		{
			int LCP = suffixes.LongestCommonPrefix(suffixes[i], suffixes[i + K - 1]);
			std::string LCPStr = s.substr(suffixes[i]).substr(0, LCP);
			std::cout << LCPStr << std::endl;
			if (LCP > maxLCP)
			{
				maxLCP = LCP;
				maxLCPSubstr = LCPStr;
			}
		}

		std::cout << "LongestRepeatedSubstr AtLeastKRepeats_SuffixArray for \"" << K << "\" in \"" << s << "\": " << maxLCP << " \"" << maxLCPSubstr << "\"" << std::endl;
		return maxLCP;
	}

	std::string BruteForce_HashMap(const std::string & s, int K)
	{
		int N = s.size();
		std::string res;
		bool found = false;

		//enumerate all possible substr len from N to 1
		//once found a repeated substr for each len, we are done
		for (int len = N; len >= 1; --len)
		{
			//1. insert all substr with len to a hash map
			std::unordered_map<std::string, int> strToCount;
			for (int i = 0; i < N - len + 1; ++i)
			{
				std::string substr = s.substr(i, len);
				if (strToCount.find(substr) != strToCount.end())
					++strToCount[substr];
				else
					strToCount[substr] = 1;//insert {substr,1}
			}
			//2. find first repeated substr
			for (const auto & p : strToCount)
			{
				if (p.second >= K)
				{
					std::cout << Debug::ToStr1D<std::string, int>()(strToCount) << std::endl;
					res = p.first;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}

		std::cout << "LongestRepeatedSubstr BruteForce_HashMap for \"" << K << "\" in \"" << s << "\": " << res << std::endl;
		return res;
	}

	std::string DP(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int>> dp(N+1, std::vector<int>(N+1, 0)); //dp[i][j]: substrs ending at i and ending at j
		int maxLen = 0; int begin;
		for (int i = 1; i <= N; ++i)
			for (int j = i+1; j <= N; ++j)
				if (s[i-1] == s[j-1])
				{
					dp[i][j] = dp[i-1][j-1]+1;
					if (dp[i][j] > maxLen)
					{
						maxLen = dp[i][j];
						begin = i-maxLen;
					}
				}

		std::cout << "LongestRepeatedSubstr DP for \"" << s << "\": " << s.substr(begin, maxLen) << std::endl;
		return s.substr(begin, maxLen);
	}
    std::string DP2(const std::string & s)
    {
        int N = s.size();
        std::vector<std::vector<int>> dp(N+1, std::vector<int>(N+1, 0)); //dp[i][j]: substrs ending at i and ending at j
        int maxLen = 0; int begin;
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j < i; ++j)
                if (i==0 || j==0)
                    dp[i][j] = 0;
                else if (s[i-1] == s[j-1])
                {
                    dp[i][j] = dp[i-1][j-1]+1;
                    if (dp[i][j] > maxLen)
                    {
                        maxLen = dp[i][j];
                        begin = i-maxLen;
                    }
                }
                else
                    dp[i][j] = 0;


        std::cout << "LongestRepeatedSubstr DP2 for \"" << s << "\": " << s.substr(begin, maxLen) << std::endl;
        return s.substr(begin, maxLen);
    }

	std::string BinarySearchLen(const std::string & s)
	{
		int N = s.size();
		int left = 1; //min len
		int right = N-1; //max len
		int begin;
		while (left <= right) //O(NlogN) time
		{
			int mid = (left+right)/2;
			if (search(s, mid, begin)) //O(N) time
				left = mid + 1;
			else
				right = mid - 1;
		}
        //now right is len of longest repeated substr
        search(s, right, begin);//search one more time to find begin with len=right
		std::cout << "LongestRepeatedSubstr BinarySearchLen for \"" << s << "\": " << s.substr(begin, right) << std::endl;
		return s.substr(begin, right);
	}
private:
	bool search(const std::string & s, int k, int & begin) //O(N) time, k is len
	{
		long mod = 1000000007;//or use prime form 6*k+1 or 6*k-1
		long powK = 1;
		for (int i = 0; i < k; ++i)
			powK = powK*26%mod;
		std::unordered_set<long> visit;
		int N = s.size();
		long hash = 0; //rolling hash of substr w/ len=k
		for (int i = 0; i < N; ++i)
		{
			hash = (hash*26+(s[i]-'a')) % mod;
			if (i >= k)
				hash = (hash - (s[i-k]-'a')*powK%mod + mod) % mod;
			if (i >= k-1)
			{
				if (visit.count(hash))
                {
				    begin = i-k+1;
                    return true;
                }
				visit.insert(hash);
			}
		}
		return false;
	}
};
/*
SuffixArray for "aababbaab":
aab----------------->3 (longest LCP)
aababbaab----------->1
ab------------------>2
ababbaab------------>2
abbaab-------------->0
b------------------->1
baab---------------->2
babbaab------------->1
bbaab
Adjacent LongestCommonPrefix Array for "aababbaab":
aab----------------->longest LCP
a
ab
ab

b
ba
b
LongestRepeatedSubstr SuffixArray for "aababbaab": aab
LongestRepeatedSubstr DP for "aababbaab": aab
LongestRepeatedSubstr DP2 for "aababbaab": aab
LongestRepeatedSubstr BinarySearchLen for "aababbaab": aab
SuffixArraySimple for "aababbaab":
0:	aab--------------->1
1:	aababbaab--------->1
2:	ab---------------->2 (longest LCP)
3:	ababbaab---------->0
4:	abbaab------------>0
5:	b----------------->1
6:	baab-------------->1
7:	babbaab
8:	bbaab
K-Adjacent LongestCommonPrefix Array for "aababbaab":
a
a
ab-------------------->longest LCP


b
b
LongestRepeatedSubstr AtLeastKRepeats_SuffixArray for "3" in "aababbaab": 2 "ab"
[aa,2], [ab,3], [ba,2], [bb,1]
LongestRepeatedSubstr BruteForce_HashMap for "3" in "aababbaab": ab

SuffixArray for "mississippi":
i-------------------->1
ippi----------------->1
issippi-------------->4 (longest LCP)
ississippi----------->0
mississippi---------->0
pi------------------->1
ppi------------------>0
sippi---------------->2
sissippi------------->1
ssippi--------------->3
ssissippi
Adjacent LongestCommonPrefix Array for "mississippi":
i
i
issi----------------->longest LCP


p

si
s
ssi
LongestRepeatedSubstr SuffixArray for "mississippi": issi
LongestRepeatedSubstr DP for "mississippi": issi
LongestRepeatedSubstr DP2 for "mississippi": issi
LongestRepeatedSubstr BinarySearchLen for "mississippi": issi
SuffixArraySimple for "mississippi":
0:	i---------------->1
1:	ippi------------->1
2:	issippi---------->4 (longest LCP)
3:	ississippi------->0
4:	mississippi------>0
5:	pi--------------->1
6:	ppi-------------->0
7:	sippi------------>2
8:	sissippi--------->1
9:	ssippi----------->3
10:	ssissippi
K-Adjacent LongestCommonPrefix Array for "mississippi":
i
i
issi----------------->longest LCP


p

si
s
ssi
LongestRepeatedSubstr AtLeastKRepeats_SuffixArray for "2" in "mississippi": 4 "issi"
[sipp,1], [issi,2], [miss,1], [ippi,1], [siss,1], [ssis,1], [ssip,1]
LongestRepeatedSubstr BruteForce_HashMap for "2" in "mississippi": issi
*/
#endif