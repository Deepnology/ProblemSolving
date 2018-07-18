#ifndef _INSERT_NODE_CYCLIC_SORTED_LINKED_LIST_H
#define _INSERT_NODE_CYCLIC_SORTED_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Insert into a cyclic sorted list
Given a node from a cyclic linked list which is sorted in ascending order,
 write a function to insert a value into the list such that it remains a cyclic sorted list.
The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the cyclic list.
If there are multiple suitable places for insertion, you may choose any place to insert the new value.
After the insertion, the cyclic list should remain sorted.
If the list is empty (i.e., given node is null), you should create a new single cyclic list and return the reference to that single node.
Otherwise, you should return the original given node.
 */
class InsertNodeCyclicSortedLinkedList
{
public:
    InsertNodeCyclicSortedLinkedList(){}

    class ListNode
    {
    public:
        int val;
        ListNode * next;
        ListNode() {}
        ListNode(int _val, ListNode * _next = NULL)
        {
            val = _val;
            next = _next;
        }
    };

    ListNode * FindMinInsert(ListNode * head, int insertVal)
    {
        ListNode * tgt = new ListNode(insertVal);
        if (head == NULL)
        {
            tgt->next = tgt;
            return tgt;
        }
        ListNode * cur = head;
        while (cur->next != head && cur->val <= cur->next->val)
            cur = cur->next;
        //now cur is max
        ListNode * max = cur;
        ListNode * min = cur->next;
        //break cycle, add dummy
        max->next = NULL;
        ListNode * dummy = new ListNode(INT_MIN);
        dummy->next = min;
        cur = dummy;
        while (cur->next && cur->next->val < tgt->val)
            cur = cur->next;
        //now insert new node to cur->next
        tgt->next = cur->next;
        cur->next = tgt;
        if (max == cur) max = max->next;
        max->next = dummy->next;
        delete dummy;
        return head;
    }

    ListNode * WithoutFindMin(ListNode * head, int insertVal)
    {
        ListNode * tgt = new ListNode(insertVal);
        if (head == NULL)
        {
            tgt->next = tgt;
            return tgt;
        }
        ListNode * cur = head;
        while (true)
        {
            if (cur->val < cur->next->val)
            {
                if (cur->val <= tgt->val && tgt->val <= cur->next->val)
                {
                    tgt->next = cur->next;
                    cur->next = tgt;
                    break;
                }
            }
            else if (cur->val > cur->next->val)//cur is max, cur->next is min
            {
                if (cur->val <= tgt->val || tgt->val <= cur->next->val)//tgt is max OR tgt is min
                {
                    tgt->next = cur->next;
                    cur->next = tgt;
                    break;
                }
            }
            else//all flat
            {
                if (cur->next == head)
                {
                    tgt->next = cur->next;
                    cur->next = tgt;
                    break;
                }
            }
            cur = cur->next;
        }
        return head;
    }
};
#endif
