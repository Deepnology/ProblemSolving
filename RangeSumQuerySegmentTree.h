#ifndef RANGE_SUM_QUERY_SEGMENT_TREE_H
#define RANGE_SUM_QUERY_SEGMENT_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
segment tree:
1. Leaf nodes are the elements of the input array
2. Each internal node represents some merging of the leaf nodes.
   The merging may be different for different problems.
   For this problem, merging is sum of leaves under a node.
An array representation of tree is used to represent segment trees.
For each node at index i, the left child is at index 2*i+1, right child at 2*i+2, and the parent is at (i-1)/2

The result segment tree is in level order traversal in a 1D array.

See also RangeMinQuerySegmentTree.h, FirstFitPacking.h
*/
class RangeSumQuerySegmentTree
{
public:
	RangeSumQuerySegmentTree(){}
	~RangeSumQuerySegmentTree(){}

	//1. Construct (preprocess): O(n) time
	std::vector<int> Construct(const std::vector<int> & A)
	{
		int N = A.size();
		int treeHeight = (int)ceil(log2(N)) + 1;//treeHeight = ceil(log2(N)) + 1
		int treeMaxSize = (int)pow(2, treeHeight) - 1;//treeMaxSize = 2^treeHeight - 1

		std::vector<int> segmentTree(treeMaxSize);
		this->PostorderRecur(A, 0, N - 1, segmentTree, 0);

		std::cout << "RangeSumQuerySegmentTree Construct for \"" << Debug::ToStr1D<int>()(A) << "\": " << Debug::ToStr1D<int>()(segmentTree) << std::endl;
		return segmentTree;
	}
private:
	int PostorderRecur(const std::vector<int> & A, int curStart, int curEnd, //array var
		std::vector<int> & segmentTree, int curNode)//segmentTree var
	{
		if (curStart == curEnd)//cur node is a leaf node
		{
			segmentTree[curNode] = A[curStart];
			return segmentTree[curNode];
		}
		//cur node is a non-leaf node
		int curMiddle = curStart + (curEnd - curStart) / 2;
		int leftSum = this->PostorderRecur(A, curStart, curMiddle, segmentTree, curNode * 2 + 1);
		int rightSum = this->PostorderRecur(A, curMiddle + 1, curEnd, segmentTree, curNode * 2 + 2);
		segmentTree[curNode] = leftSum + rightSum;

		return segmentTree[curNode];
	}

	//2. Query range: O(logn) time
	//to query a range, we process at most 4 nodes at every level and number of level is O(logn)
public:
	int QueryRange(const std::vector<int> & segmentTree, 
		int targetStart, int targetEnd, int totalCount) //fixed array var
	{
		if (targetStart < 0 || targetEnd > totalCount - 1 || targetStart > targetEnd)
			throw std::runtime_error("Invalid Input");
		int sum = this->QueryRangeRecur(segmentTree, 0, 0, totalCount - 1, targetStart, targetEnd);
		std::cout << "RangeSumQuerySegmentTree QueryRange for \"" << targetStart << "," << targetEnd << "\": " << sum << std::endl;
		return sum;
	}
private:
	int QueryRangeRecur(const std::vector<int> & segmentTree, int curNode, //segmentTree var
		int curStart, int curEnd, //array var
		int targetStart, int targetEnd) //fixed array var
	{
		//if segment of cur node is a part of target range, then return the sum of the segment
		if (targetStart <= curStart && targetEnd >= curEnd)
			return segmentTree[curNode];
		//if segment of cur node is outside the target range
		if (targetStart > curEnd || targetEnd < curStart)
			return 0;
		int curMiddle = curStart + (curEnd - curStart) / 2;
		int leftSum = this->QueryRangeRecur(segmentTree, 2 * curNode + 1, curStart, curMiddle, targetStart, targetEnd);
		int rightSum = this->QueryRangeRecur(segmentTree, 2 * curNode + 2, curMiddle + 1, curEnd, targetStart, targetEnd);
		return leftSum + rightSum;
	}

	//3. Update value O(logn) time
	//to update a leaf value, we process 1 node at every level and number of level is O(logn)
public:
	void UpdateValue(std::vector<int> & A, int targetIndex, int targetVal, std::vector<int> & segmentTree)
	{
		int N = A.size();
		if (targetIndex < 0 || targetIndex > N - 1)
			throw std::runtime_error("Invalid Input");
		A[targetIndex] = targetVal;
		this->UpdateValueRecur(segmentTree, 0, 0, N - 1, targetIndex, targetVal);
		std::cout << "RangeSumQuerySegmentTree UpdateValue for index,val = \"" << targetIndex << "," << targetVal << "\": " << Debug::ToStr1D<int>()(segmentTree) << std::endl;
	}
private:
	void UpdateValueRecur(std::vector<int> & segmentTree, int curNode, //segmentTree var
		int curStart, int curEnd, //array var
		int targetIndex, int targetVal) //fixed array var
	{
		//if tareget index is outside cur range
		if (targetIndex < curStart || targetIndex > curEnd)
			return;
		if (curStart == curEnd)//cur node is a leaf node
		{
			segmentTree[curNode] = targetVal;
			return;
		}
		//cur node is a non-leaf node
		int curMiddle = curStart + (curEnd - curStart) / 2;
		this->UpdateValueRecur(segmentTree, 2 * curNode + 1, curStart, curMiddle, targetIndex, targetVal);
		this->UpdateValueRecur(segmentTree, 2 * curNode + 2, curMiddle + 1, curEnd, targetIndex, targetVal);
		segmentTree[curNode] = segmentTree[2 * curNode + 1] + segmentTree[2 * curNode + 2];
	}
};
/*
RangeSumQuerySegmentTree Construct for "1, 3, 5, 7, 9, 11": 36, 9, 27, 4, 5, 16, 11, 1, 3, 0, 0, 7, 9, 0, 0
RangeSumQuerySegmentTree QueryRange for "1,3": 15
RangeSumQuerySegmentTree UpdateValue for index,val = "1,10": 43, 16, 27, 11, 5, 16, 11, 1, 10, 0, 0, 7, 9, 0, 0
RangeSumQuerySegmentTree QueryRange for "1,3": 22
*/
#endif