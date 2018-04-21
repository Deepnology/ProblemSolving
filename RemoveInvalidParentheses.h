#ifndef REMOVE_INVALID_PARENTHESES_H
#define REMOVE_INVALID_PARENTHESES_H
#include "Debug.h"
/*
Leetcode: Remove Invalid Parentheses
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and ).
Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]

This problem has to stop at the shallowest valid level for either BFS or DFS.
BFS is the straight forward method because we can stop at the level of valid s with longest length.
DFS has to traverse down to the deepest leaf, but is redundant.

see also ValidParentheses.h, LongestValidParentheses.h
*/
class RemoveInvalidParentheses
{
public:
	RemoveInvalidParentheses() {}
	~RemoveInvalidParentheses() {}

	//enumerate all diff result configurations with a shortest path instead of enumerating all diff shortest paths
	std::vector<std::string> BFS(const std::string & s)//better
	{
		std::unordered_set<std::string> visit;
		std::queue<std::string> que;
		std::vector<std::string> res;
		que.push(s);
		visit.insert(s);
		while (!que.empty())
		{
			int curLevelCount = que.size();
			bool reached = false;
			for (int k = 0; k < curLevelCount; ++k)
			{
				std::string cur = que.front();
				que.pop();
				if (this->isValid(cur))
				{
					res.push_back(cur);
					reached = true;
				}
				if (reached)
					continue;

				int N = cur.size();
				for (int i = 0; i < N; ++i)
				{
					if (cur[i] == '(' || cur[i] == ')')
					{
						std::string front = cur.substr(0, i);
						std::string back = cur.substr(i + 1);
						if (visit.find(front + back) != visit.end())
							continue;
						visit.insert(front + back);//mark this neighbor of cur level node visited to skip other latter cur level nodes visit this neighbor bc we don't need to enumerate all diff paths
						que.push(front + back);
					}
				}
			}
			if (reached)
				break;
		}

		std::cout << "RemoveInvalidParentheses BFS for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	//this DFS guarantees all diff shortest paths and their result configurations
	std::vector<std::string> DFS(const std::string & s)//need to prune
	{
		std::unordered_map<std::string, int> visit;//first: config, second: depth
		std::vector<std::string> res;
		std::map<int, std::vector<std::string>> allValid;//first: depth, second: all result configs
		int minDepth = INT_MAX;
		this->recur(s, 1, minDepth, visit, allValid);
		if (!allValid.empty())
			for (const auto & s : allValid.begin()->second)
				res.push_back(s);

		Debug::Print2D<int, std::string>()(allValid);
		std::cout << "RemoveInvalidParentheses DFS for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & s, int depth, int & minDepth, std::unordered_map<std::string, int> & visit, std::map<int, std::vector<std::string>> & allValid)
	{
		if (depth > minDepth)
			return;
		if (this->isValid(s))
		{
			minDepth = std::min(minDepth, depth);
			allValid[depth].push_back(s);
			return;
		}
		else if (depth == minDepth)
			return;

		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(' || s[i] == ')')
			{
				std::string front = s.substr(0, i);
				std::string back = s.substr(i + 1);
				std::string nxt = front + back;
				if (visit.find(nxt) == visit.end() || visit[nxt] > depth + 1)
				{
					visit[nxt] = depth + 1;
					this->recur(nxt, depth + 1, minDepth, visit, allValid);
				}
			}
		}
	}

private:
	bool isValid(const std::string & s)
	{
		int N = s.size();
		int count = 0;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(')
				++count;
			else if (s[i] == ')')
			{
				if (count == 0)//testing condition for incorrect order, such as ")("
					return false;
				--count;
			}
			else
				continue;
		}
		return count == 0;//general testing condition
	}
};
/*
RemoveInvalidParentheses BFS for "()())()": (())(), ()()()
Row#0	= 2: (())(), ()()()
Row#1	= 4: ()()
Row#2	= 6: ()

RemoveInvalidParentheses DFS for "()())()": (())(), ()()()

RemoveInvalidParentheses BFS for "()()))(()))(()(()))(()": (()(()))(()(()))(), (())(())(()(()))(), ()((()))(()(()))(), ()()(())(()(()))()
Row#0	= 5: (()(()))(()(()))(), (())(())(()(()))(), ()((()))(()(()))(), ()()(())(()(()))()
Row#1	= 7: ((()))(()(()))(), ()(())(()(()))(), (((()))()(()))(), (((()))(()()))(), (((()))(()(()))), (()())(()(()))(), (()(())()(()))(), (()(())(()()))(), (()(())(()(()))), (()(()))((()))(), (()(()))()(())(), (()(()))(((()))), (()(()))(()())(), (()(()))(()(()))
Row#2	= 9: (())(()(()))(), ((())()(()))(), ((())(()()))(), ((())(()(()))), ((()))((()))(), ((()))()(())(), ((()))(((()))), ((()))(()())(), ((()))(()(()))
Row#3	= 11: ()(()(()))(), (()()(()))(), (()(()()))(), (()(()(()))), (())((()))(), (())()(())(), (())(((()))), (())(()())(), (())(()(()))
Row#4	= 13: (()(()))(), ((()()))(), ((()(()))), ()((()))(), ()()(())(), ()(((()))), ()(()())(), ()(()(()))
Row#5	= 15: ((()))(), ()(())(), (((()))), (()())(), (()(()))
Row#6	= 17: (())(), ((()))
Row#7	= 19: ()(), (())
Row#8	= 21: ()

RemoveInvalidParentheses DFS for "()()))(()))(()(()))(()": (()(()))(()(()))(), (())(())(()(()))(), ()((()))(()(()))(), ()()(())(()(()))()
*/
#endif
