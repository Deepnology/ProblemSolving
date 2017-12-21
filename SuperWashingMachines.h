#ifndef SUPER_WASHING_MACHINES_H
#define SUPER_WASHING_MACHINES_H
#include "Debug.h"
/*
Leetcode: Super Washing Machines
You have n super washing machines on a line.
Initially, each washing machine has some dresses or is empty.
For each move, you could choose any m (1 <= m <= n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time.
Given an integer array representing the number of dresses in each washing machine from left to right on the line, you should find the minimum number of moves to make all the washing machines have the same number of dresses.
If it is not possible to do it, return -1.
Example1
Input: [1,0,5]
Output: 3
Explanation:
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3
3rd move:    2     1 <-- 3    =>    2     2     2
Example2
Input: [0,3,0]
Output: 2
Explanation:
1st move:    0 <-- 3     0    =>    1     2     0
2nd move:    1     2 --> 0    =>    1     1     1
Example3
Input: [0,2,0]
Output: -1
Explanation:
It's impossible to make all the three washing machines have the same number of dresses.
*/
class SuperWashingMachines
{
public:
	SuperWashingMachines() {}

	int FindMinMoves(std::vector<int> & machines)
	{
		int N = machines.size();
		int sum = std::accumulate(machines.begin(), machines.end(), 0);
		if (sum % N) return -1;//sum cannot be splitted into N machines evenly
		int avg = sum / N;
		std::vector<int> leftSum(N);
		for (int i = 0; i < N; ++i)
			leftSum[i] = machines[i] + (i >= 1 ? leftSum[i - 1] : 0);
		std::vector<int> rightSum(N);
		for (int i = N - 1; i >= 0; --i)
			rightSum[i] = machines[i] + (i < N - 1 ? rightSum[i + 1] : 0);
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			int tgtLeftSum = i * avg;//exclude i
			int tgtRightSum = (N - i - 1) * avg;//exclude i
			int curLeftSum = i - 1 >= 0 ? leftSum[i - 1] : 0;//exclude i
			int curRightSum = i + 1 <= N - 1 ? rightSum[i + 1] : 0;//exclude i
			int toLeft = tgtLeftSum > curLeftSum ? tgtLeftSum - curLeftSum : 0;//total dresses passed to left machines through machine i
			int toRight = tgtRightSum > curRightSum ? tgtRightSum - curRightSum : 0;//total dresses passed to right machines through machine i
			res = std::max(res, toLeft + toRight);//the min moves will be the machine that passes the most extra dresses to other machines till avg
		}

		std::cout << "SuperWashingMachines FindMinMoves for \"" << Debug::ToStr1D<int>()(machines) << "\": " << res << std::endl;
		return res;
	}
};
/*
SuperWashingMachines FindMinMoves for "1, 1, 6, 6, 1": 4
SuperWashingMachines FindMinMoves for "1, 1, 4, 8, 1": 5
*/
#endif
