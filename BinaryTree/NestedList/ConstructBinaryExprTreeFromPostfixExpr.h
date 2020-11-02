#ifndef _CONSTRUCT_BINARY_EXPR_TREE_FROM_POSTFIX_EXPR_H
#define _CONSTRUCT_BINARY_EXPR_TREE_FROM_POSTFIX_EXPR_H
#include "Debug.h"
/*
Leetcode: Design an Expression Tree With Evaluate Function
Given the postfix tokens of an arithmetic expression, build and return the binary expression tree that represents this expression.
Postfix notation is a notation for writing arithmetic expressions in which the operands (numbers) appear before their operators.
For example, the postfix tokens of the expression 4*(5-(2+7)) are represented in the array postfix = ["4","5","7","2","+","-","*"].
The class Node is an interface you should use to implement the binary expression tree.
The returned tree will be tested using the evaluate function, which is supposed to evaluate the tree's value.
You should not remove the Node class; however, you can modify it as you wish, and you can define other classes to implement it if needed.
A binary expression tree is a kind of binary tree used to represent arithmetic expressions.
Each node of a binary expression tree has either zero or two children.
Leaf nodes (nodes with 0 children) correspond to operands (numbers), and internal nodes (nodes with two children) correspond to the operators '+' (addition), '-' (subtraction), '*' (multiplication), and '/' (division).
It's guaranteed that no subtree will yield a value that exceeds 109 in absolute value, and all the operations are valid (i.e., no division by zero).

Follow up: Could you design the expression tree such that it is more modular? For example, is your design able to support additional operators without making changes to your existing evaluate implementation?

Example 1:
Input: s = ["3","4","+","2","*","7","/"]
Output: 2
Explanation: this expression evaluates to the above binary tree with expression ((3+4)*2)/7) = 14/7 = 2.
Example 2:
Input: s = ["4","5","7","2","+","-","*"]
Output: -16
Explanation: this expression evaluates to the above binary tree with expression 4*(5-(2+7)) = 4*(-4) = -16.
Example 3:
Input: s = ["4","2","+","3","5","1","-","*","+"]
Output: 18
Example 4:
Input: s = ["100","200","+","2","/","5","*","7","+"]
Output: 757
 */
class ConstructBinaryExprTreeFromPostfixExpr
{
public:
    class TreeNode
    {
    public:
        TreeNode(int val) : val(val), op(0), left(NULL), right(NULL) {}
        TreeNode(char ch, TreeNode * left, TreeNode * right) : val(0), op(ch), left(left), right(right) {}
        virtual int evaluate()
        {
            if (op == 0)
                return val;
            int resL = left->evaluate();
            int resR = right->evaluate();
            return op == '+' ? resL+resR : op == '-' ? resL-resR : op == '*' ? resL*resR : resL/resR;
        }
    protected:
        TreeNode *left, *right;;
        int val;
        char op;
    };

    TreeNode* UseStack(std::vector<std::string> & postfix)
    {
        std::vector<TreeNode*> stk;
        for (auto & s : postfix)
        {
            if (!isdigit(s[0]))//+,-,*,/
            {
                TreeNode * right = stk.back(); stk.pop_back();
                TreeNode * left = stk.back(); stk.pop_back();
                stk.push_back(new TreeNode(s[0],left,right));
            }
            else
                stk.push_back(new TreeNode(stoi(s)));
        }
        return stk.back();
    }
};
#endif
