#ifndef _NEXT_GREATER_NODE_IN_LINKED_LIST_H
#define _NEXT_GREATER_NODE_IN_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Next Greater Node in Linked List
We are given a linked list with head as the first node.
Let's number the nodes in the list: node_1, node_2, node_3, ... etc.
Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.
If such a j does not exist, the next larger value is 0.
Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).
Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2, second node value of 1, and third node value of 5.
Example 1:
Input: [2,1,5]
Output: [5,5,0]
Example 2:
Input: [2,7,4,3,5]
Output: [7,0,5,5,0]
Example 3:
Input: [1,7,5,1,9,2,5,1]
Output: [7,9,9,9,0,5,0,0]
 */
class NextGreaterNodeInLinkedList
{
public:
    NextGreaterNodeInLinkedList(){}

    struct ListNode
    {
        ListNode(int v): val(v), next(0){}
        int val;
        ListNode * next;
    };

    std::vector<int> UseStack(ListNode* head)
    {
        std::vector<int> res;
        std::stack<int> stk;
        for (auto cur = head; cur; cur = cur->next)
        {
            while (!stk.empty() && res[stk.top()] < cur->val)
            {
                res[stk.top()] = cur->val;
                stk.pop();
            }
            stk.push(res.size());//cur idx
            res.push_back(cur->val);//cur val
        }
        while (!stk.empty())
        {
            res[stk.top()] = 0;//set vals that don't have next right greater nodes to 0s
            stk.pop();
        }
        std::cout << "NextGreaterNodeInLinkedList UseStack: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

public:
    static void DeleteLinkedList(ListNode * head)
    {
        std::unordered_set<ListNode *> map;
        while (head != NULL)
        {
            if (map.find(head) == map.end())//doesn't exist
            {
                map.insert(head);
                head = head->next;
            }
            else//already exist
            {
                break;
            }
        }
        for (std::unordered_set<ListNode *>::iterator i = map.begin(); i != map.end(); ++i)
        {
            //std::cout << "DeleteListNode: " << (*i)->val << std::endl;
            delete *i;
        }
    }
};
/*
[0,1]->[1,7]->[2,5]->[3,1]->[4,9]->[5,2]->[6,5]->[7,1]->NULL

NextGreaterNodeInLinkedList UseStack: 7, 9, 9, 9, 0, 5, 0, 0
 */
#endif
