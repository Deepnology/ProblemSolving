#ifndef PAINTERS_PARTITION_FAIR_WORKLOAD_H
#define PAINTERS_PARTITION_FAIR_WORKLOAD_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Split Array Largest Sum
AKA Painters' Partition, Fair Workload
Elements of programming interview, Greedy: Load balancing (GreedyBinarySearchPartition)
http://leetcode.com/2011/04/the-painters-partition-problem.html
http://leetcode.com/2011/04/the-painters-partition-problem-part-ii.html
http://community.topcoder.com/stat?c=problem_statement&pm=1901&rd=4650
http://www.seas.gwu.edu/~simhaweb/alg/lectures/module9/module9.html
http://stackoverflow.com/questions/6454598/stuck-with-an-interview-question-partitioning-of-an-array
You have to paint N boards of length {A0, A1, A2, ..., AN-1}.
There are K painters available and you are also given how much time a painter takes to paint 1 unit of board. 
You have to get this job done as soon as possible under the constraints that any painter will only paint continuous sections of board, say board {2, 3, 4} or only board {1} or nothing but not board {2, 4, 5}.

Given an array of non-negative integers A and a positive integer k, we want to:
Divide A into k or fewer partitions (subarrays),
such that the maximum sum over (among) all the partitions is minimized.
Return the minimized maximum sum over all the partitions.

BruteForce Recur: exponential time
DP2D Iterate: O(K*N^2) time, O(K*N) space
GreedyBinarySearch: O(N*logW) time, O(1) space, where W is total number of work that are to be partitioned
GreedyBinarySearch2: O(N log N + N log max(A)) time in worst case, O(N log N) time in average
see also MaxPriceCutting.h, MaxProductCutting.h
*/
class PaintersPartitionFairWorkload
{
public:
	PaintersPartitionFairWorkload(){}
	~PaintersPartitionFairWorkload(){}
	//1. BruteForce Recur
	int BruteForce_Recur(const std::vector<int> & A, int K)//K: partition count
	{
		int N = A.size();
		int minMaxPartitionSum = this->minMaxPartitionSumRecur(A, N, K);
		std::cout << "PaintersPartitionFairWorkload BruteForce_Recur for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << minMaxPartitionSum << std::endl;
		return minMaxPartitionSum;
	}
private:
	int minMaxPartitionSumRecur(const std::vector<int> & A, int curSize, int K)//divide the range A[0]~A[curSize-1] into K
	{
		if (K == 1)
			return this->sumRange(A, 0, curSize - 1);
		if (curSize == 1)
			return A[0];

		int subPartitionBest = INT_MAX;
		for (int leftSize = 1; leftSize <= curSize; ++leftSize)
			subPartitionBest = std::min(subPartitionBest, 
			std::max(this->minMaxPartitionSumRecur(A, leftSize, K - 1), this->sumRange(A, leftSize, curSize - 1)));

		return subPartitionBest;
	}
	int sumRange(const std::vector<int> & A, int from, int to)
	{
		int sum = 0;
		for (int i = from; i <= to; ++i)
			sum += A[i];
		return sum;
	}

