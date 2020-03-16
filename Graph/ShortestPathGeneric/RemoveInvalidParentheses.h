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

	std::vector<std::string> BFS_Optimal(const std::string & s)
	{
		std::vector<std::string> res;
		std::queue<std::tuple<std::string,int,int,char>> que;//<cur, start, rmv, dir>
		que.push({s, 0, 0, '('});//start from left to right
		while (!que.empty())
		{
			std::string cur = std::get<0>(que.front());
			int start = std::get<1>(que.front());
			int rmv = std::get<2>(que.front());
			char left = std::get<3>(que.front());
			char right = left == '(' ? ')' : '(';
			int balance = 0;
			que.pop();

			for (int i = start; i < cur.size(); ++i)
			{
				if (cur[i] == left) ++balance;
				else if (cur[i] == right) --balance;
				if (balance < 0)//now there are more rights in cur[0:i], try to remove rights
				{
					for (int j = rmv; j <= i; ++j)
						if (cur[j] == right && (j == rmv || cur[j] != cur[j-1]))
							que.push({cur.substr(0,j)+cur.substr(j+1), i, j, left});//continue with same dir
					break;
				}
			}
			if (balance < 0) continue;
			//now balance >= 0, if finished both left to right and right to left, should be a valid parenthesis string
			//if finished only left to right, continue with right to left
			std::reverse(cur.begin(), cur.end());
			if (left == '(')//finished left to right
				que.push({cur, 0, 0, ')'});//continue with right to left
			else//finished right to left
				res.push_back(cur);//finished both dir, should be valid
		}

		std::cout << "RemoveInvalidParentheses BFS_Optimal for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}


	std::vector<std::string> BFS_NoHashMap(const std::string & s)
	{
		std::vector<std::string> res;
		std::queue<std::pair<std::string,int>> que;//<cur, rmv>
		que.push({s, 0});
		while (!que.empty())
		{
			int levelCount = que.size();
			bool reach = false;
			while (levelCount-->0)
			{
				std::string cur = que.front().first;
				int rmv = que.front().second;
				que.pop();
				if (isValid(cur))
				{
					res.push_back(cur);
					reach = true;
				}
				if (reach) continue;
				for (int i = rmv; i < cur.size(); ++i)
				{
					if (cur[i] == '(' || cur[i] == ')')
					{
                        //keep track of removal order, ex: (()(() remove 0th then 3rd and remove 3rd then 0th both generate ()()
                        //skip consecutive same chars, ex: (() remove 0th and remove 1th both generate ()
						if (i == rmv || cur[i] != cur[i-1])
						{
							que.push({cur.substr(0,i)+cur.substr(i+1), i});
						}
					}
				}
			}
			if (reach) break;
		}

		std::cout << "RemoveInvalidParentheses BFS_NoHashMap for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	std::vector<std::string> BFS(const std::string & s)
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
RemoveInvalidParentheses BFS_Optimal for "()())()": (())(), ()()()
RemoveInvalidParentheses BFS_NoHashMap for "()())()": (())(), ()()()
RemoveInvalidParentheses BFS for "()())()": (())(), ()()()
Row#0	= 2: (())(), ()()()
Row#1	= 4: ()()
Row#2	= 6: ()

RemoveInvalidParentheses DFS for "()())()": (())(), ()()()
RemoveInvalidParentheses BFS_Optimal for "()()))(()))(()(()))(()": (()(()))(()(()))(), (())(())(()(()))(), ()((()))(()(()))(), ()()(())(()(()))()
RemoveInvalidParentheses BFS_NoHashMap for "()()))(()))(()(()))(()": (()(()))(()(()))(), (())(())(()(()))(), ()((()))(()(()))(), ()()(())(()(()))()
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
