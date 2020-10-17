#ifndef _SYNONYMOUS_SENTENCES_H
#define _SYNONYMOUS_SENTENCES_H
#include "Debug.h"
/*
Leetcode: Synonymous Setences
Given a list of pairs of equivalent words synonyms and a sentence text, Return all possible synonymous sentences sorted lexicographically.
Example 1:
Input:
synonyms = [["happy","joy"],["sad","sorrow"],["joy","cheerful"]],
text = "I am happy today but was sad yesterday"
Output:
["I am cheerful today but was sad yesterday",
"I am cheerful today but was sorrow yesterday",
"I am happy today but was sad yesterday",
"I am happy today but was sorrow yesterday",
"I am joy today but was sad yesterday",
"I am joy today but was sorrow yesterday"]
 */
class SynonymousSentences
{
    std::unordered_map<std::string, std::string> chdToP;
    std::unordered_map<std::string, std::unordered_set<std::string>> rootToChds;
public:
    std::vector<std::string> FindAll_UnionFind(std::vector<std::vector<std::string>>& synonyms, std::string text)
    {
        //init: O(N) time
        for (auto & p : synonyms)
        {
            chdToP[p[0]] = p[0];
            chdToP[p[1]] = p[1];
        }
        //UnionFind: O(NlogN) time
        for (auto & p : synonyms)
        {
            std::string root1 = Find(chdToP, p[0]);
            std::string root2 = Find(chdToP, p[1]);
            if (root1 != root2)
                chdToP[root2] = root1;
        }
        //Merge: O(NlogN) time
        for (auto & p : chdToP)
            rootToChds[Find(chdToP, p.second)].insert(p.first);

        std::vector<std::string> words;
        std::istringstream iss(text);
        std::string buf;
        while (getline(iss, buf, ' '))
            words.push_back(buf);
        std::vector<std::string> res;
        recur(words, 0, "", res);
        std::sort(res.begin(), res.end());
        return res;
    }
private:
    void recur(std::vector<std::string> & words, int cur, std::string curS, std::vector<std::string> & res)
    {
        int N = words.size();
        if (cur == N)
        {
            res.push_back(curS.substr(0, curS.size()-1));
            return;
        }
        if (!chdToP.count(words[cur]))
        {
            recur(words, cur+1, curS + words[cur] + " ", res);
            return;
        }
        std::string root = Find(chdToP, words[cur]);
        for (auto & s : rootToChds[root])
            recur(words, cur+1, curS + s + " ", res);
    }
    std::string Find(std::unordered_map<std::string,std::string> & chdToP, const std::string & s)
    {
        std::string cur = s;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
#endif
