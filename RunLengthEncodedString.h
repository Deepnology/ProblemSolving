#ifndef RUN_LENGTH_ENCODED_STRING_H
#define RUN_LENGTH_ENCODED_STRING_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
Elements of programming interview, Strings: Implement run-length encoding
Run-length encoding (RLE) compression offers a fast way to do efficient on-the-fly compression and decompression of strings.
The idea is simple--encode successive repeated characters by the repetition count and the character.
For example, the RLE of "aaaabcccaa" is "4a1b3c2a".
The decoding of "3e4f2e" returns "eeeffffee".

http://www.geeksforgeeks.org/run-length-encoding/
Cracking the coding interview: Array and String
Given a string, return the Run-Length-Encoded string of it.
"aabcccccaaa" should return a2b1c5a3

O(n) time
*/
class RunLengthEncodedString
{
public:
	RunLengthEncodedString(){}
	~RunLengthEncodedString(){}

	std::string Encode(const std::string & s)
	{
		int N = s.size();
		std::ostringstream oss;
		int count = 1;
		for (int i = 1; i < N; ++i)
		{
			if (s[i] == s[i - 1])
				++count;
			else
			{
				oss << count << s[i - 1];
				count = 1;
			}
		}
		oss << count << s.back();

		std::cout << "RunLengthEncodedString Encode for \"" << s << "\": " << oss.str() << std::endl;
		return oss.str();
	}

	std::string Encode2(const std::string & s)
	{
		int N = s.size();
		std::string res;
		char lastChar = s[0];
		int sameCount = 1;
		for (int i = 1; i < N; ++i)
		{
			if (s[i] == lastChar)
				++sameCount;
			else
			{
				res += lastChar;
				res += std::to_string(sameCount);
				lastChar = s[i];//reset
				sameCount = 1;//reset
			}
		}
		res += lastChar;
		res += std::to_string(sameCount);

		std::cout << "RunLengthEncodedString Encode2 for \"" << s << "\": " << res << std::endl;
		return res;
	}

	std::string Decode(const std::string & s)
	{
		int N = s.size();
		std::string res;
		int count = 0;
		for (int i = 0; i < N; ++i)
		{
			if (isdigit(s[i]))
				count = count * 10 + s[i] - '0';
			else
			{
				res.append(count, s[i]);
				count = 0;
			}
		}

		std::cout << "RunLengthEncodedString Decode for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
RunLengthEncodedString Encode for "aabcccccaadddddddddddddddddxxxxyyyyZz": 2a1b5c2a17d4x4y1Z1z
RunLengthEncodedString Decode for "2a1b5c2a17d4x4y1Z1z": aabcccccaadddddddddddddddddxxxxyyyyZz
*/
#endif