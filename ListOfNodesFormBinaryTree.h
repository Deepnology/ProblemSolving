/*Facebook*/
#ifndef _LIST_OF_NODES_FORM_BINARY_TREE_H
#define _LIST_OF_NODES_FORM_BINARY_TREE_H
#include "Debug.h"
/*
Given a list of nodes, determine if all nodes can form a binary tree.
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

    bool HashSet(const std::vector<TreeNode *> & nodes)
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
        //now found a single root and all children
        std::cout << "ListOfNodesFromBinaryTree: True(root: " << root->val << ")" << std::endl;
        return true;
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
