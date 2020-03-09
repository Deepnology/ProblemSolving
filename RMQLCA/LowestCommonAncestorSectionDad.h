#ifndef LOWEST_COMMON_ANCESTOR_SECTION_DAD_H
#define LOWEST_COMMON_ANCESTOR_SECTION_DAD_H
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
<O(n), O(sqrt(n))> time

                                       level
  ________1_________.....................0\
 /        |         \                      | SectionDad: 1
2    _____3______    4...................1/
    /     |      \
   5      6       7......................2\
         / \     / \                       | SectionDad: 3
        8   9  10   11...................3/
               / \
             12   13.....................4\
			                               | SectionDad: 10
			                              /
Height: 5
Sqrt of Height: 2 (level count per section)
               0  1  2  3  4  5  6  7  8  9 10 11 12
DFSNodes:      1  2  3  5  6  8  9  7 10 12 13 11  4
DadIdx:        0  0  0  2  2  4  4  2  7  8  8  7  0
Level:         0  1  1  2  2  3  3  2  3  4  4  3  1
SectionDadIdx: 0  0  0  2  2  2  2  2  2  8  8  2  0
NodeIdxMap:
1: 0
2: 1
3: 2
4: 12
5: 3
6: 9
7: 7
8: 5
9: 6
10: 8
11: 11
12: 9
13: 10

To query the LCA of two nodes based on Level, SectionDad, Dad:
1. move the node that is in a lower section to the upper section where the higher node belongs to
2. move the lower node to its dad until the two nodes meets
*/
class LowestCommonAncestorSectionDad
{
public:
	LowestCommonAncestorSectionDad(){}
	~LowestCommonAncestorSectionDad(){}
	struct TreeNode//not binary!
	{
		TreeNode(int x) : val(x), children() {}
		int val;
		std::vector<TreeNode *> children;
	};
	/*
	dfsNodes: TreeNode ptrs in DFS order
	nodeIdxMap: TreeNode ptr to DFSindex
	dad: dad node DFSindex in DFS order
	level: distance from root in DFS order
	sectionDad: sectionDad node DFSindex in DFS order
	O(n) time
	*/
	void Construct(TreeNode * root, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap,
		std::vector<int> & dad, std::vector<int> & level, std::vector<int> & sectionDad)
	{
		int height = 0;
		this->dFS_Init(root, dfsNodes, nodeIdxMap, dad, level, root, 0, height);
		++height;
		this->dFS_SectionDad(root, dfsNodes, nodeIdxMap, sectionDad, root, 0, (int)sqrt(height));
		this->print(dfsNodes, nodeIdxMap, dad, level, sectionDad, height);
	}
private:
	//1. init dfsNodes, nodeIdxMap, dad, level, height
	void dFS_Init(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap,
		std::vector<int> & dad, std::vector<int> & level,
		TreeNode * dadNode, int levelCount, int & height)
	{
		dfsNodes.push_back(curNode);
		nodeIdxMap.insert({ curNode, dfsNodes.size() - 1 });
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
	//2. construct sectionDad
	void dFS_SectionDad(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap,
		std::vector<int> & sectionDad,
		TreeNode * dadNode, int levelCount, int sqrtHeight)
	{
		if (levelCount < sqrtHeight)
		{
			sectionDad.push_back(0);
		}
		else
		{
			if (!(levelCount % sqrtHeight))//1st level of current section
				sectionDad.push_back(nodeIdxMap[dadNode]);
			else//non-1st level of current section
				sectionDad.push_back(sectionDad[nodeIdxMap[dadNode]]);
		}
		int N = curNode->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * curChild = curNode->children[i];
			this->dFS_SectionDad(curChild, dfsNodes, nodeIdxMap, sectionDad, curNode, levelCount + 1, sqrtHeight);
		}
	}
public:
	//O(sqrt(n)) time
	TreeNode * Query(std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap,
		std::vector<int> & dad, std::vector<int> & level, std::vector<int> & sectionDad, 
		TreeNode * p, TreeNode * q)
	{
		int x = nodeIdxMap[p];
		int y = nodeIdxMap[q];
		//1. move the node that is in a lower section to the upper section where the higher node belongs to
		while (sectionDad[x] != sectionDad[y])
		{
			if (level[x] > level[y])
				x = sectionDad[x];
			else
				y = sectionDad[y];
		}
		//now both the two nodes are in the same section
		//2. move the lower node to its dad until the two nodes meets
		while (x != y)
		{
			if (level[x] > level[y])
				x = dad[x];
			else
				y = dad[y];
		}
		std::cout << "LowestCommonAncestorSectionDad Query for \"" << p->val << "," << q->val << "\": " << dfsNodes[x]->val << std::endl;
		return dfsNodes[x];
	}

private:
	void print(std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<int> & dad, std::vector<int> & level, std::vector<int> & sectionDad, int height)
	{
		std::ostringstream oss;
		oss << "LowestCommonAncestorSectionDad Construct:" << std::endl;
		oss << "Height,Sqrt(Height): " << height << "," << (int)sqrt(height) << std::endl;
		oss << "DFSNodes: ";
		for (int i = 0; i < (int)dfsNodes.size(); ++i)
		{
			if (dfsNodes[i] != NULL)
				oss << dfsNodes[i]->val;
			else
				oss << "N";
			if (i != (int)dfsNodes.size() - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "NodeIdxMap: ";
		for (auto i : nodeIdxMap)
		{
			oss << "[" << i.first->val << "," << i.second << "],";
		}
		oss << std::endl;
		oss << "DadIdx: " << Debug::ToStr1D<int>()(dad) << std::endl;
		oss << "Level: " << Debug::ToStr1D<int>()(level) << std::endl;
		oss << "SectionDadIdx: " << Debug::ToStr1D<int>()(sectionDad) << std::endl;
		std::cout << oss.str();
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

LowestCommonAncestorSectionDad Construct:
Height,Sqrt(Height): 5,2
DFSNodes: 1,2,3,5,6,8,9,7,10,12,13,11,4
NodeIdxMap: [1,0],[5,3],[9,6],[7,7],[13,10],[2,1],[10,8],[3,2],[6,4],[8,5],[4,12],[11,11],[12,9],
DadIdx: 0, 0, 0, 2, 2, 4, 4, 2, 7, 8, 8, 7, 0
Level: 0, 1, 1, 2, 2, 3, 3, 2, 3, 4, 4, 3, 1
SectionDadIdx: 0, 0, 0, 2, 2, 2, 2, 2, 2, 8, 8, 2, 0
LowestCommonAncestorSectionDad Query for "9,12": 3
LowestCommonAncestorSectionDad Query for "13,11": 7
LowestCommonAncestorSectionDad Query for "2,10": 1
*/
#endif