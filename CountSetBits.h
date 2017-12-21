#ifndef COUNT_SET_BITS_H
#define COUNT_SET_BITS_H
#include <iostream>
#include <sstream>
#include <string>
/*
https://leetcode.com/problems/number-of-1-bits/
Google
http://www.careercup.com/question?id=14584753
Count the number of set bits for an 32 bits integer.
How to improve the process for the second time use if the memory is unlimited?

See also DiffBitsBtw2Int.h
*/
class CountSetBits
{
public:
	CountSetBits(){}
	~CountSetBits(){}

	int Solve(unsigned int n)
	{
		std::cout << "CountSetBits for \"" << n << "\": ";

		int count = 0;
		while (n)
		{
			count += (n & 1);
			n >>= 1;
		}
		
		std::cout << count << std::endl;
		return count;
	}

	int Sparse(unsigned int n)
	{
		std::cout << "CountSetBits Sparse for \"" << n << "\": ";

		int count = 0;
		while (n)
		{
			++count;
			n &= (n - 1);//flip the lowest set bit to 0
		}

		std::cout << count << std::endl;
		return count;
	}

	int Dense(unsigned int n)
	{
		std::cout << "CountSetBits Dense for \"" << n << "\": ";

		int count = sizeof(unsigned int) * 8;
		n = ~n;
		while (n)
		{
			--count;
			n &= (n - 1);//flip the lowest set bit to 0
		}

		std::cout << count << std::endl;
		return count;
	}

private:
	static int bitInChar[256];
public:
	static void FillBitsInChar()//cache fixed results
	{
		/*
		for 1 to 255 (8-bits)
		calculate the set bit count of each specific number
		*/
		for (int i = 0; i < 256; ++i)
		{
			int count = 0;
			int n = i;
			while (n)
			{
				count += n & 1;
				n >>= 1;
			}
			bitInChar[i] = count;
		}
	}
	int ConstTime(unsigned int n)//use cached fixed results
	{
		int res = bitInChar[n & 0xffu] + //the lowest 8 bits
			bitInChar[(n >> 8) & 0xffu] + 
			bitInChar[(n >> 16) & 0xffu] + 
			bitInChar[(n >> 24) & 0xffu];//the highest 8 bits
		std::cout << "CountSetBits ConstTime for \"" << n << "\": " << res << std::endl;
		return res;
	}


public:
	/*
	O(logn) time, where n is the number of bits

	We are taking all the odd bits and all the even bits, and then shifting the odd bits over so they're in the even positions.
	So if we had 11010011, we'd now have 100000010 (odd bits) >> 1 = 01000001, and 01010001 (even bits).
	Now we'll just add the two, but because of the way this has been structured, there's guaranteed space for the carries.

	So we end up with 10 01 00 10.
	Each group of 2 digits here represents the count of 1s in the corresponding two digits.
	Now we add each group of 2 digits together
	10 00 00 00 (odd group of 2) >> 2 = 00 10 00 00

	00 10 00 00
	00 01 00 10 (even group of 2)
	-----------
	00 11 00 10
	Each group of 4 has the count of 1s in that group of 4 bits.
	
	A finally step will similarly sum 0011 + 0010 = 0101. This is the final answer of 5 set bits.
	*/
	int Tricky(int n)
	{
		int count = n;
		/*                even bits                odd bits*/
		/*                 0x5=0101                0xa=1010*/
		count = (count & 0x55555555) + ((count & 0xaaaaaaaa) >> 1);
		/*                 0x3=0011                0xc=1100*/
		count = (count & 0x33333333) + ((count & 0xcccccccc) >> 2);
		/*            0x0f=00001111           0xf0=11110000*/
		count = (count & 0x0f0f0f0f) + ((count & 0xf0f0f0f0) >> 4);
		/*  0x00ff=0000000011111111 0xff00=1111111100000000*/
		count = (count & 0x00ff00ff) + ((count & 0xff00ff00) >> 8);
		/*00000000000000001111111111111111 11111111111111110000000000000000*/
		count = (count & 0x0000ffff) + ((count & 0xffff0000) >> 16);

		std::cout << "CountSetBits Tricky for \"" << n << "\": " << count << std::endl;
		return count;
	}
};

int CountSetBits::bitInChar[];

/*
CountSetBits for "56": 3
CountSetBits Sparse for "56": 3
CountSetBits Dense for "56": 3
CountSetBits ConstTime for "56": 3
CountSetBits Tricky for "56": 3
*/
#endif