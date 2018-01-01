#ifndef SENTENCE_SCREEN_FITTING_H
#define SENTENCE_SCREEN_FITTING_H
#include "Debug.h"
/*
Leetcode: Sentence Screen Fitting
Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.
Note:
A word cannot be split into two lines.
The order of words in the sentence must remain unchanged.
Two consecutive words in a line must be separated by a single space.
Total words in the sentence won't exceed 100.
Length of each word is greater than 0 and won't exceed 10.
1 <= rows, cols <= 20,000.
Input:
rows = 2, cols = 8, sentence = ["hello", "world"]
Output:
1
Explanation:
hello---
world---
The character '-' signifies an empty space on the screen.
Example 2:
Input:
rows = 3, cols = 6, sentence = ["a", "bcd", "e"]
Output:
2
Explanation:
a-bcd-
e-a---
bcd-e-
The character '-' signifies an empty space on the screen.
Example 3:
Input:
rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]
Output:
1
Explanation:
I-had
apple
pie-I
had--
The character '-' signifies an empty space on the screen.

see also CountTheRepetitions.h
*/
class SentenceScreenFitting
{
public:
	SentenceScreenFitting() {}

	int DP(const std::vector<std::string> & sentence, int rows, int cols)
	{
		int totalCount = 0;
		int idx = 0;
		std::unordered_map<int,std::pair<int,int>> dp;//<idx in sentence at begin of each col, <times, end idx>>
		for (int i = 0; i < rows; ++i)
		{
			if (dp.count(idx) == 0)
			{
				int beginIdx = idx;
				int colCount = 0;
				int j = 0;//j is total len of words in row i so far
				while (j + (int)sentence[idx].size() <= cols)
				{
					j += sentence[idx].size() + 1;
					++idx;
					if (idx == sentence.size())
					{
						idx = 0;
						++colCount;
					}
				}
				dp[beginIdx] = {colCount,idx};
				totalCount += colCount;
			}
			else
			{
				totalCount += dp[idx].first;
				idx = dp[idx].second;
			}
		}

		std::cout << "SentenceScreenFitting DP for \"" << Debug::ToStr1D<std::string>()(sentence) << "\", (row,col)=(" << rows << "," << cols << "): " << totalCount << std::endl;
		return totalCount;
		
	}

	//this is very fast
	int FillFromBack(const std::vector<std::string> & sentence, int rows, int cols)
	{
		std::string s;
		for (const auto & str : sentence)
			s += " " + str;
		int N = s.size();
		int startIdx = 1;//skip first space
		for (int i = 0; i < rows; ++i)
		{
			startIdx += cols;
			while (s[startIdx % N] != ' ')
				--startIdx;
			//now startIdx == ' '
			++startIdx;//now startIdx points to begin next word
		}
		--startIdx;//subtract first space

		std::cout << "SentenceScreenFitting FillFromBack for \"" << Debug::ToStr1D<std::string>()(sentence) << "\", (row,col)=(" << rows << "," << cols << "): " << (startIdx / N) << std::endl;
		return startIdx / N;
	}
};
/*
SentenceScreenFitting DP for "a, bcd, e", (row,col)=(3,6): 2
SentenceScreenFitting FillFromBack for "a, bcd, e", (row,col)=(3,6): 2
SentenceScreenFitting DP for "I, had, apple, pie", (row,col)=(4,5): 1
SentenceScreenFitting FillFromBack for "I, had, apple, pie", (row,col)=(4,5): 1
*/
#endif
