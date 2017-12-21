#ifndef REMOVE_REPLACE_ELEMENT_FROM_ARR_H
#define REMOVE_REPLACE_ELEMENT_FROM_ARR_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Replace and remove

O(n) time

See also RemoveSomeElementFromArray.h
*/
class RemoveReplaceElementFromArr
{
public:
	RemoveReplaceElementFromArr(){}
	~RemoveReplaceElementFromArr(){}

	void InPlace_Remove_b_Replace_a_dd(std::string & s)
	{
		std::string before = s;
		/*1. forward iteration: remove b and count num of a*/
		int N = s.size();
		int aCount = 0;
		int newEnd = 0;
		for (int oldCur = 0; oldCur < N; ++oldCur)
		{
			if (s[oldCur] == 'b')
				continue;
			
			if (s[oldCur] == 'a')
				++aCount;
			s[newEnd++] = s[oldCur];
		}

		/*2. allocate space according to the num of a*/
		s.resize(newEnd + aCount);
		N = s.size();

		/*3. backward iteration: replace a with dd starting from the end*/
		int newEnd2 = N - 1;
		for (int oldCur = newEnd - 1; oldCur >= 0; --oldCur)
		{
			if (s[oldCur] == 'a')
			{
				s[newEnd2--] = 'd';
				s[newEnd2--] = 'd';
			}
			else
				s[newEnd2--] = s[oldCur];
		}

		std::cout << "RemoveReplaceElementFromArr InPlace_Remove_b_Replace_a_dd for \"" << before << "\": " << s << std::endl;
	}
};
#endif