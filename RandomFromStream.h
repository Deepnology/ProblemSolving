#ifndef RANDOM_FROM_STREAM_H
#define RANDOM_FROM_STREAM_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
/*
http://www.geeksforgeeks.org/select-a-random-number-from-stream-with-o1-space/
Given a stream of numbers, generate a random number from the stream.
You are allowed to use only O(1) space and the input is in the form of stream, so can't store the previously seen numbers.

So how do we generate a random number from the whole stream such that the probability of picking any number is 1/n with O(1) extra space?
This problem is a variation of Reservoir Sampling. Here the value of k is 1.
*/
class RandomFromStream
{
public:
	RandomFromStream(){}
	~RandomFromStream(){}

	int Solve(int curItem)
	{
		static int res;
		static int count = 0;

		++count;
		if (count == 1)
			res = curItem;
		else
		{
			/*1. generate a random number for 0 to count-1*/
			int i = rand() % count;
			/*2. replace the prev random number with curItem with 1/count probability*/
			if (i == count - 1)
				res = curItem;
		}

		return res;
	}

	std::vector<int> Generate(const std::vector<int> & stream)//driver function
	{
		int N = stream.size();
		srand((unsigned int)time(NULL));
		std::vector<int> res;
		for (int i = 0; i < N; ++i)
			res.push_back(this->Solve(stream[i]));
		std::cout << "RandomFromStream for \"" << Debug::ToStr1D<int>()(stream) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
RandomFromStream for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
RandomFromStream for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 0, 0, 0, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
*/
#endif