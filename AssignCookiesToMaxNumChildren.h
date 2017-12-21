#ifndef ASSIGN_COOKIES_TO_MAX_NUM_CHILDREN_H
#define ASSIGN_COOKIES_TO_MAX_NUM_CHILDREN_H
#include "Debug.h"
/*
Leetcode: Assign Cookies
Assume you are an awesome parent and want to give your children some cookies.
But, you should give each child at most one cookie.
Each child i has a greed factor gi, which is the minimum size of a cookie that the child will be content with; and each cookie j has a size sj.
If sj >= gi, we can assign the cookie j to the child i, and the child i will be content.
Your goal is to maximize the number of your content children and output the maximum number.
Note:
You may assume the greed factor is always positive.
You cannot assign more than one cookie to one child.
Example 1:
Input: [1,2,3], [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
Example 2:
Input: [1,2], [1,2,3]
Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
You have 3 cookies and their sizes are big enough to gratify all of the children,
You need to output 2.

*/
class AssignCookiesToMaxNumChildren
{
public:
	AssignCookiesToMaxNumChildren() {}

	int SortAndGreedy(std::vector<int> & g, std::vector<int> & s)
	{
		std::sort(g.begin(), g.end());
		std::sort(s.begin(), s.end());
		int N = g.size();
		int M = s.size();
		int i = 0;
		int j = 0;
		for (; i < N && j < M; ++j)
			if (g[i] <= s[j])
				++i;

		std::cout << "AssignCookiesToMaxNumChildren SortAndGreedy for \"" << Debug::ToStr1D<int>()(g) << "\", \"" << Debug::ToStr1D<int>()(s) << "\": " << i << std::endl;
		return i;
	}
};
/*
AssignCookiesToMaxNumChildren SortAndGreedy for "1, 2, 3", "1, 1": 1
AssignCookiesToMaxNumChildren SortAndGreedy for "1, 2", "1, 2, 3": 2
*/
#endif
