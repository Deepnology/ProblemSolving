#ifndef _COUNT_INCR_OR_DECR_SUBSEQ_OF_LEN_3_H
#define _COUNT_INCR_OR_DECR_SUBSEQ_OF_LEN_3_H
#include "Debug.h"
/*
Leetcode: Count Number of Teams
There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
You have to form a team of 3 soldiers amongst them under the following rules:
Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
A team is valid if:  (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).
Example 1:
Input: rating = [2,5,3,4,1]
Output: 3
Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).
Example 2:
Input: rating = [2,1,3]
Output: 0
Explanation: We can't form any team given the conditions.
Example 3:
Input: rating = [1,2,3,4]
Output: 4

see also MinNumBySwapKAdjDigits.h, LoginCountFromUnorderedStream.h
 */
class CountIncrOrDecrSubseqOfLen3
{
public:
    //BruteForce: O(N^3) time
    //Approach 1: O(N^2) time
    int BetterThanBruteForce(std::vector<int> & rating)
    {
        int N = rating.size();
        int res = 0;
        for (int i = 1; i < N-1; ++i)
        {
            int leftLess = 0, leftGreater = 0, rightLess = 0, rightGreater = 0;
            for (int j = 0; j < N; ++j)
                if (j<i)
                {
                    if (rating[j]<rating[i])
                        ++leftLess;
                    else
                        ++leftGreater;
                }
                else if (i<j)
                {
                    if (rating[i]<rating[j])
                        ++rightGreater;
                    else
                        ++rightLess;
                }
            res += leftLess*rightGreater + leftGreater*rightLess;
        }
        return res;
    }

    //Approach 2: Binary Search Tree, O(NlogN) time
    struct TreeNode
    {
        int val;
        int leftCount;
        TreeNode * left;
        TreeNode * right;
        TreeNode(int v): val(v), leftCount(0), left(NULL), right(NULL){}
    };
    void Insert(TreeNode *& root, int val)
    {
        if (root == NULL)
        {
            root = new TreeNode(val);
            return;
        }
        if (root->val > val)
        {
            Insert(root->left, val);
            root->leftCount++;
        }
        else if (root->val < val)
        {
            Insert(root->right, val);
        }
        else
        {
            //won't get here since all vals are unique
        }
    }
    void Remove(TreeNode *& root, int val)
    {
        if (root == NULL) return;
        if (root->val > val)
        {
            Remove(root->left, val);
            --root->leftCount;
        }
        else if (root->val < val)
        {
            Remove(root->right, val);
        }
        else
        {
            if (root->left && root->right)
            {
                TreeNode * RSubLmost = root->right;
                while (RSubLmost->left)
                    RSubLmost = RSubLmost->left;
                root->val = RSubLmost->val;
                Remove(root->right, root->val);
            }
            else //1 or 0 child
            {
                root = root->left ? root->left : root->right;
            }
        }
    }
    int SearchPrefixSum(TreeNode * root, int val)
    {
        int res = 0;
        while (root)
        {
            if (root->val > val)
                root = root->left;
            else if (root->val < val)
            {
                res += root->leftCount + 1;
                root = root->right;
            }
            else
            {
                res += root->leftCount + 1;
                break;
            }
        }
        return res;
    }
    int UseBinarySearchTree(std::vector<int> & rating)
    {
        int N = rating.size();
        int res = 0;
        TreeNode * left = NULL;
        TreeNode * right = NULL;
        for (int i = 0; i < N; ++i)
            Insert(right, rating[i]);
        for (int i = 0; i < N; ++i)//[leftCount,mid,rightCount]=[i,1,N-(i+1)]
        {
            Insert(left, rating[i]);
            int leftLess = SearchPrefixSum(left, rating[i])-1;//-1: to exclude rating[i]
            //leftLess is 0 when i==0
            int leftGreater = i-leftLess;
            int rightLess = SearchPrefixSum(right, rating[i])-1;//-1: to exclude rating[i]
            int rightGreater = N-(i+1)-rightLess;
            //rightGreater is 0 when i==N-1
            Remove(right, rating[i]);
            res += leftLess*rightGreater + leftGreater*rightLess;
        }
        return res;
    }

    //Approach3: Binary Indexed Tree, O(NlogN) time
    void Update(std::vector<int> & bit, int i, int val)
    {
        ++i;//convert to bit index
        while (i < bit.size())
        {
            bit[i] += val;
            i += i & -i;
        }
    }
    int PrefixSum(std::vector<int> & bit, int i)
    {
        ++i;//convert to bit index
        int res = 0;
        while(i)
        {
            res += bit[i];
            i -= i & -i;
        }
        return res;
    }
    int UseBinaryIndexedTree(std::vector<int> & rating)
    {
        int N = rating.size();
        int res = 0;
        std::vector<int> bitR(N+1, 0);
        std::map<int,int> valToBitIdx;//map vals to nums in [0:N-1] in incr order
        for (int i = 0; i < N; ++i)
            valToBitIdx.insert({rating[i],-1});
        int idx = 0;
        for (auto & p : valToBitIdx)
            p.second = idx++;
        for (int i = 0; i < N; ++i)
            Update(bitR, valToBitIdx[rating[i]], 1);
        std::vector<int> bitL(N+1, 0);
        for (int i = 0; i < N; ++i)//[leftCount,mid,rightCount]=[i,1,N-(i+1)]
        {
            Update(bitL, valToBitIdx[rating[i]], 1);
            int leftLess = PrefixSum(bitL, valToBitIdx[rating[i]])-1;//-1: to exclude rating[i]
            //leftLess is 0 when i==0
            int leftGreater = i-leftLess;
            int rightLess = PrefixSum(bitR, valToBitIdx[rating[i]])-1;//-1: to exclude rating[i]
            int rightGreater = N-(i+1)-rightLess;
            //rightGreater is 0 when i==N-1
            Update(bitR, valToBitIdx[rating[i]], -1);
            res += leftLess*rightGreater + leftGreater*rightLess;
        }
        return res;
    }
};
#endif
