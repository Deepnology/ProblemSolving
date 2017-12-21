#ifndef INT_TO_HEX_STR_H
#define INT_TO_HEX_STR_H
#include "Debug.h"
/*
Leetcode: Convert a number to hexadecimal
Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two¡¦s complement method is used.
Note:
All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s.
If the number is zero, it is represented by a single zero character '0'; otherwise, the first character in the hexadecimal string will not be the zero character.
The given number is guaranteed to fit within the range of a 32-bit signed integer.
You must not use any method provided by the library which converts/formats the number to hex directly.
Example 1:
Input:
26
Output:
"1a"
Example 2:
Input:
-1
Output:
"ffffffff"

see also UIntToBinStr.h
*/
class IntToHexStr
{
	std::vector<std::string> map = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f" };
public:
	IntToHexStr() {}
	
	std::string Convert(int num)
	{
		if (num == 0) return "0";
		std::string res;
		for (int i = 0; i <= 28; i += 4)//from lowest 4 bits to highest 4 bits
		{
			int cur = num >> i;
			if (cur == 0) break;//early stop to append extra 0s at front
			res = map[cur & 0xf] + res;
		}

		std::cout << "IntToHexStr for \"" << num << "\": " << res << " (" << FullLength(num) << ")" << std::endl;
		return res;
	}

	std::string FullLength(int num)
	{
		if (num == 0) return "0";
		std::string res;
		for (int i = 0; i <= 28; i += 4)//from lowest 4 bits to highest 4 bits
		{
			int cur = num >> i;
			res = map[cur & 0xf] + res;
		}
		return res;
	}
};
/*
IntToHexStr for "26": 1a (0000001a)
IntToHexStr for "-1": ffffffff (ffffffff)
IntToHexStr for "2147483647": 7fffffff (7fffffff)
IntToHexStr for "2147483646": 7ffffffe (7ffffffe)
IntToHexStr for "-2147483648": 80000000 (80000000)
IntToHexStr for "-2147483647": 80000001 (80000001)
IntToHexStr for "-3": fffffffd (fffffffd)
IntToHexStr for "3": 3 (00000003)
IntToHexStr for "-255": ffffff01 (ffffff01)
IntToHexStr for "255": ff (000000ff)
IntToHexStr for "-4": fffffffc (fffffffc)
IntToHexStr for "4": 4 (00000004)
IntToHexStr for "-5": fffffffb (fffffffb)
IntToHexStr for "5": 5 (00000005)
*/
#endif
