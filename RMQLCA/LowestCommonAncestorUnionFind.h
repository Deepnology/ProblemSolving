#ifndef LOWEST_COMMON_ANCESTOR_UNION_FIND_H
#define LOWEST_COMMON_ANCESTOR_UNION_FIND_H
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
#include "UnionFindGraphComponent.h"
/*
http://en.wikipedia.org/wiki/Tarjan%27s_off-line_lowest_common_ancestors_algorithm
Tarjan's algorithm:
offline: all pairs of nodes for which the lowest common ancestor is desired must be specified in advance
O(n) time

  ________1_________
 /        |         \
2    _____3______    4
    /     |      \
   5      6       7
         / \     / \
        8   9  10   11
               / \
             12   13

          0  1  2  3  4  5  6  7  8  9 10 11 12
DFSNodes: 1  2  3  5  6  8  9  7 10 12 13 11  4
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

Algorithm:
Each node is marked unvisited initially, and is marked visited after it and all its children have been visited.

The lowest common ancestor of the pair {u,v} is available as "Find(v).ancestor"
immediately (and only immediately) after u is visited, provided v is already visited.

Otherwise, it will be available later as "Find(u).ancestor", immediately after v is visited.
*/
class LowestCommonAncestorUnionFind
{
public:
	LowestCommonAncestorUnionFind(){}
	~LowestCommonAncestorUnionFind(){}
	struct TreeNode//not binary!
	{
		TreeNode(int x) : val(x), children() {}
		int val;
		std::vector<TreeNode *> children;
	};

	//return a list of nodes which are LCAs of pairs of nodes in nodePairs, using naive UnionFind
	std::vector<TreeNode *> Find_Tarjan1(TreeNode * root, std::vector<std::pair<TreeNode *, TreeNode*> > & nodePairs)
	{
		std::vector<TreeNode *> dfsNodes;//DFS index to TreeNode ptr
		std::unordered_map<TreeNode *, int> nodeIdxMap;//TreeNode ptr to DFS index
		std::vector<int> parentIdx;
		std::vector<TreeNode *> curAncestor;
		std::vector<int> visit;

		//complete: dfsNodes, nodeIdxMap
		//init: parentIdx, curAncestor, visit
		this->dFS_Init1(root, dfsNodes, nodeIdxMap, parentIdx, curAncestor, visit);//O(n) time
		//std::cout << Debug::ToStr1D<int>()(parentIdx) << std::endl;

		std::vector<TreeNode *> res(nodePairs.size(), NULL);
		this->dFS_UnionFind1(root, dfsNodes, nodeIdxMap, parentIdx, curAncestor, visit, nodePairs, res);//O(n) time

		this->print1(dfsNodes, nodeIdxMap, parentIdx, curAncestor, visit, nodePairs, res);
		return res;
	}
private:
	void dFS_Init1(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<int> & parentIdx,
		std::vector<TreeNode *> & curAncestor, std::vector<int> & visit)
	{
		dfsNodes.push_back(curNode);
		nodeIdxMap.insert({ curNode, dfsNodes.size() - 1 });
		parentIdx.push_back(-1);
		curAncestor.push_back(NULL);
		visit.push_back(0);
		int N = curNode->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * curChild = curNode->children[i];
			this->dFS_Init1(curChild, dfsNodes, nodeIdxMap, parentIdx, curAncestor, visit);
		}
	}
	void dFS_UnionFind1(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<int> & parentIdx,
		std::vector<TreeNode *> & curAncestor, std::vector<int> & visit,
		std::vector<std::pair<TreeNode *, TreeNode *> > & targetNodePairs, std::vector<TreeNode *> & targetAncestors)
	{
		int N = curNode->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * curChild = curNode->children[i];
			this->dFS_UnionFind1(curChild, dfsNodes, nodeIdxMap, parentIdx, curAncestor, visit, targetNodePairs, targetAncestors);

			//post-order Union-Find for each child:
			//1. Union curNode with curChild
			UnionFindGraphComponent().Union(parentIdx, nodeIdxMap[curNode], nodeIdxMap[curChild]);
			//2. After Union, assign curNode as ancestor of "Find(curNode) = root of the set"
			curAncestor[UnionFindGraphComponent().FindRecur(parentIdx, nodeIdxMap[curNode])] = curNode;

			std::cout << "Union " << curNode->val << "(Ancestor of new root) with " << curChild->val << ", new root: " << dfsNodes[UnionFindGraphComponent().FindRecur(parentIdx, nodeIdxMap[curNode])]->val << " (" << Debug::ToStr1D<int>()(parentIdx) << ")" << std::endl;
		}
		//now mark the curNode visited in post-order
		visit[nodeIdxMap[curNode]] = 1;

		//post-order:
		//look for target node pairs that both of the nodes have been visited, and find their lowest common ancestor
		//the lowest common ancestor will be the other node's ancestor
		int M = targetNodePairs.size();
		for (int i = 0; i < M; ++i)
		{
			if (targetAncestors[i] == NULL)
			{
				if (targetNodePairs[i].first == curNode)//immediately after curNode is visited
				{
					TreeNode * other = targetNodePairs[i].second;
					if (visit[nodeIdxMap[other]] == 1)//now both nodes in the pair have been visited
						targetAncestors[i] = curAncestor[UnionFindGraphComponent().FindRecur(parentIdx, nodeIdxMap[other])];//LCA = find(other).ancestor
				}
				else if (targetNodePairs[i].second == curNode)//immediately after curNode is visited
				{
					TreeNode * other = targetNodePairs[i].first;
					if (visit[nodeIdxMap[other]] == 1)//now both nodes in the pair have been visited
						targetAncestors[i] = curAncestor[UnionFindGraphComponent().FindRecur(parentIdx, nodeIdxMap[other])];//LCA = find(other).ancestor
				}
			}
		}
	}


