#ifndef _FIND_PAIR_WITH_MAX_APPEAL_H
#define _FIND_PAIR_WITH_MAX_APPEAL_H
/*
Amazon OA
Find pair with maximum Appeal value.
Input: Array
Output: index {i, j} ( i = j allowed) with maximum Appeal
Appeal = A[i] + A[j] + abs(i-j)
Example 1:
Input: [1, 3, -1]
Output: [1, 1]
Explanation: Appeal = A[1] + A[1] + abs(0) = 3 + 3 + 0 = 6
Example 2:
Input: [1, 6, 1, 1, 1, 1, 7]
Output: [1, 6]
Explanation 6 + 7 + abs(1 - 6) = 18
Example 3:
Input: [6, 2, 7, 4, 4, 1, 6]
Output: [0, 6]
Explanation: 6 + 6 + abs(0 - 6) = 18

A[i] + A[j] + |i-j|
there are 2 cases:
A[i] + A[j] + (i-j) => A[i]+i + A[j]-j => case1
A[i] + A[j] + (j-i) => A[i]-i + A[j]+j => case2
 */
class FindPairWithMaxAppeal
{
public:
    FindPairWithMaxAppeal(){}

    int TwoPtrs(std::vector<int> && v)
    {
        int N = v.size();
        int max1 = INT_MIN;
        int max2 = INT_MIN;
        int idx1, idx2;
        for (int i = 0; i < N; ++i)
        {
            int cur1 = v[i]+i;
            if (cur1 > max1)
            {
                max1 = cur1;
                idx1 = i;
            }
            int cur2 = v[i]-i;
            if (cur2 > max2)
            {
                max2 = cur2;
                idx2 = i;
            }
        }
        if (idx1 > idx2) std::swap(idx1, idx2);
        int res = v[idx1] + v[idx2] + std::abs(idx1-idx2);

        std::cout << "FindPairWithMaxAppeal TwoPtrs for [" << Debug::ToStr1D<int>()(v) << "]: " << res << ", [" << idx1 << "," << idx2 << "], " << max1+max2 << std::endl;
        return res;
    }

};
/*
FindPairWithMaxAppeal TwoPtrs for [1, 3, -1]: 6, [1,1], 6
FindPairWithMaxAppeal TwoPtrs for [1, 6, 1, 1, 1, 1, 7]: 18, [1,6], 18
FindPairWithMaxAppeal TwoPtrs for [6, 2, 7, 4, 4, 1, 6]: 18, [0,6], 18
FindPairWithMaxAppeal TwoPtrs for [3, 3, 1, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]: 25, [3,18], 25
FindPairWithMaxAppeal TwoPtrs for [3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1]: 15, [1,10], 15
 */

/*
Leetcode: Maximum of Absolute Value Expression
Given two arrays of integers with equal lengths, return the maximum value of:
|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
where the maximum is taken over all 0 <= i, j < arr1.length.
Example 1:
Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
Output: 13
Example 2:
Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
Output: 20
Constraints:
2 <= arr1.length == arr2.length <= 40000
-10^6 <= arr1[i], arr2[i] <= 10^6
 */
class FindPairWithMaxAbsDiffFrom2Arr
{
public:
    FindPairWithMaxAbsDiffFrom2Arr(){}

    /*
    |arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j|
    suppose i>j, there are 4 cases:
    arr1[i]-arr1[j] + arr2[i]-arr2[j] + i-j => (arr1[i]+arr2[i]+i) - (arr1[j]+arr2[j]+j) => caseA
    arr1[i]-arr1[j] + arr2[j]-arr2[i] + i-j => (arr1[i]-arr2[i]+i) - (arr1[j]-arr2[j]+j) => caseB
    arr1[j]-arr1[i] + arr2[i]-arr2[j] + i-j => (-arr1[i]+arr2[i]+i) - (-arr1[j]+arr2[j]+j) => caseC
    arr1[j]-arr1[i] + arr2[j]-arr2[i] + i-j => (-arr1[i]-arr2[i]+i) - (-arr1[j]-arr2[j]+j) => caseD
    */

    int Solve(std::vector<int> && arr1, std::vector<int> && arr2)
    {
        int N = arr1.size();
        int Amax = INT_MIN;
        int Amin = INT_MAX;
        int Bmax = INT_MIN;
        int Bmin = INT_MAX;
        int Cmax = INT_MIN;
        int Cmin = INT_MAX;
        int Dmax = INT_MIN;
        int Dmin = INT_MAX;
        for (int i = 0; i < N; ++i)
        {
            int curA = arr1[i] + arr2[i] + i;
            Amax = std::max(Amax, curA);
            Amin = std::min(Amin, curA);
            int curB = arr1[i] - arr2[i] + i;
            Bmax = std::max(Bmax, curB);
            Bmin = std::min(Bmin, curB);
            int curC = -arr1[i] + arr2[i] + i;
            Cmax = std::max(Cmax, curC);
            Cmin = std::min(Cmin, curC);
            int curD = -arr1[i] - arr2[i] + i;
            Dmax = std::max(Dmax, curD);
            Dmin = std::min(Dmin, curD);
        }
        int res = std::max(Amax-Amin,std::max(Bmax-Bmin,std::max(Cmax-Cmin,Dmax-Dmin)));

        std::cout << "FindPairWithMaxAbsDiffFrom2Arr for [" << Debug::ToStr1D<int>()(arr1) << "], [" << Debug::ToStr1D<int>()(arr2) << "]: " << res << std::endl;
        return res;
    }
};
/*
FindPairWithMaxAbsDiffFrom2Arr for [1, -2, -5, 0, 10], [0, -2, -1, -7, -4]: 20
 */
#endif
