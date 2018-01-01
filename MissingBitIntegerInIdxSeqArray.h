#ifndef MISSING_BIT_INTEGER_IN_IDX_SEQ_ARRAY_H
#define MISSING_BIT_INTEGER_IN_IDX_SEQ_ARRAY_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Google
http://www.careercup.com/question?id=2466716
Cracking the coding interview 5.7
Given an array A containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
For example,
Given nums = [0, 1, 3] return 2.
The elements of A are represented in binary, and the only operation we can use to access them is "fetch the j-th bit of A[i]", which takes constant time.
Find the missing integer in O(n) time.

We can calculate the missing integer bit-by-bit by counting the i-th bit from right of remaining integers.
If the count of the i-th bit "0" from right of remaining integers is <= the count of the i-th bit "1" from right of the remaining integers, then the missing integer's i-th bit from right must be "0".
If the count of the i-th bit "0" from right of remaining integers is > the count of the i-th bit "1" from right of the remaining integers, then the missing integer's i-th bit from right must be "1".

Observation:
0, 1, 2, (3), 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
1. compare LSB_1
00000	00100	01000	01100
00001	00101	01001	01101
00010	00110	01010
-----	00111	01011
=> count(LSB_1(0)) = 7 > count(LSB_1(1)) = 6
=> missing integer's LSB_1 must be 1
=> keep only integers whose LSB_1 is 1

2. compare LSB_2
00001	00101	01001	01101
-----	00111	01011
=> count(LSB_2(0)) = 4 > count(LSB_2(1)) = 2
=> missing integer's LSB_2 must be 1
=> keep only integers whose LSB_2 is 1

3. compare LSB_3
-----	00111	01011
=> count(LSB_3(0)) = 1 <= count(LSB_3(1)) = 1
=> missing integer's LSB_3 must be 0
=> keep only integers whose LSB_3 is 0

4. compare LSB_4
-----	01011
=> count(LSB_4(0)) = 0 <= count(LSB_4(1)) = 1
=> missing integer's LSB_4 must be 0
=> keep only integers whose LSB_4 is 0

4. compare LSB_5
-----
=> count(LSB_5(0)) = 0 <= count(LSB_5(1)) = 0
=> missing integer's LSB_5 must be 0
=> keep only integers whose LSB_5 is 0
.
.
.

Note:
LSB_N: least significant N-th bit from right
LSB_N(0): least significant N-th bit from right which is "0"
LSB_N(1): least significant N-th bit from right which is "1"
count(LSB_N(0)): the count of LSB_N(0) from the remaining integers
count(LSB_N(1)): the count of LSB_N(1) from the remaining integers

Conclusion:
If n is odd, the total LSB_1 of 0 must be equal to the total LSB_1 of 1
If n is even, the total LSB_1 of 0 must be one more greater than the total LSB_1 of 1
=> the total LSB_1 of 0 must be equal to or one more greater than the total LSB_1 of 1
=> we can determine the LSB_1 of the missing integer:
if count(LSB_1(0)) <= count(LSB_1(1)), the LSB_1 of the missing integer must be 0
if count(LSB_1(0)) > count(LSB_1(1)), the LSB_1 of the missing integer must be 1

(If count(LSB_1(0)) == count(LSB_1(1)), 
can the LSB_1 of missing integer be 0? Yes, after adding a 0, count(LSB_1(0)) becomes one more than count(LSB_1(1)),
can the LSB_1 of missing integer be 1? No, after adding a 1, count(LSB_1(0)) becomes one less than count(LSB_1(1)).)

Once the LSB_1 of the missing integer has been determined, we just need to keep those integers whose LSB_1 is same as the missing integer to compare the count of next left bit of 0 and 1

Complexity:
O(n) + O(n/2) + O(n/4) + O(n/8) + ... = O(2n) = O(n)
*/
class MissingBitIntegerInIdxSeqArray
{
public:
	MissingBitIntegerInIdxSeqArray(){}
	~MissingBitIntegerInIdxSeqArray(){}

