#ifndef INVERSIONS_IN_ARRAY_H
#define INVERSIONS_IN_ARRAY_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: count of smaller numbers after self
Elements of programming interview, Recursion: Count inversions
http://www.geeksforgeeks.org/counting-inversions/
http://www.techsamaritan.org/courses/defasun/interviewQ2.html
An inversion is an out of order pair in the array, or a pair (v[i], v[j]) such that v[i] > v[j] && i < j given an integer array v.
Apparently, for a sorted array, the number of inversions is 0.
For a array sorted by reverse order, the number of inversions is the maximum.

Naive: O(n^2) time
EnhancedMergeSort: O(nlogn) time, O(n) space
BST: O(nlogn) time, O(n) space
UsePrefixSums: O(n^2) time, O(n) space
UseBinaryIndexedTree: O(nlogn) time, O(n) space

EnhancedMergeSort: O(nlogn) time, O(n) space
We can count the number of iversions along with the merge sort.
When we merge two lists (left and right list), the number of inversions is the sum of:
1. number of inversions we have already counted in the left list
2. number of inversions we have already counted in the right list
3. number of elements in the left list that is not merged yet when an element from the right list is picked up during the merge

BST: O(nlogn) time, O(n) space
Construct a binary search tree for all elements in the array.
In each node, keep a leftCount which indicates number of child of left sub-tree.
Also keep a originalIndex which is the index of element.
Perform an inorder traversal of the tree, keep track of accumulated node count, save the accumulated node count to originalIndex in an empty array. O(n) time.
If we want to lookup the count of smaller nodes of a particular node, we can "accumulate the leftCount of each node plus 1 when going right" in the path starting from root and binary searching down to the target node. O(logn) time.
See also BinarySearchTree.h

PrefixSum:
6,3,6,5,2,4 => min=2
4,1,4,3,0,2 => shifted w/ min shifted to 0
			=> max=4, range in [0:4], size needs to be 5
idx:		0, 1, 2, 3, 4
prefixSum:	0, 0, 0, 0, 0
				  ^
			0, 0, 0, 1, 1
			^
			0, 1, 1, 2, 2
					 ^
			0, 1, 1, 2, 3
						^
			0, 1, 1, 2, 3
			   ^
			0, 1, 2, 3, 4
						^
res = 4,1,3,2,0,0

5,2,6,1 => min=1
4,1,5,0 => shifted w/ min shifted to 0
		=> max=5, range in [0:5], size needs to be 6
idx:		0, 1, 2, 3, 4, 5
prefixSum:	0, 0, 0, 0, 0, 0
			^
			0, 1, 1, 1, 1, 1
						   ^
			0, 1, 1, 1, 1, 1
			   ^
			0, 1, 2, 2, 2, 2
						^
res = 2,1,1,0
*/
class InversionsInArray
{
public:
	InversionsInArray(){}
	~InversionsInArray(){}

