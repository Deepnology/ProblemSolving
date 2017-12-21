#ifndef KEY_PRESS_SEQ_IN_MATRIX_H
#define KEY_PRESS_SEQ_IN_MATRIX_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=15542726
Given a key board with keys layout:
a b c d e
f g h i j
k l m n o
p q r s t
u v w x y
z

Initial cursor is at [0][0].
You can move the cursor up(u), down(d), left(l), right(r), and enter(!) to input a sequence of chars.
Write a function to generate a sequence of movements for a given string.

*/
class KeyPressSeqInMatrix
{
public:
	KeyPressSeqInMatrix(){}
	~KeyPressSeqInMatrix(){}

	std::string Solve(const std::string & s)
	{
		int N = s.size();
		int curRowY = 0;
		int curColX = 0;
		std::string res;
		for (int i = 0; i < N; ++i)
		{
			int rowY = this->To2DRowY(s[i], 5);
			int colX = this->To2DColX(s[i], 5);
			char vertical = rowY > curRowY ? 'd' : 'u';
			char horizontal = colX > curColX ? 'r' : 'l';
			if (i != 0 && s[i - 1] == 'z')//prev char is z, move vertically first
			{
				for (int j = 0; j < std::abs(rowY - curRowY); ++j)
					res += vertical;
				for (int j = 0; j < std::abs(colX - curColX); ++j)
					res += horizontal;
			}
			else//current target char is z, move horizontally first. for other chars, it doesn't matter to move which first.
			{
				for (int j = 0; j < std::abs(colX - curColX); ++j)
					res += horizontal;
				for (int j = 0; j < std::abs(rowY - curRowY); ++j)
					res += vertical;
			}
			res += '!';
			curRowY = rowY;
			curColX = colX;
		}
		std::cout << "KeyPressSeqInMatrix for \"" << s << "\": " << res << std::endl;
		return res;
	}

	int To2DRowY(char c, int numColX)
	{
		return (c - 'a') / numColX;
	}
	int To2DColX(char c, int numColX)
	{
		return (c - 'a') % numColX;
	}
};
/*
KeyPressSeqInMatrix for "size": rrrddd!uu!llldddd!uuuuurrrr!
KeyPressSeqInMatrix for "zdzoz": ddddd!uuuuurrr!lllddddd!uuurrrr!llllddd!
*/
#endif