#ifndef DIFF_BITS_BTW_2_INT_H
#define DIFF_BITS_BTW_2_INT_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Leetcode: Hamming Distance
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Given two integers x and y, calculate the Hamming distance.

Cracking the coding interview 5.5
Determine the number of bits required to convert integer A to integer B

Each 1 in the xor of A and B will represent one different bit btw A and B
We simply need to count the number of bits that are 1 in xor or A and B

See also CountSetBits.h

Leetcode: Total Hamming Distance
Now your job is to find the total Hamming distance between all pairs of the given numbers.
Example:
Input: 4, 14, 2
Output: 6
Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Note:
Elements of the given array are in the range of 0 to 10^9
Length of the array will not exceed 10^4.

*/
class DiffBitsBtw2Int
{
public:
	DiffBitsBtw2Int(){}
	~DiffBitsBtw2Int(){}

	int Count_1s_in_XOR(int a, int b)
	{
		int count = 0;
		int XOR = a ^ b;
		while (XOR != 0)
		{
			count += XOR & 1;
			XOR >>= 1;
		}
		/*
		for (int XOR = a ^ b; XOR != 0; XOR >>= 1)
			count += XOR & 1;
		*/
		std::cout << "DiffBitsBtw2Num for \"" << KeyGenAux().UIntToBinStr(a) << "\", \"" << KeyGenAux().UIntToBinStr(b) << "\": " << count << std::endl;
		return count;
	}

	/*
	n = n & (n-1)
	n			1101011000
	n-1			1101010111
	n&(n-1)		1101010000
	=> flip the lowest 1 to 0
	See also PowOf2.h
	*/
	int Count_1s_in_XOR2(int a, int b)
	{
		int count = 0;
		int XOR = a ^ b;
		while (XOR != 0)
		{
			++count;
			XOR &= (XOR - 1);
		}
		/*
		for (int XOR = a ^ b; XOR != 0; XOR &= (XOR - 1))
			++count;
		*/
		std::cout << "DiffBitsBtw2Num for \"" << KeyGenAux().UIntToBinStr(a) << "\", \"" << KeyGenAux().UIntToBinStr(b) << "\": " << count << std::endl;
		return count;
	}

	int TotalHammingDist(const std::vector<int> & nums)//O(32*n) time
	{
		int total = 0;
		int N = nums.size();
		for (int j = 0; j < 32; ++j)
		{
			int bitCount = 0;
			for (int i = 0; i < N; ++i)
				bitCount += (nums[i] >> j) & 1;

			total += bitCount*(N - bitCount);//!!!!!
		}

		std::cout << "DiffBitsBtw2Num TotalHammingDist for \"" << Debug::ToStr1D<int>()(nums) << "\": " << total << std::endl;
		return total;
	}
};
/*
DiffBitsBtw2Num for "00000000000000000000000110110000", "00000000000000000000000001111011": 6
DiffBitsBtw2Num for "00000000000000000000000110110000", "00000000000000000000000001111011": 6
DiffBitsBtw2Num TotalHammingDist for "4, 14, 2": 6
*/
#endif