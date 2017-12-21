#ifndef DECODE_NESTED_STRING_H
#define DECODE_NESTED_STRING_H
#include "Debug.h"
/*
Leetcode: Decode String
Given an encoded string, return it's decoded string.
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k.
For example, there won't be input like 3a or 2[4].

Examples:
s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/
class DecodeNestedString
{
public:
	DecodeNestedString() {}
	std::string Recur(std::string s)//better
	{
		int i = 0;
		std::string res = recur(s, i);
		std::cout << "DecodeNestedString Recur for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	std::string recur(const std::string & s, int & i)
	{
		std::string res;
		std::string num;
		int N = s.size();
		while (i < N)
		{
			if (s[i] == '[')
			{
				std::string str = recur(s, ++i);
				int count = stoi(num);
				num.clear();
				for (int j = 0; j < count; ++j)
					res += str;
			}
			else if (s[i] == ']')
			{
				++i;
				return res;
			}
			else if (isdigit(s[i]))
			{
				num += s[i++];
			}
			else//tail char
			{
				res += s[i++];
			}
		}
		return res;
	}

public:
	std::string Stack(std::string s)
	{
		int N = s.size();
		if (N == 0) return "";
		std::string num;
		std::stack<std::pair<int, std::string>> stk;
		stk.push({ 1,"" });
		int i = 0;
		while (i < N)
		{
			if (s[i] == '[')
			{
				stk.push({ stoi(num),"" });
				num.clear();
				++i;
			}
			else if (s[i] == ']')
			{
				std::string str = stk.top().second;
				int count = stk.top().first;
				stk.pop();
				for (int j = 0; j < count; ++j)
					stk.top().second += str;
				++i;
			}
			else if (isdigit(s[i]))
			{
				num += s[i++];
			}
			else//char
			{
				stk.top().second += s[i++];
			}
		}

		std::cout << "DecodeNestedString Stack for \"" << s << "\": " << stk.top().second << std::endl;
		return stk.top().second;
	}
};
/*
DecodeNestedString Recur for "3[a]2[bc]": aaabcbc
DecodeNestedString Stack for "3[a]2[bc]": aaabcbc
DecodeNestedString Recur for "3[a2[c]]": accaccacc
DecodeNestedString Stack for "3[a2[c]]": accaccacc
DecodeNestedString Recur for "2[abc]3[cd]ef": abcabccdcdcdef
DecodeNestedString Stack for "2[abc]3[cd]ef": abcabccdcdcdef
*/
#endif
