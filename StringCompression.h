#ifndef	STRING_COMPRESSION_H
#define STRING_COMPRESSION_H
#include "Debug.h"
/*
Leetcode: String Compression
Given an array of characters, compress it in-place.
The length after compression must always be smaller than or equal to the original array.
Every element of the array should be a character (not int) of length 1.
After you are done modifying the input array in-place, return the new length of the array.
Follow up:
Could you solve it using only O(1) extra space?
Example 1:
Input:
["a","a","b","b","c","c","c"]
Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]
Output:
Return 1, and the first 1 characters of the input array should be: ["a"]
Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
*/
class StringCompression
{
public:
	StringCompression() {}

	int InPlace_Better(std::vector<char>& chars)
	{
		int N = chars.size();
		if (N == 0) return 0;
		int i = 0;
		int j = 0;
		while (i < N)
		{
			int end = i + 1;
			while (end < N && chars[end] == chars[end - 1])
				++end;
			int count = end - i;
			chars[j++] = chars[i];
			if (count > 1)
			{
				std::vector<char> num;
				while (count)
				{
					num.push_back(count % 10 + '0');
					count /= 10;
				}
				for (auto itr = num.rbegin(); itr != num.rend(); ++itr)
					chars[j++] = *itr;
			}
			i = end;
		}
		return j;
	}

	int InPlace(std::vector<char> & chars)
	{
		int N = chars.size();
		if (N == 0) return 0;
		char cur;
		int count = 0;
		int j = 0;
		for (int i = 0; i < N; ++i)
		{
			if (count == 0)
			{
				cur = chars[i];
				count = 1;
			}
			else if (chars[i] == cur)
			{
				++count;
			}
			else//see a diff char at i: conclude
			{
				chars[j++] = cur;
				if (count > 1)
				{
					std::vector<char> num;
					while (count)
					{
						num.push_back(count % 10 + '0');
						count /= 10;
					}
					for (auto itr = num.rbegin(); itr != num.rend(); ++itr)
						chars[j++] = *itr;
				}
				count = 1;
				cur = chars[i];
			}
		}

		//conclude again
		chars[j++] = cur;
		if (count > 1)
		{
			std::vector<char> num;
			while (count)
			{
				num.push_back(count % 10 + '0');
				count /= 10;
			}
			for (auto itr = num.rbegin(); itr != num.rend(); ++itr)
				chars[j++] = *itr;
		}

		return j;
	}
};
#endif
