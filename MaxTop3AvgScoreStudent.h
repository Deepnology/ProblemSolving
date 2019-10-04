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

	std::string Find(std::istringstream && iss)
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
/*
Leetcode: High Five
Given a list of scores of different students, return the average score of each student's top five scores in the order of each student's id.
Each entry items[i] has items[i][0] the student's id, and items[i][1] the student's score.
The average score is calculated using integer division.
Example 1:
Input: [[1,91],[1,92],[2,93],[2,97],[1,60],[2,77],[1,65],[1,87],[1,100],[2,100],[2,76]]
Output: [[1,87],[2,88]]
Explanation:
The average of the student with id = 1 is 87.
The average of the student with id = 2 is 88.6. But with integer division their average converts to 88.
Note:
1 <= items.length <= 1000
items[i].length == 2
The IDs of the students is between 1 to 1000
The score of the students is between 1 to 100
For each student, there are at least 5 scores
 */
class TopFiveScoresAvgForEachStudent
{
public:
	std::vector<std::vector<int>> Find(std::vector<std::vector<int>> & items)
	{
		std::map<int,std::multiset<int>> idToScores;
		for (auto & p : items)
		{
			idToScores[p[0]].insert(p[1]);
			if (idToScores[p[0]].size() > 5)
				idToScores[p[0]].erase(idToScores[p[0]].begin());
		}
		std::vector<std::vector<int>> res;
		for (auto & p : idToScores)
		{
			res.push_back({p.first, std::accumulate(p.second.begin(), p.second.end(), 0)/5});
		}
		return res;
	}
};
#endif