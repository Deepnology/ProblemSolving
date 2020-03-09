#ifndef NUMBER_COMPLEMENT_H
#define NUMBER_COMPLEMENT_H
#include "Debug.h"
#include "IntToBinStr.h"
/*
Leetcode: Number Complement
Given a positive integer, output its complement number.
The complement strategy is to flip the bits of its binary representation. (Don't flip leading 0s !!!!)
(If flipping leading 0s, it will become one's complement, which is equal to ~n.)
Note:
The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer¡¦s binary representation.
Example 1:
Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
Example 2:
Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
*/
class NumberComplement
{
public:
	NumberComplement() {}

	int Solve(int num)
	{
		int res = 0;
		for (int i = 0; i < 32; ++i)//from lowest bit to highest bit
		{
			int cur = (num >> i);
			if (cur == 0) break;//early stop to skip flipping leading 0s
			res |= (((cur & 1) ^ 1) << i);
		}

		std::cout << "NumberComplement for \"" << num << "\"(" << IntToBinStr().FullLength(num) << "): " << res << "(" << IntToBinStr().FullLength(res) << ")" << std::endl;
		std::cout << "OnesComplement for \"" << num << "\"(" << IntToBinStr().FullLength(num) << "): " << ~num << "(" << IntToBinStr().FullLength(~num) << ")" << std::endl;
		return res;
	}

	int Solve2(int num)
	{
		unsigned mask = ~0;
		while (num & mask)
			mask <<= 1;
		return ~mask & ~num;//~num then revert flipped leading 0s back to 0s
	}
};
/*
NumberComplement for "1"(00000000000000000000000000000001): 0(0)
OnesComplement for "1"(00000000000000000000000000000001): -2(11111111111111111111111111111110)
NumberComplement for "2147483647"(01111111111111111111111111111111): 0(0)
OnesComplement for "2147483647"(01111111111111111111111111111111): -2147483648(10000000000000000000000000000000)
NumberComplement for "2147483646"(01111111111111111111111111111110): 1(00000000000000000000000000000001)
OnesComplement for "2147483646"(01111111111111111111111111111110): -2147483647(10000000000000000000000000000001)
NumberComplement for "-2147483648"(10000000000000000000000000000000): 2147483647(01111111111111111111111111111111)
OnesComplement for "-2147483648"(10000000000000000000000000000000): 2147483647(01111111111111111111111111111111)
NumberComplement for "-2147483647"(10000000000000000000000000000001): 2147483646(01111111111111111111111111111110)
OnesComplement for "-2147483647"(10000000000000000000000000000001): 2147483646(01111111111111111111111111111110)
NumberComplement for "0"(0): 0(0)
OnesComplement for "0"(0): -1(11111111111111111111111111111111)
NumberComplement for "-3"(11111111111111111111111111111101): 2(00000000000000000000000000000010)
OnesComplement for "-3"(11111111111111111111111111111101): 2(00000000000000000000000000000010)
NumberComplement for "3"(00000000000000000000000000000011): 0(0)
OnesComplement for "3"(00000000000000000000000000000011): -4(11111111111111111111111111111100)
NumberComplement for "-255"(11111111111111111111111100000001): 254(00000000000000000000000011111110)
OnesComplement for "-255"(11111111111111111111111100000001): 254(00000000000000000000000011111110)
NumberComplement for "255"(00000000000000000000000011111111): 0(0)
OnesComplement for "255"(00000000000000000000000011111111): -256(11111111111111111111111100000000)
NumberComplement for "-4"(11111111111111111111111111111100): 3(00000000000000000000000000000011)
OnesComplement for "-4"(11111111111111111111111111111100): 3(00000000000000000000000000000011)
NumberComplement for "4"(00000000000000000000000000000100): 3(00000000000000000000000000000011)
OnesComplement for "4"(00000000000000000000000000000100): -5(11111111111111111111111111111011)
NumberComplement for "-5"(11111111111111111111111111111011): 4(00000000000000000000000000000100)
OnesComplement for "-5"(11111111111111111111111111111011): 4(00000000000000000000000000000100)
NumberComplement for "5"(00000000000000000000000000000101): 2(00000000000000000000000000000010)
OnesComplement for "5"(00000000000000000000000000000101): -6(11111111111111111111111111111010)
*/
#endif
