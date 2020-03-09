#ifndef SNAKESTRING_STR_H
#define SNAKESTRING_STR_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Write a string sinusoidally
The string "Hello World!" written in sinusoidal fashion is
 e        l
H l o  W r d
   l    o   !

Define the snakestring of s to be the left-right top-to-bottom sequence in which characters appear when s is written in sinusoidal fashion.
The snakestring string for "Hello World!" is "e lHloWrdlo!"

O(n) time
*/
class SnakestringStr
{
public:
	SnakestringStr(){}
	~SnakestringStr(){}

	std::string Convert(const std::string & s)
	{
		int N = s.size();
		std::string res;

		/*output the first row, i.e., s[1], s[5], s[9], ...*/
		int cur = 1;
		while (cur < N)
		{
			res += s[cur];
			cur += 4;
		}

		/*output the second row, i.e., s[0], s[2], s[4], ...*/
		cur = 0;
		while (cur < N)
		{
			res += s[cur];
			cur += 2;
		}

		/*output the third row, i.e., s[3], s[7], s[11], ...*/
		cur = 3;
		while (cur < N)
		{
			res += s[cur];
			cur += 4;
		}

		std::cout << "SnakestringStr for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
SnakestringStr for "Hello World!": e lHloWrdlo!
*/
#endif