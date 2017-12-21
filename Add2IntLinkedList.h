#ifndef ADD_2_INT_LINKED_LIST_H
#define ADD_2_INT_LINKED_LIST_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
/*
Elements of porgramming interview, LinkedLists: Add list-based integers
Leetcode: Add Two Numbers
// You are given two linked lists representing two non-negative numbers.
// The digits are stored in reverse order and each of their nodes contain a
// single digit. Add the two numbers and return it as a linked list.
//
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
// 342 + 465 = 807
// Complexity:
// O(m+n)

Leetcode: Add Two Numbers II
You are given two non-empty linked lists representing two non-negative integers.
The most significant digit comes first and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.
Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.
Example:
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
*/
class Add2IntLinkedList
{
public:
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};

	Add2IntLinkedList(){}
	~Add2IntLinkedList(){}

	ListNode * Iterate(ListNode * head1, ListNode * head2)
	{
		ListNode * curNode1 = head1;
		ListNode * curNode2 = head2;

		ListNode * head3 = new ListNode(-1);
		ListNode * curNode = head3;
		int carry = 0;
		while (curNode1 != NULL || curNode2 != NULL)
		{
			int sum = carry;
			if (curNode1 != NULL)
			{
				sum += curNode1->val;
				curNode1 = curNode1->next;
			}
			if (curNode2 != NULL)
			{
				sum += curNode2->val;
				curNode2 = curNode2->next;
			}
			curNode->next = new ListNode(sum % 10);//digit = sum % 10
			curNode = curNode->next;
			carry = sum / 10;//carry = sum / 10
		}
		if (carry)
			curNode->next = new ListNode(carry);
		head3 = this->DeleteNode(head3);

		std::cout << "Add2IntLinkedList for \"" << this->ReverseListToStr(head1) << "\", \"" << this->ReverseListToStr(head2) << "\": " << this->ReverseListToStr(head3) << std::endl;
		return head3;
	}

	//Leetcode: Add Two Numbers II w/o reversing the input lists, using 2 stacks
	ListNode* addTwoNumbersII_2Stks(ListNode* l1, ListNode* l2)
	{
		std::stack<int> stk1;
		std::stack<int> stk2;
		while (l1)
		{
			stk1.push(l1->val);
			l1 = l1->next;
		}
		while (l2)
		{
			stk2.push(l2->val);
			l2 = l2->next;
		}
		ListNode * prevHead = NULL;
		int carry = 0;
		while (!stk1.empty() || !stk2.empty())
		{
			int sum = carry;
			if (!stk1.empty())
			{
				sum += stk1.top(); stk1.pop();
			}
			if (!stk2.empty())
			{
				sum += stk2.top(); stk2.pop();
			}
			ListNode * cur = new ListNode(sum % 10);
			carry = sum / 10;
			cur->next = prevHead;
			prevHead = cur;
		}
		if (carry != 0)
		{
			ListNode * cur = new ListNode(carry);
			cur->next = prevHead;
			prevHead = cur;
		}
		return prevHead;
	}
	//Leetcode: Add Two Numbers II w/o reversing the input lists. add, reverse to perform carry, reverse result to return
	ListNode* addTwoNumbersII_AddRevRev(ListNode* l1, ListNode* l2)
	{
		//1. add
		int len1 = GetLen(l1);
		int len2 = GetLen(l2);
		ListNode * cur1 = l1;
		ListNode * cur2 = l2;
		ListNode * resHead = NULL;
		ListNode * resCur = NULL;
		while (len1 && len2)
		{
			int sum = 0;
			if (len1 >= len2)
			{
				sum += cur1->val;
				cur1 = cur1->next;
				--len1;
			}
			if (len2 > len1)
			{
				sum += cur2->val;
				cur2 = cur2->next;
				--len2;
			}
			if (resHead == NULL)
			{
				resHead = new ListNode(sum);
				resCur = resHead;
			}
			else
			{
				resCur->next = new ListNode(sum);
				resCur = resCur->next;
			}
		}

		//2. reverse resHead to perform carry
		ListNode * rev = Rev(resHead);
		ListNode * cur = rev;
		ListNode * pre = NULL;
		int carry = 0;
		while (cur)
		{
			int sum = carry + cur->val;
			cur->val = sum % 10;
			carry = sum / 10;
			pre = cur;
			cur = cur->next;

		}
		if (carry)
			pre->next = new ListNode(carry);

		//3. reverse rev to return
		return Rev(rev);
	}
private:
	int GetLen(ListNode * h)
	{
		int res = 0;
		while (h)
		{
			++res;
			h = h->next;
		}
		return res;
	}
	ListNode * Rev(ListNode * h)
	{
		ListNode * tail = NULL;
		while (h)
		{
			ListNode * next = h->next;
			h->next = tail;
			tail = h;
			h = next;
		}
		return tail;
	}



private:
	ListNode * DeleteNode(ListNode * curNode)
	{
		ListNode * toDel = curNode;
		curNode = curNode->next;
		delete toDel;
		return curNode;
	}

	std::string ReverseListToStr(ListNode * curNode)
	{
		std::ostringstream oss;
		ListNode * dbg = curNode;
		while (dbg != NULL)
		{
			oss << dbg->val;
			dbg = dbg->next;
		}
		std::string n1Str = oss.str();
		std::reverse(n1Str.begin(), n1Str.end());
		return n1Str;
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

	static ListNode * CreateList(std::vector<int> & num)
	{
		ListNode * curNode = NULL;
		ListNode * head = NULL;
		for (std::vector<int>::const_iterator i = num.begin(); i != num.end(); ++i)
		{
			ListNode * n = new ListNode(*i);
			if (curNode)//means this is not the head node
				curNode->next = n;
			else//means this is the head node
				head = n;

			curNode = n;//update the curNode node
		}
		return head;
	}
};
/*
Add2IntLinkedList for "342", "765": 1107
Add2IntLinkedList:
[0,2]->[1,4]->[2,3]->NULL
[0,5]->[1,6]->[2,7]->NULL
[0,7]->[1,0]->[2,1]->[3,1]->NULL

*/
#endif