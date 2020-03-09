#ifndef RANDOM_SUBSET_H
#define RANDOM_SUBSET_H
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "Debug.h"
/*
Elements of programming interview, Array: Compute a random subset of {0,1,...,n-1}
Compute a random subset of {0,1,2,3,...,N-1} with size k.
                                       N         N!
THe set {0,1,2,3,...,N-1} has exactly ( ) = ------------- subsets of size k.
                                       k    (N-k)! * k!

All subsets should be equally likely and, in addition, all permutations of elements of the array should be equally likely.
Time complexity should be O(k).
Your algorithm can use O(k) space in addition to the k element array for the result.

We mimic the offline sampling sampling algorithm with A[i] = i initially.
The key to getting away with O(k) space is recognizing that "most of the entries of A are unchanged when k << N".
Therefore, we simulate A with a hash table.
Specifically, we maintain a hash table H whose keys and values are from {0,1,2,3,...,N-1}.
Conceptually, H tracks "indices of the array for which A[i] may not equal i".
If H does not contain a Key i, that means A[i] is still i.

The idea of offline sampling is to swap A[i] with A[i + rand()%(N-i)].
Intially A[i] == i.
Since time complexity is limited to O(k), we can't construct an array A with N elements.
Since it's offline, swap current index i with a random index in [i,N-1] from back in A for k times, and keep track of each pair of swapped indicies.
(hash map key: indicies that was swapped from back, value: indicies that was swapped to key)
In this way, we only keep track of 2*k index pairs.
The final result would be the values of the first k indicies from back in A.

See also OfflineSampling.h
*/
class RandomSubset
{
public:
	RandomSubset(){}
	~RandomSubset(){}

	//O(k) time, O(k) space
	std::vector<int> UseOfflineSampling(int N, int k)
	{
		std::unordered_map<int, int> H;//first: index that was swapped (0-based), second: index that was swapped to first (0-based)
		for (int i = 0; i < k; ++i)
		{
			int curRand = rand() % (N - i);//random number in [0, N-1-i]
			auto ptr1 = H.find(curRand);//mapped random index to swap
			auto ptr2 = H.find(N - 1 - i);//index from back
			if (ptr1 == H.end() && ptr2 == H.end())
			{
				H[curRand] = N - 1 - i;//insert (curRand, N-1-i) pair
				H[N - 1 - i] = curRand;//insert (N-1-i, curRand) pair
			}
			else if (ptr1 == H.end() && ptr2 != H.end())
			{
				H[curRand] = ptr2->second;//insert (curRand, H[N-1-i]) pair
				ptr2->second = curRand;//update H[N-1-i] = curRand
			}
			else if (ptr1 != H.end() && ptr2 == H.end())
			{
				H[N - 1 - i] = ptr1->second;//insert (N-1-i, H[curRand]) pair
				ptr1->second = N - 1 - i;//update H[curRand] = N-1-i
			}
			else
			{
				//swap H[curRand] and H[N-1-i]
				int tmp = ptr1->second;
				ptr1->second = ptr2->second;
				ptr2->second = tmp;
			}
		}

		std::vector<int> res;
		for (int i = 0; i < k; ++i)
			res.push_back(H[N - 1 - i]);

		std::cout << Debug::ToStr1D<int>()(H) << std::endl;
		std::cout << "RandomSubset UseOfflineSampling for \"" << k << " out of 0..." << N - 1 << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//O(k) time, O(k) space
	std::vector<int> UseOfflineSampling2(int N, int k)//better...looks more similar to offline sampling
	{
		//H tracks of "first k indices from begin and their mapped indices", as well as "other k indices and their mapped indices that were swapped with the first k indices"
		//so that H mimics the reservoir array of offline sampling

		std::unordered_map<int, int> H;//first: index whose val has been swapped, second: the index of the val
		for (int i = 0; i < k; ++i)
		{
			int curRandIdx = rand() % (N - i) + i;//random index in [i, N-1]
			auto ptr1 = H.find(curRandIdx);
			auto ptr2 = H.find(i);//index from begin
			if (ptr1 == H.end() && ptr2 == H.end())
			{
				H[curRandIdx] = i;//insert (curRandIdx, i) pair
				H[i] = curRandIdx;//insert (i, curRand) pair
			}
			else if (ptr1 == H.end() && ptr2 != H.end())
			{
				H[curRandIdx] = ptr2->second;//insert (curRandIdx, H[i]) pair
				ptr2->second = curRandIdx;//update H[i] = curRandIdx
			}
			else if (ptr1 != H.end() && ptr2 == H.end())
			{
				H[i] = ptr1->second;//insert (i, H[curRandIdx]) pair
				ptr1->second = i;//update H[curRandIdx] = i
			}
			else
			{
				//swap H[curRandIdx] and H[i]
				int tmp = ptr1->second;
				ptr1->second = ptr2->second;
				ptr2->second = tmp;
			}
		}

		std::vector<int> res;
		for (int i = 0; i < k; ++i)
			res.push_back(H[i]);

		std::cout << Debug::ToStr1D<int>()(H) << std::endl;
		std::cout << "RandomSubset UseOfflineSampling2 for \"" << k << " out of 0..." << N - 1 << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
[8,5], [7,11], [15,8], [2,13], [14,2], [13,14], [11,7], [3,12], [12,3], [0,10], [10,0], [9,15], [5,9]
RandomSubset UseOfflineSampling for "8 out of 0...15": 8, 2, 14, 3, 7, 0, 15, 5
[13,0], [0,13], [14,1], [1,14], [3,12], [11,6], [2,11], [12,3], [7,10], [4,7], [15,5], [5,15], [6,2], [10,4]
RandomSubset UseOfflineSampling2 for "8 out of 0...15": 13, 14, 11, 12, 7, 15, 2, 10
*/
#endif