#ifndef	THE_CELEBRITY_PROBLEM_H
#define THE_CELEBRITY_PROBLEM_H
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Find the Celebrity
Elements of programming interview, Array: Identify the celebrity
https://www.cs.princeton.edu/courses/archive/spring13/cos423/problem0-1.pdf
http://www.careercup.com/question?id=13167666
http://www.geeksforgeeks.org/the-celebrity-problem/
In a party of N people, only one person is known to everyone.
Such a person may be present in the party, if yes, (s)he doesn't know anyone in the party.
We can only ask questions like "does A know B?"
Find the celebrity in minimum number of questions.

Graph approach:
Construct a digraph, where each edge from vertex i to vertex j means i knows j.
After the digrah is built, find the sink vertex, which has 0 out-degree and N-1 in-degrees.
O(n^2) time to construct the digraph, O(n) time to find the sink vertex.

BruteForce: O(n^2) time
UsingStack: O(n) time, O(n) space
*/
class TheCelebrityProblem
{
public:
	TheCelebrityProblem(){}
	~TheCelebrityProblem(){}

	int Use2Ptrs(const std::vector<std::vector<int> > & adjMatrix)//best
	{
		int N = adjMatrix.size();
		int left = 0;
		int right = N - 1;
		while (left < right)
		{
			if (adjMatrix[left][right])/*if left knows right, then left can't be the celebrity, eliminate left*/
				++left;
			else/*if left doesn't know right, then right can't be the celebrity, eliminate right*/
				--right;
		}

		//verify in case there is no celebrity:
		//now left==right is a candidate, which must know nobody and anybody must know him/her
		for (int i = 0; i < N; ++i)
			if (left != i && (adjMatrix[left][i] || !adjMatrix[i][left]))
			{
				left = -1;
				break;
			}

		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TheCelebrityProblem Use2Ptrs for the above adjMatrix: " << left << std::endl;
		return left;
	}

	int Use2PtrsII(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		int i = 0;
		int j = 1;
		while (j < N)
		{
			if (adjMatrix[i][j])/*if i knows j, then i can't be the celebrity, eliminate i by: j might be celebrity, update i to j, advance j*/
				i = j++;
			else/*if i doesn't know j, then j can't be the celebrity, eliminate j*/
				++j;
		}

		//verify in case there is no celebrity
		//now i is a candidate, which must know nobody and anybody must know him/her
		for (int k = 0; k < N; ++i)
			if (i != k && (adjMatrix[i][k] || !adjMatrix[k][i]))
			{
				i = -1;
				break;
			}

		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TheCelebrityProblem Use2PtrsII for the above adjMatrix: " << i << std::endl;
		return i;
	}

	int UsingStack(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();

		/*1. use a stack to eliminate people*/
		std::stack<int> stk;
		for (int i = 0; i < N; ++i)
			stk.push(i);
		int A = stk.top();
		stk.pop();
		int B = stk.top();
		stk.pop();

		while (stk.size() != 1)
		{
			if (adjMatrix[A][B])/*if A knows B, then A can't be the celebrity, eliminate A*/
			{
				A = stk.top();
				stk.pop();
			}
			else/*if A doesn't know B, then B can't be the celebrity, eliminate B*/
			{
				B = stk.top();
				stk.pop();
			}
		}

		int C = stk.top();/*let C be the last one*/
		stk.pop();

		if (adjMatrix[C][B])/*if C knows B, eliminate C*/
			C = B;
		if (adjMatrix[C][A])/*if C knows A, eliminate A*/
			C = A;
		/*C is now the celebrity candidate*/

		/*2. verify: check if C doesn't know everyone and if everyone knows C*/
		for (int i = 0; i < N; ++i)
			if (C != i)
				stk.push(i);

		int res = C;
		while (!stk.empty())
		{
			int i = stk.top();
			stk.pop();
			if (adjMatrix[C][i])
			{
				res = -1;
				break;
			}
			if (!adjMatrix[i][C])
			{
				res = -1;
				break;
			}
		}

		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TheCelebrityProblem UsingStack for the above adjMatrix: " << res << std::endl;
		return res;
	}

