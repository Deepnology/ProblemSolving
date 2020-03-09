#ifndef PRINT_LINKED_LIST_H
#define PRINT_LINKED_LIST_H
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
template<class NODE, class OSS>
class PrintLinkedList
{
public:
	PrintLinkedList(NODE * head, OSS & oss)
	{
		int index = 0;
		NODE * curNode = head;
		std::unordered_map<NODE *, int> map;
		while (curNode != NULL)
		{
			if (map.find(curNode) == map.end())//not exist
			{
				map.insert(std::make_pair(curNode, index));
				if (index != 0)
					oss << "->";
				oss << "[" << this->SelectVal2(index, curNode) << "," << this->GetVal(curNode) << "]";
				++index;
				curNode = this->GetNextNode(curNode);
			}
			else//already exist
			{
				break;
			}
		}
		oss << "->";
		if (curNode == NULL)
		{
			oss << "NULL";
		}
		else//list has circle at curNode
		{
			NODE * curNode2 = head;
			int index2 = 0;
			int preSpaces = 0;
			int postSpaces = 0;
			while (curNode2 != curNode)
			{
				if (map[curNode2] != 0)
					preSpaces += 2;//->
				preSpaces += 1;//[
				preSpaces += this->SelectVal2(map[curNode2], curNode2).size();//index
				preSpaces += 1;//,
				preSpaces += this->CountDigit(this->GetVal(curNode2));//val
				preSpaces += 1;//]
				curNode2 = this->GetNextNode(curNode2);
				++index2;
			}
			int cycleBeginIndex = index2;
			while (index2 < index)
			{
				if (index2 == cycleBeginIndex)
				{
					if (cycleBeginIndex != 0)
						preSpaces += 2;//->
					preSpaces += 1;//[
					preSpaces += this->SelectVal2(map[curNode2], curNode2).size();//index
				}
				else
				{
					postSpaces += 2;//->
					postSpaces += 1;//[
					postSpaces += this->SelectVal2(map[curNode2], curNode2).size();//index
					postSpaces += 1;//,
				}
				
				postSpaces += this->CountDigit(this->GetVal(curNode2));//val
				postSpaces += 1;//]
				curNode2 = this->GetNextNode(curNode2);
				++index2;
			}
			postSpaces += 1;//-

			oss << std::endl;
			for (int i = 0; i < preSpaces; ++i)
			{
				oss << " ";
			}
			oss << "^";
			for (int i = 0; i < postSpaces; ++i)
			{
				oss << "_";
			}
			oss << "|";
		}
		oss << std::endl;
	}
	
	~PrintLinkedList(){}
private:
	int CountDigit(int n)
	{
		if (n == 0)
			return 1;
		int count = 0;
		if (n < 0)
		{
			count = 1;
			n = -n;
		}
		while (n)
		{
			n /= 10;
			++count;
		}	
		return count;
	}

	//specialize this member function (cannot be inlined)
	NODE * GetNextNode(NODE * curNode);
	int GetVal(NODE * curNode);
	std::string SelectVal2(int index, NODE * curNode);
};

template<class NODE, class OSS>
NODE * PrintLinkedList<NODE, OSS>::GetNextNode(NODE * curNode)
{
	return curNode->next;//by default
}
template<class NODE, class OSS>
int PrintLinkedList<NODE, OSS>::GetVal(NODE * curNode)
{
	return curNode->val;//by default
}
template<class NODE, class OSS>
std::string PrintLinkedList<NODE, OSS>::SelectVal2(int index, NODE * curNode)
{
	return std::to_string(index);//by default
}
#endif