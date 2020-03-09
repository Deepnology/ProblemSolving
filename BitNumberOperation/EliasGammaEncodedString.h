#ifndef ELIAS_GAMMA_ENCODED_STRING_H
#define ELIAS_GAMMA_ENCODED_STRING_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Implement Elias Gamma Encoding
The Elias gamma code is used to encode positive integers.
Specifically, the Elias gamma code of a positive integer n is computed as follows.
-Write n in binary to form string b
-Subtract 1 from the "number of bits" written in the first step, and add that many zeros to the beginning of string b

For example, the binary representation of 13 is 1101, which takes 4 bits to write.
Hence, the Elias Gamma code for 13 is 0001101.

Encode:
1. transform decimal to binary and count numOfBits
2. prepend "numOfBits - 1" 0s to binary form

Decode:
1. count consecutive 0s from begin till a first 1, which is the begin of binary
2. transform the binary starting from the first 1 with length of "numOfConsecutive0s + 1" into decimal
3. remove the transformed binary and repeat

O(n) time
*/
class EliasGammaEncodedString
{
public:
	EliasGammaEncodedString(){}
	~EliasGammaEncodedString(){}

	std::string Encode(const std::vector<int> & nums)
	{
		std::string res;
		int N = nums.size();
		for (int i = 0; i < N; ++i)
		{
			std::string binary = this->IntToBinStr(nums[i]);
			binary.insert(0, binary.size() - 1, '0');//prepend 0s
			res += binary;
		}

		std::cout << "EliasGammaEncodedString Encode for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
	std::vector<int> Decode(const std::string & s)
	{
		std::vector<int> res;
		int N = s.size();
		int idx = 0;
		while (idx < N)
		{
			int zeroIdx = idx;
			while (zeroIdx < N && s[zeroIdx] == '0')
				++zeroIdx;

			/*
			now zeroIdx points to the leftmost digit that is not zero
			zeroCount = zeroIdx - idx
			nonZeroCount = zeroCount + 1 = zeroIdx - idx + 1
			*/
			int nonZeroLen = zeroIdx - idx + 1;
			res.push_back(this->BinStrToInt(s.substr(zeroIdx, nonZeroLen)));
			idx = zeroIdx + nonZeroLen;
		}

		std::cout << "EliasGammaEncodedString Decode for \"" << s << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

private:
	std::string IntToBinStr(int positive)
	{
		std::string res;
		while (positive)
		{
			int curLowestBit = positive % 2;
			positive >>= 1;
			res = std::to_string(curLowestBit) + res;
		}
		return res;
	}
	int BinStrToInt(const std::string & binary)
	{
		int res = 0;
		int N = binary.size();
		for (int i = 0; i < N; ++i)
		{
			res = res * 2 + (binary[i] - '0');
		}
		return res;
	}
};
/*
EliasGammaEncodedString Encode for "9, 4, 37, 17, 3": 00010010010000000100101000010001011
EliasGammaEncodedString Decode for "00010010010000000100101000010001011": 9, 4, 37, 17, 3
*/
#endif