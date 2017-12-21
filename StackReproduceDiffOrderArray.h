#ifndef STACK_REPRODUCE_DIFF_ORDER_ARRAY_H
#define STACK_REPRODUCE_DIFF_ORDER_ARRAY_H
#include "Debug.h"
/*
Amazon
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=278634&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption[3046][value]%3D5%26searchoption[3046][type]%3Dradio%26sortid%3D311
Given two integer arrays A and B, where all elements in A and B are the same except the order.
The elements are all distinct.
Use a stack to reproduce the elements in array B by pushing or popping elements in array A.

*/
class StackReproduceDiffOrderArray
{
public:
	StackReproduceDiffOrderArray() {}

	bool UseStack(std::vector<int> & A, std::vector<int> & B)
	{
		int N = A.size();
		if (N != B.size()) return false;
		int i = 0;
		int j = 0;
		std::stack<int> stk;
		std::vector<int> res;
		bool res2 = true;
		while (i < N && j < N)
		{
			if (A[i] == B[j])
			{
				stk.push(A[i]);
				res.push_back(stk.top());
				stk.pop();
				++i;
				++j;
			}
			else if (!stk.empty() && stk.top() == B[j])
			{
				res.push_back(stk.top());
				stk.pop();
				++j;
			}
			else
			{
				stk.push(A[i]);
				++i;
			}
		}
		while (!stk.empty())
		{
			if (stk.top() != B[j])
			{
				res2 = false;
				break;
			}
			res.push_back(stk.top());
			stk.pop();
			++j;
		}

		std::cout << "StackReproduceDiffOrderArray for the following 2 arrays: " << res2 << " (" << Debug::ToStr1D<int>()(res) << ")" << std::endl;
		std::cout << "\"" << Debug::ToStr1D<int>()(A) << "\"" << std::endl << "\"" << Debug::ToStr1D<int>()(B) << "\"" << std::endl;
		return res2;
	}
};
/*
StackReproduceDiffOrderArray for the following 2 arrays: 0 (3, 2, 4)
"1, 3, 2, 6, 5, 0, 4"
"3, 2, 4, 1, 6, 0, 5"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (4)
"5, 0, 1, 6, 4, 3, 2"
"4, 0, 2, 5, 6, 3, 1"
StackReproduceDiffOrderArray for the following 2 arrays: 1 (0, 6, 1, 2, 4, 3, 5)
"5, 0, 1, 6, 2, 4, 3"
"0, 6, 1, 2, 4, 3, 5"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (0, 2)
"0, 6, 5, 4, 3, 1, 2"
"0, 2, 6, 4, 1, 3, 5"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (2)
"3, 1, 4, 5, 6, 2, 0"
"2, 5, 4, 3, 1, 0, 6"
StackReproduceDiffOrderArray for the following 2 arrays: 1 (0, 4, 2, 6, 1, 3, 5)
"0, 6, 4, 2, 5, 1, 3"
"0, 4, 2, 6, 1, 3, 5"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (5, 2)
"1, 6, 0, 3, 5, 4, 2"
"5, 2, 3, 0, 1, 4, 6"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (0, 6, 2)
"0, 5, 1, 6, 3, 2, 4"
"0, 6, 2, 1, 5, 3, 4"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (5, 4, 2, 1)
"6, 3, 5, 4, 0, 1, 2"
"5, 4, 2, 1, 3, 6, 0"
StackReproduceDiffOrderArray for the following 2 arrays: 0 (5, 1)
"4, 3, 2, 5, 0, 6, 1"
"5, 1, 0, 3, 6, 4, 2"

*/
#endif
