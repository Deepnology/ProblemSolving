#ifndef ENCODE_DECODE_STRINGS_H
#define ENCODE_DECODE_STRINGS_H
#include <string>
#include <iostream>
#include <vector>
#include "Debug.h"
/*
Leetcode: Encode and Decode Strings
Design an algorithm to encode a list of strings to a string.
The encoded string is then sent over the network and is decoded back to the original list of strings.
Machine 1 (sender) has the function:
string encode(vector<string> strs) {
// ... your code
return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
//... your code
return strs;
}
So Machine 1 does:
string encoded_string = encode(strs);
and Machine 2 does:
vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.
Implement the encode and decode methods.
Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.

Encode: len1#str1len2#str2...lenN#strN
*/
class EncodeDecodeStrings
{
public:
	EncodeDecodeStrings() {}
	~EncodeDecodeStrings() {}

	std::string Encode(const std::vector<std::string> & strs)
	{
		std::string res;
		for (const auto & s : strs)
		{
			res += (std::to_string(s.length()) + "#" + s);
		}

		std::cout << "EncodeDecodeStrings Encode for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << res << std::endl;
		return res;
	}

	std::vector<std::string> Decode(const std::string & s)
	{
		int N = s.size();
		std::vector<std::string> res;
		int len = 0;
		int i = 0;
		while (i < N)
		{
			while (s[i] >= '0' && s[i] <= '9')
			{
				len = len * 10 + (s[i] - '0');
				++i;
			}
			++i;//skip '#'
			res.push_back(s.substr(i, len));
			i += len;
			len = 0;
		}

		std::cout << "EncodeDecodeStrings Decode for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
EncodeDecodeStrings Encode for "42#asdf, 7659564235232, yt641, , , @#(*&1213, abc, 3242342523452339#sdgf, 4, 1a": 7#42#asdf13#76595642352325#yt6410#0#9#@#(*&12133#abc21#3242342523452339#sdgf1#42#1a
EncodeDecodeStrings Decode for "7#42#asdf13#76595642352325#yt6410#0#9#@#(*&12133#abc21#3242342523452339#sdgf1#42#1a": 42#asdf, 7659564235232, yt641, , , @#(*&1213, abc, 3242342523452339#sdgf, 4, 1a
*/
#endif
