/*SuffixArray*/
#ifndef SHORTEST_UNIQUE_SUBSTR_H
#define SHORTEST_UNIQUE_SUBSTR_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
/*
http://penguin.ewu.edu/~bojianxu/publications/unique_cpm2014.pdf
http://www.csie.ntnu.edu.tw/~u91029/LongestCommonSubstring.html#4
http://mattcb.blogspot.tw/2013/01/shortest-non-repeated-substring.html

1. suffix array
Build a suffix array.
For each suffix, compute the "LCP of prev suffix and current suffix", and the "LCP of current suffix and next suffix"
, then the "shortest unique substr among the 3" will be the "current suffix with length of max(LCP1,LCP2)+1".
The overall shortest unique substr will be the shortest one of all "shortest unique substr among the 3".

2. hash table (key: substr, value: count)
*/
class ShortestUniqueSubstr
{
public:
	ShortestUniqueSubstr(){}
	~ShortestUniqueSubstr(){}

	std::string SuffixArray(std::string s)
	{
		int N = s.length();

		//1. build suffix array
		std::vector<std::string> suffixes(N);
		for (int i = 0; i < N; ++i)
			suffixes[i] = s.substr(i, N);
		std::sort(suffixes.begin(), suffixes.end());
		std::cout << "SuffixArray for \"" << s << "\":" << std::endl;
		this->PrintStringVector(suffixes);

		//2. build 3-Adjacent LongestCommonPrefix+1 array
		std::vector<std::string> LCP1s(N, std::string());//all the LCP1 in LCP1s doesn't contain each other (some suffix is a unique substr but it contains other LCP1 so it doesn't count as a LCP1.)
		for (int i = 0; i < N; ++i)
		{
			int LCPprev = 0;
			int LCPnext = 0;
			if (i - 1 >= 0)
				LCPprev = this->LongestCommonPrefix(suffixes[i], suffixes[i - 1]).size();
			if (i + 1 <= N - 1)
				LCPnext = this->LongestCommonPrefix(suffixes[i], suffixes[i + 1]).size();
			int LCPmax = std::max(LCPprev, LCPnext);
			if (LCPmax < (int)suffixes[i].size())
				LCP1s[i] = suffixes[i].substr(0, LCPmax + 1);
		}
		std::cout << "3-Adjacent LongestCommonPrefix+1 Array for \"" << s << "\":" << std::endl;
		this->PrintStringVector(LCP1s);
		
		//3. find the shortest one from 3-Adjacent LongestCommonPrefix+1 array
		std::string SUS;
		for (int i = 0; i < N; ++i)
		{
			if (!LCP1s[i].empty())
			{
				if (SUS.empty())
					SUS = LCP1s[i];
				else if (SUS.size() >= LCP1s[i].size())
					SUS = LCP1s[i];
			}
		}
		std::cout << "ShortestUniqueSubstr SuffixArray for \"" << s << "\" is: " << SUS << std::endl;
		return SUS;
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
	std::string BruteForce_HashMap(std::string s)
	{
		int N = s.size();
		std::string res;
		bool found = false;

		//enumerate all possible substr len from 1 to N
		//once found a non-repeated substr for each len, we are done
		for (int len = 1; len <= N; ++len)
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
			//2. find first non-repeated substr
			for (const auto & p : strToCount)
			{
				if (p.second == 1)
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
		
		std::cout << "ShortestUniqueSubstr BruteForce_HashMap for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
SuffixArray for "aabbabbaab":
aab---------------->max(0,3)+1=4 (too big)
aabbabbaab--------->max(3,1)+1=4
ab----------------->max(1,2)+1=3 (too big)
abbaab------------->max(2,4)+1=5
abbabbaab---------->max(4,0)+1=5
b------------------>max(0,1)+1=2 (too big)
baab--------------->max(1,2)+1=3
babbaab------------>max(2,1)+1=3
bbaab-------------->max(1,3)+1=4
bbabbaab----------->max(3,0)+1=4
3-Adjacent LongestCommonPrefix+1 Array for "aabbabbaab":

aabb

abbaa
abbab

baa------------->shortest 3-Adjacent LCP+1
bab------------->shortest 3-Adjacent LCP+1
bbaa
bbab
ShortestUniqueSubstr SuffixArray for "aabbabbaab" is: bab
[baa,1], [aab,2], [abb,2], [bba,2], [bab,1]
ShortestUniqueSubstr BruteForce_HashMap for "aabbabbaab": baa

SuffixArray for "mississippi":
i----------------->max(0,1)+1=2 (too big)
ippi-------------->max(1,1)+1=2
issippi----------->max(1,4)+1=5
ississippi-------->max(4,0)+1=5
mississippi------->max(0,0)+1=1
pi---------------->max(0,1)+1=2
ppi--------------->max(1,0)+1=2
sippi------------->max(0,2)+1=3
sissippi---------->max(2,1)+1=3
ssippi------------>max(1,3)+1=4
ssissippi--------->max(3,0)+1=4
3-Adjacent LongestCommonPrefix+1 Array for "mississippi":

ip
issip
issis
m------------->shortest 3-Adjacent LCP+1
pi
pp
sip
sis
ssip
ssis
ShortestUniqueSubstr SuffixArray for "mississippi" is: m
[m,1], [i,4], [s,4], [p,2]
ShortestUniqueSubstr BruteForce_HashMap for "mississippi": m
*/
#endif