#ifndef REVERSE_BITS_H
#define REVERSE_BITS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "KeyGenAux.hpp"
/*
https://leetcode.com/problems/reverse-bits/
Elements of programming interview, PrimitiveTypes: LookupTable
see also SwapTwoBits.h
*/
class ReverseBits
{
public:
	ReverseBits(){}
	~ReverseBits(){}

	unsigned int BruteForce(unsigned int n)
	{
		unsigned int original = n;
		unsigned int res = 0;
		for (int i = 0; i < 32; ++i)
		{
			res = (res << 1) | (n & 1);
			n >>= 1;
		}

		std::cout << "ReverseBit BruteForce for \"" << original << "\": " << res << std::endl;
		return res;
	}

	unsigned int SwapTwoBits(unsigned int n)
	{
		int bitCount = sizeof(unsigned int) * 8;
		int halfBitCount = bitCount >> 1;/*divided by 2*/
		unsigned int res = n;
		for (int i = 0; i < halfBitCount; ++i)
		{
			res = this->Swap(res, i, bitCount - i - 1);
		}

		std::cout << "ReverseBit SwapTwoBits for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	unsigned int Swap(unsigned int n, int idx1, int idx2)
	{
		int res = n;
		if (((n >> idx1) & 1) != ((n >> idx2) & 1))
		{
			/*
			when the idx1 bit is diff from the idx2 bit, i.e., one is 1 and the other is 0
			, flip the two bits individually by XOR with bit 1
			*/
			res ^= (1 << idx1) | (1 << idx2);
		}
		return res;
	}

public:
	unsigned long long LookupTable(unsigned long long n)
	{
		const int kWordSize = 16;
		const int kBitMask = 0xffff;

		//cache a lookup table for precomputed reversed 16-bit numbers (2^16 numbers in total)
		static std::vector<unsigned short> Bit16NumReverseTable = this->CreateLookupTable_2Pow16();

		unsigned long long res = static_cast<unsigned long long>(Bit16NumReverseTable[n & kBitMask]) << (3 * kWordSize) |//the resulted higher 4 bits
			static_cast<unsigned long long>(Bit16NumReverseTable[(n >> kWordSize) & kBitMask]) << (2 * kWordSize) |//the resulted 2nd higher 4 bits
			static_cast<unsigned long long>(Bit16NumReverseTable[(n >> 2 * kWordSize) & kBitMask]) << kWordSize |//the resulted 3rd higher 4 bits
			static_cast<unsigned long long>(Bit16NumReverseTable[(n >> 3 * kWordSize) & kBitMask]);//the resulted lower 4 bits

		std::cout << "ReverseBit LookupTable for \"" << n << "\": " << res << ". " << KeyGenAux().UInt64ToBinStr(n) << ": " << KeyGenAux().UInt64ToBinStr(res) << std::endl;
		return res;
	}
private:
	std::vector<unsigned short> CreateLookupTable_2Pow16()
	{
		std::vector<unsigned short> res;
		for (unsigned int i = 0; i < (1 << 16); ++i)
			res.emplace_back(this->ReverseNum(i, 16));//reverse the lower 16 bits
		return res;
	}
	unsigned int ReverseNum(unsigned int n, unsigned int length)
	{
		for (int i = 0, j = length - 1; i < j; ++i, --j)
			n = this->Swap(n, i, j);
		return n;
	}

public:
	unsigned int Mirror(unsigned int n)
	{
		int res = n;
		for (int i = 0; i < 16; ++i)
		{
			res = (res & (0xffffffff - (1 << i) - (1 << (31 - i)))) |/*get all isolated bits except right bit and left bit*/
				((n & (1 << i)) << (31 - i * 2)) |/*get isolated right bit then shift to left*/
				((n & (1 << (31 - i))) >> (31 - i * 2));/*get isolated left bit then shift to right*/
		}
		/*
		 (31-i)     (31-i*2)      (i)
		<------>|<------------>|<----->
		31....left....mid....right....0
		*/
		std::cout << "ReverseBit Mirror for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
ReverseBit BruteForce for "56": 469762048
ReverseBit SwapTwoBits for "56": 469762048
ReverseBit LookupTable for "56": 2017612633061982208. 0000000000000000000000000000000000000000000000000000000000111000: 0001110000000000000000000000000000000000000000000000000000000000
ReverseBit Mirror for "56": 469762048
UIntToBinStr for "469762048": 00011100000000000000000000000000
*/
#endif