#ifndef THREE_INCR_ELEMENTS_IN_ARRAY_H
#define THREE_INCR_ELEMENTS_IN_ARRAY_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Increasing Triplet Subsequence (requires O(n) time and O(1) space)
Google
http://www.careercup.com/question?id=14960662
https://sites.google.com/site/spaceofjameschen/annnocements/findatupleinascendingorder--flipkart
Given an array v of integers.
Find 3 integers, i, j, k such that i < j < k and v[i] < v[j] < v[k].

Consider this array:
{ 10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 4, 3, 2, 7 }
the output should be {5, 6, 7}.

O(n) time, O(1) space
*/
class ThreeIncrElementsInArray
{
public:
	ThreeIncrElementsInArray(){}
	~ThreeIncrElementsInArray(){}

	bool Exist_Find(const std::vector<int> & v)//best
	{
		int N = v.size();
		int x = INT_MAX;//first
		int y = INT_MAX;//second
		int z = 0;//third
		bool res = false;
		for (int i = 0; i < N; ++i)
		{
			z = v[i];
			if (z <= x)
			{
				x = z;
			}
			else if (z <= y)
			{
				y = z;
			}
			else//z > x && z > y
			{
				res = true;
				break;
			}
		}

		std::string s;
		if (res)
			s.append(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
		else
			s.append("Null");
		std::cout << "ThreeIncrElementsInArray Exist_Find for \"" << Debug::ToStr1D<int>()(v) << "\": " << s << std::endl;
		return res;
	}
	bool Exist_Find2(const std::vector<int> & v)
	{
		int N = v.size();
		int x = -1;//1st smallest
		int y = -1;//2nd smallest
		int z = -1;//3rd smallest
		bool res = false;
		for (int i = 0; i < N; ++i)
		{
			if (x == -1 || v[i] < v[x])
			{
				x = i;
			}
			else if (v[i] != v[x] && (y == -1 || v[i] < v[y]))
			{
				y = i;
			}
			else if (v[i] != v[x] && (y != -1 && v[i] != v[y]) && (z == -1 || v[i] < v[z]))
			{
				z = i;
				res = true;
				break;
			}
		}

		std::string s;
		if (res)
			s.append(std::to_string(v[x]) + ", " + std::to_string(v[y]) + ", " + std::to_string(v[z]));
		else
			s.append("Null");
		std::cout << "ThreeIncrElementsInArray Exist_Find2 for \"" << Debug::ToStr1D<int>()(v) << "\": " << s << std::endl;
		return res;
	}

	void Find(const std::vector<int> & v)
	{
		int N = v.size();
		int i = -1;
		int j = -1;
		int k = -1;
		int pre_i = -1;
		int pre_j = -1;
		
		/*
		keep 2 increasing pairs: [i, j], [pre_i, pre_j], where v[i]<v[j] and v[pre_i]<v[pre_j]
		when meeting a val smaller than v[i], save [i, j] to [pre_i, pre_j], update [i, j]
		when meeting a val larger than v[i] but smaller than v[j], update j
		when meeting a val larger than v[j], update k, return [i, j, k]
		when meeting a val larger than v[pre_j], update k, return [pre_i, pre_j, k]
		*/

		for (int cur = 0; cur < N; ++cur)
		{
			if (pre_i != -1 && pre_j != -1 && v[cur] > v[pre_j])
			{
				k = cur;
				i = pre_i;
				j = pre_j;
				break;
			}
			else if (i != -1 && j != -1 && v[cur] > v[j])
			{
				k = cur;
				break;
			}

			/*got only i*/
			else if (i != -1 && j == -1)
			{
				if (v[cur] > v[i])
					j = cur;/*got first j*/
				else if (v[cur] < v[i])
					i = cur;/*when we have only i, just update i*/
			}

			/*got both i and j*/
			else if (i != -1 && j != -1)
			{
				if (v[cur] > v[i] && v[cur] < v[j])
					j = cur;/*keep j as small as possible*/
				else if (v[cur] < v[i])
				{
					/*now met a new i, we have to save both i and j*/
					pre_i = i;
					pre_j = j;
					i = cur;
					j = -1;
				}
			}

			/*for cur=0*/
			else
			{
				i = cur;
			}
		}

		std::string first = (i == -1) ? "N" : std::to_string(v[i]);
		std::string second = (j == -1) ? "N" : std::to_string(v[j]);
		std::string third = (k == -1) ? "N" : std::to_string(v[k]);
		std::cout << "ThreeIncrElementsInArray for \"" << Debug::ToStr1D<int>()(v) << "\": " << first << ", " << second << ", " << third << std::endl;
	}

	void DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> leftMin(N);
		std::vector<int> rightMax(N);

		leftMin[0] = v[0];
		for (int i = 1; i < N; ++i)
		{
			leftMin[i] = std::min(v[i], leftMin[i - 1]);
		}

		rightMax[N - 1] = v[N - 1];
		for (int i = N - 2; i >= 0; --i)
		{
			rightMax[i] = std::max(v[i], rightMax[i + 1]);
		}

		std::string first("N");
		std::string second("N");
		std::string third("N");
		for (int i = 1; i < N - 1; ++i)
		{
			if (v[i] > leftMin[i] && v[i] < rightMax[i])
			{
				first = std::to_string(leftMin[i]);
				second = std::to_string(v[i]);
				third = std::to_string(rightMax[i]);
				break;
			}
		}

		std::cout << "ThreeIncrElementsInArray DP1D for \"" << Debug::ToStr1D<int>()(v) << "\": " << first << ", " << second << ", " << third << std::endl;
	}

