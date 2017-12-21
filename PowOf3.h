#ifndef POW_OF_3_H
#define POW_OF_3_H
#include <iostream>
#include <limits.h>
#include <math.h>
#include <string>
/*
Leetcode: Power of Three
Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?



std::round
Returns the integral value that is nearest to x, with halfway cases rounded away from zero.

value   round   floor   ceil    trunc
-----   -----   -----   ----    -----
2.3     2.0     2.0     3.0     2.0
3.8     4.0     3.0     4.0     3.0
5.5     6.0     5.0     6.0     5.0
-2.3    -2.0    -3.0    -2.0    -2.0
-3.8    -4.0    -4.0    -3.0    -3.0
-5.5    -6.0    -6.0    -5.0    -5.0
*/
class PowOf3
{
public:
	PowOf3() {}
	~PowOf3() {}

	bool Solve(int n)
	{
		bool naive = this->Naive(n);
		bool math = this->Math(n);
		bool maxMultipleOf3 = this->CompareMaxMultipleOf3(n);

		std::cout << "PowOf3 for \"" << n << "\": " << naive << ", " << math << ", " << maxMultipleOf3 << std::endl;
		return math;
	}

	bool Naive(int n)
	{
		if (n == 0)
			return false;
		while (n % 3 == 0)
			n /= 3;
		return n == 1;
	}

	bool Math(int n)
	{
		//log (b) = log (b) / log (a)
		//   a         c         c
		//log (n) = log  (n) / log  (3)
		//   3         10         10	
		//just need to test if log (n) is an integer
		//                        3

		return n > 0 && (log(n) / log(3)) - (int)(log(n) / log(3)) == 0;
		//return n > 0 && n == pow(3, round(log(n) / log(3)));
	}

	bool CompareMaxMultipleOf3(int n)
	{
		//3^19=1162261467 which is the max powOf3 of a 32-bit integer
		return (n > 0 && ((int)pow(3, 19) % n == 0));
	}
};
/*
PowOf3 for "36": 0, 0, 0
PowOf3 for "81": 1, 1, 1
*/

#endif
