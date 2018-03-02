#ifndef _SPLIT_NODES_IN_K_GROUP_LINKED_LIST_H
#define _SPLIT_NODES_IN_K_GROUP_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Split Linked List in Parts
Given a (singly) linked list with head node root, write a function to split the linked list into k consecutive linked list "parts".
The length of each part should be as equal as possible: no two parts should have a size differing by more than 1.
This may lead to some parts being null.
The parts should be in order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal parts occurring later.
Return a List of ListNode's representing the linked list parts that are formed.
Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
Example 1:
Input:  root = [1, 2, 3], k = 5 Output: [[1],[2],[3],[],[]]
Explanation: The input and each element of the output are ListNodes, not arrays.
For example, the input root has root.val = 1, root.next.val = 2, \root.next.next.val = 3, and root.next.next.next = null.
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but it's string representation as a ListNode is [].
Example 2:
Input:
root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
Explanation:
The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.
 */
class SplitNodesInKGroupLinkedList
{
public:
    struct ListNode
    {
        ListNode(int x) : val(x), next(NULL){}
        ListNode(): val(INT_MIN), next(NULL){}
        int val;
        ListNode * next;
    };
    SplitNodesInKGroupLinkedList(){}

    std::vector<ListNode *> TwoScan(ListNode * root, int k)
    {
        int len = 0;
        ListNode * cur = root;
        while(cur)
        {
            ++len;
            cur = cur->next;
        }
        std::vector<ListNode *> res;
        int count = len / k;
        int remain = len % k;
        ListNode * pre = NULL;
        cur = root;
        for (int i = 0; i < k; ++i)
        {
            res.push_back(cur);
            if (cur)
            {
                for (int j = 0; j < (count + (remain ? 1:0)); ++j)
                {
                    pre = cur;
                    cur = cur->next;
                }
                if (remain) --remain;
                pre->next = NULL;
            }
        }
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
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->[9,10]->NULL
SplitNodesInKGroupLinkedList TwoScan for above linked list:
[0,1]->[1,2]->[2,3]->[3,4]->NULL
[0,5]->[1,6]->[2,7]->NULL
[0,8]->[1,9]->[2,10]->NULL
 */
#endif
