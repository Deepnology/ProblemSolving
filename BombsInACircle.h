#ifndef BOMBS_IN_A_CIRCLE_H
#define BOMBS_IN_A_CIRCLE_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=5231103736545280
Given N bombs placed in a circle.
Each bomb has a value and a explosion range.
When you detonate a bomb, you can get its value, but the bomb will destroy its neighbors in its explosion range.
Design an algorithm to find the maximun value of bombs.

for example:
value: 1, 3, 1, 1, 1, 1
range: 1, 2, 1, 1, 0, 0
index: 0, 1, 2, 3, 4, 5

If we can only detonate in a fixed order from the first to the last one, the maximum value would be 4.
But if we can detonate in an arbitrary order, the maximum value can be 6.

This problem is a combination of LIS and Permutations.
LIS: include and exclude current element and recurse down
Permutations: fix all previous elements, swap current element with each one from current to the last, and recurse down

*/
class BombsInACircle
{
public:
	BombsInACircle(){}
	~BombsInACircle(){}


	int FixedOrderFromBegin_InPlace_Recur(const std::vector<int> & val, const std::vector<int> & range)
	{
		int N = val.size();
		int max = this->recur(val, range, 0, N - 1);
		std::cout << "BombsInACircle FixedOrderFromBegin_InPlace_Recur for \"" << Debug::ToStr1D<int>()(val) << "\", \"" << Debug::ToStr1D<int>()(range) << "\": " << max << std::endl;
		return max;
	}
private:
	int recur(const std::vector<int> & val, const std::vector<int> & range,
		int fwd, int bwd)//only bombs in between val[fwd]~val[bwd], inclusive, can be denoted
	{
		int N = val.size();
		if (fwd >= N)
			return 0;
		if (fwd > bwd)
			return 0;
		if (fwd == bwd)
			return val[fwd];
		
		int include = this->recur(val, range, fwd + range[fwd] + 1, this->Bkd(bwd, fwd - range[fwd] - 1, N)) + val[fwd];
		int exclude = this->recur(val, range, fwd + 1, bwd);
		return std::max(include, exclude);
	}
private:
	int Bkd(int curBkd, int newBkd, int N)//compute a new bwd when denoting val[fwd] which causes explosions on val[fwd]'s left
	{
		if (newBkd < 0)
		{
			if (newBkd < 0 - N)
				return -1;
			return std::min(curBkd, newBkd + N);
		}
		return curBkd;
	}



public:
	int FixedOrderFromBegin_ExtraSpace_Recur(const std::vector<int> & val, const std::vector<int> & range)
	{
		int N = val.size();
		std::vector<int> detonated(N, 0);
		int res = this->recur(val, range, detonated, 0);
		std::cout << "BombsInACircle FixedOrderFromBegin_ExtraSpace_Recur for \"" << Debug::ToStr1D<int>()(val) << "\", \"" << Debug::ToStr1D<int>()(range) << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(const std::vector<int> & val, const std::vector<int> & range, std::vector<int> & detonated, int cur)
	{
		int N = val.size();
		if (cur == N)
			return 0;
		
		int include = 0;
		if (detonated[cur] == 0)
		{
			std::vector<int> copy(detonated);
			int r = range[cur];
			this->Detonate(copy, cur, r);
			include = this->recur(val, range, copy, cur + 1) + val[cur];
		}
		int exclude = this->recur(val, range, detonated, cur + 1);
		return std::max(include, exclude);
	}







public:
	int ArbitraryOrder_Recur(const std::vector<int> & val, const std::vector<int> & range)
	{
		int N = val.size();
		std::vector<int> permutation(N);
		for (int i = 0; i < N; ++i)
			permutation[i] = i;
		int max = this->permu_recur(val, range, permutation, 0);
		std::cout << "BombsInACircle ArbitraryOrder_Recur for \"" << Debug::ToStr1D<int>()(val) << "\", \"" << Debug::ToStr1D<int>()(range) << "\": " << max << std::endl;
		return max;
	}
private:
	int permu_recur(const std::vector<int> & val, const std::vector<int> & range, std::vector<int> & permutation,
		int curSwap)
	{
		int N = val.size();	
		if (curSwap == N)
		{
			std::vector<int> detonated(N, 0);
			//std::cout << "permutation: " << Debug::ToStr1D<int>()(permutation) << std::endl;
			return this->inexclude_recur(val, range, detonated, permutation, 0);
		}
		int res = INT_MIN;
		for (int i = curSwap; i < N; ++i)
		{	
			std::swap(permutation[i], permutation[curSwap]);
			int cur = this->permu_recur(val, range, permutation, curSwap + 1);
			if (cur > res)
				res = cur;
			std::swap(permutation[i], permutation[curSwap]);
		}
		return res;
	}
	int inexclude_recur(const std::vector<int> & val, const std::vector<int> & range, std::vector<int> & detonated, 
		const std::vector<int> & permutation, int startIdx)
	{
		int N = val.size();
		if (startIdx == N)
			return 0;
		
		int include = 0;
		if (detonated[permutation[startIdx]] == 0)
		{
			std::vector<int> copy(detonated);
			int r = range[permutation[startIdx]];
			this->Detonate(copy, permutation[startIdx], r);
			include = this->inexclude_recur(val, range, copy, permutation, startIdx + 1) + val[permutation[startIdx]];
		}
		int exclude = this->inexclude_recur(val, range, detonated, permutation, startIdx + 1);
		return std::max(include, exclude);
	}
	void Detonate(std::vector<int> & detonated, int i, int range)
	{
		int N = detonated.size();
		detonated[i] = 1;
		for (int count = 1; count <= range; ++count)
		{
			int fwd = this->ToCircle(i + count, N);
			int bkd = this->ToCircle(i - count, N);
			detonated[fwd] = 1;
			detonated[bkd] = 1;
		}
	}
	int ToCircle(int i, int N)
	{
		while (i >= N)
			i -= N;
		while (i < 0)
			i += N;
		return i;
	}
	
};
/*
BombsInACircle FixedOrderFromBegin_InPlace_Recur for "1, 3, 1, 1, 1, 1", "1, 2, 1, 1, 0, 0": 4
BombsInACircle FixedOrderFromBegin_ExtraSpace_Recur for "1, 3, 1, 1, 1, 1", "1, 2, 1, 1, 0, 0": 4
BombsInACircle ArbitraryOrder_Recur for "1, 3, 1, 1, 1, 1", "1, 2, 1, 1, 0, 0": 6
*/
#endif