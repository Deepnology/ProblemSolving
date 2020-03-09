#ifndef MIN_MAX_RIGHT_LEFT_HAND_WORD_H
#define MIN_MAX_RIGHT_LEFT_HAND_WORD_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=25127665
Given a dictionary of words.
Find the longest and shortest word that can be typed by a single hand on a qwerty-style keyboard.

O(n * m) time, where n is the number of words in dict, and m is the average length of words
*/
class MinMaxRightLeftHandWord
{
public:
	MinMaxRightLeftHandWord(){}
	~MinMaxRightLeftHandWord(){}

	void Match(const std::vector<std::string> & dict)
	{
		int N = dict.size();
		/*
		leftHand: qwertasdfgzxcvb
		rightHand: yuiophjklnm
		*/
		/*                               a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z*/
		static const bool leftHand[] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
		
		std::string minLeftHand("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		std::string maxLeftHand;
		std::string minRightHand("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		std::string maxRightHand;

		for (const std::string & s : dict)
		{
			int n = s.size();
			bool isLeftHand = true;
			for (int i = 0; i < n; ++i)
			{
				if (leftHand[s[i] - 'a'] == 0)
				{
					isLeftHand = false;
					break;
				}
			}
			if (isLeftHand)
			{
				if (s.size() > maxLeftHand.size())
					maxLeftHand = s;
				if (s.size() < minLeftHand.size())
					minLeftHand = s;
			}

			bool isRightHand = true;
			for (int i = 0; i < n; ++i)
			{
				if (leftHand[s[i] - 'a'] == 1)
				{
					isRightHand = false;
					break;
				}
			}
			if (isRightHand)
			{
				if (s.size() > maxRightHand.size())
					maxRightHand = s;
				if (s.size() < minRightHand.size())
					minRightHand = s;
			}
		}

		std::cout << "MinMaxRightLeftHandWord for \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << minLeftHand << ", " << maxLeftHand << ", " << minRightHand << ", " << maxRightHand << std::endl;
	}
};

/*
Leetcode: Keyboard Row
Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.
Example 1:
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
*/
class KeyboardRow
{
public:
	KeyboardRow() {}
	std::vector<std::string> findWords(std::vector<std::string> & words)
	{
		std::vector<int> charRowMap({ 1,2,2,1,0,1,1,1,0,1,1,1,2,2,0,0,0,0,1,0,0,2,0,2,0,2 });//0: top row, 1: mid row, 2: bottom row
		std::vector<std::string> res;
		for (const auto & s : words)
		{
			int row = charRowMap[std::tolower(s[0]) - 'a'];
			int i = 1;
			for (; i < (int)s.size(); ++i)
			{
				if (charRowMap[std::tolower(s[i]) - 'a'] != row)
					break;
			}
			if (i == s.size()) res.push_back(s);
		}
		return res;
	}
};
#endif