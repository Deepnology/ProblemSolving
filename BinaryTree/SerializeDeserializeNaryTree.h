#ifndef _SERIALIZE_DESERIALIZE_NARY_TREE_H
#define _SERIALIZE_DESERIALIZE_NARY_TREE_H
#include "Debug.h"
/*
Leetcode: Serialize and Deserialize N-ary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that
it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed
later in the same or another computer environment.
Design an algorithm to serialize and deserialize an N-ary tree.
An N-ary tree is a rooted tree in which each node has no more than N children.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.
 */
class SerializeDeserializeNaryTree
{
public:
    SerializeDeserializeNaryTree(){}
    struct Node
    {
        int val;
        std::vector<Node*> children;
        Node(int v):val(v), children(){}
    };

    std::string Serialize(Node * root)
    {
        std::string res = recur(root);
        return res;
    }
    std::string recur(Node * cur)
    {
        if (cur == NULL) return "";
        std::string res = std::to_string(cur->val);
        if (cur->children.empty())
            return res;
        res += "(";
        int N = cur->children.size();
        for (int i = 0; i < N; ++i)
        {
            res += recur(cur->children[i]);
            if (i != N-1)
                res += ',';
        }
        res += ")";
        return res;
    }

    Node * Deserialize(std::string data)
    {
        if (data.empty()) return NULL;
        int i = 0;
        std::vector<Node *> roots = recur(data, i);
        return roots[0];
    }
    std::vector<Node *> recur(std::string & s, int & i)
    {
        int N = s.size();
        std::vector<Node *> cur;
        while (i < N)
        {
            if (s[i] == ',')
            {
                ++i;
            }
            else if (s[i] == ')')
            {
                ++i;
                return cur;
            }
            else if (s[i] == '(')//child level nodes: add to last node in cur level
            {
                std::vector<Node *> chd = recur(s, ++i);
                cur.back()->children.insert(cur.back()->children.end(), chd.begin(), chd.end());
            }
            else//same level nodes: add to cur vec
            {
                int begin = i;
                while (i < N && isdigit(s[i]))
                    ++i;
                cur.push_back(new Node(stoi(s.substr(begin,i-begin))));
            }
        }
        return cur;
    }
};
#endif
