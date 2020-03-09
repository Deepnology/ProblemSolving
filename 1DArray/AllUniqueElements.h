#ifndef ALL_UNIQUE_ELEMENTS_H
#define ALL_UNIQUE_ELEMENTS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Cracking the coding interview 1.1
Determine if a string has all unique characters
*/
class AllUniqueElements
{
public:
	AllUniqueElements(){}
	~AllUniqueElements(){}

	bool CharArray(const std::string & s)
	{
		bool res = true;
		std::vector<int> CharSet(256, 0);
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			if (CharSet[s[i]] == 1)
			{
				res = false;
				break;
			}
			CharSet[s[i]] = 1;
		}
		
		std::cout << "AllUniqueElements CharArray for \"" << s << "\": " << res << std::endl;
		return res;
	}
	bool CharArray2(const std::string & s)//s should be composed of 'a'-'z'
	{
		bool res = true;
		int BitVec26 = 0;//use the lower 26 bits to represent 'a'-'z'
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			int val = s[i] - 'a';
			int bitvec = 1 << val;//bitvec contains only one bit '1' and rest bits are '0's
			if ((BitVec26 & bitvec) > 0)
			{
				res = false;
				break;
			}
			BitVec26 |= bitvec;//add to BitVec26
			//std::cout << "=> " << KeyGenAux().UIntToBinStr((unsigned int)BitVec26) << std::endl;
		}

		std::cout << "AllUniqueElements CharArray2 for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
AllUniqueElements CharArray for "afcdefg": 0
AllUniqueElements CharArray2 for "abcdefg": 1
*/
#endif