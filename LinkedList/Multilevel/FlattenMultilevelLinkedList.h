/*Facebook*/
#ifndef _FLATTEN_MULTILEVEL_LINKED_LIST_H
#define _FLATTEN_MULTILEVEL_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Flatten a Multilevel Doubly Linked List
flatten a multi-level linkedlist
no cycle:
1 - 2 - 3 - 4
    |
    7 -  8 - 10 - 12
    |    |    |
    9    16   11
    |    |
    14   17 - 18 - 19 - 20
    |                    |
    15 - 23             21
         |
         24
Output:
down then next: 1->2->7->9->14->15->23->24->8->16->17->18->19->20->21->10->11->12->3->4
level by level: 1->2->3->4->7->8->10->12->9->16->11->14->17->18->19->20->15->23->21->24

with cycle:
10 - 5 - 12 - 7 - 11 <-
|             |        |
4 - 20 - 13 - 17 - 6 --+--
    |    |    |        |  |
    2    16   9 - 8 ---   |
         |    |           |
         3   19 - 15 <----
Output:
down then next: 10->4->20->2->13->16->3->17->9->19->15->8->11->6->5->12->7
level by level: 10->5->12->7->11->4->20->13->17->6->15->2->16->9->8->3->19
 */
class FlattenMultilevelLinkedList
{
public:
    FlattenMultilevelLinkedList(){}
    struct ListNode
    {
        ListNode(int x) : val(x), next(NULL), down(NULL){}
        int val;
        ListNode * next;
        ListNode * down;
    };

    ListNode * DFS(ListNode * head)//connect down then next
    {
        ListNode * tail;
        std::unordered_set<ListNode*> visit;//for cycles only
        recur(head, tail, visit);
        return head;
    }
    ListNode * recur(ListNode * cur, ListNode *& tail, std::unordered_set<ListNode*> & visit)
    {
        if (cur == NULL) return NULL;

        visit.insert(cur);
        tail = cur;
        ListNode * next = cur->next;
        ListNode * down = cur->down;
        if (down && !visit.count(down))
        {
            ListNode * curTail = tail;
            curTail->next = recur(down, tail, visit);
        }
        //now tail has been updated to a new tail after appending down
        if (next && !visit.count(next))
        {
            ListNode * curTail = tail;
            curTail->next = recur(next, tail, visit);
        }
        //now tail has been updated to a new tail after appending next
        tail->next = NULL;
        cur->down = NULL;
        return cur;
    }

    ListNode * BFS(ListNode * head)//level by level
    {
        if (head == NULL) return NULL;

        ListNode * cur = head;
        ListNode * tail = head;
        std::unordered_set<ListNode*> visit;//for cycles only
        visit.insert(tail);
        while (tail->next && !visit.count(tail->next))
        {
            visit.insert(tail->next);
            tail = tail->next;
        }
        while (cur != tail)
        {
            if (cur->down && !visit.count(cur->down))
            {
                tail->next = cur->down;//append down to tail
                while (tail->next && !visit.count(tail->next))
                {
                    visit.insert(tail->next);
                    tail = tail->next;
                }
                cur->down = NULL;
            }
            cur = cur->next;
        }
        tail->next = NULL;
        return head;
    }


};
#endif
