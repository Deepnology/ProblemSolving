#ifndef ROTATED_STR_H
#define ROTATED_STR_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=14968587
http://stackoverflow.com/questions/2553522/interview-question-check-if-one-string-is-a-rotation-of-other-string
Given 2 strings a and b, determine if a is a rotated version of b.

see also RotateArray.h, MinLexicographicStrRotation.h, CircularQueueByArray.h
*/
class RotatedStr
{
public:
	RotatedStr(){}
	~RotatedStr(){}

	bool Solve_WConcat(const std::string & a, const std::string & b)
	{
		bool res =
			a.size() == b.size() &&
			std::string(a + a).find(b) != std::string::npos;//or use strstr, or use any string matching algorithm

		std::cout << "RotatedStr WConcat for \"" << a << "\" and \"" << b << "\": " << res << std::endl;
		return res;
	}
	bool Solve_WoConcat(const std::string & a, const std::string & b)
	{
		int N = a.size();
		if (N != (int)b.size())
			return false;

		bool res = false;
		int i = 0;
		int j = 0;
		while (i < N && j < N)
		{
			//1. count same chars starting from a[i] and b[i] circularly
			int sameCount = 0;
			while (sameCount < N && a[(i + sameCount) % N] == b[(j + sameCount) % N])
				++sameCount;
			std::cout << "i,j,sameCount = " << i << "," << j << "," << sameCount << std::endl;

			//2. return true when count is N
			if (sameCount == N)
			{
				res = true;
				break;
			}

			//now a[(i + sameCount) % N] != b[(j + sameCount) % N]
			//3. otherwise, advance the starting index of the string with a higher char for next comparison
			//(finally i and j will point to the SORTED starting index of the 2 strings)
			if (a[(i + sameCount) % N] > b[(j + sameCount) % N])
				i += (sameCount == 0 ? 1 : sameCount);//advance the bigger one
			else
				j += (sameCount == 0 ? 1 : sameCount);//advance the bigger one
		}

		std::cout << "RotatedStr WoConcat for \"" << a << "\" and \"" << b << "\": " << res << std::endl;
		return res;
	}
};
/*
RotatedStr WConcat for "aaabab" and "abaaab": 1
i,j,sameCount = 0,0,1
i,j,sameCount = 0,1,0
i,j,sameCount = 0,2,6
RotatedStr WoConcat for "aaabab" and "abaaab": 1
i,j,sameCount = 0,0,0
i,j,sameCount = 0,1,0
i,j,sameCount = 0,2,1
i,j,sameCount = 1,2,0
i,j,sameCount = 2,2,0
i,j,sameCount = 3,2,3
i,j,sameCount = 3,5,0
i,j,sameCount = 3,6,11
RotatedStr WoConcat for "abcaabbbbca" and "bcaabcaabbb": 1
i,j,sameCount = 0,0,0
i,j,sameCount = 0,1,3
i,j,sameCount = 0,4,0
i,j,sameCount = 0,5,2
i,j,sameCount = 2,5,0
i,j,sameCount = 3,5,0
i,j,sameCount = 4,5,0
i,j,sameCount = 5,5,0
i,j,sameCount = 6,5,2
i,j,sameCount = 8,5,0
i,j,sameCount = 9,5,0
i,j,sameCount = 10,5,11
RotatedStr WoConcat for "aabbccaabca" and "caabcaaabbc": 1
i,j,sameCount = 0,0,0
i,j,sameCount = 0,1,3
i,j,sameCount = 0,4,0
i,j,sameCount = 0,5,2
i,j,sameCount = 2,5,0
i,j,sameCount = 3,5,0
i,j,sameCount = 4,5,0
i,j,sameCount = 5,5,0
i,j,sameCount = 6,5,2
i,j,sameCount = 8,5,0
i,j,sameCount = 9,5,0
i,j,sameCount = 10,5,10
RotatedStr WoConcat for "aabbccaabca" and "caabdaaabbc": 0
i,j,sameCount = 0,0,0
i,j,sameCount = 0,1,2
i,j,sameCount = 2,1,0
i,j,sameCount = 3,1,4
RotatedStr WoConcat for "aaba" and "baaa": 1
i,j,sameCount = 0,0,5
RotatedStr WoConcat for "aaaaa" and "aaaaa": 1
i,j,sameCount = 0,0,0
i,j,sameCount = 0,1,2
i,j,sameCount = 2,1,0
i,j,sameCount = 3,1,8
RotatedStr WoConcat for "aacaabaa" and "caabaaaa": 1
*/
#endif