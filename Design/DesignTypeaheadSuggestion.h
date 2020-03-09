#ifndef _DESIGN_TYPEAHEAD_SUGGESTION_H
#define _DESIGN_TYPEAHEAD_SUGGESTION_H
#include "Debug.h"
/*
Grokking the system design interview: Design Typeahead Suggestion
Leetcode: Design Search Autocomplete System
 */
class DesignTypeaheadSuggestion
{
    struct Trie
    {
        Trie():children(27,NULL),topK(),parent(NULL),c('~'),isKey(false),times(0){}
        std::vector<Trie*> children;
        std::vector<Trie*> topK;
        Trie * parent;
        char c;
        bool isKey;
        int times;
    };
    Trie * _root;
    std::string history;

    int Idx(char c)
    {
        if (c == ' ') return 26;
        return c-'a';
    }
    char Char(int i)
    {
        if (i == 26) return ' ';
        return i+'a';
    }
    void Insert(Trie * root, const std::string & s, int times)
    {
        if (s.empty()) return;
        insertRecur(root, s, 0, times, root, '~');
    }
    std::vector<Trie*> insertRecur(Trie *& cur, const std::string & s, int begin, int times, Trie * parent, char c)
    {
        if (cur == NULL)
        {
            cur = new Trie;
            cur->parent = parent;
            cur->c = c;
        }
        if (begin == (int)s.size())
        {
            cur->isKey = true;
            cur->times += times;
            cur->topK = merge(cur->topK, std::vector<Trie*>({cur}));
            return cur->topK;
        }
        auto childrenTopK = insertRecur(cur->children[Idx(s[begin])], s, begin+1, times, cur, s[begin]);
        cur->topK = merge(cur->topK, childrenTopK);
        return cur->topK;
    }
    void printRecur(Trie * cur, std::string & s, int depth)
    {
        if (cur == NULL) return;
        s.push_back(cur->c);
        std::cout << s.substr(0, depth) << ": ";
        for (const auto & t : cur->topK)
            std::cout << getStr(_root, t) << ",";
        std::cout << std::endl;
        for (int i = 0; i < 27; ++i)
            if (cur->children[i])
                printRecur(cur->children[i], s, depth+1);
        s.pop_back();
    }
    bool lexSmaller(Trie * t1, Trie * t2)
    {
        /*
        std::string a = getStr(_root, t1);
        std::string b = getStr(_root, t2);
        return a<b;
        */
        /*
        std::unordered_set<Trie*> visit;
        Trie * LCA;
        std::queue<Trie*> que;
        que.push(t1);
        que.push(t2);
        while (!que.empty())
        {
            Trie * cur = que.front(); que.pop();
            if (visit.count(cur))
            {
                LCA = cur;
                break;
            }
            visit.insert(cur);
            if (cur->parent)
                que.push(cur->parent);
        }
        if (LCA == t1) return true;
        if (LCA == t2) return false;
        char c1 = t1->c;
        char c2 = t2->c;
        while (t1 != LCA)
        {
            c1 = t1->c;
            t1 = t1->parent;
        }
        while (t2 != LCA)
        {
            c2 = t2->c;
            t2 = t2->parent;
        }
        return c1 < c2;
        */
        std::unordered_set<Trie*> visit;
        Trie * cur1 = t1; Trie * cur2 = t2;
        Trie * LCA;
        while (cur1 || cur2)
        {
            if (cur1)
            {
                if (visit.count(cur1))
                {
                    LCA = cur1;
                    break;
                }
                visit.insert(cur1);
                cur1 = cur1->parent;
            }
            if (cur2)
            {
                if (visit.count(cur2))
                {
                    LCA = cur2;
                    break;
                }
                visit.insert(cur2);
                cur2 = cur2->parent;
            }
        }
        if (LCA == t1) return true;
        if (LCA == t2) return false;
        char c1 = t1->c;
        char c2 = t2->c;
        while (t1 != LCA)
        {
            c1 = t1->c;
            t1 = t1->parent;
        }
        while (t2 != LCA)
        {
            c2 = t2->c;
            t2 = t2->parent;
        }
        return c1 < c2;
    }
    std::vector<Trie*> merge(const std::vector<Trie*> & v1, const std::vector<Trie*> & v2)
    {
        //apart from the current updated node, there still might be other duplicated nodes in v1 and v2
        std::unordered_set<Trie*> set;
        for (const auto & t : v1) set.insert(t);
        for (const auto & t : v2) set.insert(t);
        std::vector<Trie*> res(set.begin(), set.end());
        int N = res.size();
        for (int i = 1; i < N; ++i)//insertion sort
        {
            auto cur = res[i];
            int j;
            for (j = i; j > 0 && (res[j-1]->times < cur->times
                || (res[j-1]->times==cur->times && lexSmaller(cur,res[j-1]))); --j)
                res[j] = res[j-1];//right shift
            res[j] = cur;
        }
        if (res.size() > 3)
            res.resize(3);
        return res;
    }

    std::string getStr(Trie * root, Trie * cur)
    {
        std::string res;
        while (cur != root)
        {
            res.push_back(cur->c);
            cur = cur->parent;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
    std::vector<std::string> getTopK(Trie * root, const std::string & s)
    {
        int begin = 0;
        Trie * cur = root;
        int N = s.size();
        while (begin < N)
        {
            if (!cur->children[Idx(s[begin])])
                return std::vector<std::string>();
            cur = cur->children[Idx(s[begin])];
            ++begin;
        }
        //now found target node
        std::vector<std::string> res;
        for (const auto & t : cur->topK)
            res.push_back(getStr(root, t));
        return res;
    }

public:
    DesignTypeaheadSuggestion(std::vector<std::string> sentences, std::vector<int> times) : _root(0), history()
    {
        _root = new Trie;
        int N = sentences.size();
        for (int i = 0; i < N; ++i)
            Insert(_root, sentences[i], times[i]);
    }

    std::vector<std::string> input(char c)
    {
        if (c != '#')
        {
            history.push_back(c);
            return getTopK(_root, history);
        }
        else
        {
            if (!history.empty())
            {
                Insert(_root, history, 1);
                history.clear();
            }
            return std::vector<std::string>();
        }
    }
};
#endif
