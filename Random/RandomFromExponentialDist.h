#ifndef RANDOM_FROM_EXPONENTIAL_DIST_H
#define RANDOM_FROM_EXPONENTIAL_DIST_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Debug.h"
/*
Elements of programming interview, Array: Generate nonuniform random numbers
http://stackoverflow.com/questions/2106503/pseudorandom-number-generator-exponential-distribution
http://en.wikipedia.org/wiki/Exponential_distribution#Generating_exponential_variates
*/
class RandomFromExponentialDist
{
public:
	RandomFromExponentialDist(){}
	~RandomFromExponentialDist(){}

	double Solve(double lambda)
	{
		/*rand() is in [0, RAND_MAX]*/
		double r = (double)rand() / RAND_MAX;
		while (r == 1.0)
			r = (double)rand() / RAND_MAX;
		/*now r is in [0, 1)*/
		
		return -(log(1 - r) / lambda);
	}

	void Roll(double lambda, int times)
	{
		std::vector<double> res;
		for (int i = 0; i < times; ++i)
			res.push_back(this->Solve(lambda));
		std::cout << "RandomFromExponentialDist for \"lambda=" << lambda << ", times=" << times << "\": " << Debug::ToStr1D<double>()(res) << std::endl;
	}
};
/*
RandomFromExponentialDist for "lambda=1.5, times=30": 1.8222, 1.28864, 1.52071, 1.43104, 0.488811, 0.516706, 0.0502714, 0.0373222, 1.03092, 1.02606, 0.00816775, 0.886446, 0.691531, 0.241511, 1.00131, 0.734691, 0.605935, 1.59721, 0.422159, 0.360486, 1.19808, 1.25774, 0.301315, 0.606187, 0.804625, 0.0345951, 0.23572, 0.267407, 0.361815, 0.55844
*/
#endif