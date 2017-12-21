#ifndef REMOVE_BOXES_H
#define REMOVE_BOXES_H
#include "Debug.h"
/*
Leetcode: Remove Boxes
Given several boxes with different colors represented by different positive numbers.
You may experience several rounds to remove boxes until there is no box left.
Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.
Example 1:
Input:
[1, 3, 2, 2, 2, 3, 4, 3, 1]
Output:
23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
----> [1, 3, 3, 3, 1] (1*1=1 points)
----> [1, 1] (3*3=9 points)
----> [] (2*2=4 points)
Note: The number of boxes n would not exceed 100.
*/
class RemoveBoxes
{
public:
	RemoveBoxes() {}

	int Recur(std::vector<int> & boxes)
	{
		int res = recur(boxes);
		std::cout << "RemoveBoxes Recur for \"" << Debug::ToStr1D<int>()(boxes) << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(std::vector<int> boxes)
	{
		int N = boxes.size();
		if (N == 0) return 0;

		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			int j = i + 1;
			while (j < N && boxes[j] == boxes[i])
				++j;
			//now remove boxes[i:j-1]
			std::vector<int> nxt;
			for (int k = 0; k < i; ++k)
				nxt.push_back(boxes[k]);
			for (int k = j; k < N; ++k)
				nxt.push_back(boxes[k]);
			res = std::max(res, recur(nxt) + (j - i)*(j - i));
		}
		return res;
	}

public:
	int RecurDP3D(std::vector<int> & boxes)
	{
		int N = boxes.size();
		std::vector<std::vector<std::vector<int>>> dp(N, std::vector<std::vector<int>>(N, std::vector<int>(N, 0)));
		int res = recur(boxes, 0, N - 1, 0, dp);
		std::cout << "RemoveBoxes RecurDP3D for \"" << Debug::ToStr1D<int>()(boxes) << "\": " << res << std::endl;
		return res;
	}
private:
	//rSame: count of same boxes[right] on the right side of boxes[right] which doesn't include boxes[right]
	int recur(std::vector<int> & boxes, int left, int right, int rSame, std::vector<std::vector<std::vector<int>>> & dp)
	{
		if (left > right) return 0;
		if (dp[left][right][rSame] != 0) return dp[left][right][rSame];
		int r = right;
		while (left <= r && boxes[r] == boxes[right])
		{
			--r;
			++rSame;
		}
		++r;
		--rSame;
		//now r points to the leftmost num from right that == boxes[right], and rSame doesn't includes boxes[r]
		//1. try remove boxes[left:r-1] and group boxes[r:r+rSame]
		dp[left][r][rSame] = recur(boxes, left, r - 1, 0, dp) + (rSame + 1)*(rSame + 1);

		for (int mid = left; mid < r; ++mid)
		{
			//2. try remove boxes[mid+1:r-1] to group boxes[mid] with boxes[r]
			if (boxes[mid] == boxes[r])
				dp[left][r][rSame] = std::max(dp[left][r][rSame],
					recur(boxes, left, mid, rSame + 1, dp) + recur(boxes, mid + 1, r - 1, 0, dp));
		}
		return dp[left][r][rSame];
	}
};
/*
RemoveBoxes Recur for "1, 3, 2, 2, 2, 3, 4, 3, 1": 23
RemoveBoxes RecurDP3D for "1, 3, 2, 2, 2, 3, 4, 3, 1": 23
*/
#endif
