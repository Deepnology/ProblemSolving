/*MUST*/
#ifndef SHORTEST_STRAIGHT_LINE_PROGRAM_X_POW_N_H
#define SHORTEST_STRAIGHT_LINE_PROGRAM_X_POW_N_H
#include <list>
#include <queue>
#include <iostream>
#include <algorithm>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: The shortest straight-line program for X^n
A straight-line program for computing X^n is a finite sequence <X, X^i1, X^i2, ..., X^n> where each element after the first 
is either "the square of some previous element" or "the product of any two previous elements".
For example, the term X^15 can be computed by the following two straight-line programs.

P1 = <X, X^2, X^4, X^8, X^12, X^14, X^15>
where
X^4 = (X^2)^2
X^8 = (X^4)^2
X^12 = (X^8)*(X^4)
X^14 = (X^12)*(X^2)
X^15 = (X^14)*X

P2 = <X, X^2, X^3, X^5, X^10, X^15>
where
X^3 = (X^2)*X
X^5 = (X^3)*(X^2)
X^10 = (X^5)^2
X^15 = (X^10)*(X^5)

Given a positive integer n, how would compute a shortest straight-line program to evaluate X^n?

The program shown below is heuristic, and we cannot give a nontrivial bound on its time complexity.
*/
class ShortestStraightLineProgramXPowN
{
public:
	ShortestStraightLineProgramXPowN(){}
	~ShortestStraightLineProgramXPowN(){}

	std::list<int> BruteForce_BFS_Queue(int n)
	{
		if (n == 1)
			return{ 1 };

		std::list<int> res;//a sequence of powers toward n, where the last power is always either "a DOUBLE of any previous power" or "a SUM of any 2 previous powers"
		std::queue<std::list<int> > pathQue;//a queue of candidate sequences
		pathQue.push({ 1 });//the first sequence is always 1

		//BFS check all candidate sequences is a solution sequence toward n, stop when found the first one, which must be the shortest
		while (!pathQue.empty())
		{
			std::list<int> curPath = pathQue.front();
			pathQue.pop();

			//check if curPath with all possible cases of the next power is a solution sequence toward n
			//the next power must be greater than the last power in curPath
			//so we check the sum of each power and the last power in curPath, where the "sum of the last power and the last power" can be just used for the "double of the last power"
			for (const int & i : curPath)
			{
				int power = i + curPath.back();//means X^i * X^end, where X^end * X^end means (X^end)^2
				if (power > n)
					break;//curPath can never be a solution for later greater elements, just skip curPath

				//now we know "curPath, power" is a candidate solution sequence toward n
				std::list<int> newPath(curPath);
				newPath.push_back(power);
				if (power == n)//found first solution sequence, which must be the shortest one
				{
					res = newPath;
					break;
				}

				//candidate sequence is not a solution yet, enqueue it for later check
				pathQue.push(newPath);
			}

			if (!res.empty())
				break;
		}

		std::cout << "ShortestStraightLineProgramXPowN BruteForce_BFS_Queue for \"" << n << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
ShortestStraightLineProgramXPowN BruteForce_BFS_Queue for "15": 1, 2, 3, 5, 10, 15
*/
#endif