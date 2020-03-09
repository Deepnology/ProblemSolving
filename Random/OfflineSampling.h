#ifndef OFFLINE_SAMPLING_H
#define OFFLINE_SAMPLING_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"
/*
Elements of programming interview, Array: Sample offline data
Let A be an array whose entries are all distinct.
Implement an algorithm that takes A and an integer k and returns a subset of k elements of A.
All subsets should be equally likely.

The key to solve this problem is to build larger random subsets out of smaller ones.
O(k) time, O(1) space
*/
class OfflineSampling
{
public:
	OfflineSampling(){}
	~OfflineSampling(){}

	std::vector<int> Iterate(const std::vector<int> & v, int k)
	{
		int N = v.size();
		std::vector<int> res(v);
		for (int i = 0; i < k; ++i)//O(k) time ONLY !! (Online sampling always requires O(N) time!)
		{
			/*
			count from i to N-1 = (N-1) - i + 1 = N-i
			rand() % (N-i) = 0~(N-i-1)
			rand() % (N-i) + i = i~(N-1)
			*/
			int rand_from_i_to_NminusOne = (rand() % (N - i)) + i;
			std::swap(res[i], res[rand_from_i_to_NminusOne]);//swap v[i] with an random pick from v[i] to v[N-1]
		}
		res.resize(k);

		std::cout << "OfflineSampling Iterate for \"" << k << "\" out of \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
OfflineSampling Iterate for "8" out of "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 4, 3, 8, 6, 15, 5, 7, 9
*/
#endif