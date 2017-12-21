#ifndef STROBOGRAMMATIC_NUMBER_H
#define STROBOGRAMMATIC_NUMBER_H
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Strobogrammatic Number
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Write a function to determine if a number is strobogrammatic. The number is represented as a string.
For example, the numbers "69", "88", and "818" are all strobogrammatic.

Leetcode: Strobogrammatic Number II
Find all strobogrammatic numbers that are of length = n.
For example,
Given n = 2, return ["11","69","88","96"].

Leetcode: Strobogrammatic Number III
Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.
For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.
Note:
Because the range might be a large number, the low and high numbers are represented as string.

*/
class StrobogrammaticNumber
{
public:
	StrobogrammaticNumber() {}
	~StrobogrammaticNumber() {}

	//I.
	bool Valid(const std::string & num)
	{
		//0->0, 1->1, 6->9, 8->8, 9->6
		static std::unordered_map<char, char> upsideDown({ {'0','0'}, {'1','1'}, {'6','9'}, {'8','8'}, {'9', '6'} });
		
		int N = num.size();
		int left = 0;
		int right = N - 1;
		bool res = true;
		while (left <= right)
		{
			if (upsideDown.find(num[left]) == upsideDown.end() ||
				upsideDown.find(num[right]) == upsideDown.end() ||
				upsideDown[num[left]] != num[right])
			{
				res = false;
				break;
			}
			++left, --right;
		}

		std::cout << "StrobogrammaticNumber Valid for \"" << num << "\": " << res << std::endl;
		return res;
	}

	//II.
	std::vector<std::string> GenerateRecur(int N)//N is the length
	{
		std::vector<std::string> res = this->recur(N, N);
		std::cout << "StrobogrammaticNumber GenerateRecur for \"" << N << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
	std::vector<std::string> recur(int curLen, int N)
	{
		//2 base cases: 0 for even N, 1 for odd N
		if (curLen == 0)
			return std::vector<std::string>({ "" });
		if (curLen == 1)
			return std::vector<std::string>({ "0", "1", "8" });

		//postorder adding 2 more nums at front and back to strs of curLen-2
		std::vector<std::string> strs = this->recur(curLen - 2, N);
		std::vector<std::string> res;
		for (const std::string & s : strs)
		{
			if (curLen != N)
				res.push_back("0" + s + "0");
			res.push_back("1" + s + "1");
			res.push_back("6" + s + "9");
			res.push_back("8" + s + "8");
			res.push_back("9" + s + "6");
		}
		return res;
	}

	//III.
	int CountInRange(const std::string & lower, const std::string & upper)
	{
		int lowLen = lower.size();
		int highLen = upper.size();
		std::vector<std::string> res;

		//1. find all with length from lower.size() to upper.size() using II.
		for (int i = lowLen; i <= highLen; ++i)
		{
			std::vector<std::string> strs = this->recur(i, i);
			res.insert(res.end(), strs.begin(), strs.end());
		}

		//2. exclude nums whose value are less than lower or greater than upper
		int count = res.size();
		for (const std::string & s : res)
		{
			if (s.size() == lowLen && s.compare(lower) < 0)
			{
				--count;
			}
			else if (s.size() == highLen && s.compare(upper) > 0)
			{
				--count;
			}
		}

		std::cout << Debug::ToStr1D<std::string>()(res) << std::endl;
		std::cout << "StrobogrammaticNumber CountInRange for \"[" << lower << ", " << upper << "]\": " << count << std::endl;
		return count;
	}
};
/*
StrobogrammaticNumber Valid for "1": 1
StrobogrammaticNumber Valid for "7": 0
StrobogrammaticNumber Valid for "1680891": 1
StrobogrammaticNumber GenerateRecur for "1": 0, 1, 8
StrobogrammaticNumber GenerateRecur for "2": 11, 69, 88, 96
StrobogrammaticNumber GenerateRecur for "3": 101, 609, 808, 906, 111, 619, 818, 916, 181, 689, 888, 986
StrobogrammaticNumber GenerateRecur for "4": 1001, 6009, 8008, 9006, 1111, 6119, 8118, 9116, 1691, 6699, 8698, 9696, 1881, 6889, 8888, 9886, 1961, 6969, 8968, 9966
11, 69, 88, 96, 101, 609, 808, 906, 111, 619, 818, 916, 181, 689, 888, 986
StrobogrammaticNumber CountInRange for "[50, 100]": 3
101, 609, 808, 906, 111, 619, 818, 916, 181, 689, 888, 986
StrobogrammaticNumber CountInRange for "[181, 808]": 5
*/
#endif
