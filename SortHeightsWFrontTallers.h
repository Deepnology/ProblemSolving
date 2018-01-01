/*MUST*/
#ifndef SORT_HEIGHTS_W_FRONT_TALLERS_H
#define SORT_HEIGHTS_W_FRONT_TALLERS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Leetcode: Queue Reconstruction By Height
Suppose you have a random list of people standing in a queue.
Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h.
Write an algorithm to reconstruct the queue.
Note:
The number of people is less than 1,100.
Example
Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

sort:	  4321
		  0011
insert 4: 4
		  0
insert 3: 34
		  00
insert 2: 324
		  010
insert 1: 3124
		  0110

sort:	  776554
		  011024
insert 7: 7
		  0
insert 7: 77
		  01
insert 6: 767
		  011
insert 5: 5767
		  0011
insert 5: 57567
		  00211
insert 4: 575647
		  002141
*/
class SortHeightsWFrontTallers
{
public:
	SortHeightsWFrontTallers(){}
	~SortHeightsWFrontTallers(){}

	std::vector<std::pair<int,int>> Sort_Insert(std::vector<std::pair<int,int>> && heightsWCounts)
	{
		int N = heightsWCounts.size();

		/*1. sort the heightsWCounts array with heights in descending order O(nlogn) time*/
		std::sort(heightsWCounts.begin(), heightsWCounts.end(),
			[](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool { return a.first == b.first ? a.second < b.second : a.first > b.first; });

		/*2. */
		std::vector<std::pair<int, int>> res;
		for (int i = 0; i < N; ++i)
		{
			res.insert(res.begin() + heightsWCounts[i].second, heightsWCounts[i]);
			std::cout << Debug::ToStr1D<int>()(res) << std::endl;
		}
		std::cout << "SortHeightsWFrontTallers Sort_Insert for \"" << Debug::ToStr1D<int>()(heightsWCounts) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}


	struct RopeNode
	{
		RopeNode(int val, int frontTaller) : val(val), val2(frontTaller), left(NULL), right(NULL), leftCountPlus1(frontTaller) {}
		int val;
		int val2;
		RopeNode * left;
		RopeNode * right;
		int leftCountPlus1;
	};
	std::vector<std::pair<int,int>> Sort_RopeInsertion_Inorder(std::vector<std::pair<int,int>> && heightsWCounts)
	{
		int N = heightsWCounts.size();
		
		/*1. sort the heightsWCounts array with heights in decending order O(nlogn) time*/
		std::sort(heightsWCounts.begin(), heightsWCounts.end(),
			[](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool { return a.first == b.first ? a.second < b.second : a.first > b.first; });

		/*
		2. insert each pair into a rope data structure
		newNode->val = height
		newNode->leftCountPlus1 = tallerCount

		insertion stops as a leaf node: newNode->leftCountPlus1 = 1
		newNode->leftCountPlus1 < branchNode->leftCountPlus1: go left, branchNode->leftCountPlus1 += 1
		newNode->leftCountPlus1 >= branchNode->leftCountPlus1: go right, newNode->leftCountPlus1 -= branchNode->leftCountPlus1
		ex: 4321
		    0011
		insert (4,0):               insert (3,0):                  insert (2,1):                    insert (1,1):
							1                           2                              3                                 4
							4                           4                              4                                 4
						   / \                         / \                            / \                               / \
						  N   N                       1   N                          1   N                             1   N
						                              3                              3                                 3
													 / \                            / \                               / \
													N   N                          N   1                             N   2
													                                   2                                 2
																					  / \                               / \
																					 N   N                             1   N
																					                                   1
																													  / \
																													 N   N
		*/
		RopeNode * root = new RopeNode(heightsWCounts[0].first, heightsWCounts[0].second);
		root->leftCountPlus1 = 1;//root now is a leaf node

		//debug print
		{
			std::ostringstream oss;
			PrintBinaryTree<RopeNode, std::ostringstream>(root, oss);
			std::cout << oss.str() << std::endl;
		}

		for (int i = 1; i < N; ++i)
		{
			RopeNode * curNode = root;
			RopeNode * newNode = new RopeNode(heightsWCounts[i].first, heightsWCounts[i].second);

			while (true)
			{
				if (newNode->leftCountPlus1 < curNode->leftCountPlus1)//curNode is too big: go left
				{
					curNode->leftCountPlus1 += 1;
					if (curNode->left != nullptr)
						curNode = curNode->left;
					else
					{
						curNode->left = newNode;
						newNode->leftCountPlus1 = 1;
						break;
					}
				}
				else//curNode is too small: go right
				{
					newNode->leftCountPlus1 -= curNode->leftCountPlus1;
					if (curNode->right != nullptr)
						curNode = curNode->right;
					else
					{
						curNode->right = newNode;
						newNode->leftCountPlus1 = 1;
						break;
					}
				}
			}

			//debug print
			{
				std::ostringstream oss;
				PrintBinaryTree<RopeNode, std::ostringstream>(root, oss);
				std::cout << oss.str() << std::endl;
			}
		}

		/*3. perform iterative inorder traversal*/
		RopeNode * curNode = root;
		std::vector<std::pair<int,int>> res;
		std::stack<RopeNode *> stk;
		for (; curNode != NULL; curNode = curNode->left)
			stk.push(curNode);
		//now stk has all the nodes in the leftmost node path (straight left) (straight left path might not go to the leaf node)

		while (!stk.empty())
		{
			curNode = stk.top();
			stk.pop();
			res.push_back({ curNode->val,curNode->val2 });//in-order: visit the node

			//push all the nodes in the leftmost node path (straight left) of the right subtree to stk (straight left path might not go to the leaf node)
			for (curNode = curNode->right; curNode != NULL; curNode = curNode->left)
				stk.push(curNode);//RSubLmost path
		}
		this->DeleteTree(root);

		std::cout << "SortHeightsWFrontTallers Sort_RopeInsertion_Inorder for \"" << Debug::ToStr1D<int>()(heightsWCounts) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void DeleteTree(RopeNode * root)
	{
		if (root == 0)
			return;

		DeleteTree(root->left);
		DeleteTree(root->right);

		//post order
		delete root;
		root = 0;
	}
};

template<>
std::string PrintBinaryTree<SortHeightsWFrontTallers::RopeNode, std::ostringstream>::selectVal2(int depth, SortHeightsWFrontTallers::RopeNode * n)
{
	return std::to_string(n->leftCountPlus1);
}
/*

 1
 7


  
   1
   7
 /   \
 X   1
 N   7


      
       1
    __ 7__
   /       \
   X       2
   N       7
 /   \   /   \
 X   X   1   X
 N   N   6   N


      
       2
    __ 7__
   /       \
   1       2
   5       7
 /   \   /   \
 X   X   1   X
 N   N   6   N


              
               2
        ______ 7______
       /               \
       1               3
    __ 5__          __ 7__
   /       \       /       \
   X       X       2       X
   N       N       6       N
 /   \   /   \   /   \   /   \
 X   X   X   X   1   X   X   X
 N   N   N   N   5   N   N   N


              
               2
        ______ 7______
       /               \
       1               4
    __ 5__          __ 7__
   /       \       /       \
   X       X       2       X
   N       N       6       N
 /   \   /   \   /   \   /   \
 X   X   X   X   1   1   X   X
 N   N   N   N   5   4   N   N


SortHeightsWFrontTallers Sort_RopeInsertion_Inorder for "[7,0], [7,1], [6,1], [5,0], [5,2], [4,4]": [5,0], [7,0], [5,2], [6,1], [4,4], [7,1]
[7,0]
[7,0], [7,1]
[7,0], [6,1], [7,1]
[5,0], [7,0], [6,1], [7,1]
[5,0], [7,0], [5,2], [6,1], [7,1]
[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]
SortHeightsWFrontTallers Sort_Insert for "[7,0], [7,1], [6,1], [5,0], [5,2], [4,4]": [5,0], [7,0], [5,2], [6,1], [4,4], [7,1]

 1
 4


  
   2
   4
 /   \
 1   X
 3   N


      
       3
    __ 4__
   /       \
   1       X
   3       N
 /   \   /   \
 X   1   X   X
 N   2   N   N


              
               4
        ______ 4______
       /               \
       1               X
    __ 3__          __ N__
   /       \       /       \
   X       2       X       X
   N       2       N       N
 /   \   /   \   /   \   /   \
 X   X   1   X   X   X   X   X
 N   N   1   N   N   N   N   N


SortHeightsWFrontTallers Sort_RopeInsertion_Inorder for "[4,0], [3,0], [2,1], [1,1]": [3,0], [1,1], [2,1], [4,0]
[4,0]
[3,0], [4,0]
[3,0], [2,1], [4,0]
[3,0], [1,1], [2,1], [4,0]
SortHeightsWFrontTallers Sort_Insert for "[4,0], [3,0], [2,1], [1,1]": [3,0], [1,1], [2,1], [4,0]
*/
#endif