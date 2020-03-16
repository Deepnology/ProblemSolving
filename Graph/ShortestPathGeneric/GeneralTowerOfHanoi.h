#ifndef GENERAL_TOWER_OF_HANOI_H
#define GENERAL_TOWER_OF_HANOI_H
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include "TestCase.h"
#include "Debug.h"
/*
http://tristan-interview.blogspot.tw/2012/02/n-disks-and-k-pegs-extension-problem-of.html
http://www.careercup.com/question?id=13548681
http://stackoverflow.com/questions/3607161/towers-of-hanoi-with-k-pegs
http://coding-exercise.blogspot.tw/2013/04/facebook-hiring-sample-test.html
General Problem of Tower of Hanoi: N disks and K pegs
Given a start config and an end config, find the minimum move sequence to move disks from the start config to the end config.
For example, a start config and an end config, where N=5, K=4 are given as followed (disk index also represents its diameter):
{ 4 },
{ 1, 0 },
{ 3 },
{ 2 },

{ },
{ 4 },
{ 3, 0 },
{ 2, 1 },

The minimum move sequence: [1,2], [1,3], [0,1].

This is a graph problem.
DFS solution:
From the current config, try every possible move to get the next config, and recur down.
When coming back from recur, restore the move and try the next move.
Represent each config as a hash code, and save all visited configs as hash codes in a map.
Each time of recur when seeing a visited config that has less move count, just skip (return).
Each time of recur when seeing an end config that has less move count, record the path and return.

HashCodeTable: Map a particular config to unique hash code
There are K pegs, each peg can contain max of N disks
=> K pegs, each peg has N positions, each position has N+1 states (can be disk of index 0 to N-1, or empty)
=> Generate K*N*(N+1) unique constant random numbers for each state of each position of each peg
=> The hash code for a particular config will be XOR of K*N corresponding unique random numbers from the HashCodeTable
=> To update a hash code of a config to move a disk from a peg to another:
1. XOR current hash code with the random number at disk's FROM corresponding peg, position, diameter index (to remove disk)
2. XOR current hash code with the random number at disk's FROM corresponding peg, position, empty index (to add blank)
3. XOR current hash code with the random number at disk's TO corresponding peg, position, empty index (to remove blank)
4. XOR current hash code with the random number at disk's TO corresponding peg, position, diameter index (to add disk)

see also WordLadder.h, RemoveInvalidParentheses.h
*/
class GeneralTowerOfHanoi
{
public:
	GeneralTowerOfHanoi(){}
	~GeneralTowerOfHanoi(){}

	//enumerate all diff shortest paths instead of enumerating all diff result configurations with a shortest path
	void BFS(const std::vector<std::vector<int>> & startConfig, const std::vector<std::vector<int>> & endConfig, int N, int K)//better
	{
		std::vector<std::vector<std::vector<unsigned long long>>> hashCodeTable = this->createHashCodeTable(N, K);
		unsigned long long endConfigHashCode = this->getHashCodeOfConfig(endConfig, hashCodeTable);
		std::vector<std::vector<std::pair<int, int>>> res;//first: from peg idx, second: to peg idx
		std::unordered_set<unsigned long long> visitedConfig;

		std::queue<std::vector<std::pair<int, int>>> pathQue;//first: from peg idx, second: to peg idx
		std::queue<std::vector<std::vector<int>>> que;
		que.push(startConfig);
		pathQue.push(std::vector<std::pair<int, int>>(1, { -1, -1 }));
		int maxLen = INT_MAX;

		while (!que.empty())
		{
			int curLevelCount = que.size();
			bool reached = false;
			std::vector<unsigned long long> levelVisit;
			for (int k = 0; k < curLevelCount; ++k)
			{
				std::vector<std::vector<int>> curConfig = que.front();
				que.pop();
				std::vector<std::pair<int, int>> curPath = pathQue.front();
				pathQue.pop();

				int curLen = curPath.size();
				if (curLen > maxLen)//redundant
					continue;
				unsigned long long curConfigHashCode = this->getHashCodeOfConfig(curConfig, hashCodeTable);
				if (curConfigHashCode == endConfigHashCode)
				{
					res.push_back(curPath);
					if (maxLen == INT_MAX)
						maxLen = curLen;
					if (!reached)
						reached = true;
					continue;
				}
				else if (curLen == maxLen)
					continue;

				for (int i = 0; i < K; ++i)
				{
					if (!curConfig[i].empty())
					{
						int top = curConfig[i].back();
						curConfig[i].pop_back();
						for (int j = 0; j < K; ++j)
						{
							if (j == i) continue;
							if (curConfig[j].empty() || ((int)curConfig[j].size() < N && curConfig[j].back() > top))
							{
								curConfig[j].push_back(top);
								unsigned long long nxtConfigHashCode = this->getHashCodeOfConfig(curConfig, hashCodeTable);
								if (visitedConfig.find(nxtConfigHashCode) == visitedConfig.end())
								{
									//cannot mark this neighbor visited here to find ALL diff shortest paths: bc this neighbor of cur level node might be a neighbor of other latter cur level nodes !!!
									if (nxtConfigHashCode != endConfigHashCode)
										levelVisit.push_back(nxtConfigHashCode);
									curPath.push_back({ i, j });
									que.push(curConfig);
									pathQue.push(curPath);
									curPath.pop_back();
								}
								curConfig[j].pop_back();
							}
						}
						curConfig[i].push_back(top);
					}
				}

			}
			if (reached)
				break;

			//now mark all neighbors of all cur level nodes as visited after all neighbors of all cur level nodes have been visited
			//this is to ensure ALL diff shortest paths can be enumerated
			for (auto & i : levelVisit)
				visitedConfig.insert(i);
		}

		Debug::Print2D<int>()(startConfig, false);
		Debug::Print2D<int>()(endConfig, false);
		std::cout << "GeneralTowerOfHanoi BFS for above start and end configs: " << std::endl;
		Debug::Print2D<int>()(res, false);
	}

