#ifndef RAND_1_TO_N_EXCLUDE_K_SORTED_NUM_H
#define RAND_1_TO_N_EXCLUDE_K_SORTED_NUM_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <time.h>
#include <random>
#include <chrono>
#include <cmath>
#include "Debug.h"
/*
Leetcode: Random Pick With Blacklist
Given a blacklist B containing unique integers from [0, N), write a function to return a uniform random integer from [0, N) which is NOT in B.
Google
http://www.careercup.com/question?id=6065702117048320
Given a positive integer N, and a sorted num array, K, containing integers [1, N].
Generate a random number with probability 1/(N-K.size()) from 1~N exclude all integers in K.
Expected O(log(K.length)) time, O(1) space

The main idea is to find the Xth number that does not appear in the K sorted array, i.e., the Xth number of all the hidden interval numbers.
Interval nums accumulated count till i = K[i] - (i+1)
(i+1: transform to 1-based)
For example, 1~20
Idx:						0  1  2   3   4   5   6   7   8
K:  						4, 5, 7, 10, 11, 12, 16, 17, 18
Interval Nums Accu Count
till current index:			3  3  4   6   6   6   9   9   9  11
*/

class RandomPickWithBlacklist_HashMap //best
{
    std::unordered_map<int,int> bToW;//map blacks below M to whites above M
    int M;
public:
    //blacklist[i] is 0-based
    RandomPickWithBlacklist_HashMap(int n, std::vector<int> blacklist) //O(n) time
    {
        for (int & b : blacklist)
            bToW.insert({b,-1});
        M = n - blacklist.size();
        for (int & b : blacklist)
            if (b < M)
            {
                while(bToW.count(n-1))
                    --n;
                bToW[b] = n-1;
                --n;
            }
    }
    int Pick() //O(1) time
    {
        int res = rand() % M;
        if (bToW.count(res))
            return bToW[res];
        return res;
    }
};
class RandomPickWithBlacklist_BinarySearch_AccuWhiteCount
{
    std::vector<int> accuWhiteCount;
    int N;
    int M;
public:
    RandomPickWithBlacklist_BinarySearch_AccuWhiteCount(int n, std::vector<int> blacklist) : N(n)
    {
        M = N - blacklist.size();
        std::sort(blacklist.begin(), blacklist.end());
        blacklist.push_back(n);
        for (int i = 0; i < blacklist.size(); ++i)
            accuWhiteCount.push_back(blacklist[i] - i);
    }
    int Pick() //O(logn) time
    {
        int res = rand() % M;
        auto itr = std::upper_bound(accuWhiteCount.begin(), accuWhiteCount.end(), res) - 1;//find rightmost num that is equal to res (already have 'res' white nums before itr)
        int idx = itr - accuWhiteCount.begin();
        return res + (idx+1);//right shift res with black nums
    }
};
class RandomPickWithBlacklist_BinarySearch_InPlace
{
    std::vector<int> black;
    int N;
public:
    //blacklist[i] is 0-based
    RandomPickWithBlacklist_BinarySearch_InPlace(int n, std::vector<int> blacklist): N(n), black(blacklist) //O(nlogn) time
    {
        std::sort(black.begin(), black.end());
    }
    int Pick() //O(logn) time
    {
        int tgt = rand() % (N-black.size());//0-based white number index
        int res = 0;
        int left = 0;
        int right = black.size() - 1;
        //white number accumulated count till mid = black[mid]-mid
        //then -1 to transform to 0-based white number index
        //so black[mid]-mid-1 means the white number index
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (black[mid] - mid - 1 >= tgt)
                right = mid - 1;
            else
                left = mid + 1;
        }
        //now left is lower bound
        if (left == black.size())
        {
            int whiteNumCount = black.back() - (black.size()-1);//black.back() - lastIdx
            int extraMore = (tgt+1) - whiteNumCount;
            res = black.back() + extraMore;
        }
        else
        {
            int whiteNumCount = black[left] - left;
            int extraLess = whiteNumCount - (tgt+1);
            res = (black[left]-1) - extraLess;
        }
        return res;
    }
};
class Rand1toNExcludeKSortedNum
{
public:
	Rand1toNExcludeKSortedNum(){}
	~Rand1toNExcludeKSortedNum(){}

	int BinarySearch(int N, const std::vector<int> & K)
	{
		int tgt = rand() % (N - K.size()) + 1;//1-based random target index in the interval nums
		int res = 0;

		//find the lower bound
		int left = -1;
		int right = K.size();
		while (right - left > 1)
		{
			int mid = (left + right) / 2;

			//interval nums accumulated count till mid = K[mid]-(mid+1)
			if (K[mid] - (mid + 1) >= tgt)
			{
				right = mid;
			}
			else
			{
				left = mid;
			}
		}
		std::cout << tgt << ": " << left << "," << right << std::endl;

		//now right is the lower bound
		if (right == (int)K.size())
		{
			int intervalNumsAccumuCount = K.back() - K.size();
			int extraMore = tgt - intervalNumsAccumuCount;
			res = K.back() + extraMore;
		}
		else
		{
			int intervalNumsAccumuCount = K[right] - (right + 1);
			int extraLess = intervalNumsAccumuCount - tgt;
			res = (K[right] - 1) - extraLess;//K[right] - 1: next left of K[right] in interval
		}
		
		//===========find the lower bound2===============
		int res2;
		left = 0;
		right = K.size() - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (K[mid] - (mid + 1) >= tgt)
				right = mid - 1;
			else
				left = mid + 1;
		}
		std::cout << tgt << ": " << left << "," << right << std::endl;
		//now left is the lower bound
		if (left == (int)K.size())
		{
			int intervalNumsAccumuCount = K.back() - K.size();
			int extraMore = tgt - intervalNumsAccumuCount;
			res2 = K.back() + extraMore;
		}
		else
		{
			int intervalNumsAccumuCount = K[left] - (left + 1);
			int extraLess = intervalNumsAccumuCount - tgt;
			res2 = (K[left] - 1) - extraLess;//K[left] - 1: next left of K[left] in interval
		}
		//===============================================

