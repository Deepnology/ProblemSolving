#ifndef MISSING_IP_ADDRESS_H
#define MISSING_IP_ADDRESS_H
#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string>
#include <numeric>
#include "Debug.h"
#include "TestCase.h"
/*
Elements of programming interview, Searching: Find the missing IP address
https://github.com/epibook/epibook.github.io/blob/master/solutions/cpp/Missing_element.cc
The storage capacity of hard drives dwarfs that of RAM.
This can lead to interesting space-time trade-offs.

Suppose you were given a file containing roughly one billion IP addresses, each of which is a 32-bit unsigned integer.
How would you programmatically find an IP address that is not in the file?
Assume you have unlimited drive space but only two megabytes of RAM at your disposal.

In the first step, we build an array of 2^16 32-bit unsigned integers that is initialized to 0
, and for every IP address in the file, we take its 16 MSBs to index into this array and increment the count of that number.
Since the file contains fewer than 2^32 numbers, there must be one entry in the array that is less than 2^16.
This tells us that there is at least one IP address which has those upper bits and is not in the file.
In the second pass, we can focus only on the addresses that match this criterion and use a bit array of size 2^16 to identify one of the missing numbers.

IP address:
255.255.255.255
2^8.2^8.2^8.2^8
8bit.8bit.8bit.8bit
32 bits in total can represent an IP address
so an unsigned 32-bit integer can represent an IP address
, which can be divided into 4 8-bit numbers

1 MB = 1 024 000 bytes = 1000 * 1024 bytes = 1024^2 bytes = 2^20 bytes
*/
class MissingIPaddress
{
public:
	MissingIPaddress(){}
	~MissingIPaddress(){}

	int Find(std::ifstream & ifs)
	{
		//1. count the upper 16 bits of each IP address
		std::vector<unsigned int> upper16bitCount(1 << 16, 0);//size of 2^16 for all upper 16 bit combinations
		unsigned int buf;
		while (ifs >> buf)//first pass of all IP addresses
			++upper16bitCount[buf >> 16];//take the upper 16 bits, find it and increment


		//2. find one bucket contains less than 2^16 elements
		int candidateBucket;
		for (int i = 0; i < (int)upper16bitCount.size(); ++i)
		{
			if (upper16bitCount[i] < (1 << 16))
			{
				candidateBucket = i;
				break;
			}
		}


		//3. find all IP addresses in the stream whose upper 16 bits are equal to candidateBucket, and mark the found IP addresses in lower16bitVec
		std::bitset<(1 << 16)> lower16bitVec;//2^16 bit vec (of all lower 16 bit combinations) for all those IP addresses in file whose upper 16 bits are equal to candidateBucket
		ifs.clear();
		ifs.seekg(0, std::ios::beg);
		while (ifs >> buf)//second pass of all IP addresses
		{
			int upper16 = buf >> 16;
			if (candidateBucket == upper16)
			{
				int lower16 = ((1 << 16) - 1) & buf;
				lower16bitVec.set(lower16);//set the bit at position lower16 to be 1
			}
		}
		ifs.close();


		//4. at least one of the lower 16 bit combinations is absent, find it
		for (int i = 0; i < (1 << 16); ++i)
		{
			if (lower16bitVec[i] == 0)
			{
				int res = (candidateBucket << 16) | i;
				std::cout << "MissingIPaddress Find: " << res << std::endl;
				return res;
			}
		}


		std::cout << "MissingIPaddress Find: no missing element" << std::endl;
		return -1;
	}

	void Test()
	{
		int N = 10000;
		std::vector<int> A(N);
		std::iota(A.begin(), A.end(), 0);
		//std::cout << Debug::ToStr1D<int>()(A) << std::endl;
		std::ofstream ofs("missing.txt");
		for (int i = 0; i < N; ++i)
		{
			if (i != 7788)
			{
				ofs << A[i] << std::endl;
			}
		}
		A.clear();
		ofs.close();
		std::ifstream ifs("missing.txt");
		int missing = this->Find(ifs);
		std::remove("missing.txt");
	}
};
/*
MissingIPaddress Find: 7788
*/
#endif