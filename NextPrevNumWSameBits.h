/*MUST*/
#ifndef NEXT_PREV_NUM_W_SAME_BITS_H
#define NEXT_PREV_NUM_W_SAME_BITS_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Google
http://www.careercup.com/question?id=5747769461440512
Cracking the coding interview 5.3
To keep same number of "1" bits, we must turn a "0" to "1" and turn a "1" to "0"
1.
To get the next big integer, we must turn a higher bit of "0" to "1" and turn a lower bit of "1" to "0"
Pick the higher bit of "0" as the first "0" that is followed by "1"
Pick the lower bit of "1" as the next right "1" of the first "0"
By turning this pair of higher "0" bit and lower "1" bit will guarantee a bigger integer
To keep the integer as small as possible, we move those remaining "1"s to the lowest side

init											11011001111100
flip the first "0" that is followed by "1"		11011011111100
flip the next right "1" of the first "0"		11011010111100
move the remaining "1"s to lowest				11011010001111

2.
To get the next small integer, we must turn a lower bit of "0" to "1" and turn a higher bit of "1" to "0"

init											10011110000011
flip the first "1" that is followed by "0"		10011100000011
flip the next right "0" of the first "1"		10011101000011
move the remaining "0" to lowest				10011101110000

See also ClosestNumWSameBits.h

Same strategy of NextPermutation.h and PreviousPermutation.h can be applied here too.
Next big: find ascendingEnd from right, reverse n[ascendingEnd]~n[end], find upper bound<less> of n[ascendingEnd-1] in n[ascendingEnd]~n[end] and swap.
Prev small: find descendingEnd from right, reverse n[descendingEnd]~n[end], find upper bound<greater> of n[descendingEnd-1] in n[descendingEnd]~n[end] and swap.
*/
class NextPrevNumWSameBits
{
public:
	NextPrevNumWSameBits(){}
	~NextPrevNumWSameBits(){}

	int GetNext(int n)
	{
		int beforeN = n;
		std::string before = KeyGenAux().UIntToBinStr(n);
		if (n == 0 || n == ~0) return -1;
		int curIdx = 0;
		int countZeros = 0;
		int countOnes = 0;

		while (curIdx < 32 && !this->GetBit(n, curIdx))
		{
			++curIdx;
			++countZeros;
		}
		//curIdx now points to the first 1

		while (curIdx < 32 && this->GetBit(n, curIdx))
		{
			++curIdx;
			++countOnes;
		}
		//curIdx now points to the first 0 that is followed by 1s
		if (curIdx == 32) return -1;

		n = this->SetBit(n, curIdx, true);
		++countZeros;
		--countOnes;
		--curIdx;

		while (countZeros--)
			n = this->SetBit(n, curIdx--, false);

		while (countOnes--)
			n = this->SetBit(n, curIdx--, true);

		std::cout << "NextPrevNumWSameBits GetNext for \"" << before << "(" << beforeN << ")\": " << KeyGenAux().UIntToBinStr(n) << "(" << n << ")" << std::endl;
		return n;
	}
	int GetPrev(int n)
	{
		int beforeN = n;
		std::string before = KeyGenAux().UIntToBinStr(n);
		if (n == 0 || n == ~0) return -1;
		int curIdx = 0;
		int countOnes = 0;
		int countZeros = 0;

		while (curIdx < 32 && this->GetBit(n, curIdx))
		{
			++curIdx;
			++countOnes;
		}
		//curIdx now points to the first 0

		while (curIdx < 32 && !this->GetBit(n, curIdx))
		{
			++curIdx;
			++countZeros;
		}
		//curIdx now points to the first 1 that is followed by 0s
		if (curIdx == 32) return -1;

		n = this->SetBit(n, curIdx, false);
		++countOnes;
		--countZeros;
		--curIdx;

		while (countOnes--)
			n = this->SetBit(n, curIdx--, true);

		while (countZeros--)
			n = this->SetBit(n, curIdx--, false);

		std::cout << "NextPrevNumWSameBits GetPrev for \"" << before << "(" << beforeN << ")\": " << KeyGenAux().UIntToBinStr(n) << "(" << n << ")" << std::endl;
		return n;
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
	//Leetcode: Next Greater Element III
	int NextGreaterElement(int n)
	{
		std::string s = std::to_string(n);
		int N = s.size();
		int i = N - 1;
		while (i>0 && s[i] <= s[i - 1])
			--i;
		std::reverse(s.begin() + i, s.end());
		if (i - 1 >= 0)
		{
			auto itr = std::upper_bound(s.begin() + i, s.end(), s[i - 1]);
			if (itr != s.end())
			{
				std::swap(s[i - 1], s[(itr - s.begin())]);
			}
			else
			{
				char c = s[i - 1];
				s.erase(i - 1, 1);
				s += c;
			}
			long long res = stoll(s);
			if (res >= INT_MAX) return -1;
			return (int)res;
		}
		else
			return -1;
	}
};
/*
NextPrevNumWSameBits GetNext for "00000000000000000011011001111100(13948)": 00000000000000000011011010001111(13967)
NextPrevNumWSameBits GetPrev for "00000000000000000011011001111100(13948)": 00000000000000000011011001111010(13946)
NextPrevNumWSameBits GetNext for "00000000000000000010011110000011(10115)": 00000000000000000010011110000101(10117)
NextPrevNumWSameBits GetPrev for "00000000000000000010011110000011(10115)": 00000000000000000010011101110000(10096)
NextPrevNumWSameBits GetNext for "00000000000000000000000000000001(1)": 00000000000000000000000000000010(2)
NextPrevNumWSameBits GetNext for "01111111111111111111111111111111(2147483647)": 10111111111111111111111111111111(-1073741825)
NextPrevNumWSameBits GetPrev for "10000000000000000000000000000000(-2147483648)": 01000000000000000000000000000000(1073741824)
NextPrevNumWSameBits GetPrev for "11111111111111111111111111111110(-2)": 11111111111111111111111111111101(-3)
NextPrevNumWSameBits GetPrev for "10000000000000000000000000000000(-2147483648)": 01000000000000000000000000000000(1073741824)
*/
#endif