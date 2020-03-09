#ifndef _IMPLEMENT_LINKED_LIST_H
#define _IMPLEMENT_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Design Linked List
Design your implementation of the linked list.
You can choose to use the singly linked list or the doubly linked list. A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list.
Assume all nodes in the linked list are 0-indexed.
Implement these functions in your linked list class:
get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.
addAtHead(val) : Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
addAtTail(val) : Append a node of value val to the last element of the linked list.
addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
Example:
MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3
 */
class MyLinkedList
{
    struct ListNode
    {
        int val;
        ListNode * next;
        ListNode * pre;
        ListNode(int v): val(v), next(NULL), pre(NULL){}
    };
    int m_size;
    ListNode * m_head;
    ListNode * m_tail;
public:
    /** Initialize your data structure here. */
    MyLinkedList() : m_size(0), m_head(new ListNode(0)), m_tail(new ListNode(0))
    {
        m_head->next = m_tail;
        m_tail->pre = m_head;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int Get(int index)
    {
        //std::cout << "get at " << index << std::endl;
        if (index < 0 || index >= m_size) return -1;
        ListNode * cur = m_head->next;
        while (index-- > 0)
            cur = cur->next;
        return cur->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void AddAtHead(int val)
    {
        AddAtIndex(0, val);
    }

    /** Append a node of value val to the last element of the linked list. */
    void AddAtTail(int val)
    {
        AddAtIndex(m_size, val);
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void AddAtIndex(int index, int val)
    {
        //std::cout << "add at " << index << ":" << val << std::endl;
        if (index > m_size) return;
        if (index < 0) index = 0; // this is the bug from the test case
        ListNode * cur = m_head;
        while (index-- > 0)
            cur = cur->next;
        ListNode * add = new ListNode(val);
        ListNode * nxt = cur->next;
        cur->next = add;
        add->next = nxt;
        nxt->pre = add;
        add->pre = cur;
        ++m_size;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void DeleteAtIndex(int index)
    {
        //std::cout << "delete at " << index << std::endl;
        if (m_size == 0 || index < 0 || index >= m_size) return;
        ListNode * cur = m_head;
        while (index-- > 0)
            cur = cur->next;
        ListNode * del = cur->next;
        ListNode * nxt = del->next;
        cur->next = nxt;
        nxt->pre = cur;
        delete del;
        --m_size;
    }
};
#endif
