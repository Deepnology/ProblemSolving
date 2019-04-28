#ifndef _CONNECTED_COMPONENTS_BY_STR_SWAP_2_CHARS_H
#define _CONNECTED_COMPONENTS_BY_STR_SWAP_2_CHARS_H
#include "Debug.h"
/*
Leetcode: Similar String Groups
Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.
For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.
Notice that "tars" and "arts" are in the same group even though they are not similar.
Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
We are given a list A of strings.
Every string in A is an anagram of every other string in A.
How many groups are there?
Example 1:
Input: ["tars","rats","arts","star"]
Output: 2
 */
class ConnectedComponentsByStrSwap2Chars
{
public:
    ConnectedComponentsByStrSwap2Chars(){}

    //strings are in the same group as long as there is a path of similarity thru all strings
    //not necessarily each pair of strings must be similar
    int BFS(std::vector<std::string> && A)
    {
        //BFS: O(NM^2) time
        std::unordered_set<std::string> nonVisit(A.begin(),A.end());
        int N = A.size();
        int res = 0;
        while (!nonVisit.empty())
        {
            ++res;
            std::string cur = *nonVisit.begin();
            nonVisit.erase(cur);
            std::queue<std::string> que;
            que.push(cur);
            while (!que.empty())
            {
                cur = que.front();
                que.pop();
                int M = cur.size();
                for (int i = 0; i < M-1; ++i)
                    for (int j = i+1; j < M; ++j)
                    {
                        if (cur[i] == cur[j]) continue;
                        std::swap(cur[i], cur[j]);
                        if (nonVisit.count(cur))
                        {
                            nonVisit.erase(cur);
                            que.push(cur);
                        }
                        std::swap(cur[i], cur[j]);
                    }
            }
        }
        std::cout << "ConnectedComponentsByStrSwap2Chars BFS for [" << Debug::ToStr1D<std::string>()(A) << "]: " << res << std::endl;
        return res;
    }
    int DFS(std::vector<std::string> && A)
    {
        //DFS: O(N!M) time
        std::unordered_set<std::string> visit;
        int res = 0;
        int N = A.size();
        for (int i = 0; i < N; ++i)
        {
            if (!visit.count(A[i]))
            {
                visit.insert(A[i]);
                ++res;
                DFS(A, i+1, A[i], visit);
            }
        }
        std::cout << "ConnectedComponentsByStrSwap2Chars DFS for [" << Debug::ToStr1D<std::string>()(A) << "]: " << res << std::endl;
        return res;
    }
    int UnionFind(std::vector<std::string> && A)
    {
        //UnionFind: O(N^2logNM) time
        std::unordered_map<std::string,std::string> chdToP;
        for (auto & s : A)
            chdToP.insert({s,s});
        int N = A.size();
        int countComponent = chdToP.size();
        for (int i = 0; i < N-1; ++i)
            for (int j = i+1; j < N; ++j)
            {
                if (Similar(A[i], A[j]))
                {
                    std::string root1 = Find(chdToP, A[i]);
                    std::string root2 = Find(chdToP, A[j]);
                    if (root1 != root2)
                    {
                        chdToP[root2] = root1;
                        --countComponent;
                    }
                }
            }
        std::cout << "ConnectedComponentsByStrSwap2Chars UnionFind for [" << Debug::ToStr1D<std::string>()(A) << "]: " << countComponent << std::endl;
        return countComponent;
    }
private:
    void DFS(std::vector<std::string> & A, int begin, std::string cur, std::unordered_set<std::string> & visit)
    {
        int N = A.size();
        for (int i = begin; i < N; ++i)
        {
            if (!visit.count(A[i]) && Similar(cur, A[i]))
            {
                visit.insert(A[i]);
                DFS(A, begin, A[i], visit);
            }
        }
    }
    bool Similar(std::string & a, std::string & b)
    {
        int N = a.size();
        int diff = 0;
        int d1, d2;
        for (int i = 0; i < N; ++i)
        {
            if (a[i] != b[i])
            {
                ++diff;
                if (diff > 2) return false;
                else if (diff == 2) d2 = i;
                else d1 = i;
            }
        }
        return diff == 2 && a[d1] == b[d2] && a[d2] == b[d1];
    }
    std::string Find(std::unordered_map<std::string,std::string> & chdToP, std::string chd)
    {
        std::string cur = chd;
        while(chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
ConnectedComponentsByStrSwap2Chars DFS for [tars, rats, arts, star]: 2
ConnectedComponentsByStrSwap2Chars BFS for [tars, rats, arts, star]: 2
ConnectedComponentsByStrSwap2Chars UnionFind for [tars, rats, arts, star]: 2
 */
#endif
