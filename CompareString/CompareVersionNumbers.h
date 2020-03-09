#ifndef COMPARE_VERSION_NUMBERS_H
#define COMPARE_VERSION_NUMBERS_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
https://leetcode.com/problems/compare-version-numbers/
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:
0.1 < 1.1 < 1.2 < 13.37

*/
class CompareVersionNumbers
{
public:
	CompareVersionNumbers(){}
	~CompareVersionNumbers(){}

	int Solve(const std::string & version1, const std::string & version2)
	{
		int res = this->Compare(version1, version2);
		std::cout << "CompareVersionNumbers for \"" << version1 << " and " << version2 << "\": " << res << std::endl;
		return res;
	}

	int Compare(const std::string & version1, const std::string & version2)
	{
		std::vector<int> v1 = this->SplitNums(version1);
		std::vector<int> v2 = this->SplitNums(version2);
		int N1 = v1.size();
		int N2 = v2.size();
		int len = std::min(N1, N2);
		
		for (int i = 0; i < len; ++i)
		{
			if (v1[i] > v2[i])
			{
				return 1;
			}
			else if (v1[i] < v2[i])
			{
				return -1;
			}
		}
		//now every number in common length is equal

		if (N1 > N2)
		{
			while (len < N1)
				if (v1[len++] != 0)
					return 1;
			//now all trailing numbers in v1 are 0s, which means v1 is same as v2
			return 0;
		}
		else if (N1 < N2)
		{
			while (len < N2)
				if (v2[len++] != 0)
					return -1;
			//now all trailing numbers in v2 are 0s, which means v1 is same as v2
			return 0;
		}
		else//same size
		{
			return 0;
		}
	}

private:
	std::vector<int> SplitNums(const std::string & s)
	{
		std::vector<int> res;
		int N = s.size();
		int begin = 0;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '.')
			{
				res.push_back(stoi(s.substr(begin, i - begin)));
				begin = i + 1;
			}
		}
		res.push_back(stoi(s.substr(begin, N - begin)));
		return res;
	}
};
/*
CompareVersionNumbers for "1.1.2.3 and 1.1.2.3.0.0.1": -1
*/
#endif