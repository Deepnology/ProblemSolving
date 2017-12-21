#ifndef RANGE_MIN_QUERY_SEGMENT_TREE_H
#define RANGE_MIN_QUERY_SEGMENT_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lowestCommonAncestor#Range_Minimum_Query_(RMQ)
http://gsourcecode.wordpress.com/2014/03/12/introduction-to-segment-trees-range-minimum-query/
Properties of a segment tree:
1. It's a binary tree, which has a left and a right child.
2. Each leaf node are the elements of the input array.
3. Each internal node represents minimum of all leaves under it.

Segment tree can also be represented as a 1D array:
1. The result segment tree is a top-down level-order traversal in a 1D array. The first element in the array is the root.
2. The leftNode index is equal to the index of curNode*2 + 1.
3. The rightNode index is equal to the index of curNode*2 + 2.
4. The parentNode index is equal to the index of (curNode - 1)/2.

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

see also RangeSumQuerySegmentTree.h, FirstFitPacking.h
*/
class RangeMinQuerySegmentTree
{
public:
	RangeMinQuerySegmentTree(){}
	~RangeMinQuerySegmentTree(){}

	//1. Construct (preprocess): O(n) time
	std::vector<int> Construct(const std::vector<int> & A)
	{
		int N = A.size();
		int treeHeight = (int)ceil(log2(N)) + 1;//treeHeight = ceil(log2(N)) + 1
		int treeMaxSize = (int)pow(2, treeHeight) - 1;//treeMaxSize = 2^treeHeight - 1

		std::vector<int> segmentTree(treeMaxSize);
		this->PostorderRecur(A, 0, N - 1, segmentTree, 0);

		std::cout << "RangeMinQuerySegmentTree Construct for \"" << Debug::ToStr1D<int>()(A) << "\": " << Debug::ToStr1D<int>()(segmentTree) << std::endl;
		return segmentTree;
	}
private:
	int PostorderRecur(const std::vector<int> & A, int curStart, int curEnd, //array var
		std::vector<int> & segmentTree, int curNode) //segmentTree var
	{
		if (curStart == curEnd)//cur node is a leaf node
		{
			segmentTree[curNode] = A[curStart];
			return segmentTree[curNode];
		}
		//cur node is a non-leaf node
		int curMiddle = curStart + (curEnd - curStart) / 2;
		int leftMin = this->PostorderRecur(A, curStart, curMiddle, segmentTree, curNode * 2 + 1);
		int rightMin = this->PostorderRecur(A, curMiddle + 1, curEnd, segmentTree, curNode * 2 + 2);
		segmentTree[curNode] = std::min(leftMin, rightMin);
		return segmentTree[curNode];
	}

	//2. Query range: O(logn) time
	//to query a range, we process at most 4 nodes at every level and number of level is O(logn)
public:
	int QueryRange(const std::vector<int> & segmentTree,
		int targetStart, int targetEnd, int totalCount) //fixed array var
	{
		if (targetStart < 0 || targetEnd > totalCount - 1 || targetStart > targetEnd)
			throw std::exception("Invalid Input");
		int min = this->QueryRangeRecur(segmentTree, 0, 0, totalCount - 1, targetStart, targetEnd);
		std::cout << "RangeMinQuerySegmentTree QueryRange for \"" << targetStart << "," << targetEnd << "\": " << min << std::endl;
		return min;
	}
private:
	int QueryRangeRecur(const std::vector<int> & segmentTree, int curNode, //segmentTree var
		int curStart, int curEnd, //array var
		int targetStart, int targetEnd) //fixed array var
	{
		//if segment of cur node is a part of target range, then return the min of the segment
		if (targetStart <= curStart && targetEnd >= curEnd)
			return segmentTree[curNode];
		//if segment of cur node is outside the target range
		if (targetStart > curEnd || targetEnd < curStart)
			return INT_MAX;
		int curMiddle = curStart + (curEnd - curStart) / 2;
		int leftMin = this->QueryRangeRecur(segmentTree, 2 * curNode + 1, curStart, curMiddle, targetStart, targetEnd);
		int rightMin = this->QueryRangeRecur(segmentTree, 2 * curNode + 2, curMiddle + 1, curEnd, targetStart, targetEnd);
		return std::min(leftMin, rightMin);
	}

	//3. Update value O(logn) time
	//to update a leaf value, we process 1 node at every level and number of level is O(logn)
public:
	void UpdateValue(std::vector<int> & A, int targetIndex, int targetVal, std::vector<int> & segmentTree)
	{
		int N = A.size();
		if (targetIndex < 0 || targetIndex > N - 1)
			throw std::exception("Invalid Input");
		A[targetIndex] = targetVal;
		this->UpdateValueRecur(segmentTree, 0, 0, N - 1, targetIndex, targetVal);
		std::cout << "RangeMinQuerySegmentTree UpdateValue for index,val = \"" << targetIndex << "," << targetVal << "\": " << Debug::ToStr1D<int>()(segmentTree) << std::endl;
	}
private:
	int UpdateValueRecur(std::vector<int> & segmentTree, int curNode, //segmentTree var
		int curStart, int curEnd, //array var
		int targetIndex, int targetVal) //fixed array var
	{
		//if tareget index is outside cur range
		if (targetIndex < curStart || targetIndex > curEnd)
			return INT_MAX;
		if (curStart == curEnd)//cur node is leaf node: update cur node
		{
			segmentTree[curNode] = targetVal;
			return segmentTree[curNode];
		}
		//cur node is non-leaf node: update children of cur node, then update cur node
		//1. update children
		int curMiddle = curStart + (curEnd - curStart) / 2;
		int leftMin = this->UpdateValueRecur(segmentTree, 2 * curNode + 1, curStart, curMiddle, targetIndex, targetVal);
		int rightMin = this->UpdateValueRecur(segmentTree, 2 * curNode + 2, curMiddle + 1, curEnd, targetIndex, targetVal);
		//2. update cur node
		segmentTree[curNode] = std::min(leftMin, rightMin);

		return segmentTree[curNode];
	}
};
/*
RangeMinQuerySegmentTree Construct for "2, 5, 1, 4, 9, 3": 1, 1, 3, 2, 1, 4, 3, 2, 5, 0, 0, 4, 9, 0, 0
RangeMinQuerySegmentTree QueryRange for "1,5": 1
RangeMinQuerySegmentTree UpdateValue for index,val = "2,-1": -1, -1, 3, 2, -1, 4, 3, 2, 5, 0, 0, 4, 9, 0, 0
RangeMinQuerySegmentTree QueryRange for "1,5": -1
*/
#endif