/*Facebook*/
#ifndef _LIST_OF_NODES_FORM_BINARY_TREE_H
#define _LIST_OF_NODES_FORM_BINARY_TREE_H
#include "Debug.h"
/*
Given a list of nodes, determine if all nodes can form a binary tree.
Leetcode: Validate Binary Tree Nodes
You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
Note that the nodes have no values and that we only use the node numbers in this problem.
 */
class ListOfNodesFormBinaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    ListOfNodesFormBinaryTree(){}

    bool Validate1(const std::vector<TreeNode *> & nodes)
    {
        //actually we just need unordered_set<TreeNode *> chd;
        std::unordered_map<TreeNode *, TreeNode *> chdToP;//<child, parent>
        int N = nodes.size();
        for (int i = 0; i < N; ++i)
        {
            TreeNode * cur = nodes[i];
            if (cur->left)
            {
                if (chdToP.count(cur->left))//cur->left has 2 parents
                {
                    std::cout << "ListOfNodesFromBinaryTree: False(" << cur->left->val << " has 2 parents)" << std::endl;
                    return false;
                }
                chdToP[cur->left] = cur;
            }
            if (cur->right)
            {
                if (chdToP.count(cur->right))//cur->right has 2 parents
                {
                    std::cout << "ListOfNodesFromBinaryTree: False(" << cur->right->val << " has 2 parents)" << std::endl;
                    return false;
                }
                chdToP[cur->right] = cur;
            }
        }
        //now chdToP contains all nodes except root(s)
        TreeNode * root = NULL;
        for (int i = 0; i < N; ++i)
        {
            if (chdToP.count(nodes[i])) continue;//nodes[i] is not root
            if (root)
            {
                std::cout << "ListOfNodesFromBinaryTree: False(Found 2nd root: " << root->val << ", " << nodes[i]->val << ")" << std::endl;
                return false;//found a 2nd root
            }
            root = nodes[i];
        }
        if (root == NULL) return false;
        //now we have 1 root, but we might have a situation where 1 tree w/ cycle and w/o root and 1 tree w/o cycle

        int numComponent = N;
        std::unordered_map<TreeNode*,TreeNode*> chdToP2;
        for (int i = 0; i < N; ++i)
            chdToP2[nodes[i]] = nodes[i];
        for (int i = 0; i < N; ++i)
        {
            if (chdToP[nodes[i]] == NULL) continue;
            TreeNode * root1 = Find(chdToP2, nodes[i]);
            TreeNode * root2 = Find(chdToP2, chdToP[nodes[i]]);
            if (root1 != root2)
            {
                chdToP2[root1] = root2;
                --numComponent;
            }
            else
                return false;//found a cycle
        }
        std::cout << "ListOfNodesFromBinaryTree: True(root: " << root->val << ")" << std::endl;
        return true;
    }

    bool Validate2(int n, std::vector<int>& leftChild, std::vector<int>& rightChild)
    {
        std::vector<int> chdToP(n, -1);
        for (int i = 0; i < n; ++i)
        {
            int cur = i;
            int left = leftChild[cur];
            int right = rightChild[cur];
            if (left != -1)
            {
                if (chdToP[left] != -1) return false;
                chdToP[left] = cur;
            }
            if (right != -1)
            {
                if (chdToP[right] != -1) return false;
                chdToP[right] = cur;
            }
        }
        int root = -1;
        for (int i = 0; i < n; ++i)
        {
            if (root == -1 && chdToP[i] == -1)
                root = i;
            else if (root != -1 && chdToP[i] == -1)//found 2nd root
                return false;
        }
        if (root == -1) return false;//found no root
        /*
        now we have 1 root, but we might have a situation where 1 tree w/ cycle and w/o root and 1 tree w/o cycle
        ex: 4, [1,0,3,-1], [-1,-1,-1,-1]
        */
        int numComponent = n;
        std::vector<int> chdToP2;
        for (int i = 0; i < n; ++i)
            chdToP2.push_back(i);
        for (int i = 0; i < n; ++i)
        {
            if (chdToP[i] == -1) continue;
            int root1 = Find(chdToP2, i);
            int root2 = Find(chdToP2, chdToP[i]);
            if (root1 != root2)
            {
                chdToP2[root1] = root2;
                --numComponent;
            }
            else
                return false;//found a cycle
        }
        return true;
    }
private:
    TreeNode * Find(std::unordered_map<TreeNode*,TreeNode*> & chdToP, TreeNode * cur)
    {
        while (cur != chdToP[cur])
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
    int Find(std::vector<int> & chdToP, int cur)
    {
        while (cur != chdToP[cur])
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
public:
    static void DeleteTree(TreeNode * root)
    {
        if (root == 0)
            return;

        DeleteTree(root->left);
        DeleteTree(root->right);

        //post order
        delete root;
        root = 0;
    }
};
/*
 1
 0


ListOfNodesFromBinaryTree: True(root: 0)

 1
 0


 1
 1


ListOfNodesFromBinaryTree: False(Found 2nd root: 0, 1)

   1
   0
 /   \
 2   2
 2   3


ListOfNodesFromBinaryTree: True(root: 0)

   1
   0
 /   \
 2   2
 2   3


   1
   1
 /   \
 2   X
 3   N


ListOfNodesFromBinaryTree: False(3 has 2 parents)
 */
#endif
