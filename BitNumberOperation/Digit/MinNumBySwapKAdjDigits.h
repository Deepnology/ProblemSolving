#ifndef _MIN_NUM_BY_SWAP_K_ADJ_DIGITS_H
#define _MIN_NUM_BY_SWAP_K_ADJ_DIGITS_H
#include "Debug.h"
/*
Leetcode: Minimum Possible Integer After at Most K Adjacent Swaps On Digits
Given a string num representing the digits of a very large integer and an integer k.
You are allowed to swap any two adjacent digits of the integer at most k times.
Return the minimum integer you can obtain also as a string.

see also LoginCountFromUnorderedStream.h, CountIncrOrDecrSubseqOfLen3.h
 */
class MinNumBySwapKAdjDigits
{
public:
    //the total num of swaps to reverse the string =
    //(n-1)+(n-2)+...+1 = (n-1)*(n-1+1)/2 = (n-1)*n/2

    //Approach 1: brute force, O(N^2) time
    std::string BruteForce(std::string num, int k)
    {
        return recur(num, k);
    }
private:
    std::string recur(std::string cur, int k)
    {
        if (k <= 0) return cur;
        int N = cur.size();
        if (k >= (N-1)*N/2)
        {
            std::sort(cur.begin(), cur.end());
            return cur;
        }
        //repeat: find the leftest smallest digit in range[0:k] and move it to front
        int minDigit = cur[0]-'0';
        int minIdx = 0;
        for (int i = 1; i <= std::min(N-1,k); ++i)
        {
            if (cur[i]-'0' < minDigit)
            {
                minDigit = cur[i]-'0';
                minIdx = i;
            }
        }
        return std::to_string(minDigit) +
               recur(cur.substr(0,minIdx) + cur.substr(minIdx+1), k-minIdx);
    }

    //Approach 2: Binary Indexed Tree
private:
    std::vector<int> bit;//bit[0] is dummy
    void update(int i)
    {
        ++i;//convert to bit index
        while (i < bit.size())
        {
            ++bit[i];
            i += i & -i;
        }
    }
    int prefixSum(int i)
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
public:
    std::string UseBinaryIndexedTree(std::string num, int k)
    {
        if (k <= 0) return num;
        int N = num.size();
        if (k >= (N - 1) * N / 2)
        {
            std::sort(num.begin(), num.end());
            return num;
        }
        bit.resize(N + 1, 0);
        //bit[i]: prefixSum of cur and prev digits' num of times being shifted to right
        std::vector<std::deque<int>> idx(10, std::deque<int>());
        for (auto i = 0; i < N; ++i)
            idx[num[i] - '0'].push_back(i);
        std::string res;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                if (!idx[j].empty() && idx[j].front() - prefixSum(idx[j].front() - 1) <= k)
                {
                    res.push_back(j + '0');
                    update(idx[j].front());
                    //increment cur and all prev digits' num of times being shifted to right
                    k -= idx[j].front() - prefixSum(idx[j].front() - 1);
                    idx[j].pop_front();
                    break;
                }
            }
        }
        return res;
    }

    //Approach 3: Binary Search Tree
private:
    struct TreeNode
    {
        int val;
        int sum;
        int leftSum;
        TreeNode * left;
        TreeNode * right;
        TreeNode(int v): val(v), sum(0), leftSum(0), left(NULL), right(NULL){}
    };
    void InsertOrIncr(TreeNode *& root, int val, int incrVal)
    {
        if (root == NULL)
        {
            root = new TreeNode(val);
            root->sum += incrVal;
            return;
        }
        if (root->val > val)
        {
            InsertOrIncr(root->left, val, incrVal);
            root->leftSum += incrVal;
        }
        else if (root->val < val)
        {
            InsertOrIncr(root->right, val, incrVal);
        }
        else
        {
            root->sum += incrVal;
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
                res += root->leftSum + root->sum;
                root = root->right;
            }
            else
            {
                res += root->leftSum;//note: don't add root->sum to exclude cur node
                break;
            }
        }
        return res;
    }
public:
    std::string UseBinarySearchTree(std::string num, int k)
    {
        if (k <= 0) return num;
        int N = num.size();
        if (k >= (N - 1) * N / 2)
        {
            std::sort(num.begin(), num.end());
            return num;
        }
        TreeNode * root = NULL;
        //for (auto i = 0; i < N; ++i)
        //    InsertOrIncr(root, i, 0);
        std::vector<std::deque<int>> idx(10, std::deque<int>());
        for (auto i = 0; i < N; ++i)
            idx[num[i]-'0'].push_back(i);
        std::string res;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                if (!idx[j].empty() && idx[j].front()-SearchPrefixSum(root, idx[j].front()) <= k)
                {
                    res.push_back(j+'0');
                    InsertOrIncr(root, idx[j].front(), 1);
                    //increment cur and all prev digits' num of times being shifted to right
                    k -= idx[j].front() - SearchPrefixSum(root, idx[j].front());
                    idx[j].pop_front();
                    break;
                }
            }
        }
        return res;
    }
};
#endif
