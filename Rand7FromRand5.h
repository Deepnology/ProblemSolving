#ifndef RAND7_FROM_RAND5_H
#define RAND7_FROM_RAND5_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"
/*
http://stackoverflow.com/questions/137783/expand-a-random-range-from-1-5-to-1-7
http://tianrunhe.wordpress.com/2012/05/21/implement-rand7-using-rand5/

To generate a random number in between [0, K-1] with equal probabilities (without modulo bias) using "n % K" where n is in between [1, N], N must be a multiple of K.
To generate a random number in between [1, 7], e.g., [0, 6], with equal probabilities using modulo, we must first get a random number uniformly distributed in between [1, N] where N must be a multiple of 7.

See also RandWoModuloBias.h
*/
class Rand7FromRand5
{
public:
	Rand7FromRand5()
	{
		srand((unsigned int)time(NULL));
	}
	~Rand7FromRand5(){}

	int rand7_Matrix()
	{
		int vals[5][5] =
		{
			{ 1, 2, 3, 4, 5 },
			{ 6, 7, 1, 2, 3 },
			{ 4, 5, 6, 7, 1 },
			{ 2, 3, 4, 5, 6 },
			{ 7, 0, 0, 0, 0 },
		};

		int res = 0;
		while (res == 0)
		{
			int i = this->rand5();
			int j = this->rand5();
			res = vals[i - 1][j - 1];
		}
		return res;
	}
	int rand7()
	{
		int val;
		do
		{
			val = 5 * (this->rand5() - 1) + this->rand5();
			/*val is now uniformly random btw 1~25*/

		} while (val > 21);
		/*val is now uniformly random btw 1~21*/

		val = val % 7 + 1;
		return val;
	}
private:
	int rand5()//1~5
	{
		return (rand() % 5) + 1;
	}

public:
	void Roll(int times)
	{
		std::vector<std::pair<int,int> > res;
		for (int i = 1; i <= 7; ++i)
			res.push_back(std::make_pair(i, 0));
		for (int i = 0; i < times; ++i)
			++res[this->rand7() - 1].second;

		std::cout << "Rand7FromRand5 Roll \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
};
/*
Rand7FromRand5 Roll "1000"-times: [1,137], [2,146], [3,140], [4,145], [5,144], [6,136], [7,152]
*/
#endif