	//2. DP2D Recur
public:
	int DP2D_Recur(const std::vector<int> & A, int K)//K: partition count
	{
		int N = A.size();
		std::vector<int> prefixSum(N);
		prefixSum[0] = A[0];
		for (int i = 1; i < N; ++i)
			prefixSum[i] = prefixSum[i - 1] + A[i];
		std::vector<std::vector<int> > dp2d(N, std::vector<int>(K, -1));

		int minMaxPartitionSum = this->minMaxPartitionSumDP2DRecur(A, N, K, prefixSum, dp2d);

		Debug::Print2D<int>()(dp2d, false);
		std::cout << "PaintersPartitionFairWorkload DP2D_Recur for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << minMaxPartitionSum << std::endl;
		return minMaxPartitionSum;
	}
private:
	int minMaxPartitionSumDP2DRecur(const std::vector<int> & A, int curSize, int K, const std::vector<int> & prefixSum, std::vector<std::vector<int> > & dp2d)//divide the range A[0]~A[curSize-1] into K
	{
		if (K == 1)
			return dp2d[curSize - 1][K - 1] = prefixSum[curSize - 1];
		if (curSize == 1)
			return dp2d[curSize - 1][K - 1] = A[0];

		if (dp2d[curSize - 1][K - 1] != -1)
			return dp2d[curSize - 1][K - 1];

		int subPartitionBest = INT_MAX;
		for (int leftSize = 1; leftSize <= curSize; ++leftSize)
			subPartitionBest = std::min(subPartitionBest,
			std::max(this->minMaxPartitionSumDP2DRecur(A, leftSize, K - 1, prefixSum, dp2d), prefixSum[curSize - 1] - prefixSum[leftSize - 1]));

		return dp2d[curSize - 1][K - 1] = subPartitionBest;
	}

	//3. DP2D Iterate
public:
	int DP2D_Iterate(const std::vector<int> & A, int K)
	{
		int N = A.size();
		std::vector<int> prefixSum(N);
		prefixSum[0] = A[0];
		for (int i = 1; i < N; ++i)
			prefixSum[i] = prefixSum[i - 1] + A[i];
		std::vector<std::vector<int> > dp2d(N, std::vector<int>(K, 0));

		for (int i = 0; i < N; ++i)
			dp2d[i][0] = prefixSum[i];//when there is only one worker (K==1), the min max single worker workload is the total length A[0]~A[i]
		for (int i = 0; i < K; ++i)
			dp2d[0][i] = A[0];//when there is only one task, the min max single worker workload is the length of that one task

		for (int colX = 1; colX < K; ++colX)
		{
			for (int rowY = 1; rowY < N; ++rowY)
			{
				int best = INT_MAX;
				for (int curY = 0; curY <= rowY; ++curY)
				{
					best = std::min(best, std::max(dp2d[curY][colX - 1], prefixSum[rowY] - prefixSum[curY]));//dp2d[curY][colX-1]: previous optimum single worker workload with A[0]~A[curY] tasks and one less workers; prefixSum[rowY]-prefixSum[curY]: the workload with A[curY+1]~A[rowY] tasks of current worker
				}
				dp2d[rowY][colX] = best;
			}
		}

		Debug::Print2D<int>()(dp2d, false);
		std::cout << "PaintersPartitionFairWorkload DP2D_Iterate for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << dp2d[N - 1][K - 1] << std::endl;
		return dp2d[N - 1][K - 1];
	}

	//4. Binary Search Greedy Partition
public:
	std::vector<int> BinarySearchGreedyPartition(const std::vector<int> & A, int K)
	{
		int lo = 0;
		int hi = std::accumulate(A.cbegin(), A.cend(), 0);
		std::vector<int> res;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;//mid will be the current limit of each partition
			std::vector<int> assigned(K, 0);
			bool isFeasible = this->greedyAssignment(A, K, mid, assigned);//try current limit
			if (isFeasible)
			{
				res = assigned;
				hi = mid - 1;//decrease the limit of each partition if current limit is feasible to assign all tasks
			}
			else
				lo = mid + 1;//increase the limit of each partition if current limit is not feasible to assign all tasks
		}
		//now lo will be the final limit of each partition, which is also the minimized limit of each partition

		std::cout << "PaintersPartitionFairWorkload BinarySearchGreedyPartition for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << lo << ", (" << Debug::ToStr1D<int>()(res) << ")" << std::endl;
		return res;
	}
private:
	bool greedyAssignment(const std::vector<int> & A, int K, int limit, std::vector<int> & assigned)//O(N*K) time
	{
		int idx = 0;
		for (const int & val : A)
		{
			//1. find the next available partition that can accommodate val
			while (idx < K && val + assigned[idx] > limit)
				++idx;

			//2. add val to that partition if found
			if (idx >= K)
				return false;
			else
				assigned[idx] += val;
		}
		return true;
	}