	void DFS(const std::vector<std::vector<int>> & startConfig, const std::vector<std::vector<int>> & endConfig, int N, int K)//need to prune
	{
		std::vector<std::vector<std::vector<unsigned long long>>> hashCodeTable = this->createHashCodeTable(N, K);
		unsigned long long endConfigHashCode = this->getHashCodeOfConfig(endConfig, hashCodeTable);
		std::vector<std::vector<int>> start(startConfig);
		std::vector<std::pair<int, int>> path;//first: from peg idx, second: to peg idx
		std::map<int, std::vector<std::vector<std::pair<int, int>>>> allValid;//first: depth, second.first: from peg idx, second.second: to peg idx
		std::unordered_map<unsigned long long, int> visitedConfig;//first: config hash code, second: depth
		int curMinMoveCount = INT_MAX;
		path.push_back({ -1,-1 });
		this->dfsRecur(start, endConfigHashCode, N, K, hashCodeTable, visitedConfig, curMinMoveCount, path, allValid);

		Debug::Print2D<int>()(startConfig, false);
		Debug::Print2D<int>()(endConfig, false);
		std::cout << "GeneralTowerOfHanoi DFS for above start and end configs: " << std::endl;
		//for (auto & p : allValid)
		//	Debug::Print2D<int>()(p.second, false);
		Debug::Print2D<int>()(allValid.begin()->second, false);
		//Debug::Print3D<unsigned long long>()(hashCodeTable, false);
	}
private:
	void dfsRecur(std::vector<std::vector<int>> & startConfig, const unsigned long long & endConfig, int N, int K
		, const std::vector<std::vector<std::vector<unsigned long long>>> & hashCodeTable
		, std::unordered_map<unsigned long long, int> & visitedConfig
		, int & curMinMoveCount
		, std::vector<std::pair<int, int>> & path, std::map<int, std::vector<std::vector<std::pair<int, int>>>> & allValid)
	{
		int curLen = path.size();
		if (curLen > curMinMoveCount)
			return;

		unsigned long long curConfig = this->getHashCodeOfConfig(startConfig, hashCodeTable);
		if (curConfig == endConfig)
		{
			curMinMoveCount = std::min(curMinMoveCount, curLen);
			allValid[curLen].push_back(path);
			return;
		}
		else if (curLen == curMinMoveCount)
			return;

		for (int i = 0; i < K; ++i)
		{
			if (!startConfig[i].empty())
			{
				int top = startConfig[i].back();
				startConfig[i].pop_back();
				for (int j = 0; j < K; ++j)
				{
					if (j == i)
						continue;
					if (startConfig[j].empty() ||
						((int)startConfig[j].size() < N && startConfig[j].back() > top))
					{
						startConfig[j].push_back(top);
						std::vector<std::vector<int>> nxtConfig(startConfig);
						unsigned long long nxtConfigHashCode = this->getHashCodeOfConfig(nxtConfig, hashCodeTable);
						if (nxtConfigHashCode == endConfig || visitedConfig.find(nxtConfigHashCode) == visitedConfig.end() || visitedConfig[nxtConfigHashCode] >= curLen + 1)
						{
							if (nxtConfigHashCode != endConfig)
							{
								visitedConfig[nxtConfigHashCode] = curLen + 1;
							}
							path.push_back({ i, j });//move disc from peg i to peg j
							this->dfsRecur(nxtConfig, endConfig, N, K, hashCodeTable, visitedConfig, curMinMoveCount, path, allValid);
							path.pop_back();
						}
						startConfig[j].pop_back();
					}
				}
				startConfig[i].push_back(top);
			}
		}
	}

