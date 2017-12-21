#ifndef REMOVE_CONSECU_SAME_CHARS_H
#define REMOVE_CONSECU_SAME_CHARS_H
#include "Debug.h"
/*
Bloomberg
Given a string, remove consecutive same chars with length >= 3.
aacbbbccd -> aacccd -> aad
aabbba -> aaa -> 
aabbccccdd -> aabbdd
aabbcccbadd -> aabbbadd -> aaadd -> dd
*/
class RemoveConsecuSameChars
{
public:
	std::string Linear(std::string s)
	{
		std::string before = s;
		int i = 0;
		while (!s.empty() && i < (int)s.size())
		{
			int end = i + 1;//find end of same char of s[i]
			while (end < (int)s.size() && s[end] == s[i])
				++end;
			if (end - i >= 3)
			{
				s = s.substr(0, i) + s.substr(end);
				//now i points to the first char of the right substr
				//move i to leftmost same char after merge: at most 2 steps
				while (i - 1 >= 0 && s[i - 1] == s[i])
					--i;
			}
			else
				i = end;//i+=1 or i+=2
		}

		std::cout << "RemoveConsecuSameChars Linear for \"" << before << "\": " << s << std::endl;
		return s;
	}
};
/*
RemoveConsecuSameChars Linear for "aacbbbccd": aad
RemoveConsecuSameChars Linear for "aabbba":
RemoveConsecuSameChars Linear for "aabbccccdd": aabbdd
RemoveConsecuSameChars Linear for "aabbcccbadd": dd
RemoveConsecuSameChars Linear for "abbbdbbccddaccddddccaaddcb": ad
*/
#endif
