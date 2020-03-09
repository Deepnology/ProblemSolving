#ifndef GET_SET_TOGGLE_BIT_H
#define GET_SET_TOGGLE_BIT_H
#include <iostream>
#include <string>
#include <sstream>
/*

*/
class GetSetToggleBit
{
public:
	GetSetToggleBit(){}
	~GetSetToggleBit(){}

	void GetBit(int n, int index)
	{
		std::cout << "GetBit for \"" << index << "-th\" bit in \"" << n << "\": " << this->getBit(n, index) << std::endl;
	}
	void SetBit(int n, int index, bool b)
	{
		std::cout << "SetBit for \"" << b << "\" at \"" << index << "-th\" bit in \"" << n << "\": " << this->setBit(n, index, b) << std::endl;
	}
	void ToggleBit(int n, int index)
	{
		std::cout << "ToggleBit for \"" << index << "-th\" bit in \"" << n << "\": " << this->toggleBit(n, index) << std::endl;
	}

	bool getBit(int n, int index)
	{
		//return ((n & (1 << index)) > 0);//-->incorrect for 10000000000000000000000000000000
		return ((n >> index) & 1) > 0;
	}
	int setBit(int n, int index, bool b)
	{
		if (b)
			return n | (1 << index);
		else
		{
			int mask = ~(1 << index);
			return n & mask;
		}
	}
	int toggleBit(int n, int index)
	{
		return n ^ (1 << index);
	}
};
/*
GetBit for "10-th" bit in "764234981": 1
SetBit for "0" at "10-th" bit in "764234981": 764233957
ToggleBit for "10-th" bit in "764234981": 764233957
*/
#endif