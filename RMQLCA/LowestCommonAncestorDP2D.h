#ifndef LOWEST_COMMON_ANCESTOR_DP2D_H
#define LOWEST_COMMON_ANCESTOR_DP2D_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.topcoder.com/tc?d1=tutorials&d2=lowestCommonAncestor&module=Static
<O(nlogn), O(logn)> time

not understood
*/
class LowestCommonAncestorDP2D
{
public:
	LowestCommonAncestorDP2D(){}
	~LowestCommonAncestorDP2D(){}
	struct TreeNode//not binary!
	{
		TreeNode(int x) : val(x), children() {}
		int val;
		std::vector<TreeNode *> children;
	};
	//O(nlogn) time
	void Construct(TreeNode * root, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<int> & dad, std::vector<int> & level, std::vector<std::vector<int> > & dp2d)
	{
		//1. construct dfsNodes, nodeIdxMap, dad, level
		int height = 0;
		this->dFS_Init(root, dfsNodes, nodeIdxMap, dad, level, root, 0, height);
		++height;

		//2. construct dp2d
		int N = dfsNodes.size();
		std::cout << "log(" << N << "),floor(log(" << N << ")): " << log2(N) << "," << floor(log2(N)) << std::endl;
		int logN = (int)floor(log2(N)) + 1;
		std::vector<std::vector<int> >(N, std::vector<int>(logN, -1)).swap(dp2d);//[N][logN] with value = -1
		for (int i = 0; i < N; ++i)
			dp2d[i][0] = dad[i];
		//Debug::Print2D<int>()(dp2d, false);
		for (int j = 1; 1 << j < N; ++j)//1,2,...,logN (check also RangeMinQuerySparseTable.h)
		{
			//std::cout << "j: " << j << std::endl;
			for (int i = 0; i < N; ++i)
				if (dp2d[i][j - 1] != -1)
					dp2d[i][j] = dp2d[dp2d[i][j - 1]][j - 1];
			//Debug::Print2D<int>()(dp2d, false);
		}
		
		this->print(dfsNodes, nodeIdxMap, dad, level, dp2d);
	}
private:
	//1. init dfsNodes, nodeIdxMap, dad, level, height
	void dFS_Init(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap,
		std::vector<int> & dad, std::vector<int> & level,
		TreeNode * dadNode, int levelCount, int & height)
	{
		dfsNodes.push_back(curNode);
		nodeIdxMap.insert(std::make_pair(curNode, dfsNodes.size() - 1));
		dad.push_back(nodeIdxMap[dadNode]);
		level.push_back(levelCount);
		if (levelCount > height)
			height = levelCount;
		int N = curNode->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * curChild = curNode->children[i];
			this->dFS_Init(curChild, dfsNodes, nodeIdxMap, dad, level, curNode, levelCount + 1, height);
		}
	}
public:
	//O(logn) time
	TreeNode * Query(const std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, const std::vector<int> & dad, const std::vector<int> & level, const std::vector<std::vector<int> > & dp2d, 
		TreeNode * p, TreeNode * q)
	{
		int x = nodeIdxMap[p];
		int y = nodeIdxMap[q];
		if (level[x] < level[y])//make sure x is lower than y
			std::swap(x, y);
		
		int logLevelX;
		for (logLevelX = 1; 1 << logLevelX <= level[x]; ++logLevelX);//1,2,3,...,ceil(log2(level[x]))
		--logLevelX;//equivalent to floor(log2(level[x]))
		//std::cout << "log(" << level[x] << "): " << logLevelX << "," << floor(log2(level[x])) << std::endl;

		for (int i = logLevelX; i >= 0; --i)
			if (level[x] - (1 << i) >= level[y])
				x = dp2d[x][i];

		if (x == y)
		{
			
		}
		else
		{
			for (int i = logLevelX; i >= 0; --i)
				if (dp2d[x][i] != -1 && dp2d[x][i] != dp2d[y][i])
				{
					x = dp2d[x][i];
					y = dp2d[y][i];
				}
			x = dad[x];
		}
		std::cout << "LowestCommonAncestorDP2D Query for \"" << p->val << "," << q->val << "\": " << dfsNodes[x]->val << std::endl;
		return dfsNodes[x];
	}

private:
	void print(std::vector<TreeNode *> & levelOrderNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<int> & dad, std::vector<int> & level, std::vector<std::vector<int> > & dp2d)
	{
		std::ostringstream oss;
		oss << "LowestCommonAncestorDP2D Construct:" << std::endl;
		oss << "Index:		";
		for (int i = 0; i < (int)levelOrderNodes.size(); ++i)
		{
			oss << i << ", ";
		}
		oss << std::endl;
		oss << "DFSNodes:	";
		for (int i = 0; i < (int)levelOrderNodes.size(); ++i)
		{
			if (levelOrderNodes[i] != NULL)
				oss << levelOrderNodes[i]->val;
			else
				oss << "N";
			if (i != (int)levelOrderNodes.size() - 1)
				oss << ", ";
		}
		oss << std::endl;
		oss << "DadIdx:		" << Debug::ToStr1D<int>()(dad) << std::endl;
		oss << "Level:		" << Debug::ToStr1D<int>()(level) << std::endl;
		oss << "NodeIdxMap:	";
		for (auto i : nodeIdxMap)
		{
			oss << "[" << i.first->val << "," << i.second << "],";
		}
		oss << std::endl;
		oss << "DP2D:" << std::endl;
		std::cout << oss.str();
		Debug::Print2D<int>()(dp2d, false);
	}

public:
	static void DeleteTree(TreeNode * root)
	{
		if (root == 0)
			return;

		int N = root->children.size();
		for (int i = 0; i < N; ++i)
			DeleteTree(root->children[i]);

		//post order
		delete root;
		root = 0;
	}
};
/*
  ___________1___________
 /           |           \
2   _________3_________   4
   /         |         \
  5        __6__      __7__
          /     \    /     \
	     8       9  10     11
	               /  \
			      12  13

log(13),floor(log(13)): 3.70044,3
LowestCommonAncestorDP2D Construct:
Index:		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
DFSNodes:	1, 2, 3, 5, 6, 8, 9, 7, 10, 12, 13, 11, 4
DadIdx:		0, 0, 0, 2, 2, 4, 4, 2, 7, 8, 8, 7, 0
Level:		0, 1, 1, 2, 2, 3, 3, 2, 3, 4, 4, 3, 1
NodeIdxMap:	[5,3],[1,0],[11,11],[2,1],[3,2],[6,4],[8,5],[10,8],[4,12],[13,10],[9,6],[12,9],[7,7],
DP2D:
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 0, 0
Row#2	= 0, 0, 0, 0
Row#3	= 2, 0, 0, 0
Row#4	= 2, 0, 0, 0
Row#5	= 4, 2, 0, 0
Row#6	= 4, 2, 0, 0
Row#7	= 2, 0, 0, 0
Row#8	= 7, 2, 0, 0
Row#9	= 8, 7, 0, 0
Row#10	= 8, 7, 0, 0
Row#11	= 7, 2, 0, 0
Row#12	= 0, 0, 0, 0

LowestCommonAncestorDP2D Query for "9,12": 3
LowestCommonAncestorDP2D Query for "13,11": 7
LowestCommonAncestorDP2D Query for "2,10": 1
LowestCommonAncestorDP2D Query for "13,12": 10
LowestCommonAncestorDP2D Query for "10,11": 7
*/
#endif