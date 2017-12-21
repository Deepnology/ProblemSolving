#ifndef PARSE_NESTED_LIST_STRING_H
#define PARSE_NESTED_LIST_STRING_H
#include "Debug.h"
/*
Leetcode: Mini Parser
Given a nested list of integers represented as a string, implement a parser to deserialize it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.
Note: You may assume that the string is well-formed:
String is non-empty.
String does not contain white spaces.
String contains only digits 0-9, [, - ,, ].
Example 1:
Given s = "324",
You should return a NestedInteger object which contains a single integer 324.
Example 2:
Given s = "[123,[456,[789]]]",
Return a NestedInteger object containing a nested list with 2 elements:
1. An integer containing value 123.
2. A nested list containing two elements:
i.  An integer containing value 456.
ii. A nested list with one element:
a. An integer containing value 789.

*/
class ParseNestedListString
{
public:
	ParseNestedListString() {}
	
	class NestedInteger 
	{
		std::vector<NestedInteger> list;
		bool isInt;
		int myInt;
	public:
		NestedInteger():isInt(false), myInt(0)
		{}
		NestedInteger(int value): isInt(true), myInt(value)
		{}
		bool isInteger() const
		{
			return isInt;
		}
		int getInteger() const
		{
			return myInt;
		}
		void setInteger(int value)
		{
			isInt = true;
			myInt = value;
		}
		void add(const NestedInteger & ni)
		{
			isInt = false;
			list.push_back(ni);
		}
		const std::vector<NestedInteger> & getList() const
		{
			return list;
		}

		std::string ToStr()
		{
			if (isInt)
				return std::to_string(myInt);
			else
			{
				std::string res = "[";
				int N = list.size();
				for (int i = 0; i < N; ++i)
				{
					res += list[i].ToStr();
					if (i != N - 1)
						res += ",";
				}
				res += "]";
				return res;
			}
		}
	};

public:
	NestedInteger deserialize(std::string s)
	{
		int i = 0;
		NestedInteger res;
		if (s[i] == '[')
			res = recur(s, ++i);
		else
			res.setInteger(stoi(s));

		std::cout << "ParseNestedListString for \"" << s << "\": " << res.ToStr() << std::endl;
		return res;
	}
private:
	//identify the smallest unit of recursion: []; identify the situation to go down recursion: [; identify the situation to go up and do postorder: ]
	NestedInteger recur(std::string & s, int & i)
	{
		int N = s.size();
		NestedInteger res;
		while (i < N)
		{
			if (s[i] == ']')
			{
				++i;
				//std::cout << "->" << res.ToStr() << std::endl;
				return res;
			}
			else if (s[i] == '[')
			{
				auto nxt = recur(s, ++i);
				res.add(nxt);//postorder add
			}
			else if (s[i] == ',')
			{
				++i;
			}
			else//0-9, -
			{
				int begin = i;
				while (i < N && (isdigit(s[i]) || s[i] == '-'))
					++i;
				res.add(NestedInteger(stoi(s.substr(begin, i - begin))));//add a single num
			}
		}

		//must have already returned when seeing ]
		return res;
	}
};
/*
ParseNestedListString for "[]": []
ParseNestedListString for "[[]]": [[]]
ParseNestedListString for "[-1]": [-1]
ParseNestedListString for "[1,2]": [1,2]
ParseNestedListString for "[1,[2]]": [1,[2]]
ParseNestedListString for "[[1],2]": [[1],2]
ParseNestedListString for "324": 324
ParseNestedListString for "[[1,2],3,[4,5]]": [[1,2],3,[4,5]]
ParseNestedListString for "[123,[456,[789]]]": [123,[456,[789]]]
ParseNestedListString for "[[[6,7],4,5],2,[3,[[6],8,[4,[5,[[7,3],0]]],4],1],9]": [[[6,7],4,5],2,[3,[[6],8,[4,[5,[[7,3],0]]],4],1],9]
*/
#endif
