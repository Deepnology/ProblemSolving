#ifndef QUAD_TREE_H
#define QUAD_TREE_H
#include "Debug.h"
/*
Leetcode: Construct Quad Tree
We want to use quad trees to store an N x N boolean grid.
Each cell in the grid can only be true or false.
The root node represents the whole grid.
For each node, it will be subdivided into four children nodes until the values in the region it represents are all the same.
Each node has another two boolean attributes : isLeaf and val.
isLeaf is true if and only if the node is a leaf node.
The val attribute for a leaf node contains the value of the region it represents.

Leetcode: Quad Tree Intersection
A quadtree is a tree data in which each internal node has exactly four children: topLeft, topRight, bottomLeft and bottomRight.
Quad trees are often used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions.
We want to store True/False information in our quad tree.
The quad tree is used to represent a N * N boolean grid.
For each node, it will be subdivided into four children nodes until the values in the region it represents are all the same.
Each node has another two boolean attributes : isLeaf and val.
isLeaf is true if and only if the node is a leaf node.
The val attribute for a leaf node contains the value of the region it represents.

 */
class QuadTree
{
public:
	class Node
	{
	public:
		bool val;
		bool isLeaf;
		Node* topLeft;
		Node* topRight;
		Node* bottomLeft;
		Node* bottomRight;
		Node() {}
		Node(bool _val, bool _isLeaf, Node * _topLeft, Node * _topRight, Node * _bottomLeft, Node * _bottomRight)
		{
			val = _val;
			isLeaf = _isLeaf;
			topLeft = _topLeft;
			topRight = _topRight;
			bottomLeft = _bottomLeft;
			bottomRight = _bottomRight;
		}
	};

	QuadTree(){}
	~QuadTree(){}

	Node * Construct(std::vector<std::vector<int>> && grid)
	{
		int N = grid.size();
		Node * root = recur(grid, 0, 0, N);
		Debug::Print2D<int>()(grid, false);
		PrintBFS(root);
		return root;
	}
	Node * recur(std::vector<std::vector<int>> & grid, int row, int col, int len)//(row,col) is upper left corner of each quarter
	{
		if (len == 1)
			return new Node(grid[row][col], true, NULL, NULL, NULL, NULL);
		Node * upperLeft = recur(grid, row, col, len/2);
		Node * upperRight = recur(grid, row, col+len/2, len/2);
		Node * bottomLeft = recur(grid, row+len/2, col, len/2);
		Node * bottomRight = recur(grid, row+len/2, col+len/2, len/2);
		Node * cur;
		if (upperLeft->isLeaf && upperRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf)
			if (upperLeft->val == upperRight->val && upperRight->val == bottomLeft->val && bottomLeft->val == bottomRight->val)
			{
				int val = upperLeft->val;
				delete upperLeft; delete upperRight; delete bottomLeft; delete bottomRight;
				return new Node(val, true, NULL, NULL, NULL, NULL);
			}
		return new Node(false, false, upperLeft, upperRight, bottomLeft, bottomRight);
	}

	Node * Intersect(Node * quadTree1, Node * quadTree2)
	{
		Node * root = recur(quadTree1, quadTree2);
		std::cout << "QuadTree Intersect (OR): " << std::endl;
		PrintBFS(root);
		return root;
	}
	Node * recur(Node * cur1, Node * cur2)
	{
		if (cur1->isLeaf) return cur1->val ? cur1 : cur2;
		if (cur2->isLeaf) return cur2->val ? cur2 : cur1;

		Node * topLeft = recur(cur1->topLeft, cur2->topLeft);
		Node * topRight = recur(cur1->topRight, cur2->topRight);
		Node * bottomLeft = recur(cur1->bottomLeft, cur2->bottomLeft);
		Node * bottomRight = recur(cur1->bottomRight, cur2->bottomRight);

		if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf &&
			(topLeft->val && topRight->val && bottomLeft->val && bottomRight->val ||
			 !topLeft->val && !topRight->val && !bottomLeft->val && !bottomRight->val))
		{
			bool val = topLeft->val;
			delete topLeft; delete topRight; delete bottomLeft; delete bottomRight;
			return new Node(val, true, NULL, NULL, NULL, NULL);
		}
		else
			return new Node(true, false, topLeft, topRight, bottomLeft, bottomRight);//the val for a parent node doesn't matter
	}

	void PrintBFS(Node * root)
	{
		if (root == NULL) return;
		std::ostringstream oss;
		std::queue<std::pair<Node*,int>> que;//<Node,idx>
		que.push({root,0});
		int curMaxIdx = 0; //idx of last leaf node visited
		while (!que.empty())
		{
			int levelCount = que.size();
			while (levelCount-- > 0)
			{
				Node * cur = que.front().first;
				int idx = que.front().second;
				que.pop();
				if (cur)
					oss << "(" << cur->isLeaf << "," << cur->val << "), ";
				else if (idx < curMaxIdx) //there is a leaf node in the queue
					oss << "NULL, ";
				if (cur)
				{
					que.push({cur->topLeft,4*idx+1}); if (cur->topLeft) curMaxIdx = 4*idx+1;
					que.push({cur->topRight,4*idx+2}); if (cur->topRight) curMaxIdx = 4*idx+2;
					que.push({cur->bottomLeft,4*idx+3}); if (cur->bottomLeft) curMaxIdx = 4*idx+3;
					que.push({cur->bottomRight,4*idx+4}); if (cur->bottomRight) curMaxIdx = 4*idx+4;
				}
			}
		}
		std::cout << "QuadTree BFS: " << oss.str() << std::endl;
	}
};
#endif