#ifndef ORTHOGONAL_RECTANGLE_INTERSECTION_H
#define ORTHOGONAL_RECTANGLE_INTERSECTION_H
#include "Debug.h"
/*
http://algs4.cs.princeton.edu/93intersection/IntervalST.java.html
http://algs4.cs.princeton.edu/93intersection/VLSI.java.html
https://www.youtube.com/watch?v=3kpmHEJXrsA
https://www.youtube.com/watch?v=iwN32lgiFCU

sweep line algorithm:
2D line segment intersection->1D range search->BST
2D rectangle intersection->1D interval search->interval search tree

just drafted the algorithm, not tested yet (wait for leetcode)

interval search tree, search any one intersected interval:
|------|
4      8
  |----|
  5    8
     |------|
	 7     10
	               |------|
				   15     18
				     |---------------|
					 16             22
					   |-----|
					   17    19
					               |--------|
								   21      24
search:
									   |-------|
                                       23      25
			  |--|
			  12 14
			                       |---|
								   21  23
*/
class OrthogonalRectangleIntersection
{
public:
	OrthogonalRectangleIntersection() {}

	//interval search tree
	struct IntervalNode
	{
		IntervalNode(int _lo = 0, int _hi = 0) : lo(_lo), hi(_hi), maxHi(_hi), left(NULL), right(NULL) {}
		int lo;//loY
		int hi;//hiY
		int maxHi;//max hiY of all interval nodes in this node's subtree
		IntervalNode * left;
		IntervalNode * right;

		int compare(int _lo, int _hi)
		{
			//1. compare lo
			if (lo < _lo) return -1;
			else if (lo > _lo) return +1;
			//2. compare hi
			else if (hi < _hi) return -1;
			else if (hi > _hi) return +1;
			//3. equal
			else return 0;
		}

		//std::vector<int> rect;//[loX,hiX,loY,hiY]
	};
	IntervalNode * Insert(IntervalNode * root, int lo, int hi)
	{
		IntervalNode * node = new IntervalNode(lo, hi);
		if (root == NULL) return node;
		IntervalNode * cur = root;
		while (true)
		{
			cur->maxHi = std::max(cur->maxHi, node->hi);
			if (cur->compare(node->lo, node->hi) > 0)//too big: go left
			{
				if (cur->left)
					cur = cur->left;
				else
				{
					cur->left = node;
					break;
				}
			}
			else//too small or equal: go right
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
	void Remove(IntervalNode * root, int lo, int hi)
	{
		removeRecur(root, lo, hi);
	}
	int removeRecur(IntervalNode *& cur, int lo, int hi)
	{
		if (cur == NULL) return INT_MIN;
		if (cur->compare(lo, hi) > 0)//too big: go left
		{
			int maxHi = removeRecur(cur->left, lo, hi);
			cur->maxHi = std::max(cur->hi, maxHi);
			return cur->maxHi;
		}
		else if (cur->compare(lo, hi) < 0)//too small: go right
		{
			int maxHi = removeRecur(cur->right, lo, hi);
			cur->maxHi = std::max(cur->hi, maxHi);
			return cur->maxHi;
		}
		else//equal
		{
			if (cur->left && cur->right)//two children
			{
				/*found the target node, replace its value with the successor (min of RSubtree (RSubLmost)), then recur down to remove that successor*/
				IntervalNode * RSubLmost = cur->right;
				while (RSubLmost->left)
					RSubLmost = RSubLmost->left;
				cur->lo = RSubLmost->lo;
				cur->hi = RSubLmost->hi;
				int maxHi = removeRecur(cur->right, cur->lo, cur->hi);
				cur->maxHi = std::max(cur->hi, maxHi);
				return cur->maxHi;
			}
			else//1 or 0 child (a node with 1 child or a leaf node)
			{
				IntervalNode * oldNode = cur;
				cur = cur->left != NULL ? cur->left : cur->right;//replace cur with its child, or with nullptr
				delete oldNode;
				oldNode = NULL;
				cur->maxHi = cur->hi;
				return cur->maxHi;
			}
		}
	}
	IntervalNode * Search(IntervalNode * root, int lo, int hi)//returns any one interval that intersects the given interval
	{
		//refer to the video lecture !!!
		IntervalNode * cur = root;
		while (cur)
		{
			if (cur->lo <= hi && lo <= cur->hi)//intersect !!!
			{
				return cur;
			}
			else if (cur->left == NULL)
				cur = cur->right;
			else if (cur->left->maxHi < lo)
				cur = cur->right;
			else
				cur = cur->left;
		}
		return NULL;
	}
	std::vector<IntervalNode *> SearchAll(IntervalNode * root, int lo, int hi)//return all intervals that intersect the given interval
	{
		//refer to the online source code !!!
		std::vector<IntervalNode *> res;
		searchAllRecur(root, lo, hi, res);
		return res;
	}
	bool searchAllRecur(IntervalNode * cur, int lo, int hi, std::vector<IntervalNode *> & res)
	{
		if (cur == NULL) return false;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		if (cur->lo <= hi && lo <= cur->hi)//intersect !!!
		{
			res.push_back(cur);
			found1 = true;
		}
		if (cur->left && cur->left->maxHi >= lo)//condition to search left
			found2 = searchAllRecur(cur->left, lo, hi, res);
		if (found2 || cur->left == NULL || cur->left->maxHi < lo)//condition to search right
			found3 = searchAllRecur(cur->right, lo, hi, res);
		return found1 || found2 || found3;
	}

	struct Greater
	{
		bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
		{
			return a[0] == b[0] ? a[1] && !b[1] : a[0] > b[0];
		}
	};
	void SweepLine(std::vector<std::vector<int>> & rects)//[loX,hiX,loY,hiY]
	{
		int N = rects.size();
		std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;
		for (int i = 0; i < N; ++i)
		{
			minHeap.push({ rects[i][0],0,i });//[loX,0,idx]
			minHeap.push({ rects[i][1],1,i });//[hiX,1,idx]
		}
		IntervalNode * root = nullptr;
		std::vector<std::vector<int>> res(N, std::vector<int>());
		while (!minHeap.empty())//loop thru all loX and hiX in incr order
		{
			auto v = minHeap.top();
			minHeap.pop();
			if (v[1])//hiX
				Remove(root, rects[v[2]][2], rects[v[2]][3]);//remove rects[v[2]]'s intervalY
			else//loX
			{
				//find intervalYs in tree that intersect w/ rects[v[2]]'s intervalY
				std::vector<IntervalNode*> nodes = SearchAll(root, rects[v[2]][2], rects[v[2]][3]);

				for (auto & n : nodes)//record
				{
					res[v[2]].push_back(n->lo);
					res[v[2]].push_back(n->hi);
				}

				root = Insert(root, rects[v[2]][2], rects[v[2]][3]);//insert rects[v[2]]'s intervalY
			}
		}

		Debug::Print2D<int>()(rects, false);
		std::cout << "OrthogonalRectangleIntersection SweepLine for the above rectangles:" << std::endl;
		Debug::Print2D<int>()(res, false);
	}
};
#endif