	int FindIterate(const std::vector<int> & A)
	{
		int N = A.size();
		std::vector<int> v(A);
		int res = 0;

		//for each bit
		for (int i = 0; i < 32; ++i)
		{
			//1. count number of entries in A whose bit at i is 0 and whose bit at i is 1, respectively
			int zeroCount = 0;
			int oneCount = 0;
			for (int j = 0; j < (int)v.size(); ++j)
			{
				if (!this->GetBit(v[j], i))
					++zeroCount;
				else
					++oneCount;
			}

			//2. judge missing integer's bit at i, and keep only same bit nums in v
			if (zeroCount <= oneCount)//missing integer's bit at i is 0
			{
				res = this->SetBit(res, i, false);
				for (auto itr = v.begin(); itr != v.end();)//remove all entries in v whose bit at i is 1 (keep those 0s)
				{
					if (!this->GetBit(*itr, i))
						++itr;
					else
						itr = v.erase(itr);
				}
			}
			else//missing integer's bit at i is 1
			{
				res = this->SetBit(res, i, true);
				for (auto itr = v.begin(); itr != v.end();)//remove all entries in v whose bit at i is 0 (keep those 1s)
				{
					if (this->GetBit(*itr, i))
						++itr;
					else
						itr = v.erase(itr);
				}
			}
			//std::cout << res << ": " << Debug::ToStr1D<int>()(v) << std::endl;
			if (v.empty())
				break;//early stop bc the rest higher bits in res should be all 0s anyway
		}

		std::cout << "MissingBitIntegerInIdxSeqArray FindIterate for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return (int)res;
	}

	int FindRecur(const std::vector<int> & A)
	{
		int res = this->findRecur(A, 0);
		std::cout << "MissingBitIntegerInIdxSeqArray FindRecur for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
private:
	int findRecur(const std::vector<int> & A, int bitIdx)
	{
		if (bitIdx >= 31)
			return 0;

		//now count number of entries in A whose bit at bitIdx is 0 and whose bit at bitIdx is 1, respectively
		std::vector<int> oneBits;
		std::vector<int> zeroBits;
		int N = A.size();
		for (int i = 0; i < N; ++i)
		{
			if (!this->GetBit(A[i], bitIdx))
				zeroBits.push_back(A[i]);
			else
				oneBits.push_back(A[i]);
		}

		if (zeroBits.size() <= oneBits.size())//count(LSB_N(0)) <= count(LSB_N(1)), the missing integer's LSB_N must be 0
		{
			int v = this->findRecur(zeroBits, bitIdx + 1);//we keep only those integers whose LSB_N is 0 to compare the count of next left bit of 0 and 1
			return (v << 1) | 0;//insert a "0" bit to the right
		}
		else//count(LSB_N(0)) > count(LSB_N(1)), the missing integer's LSB_N must be 1
		{
			int v = this->findRecur(oneBits, bitIdx + 1);//we keep only those integers whose LSB_N is 1 to compare the count of next left bit of 0 and 1
			return (v << 1) | 1;//insert a "1" bit to the right
		}
	}

private:
	bool GetBit(int n, int index)
	{
		return ((n >> index) & 1) > 0;
	}
	int SetBit(int n, int index, bool b)
	{
		if (b)
			return n | (1 << index);
		else
		{
			int mask = ~(1 << index);
			return n & mask;
		}
	}

public:
	int UseXOR(const std::vector<int> & A)//Leetcode: Missing Number
	{
		int N = A.size();
		int XOR = 0;
		for (int i = 0; i < N; ++i)
		{
			XOR ^= A[i];
		}
		for (int i = 0; i <= N; ++i)
		{
			XOR ^= i;
		}

		std::cout << "MissingBitIntegerInIdxSeqArray UseXOR for \"" << Debug::ToStr1D<int>()(A) << "\": " << XOR << std::endl;
		return XOR;
	}
};
/*
MissingBitIntegerInIdxSeqArray FindIterate for "0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13": 3
MissingBitIntegerInIdxSeqArray FindIterate for "4, 3, 6, 9, 1, 8, 10, 2, 5, 0": 7
MissingBitIntegerInIdxSeqArray FindIterate for "1, 2, 3, 4, 5, 6, 8, 9, 10, 0": 7
MissingBitIntegerInIdxSeqArray FindRecur for "0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13": 3
MissingBitIntegerInIdxSeqArray FindRecur for "4, 3, 6, 9, 1, 8, 10, 2, 5, 0": 7
MissingBitIntegerInIdxSeqArray FindRecur for "1, 2, 3, 4, 5, 6, 8, 9, 10, 0": 7
MissingBitIntegerInIdxSeqArray UseXOR for "0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13": 3
MissingBitIntegerInIdxSeqArray UseXOR for "4, 3, 6, 9, 1, 8, 10, 2, 5, 0": 7
MissingBitIntegerInIdxSeqArray UseXOR for "1, 2, 3, 4, 5, 6, 8, 9, 10, 0": 7
*/
#endif