	unsigned long long getHashCodeOfConfig(const std::vector<std::vector<int>> & vv, const std::vector<std::vector<std::vector<unsigned long long >>> & hashCodeTable)
	{
		int K = hashCodeTable.size();
		int N = hashCodeTable[0].size();
		unsigned long long res = 0;
		for (int i = 0; i < K; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (j > (int)vv[i].size() - 1)//vv[i][j] is empty
					res ^= hashCodeTable[i][j][N];
				else
					res ^= hashCodeTable[i][j][vv[i][j]];
			}
		}
		return res;
	}
	std::vector<std::vector<std::vector<unsigned long long>>> createHashCodeTable(int N, int K)//N discs, K pegs
	{
		std::vector<std::vector<std::vector<unsigned long long>>> res(K, std::vector<std::vector<unsigned long long>>(N, std::vector<unsigned long long>(N + 1, 0)));
		std::unordered_set<unsigned long long> set;
		int idx = 0;
		while (idx < K * N * (N + 1))
		{
			//get the next unique random number and put in res
			unsigned long long r;
			do
			{
				r = TestCase::RandNum<unsigned long long>(std::numeric_limits<unsigned long long>::min(), std::numeric_limits<unsigned long long>::max());
			} while (set.find(r) != set.end());
			set.insert(r);
			/*
			idx = (N+1)*N*a + (N+1)*b + c
			*/
			int a = idx / ((N + 1)*N);
			int b = (idx - a*(N + 1)*N) / (N + 1);
			int c = idx - a*(N + 1)*N - b*(N + 1);
			//std::cout << a << "," << b << "," << c << std::endl;
			res[a][b][c] = r;
			++idx;
		}
		return res;
	}
	
};
/*
[rY][cX]
Row#0	= 4, 3, 2, 1, 0
Row#1	=  ,  ,  ,  ,
Row#2	=  ,  ,  ,  ,

[rY][cX]
Row#0	=  ,  ,  ,  ,
Row#1	= 4, 3, 2, 1, 0
Row#2	=  ,  ,  ,  ,

GeneralTowerOfHanoi BFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [0,1], [0,2], [1,2], [0,1], [2,0], [2,1], [0,1], [0,2], [1,2], [1,0], [2,0], [1,2], [0,1], [0,2], [1,2], [0,1], [2,0], [2,1], [0,1], [2,0], [1,2], [1,0], [2,0], [2,1], [0,1], [0,2], [1,2], [0,1], [2,0], [2,1], [0,1]

[rY][cX]
Row#0	= 4, 3, 2, 1, 0
Row#1	=  ,  ,  ,  ,
Row#2	=  ,  ,  ,  ,

[rY][cX]
Row#0	=  ,  ,  ,  ,
Row#1	= 4, 3, 2, 1, 0
Row#2	=  ,  ,  ,  ,

GeneralTowerOfHanoi DFS for above start and end configs: [0,1], [0,2], [1,2], [0,1], [2,0], [2,1], [0,1], [0,2], [1,2], [1,0], [2,0], [1,2], [0,1], [0,2], [1,2], [0,1], [2,0], [2,1], [0,1], [2,0], [1,2], [1,0], [2,0], [2,1], [0,1], [0,2], [1,2], [0,1], [2,0], [2,1], [0,1]
[rY][cX]
Row#0	= 4,
Row#1	= 1, 0
Row#2	= 3,
Row#3	= 2,

[rY][cX]
Row#0	=  ,
Row#1	= 4,
Row#2	= 3, 0
Row#3	= 2, 1

GeneralTowerOfHanoi BFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [1,2], [1,3], [0,1]

[rY][cX]
Row#0	= 4,
Row#1	= 1, 0
Row#2	= 3,
Row#3	= 2,

[rY][cX]
Row#0	=  ,
Row#1	= 4,
Row#2	= 3, 0
Row#3	= 2, 1

GeneralTowerOfHanoi DFS for above start and end configs: [1,2], [1,3], [0,1]

[rY][cX]
Row#0	=  ,  ,
Row#1	= 3, 0,
Row#2	=  ,  ,
Row#3	= 4, 2, 1

[rY][cX]
Row#0	=  ,  ,  ,  ,
Row#1	= 4, 3, 2, 1, 0
Row#2	=  ,  ,  ,  ,
Row#3	=  ,  ,  ,  ,

GeneralTowerOfHanoi BFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [3,0], [1,0], [1,2], [3,2], [3,1], [2,3], [2,1], [0,2], [3,1], [0,1], [2,1]
Row#1	= [-1,-1], [3,0], [1,0], [1,2], [3,2], [3,1], [2,3], [2,1], [3,1], [0,2], [0,1], [2,1]
Row#2	= [-1,-1], [3,0], [1,0], [1,2], [3,2], [3,1], [2,3], [2,1], [3,1], [0,3], [0,1], [3,1]
Row#3	= [-1,-1], [3,2], [1,2], [1,0], [3,0], [3,1], [0,3], [0,1], [2,0], [3,1], [2,1], [0,1]
Row#4	= [-1,-1], [3,2], [1,2], [1,0], [3,0], [3,1], [0,3], [0,1], [3,1], [2,0], [2,1], [0,1]
Row#5	= [-1,-1], [3,2], [1,2], [1,0], [3,0], [3,1], [0,3], [0,1], [3,1], [2,3], [2,1], [3,1]

[rY][cX]
Row#0	= 3, 1
Row#1	= 0,
Row#2	=  ,
Row#3	= 2,

[rY][cX]
Row#0	= 1,
Row#1	= 2, 0
Row#2	= 3,
Row#3	=  ,

GeneralTowerOfHanoi BFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [0,3], [0,2], [1,2], [3,0], [3,1], [2,1]
Row#1	= [-1,-1], [0,3], [0,2], [3,0], [1,0], [3,1], [0,1]
Row#2	= [-1,-1], [0,3], [0,2], [3,0], [1,2], [3,1], [2,1]
Row#3	= [-1,-1], [1,0], [3,1], [0,1], [0,3], [0,2], [3,0]
Row#4	= [-1,-1], [1,2], [3,1], [0,3], [2,1], [0,2], [3,0]
Row#5	= [-1,-1], [1,2], [3,1], [2,1], [0,3], [0,2], [3,0]

[rY][cX]
Row#0	= 3, 1
Row#1	= 0,
Row#2	=  ,
Row#3	= 2,

[rY][cX]
Row#0	= 1,
Row#1	= 2, 0
Row#2	= 3,
Row#3	=  ,

GeneralTowerOfHanoi DFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [0,3], [0,2], [1,2], [3,0], [3,1], [2,1]
Row#1	= [-1,-1], [0,3], [0,2], [3,0], [1,0], [3,1], [0,1]
Row#2	= [-1,-1], [0,3], [0,2], [3,0], [1,2], [3,1], [2,1]
Row#3	= [-1,-1], [1,0], [3,1], [0,1], [0,3], [0,2], [3,0]
Row#4	= [-1,-1], [1,2], [3,1], [0,3], [2,1], [0,2], [3,0]
Row#5	= [-1,-1], [1,2], [3,1], [2,1], [0,3], [0,2], [3,0]

[rY][cX]
Row#0	=  ,
Row#1	= 2, 0
Row#2	= 1,
Row#3	= 3,

[rY][cX]
Row#0	= 3, 1
Row#1	= 0,
Row#2	=  ,
Row#3	= 2,

GeneralTowerOfHanoi BFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [1,2], [3,0], [1,3], [2,1], [2,0]
Row#1	= [-1,-1], [3,0], [1,0], [1,3], [0,1], [2,0]
Row#2	= [-1,-1], [3,0], [1,2], [1,3], [2,1], [2,0]
Row#3	= [-1,-1], [3,0], [2,0], [1,0], [1,3], [0,1]
Row#4	= [-1,-1], [3,0], [2,0], [1,2], [1,3], [2,1]

[rY][cX]
Row#0	=  ,
Row#1	= 2, 0
Row#2	= 1,
Row#3	= 3,

[rY][cX]
Row#0	= 3, 1
Row#1	= 0,
Row#2	=  ,
Row#3	= 2,

GeneralTowerOfHanoi DFS for above start and end configs:
[rY][cX]
Row#0	= [-1,-1], [1,2], [3,0], [1,3], [2,1], [2,0]
Row#1	= [-1,-1], [3,0], [1,0], [1,3], [0,1], [2,0]
Row#2	= [-1,-1], [3,0], [1,2], [1,3], [2,1], [2,0]
Row#3	= [-1,-1], [3,0], [2,0], [1,0], [1,3], [0,1]
Row#4	= [-1,-1], [3,0], [2,0], [1,2], [1,3], [2,1]
*/
#endif