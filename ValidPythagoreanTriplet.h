#ifndef VALID_PYTHAGOREAN_TRIPLET_H
#define vALID_PYTHAGOREAN_TRIPLET_H
#include "Debug.h"
/*
Amazon
http://www.geeksforgeeks.org/find-pythagorean-triplet-in-an-unsorted-array/
A Pythagorean triplet is a set of three natural numbers, a, b and c, for which a^2 + b^2 = c^2.
Given an integer array, returns true if there is a triplet with following property A[i]*A[i] = A[j]*A[j] + A[k]*[k].
*/
class ValidPythagoreanTriplet
{
public:
	ValidPythagoreanTriplet() {}

	bool HasTriplet_Greedy(std::vector<int> & v)//similar to 3sum
	{
		int N = v.size();
		std::vector<int> v2;
		for (int i = 0; i < N; ++i)
			v2.push_back(v[i] * v[i]);
		std::sort(v2.begin(), v2.end());
		
		for (int i = 0; i < N - 2; ++i)
		{
			int left = i + 1;
			int right = N - 1;
			while (left < right)
			{
				if (v2[i] + v2[left] == v2[right])
					return true;
				else if (v2[i] + v2[left] < v2[right])
					++left;
				else
					--right;
			}
		}
		return false;
	}
};
#endif
