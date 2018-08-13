#ifndef _CRACK_SAFE_H
#define _CRACK_SAFE_H
#include "Debug.h"
/*
Leetcode: Cracking the Safe
There is a box protected by a password. The password is n digits, where each letter can be one of the first k digits 0, 1, ..., k-1.
You can keep inputting the password, the password will automatically be matched against the last n digits entered.
For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.
Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.
Example 1:
Input: n = 1, k = 2
Output: "01"
Note: "10" will be accepted too.
Example 2:
Input: n = 2, k = 2
Output: "00110"
Note: "01100", "10011", "11001" will be accepted too.
Note:
n will be in the range [1, 4].
k will be in the range [1, 10].
k^n will be at most 4096.

"a de Bruijn sequence of order n on a size-k alphabet A is a cyclic sequence in which every possible length-n string on A occurs exactly once as a substring".
The De Brujin sequence has length k^n.
"The de Bruijn sequences can be constructed by taking a Hamiltonian path of an n-dimensional de Bruijn graph over k symbols (or equivalently, an Eulerian cycle of an (n − 1)-dimensional de Bruijn graph)."
Use Hierholzer's Algorithm to construct the Eulerian circuit.
 */
class CrackSafe
{
public:
    CrackSafe(){}

    std::string deBruijnSeq(int n, int k) //generate a sequence of all possible combinations of n digits with nums in [0:k-1]
    {//where a consecutive subsequence with n digits is a valid combination
        std::string res(n, '0');
        std::unordered_set<std::string> visit;//visited nodes
        visit.insert(res);
        int total = pow(k, n);//total num combinations for n digits in [0:k-1]
        recur(res, n, k, total, visit);
        std::cout << "CrackSafe deBruijinSeq for " << n << " digits in [0:" << k-1 << "]: " << res << std::endl;
        return res;
    }
private:
    bool recur(std::string & res, int n, int k, int total, std::unordered_set<std::string> & visit)
    {
        if (visit.size() == total) return true;
        std::string curNode = res.substr(res.size()-n+1);//last n-1 digits can re-used
        for (int nxt = 0; nxt < k; ++nxt)
        {
            std::string nxtNode = curNode;
            nxtNode.push_back(nxt+'0');
            if (visit.count(nxtNode)) continue;
            visit.insert(nxtNode);
            res.push_back(nxt+'0');
            if (recur(res, n, k, total, visit)) return true;
            res.pop_back();
            visit.erase(nxtNode);
        }
        return false;
    }
};
/*
CrackSafe deBruijinSeq for 2 digits in [0:1]: 00110
CrackSafe deBruijinSeq for 3 digits in [0:2]: 00010020110120210221112122200
 */
#endif
