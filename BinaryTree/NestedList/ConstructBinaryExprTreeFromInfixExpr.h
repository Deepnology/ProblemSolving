#ifndef _CONSTRUCT_BINARY_EXPR_TREE_FROM_INFIX_EXPR_H
#define _CONSTRUCT_BINARY_EXPR_TREE_FROM_INFIX_EXPR_H
#include "Debug.h"
/*
Leetcode: Build Binary Expression Tree From Infix Expression
A binary expression tree is a kind of binary tree used to represent arithmetic expressions.
Each node of a binary expression tree has either zero or two children.
Leaf nodes (nodes with 0 children) correspond to operands (numbers)
 , and internal nodes (nodes with 2 children) correspond to the operators '+' (addition), '-' (subtraction), '*' (multiplication), and '/' (division).
For each internal node with operator o, the infix expression that it represents is (A o B)
 , where A is the expression the left subtree represents and B is the expression the right subtree represents.
You are given a string s, an infix expression containing operands, the operators described above, and parentheses '(' and ')'.
Return any valid binary expression tree, which its in-order traversal reproduces s after omitting the parenthesis from it (see examples below).
Please note that order of operations applies in s.
That is, expressions in parentheses are evaluated first, and multiplication and division happen before addition and subtraction.
Operands must also appear in the same order in both s and the in-order traversal of the tree.
 */
class ConstructBinaryExprTreeFromInfixExpr
{
public:
    struct TreeNode
    {
        TreeNode() : val(' '), left(nullptr), right(nullptr) {}
        TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(char x, TreeNode * left, TreeNode *right) : val(x), left(left), right(right) {}
        char val;
        TreeNode * left;
        TreeNode * right;
    };
    TreeNode * Recur(std::string s)
    {
        int i = 0;
        return recur(s, i);
    }
private:
    TreeNode * recur(const std::string & s, int & i)
    {
        int N = s.size();
        std::vector<TreeNode*> nodeStk;
        std::vector<char> opStk;
        while (i < N)
        {
            if (s[i] == ')')
            {
                ++i;
                break;
            }
            else if (s[i] == '(')
            {
                nodeStk.push_back(recur(s, ++i));
            }
            else if (isdigit(s[i]))
            {
                nodeStk.push_back(new TreeNode(s[i++]));
            }
            else //+,-,*,/
            {
                while (nodeStk.size()>=2 && !opStk.empty() && (opStk.back()=='*'||opStk.back()=='/'||s[i]=='+'||s[i]=='-'))
                {
                    TreeNode * right = nodeStk.back(); nodeStk.pop_back();
                    TreeNode * left = nodeStk.back(); nodeStk.pop_back();
                    char op = opStk.back(); opStk.pop_back();
                    nodeStk.push_back(new TreeNode(op, left, right));
                }
                opStk.push_back(s[i++]);
            }
        }
        while (nodeStk.size()>=2 && !opStk.empty())
        {
            TreeNode * right = nodeStk.back(); nodeStk.pop_back();
            TreeNode * left = nodeStk.back(); nodeStk.pop_back();
            char op = opStk.back(); opStk.pop_back();
            nodeStk.push_back(new TreeNode(op, left, right));
        }
        return nodeStk.back();
    }
};
#endif
