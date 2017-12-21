#ifndef PARITY_OF_NUM_H
#define PARITY_OF_NUM_H
#include <string>
#include <iostream>
/*
Elements of programming interview, PrimitiveTypes: Compute parity
The parity of a binary word is 1 if the number of 1s in the word is odd; otherwise, 0.

FourBitParityLookup: O(n/4) time, where n is the number of bits, 4 is the length of words for which we cache the results
(the time complexity is a function of the size of the keys used to index the lookup table)

Flip the lowest set bit: O(k) time, where k is the number of set bits
BruteForce: O(n) time, where n is the number of bits

lookup table for a 4 bit number:
0x6996 //0b0110100110010110
num: parity
0=0000: 0
1=0001: 1
2=0010: 1
3=0011: 0
4=0100: 1
5=0101: 0
6=0110: 0
7=0111: 1
8=1000: 1
9=1001: 0
10=1010: 0
11=1011: 1
12=1100: 0
13=1101: 1
14=1110: 1
15=1111: 0
*/
class ParityOfNum
{
public:
	ParityOfNum(){}
	~ParityOfNum(){}

	unsigned short FourBitParityLookup(unsigned long long n)
	{
		std::cout << "ParityOfNum FourBitParityLookup for \"" << n << "\": ";

		/*
		use the property that the order in which we perform XOR does not change the result, e.g., XOR commutes:
		the parity of a 64 bit number equals "XOR of the parity of higher 32 bits with the parity of lower 32 bits"
		*/

		n ^= n >> 32;//the result lower 32 bits is "XOR of the higher 32 bits and the lower 32 bits"
		n ^= n >> 16;//the result lower 16 bits is "XOR of the 2nd lower 16 bits and the lower 16 bits"
		n ^= n >> 8;//the result lower 8 bits is "XOR of the 2nd lower 8 bits and the lower 8 bits"
		n ^= n >> 4;//the result lower 4 bits is "XOR of the 2nd lower 4 bits and the lower 4 bits"
		n &= 0xf;//keep only the lower 4 bits to lookup in table

		//the LSB of kFourBitLookupTable is the parity of 0, next bit is parity of 1, followed by the parity of 2, etc
		//the MSB of kFourBitLookupTable is the parity of 15
		const int kFourBitLookupTable = 0x6996;//0b0110100110010110

		unsigned short res = (kFourBitLookupTable >> n) & 1;

		std::cout << res << std::endl;
		return res;
	}

	unsigned short Solve(unsigned long long n)
	{
		std::cout << "ParityOfNum for \"" << n << "\": ";

		unsigned short res = 0;
		while (n)
		{
			res ^= 1;//flip res
			n &= (n - 1);//flip the lowest set bit to 0
		}
		
		std::cout << res << std::endl;
		return res;
	}

	unsigned short BruteForce(unsigned long long n)
	{
		std::cout << "ParityOfNum BruteForce for \"" << n << "\": ";

		unsigned short res = 0;
		while (n)
		{
			res ^= (n & 1);
			n >>= 1;
		}

		std::cout << res << std::endl;
		return res;
	}


	
};
/*
ParityOfNum FourBitParityLookup for "56": 1
ParityOfNum for "56": 1
ParityOfNum BruteForce for "56": 1
*/
#endif