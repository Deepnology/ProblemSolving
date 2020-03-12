#ifndef PARENTHESES_COMBINATION_H
#define PARENTHESES_COMBINATION_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Enumerate strings of balanced parens
Leetcode: Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:
"((()))", "(()())", "(())()", "()(())", "()()()"
Complexity:
O(n!)

See also CatalanNumber.h, UniqueBinarySearchTree.h
*/
class ParenthesesCombination
{
public:
	ParenthesesCombination(){}
	~ParenthesesCombination(){}

	std::vector<std::string> GenRecur(int n)//n is the count of parentheses pairs
	{
		std::string path;
		std::vector<std::string> res;
		this->genRecur(n, n, path, res);//starting from total count of '(' and ')' down to 0
		std::cout << "ParenthesesCombination for \"" << n << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void genRecur(int leftCount, int rightCount, std::string & path, std::vector<std::string> & res)
	{
		if (leftCount == 0 && rightCount == 0)//have put all amount of '(' and ')' in path
		{
			res.push_back(path);
			return;
		}
		if (leftCount > 0)//still remains some amount of '(' that haven't been put in path
		{
			path.push_back('(');
			this->genRecur(leftCount - 1, rightCount, path, res);
			path.pop_back();
		}
		if (rightCount > leftCount)//if (rightCount <= leftCount) then add more ')' will make it invalid
		{
			path.push_back(')');
			this->genRecur(leftCount, rightCount - 1, path, res);
			path.pop_back();
		}
	}

};
/*
ParenthesesCombination for "3": ((())), (()()), (())(), ()(()), ()()()
*/
#endif