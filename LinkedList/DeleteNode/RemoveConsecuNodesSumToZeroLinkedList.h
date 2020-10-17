#ifndef _REMOVE_CONSECU_NODES_SUM_TO_ZERO_LINKED_LIST_H
#define _REMOVE_CONSECU_NODES_SUM_TO_ZERO_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Remove Zero Sum Consecutive Nodes from Linked List
Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
After doing so, return the head of the final linked list.  You may return any such answer.
Example 1:
Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Example 2:
Input: head = [1,2,3,-3,4]
Output: [1,2,4]
Example 3:
Input: head = [1,2,3,-3,-2]
Output: [1]
 */
class RemoveConsecuNodesSumToZeroLinkedList
{
public:
    struct ListNode
    {
        ListNode(int v): val(v), next(0){}
        int val;
        ListNode * next;
    };
    ListNode * UsePrefixSumMap(ListNode* head)
    {
        ListNode * dummy = new ListNode(0);
        dummy->next = head;
        std::unordered_map<int,ListNode*> prefixSumMap;
        ListNode * cur = head;
        int prefixSum = 0;
        prefixSumMap[0] = dummy;
        while (cur)
        {
            prefixSum += cur->val;
            //means [prefixSumMap[prefixSum]->next:cur] sum to 0
            //prefixSum(cur)-prefixSum(prefixSumMap[prefixSum]) = 0
            if (prefixSumMap.count(prefixSum))
            {
                ListNode * nxt = cur->next;
                //1. remove [prefixSumMap[prefixSum]->next:cur]
                ListNode * del = prefixSumMap[prefixSum]->next;
                int delSum = prefixSum + del->val;
                while (del != cur)
                {
                    prefixSumMap.erase(delSum);
                    del = del->next;
                    delSum += del->val;
                }
                //2. connect prefixSumMap[prefixSum]->next = nxt
                prefixSumMap[prefixSum]->next = nxt;
                cur = prefixSumMap[prefixSum];
            }
            else
                prefixSumMap[prefixSum] = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};
#endif
