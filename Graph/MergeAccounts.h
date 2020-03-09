/*Graph*/
#ifndef _MERGE_ACCOUNTS_H
#define _MERGE_ACCOUNTS_H
#include "Debug.h"
/*
Leetcode: Accounts Merge
Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name
, and the rest of the elements are emails representing emails of the account.
Now, we would like to merge these accounts.
Two accounts definitely belong to the same person if there is some email that is common to both accounts.
Note that even if two accounts have the same name, they may belong to different people as people could have the same name.
A person can have any number of accounts initially, but all of their accounts definitely have the same name.
After merging the accounts, return the accounts in the following format:
the first element of each account is the name, and the rest of the elements are emails in sorted order.
The accounts themselves can be returned in any order.
Example 1:
Input:
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation:
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
 */
class MergeAccounts
{
public:
    MergeAccounts(){}

    std::vector<std::vector<std::string>> UnionFind(const std::vector<std::vector<std::string>> & accounts)
    {
        std::unordered_map<std::string,std::string> toRoot;
        std::unordered_map<std::string,std::string> toOwner;
        std::unordered_map<std::string,std::set<std::string>> rootToChildren;
        std::vector<std::vector<std::string>> res;
        int N = accounts.size();
        //init
        for (int i = 0; i < N; ++i)
        {
            int M = accounts[i].size();
            for (int j = 1; j < M; ++j)
            {
                toRoot[accounts[i][j]] = accounts[i][j];//init toRoot
                toOwner[accounts[i][j]] = accounts[i][0];//init toOwner
            }
        }
        //perform union
        for (int i = 0; i < N; ++i)
        {
            int M = accounts[i].size();
            //union accounts[i][1]~accounts[i][M-1]
            std::string root1 = Find(toRoot, accounts[i][1]);
            for (int j = 2; j < M; ++j)
            {
                std::string root2 = Find(toRoot, accounts[i][j]);
                if (root1 != root2)
                    toRoot[root2] = root1;
            }
        }
        std::cout << "toRoot: " << Debug::ToStr1D<std::string>()(toRoot) << std::endl;
        //note: toRoot[i] maps to one of i's ancestor only, not necessarily to i's root !!!

        //classify root and children
        for (const auto & p : toRoot)
            rootToChildren[Find(toRoot, p.second)].insert(p.first);
        std::cout << "rootToChildren: " << std::endl;
        Debug::Print2D<std::string>()(rootToChildren);

        //output
        for (const auto & p : rootToChildren)
        {
            std::vector<std::string> cur;
            cur.push_back(toOwner[p.first]);
            cur.insert(cur.end(), p.second.begin(), p.second.end());
            res.push_back(cur);
        }

        Debug::Print2D<std::string>()(accounts, false);
        std::cout << "MergeAccounts UnionFind for above accounts:" << std::endl;
        Debug::Print2D<std::string>()(res, false);
        return res;
    }
private:
    std::string Find(std::unordered_map<std::string,std::string> & toRoot, const std::string & s)
    {
        std::string cur = s;
        while (toRoot[cur] != cur)
        {
            toRoot[cur] = toRoot[toRoot[cur]];
            cur = toRoot[cur];
        }
        return cur;
    }

public:
    std::vector<std::vector<int>> MergeSets_UnionFind(const std::vector<std::vector<int>> & sets)
    {
        std::unordered_map<int,int> chdToP;
        std::unordered_map<int,std::unordered_set<int>> rootToChildren;
        int N = sets.size();
        //init: O(N) time
        for (int i = 0; i < N; ++i)
        {
            int M = sets[i].size();
            for (int j = 0; j < M; ++j)
                chdToP[sets[i][j]] = sets[i][j];
        }
        //UnionFind: O(NlogN) time
        for (int i = 0; i < N; ++i)
        {
            int root1 = Find(chdToP, sets[i][0]);
            int M = sets[i].size();
            for (int j = 1; j < M; ++j)
            {
                int root2 = Find(chdToP, sets[i][j]);
                if (root2 != root1)
                    chdToP[root2] = root1;
            }
        }
        //Classify: O(NlogN) time
        for (const auto & p : chdToP)
            rootToChildren[Find(chdToP, p.second)].insert(p.first);

        std::vector<std::vector<int>> res;
        for (const auto & p : rootToChildren)
            res.push_back(std::vector<int>(p.second.begin(), p.second.end()));

        Debug::Print2D<int>()(rootToChildren);
        std::cout << "MergeSets UnionFind for sets=[" << Debug::ToStr1D<int>()(sets) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
private:
    int Find(std::unordered_map<int,int> & chdToP, int chd)//O(logN) time
    {
        int cur = chd;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
toRoot: [David4@m.co,David3@m.co], [David1@m.co,David0@m.co], [David2@m.co,David0@m.co], [David5@m.co,David3@m.co], [David3@m.co,David2@m.co], [David0@m.co,David0@m.co]
rootToChildren:
Row#0	= David0@m.co: David0@m.co, David1@m.co, David2@m.co, David3@m.co, David4@m.co, David5@m.co

[rY][cX]
Row#0	= David, David0@m.co, David1@m.co
Row#1	= David, David3@m.co, David4@m.co
Row#2	= David, David4@m.co, David5@m.co
Row#3	= David, David2@m.co, David3@m.co
Row#4	= David, David1@m.co, David2@m.co

MergeAccounts UnionFind for above accounts:
[rY][cX]
Row#0	= David, David0@m.co, David1@m.co, David2@m.co, David3@m.co, David4@m.co, David5@m.co


Row#0	= 2: 3, 4, 2, 1
Row#1	= 9: 9
Row#2	= 11: 7, 8, 6, 11, 5, 10

MergeSets UnionFind for sets=[[3,4], [2,3], [2,1], [7,8], [6,5,7], [9], [9], [11,10,5]]: [3,4,2,1], [9], [7,8,6,11,5,10]
 */
#endif