	//enumerate all possible 3 entries
	void BruteForce(const std::vector<int> & v)
	{
		int N = v.size();
		int res_i = -1;
		int res_j = -1;
		int res_k = -1;
		bool found = false;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (v[i] < v[j])
				{
					for (int k = j + 1; k < N; ++k)
					{
						if (v[j] < v[k])
						{
							res_i = i;
							res_j = j;
							res_k = k;
							found = true;
							break;
						}
					}
				}
				if (found)
					break;
			}
			if (found)
				break;
		}

		std::string first = found ? std::to_string(v[res_i]) : "N";
		std::string second = found ? std::to_string(v[res_j]) : "N";
		std::string third = found ? std::to_string(v[res_k]) : "N";
		std::cout << "ThreeIncrElementsInArray BruteForce for \"" << Debug::ToStr1D<int>()(v) << "\": " << first << ", " << second << ", " << third << std::endl;
	}
};
/*
ThreeIncrElementsInArray Exist_Find for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 1, 5, 0": 1, 4, 5
ThreeIncrElementsInArray Exist_Find for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 0, 1, 2": 0, 1, 2
ThreeIncrElementsInArray Exist_Find for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": Null
ThreeIncrElementsInArray Exist_Find for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2, 17": 1, 2, 17
ThreeIncrElementsInArray Exist_Find for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 4, 3, 2, 7": 2, 6, 7
ThreeIncrElementsInArray Exist_Find2 for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 1, 5, 0": 1, 4, 5
ThreeIncrElementsInArray Exist_Find2 for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 0, 1, 2": 0, 1, 2
ThreeIncrElementsInArray Exist_Find2 for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": Null
ThreeIncrElementsInArray Exist_Find2 for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2, 17": 1, 2, 17
ThreeIncrElementsInArray Exist_Find2 for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 4, 3, 2, 7": 2, 6, 7
ThreeIncrElementsInArray for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 1, 5, 0": 3, 4, 5
ThreeIncrElementsInArray for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 0, 1, 2": 0, 1, 2
ThreeIncrElementsInArray for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": 1, 2, N
ThreeIncrElementsInArray for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2, 17": 5, 6, 17
ThreeIncrElementsInArray for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 4, 3, 2, 7": 5, 6, 7
ThreeIncrElementsInArray DP1D for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 1, 5, 0": 3, 4, 5
ThreeIncrElementsInArray DP1D for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 0, 1, 2": 0, 1, 2
ThreeIncrElementsInArray DP1D for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": N, N, N
ThreeIncrElementsInArray DP1D for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2, 17": 10, 16, 17
ThreeIncrElementsInArray DP1D for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 4, 3, 2, 7": 5, 6, 7
ThreeIncrElementsInArray BruteForce for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 1, 5, 0": 3, 4, 5
ThreeIncrElementsInArray BruteForce for "10, 16, 14, 11, 3, 7, 6, 5, 4, 2, 0, 1, 2": 0, 1, 2
ThreeIncrElementsInArray BruteForce for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2": N, N, N
ThreeIncrElementsInArray BruteForce for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 1, 4, 3, 2, 17": 10, 16, 17
ThreeIncrElementsInArray BruteForce for "10, 16, 15, 14, 9, 13, 12, 11, 5, 8, 7, 6, 4, 3, 2, 7": 5, 6, 7
*/

/*
Leetcode: Third Maximum Number
Given a non-empty array of integers, return the third maximum number in this array.
If it does not exist, return the maximum number.
The time complexity must be in O(n).
Example 1:
Input: [3, 2, 1]
Output: 1
Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]
Output: 2
Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]
Output: 1
Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
*/
class ThirdMaximumNumber
{
public:
	ThirdMaximumNumber() {}

	int Solve(std::vector<int> & nums)//note: max1, max2, max3 is NOT necessarily a subseq of the input array
	{
		int N = nums.size();

		long long max1 = LLONG_MIN;
		long long max2 = LLONG_MIN;
		long long max3 = LLONG_MIN;

		for (int i = 0; i < N; ++i)
		{
			if (nums[i] > max1)
			{
				max3 = max2;
				max2 = max1;
				max1 = nums[i];
			}
			else if (nums[i] != max1 && nums[i] > max2)
			{
				max3 = max2;
				max2 = nums[i];
			}
			else if (nums[i] != max1 && nums[i] != max2 && nums[i] > max3)
			{
				max3 = nums[i];
			}
		}
		int res = (max3 == LLONG_MIN) ? (int)max1 : (int)max3;

		std::cout << "ThirdMaximumNumber for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
};
/*
ThirdMaximumNumber for "2, 2, 3, 1": 1
*/
#endif