#ifndef _KTH_SYMBOL_IN_GRAMMAR_H
#define _KTH_SYMBOL_IN_GRAMMAR_H
/*
Leetcode: Kth Symbol in Grammar
On the first row, we write a 0.
Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.
Given row N and index K, return the K-th indexed symbol in row N. (The values of K are 1-indexed.) (1 indexed).
Examples:
Input: N = 1, K = 1
Output: 0
Input: N = 2, K = 1
Output: 0
Input: N = 2, K = 2
Output: 1
Input: N = 4, K = 5
Output: 1
Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001
 */
class KthSymbolInGrammar
{
public:
    KthSymbolInGrammar(){}

    int Recur(int N, int K) //o(logK) time
    {
        int res = recur(K-1); //change to 0-based

        std::cout << "KthSymbolInGrammar Recur for " << N << "-th row " << K << "-th bit: " << res << std::endl;
        return res;
    }
    int recur(int k) //k is 0-based
    {
        if (k==0) return 0;
        if (k%2==0) return recur(k/2); //kth bit is equal to k/2th bit in prev row
        return recur(k/2)^1; //kth bit is equal to k/2th bit's flip in prev row
    }
};
/*
KthSymbolInGrammar Recur for 4-th row 5-th bit: 1
 */
#endif