public:
    int BinarySearchGreedyPartition2(const std::vector<int> & A, int K)
    {
        long long lo = *std::min_element(A.begin(),A.end());
        long long hi = 0;
        for (auto & i : A) hi += (long long)i;
        while (lo <= hi)
        {
            long long mid = lo + (hi - lo) / 2;
            bool valid = canPartitionAtMostKSubarrs(A, K, mid);
            if (valid)
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        std::cout << "PaintersPartitionFairWorkload BinarySearchGreedyPartition2 for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << lo << std::endl;
        return (int)lo;
    }
private:
    bool canPartitionAtMostKSubarrs(const std::vector<int> & A, int K, long long limit)
    {
        int N = A.size();
        int i = 0;
        int curK = 0;
        long long curSum = 0;
        while (i < N && curK < K)
        {
            while (i < N && curSum + (long long)A[i] <= limit)
            {
                curSum += (long long)A[i++];
            }
            curSum = 0;
            ++curK;
        }
        return i == N;
    }
};
/*
Leetcode: Capacity To Ship Packages Within D Days
A conveyor belt has packages that must be shipped from one port to another within D days.
The i-th package on the conveyor belt has a weight of weights[i].
Each day, we load the ship with packages on the conveyor belt (in the order given by weights).
We may not load more weight than the maximum weight capacity of the ship.
Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within D days.
Example 1:
Input: weights = [1,2,3,4,5,6,7,8,9,10], D = 5
Output: 15
Explanation:
A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10
Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
 */
class MinMaxSubarrSumToPartitionAtMostKSubarr
{
public:
    int FindMinMaxSubarrSum(const std::vector<int> & weights, int K)
    {
        int right = std::accumulate(weights.begin(), weights.end(), 0);
        int left = *std::max_element(weights.begin(), weights.end());
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            bool valid = canPartitionAtMostKSubarr(weights, K, mid);
            if (valid)
                right = mid-1;
            else
                left = mid+1;
        }
        return left;
    }
private:
    bool canPartitionAtMostKSubarr(const std::vector<int> & weights, int K, int sum)
    {
        int curK = 0;
        int curSum = 0;
        int N = weights.size();
        int i = 0;
        while (i < N && curK < K)
        {
            while (i < N && curSum + weights[i] <= sum)
            {
                curSum += weights[i++];
            }
            curSum = 0;
            ++curK;
        }
        return i == N;
    }
};
/*
Elements of programming interview:
Suppose you want to build a large distributed storage system on the web.
Millions of users will store terabytes of data on your servers.
One way to design the system would be to compute a hash code for each user's login ID, partition the hash codes across equal-sized buckets, and store the data for each bucket of users on one server.
For this scheme, mapping a user to his server entails evaluating a hash function.
However, if a small number of users occupy a large fraction of the storage space, this scheme will not achieve a balanced partition.
One way to solve this problem is to use a nonuniform partition.

You have n users with unique hash codes h0 through h(n-1), and m servers.
The hash code are ordered by index, i.e., hi < h(i+1) for i belongs to [0, n-2].
User i requires bi bytes of storage.
The values k0 < k1 < ... < k(m-2) are used to assign users to servers.
Specifically, the user with hash code c gets assigned to the server with the lowest ID i such that c <= ki, or to Server m-1 if no such i exists.
This restricted mapping of users to servers means that the user-to-server lookup can be implemented with a BST on m-1 nodes, rather than a hash table on n users.
The load on a server is the sum of the bytes of storage of all users assigned to that server.
Compute values for k0, k1, ..., k(m-2) that minimizes the load on the most heavily loaded server.
*/

