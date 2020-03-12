#ifndef BEAUTIFUL_ARRANGEMENT_H
#define BEAUTIFUL_ARRANGEMENT_H
#include "Debug.h"
/*
Leetcode: Beautiful Arrangement
Suppose you have N integers from 1 to N.
We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 <= i <= N) in this array:
1. The number at the ith position is divisible by i.
2. i is divisible by the number at the ith position.
Now given N, how many beautiful arrangements can you construct?
Example 1:
Input: 2
Output: 2
Explanation:
The first beautiful arrangement is [1, 2]:
Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).
Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).
The second beautiful arrangement is [2, 1]:
Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).
Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
Note:
N is a positive integer and will not exceed 15.

Leetcode: Beautiful Arrangement II
Given two integers n and k, you need to construct a list which contains n different positive integers ranging from 1 to n and obeys the following requirement:
Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
If there are multiple answers, print any of them.
Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.
Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.
*/
class BeautifulArrangement
{
public:
	BeautifulArrangement() {}

	int Recur(int N)
	{
		//enumerate all possible permutations 
		//record used numbers in an integer that map to their already computed counts
		std::vector<int> v;
		for (int i = 1; i <= N; ++i)
			v.push_back(i);
		int used = 0;
		std::vector<int> count(1 << 16, -1);
		int res = recur(v, 0, used, count);

		std::cout << "BeautifulArrangement Recur for \"" << N << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(std::vector<int> & v, int cur, int & used, std::vector<int> & count)
	{
		int N = v.size();
		if (cur == N)
		{
			return 1;
		}
		if (count[used] != -1) return count[used];
		int res = 0;
		for (int i = cur; i < N; ++i)
		{
			if (v[i] % (cur + 1) == 0 || (cur + 1) % v[i] == 0)
			{
				std::swap(v[cur], v[i]);
				used |= (1 << v[cur]);
				res += recur(v, cur + 1, used, count);
				used ^= (1 << v[cur]);
				std::swap(v[cur], v[i]);
			}
		}
		return count[used] = res;
	}

public:
	//Beautiful Arrangement II
	std::vector<int> FindArrangement(int n, int k)
	{
		/*
		We want to permute nums in [1:n] so that it contains k adj diff values.
		If you have n number, the maximum k can be n-1.
		If n is 9, maximum k is 8.
		This can be done by folding the sequence of [1:n] interleavingly.
		nums: 1 n 2 n-1 3 n-2 4 n-3 5
		   =  1 9 2  8  3  7  4  6  5
		diff:  8 7  6  5  4  3  2  1
		*/
		std::vector<int> res;
		int left = 1;
		int right = n;

		while (left <= right)
		{
			if (k > 1)
			{
				if (k & 1)
					res.push_back(right--);
				else
					res.push_back(left++);
				--k;
			}
			else
				res.push_back(right--);
		}

		return res;
	}
};
/*
BeautifulArrangement Recur for "4": 8
*/
#endif
