#ifndef GENERIC_DFS_W_STACK_H
#define GENERIC_DFS_W_STACK_H
#include "Debug.h"
/*
Leetcode: N-ary Tree Preorder Traversal
Leetcode: N-ary Tree Postorder Traversal
Leetcode: N-ary Tree Levelorder Traversal
*/
class GenericDFSWStack
{
public:
	struct TreeNode
	{
		int val;
		std::vector<TreeNode *> children;
		explicit TreeNode(int v) : val(v) {}
		~TreeNode() {}
	};
	GenericDFSWStack() {}
	~GenericDFSWStack() {}

	//Approach 1: use stack
	std::vector<int> PreorderStack(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		if (root)
			stk.push(root);
		while (!stk.empty())
		{
			TreeNode * cur = stk.top();
			stk.pop();
			std::cout << cur->val << ",";
			int N = cur->children.size();
			for (int i = N-1; i >= 0; --i)
				stk.push(cur->children[i]);
			std::cout << "[" << ToStr1D(stk) << "]," << cur->val << std::endl;
			res.push_back(cur->val);
		}
		std::cout << "GenericDFSWStack PreorderS: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<int> PostorderStack(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		if (root)
			stk.push(root);
		while (!stk.empty())
		{
			TreeNode * cur = stk.top();
			stk.pop();
			int N = cur->children.size();
			for (int i = 0; i < N; ++i)
				stk.push(cur->children[i]);
			res.push_back(cur->val);
		}
		std::reverse(res.begin(), res.end());
		std::cout << "GenericDFSWStack PostorderS: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//Approach 2: use stack and unordered_set
	std::vector<int> PreorderStackHashMap(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		std::unordered_set<TreeNode *> visit;
		if (root)
			stk.push(root), visit.insert(root);
		while (!stk.empty())
		{
			std::cout << stk.top()->val << ",";
			//push all nodes in the rightmost child path to stk
			TreeNode * chd;
			while ((chd = GetNextNonVisitedChild(stk.top(), visit, false)) != nullptr)//Children: Right to Left
			{
				stk.push(chd);
				visit.insert(chd);
			}
			std::cout << "[" << ToStr1D(stk) << "]," << stk.top()->val << std::endl;
			//now visit cur node in reversed preorder
			TreeNode * cur = stk.top();
			stk.pop();
			res.push_back(cur->val);
		}
		std::reverse(res.begin(), res.end());
		std::cout << "GenericDFSWStack PreorderSH: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<int> PostorderStackHashMap(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		std::unordered_set<TreeNode *> visit;
		if (root)
			stk.push(root), visit.insert(root);
		while (!stk.empty())
		{
			//push all nodes in the leftmost child path to stk
			TreeNode * chd;
			while ((chd = GetNextNonVisitedChild(stk.top(), visit, true)) != nullptr)//Children: Left to Right
			{
				stk.push(chd);
				visit.insert(chd);
			}
			//now visit cur node in postorder
			TreeNode * cur = stk.top();
			stk.pop();
			res.push_back(cur->val);
		}
		std::cout << "GenericDFSWStack PostorderSH: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	TreeNode * GetNextNonVisitedChild(TreeNode * cur, std::unordered_set<TreeNode *> & visit, bool LToR)
	{
		if (LToR)
		{
			for (auto itr = cur->children.cbegin(); itr != cur->children.cend(); ++itr)
			{
				if (visit.count(*itr) == 0)
					return *itr;
			}
		}
		else
		{
			for (auto itr = cur->children.crbegin(); itr != cur->children.crend(); ++itr)
			{
				if (visit.count(*itr) == 0)
					return *itr;
			}
		}
		return nullptr;
	}

public:
	//Approach 3: recursion
	std::vector<int> PreorderRecur(TreeNode * root)
	{
		std::vector<int> res;
		recurPre(root, res);
		std::cout << "GenericDFSWStack PreorderR: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	void recurPre(TreeNode * cur, std::vector<int> & res)
	{
		if (cur == NULL) return;
		res.push_back(cur->val);
		int N = cur->children.size();
		for (int i = 0; i < N; ++i)
			recurPre(cur->children[i], res);
	}

	std::vector<int> PostorderRecur(TreeNode * root)
	{
		std::vector<int> res;
		recurPost(root, res);
		std::cout << "GenericDFSWStack PostorderR: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	void recurPost(TreeNode * cur, std::vector<int> & res)
	{
		if (cur == NULL) return;
		int N = cur->children.size();
		for (int i = 0; i < N; ++i)
			recurPost(cur->children[i], res);
		res.push_back(cur->val);
	}


    std::vector<std::vector<int>> LevelOrder(TreeNode * root)
    {
        std::vector<std::vector<int>> res;
        std::queue<TreeNode*> que;
        if (root)
        {
            que.push(root);
            res.push_back(std::vector<int>());
        }
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-- > 0)
            {
                TreeNode * cur = que.front();
                que.pop();
                res.back().push_back(cur->val);
                for (auto nxt : cur->children)
                    que.push(nxt);
            }
            if (!que.empty())
                res.push_back(std::vector<int>());
        }
        return res;
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

	std::string ToStr1D(const std::stack<GenericDFSWStack::TreeNode *> &s, bool topToBottom = false)
	{
		std::stack<GenericDFSWStack::TreeNode *> copy(s);
		if (!topToBottom)
		{
			std::stack<GenericDFSWStack::TreeNode *> rev;
			while (!copy.empty())
				rev.push(copy.top()), copy.pop();
			rev.swap(copy);
		}
		std::ostringstream oss;
		while (!copy.empty())
		{
			oss << copy.top()->val;
			copy.pop();
			if (!copy.empty())
				oss << ", ";
		}
		return oss.str();
	}
};
/*
     _______0________
    /       |        \
  _1_      _5_      __9__
 / | \    / | \    /  |  \
2  3  4  6  7  8  10  11  12

GenericDFSWStack PreorderS: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
GenericDFSWStack PreorderSH: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
GenericDFSWStack PreorderR: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
GenericDFSWStack PostorderS: 2, 3, 4, 1, 6, 7, 8, 5, 10, 11, 12, 9, 0
GenericDFSWStack PostorderSH: 2, 3, 4, 1, 6, 7, 8, 5, 10, 11, 12, 9, 0
GenericDFSWStack PostorderR: 2, 3, 4, 1, 6, 7, 8, 5, 10, 11, 12, 9, 0

					    _________________________0_____________________________
				       /                |                  |                   \
				  ____1____         ____5____          ____9_____           ____13____
				 /    |    \       /    |    \        /    |     \         /    |     \
				2     3    _4_    6   __7__   8   __10_   _11    _12_    14    _15    _16____
			   / \    |   / | \   |  /  |  \  |  /  |  \ /   \  /  | \  /  \  /   \  /  |  | \
			  17 18  19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43

GenericDFSWStack PreorderS: 0, 1, 2, 17, 18, 3, 19, 4, 20, 21, 22, 5, 6, 23, 7, 24, 25, 26, 8, 27, 9, 10, 28, 29, 30, 11, 31, 32, 12, 33, 34, 35, 13, 14, 36, 37, 15, 38, 39, 16, 40, 41, 42, 43
GenericDFSWStack PreorderSH: 0, 1, 2, 17, 18, 3, 19, 4, 20, 21, 22, 5, 6, 23, 7, 24, 25, 26, 8, 27, 9, 10, 28, 29, 30, 11, 31, 32, 12, 33, 34, 35, 13, 14, 36, 37, 15, 38, 39, 16, 40, 41, 42, 43
GenericDFSWStack PreorderR: 0, 1, 2, 17, 18, 3, 19, 4, 20, 21, 22, 5, 6, 23, 7, 24, 25, 26, 8, 27, 9, 10, 28, 29, 30, 11, 31, 32, 12, 33, 34, 35, 13, 14, 36, 37, 15, 38, 39, 16, 40, 41, 42, 43
GenericDFSWStack PostorderS: 17, 18, 2, 19, 3, 20, 21, 22, 4, 1, 23, 6, 24, 25, 26, 7, 27, 8, 5, 28, 29, 30, 10, 31, 32, 11, 33, 34, 35, 12, 9, 36, 37, 14, 38, 39, 15, 40, 41, 42, 43, 16, 13, 0
GenericDFSWStack PostorderSH: 17, 18, 2, 19, 3, 20, 21, 22, 4, 1, 23, 6, 24, 25, 26, 7, 27, 8, 5, 28, 29, 30, 10, 31, 32, 11, 33, 34, 35, 12, 9, 36, 37, 14, 38, 39, 15, 40, 41, 42, 43, 16, 13, 0
GenericDFSWStack PostorderR: 17, 18, 2, 19, 3, 20, 21, 22, 4, 1, 23, 6, 24, 25, 26, 7, 27, 8, 5, 28, 29, 30, 10, 31, 32, 11, 33, 34, 35, 12, 9, 36, 37, 14, 38, 39, 15, 40, 41, 42, 43, 16, 13, 0
*/

/*
0,[9, 5, 1],0
1,[9, 5, 4, 3, 2],1
2,[9, 5, 4, 3],2
3,[9, 5, 4],3
4,[9, 5],4
5,[9, 8, 7, 6],5
6,[9, 8, 7],6
7,[9, 8],7
8,[9],8
9,[12, 11, 10],9
10,[12, 11],10
11,[12],11
12,[],12
GenericDFSWStack PreorderS: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
0,[0, 9, 12],12
9,[0, 9, 11],11
9,[0, 9, 10],10
9,[0, 9],9
0,[0, 5, 8],8
5,[0, 5, 7],7
5,[0, 5, 6],6
5,[0, 5],5
0,[0, 1, 4],4
1,[0, 1, 3],3
1,[0, 1, 2],2
1,[0, 1],1
0,[0],0
GenericDFSWStack PreorderSH: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12

0,[13, 9, 5, 1],0
1,[13, 9, 5, 4, 3, 2],1
2,[13, 9, 5, 4, 3, 18, 17],2
17,[13, 9, 5, 4, 3, 18],17
18,[13, 9, 5, 4, 3],18
3,[13, 9, 5, 4, 19],3
19,[13, 9, 5, 4],19
4,[13, 9, 5, 22, 21, 20],4
20,[13, 9, 5, 22, 21],20
21,[13, 9, 5, 22],21
22,[13, 9, 5],22
5,[13, 9, 8, 7, 6],5
6,[13, 9, 8, 7, 23],6
23,[13, 9, 8, 7],23
7,[13, 9, 8, 26, 25, 24],7
24,[13, 9, 8, 26, 25],24
25,[13, 9, 8, 26],25
26,[13, 9, 8],26
8,[13, 9, 27],8
27,[13, 9],27
9,[13, 12, 11, 10],9
10,[13, 12, 11, 30, 29, 28],10
28,[13, 12, 11, 30, 29],28
29,[13, 12, 11, 30],29
30,[13, 12, 11],30
11,[13, 12, 32, 31],11
31,[13, 12, 32],31
32,[13, 12],32
12,[13, 35, 34, 33],12
33,[13, 35, 34],33
34,[13, 35],34
35,[13],35
13,[16, 15, 14],13
14,[16, 15, 37, 36],14
36,[16, 15, 37],36
37,[16, 15],37
15,[16, 39, 38],15
38,[16, 39],38
39,[16],39
16,[43, 42, 41, 40],16
40,[43, 42, 41],40
41,[43, 42],41
42,[43],42
43,[],43
GenericDFSWStack PreorderS: 0, 1, 2, 17, 18, 3, 19, 4, 20, 21, 22, 5, 6, 23, 7, 24, 25, 26, 8, 27, 9, 10, 28, 29, 30, 11, 31, 32, 12, 33, 34, 35, 13, 14, 36, 37, 15, 38, 39, 16, 40, 41, 42, 43
0,[0, 13, 16, 43],43
16,[0, 13, 16, 42],42
16,[0, 13, 16, 41],41
16,[0, 13, 16, 40],40
16,[0, 13, 16],16
13,[0, 13, 15, 39],39
15,[0, 13, 15, 38],38
15,[0, 13, 15],15
13,[0, 13, 14, 37],37
14,[0, 13, 14, 36],36
14,[0, 13, 14],14
13,[0, 13],13
0,[0, 9, 12, 35],35
12,[0, 9, 12, 34],34
12,[0, 9, 12, 33],33
12,[0, 9, 12],12
9,[0, 9, 11, 32],32
11,[0, 9, 11, 31],31
11,[0, 9, 11],11
9,[0, 9, 10, 30],30
10,[0, 9, 10, 29],29
10,[0, 9, 10, 28],28
10,[0, 9, 10],10
9,[0, 9],9
0,[0, 5, 8, 27],27
8,[0, 5, 8],8
5,[0, 5, 7, 26],26
7,[0, 5, 7, 25],25
7,[0, 5, 7, 24],24
7,[0, 5, 7],7
5,[0, 5, 6, 23],23
6,[0, 5, 6],6
5,[0, 5],5
0,[0, 1, 4, 22],22
4,[0, 1, 4, 21],21
4,[0, 1, 4, 20],20
4,[0, 1, 4],4
1,[0, 1, 3, 19],19
3,[0, 1, 3],3
1,[0, 1, 2, 18],18
2,[0, 1, 2, 17],17
2,[0, 1, 2],2
1,[0, 1],1
0,[0],0
GenericDFSWStack PreorderSH: 0, 1, 2, 17, 18, 3, 19, 4, 20, 21, 22, 5, 6, 23, 7, 24, 25, 26, 8, 27, 9, 10, 28, 29, 30, 11, 31, 32, 12, 33, 34, 35, 13, 14, 36, 37, 15, 38, 39, 16, 40, 41, 42, 43
 */
#endif