	int BruteForce(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		int res = -1;

		/*1. check every pair of 2 people: a celebrity knows no one*/
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (adjMatrix[i][j])/*if i knows j, i can't be a celebrity, so eliminate i*/
					break;
				else
					res = i;
			}
		}

		/*2. verify: everyone must know the celebrity*/
		for (int i = 0; i < N; ++i)
		{
			if (i != res && !adjMatrix[i][res])/*if i doesn't know res, res isn't a valid celebrity*/
			{
				res = -1;
				break;
			}
		}

		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TheCelebrityProblem BruteForce for the above adjMatrix: " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 1
Row#1	= 1, 0, 0, 1, 1, 1
Row#2	= 0, 1, 1, 1, 1, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 1, 0, 1, 1, 0, 1
Row#5	= 0, 1, 0, 1, 1, 0

TheCelebrityProblem Use2Ptrs for the above adjMatrix: 3
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 1
Row#1	= 1, 0, 0, 1, 1, 1
Row#2	= 0, 1, 1, 1, 1, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 1, 0, 1, 1, 0, 1
Row#5	= 0, 1, 0, 1, 1, 0

TheCelebrityProblem Use2PtrsII for the above adjMatrix: 3
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 1
Row#1	= 1, 0, 0, 1, 1, 1
Row#2	= 0, 1, 1, 1, 1, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 1, 0, 1, 1, 0, 1
Row#5	= 0, 1, 0, 1, 1, 0

TheCelebrityProblem UsingStack for the above adjMatrix: 3
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 1
Row#1	= 1, 0, 0, 1, 1, 1
Row#2	= 0, 1, 1, 1, 1, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 1, 0, 1, 1, 0, 1
Row#5	= 0, 1, 0, 1, 1, 0

TheCelebrityProblem BruteForce for the above adjMatrix: 3
*/
/*
Leetcode: Find the Town Judge
In a town, there are N people labelled from 1 to N.  There is a rumor that one of these people is secretly the town judge.
If the town judge exists, then:
The town judge trusts nobody.
Everybody (except for the town judge) trusts the town judge.
There is exactly one person that satisfies properties 1 and 2.
You are given trust, an array of pairs trust[i] = [a, b] representing that the person labelled a trusts the person labelled b.
If the town judge exists and can be identified, return the label of the town judge.  Otherwise, return -1.
Example 1:
Input: N = 2, trust = [[1,2]]
Output: 2
Example 2:
Input: N = 3, trust = [[1,3],[2,3]]
Output: 3
Example 3:
Input: N = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1
Example 4:
Input: N = 3, trust = [[1,2],[2,3]]
Output: -1
Example 5:
Input: N = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
Output: 3
 */
class FindTheJudgeInTown
{
public:
	FindTheJudgeInTown(){}

	int Solve1(int N, std::vector<std::vector<int>> && trust)
	{
		std::vector<int> trustCount(N, 0);
		std::vector<int> beTrustedCount(N, 0);
		for (auto & p : trust)
		{
			++trustCount[p[0]-1];
			++beTrustedCount[p[1]-1];
		}
		for (int i = 0; i < N; ++i)
			if (trustCount[i] == 0 && beTrustedCount[i] == N-1)
				return i + 1;
		return -1;
	}
	int Solve2(int N, std::vector<std::vector<int>> && trust)
	{
		std::vector<int> degree(N, 0);//sum of in-degree and out-degree
		for (auto & p : trust)
		{
			--degree[p[0]-1];//out-degree
			++degree[p[1]-1];//in-degree
		}
		for (int i = 0; i < N; ++i)
			if (degree[i] == N-1)
				return i+1;
		return -1;
	}
};
#endif