	std::vector<int> Naive(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> res(N, 0);
		//enumerate all the pairs in v
		for (int i = 0; i < N - 1; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (v[i] > v[j])
					++res[i];
			}
		}
		std::cout << "InversionsInArray Naive for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> EnhancedMergeSort(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::pair<int, int>> v2;//first: value, second: original index before sorting
		for (int i = 0; i < N; ++i)
		{
			v2.push_back(std::make_pair(v[i], i));
		}
		std::vector<std::pair<int, int> > tmp(N);
		std::vector<int> res(N, 0);
		this->MergeSortRecur(v2, 0, N - 1, tmp, res);
		std::cout << "InversionsInArray EnhancedMergeSort for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void MergeSortRecur(std::vector<std::pair<int, int>> & v2, int left, int right, std::vector<std::pair<int, int> > & tmp, std::vector<int> & res)
	{
		if (left >= right)
			return;
		int mid = (left + right) / 2;

		this->MergeSortRecur(v2, left, mid, tmp, res);
		this->MergeSortRecur(v2, mid + 1, right, tmp, res);

		int i = left;
		int j = mid + 1;
		int k = left;
		int numCount = 0;
		while (i <= mid && j <= right)
		{
			if (v2[i].first <= v2[j].first)
			{
				/*accumulate numCount to current element*/
				res[v2[i].second] += numCount;
				tmp[k++] = v2[i++];
			}
			else
			{
				/*increment numCount when an element from the right list is picked up*/
				++numCount;
				tmp[k++] = v2[j++];
			}
		}
		while (i <= mid)
		{
			res[v2[i].second] += numCount;
			tmp[k++] = v2[i++];
		}
		while (j <= right)
		{
			tmp[k++] = v2[j++];
		}

		for (int x = left; x <= right; ++x)
		{
			v2[x] = tmp[x];
		}
	}
public:
	std::vector<int> UsePrefixSums(std::vector<int> && v)//O(n^2) time
	{
		if (v.empty()) return std::vector<int>();
		int N = v.size();
		int Min = *std::min_element(v.begin(), v.end());
		for (int i = 0; i < N; ++i)
			v[i] = v[i] - Min;
		int range = *std::max_element(v.begin(), v.end()) + 1;//range = [0:max]
		std::vector<int> res(N);
		
		std::vector<int> prefixSums(range, 0);
		for (int i = N - 1; i >= 0; --i)
		{
			res[i] = prefixSums[v[i]];
			//res[i] = v[i] - 1 < 0 ? 0 : prefixSums[v[i] - 1];
			for (int j = v[i] + 1; j < range; ++j)
				prefixSums[j] += 1;
		}

		std::cout << "InversionsInArray UsePrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> UseBinaryIndexedTree(std::vector<int> && v)//O(nlogn) time
	{
		if (v.empty()) return std::vector<int>();
		int N = v.size();
		int Min = *std::min_element(v.begin(), v.end());
		for (int i = 0; i < N; ++i)
			v[i] = v[i] - Min;
		int range = *std::max_element(v.begin(), v.end()) + 1;//range = [0:max]
		std::vector<int> res(N);

		std::vector<int> bit(range + 1, 0);
		for (int i = N - 1; i >= 0; --i)
		{
			res[i] = prefixSum(bit, v[i]);
			update(bit, v[i] + 1, 1);
		}

		std::cout << "InversionsInArray UseBinaryIndexedTree for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	int prefixSum(const std::vector<int> & bit, int idx)
	{
		int sum = 0;
		for (int i = idx + 1; i > 0; i -= i&(-i))
			sum += bit[i];
		return sum;
	}
	void update(std::vector<int> & bit, int idx, int val)
	{
		int N = bit.size();
		for (int i = idx + 1; i < N; i += i&(-i))
			bit[i] += val;
	}

public:
	int CountTotal_MergeSort2(std::vector<int> && v)
	{
		int N = v.size();
		std::vector<int> tmp(N);
		int res = MergeSortRecur2(v, 0, N - 1, tmp);
		std::cout << "InversionsInArray CountTotal_MergeSort2 for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	int MergeSortRecur2(std::vector<int> & v, int left, int right, std::vector<int> & tmp)
	{
		if (left >= right)
			return 0;
		int mid = (left + right) / 2;
		int count = 0;
		count += MergeSortRecur2(v, left, mid, tmp);
		count += MergeSortRecur2(v, mid + 1, right, tmp);
		int i = left;
		int j = mid + 1;
		int k = left;
		while (i <= mid && j <= right)
		{
			if (v[i] <= v[j])
			{
				tmp[k++] = v[i++];
			}
			else
			{
				tmp[k++] = v[j++];
				count += (mid - i + 1);//add count of elements in leftside that are not merged yet when picking an element from rightside
			}
		}
		while (i <= mid)
			tmp[k++] = v[i++];
		while (j <= right)
			tmp[k++] = v[j++];
		for (int x = left; x <= right; ++x)
			v[x] = tmp[x];
		return count;
	}


    //use BST
    struct TreeNode
    {
        TreeNode * left;
        TreeNode * right;
        int val;
        int leftCount;
        explicit TreeNode(int val_):val(val_),leftCount(0),left(NULL),right(NULL){}
    };
    int Insert(int val, TreeNode *& cur)
    {
        if (cur == NULL)
        {
            cur = new TreeNode(val);
            return 0;
        }
        else if (val < cur->val)//too big, go left
        {
            int smallerCount = Insert(val, cur->left);
            ++cur->leftCount;
            return smallerCount;
        }
        else if (val > cur->val)
        {
            int smallerCount = cur->leftCount + 1 + Insert(val, cur->right);//accumulate smaller node count when going right
            return smallerCount;
        }
        else//when equal, insert to right
        {
            int smallerCount = cur->leftCount + Insert(val, cur->right);//accumulate smaller node count when going right
            return smallerCount;
        }
    }
public:
    std::vector<int> UseBST(const std::vector<int> & v)
    {
        if (v.empty()) return std::vector<int>();
        int N = v.size();
        std::vector<int> res(N, 0);
        TreeNode * root = NULL;
        for (int i = N-1; i >= 0; --i)
            res[i] = Insert(v[i], root);
        //res[i] is the smaller node count of current inserted node in the BST during the process of insertion from right to left of v.

        std::cout << "InversionsInArray UseBST for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
InversionsInArray Naive for "2, 4, 2, 1, 3, 5": 1, 3, 1, 0, 0, 0
InversionsInArray EnhancedMergeSort for "2, 4, 2, 1, 3, 5": 1, 3, 1, 0, 0, 0
InversionsInArray UsePrefixSums for "1, 3, 1, 0, 2, 4": 1, 3, 1, 0, 0, 0
InversionsInArray UseBinaryIndexedTree for "1, 3, 1, 0, 2, 4": 1, 3, 1, 0, 0, 0
InversionsInArray CountTotal_MergeSort2 for "1, 2, 2, 3, 4, 5": 5
InversionsInArray UseBST for "2, 4, 2, 1, 3, 5": 1, 3, 1, 0, 0, 0
InversionsInArray Naive for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": 9, 14, 13, 12, 8, 10, 9, 8, 4, 6, 5, 4, 0, 2, 1, 0
InversionsInArray EnhancedMergeSort for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": 9, 14, 13, 12, 8, 10, 9, 8, 4, 6, 5, 4, 0, 2, 1, 0
InversionsInArray UsePrefixSums for "9, 15, 14, 13, 8, 12, 11, 10, 4, 7, 6, 5, 0, 3, 2, 1": 9, 14, 13, 12, 8, 10, 9, 8, 4, 6, 5, 4, 0, 2, 1, 0
InversionsInArray UseBinaryIndexedTree for "9, 15, 14, 13, 8, 12, 11, 10, 4, 7, 6, 5, 0, 3, 2, 1": 9, 14, 13, 12, 8, 10, 9, 8, 4, 6, 5, 4, 0, 2, 1, 0
InversionsInArray CountTotal_MergeSort2 for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16": 105
InversionsInArray UseBST for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": 9, 14, 13, 12, 8, 10, 9, 8, 4, 6, 5, 4, 0, 2, 1, 0
InversionsInArray Naive for "6, 3, 6, 5, 2, 4": 4, 1, 3, 2, 0, 0
InversionsInArray EnhancedMergeSort for "6, 3, 6, 5, 2, 4": 4, 1, 3, 2, 0, 0
InversionsInArray UsePrefixSums for "4, 1, 4, 3, 0, 2": 4, 1, 3, 2, 0, 0
InversionsInArray UseBinaryIndexedTree for "4, 1, 4, 3, 0, 2": 4, 1, 3, 2, 0, 0
InversionsInArray CountTotal_MergeSort2 for "2, 3, 4, 5, 6, 6": 10
InversionsInArray UseBST for "6, 3, 6, 5, 2, 4": 4, 1, 3, 2, 0, 0
InversionsInArray Naive for "6, 3, 0, 4, 2, 5, 1": 6, 3, 0, 2, 1, 1, 0
InversionsInArray EnhancedMergeSort for "6, 3, 0, 4, 2, 5, 1": 6, 3, 0, 2, 1, 1, 0
InversionsInArray UsePrefixSums for "6, 3, 0, 4, 2, 5, 1": 6, 3, 0, 2, 1, 1, 0
InversionsInArray UseBinaryIndexedTree for "6, 3, 0, 4, 2, 5, 1": 6, 3, 0, 2, 1, 1, 0
InversionsInArray CountTotal_MergeSort2 for "0, 1, 2, 3, 4, 5, 6": 13
InversionsInArray UseBST for "6, 3, 0, 4, 2, 5, 1": 6, 3, 0, 2, 1, 1, 0
InversionsInArray Naive for "5, 3, 0, 4, 2, 5, 1": 5, 3, 0, 2, 1, 1, 0
InversionsInArray EnhancedMergeSort for "5, 3, 0, 4, 2, 5, 1": 5, 3, 0, 2, 1, 1, 0
InversionsInArray UsePrefixSums for "5, 3, 0, 4, 2, 5, 1": 5, 3, 0, 2, 1, 1, 0
InversionsInArray UseBinaryIndexedTree for "5, 3, 0, 4, 2, 5, 1": 5, 3, 0, 2, 1, 1, 0
InversionsInArray CountTotal_MergeSort2 for "0, 1, 2, 3, 4, 5, 5": 12
InversionsInArray UseBST for "5, 3, 0, 4, 2, 5, 1": 5, 3, 0, 2, 1, 1, 0
*/
/*
variant:
Runners numbered from 0 to n-1 race on a straight one-way road to a common finish line.
The runners have difference (constant) speeds and start at different distances from the finish line.
Specially, Runner i has a speed Si and begins at a distance Di from the finish line.
Each runner stops at the finish line, and the race ends when all runners have reached the finish line.
How many times does one runner pass another?

The time for each runner to reach the finish line would be Di/Si.
Sort the runners by the starting distance to the finish line, i.e., the shortest in the left, and the longest in the right.
Based the sorted order, count the inversions of time for each runner to reach the finish line.
(an inversion of time is a longer time on the left side of a shorter time)

O(nlogn) time, O(n) space

variant:
Count number of line intersections
0    1    2
  \   \  /
   \   X
    X   \
  /  \   \
2    0    1


0    1    2
|     \  /
|      \/
|      /\
|     /  \
0    2    1
*/
#endif