/*
PaintersPartitionFairWorkload BruteForce_Recur for "5" in "10, 20, 30, 40, 50, 60, 70, 80, 90": 110
[rY][cX]
Row#0	= 10, 10, 10, 10, -1
Row#1	= 30, 20, 20, 20, -1
Row#2	= 60, 30, 30, 30, -1
Row#3	= 100, 60, 40, 40, -1
Row#4	= 150, 90, 60, 50, -1
Row#5	= 210, 110, 90, 60, -1
Row#6	= 280, 150, 110, 90, -1
Row#7	= 360, 210, 150, 110, -1
Row#8	= 450, 240, 170, 150, 110

PaintersPartitionFairWorkload DP2D_Recur for "5" in "10, 20, 30, 40, 50, 60, 70, 80, 90": 110
[rY][cX]
Row#0	= 10, 10, 10, 10, 10
Row#1	= 30, 20, 20, 20, 20
Row#2	= 60, 30, 30, 30, 30
Row#3	= 100, 60, 40, 40, 40
Row#4	= 150, 90, 60, 50, 50
Row#5	= 210, 110, 90, 60, 60
Row#6	= 280, 150, 110, 90, 70
Row#7	= 360, 210, 150, 110, 90
Row#8	= 450, 240, 170, 150, 110

PaintersPartitionFairWorkload DP2D_Iterate for "5" in "10, 20, 30, 40, 50, 60, 70, 80, 90": 110
PaintersPartitionFairWorkload BinarySearchGreedyPartition for "5" in "10, 20, 30, 40, 50, 60, 70, 80, 90": 110, (100, 110, 70, 80, 90)
PaintersPartitionFairWorkload BinarySearchGreedyPartition2 for "5" in "10, 20, 30, 40, 50, 60, 70, 80, 90": 110
PaintersPartitionFairWorkload BruteForce_Recur for "5" in "70, 10, 20, 40, 80, 30, 50, 90, 60": 120
[rY][cX]
Row#0	= 70, 70, 70, 70, -1
Row#1	= 80, 70, 70, 70, -1
Row#2	= 100, 70, 70, 70, -1
Row#3	= 140, 70, 70, 70, -1
Row#4	= 220, 120, 80, 80, -1
Row#5	= 250, 140, 110, 80, -1
Row#6	= 300, 160, 120, 80, -1
Row#7	= 390, 220, 140, 120, -1
Row#8	= 450, 230, 160, 140, 120

PaintersPartitionFairWorkload DP2D_Recur for "5" in "70, 10, 20, 40, 80, 30, 50, 90, 60": 120
[rY][cX]
Row#0	= 70, 70, 70, 70, 70
Row#1	= 80, 70, 70, 70, 70
Row#2	= 100, 70, 70, 70, 70
Row#3	= 140, 70, 70, 70, 70
Row#4	= 220, 120, 80, 80, 80
Row#5	= 250, 140, 110, 80, 80
Row#6	= 300, 160, 120, 80, 80
Row#7	= 390, 220, 140, 120, 90
Row#8	= 450, 230, 160, 140, 120

PaintersPartitionFairWorkload DP2D_Iterate for "5" in "70, 10, 20, 40, 80, 30, 50, 90, 60": 120
PaintersPartitionFairWorkload BinarySearchGreedyPartition for "5" in "70, 10, 20, 40, 80, 30, 50, 90, 60": 120, (100, 120, 80, 90, 60)
PaintersPartitionFairWorkload BinarySearchGreedyPartition2 for "5" in "70, 10, 20, 40, 80, 30, 50, 90, 60": 120
PaintersPartitionFairWorkload BruteForce_Recur for "4" in "568, 712, 412, 231, 241, 393, 865, 287, 128, 457, 238, 98, 980, 23, 782": 1785
[rY][cX]
Row#0	= 568, 568, 568, -1
Row#1	= 1280, 712, 712, -1
Row#2	= 1692, 1124, 712, -1
Row#3	= 1923, 1280, 712, -1
Row#4	= 2164, 1280, 884, -1
Row#5	= 2557, 1280, 1124, -1
Row#6	= 3422, 1730, 1280, -1
Row#7	= 3709, 1923, 1280, -1
Row#8	= 3837, 1923, 1280, -1
Row#9	= 4294, 2164, 1730, -1
Row#10	= 4532, 2368, 1730, -1
Row#11	= 4630, 2466, 1730, -1
Row#12	= 5610, 3053, 1923, -1
Row#13	= 5633, 3076, 1923, -1
Row#14	= 6415, 3422, 2164, 1785

PaintersPartitionFairWorkload DP2D_Recur for "4" in "568, 712, 412, 231, 241, 393, 865, 287, 128, 457, 238, 98, 980, 23, 782": 1785
[rY][cX]
Row#0	= 568, 568, 568, 568
Row#1	= 1280, 712, 712, 712
Row#2	= 1692, 1124, 712, 712
Row#3	= 1923, 1280, 712, 712
Row#4	= 2164, 1280, 884, 712
Row#5	= 2557, 1280, 1124, 712
Row#6	= 3422, 1730, 1280, 1124
Row#7	= 3709, 1923, 1280, 1152
Row#8	= 3837, 1923, 1280, 1280
Row#9	= 4294, 2164, 1730, 1280
Row#10	= 4532, 2368, 1730, 1280
Row#11	= 4630, 2466, 1730, 1280
Row#12	= 5610, 3053, 1923, 1730
Row#13	= 5633, 3076, 1923, 1730
Row#14	= 6415, 3422, 2164, 1785

PaintersPartitionFairWorkload DP2D_Iterate for "4" in "568, 712, 412, 231, 241, 393, 865, 287, 128, 457, 238, 98, 980, 23, 782": 1785
PaintersPartitionFairWorkload BinarySearchGreedyPartition for "4" in "568, 712, 412, 231, 241, 393, 865, 287, 128, 457, 238, 98, 980, 23, 782": 1785, (1692, 1730, 1208, 1785)
PaintersPartitionFairWorkload BinarySearchGreedyPartition2 for "4" in "568, 712, 412, 231, 241, 393, 865, 287, 128, 457, 238, 98, 980, 23, 782": 1785
PaintersPartitionFairWorkload BruteForce_Recur for "5" in "85, 39, 64, 11, 70, 80, 78, 61, 65, 20": 145
[rY][cX]
Row#0	= 85, 85, 85, 85, -1
Row#1	= 124, 85, 85, 85, -1
Row#2	= 188, 103, 85, 85, -1
Row#3	= 199, 114, 85, 85, -1
Row#4	= 269, 145, 103, 85, -1
Row#5	= 349, 188, 145, 103, -1
Row#6	= 427, 228, 158, 145, -1
Row#7	= 488, 269, 188, 145, -1
Row#8	= 553, 284, 204, 158, -1
Row#9	= 573, 304, 224, 158, 145

PaintersPartitionFairWorkload DP2D_Recur for "5" in "85, 39, 64, 11, 70, 80, 78, 61, 65, 20": 145
[rY][cX]
Row#0	= 85, 85, 85, 85, 85
Row#1	= 124, 85, 85, 85, 85
Row#2	= 188, 103, 85, 85, 85
Row#3	= 199, 114, 85, 85, 85
Row#4	= 269, 145, 103, 85, 85
Row#5	= 349, 188, 145, 103, 85
Row#6	= 427, 228, 158, 145, 103
Row#7	= 488, 269, 188, 145, 139
Row#8	= 553, 284, 204, 158, 145
Row#9	= 573, 304, 224, 158, 145

PaintersPartitionFairWorkload DP2D_Iterate for "5" in "85, 39, 64, 11, 70, 80, 78, 61, 65, 20": 145
PaintersPartitionFairWorkload BinarySearchGreedyPartition for "5" in "85, 39, 64, 11, 70, 80, 78, 61, 65, 20": 145, (124, 145, 80, 139, 85)
PaintersPartitionFairWorkload BinarySearchGreedyPartition2 for "5" in "85, 39, 64, 11, 70, 80, 78, 61, 65, 20": 145
*/
#endif