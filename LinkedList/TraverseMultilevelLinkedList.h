#ifndef _TRAVERSE_MULTILEVEL_LINKED_LIST_H
#define _TRAVERSE_MULTILEVEL_LINKED_LIST_H
#include "Debug.h"
/*
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
Levelorder: 1,2,3,4,7,8,10,12,9,16,11,14,17,18,19,20,15,23,21,24
Verticalorder: 1,2,7,9,14,15,3,8,16,17,23,24,4,10,11,18,12,19,20,21

with cycle:
10 - 5 - 12 - 7 - 11 <-
|             |        |
4 - 20 - 13 - 17 - 6 --+--
    |    |    |        |  |
    2    16   9 - 8 ---   |
         |    |           |
         3   19 - 15 <----
Levelorder: 10,5,12,7,11,4,20,13,17,6,15,2,16,9,8,3,19
Verticalorder: 10,4,5,20,2,12,13,16,3,7,17,9,19,11,6,8,15

 */
class TraverseMultilevelLinkedList
{
public:
    TraverseMultilevelLinkedList(){}
    struct ListNode
    {
        ListNode(int x) : val(x), next(NULL), down(NULL){}
        int val;
        ListNode * next;
        ListNode * down;
    };

    std::vector<int> Levelorder(ListNode * head)
    {
        std::vector<int> res;
        if (head == NULL) return res;
        std::queue<ListNode *> que;
        std::unordered_set<ListNode *> visit;
        ListNode * cur = head;
        que.push(cur);
        visit.insert(cur);
        while (cur->next && !visit.count(cur->next))
        {
            que.push(cur->next);
            visit.insert(cur->next);
            cur = cur->next;
        }
        while (!que.empty())
        {
            cur = que.front();
            que.pop();
            res.push_back(cur->val);
            if (cur->down && !visit.count(cur->down))
            {
                que.push(cur->down);
                visit.insert(cur->down);
                cur = cur->down;
                while (cur->next && !visit.count(cur->next))
                {
                    que.push(cur->next);
                    visit.insert(cur->next);
                    cur = cur->next;
                }
            }
        }
        std::cout << "TraverseMultilevelLinkedList Levelorder: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

    std::vector<int> Verticalorder(ListNode * head)
    {
        std::vector<int> res;
        if (head == NULL) return res;
        std::queue<ListNode *> que;
        std::unordered_set<ListNode *> visit;
        ListNode * cur = head;
        que.push(cur);
        visit.insert(cur);
        while (cur->down && !visit.count(cur->down))
        {
            que.push(cur->down);
            visit.insert(cur->down);
            cur = cur->down;
        }
        while (!que.empty())
        {
            cur = que.front();
            que.pop();
            res.push_back(cur->val);
            if (cur->next && !visit.count(cur->next))
            {
                que.push(cur->next);
                visit.insert(cur->next);
                cur = cur->next;
                while (cur->down && !visit.count(cur->down))
                {
                    que.push(cur->down);
                    visit.insert(cur->down);
                    cur = cur->down;
                }
            }
        }
        std::cout << "TraverseMultilevelLinkedList Verticalorder: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

    std::vector<int> PreorderNext(ListNode * head)
    {
        std::vector<int> res;
        if (head == NULL) return res;
        std::stack<ListNode *> stk;
        std::unordered_set<ListNode *> visit;
        ListNode * cur = head;
        stk.push(cur);
        visit.insert(cur);
        while (!stk.empty())
        {
            cur = stk.top();
            stk.pop();
            res.push_back(cur->val);
            if (cur->down && !visit.count(cur->down))
            {
                visit.insert(cur->down);
                stk.push(cur->down);
            }
            if (cur->next && !visit.count(cur->next))
            {
                visit.insert(cur->next);
                stk.push(cur->next);
            }
        }
        std::cout << "TraverseMultilevelLinkedList PreorderNext: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

    std::vector<int> PreorderDown(ListNode * head)
    {
        std::vector<int> res;
        if (head == NULL) return res;
        std::stack<ListNode *> stk;
        std::unordered_set<ListNode *> visit;
        ListNode * cur = head;
        stk.push(cur);
        visit.insert(cur);
        while (!stk.empty())
        {
            cur = stk.top();
            stk.pop();
            res.push_back(cur->val);
            if (cur->next && !visit.count(cur->next))
            {
                visit.insert(cur->next);
                stk.push(cur->next);
            }
            if (cur->down && !visit.count(cur->down))
            {
                visit.insert(cur->down);
                stk.push(cur->down);
            }
        }
        std::cout << "TraverseMultilevelLinkedList PreorderDown: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
TraverseMultilevelLinkedList Levelorder: 1, 2, 3, 4, 7, 8, 10, 12, 9, 16, 11, 14, 17, 18, 19, 20, 15, 23, 21, 24
TraverseMultilevelLinkedList Verticalorder: 1, 2, 7, 9, 14, 15, 3, 8, 16, 17, 23, 24, 4, 10, 11, 18, 12, 19, 20, 21
TraverseMultilevelLinkedList PreorderNext: 1, 2, 3, 4, 7, 8, 10, 12, 11, 16, 17, 18, 19, 20, 21, 9, 14, 15, 23, 24
TraverseMultilevelLinkedList PreorderDown: 1, 2, 7, 9, 14, 15, 23, 24, 8, 16, 17, 18, 19, 20, 21, 10, 11, 12, 3, 4
TraverseMultilevelLinkedList Levelorder: 10, 5, 12, 7, 11, 4, 20, 13, 17, 6, 15, 2, 16, 9, 8, 3, 19
TraverseMultilevelLinkedList Verticalorder: 10, 4, 5, 20, 2, 12, 13, 16, 3, 7, 17, 9, 19, 11, 6, 8, 15
TraverseMultilevelLinkedList PreorderNext: 10, 5, 12, 7, 11, 17, 6, 15, 9, 8, 19, 4, 20, 13, 16, 3, 2
TraverseMultilevelLinkedList PreorderDown: 10, 4, 20, 2, 13, 16, 3, 17, 9, 19, 15, 8, 11, 6, 5, 12, 7
 */
#endif
