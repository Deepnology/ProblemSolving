#ifndef VALID_UTF8_OCTET_SEQUENCE_H
#define VALID_UTF8_OCTET_SEQUENCE_H
#include "Debug.h"
/*
Leetcode: UTF-8 Validation
A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:
For 1-byte character, the first bit is a 0, followed by its unicode code.
For n-bytes character, the first n-bits are all one's, the n+1 bit is 0, followed by n-1 bytes with most significant 2 bits being 10.
This is how the UTF-8 encoding would work:

   Char. number range  |        UTF-8 octet sequence
      (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
Given an array of integers representing the data, return whether it is a valid utf-8 encoding.

Note:
The input is an array of integers. Only the least significant 8 bits of each integer is used to store the data. This means each integer represents only 1 byte of data.

Example 1:
data = [197, 130, 1], which represents the octet sequence: 11000101 10000010 00000001.
Return true.
It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.

Example 2:
data = [235, 140, 4], which represented the octet sequence: 11101011 10001100 00000100.
Return false.
The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes character.
The next byte is a continuation byte which starts with 10 and that's correct.
But the second continuation byte does not start with 10, so it is invalid.
*/
class ValidUTF8OctetSequence
{
public:
	ValidUTF8OctetSequence() {}

	bool Validate(const std::vector<int> & data)
	{
		bool res = validUtf8(data);
		std::cout << "ValidUTF8OctetSequence for \"" << Debug::ToStr1D<int>()(data) << "\": " << res << std::endl;
		return res;
	}

	bool validUtf8(const std::vector<int> & data)
	{
		int N = data.size();
		if (N == 0) return false;

		int curByte = 0;
		for (int i = 0; i < N; ++i)
		{
			if (curByte == 0)//data[i] is the the header byte: "1..10x..x"
			{
				if (((data[i] >> 7) & 1) == 0)//1 byte sequence
					continue;
				else//non 1 byte sequence
				{
					for (int j = 7; j >= 3; --j)
					{
						if (((data[i] >> j) & 1) == 1)
							++curByte;
						else
							break;
					}
					if (curByte < 2 || curByte > 4)//only 2 or 3 or 4 '1's are valid
						return false;
					--curByte;//count in header
				}
			}
			else//data[i] isn't the header byte: "10x..x"
			{
				--curByte;
				if (((data[i] >> 7) & 1) != 1)//check MSB
					return false;
				if (((data[i] >> 6) & 1) != 0)//check 2nd MSB
					return false;
			}
		}
		if (curByte != 0) return false;
		return true;
	}
};
/*
ValidUTF8OctetSequence for "197, 130, 1": 1
ValidUTF8OctetSequence for "235, 140, 4": 0
*/
#endif
