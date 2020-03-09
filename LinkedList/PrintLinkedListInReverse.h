#ifndef _PRINT_LINKED_LIST_IN_REVERSE_H
#define _PRINT_LINKED_LIST_IN_REVERSE_H
#include "Debug.h"
/*
https://leetcode.com/discuss/interview-question/124617/Print-out-an-immutable-singly-linked-list-in-reverse/
Facebook Reality Labs
1. Recursion: O(N) time, O(N) space
2. Stack: O(N) time, O(N) space
3. Reverse List: O(N) time, O(1) space
4. Repeatedly iterate to end: O(N^2) time, O(1) space
5. Divide Conquer: O(NlogN) time, < O(N) space
 */
class PrintLinkedListInReverse
{
public:
    PrintLinkedListInReverse(){}

    struct ListNode
    {
        ListNode(int v): val(v), next(0){}
        int val;
        ListNode * next;
    };

    void DivideConquer(ListNode * head)
    {
        int len = 1;
        ListNode * cur = head;
        for (; cur->next; cur = cur->next)
            ++len;

        std::cout << "PrintLinkedListInReverse DivideConquer for above list with size=" << len << ": ";
        Recur(head, len);
        std::cout << std::endl;
    }
    void Recur(ListNode * cur, int len)
    {
        if (len == 1)
        {
            std::cout << cur->val << ", ";
            return;
        }

        ListNode * mid = cur;
        int halfLen = len / 2;
        while (halfLen-- > 0)
            mid = mid->next;

        Recur(mid, len - len / 2);
        Recur(cur, len / 2);
    }
};
/*
[0,1]->[1,2]->[2,3]->[3,4]->NULL

PrintLinkedListInReverse DivideConquer for above list with size=4: 4, 3, 2, 1,
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->NULL

PrintLinkedListInReverse DivideConquer for above list with size=5: 5, 4, 3, 2, 1,
 */
#endif