public:
	//return a list of nodes which are LCAs of pairs of nodes in nodePairs, using rank and compression UnionFind
	std::vector<TreeNode *> Find_Tarjan2(TreeNode * root, std::vector<std::pair<TreeNode *, TreeNode*> > & nodePairs)
	{
		std::vector<TreeNode *> dfsNodes;//DFS index to TreeNode ptr
		std::unordered_map<TreeNode *, int> nodeIdxMap;//TreeNode ptr to DFS index
		std::vector<std::pair<int, int> > parentRankPairs;
		std::vector<TreeNode *> curAncestor;
		std::vector<int> visit;

		//complete: dfsNodes, nodeIdxMap
		//init: parentRankPairs, curAncestor, visit
		this->dFS_Init2(root, dfsNodes, nodeIdxMap, parentRankPairs, curAncestor, visit);//O(n) time
		//std::cout << Debug::ToStr1D<int>()(parentRankPairs) << std::endl;

		std::vector<TreeNode *> res(nodePairs.size(), NULL);
		this->dFS_UnionFind2(root, dfsNodes, nodeIdxMap, parentRankPairs, curAncestor, visit, nodePairs, res);//O(n) time

		this->print2(dfsNodes, nodeIdxMap, parentRankPairs, curAncestor, visit, nodePairs, res);
		return res;
	}