		std::cout << "Rand1toNExcludeKSortedNum BinarySearch for \"1~" << N << " Exclude " << Debug::ToStr1D<int>()(K) << "\": " << res << ", " << res2 << std::endl;
		return res;
	}
};

class RandNonRepeat1toN
{
	int N;
	std::vector<int> m_sorted;
	std::mt19937 m_generator;
public:
	explicit RandNonRepeat1toN(int n) : N(n), m_sorted(), m_generator(this->currentTime()) 
	{
		m_sorted.reserve(N);
	}
	~RandNonRepeat1toN() {}
	int Next()
	{
		if (N == (int)m_sorted.size())
			return 0;
		int next = this->nextInt(1, N - m_sorted.size());//1-based random target index in the interval nums, which is also randAccuItervalNumCount
		int res = 0;

		//keep using the randAccuIntervalNumCount to compare in mind
		//1. imagine to find lower bound of next in a "interval accumulated count sorted array": O(log(m_sorted.length)) time
		int left = -1;
		int right = m_sorted.size();
		while (right - left > 1)
		{
			int mid = (left + right) / 2;

			//interval nums accumulated count till mid = m_sorted[mid]-(mid+1)
			if (m_sorted[mid] - (mid + 1) >= next)
				right = mid;
			else
				left = mid;
		}

		//now right is the lower bound
		if (right == (int)m_sorted.size())
		{
			if (m_sorted.size() == 0)
				res = next;
			else
			{
				int intervalNumsAccumuCount = m_sorted.back() - m_sorted.size();
				int extraMore = next - intervalNumsAccumuCount;
				res = m_sorted.back() + extraMore;
			}
		}
		else
		{
			int intervalNumsAccumuCount = m_sorted[right] - (right + 1);
			int extraLess = intervalNumsAccumuCount - next;
			res = (m_sorted[right] - 1) - extraLess;//m_sorted[right] - 1: next left of m_sorted[right] in interval
		}

		//2. insert res into m_sorted vector: O(m_sorted.length) time
		m_sorted.insert(m_sorted.begin() + right, res);
		//std::cout << next << "," << res << "," << right << ": " << Debug::ToStr1D<int>()(m_sorted) << std::endl;
		return res;
	}
	std::vector<int> Roll()
	{
		//O(NlogN) time
		std::vector<int> res;
		std::unordered_set<int> check;
		int buf;
		while ((buf = this->Next()) != 0)
		{
			if (check.count(buf) != 0)
				std::cout << "RandNonRepeat1toN Roll found duplicate: " << buf << "!!!!" << std::endl;
			check.insert(buf);

			res.push_back(buf);
		}
		//std::cout << Debug::ToStr1D<int>()(m_sorted) << std::endl;
		std::cout << "RandNonRepeat1toN Roll for \"1~" << N << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	void Reset()
	{
		m_sorted.clear();
	}

private:
	int currentTime()
	{
		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		return (int)(std::chrono::duration_cast<std::chrono::seconds>(now)).count();
	}
	int nextInt(int low, int high)
	{
		std::uniform_int_distribution<int> distribution(low, high);
		return distribution(m_generator);
	}
};
/*
68: 13,14
68: 14,13
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 82, 82
12: 1,2
12: 2,1
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 14, 14
84: 15,16
84: 16,15
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 100, 100
5: 0,1
5: 1,0
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 6, 6
68: 13,14
68: 14,13
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 82, 82
12: 1,2
12: 2,1
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 14, 14
70: 13,14
70: 14,13
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 84, 84
23: 4,5
23: 5,4
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 28, 28
69: 13,14
69: 14,13
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 83, 83
23: 4,5
23: 5,4
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 28, 28
2: -1,0
2: 0,-1
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 2, 2
83: 15,16
83: 16,15
Rand1toNExcludeKSortedNum BinarySearch for "1~100 Exclude 4, 13, 19, 25, 27, 31, 39, 43, 52, 58, 64, 67, 73, 81, 88, 94": 99, 99
RandNonRepeat1toN Roll for "1~100": 25, 19, 23, 86, 100, 18, 70, 30, 47, 74, 94, 73, 37, 95, 8, 43, 92, 77, 3, 54, 61, 41, 33, 78, 72, 12, 44, 81, 88, 51, 76, 20, 60, 10, 36, 9, 80, 79, 97, 65, 26, 84, 14, 46, 83, 69, 50, 99, 35, 87, 63, 11, 39, 2, 28, 82, 4, 85, 89, 52, 64, 21, 7, 91, 13, 1, 90, 24, 56, 57, 40, 48, 5, 38, 49, 55, 34, 17, 71, 96, 66, 45, 29, 42, 32, 62, 93, 75, 98, 15, 6, 58, 68, 31, 53, 22, 27, 67, 59, 16
*/
#endif