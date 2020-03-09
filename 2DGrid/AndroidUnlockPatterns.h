#ifndef ANDROID_UNLOCK_PATTERNS_H
#define ANDROID_UNLOCK_PATTERNS_H
#include "Debug.h"
/*
Leetcode: Android Unlock Patterns
Given Android 9 key lock screen and numbers m and n, where 1 <= m <= n <= 9.
Count the total number of patterns of Android lock screen, which consist of minimum of m keys and maximum n keys.
Rules for valid pattern:

1. Each pattern must connect at least m keys and at most n keys.
2. All the keys must be distinct.
3. If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must have previously selected in the pattern.
No jumps through non selected key is allowed.
4. The order of keys used matters.

Example:

| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
Valid move : 6 - 5 - 4 - 1 - 9 - 2
Line 1 - 9 is valid because it pass through key 5, which has been already selected in the pattern.

Valid move : 2 - 4 - 1 - 3 - 6
Line 1 - 3 is valid because it pass through key 2, which has been already selected in the pattern.

Invalid move : 4 - 1 - 3 - 6
Line 1 - 3 pass through key 2 which is not still selected in the pattern.

Invalid move : 4 - 1 - 9 - 2
Line 1 - 9 pass through key 5 which is not still selected in the pattern.

Example:
Given m = 1, n = 1, return 9.
*/
class AndroidUnlockPatterns
{
public:
	AndroidUnlockPatterns() {}
	~AndroidUnlockPatterns() {}

	int CountNumPatterns(int m, int n)
	{
		std::vector<std::vector<int>> jumps(10, std::vector<int>(10, -1));
		jumps[1][3] = jumps[3][1] = 2;
		jumps[4][6] = jumps[6][4] = 5;
		jumps[7][9] = jumps[9][7] = 8;
		jumps[1][7] = jumps[7][1] = 4;
		jumps[2][8] = jumps[8][2] = 5;
		jumps[3][9] = jumps[9][3] = 6;
		jumps[1][9] = jumps[9][1] = jumps[7][3] = jumps[3][7] = 5;
		std::vector<int> visit(10, 0);
		int count = 0;
		for (int len = m; len <= n; ++len)
		{
			count += this->recur(1, 1, len, jumps, visit) * 4;
			count += this->recur(2, 1, len, jumps, visit) * 4;
			count += this->recur(5, 1, len, jumps, visit);
		}

		std::cout << "AndroidUnlockPatterns CountNumPatterns for \"" << m << "\", \"" << n << "\": " << count << std::endl;
		return count;
	}
	int recur(int curNum, int curLen, int tgtLen, const std::vector<std::vector<int>> & jumps, std::vector<int> & visit)
	{
		if (curLen > tgtLen) return 0;
		if (curLen == tgtLen) return 1; // 1 solution

		visit[curNum] = 1;
		int count = 0;
		for (int i = 1; i <= 9; ++i)
		{
			if (!visit[i])
			{
				int jump = jumps[curNum][i];
				if (jump == -1 || visit[jump])
					count += this->recur(i, curLen + 1, tgtLen, jumps, visit);
			}
		}
		visit[curNum] = 0;
		return count;
	}
};
/*
AndroidUnlockPatterns CountNumPatterns for "1", "1": 9
AndroidUnlockPatterns CountNumPatterns for "2", "2": 56
AndroidUnlockPatterns CountNumPatterns for "2", "3": 376
AndroidUnlockPatterns CountNumPatterns for "3", "3": 320
AndroidUnlockPatterns CountNumPatterns for "4", "4": 1624
AndroidUnlockPatterns CountNumPatterns for "3", "4": 1944
*/
#endif