private:
	void dFS_Init2(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<std::pair<int, int> > & parentRankPairs,
		std::vector<TreeNode *> & curAncestor, std::vector<int> & visit)
	{
		dfsNodes.push_back(curNode);
		nodeIdxMap.insert({ curNode, dfsNodes.size() - 1 });
		parentRankPairs.push_back(std::make_pair(dfsNodes.size() - 1, 0));//init parentRankPairs with (parent, rank) = (current index, 0)
		curAncestor.push_back(NULL);
		visit.push_back(0);
		int N = curNode->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * curChild = curNode->children[i];
			this->dFS_Init2(curChild, dfsNodes, nodeIdxMap, parentRankPairs, curAncestor, visit);
		}
	}
	void dFS_UnionFind2(TreeNode * curNode, std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<std::pair<int, int> > & parentRankPairs,
		std::vector<TreeNode *> & curAncestor, std::vector<int> & visit,
		std::vector<std::pair<TreeNode *, TreeNode *> > & targetNodePairs, std::vector<TreeNode *> & targetAncestors)
	{
		int N = curNode->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * curChild = curNode->children[i];
			this->dFS_UnionFind2(curChild, dfsNodes, nodeIdxMap, parentRankPairs, curAncestor, visit, targetNodePairs, targetAncestors);
			//post-order Union-Find for each child:
			//1. Union current node with child
			UnionFindGraphComponent().Union(parentRankPairs, nodeIdxMap[curNode], nodeIdxMap[curChild]);
			//2. After Union, assign curNode as ancestor of "Find(curNode) = root of the set"
			curAncestor[UnionFindGraphComponent().FindRecur(parentRankPairs, nodeIdxMap[curNode])] = curNode;
		}
		//now mark the curNode visited in post-order
		visit[nodeIdxMap[curNode]] = 1;
		
		//post-order:
		//look for target node pairs that both of the nodes have been visited, and find their lowest common ancestor
		//the lowest common ancestor will be the other node's ancestor
		int M = targetNodePairs.size();
		for (int i = 0; i < M; ++i)
		{
			if (targetAncestors[i] == NULL)
			{
				if (targetNodePairs[i].first == curNode)//immediately after curNode is visited
				{
					TreeNode * other = targetNodePairs[i].second;
					if (visit[nodeIdxMap[other]] == 1)//now both nodes in the pair have been visited
						targetAncestors[i] = curAncestor[UnionFindGraphComponent().FindRecur(parentRankPairs, nodeIdxMap[other])];//LCA = Find(other).ancestor
				}
				else if (targetNodePairs[i].second == curNode)//immediately after curNode is visited
				{
					TreeNode * other = targetNodePairs[i].first;
					if (visit[nodeIdxMap[other]] == 1)//now both nodes in the pair have been visited
						targetAncestors[i] = curAncestor[UnionFindGraphComponent().FindRecur(parentRankPairs, nodeIdxMap[other])];//LCA = Find(other).ancestor
				}
			}
		}
	}

