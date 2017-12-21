#ifndef MAX_TOP_3_AVG_SCORE_STUDENT_H
#define MAX_TOP_3_AVG_SCORE_STUDENT_H
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "Debug.h"
/*
Elements of programming interview, BST: Compute the average of the top 3 scores
Write a function which takes as input the name of the file containing n test scores and outputs the student who has the max average score across his top three tests.
If the student has fewer than three test scores, discard that student.
Return "no such student" if no student has three or more test scores.

O(n) time
*/
class MaxTop3AvgScoreStudent
{
public:
	MaxTop3AvgScoreStudent(){}
	~MaxTop3AvgScoreStudent(){}

	std::string Find(std::istringstream & iss)
	{
		std::string before = iss.str();
		std::unordered_map<std::string, std::multiset<int> > nameToScores;
		std::string nameBuf;
		int scoreBuf;
		while (iss >> nameBuf >> scoreBuf)
		{
			nameToScores[nameBuf].emplace(scoreBuf);
		}

		std::string res("no such student");
		int maxTop3ScoreSum = INT_MIN;
		for (const auto & p : nameToScores)
		{
			if (p.second.size() >= 3)
			{
				int curTop3ScoreSum = 0;
				std::multiset<int>::const_reverse_iterator itr = p.second.crbegin();
				int count = 0;
				for (; count < 3; ++itr, ++count)
					curTop3ScoreSum += *itr;

				if (curTop3ScoreSum > maxTop3ScoreSum)
				{
					maxTop3ScoreSum = curTop3ScoreSum;
					res = p.first;
				}
			}
		}

		Debug::Print2D<std::string, int>()(nameToScores);
		std::cout << "MaxTop3AvgScoreStudent for \"" << before << "\": " << res << std::endl;
		return res;
	}


};
#endif