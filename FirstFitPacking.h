#ifndef FIRST_FIT_PACKING_H
#define FIRST_FIT_PACKING_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Pack the USPS priority mail (First-Fit Packing)
The USPS makes fixed-size mail shipping boxes--you pay a fixed price for a given box and can ship anything you want that fits in the box.
Suppose you have a set of n items that you need to ship and have an unlimited supply of the 4x12x8 inch priority mail shipping boxes.
Each item will fit in such a box but all of them combined will take multiple boxes.
Naturally, you want to minimize the number of boxes you use.
The first-fit heuristic is a greedy algorithm for the packing problem--it maintains a sequence of boxes, and processes items to pack in the sequence in which they are given.
(The greedy algorithm doesn't always give the optimum solution.)
Items are placed in the first box in which they fit.

Given n items with different sizes and an unlimited supply of boxes with same size which is big enough to accommodate the largest item.
Find the minimum number of boxes that are needed to pack all items.

Approach1: Enumerate all (always give the optimum solution)
The worst case is to use a single box to pack a single item, which requires n boxes.
In this case, enumerate all cases to use n boxes to pack n items, and find the best case with minimum box numbers.
See also BinPacking2.h

Approach2: Greedy (doesn't always give the optimum solution)
2.1 Simple greedy algorithm: O(n^2) time
2.2 Implement the first-fit packing algorithm to run in O(nlogn) time.
Construct a max-first binary tournament tree with n leaf nodes, which represent n boxes for the worst case to pack each item in a single box.
A leaf node's capacity: the remaining capacity of the underlying box.
A leaf node's items vector: the items that has been placed in the underlying box.
A parent node's capacity: the max remaining capacity of its two child subtrees.
To place an item, whenever a left subtree has big enough capacity to accommodate the current item, we place the current item to the left subtree.

For level-order traversal binary tree array:

       ____0____................1
      /         \
     1           2..............2
   /   \       /   \
  3     4     5     6...........4
/  \  /  \  /  \  /  \
7  8  9 10 11 12 13 14..........8

(perfect binary tree)
leafCount = 8
treeHeight = ceil(log2(leafCount)) + 1 = 4
treeMaxSize = 2^treeHeight - 1 = 15 (for perfect binary tree)
treeMinSize = 2*leafCount - 1 = 15 (for full binary tree)

       ____0____................1
      /         \
     1           2..............2
   /   \       /   \
  3     4     5     6...........4
      /  \  /  \
      7  8  9 10................4

(full binary tree)
leafCount = 6
treeHeight = ceil(log2(leafCount)) + 1 = 4
treeMaxSize = 2^treeHeight - 1 = 15 (for perfect binary tree)
treeMinSize = 2*leafCount - 1 = 11 (for full binary tree)

       ____0____................1
      /         \
     1           2..............2
   /   \       /   \
  3     4     5     6...........4
/  \  /  \  /
7  8  9 10 11...................5

(complete binary tree)
leafCount = 6
treeHeight = ceil(log2(leafCount)) + 1 = 4
treeMaxSize = 2^treeHeight - 1 = 15 (for perfect binary tree)

A full binary tree is a binary tree in which every node other than the leaves has two children.
A perfect binary tree is a full binary tree in which all leaves are at the same depth, and in which every parent has two children.
A complete binary tree is a binary tree in which every level, except possible the last, is completely filled, and all nodes are as far left as possible.

See also RangeMinQuerySegmentTree.h, RangeSumQuerySegmentTree.h
*/
class TournamentTree
{
	struct TreeNode
	{
		explicit TreeNode(double c): capacity(c), items(){}
		double capacity;
		std::vector<int> items;
	};
	std::vector<TreeNode> m_tree;//level order traversal of the tree
public:
	TournamentTree(int n, double unitCap) : m_tree(2 * n - 1, TreeNode(unitCap))//n leaf nodes required => the total nodes in the tree will be 2*n-1 for a complete full binary tree
	{}
	~TournamentTree(){}
	void Insert(int item, double itemCap)
	{
		this->insertRecur(0, item, itemCap);
	}
private:
	void insertRecur(int idx, int item, double itemCap)
	{
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		if (left < (int)m_tree.size())//m_tree[idx] is an INTERNAL node
		{
			this->insertRecur(m_tree[left].capacity >= itemCap ? left : right, item, itemCap);//if left child is able to accommodate, go left; otherwise, go right
			m_tree[idx].capacity = std::max(m_tree[left].capacity, m_tree[right].capacity);//update nodes bottom up with the max capacity of its left or right child
		}
		else//m_tree[idx] is a LEAF node
		{
			if (m_tree[idx].capacity - itemCap >= 0)
			{
				m_tree[idx].capacity -= itemCap;
				m_tree[idx].items.push_back(item);
			}
			else
				std::cout << "TournamentTree insufficient capacity, can't insert: " << item << ", " << itemCap << std::endl;
		}
	}
public:
	void Print() const
	{
		std::ostringstream oss;
		int N = m_tree.size();
		for (int i = 0; i < N; ++i)
		{
			int left = 2 * i + 1;
			if (left >= N)//left node only
			{
				oss << "[(" << Debug::ToStr1D<int>()(m_tree[i].items) << ")," << m_tree[i].capacity << "]";
				if (i != N - 1)
					oss << ", ";
			}
		}
		std::cout << "TournamentTree LeafNodes [(itemIdx),remainCapacity]: " << oss.str() << std::endl;
	}
};

class FirstFitPacking
{
public:
	FirstFitPacking(){}
	~FirstFitPacking(){}

	void Solve(const std::vector<double> & itemSizes, int boxSize)//boxSize should be big enough to fit the largest itemSize
	{
		int N = itemSizes.size();
		TournamentTree t(N, boxSize);
		for (int i = 0; i < N; ++i)
			t.Insert(i, itemSizes[i]);

		std::cout << "FirstFitPacking for itemSizes=\"" << Debug::ToStr1D<double>()(itemSizes) << "\", boxSize=\"" << boxSize << "\":" << std::endl;
		t.Print();
	}
};
/*
FirstFitPacking for itemSizes="9.66412, 11.5652, 16.568, 16.2848, 9.22883, 13.487, 14.0652, 6.29788, 13.3948, 17.9631, 5.98986, 11.4065, 19.4275, 16.8109, 9.50048, 13.1663, 13.8943, 13.3371, 16.3437, 11.907", boxSize="20":
TournamentTree LeafNodes [(itemIdx),remainCapacity]: [(11),8.59352], [(12),0.572543], [(13),3.1891], [(14),10.4995], [(15),6.83373], [(16),6.10575], [(17),6.66289], [(18),3.65627], [(19),8.09299], [(),20], [(),20], [(),20], [(0, 4),1.10705], [(1, 7),2.13688], [(2),3.43198], [(3),3.71517], [(5, 10),0.523174], [(6),5.93477], [(8),6.60516], [(9),2.03691]
FirstFitPacking for itemSizes="1, 2, 4, 3", boxSize="5":
TournamentTree LeafNodes [(itemIdx),remainCapacity]: [(0, 1),2], [(2),1], [(3),2], [(),5]
FirstFitPacking for itemSizes="1, 1, 1, 1, 4, 3, 2, 2", boxSize="5":
TournamentTree LeafNodes [(itemIdx),remainCapacity]: [(0, 1, 2, 3),1], [(4),1], [(5, 6),0], [(7),3], [(),5], [(),5], [(),5], [(),5]
*/

#endif