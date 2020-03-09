#ifndef UNIFORM_RAND_FROM_RAND2_H
#define UNIFORM_RAND_FROM_RAND2_H
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"
/*
Elements of programming interview, PrimitiveTypes: Generate uniform random numbers

We can use a 0/1-valued random number generator to produce an integer by concatenating bits produced by the random number generator.

To understand the running time, first observe that the probability that it takes more than "diff" calls is ((2^i - diff) / 2^i)^diff.
Since 2^i is the smallest power of 2 greater than or equals to "diff", ((2^i-diff)/2^i)^diff < (1/2)^diff.
Hence, the average number of calls is bounded by 1(1/2) + 2(1/2)^2 + 3(1/2)^3 +.....
Terms in this series reduce by a factor of 2 at each step, in the limit, so the series converges, and the time complexity is O(1).

*/
class UniformRandFromRand2
{
public:
	UniformRandFromRand2(){}
	~UniformRandFromRand2(){}

	int Next(int low, int high)
	{
		int diff = high - low + 1;
		int res;
		do
		{
			res = 0;
			/*concatenate bits from MSB to LSB*/
			for (int i = 0; (1 << i) < diff; ++i)
			{
				res = (res * 2) | (rand() % 2);//res = (res << 1) | (rand() & 1);
			}
		} while (res >= diff);

		return res + low;
	}

	void Roll(int low, int high, int times)
	{
		std::vector<int> res;
		for (int i = 0; i < times; ++i)
			res.push_back(this->Next(low, high));
		std::cout << "UniformRandFromRand2 Roll \"" << times << "\"-times for \"" << low << "," << high << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
	}
};
/*
UniformRandFromRand2 Roll "30"-times for "0,31": 6, 23, 26, 24, 26, 26, 7, 27, 28, 3, 28, 6, 0, 11, 5, 3, 12, 2, 28, 19, 17, 21, 15, 3, 30, 26, 11, 13, 7, 28
*/
#endif