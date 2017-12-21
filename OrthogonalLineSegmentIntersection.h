#ifndef ORTHOGONAL_LINE_SEGMENT_INTERSECTION_H
#define ORTHOGONAL_LINE_SEGMENT_INTERSECTION_H
#include "Debug.h"
/*
https://www.youtube.com/watch?v=Igr6yONkpIQ
https://www.youtube.com/watch?v=H87H9iEa9to

1D range search:
data structure     insert    range count    range search
unordered array:     1            N              N
ordered array:       N           logN         R+logN
                  (involves
			   element shifts)
BST:                logN         logN         R+logN

(N=num of keys, R=num of keys that match)

sweep line algorithm:
2D line segment intersection->1D range search->BST
2D rectangle intersection->1D interval search->interval search tree

just drafted the algorithm, not tested yet (wait for leetcode)
*/
class OrthogonalLineSegmentIntersection
{
public:
	OrthogonalLineSegmentIntersection() {}

	struct TreeNode
	{
		TreeNode(const int & val, const int leftCount = 0) : val(val), leftCount(leftCount), left(nullptr), right(nullptr) {}
		~TreeNode() {}
		int val;
		TreeNode * left;
		TreeNode * right;
		int leftCount;/*the node count of left subtree, used to get the rank (sorted order index) of a node in O(logn) time*/
	};
	TreeNode * Insert(TreeNode * root, int val)
	{
		TreeNode * node = new TreeNode(val);
		if (root == NULL) return node;
		TreeNode * cur = root;
		while (true)
		{
			if (cur->val >= node->val)//too big: go left
			{
				++cur->leftCount;
				if (cur->left)
					cur = cur->left;
				else
				{
					cur->left = node;
					break;
				}
			}
			else//too small: go right
			{
				if (cur->right)
					cur = cur->right;
				else
				{
					cur->right = node;
					break;
				}
			}
		}
		return root;
	}
	void Remove(TreeNode * root, int val)
	{
		removeRecur(root, val);
	}
	void removeRecur(TreeNode *& cur, int val)
	{
		if (cur == nullptr)
			return;
		if (cur->val > val)
		{
			removeRecur(cur->left, val);
			--cur->leftCount;
		}
		else if (cur->val < val)
			removeRecur(cur->right, val);
		else
		{
			if (cur->left && cur->right)//two children
			{
				/*found the target node, replace its value with the successor (min of RSubtree (RSubLmost)), then recur down to remove that successor*/
				TreeNode * RSubLmost = cur->right;
				while (RSubLmost->left)
					RSubLmost = RSubLmost->left;
				cur->val = RSubLmost->val;
				removeRecur(cur->right, cur->val);
			}
			else//1 or 0 child (a node with 1 child or a leaf node)
			{
				TreeNode * oldNode = cur;
				cur = cur->left != nullptr ? cur->left : cur->right;//replace n with its child, or with nullptr
				delete oldNode;
				oldNode = nullptr;
			}
		}
	}
	std::pair<TreeNode *, int> Rank(TreeNode * root, int val)//range count = Rank(y2) - Rank(y1) + 1
	{
		return getRankRecur(root, val);
	}
	std::pair<TreeNode *, int> getRankRecur(TreeNode * n, int val)
	{
		if (n == nullptr)
			return{ nullptr, 0 };
		else if (val < n->val)
			return getRankRecur(n->left, val);
		else if (val > n->val)
		{
			auto findRight = getRankRecur(n->right, val);
			return{ findRight.first, n->leftCount + 1 + findRight.second };//node count in left subtree + this node + recur down right subtree
		}
		else
		{
			auto findLeft = this->getRankRecur(n->left, val);//find the leftmost duplicate if possible
			if (findLeft.first != nullptr)
				return findLeft;
			else
				return{ n, n->leftCount };
		}
	}
	std::vector<int> FindRange(TreeNode * root, int lo, int hi)//range search
	{
		std::vector<int> res;
		findRangeRecur(root, lo, hi, res);
		return res;
	}
	void findRangeRecur(TreeNode * curNode, int lower, int upper, std::vector<int> & res)
	{
		if (curNode == nullptr)
			return;
		if (lower <= curNode->val)
			this->findRangeRecur(curNode->left, lower, upper, res);

		//in-order
		if (lower <= curNode->val && curNode->val <= upper)
			res.push_back(curNode->val);

		if (curNode->val <= upper)
			this->findRangeRecur(curNode->right, lower, upper, res);
	}


	struct Greater
	{
		bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
		{
			return a[0] == b[0] ? a[2] > b[2] : a[0] > b[0];
		}
	};
	void SweepLine(std::vector<std::vector<int>> & lines)//[x1,y1,x2,y2]
	{
		int N = lines.size();
		std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;
		for (int i = 0; i < N; ++i)
		{
			if (lines[i][1] == lines[i][3])//horizontal line
			{
				minHeap.push({ lines[i][0],0,i });//[x1,0,idx]
				minHeap.push({ lines[i][2],1,i });//[x2,1,idx]
			}
			else if (lines[i][0] == lines[i][2])//vertical line
			{
				minHeap.push({ lines[i][0],2,i });//[x1,2,idx]
			}
		}
		TreeNode * root = nullptr;
		std::vector<std::vector<int>> res(N, std::vector<int>());
		while (!minHeap.empty())
		{
			auto v = minHeap.top();
			minHeap.pop();
			if (v[1] == 1)//end point of horizontal line
			{
				Remove(root, lines[v[2]][1]);//remove y
			}
			else if (v[1] == 0)//start point of horizontal line
			{
				root = Insert(root, lines[v[2]][1]);//insert y
			}
			else if (v[1] == 2)//vertical line: collect Ys(horizontal lines) from BST in range
			{
				std::vector<int> yInRange = FindRange(root, lines[v[2]][1], lines[v[2]][3]);//find range in [y1:y2]
				for (auto & y : yInRange)
					res[v[2]].push_back(y);
			}
		}

		Debug::Print2D<int>()(lines, false);
		std::cout << "OrthogonalLineSegmentIntersections SweepLine for the above lines:" << std::endl;
		Debug::Print2D<int>()(res, false);
	}
};
#endif
