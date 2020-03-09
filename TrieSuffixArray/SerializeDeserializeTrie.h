#ifndef _SERIALIZE_DESERIALIZE_TRIE_H
#define _SERIALIZE_DESERIALIZE_TRIE_H
#include "Debug.h"
/*
Grokking the system design interview: Design Typeahead Suggestion
 */
class SerializeDeserializeTrie
{
public:
    struct Trie
    {
        Trie() :children(26, NULL) {}
        std::vector<Trie*> children;
    };

public:
    SerializeDeserializeTrie()
    {

    }
    Trie * Construct(Trie * root, const std::vector<std::string> & v)
    {
        for (const auto & s : v)
            Insert(root, s);
        return root;
    }
    void Insert(Trie * root, const std::string & s)
    {
        int N = s.size();
        int cur = 0;
        while (true)
        {
            if (!root->children[s[cur]-'a'])
                root->children[s[cur]-'a'] = new Trie;
            if (cur == N - 1)
                break;
            root = root->children[s[cur]-'a'];
            ++cur;
        }
    }

    std::string Serialize(Trie * root)
    {
        std::string res = recur(root, '~');
        std::cout << "SerializeDeserializeTrie Serialize: " << res << std::endl;
        return res;
    }
    std::string recur(Trie * cur, char c)
    {
        std::string res(1, c);
        int count = 0;
        for (int i = 0; i < 26; ++i)
            if (cur->children[i] != NULL) ++count;
        res += std::to_string(count);
        for (int i = 0; i < 26; ++i)
        {
            if (cur->children[i] == NULL) continue;
            res.push_back(',');
            res += recur(cur->children[i], 'a'+i);
        }
        return res;
    }

    Trie * Deserialize(const std::string & s)
    {
        int i = 0;
        return recur(s, i).second;
    }
    std::pair<char, Trie*> recur(const std::string & s, int & i)
    {
        int N = s.size();
        Trie * cur = NULL;
        char c;
        int count = 0;
        while (i < N)
        {
            if ((s[i] >= 'a' && s[i] <= 'z') || s[i] == '~')
            {
                c = s[i];
                cur = new Trie;
                ++i;
            }
            else if (s[i] == ',')
            {
                while (count--)
                {
                    auto p = recur(s, ++i);
                    cur->children[p.first-'a'] = p.second;
                }
                return {c,cur};
            }
            else//digit
            {
                int begin = i;
                while (i < N && isdigit(s[i]))
                    ++i;
                count = stoi(s.substr(begin, i-begin));
            }
        }
        return {c,cur};
    };
};
/*
SerializeDeserializeTrie Serialize: ~2,c2,a2,p2,i1,t1,a1,l0,t2,a1,i1,n0,i1,o1,n0,t0,i2,s1,c1,o0,t2,a1,d1,e1,l0,y0,g1,o1,o3,d1,b1,y1,e0,g1,l1,e0,s1,e0
SerializeDeserializeTrie Serialize: ~2,c2,a2,p2,i1,t1,a1,l0,t2,a1,i1,n0,i1,o1,n0,t0,i2,s1,c1,o0,t2,a1,d1,e1,l0,y0,g1,o1,o3,d1,b1,y1,e0,g1,l1,e0,s1,e0
 */
#endif
