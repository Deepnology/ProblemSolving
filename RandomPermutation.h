#ifndef RANDOM_PERMUTATION_H
#define RANDOM_PERMUTATION_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
/*
Elements of programming interview, Array: Compute a random permutation

UseOfflineSampling: O(n) time

See also ReservoirSampling.h
*/
class RandomPermutation
{
public:
	RandomPermutation(){}
	~RandomPermutation(){}

	std::vector<int> OfflineIterate(int N)
	{
		std::vector<int> res(N);
		for (int i = 0; i < N; ++i)
			res[i] = i + 1;

		for (int i = 0; i < N; ++i)
		{
			/*
			count from i to N-1 = (N-1) - i + 1 = N-i
			rand() % (N-i) = 0~(N-i-1)
			rand() % (N-i) + i = i~(N-1)
			*/
			int rand_from_i_to_NminusOne = (rand() % (N - i)) + i;//pick a random index j in [i : N-1] and swap its val with res[i]
			std::swap(res[i], res[rand_from_i_to_NminusOne]);
		}

		std::cout << "RandomPermutation OfflineIterate for \"1..." << N << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<int> OnlineIterate(int N)
	{
		std::vector<int> res(N);
		for (int i = 0; i < N; ++i)
			res[i] = i + 1;

		for (int i = 1; i < N; ++i)
		{
			/*pick a random index j in [0 : i] and swap its val with res[i]*/
			int j = rand() % (i + 1);
			std::swap(res[i], res[j]);
		}

		std::cout << "RandomPermutation OnlineIterate for \"1..." << N << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
RandomPermutation OfflineIterate for "1...30": 20, 13, 3, 10, 5, 8, 23, 25, 6, 17, 15, 16, 21, 24, 27, 26, 12, 30, 28, 1, 29, 4, 19, 11, 18, 22, 14, 7, 2, 9
RandomPermutation OnlineIterate for "1...30": 29, 4, 28, 23, 13, 17, 30, 2, 19, 12, 22, 14, 18, 1, 21, 8, 15, 27, 5, 3, 6, 7, 11, 16, 10, 9, 20, 25, 26, 24
*/
#endif