private:
	void print1(std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<int> & parentIdx,
		std::vector<TreeNode *> & curAncestor, std::vector<int> & visit,
		std::vector<std::pair<TreeNode *, TreeNode *> > & targetNodePairs, std::vector<TreeNode *> & targetAncestors)
	{
		std::ostringstream oss;
		oss << "LowestCommonAncestorUnionFind1:" << std::endl;
		oss << "DFSNodes:	";
		int N = dfsNodes.size();
		for (int i = 0; i < N; ++i)
		{
			oss << dfsNodes[i]->val;
			if (i != N - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "NodeIdxMap: ";
		for (auto i : nodeIdxMap)
		{
			oss << "[" << i.first->val << "," << i.second << "],";
		}
		oss << std::endl;
		oss << "ParentIdx:	";
		for (int i = 0; i < N; ++i)
		{
			oss << parentIdx[i];
			if (i != N - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "CurAncestor:	";
		for (int i = 0; i < N; ++i)
		{
			if (curAncestor[i] != NULL)
				oss << curAncestor[i]->val;
			else
				oss << "N";
			if (i != N - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "TargetNodePairs: ";
		for (int i = 0; i < (int)targetNodePairs.size(); ++i)
		{
			oss << "[" << targetNodePairs[i].first->val << "," << targetNodePairs[i].second->val << "]";
			if (i != (int)targetNodePairs.size() - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "TargetLCAs: ";
		for (int i = 0; i < (int)targetAncestors.size(); ++i)
		{
			if (targetAncestors[i] != NULL)
				oss << targetAncestors[i]->val;
			else
				oss << "N";
			if (i != (int)targetAncestors.size() - 1)
				oss << ",";
		}
		oss << std::endl;
		std::cout << oss.str() << std::endl;
	}
	void print2(std::vector<TreeNode *> & dfsNodes, std::unordered_map<TreeNode *, int> & nodeIdxMap, std::vector<std::pair<int, int> > & parentRankPairs,
		std::vector<TreeNode *> & curAncestor, std::vector<int> & visit,
		std::vector<std::pair<TreeNode *, TreeNode *> > & targetNodePairs, std::vector<TreeNode *> & targetAncestors)
	{
		std::ostringstream oss;
		oss << "LowestCommonAncestorUnionFind2:" << std::endl;
		oss << "DFSNodes:	";
		int N = dfsNodes.size();
		for (int i = 0; i < N; ++i)
		{
			oss << dfsNodes[i]->val;
			if (i != N - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "NodeIdxMap: ";
		for (auto i : nodeIdxMap)
		{
			oss << "[" << i.first->val << "," << i.second << "],";
		}
		oss << std::endl;
		oss << "Parent,Rank: " << Debug::ToStr1D<int>()(parentRankPairs) << std::endl;
		oss << "CurAncestor:	";
		for (int i = 0; i < N; ++i)
		{
			if (curAncestor[i] != NULL)
				oss << curAncestor[i]->val;
			else
				oss << "N";
			if (i != N - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "TargetNodePairs: ";
		for (int i = 0; i < (int)targetNodePairs.size(); ++i)
		{
			oss << "[" << targetNodePairs[i].first->val << "," << targetNodePairs[i].second->val << "]";
			if (i != (int)targetNodePairs.size() - 1)
				oss << ",";
		}
		oss << std::endl;
		oss << "TargetLCAs: ";
		for (int i = 0; i < (int)targetAncestors.size(); ++i)
		{
			if (targetAncestors[i] != NULL)
				oss << targetAncestors[i]->val;
			else
				oss << "N";
			if (i != (int)targetAncestors.size() - 1)
				oss << ",";
		}
		oss << std::endl;
		std::cout << oss.str() << std::endl;
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

Union 1(Ancestor of new root) with 2, new root: 2 (1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1)
Union 3(Ancestor of new root) with 5, new root: 5 (1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1)
Union 6(Ancestor of new root) with 8, new root: 8 (1, -1, 3, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1)
Union 6(Ancestor of new root) with 9, new root: 9 (1, -1, 3, -1, 5, 6, -1, -1, -1, -1, -1, -1, -1)
Union 3(Ancestor of new root) with 6, new root: 9 (1, -1, 3, 6, 5, 6, -1, -1, -1, -1, -1, -1, -1)
Union 10(Ancestor of new root) with 12, new root: 12 (1, -1, 3, 6, 5, 6, -1, -1, 9, -1, -1, -1, -1)
Union 10(Ancestor of new root) with 13, new root: 13 (1, -1, 3, 6, 5, 6, -1, -1, 9, 10, -1, -1, -1)
Union 7(Ancestor of new root) with 10, new root: 13 (1, -1, 3, 6, 5, 6, -1, 10, 9, 10, -1, -1, -1)
Union 7(Ancestor of new root) with 11, new root: 11 (1, -1, 3, 6, 5, 6, -1, 10, 9, 10, 11, -1, -1)
Union 3(Ancestor of new root) with 7, new root: 11 (1, -1, 3, 6, 5, 6, 11, 10, 9, 10, 11, -1, -1)
Union 1(Ancestor of new root) with 3, new root: 11 (1, 11, 3, 6, 5, 6, 11, 10, 9, 10, 11, -1, -1)
Union 1(Ancestor of new root) with 4, new root: 4 (1, 11, 3, 6, 5, 6, 11, 10, 9, 10, 11, 12, -1)
LowestCommonAncestorUnionFind1:
DFSNodes:	1,2,3,5,6,8,9,7,10,12,13,11,4
NodeIdxMap: [1,0],[2,1],[3,2],[11,11],[5,3],[6,4],[8,5],[4,12],[9,6],[12,9],[7,7],[10,8],[13,10],
ParentIdx:	1,11,3,6,5,6,11,10,9,10,11,12,-1
CurAncestor:	N,1,N,3,N,6,3,N,N,10,7,1,1
TargetNodePairs: [9,12],[13,11],[2,10]
TargetLCAs: 3,7,1

LowestCommonAncestorUnionFind2:
DFSNodes:	1,2,3,5,6,8,9,7,10,12,13,11,4
NodeIdxMap: [1,0],[2,1],[3,2],[11,11],[5,3],[6,4],[8,5],[4,12],[9,6],[12,9],[7,7],[10,8],[13,10],
Parent,Rank: [2,1], [0,0], [2,2], [2,0], [2,1], [4,0], [2,0], [8,0], [2,1], [8,0], [8,0], [8,0], [2,0]
CurAncestor:	1,N,1,N,6,N,N,N,7,N,N,N,N
TargetNodePairs: [9,12],[13,11],[2,10]
TargetLCAs: 3,7,1
*/
#endif