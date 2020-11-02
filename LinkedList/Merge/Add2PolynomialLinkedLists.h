#ifndef _ADD_2_POLYNOMIAL_LINKED_LISTS_H
#define _ADD_2_POLYNOMIAL_LINKED_LISTS_H
#include "Debug.h"
/*
Leetcode: Add Two Polynomials Represented as Linked Lists

 */
class Add2PolynomialLinkedLists
{
public:
    struct ListNode
    {
        ListNode(): coefficient(0), power(0), next(nullptr) {}
        ListNode(int x, int y): coefficient(x), power(y), next(nullptr) {}
        ListNode(int x, int y, ListNode* next): coefficient(x), power(y), next(next) {}
        int coefficient;
        int power;
        ListNode * next;
    };
    ListNode * Add(ListNode * p1, ListNode* p2)
    {
        ListNode * dummy = new ListNode;
        ListNode * cur = dummy;
        while (p1 || p2)
        {
            if (p1 && p2 && p1->power==p2->power)
            {
                if (p1->coefficient+p2->coefficient != 0)
                {
                    cur->next = new ListNode(p1->coefficient+p2->coefficient, p1->power);
                    cur = cur->next;
                }
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (p2 == NULL || p1 && (p1->power > p2->power))
            {
                cur->next = new ListNode(p1->coefficient, p1->power);
                p1 = p1->next;
                cur = cur->next;
            }
            else
            {
                cur->next = new ListNode(p2->coefficient, p2->power);
                p2 = p2->next;
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};
#endif
