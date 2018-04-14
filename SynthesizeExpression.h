/*Facebook*/
#ifndef SYNTHESIZE_EXPRESSION_H
#define SYNTHESIZE_EXPRESSION_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Synthesize an expression
Leetcode: Expression Add Operators
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
Examples:
"123", 6 -> ["1+2+3", "1*2*3"]
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

O(n*4^n) time, O(n) space

See also ParenthesizeBoolExpr.h
*/
class SynthesizeExpression
{
public:
	SynthesizeExpression(){}
	~SynthesizeExpression(){}

	std::vector<std::string> BetterRecur(std::string num, int target)
	{
		std::vector<std::string> res;
		if (num.empty()) return res;
		std::string path;
		recur(num, 0, "", path, target, res);
		std::cout << "SynthesizeExpression BetterRecur for \"" << target << " from " << num << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & num, int begin, std::string curNum, std::string & path, int target, std::vector<std::string> & res)
	{
		if (!curNum.empty() && curNum[0] == '0') return;
		curNum.push_back(num[begin]);
		if (std::stoll(curNum) > INT_MAX || -std::stoll(curNum) < INT_MIN) return;
		int N = num.size();
		if (begin == N-1)
		{
			path += curNum;
			if (Eval(path) == target)
				res.push_back(path);
			path = path.substr(0, path.size()-curNum.size());
			return;
		}
		recur(num, begin+1, curNum, path, target, res);

		path += curNum;
		path.push_back('+');
		recur(num, begin+1, "", path, target, res);
		path.pop_back();

		path.push_back('-');
		recur(num, begin+1, "", path, target, res);
		path.pop_back();

		path.push_back('*');
		recur(num, begin+1, "", path, target, res);
		path.pop_back();
		path = path.substr(0, path.size()-curNum.size());
	}
	int Eval(const std::string & s)//BasicCalculatorII: with +,-,*,/, without (,)
	{
		int N = s.size();
		std::vector<long> nums;
		char op = '+';
		int i = 0;
		while (i < N)
		{
			if (isdigit(s[i]))
			{
				int begin = i;
				while (i < N && isdigit(s[i]))
					++i;
				long nxt = stol(s.substr(begin,i-begin));
				Add(nums, nxt, op);
			}
			else//+,-,*,/
			{
				op = s[i];
				++i;
			}
		}
		long res = 0;
		for (const auto & n : nums)
			res += n;
		return res;
	}
	void Add(std::vector<long> & nums, long cur, char op)
	{
		switch(op)
		{
			case '+': nums.push_back(cur); break;
			case '-': nums.push_back(-cur); break;
			case '*': nums.back() *= cur; break;
			case '/': nums.back() /= cur; break;
			default: break;
		}
	}




public:
	std::vector<std::string> Recur(const std::string & v, int sum)
	{
		std::vector<std::string> res;
		if (v.empty()) return res;
		std::vector<long long> operandsPath;
		std::vector<char> operatorsPath;
		this->recur(v, sum, std::string(""), 0, operandsPath, operatorsPath, res);
		std::cout << "SynthesizeExpression Recur for \"" << sum << " from " << v << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & v, int sum, std::string curNum, int begin, std::vector<long long> & operandsPath, std::vector<char> & operatorsPath, std::vector<std::string> & res)
	{
		if (!curNum.empty() && curNum[0] == '0')//important: early return when starting with 0
			return;
		int N = v.size();
		curNum.push_back(v[begin]);
		if (std::stoll(curNum) > INT_MAX || -std::stoll(curNum) < INT_MIN)//important: early return when including cur digit results in out of bound of an integer value
			return;

		if (begin == N - 1)
		{
			operandsPath.push_back(std::stoll(curNum));//just add curNum to path at N-1 so that we don't need to consider operators

			if (this->evaluate(operandsPath, operatorsPath) == sum)
			{
				std::ostringstream oss;
				std::vector<long long>::const_iterator operandItr = operandsPath.cbegin();
				oss << *operandItr++;
				for (const char & optor : operatorsPath)
				{
					oss << optor << *operandItr++;
				}
				res.push_back(oss.str());
			}
			operandsPath.pop_back();
			return;
		}

		//include curNum to the next running number
		this->recur(v, sum, curNum, begin + 1, operandsPath, operatorsPath, res);

		//exclude curNum from the next running number
		operandsPath.push_back(std::stoll(curNum));
		operatorsPath.push_back('+');
		this->recur(v, sum, std::string(""), begin + 1, operandsPath, operatorsPath, res);
		operatorsPath.pop_back();
		operatorsPath.push_back('-');
		this->recur(v, sum, std::string(""), begin + 1, operandsPath, operatorsPath, res);
		operatorsPath.pop_back();
		operatorsPath.push_back('*');
		this->recur(v, sum, std::string(""), begin + 1, operandsPath, operatorsPath, res);
		operatorsPath.pop_back();
		operandsPath.pop_back();
	}

	int evaluate(const std::vector<long long> & operands, const std::vector<char> & operators)
	{
		//1. compute multiplication: erase first operand and update second operand as the result; erase '*' operators
		std::vector<long long> operandsCopy(operands);
		std::vector<char> operatorsCopy(operators);
		std::vector<long long>::iterator operandItr = operandsCopy.begin();
		std::vector<char>::iterator operatorItr = operatorsCopy.begin();

		while (operatorItr != operatorsCopy.end())
		{
			if (*operatorItr == '*')
			{
				//a. update operandCopy
				long long res = *operandItr;
				operandItr = operandsCopy.erase(operandItr);//erase first operand, return second operand
				res *= *operandItr;
				*operandItr = res;

				//b. update operatorsCopy
				operatorItr = operatorsCopy.erase(operatorItr);//erase '*'
			}
			else
			{
				//a. update operandCopy
				++operandItr;

				//b. update operatorsCopy
				++operatorItr;
			}
		}

		//2. compute addition/subtraction of all operands
		operandItr = operandsCopy.begin();
		operatorItr = operatorsCopy.begin();
		long long sum = *operandItr++;
		while (operatorItr != operatorsCopy.end())
		{
			if (*operatorItr == '+')
				sum += *operandItr++;
			else if (*operatorItr == '-')
				sum -= *operandItr++;

			++operatorItr;
		}

		std::cout << "Evaluate \"" << Debug::ToStr1D<long long>()(operands) << "\", \"" << Debug::ToStr1D<char>()(operators) << "\": " << sum << std::endl;
		return (int)sum;
	}

};
/*
Evaluate "123", "": 123
Evaluate "12, 3", "+": 15
Evaluate "12, 3", "-": 9
Evaluate "12, 3", "*": 36
Evaluate "1, 23", "+": 24
Evaluate "1, 2, 3", "+, +": 6
Evaluate "1, 2, 3", "+, -": 0
Evaluate "1, 2, 3", "+, *": 7
Evaluate "1, 23", "-": -22
Evaluate "1, 2, 3", "-, +": 2
Evaluate "1, 2, 3", "-, -": -4
Evaluate "1, 2, 3", "-, *": -5
Evaluate "1, 23", "*": 23
Evaluate "1, 2, 3", "*, +": 5
Evaluate "1, 2, 3", "*, -": -1
Evaluate "1, 2, 3", "*, *": 6
SynthesizeExpression Recur for "6 from 123": 1+2+3, 1*2*3
SynthesizeExpression BetterRecur for "6 from 123": 1+2+3, 1*2*3
Evaluate "232", "": 232
Evaluate "23, 2", "+": 25
Evaluate "23, 2", "-": 21
Evaluate "23, 2", "*": 46
Evaluate "2, 32", "+": 34
Evaluate "2, 3, 2", "+, +": 7
Evaluate "2, 3, 2", "+, -": 3
Evaluate "2, 3, 2", "+, *": 8
Evaluate "2, 32", "-": -30
Evaluate "2, 3, 2", "-, +": 1
Evaluate "2, 3, 2", "-, -": -3
Evaluate "2, 3, 2", "-, *": -4
Evaluate "2, 32", "*": 64
Evaluate "2, 3, 2", "*, +": 8
Evaluate "2, 3, 2", "*, -": 4
Evaluate "2, 3, 2", "*, *": 12
SynthesizeExpression Recur for "8 from 232": 2+3*2, 2*3+2
SynthesizeExpression BetterRecur for "8 from 232": 2+3*2, 2*3+2
Evaluate "105", "": 105
Evaluate "10, 5", "+": 15
Evaluate "10, 5", "-": 5
Evaluate "10, 5", "*": 50
Evaluate "1, 0, 5", "+, +": 6
Evaluate "1, 0, 5", "+, -": -4
Evaluate "1, 0, 5", "+, *": 1
Evaluate "1, 0, 5", "-, +": 6
Evaluate "1, 0, 5", "-, -": -4
Evaluate "1, 0, 5", "-, *": 1
Evaluate "1, 0, 5", "*, +": 5
Evaluate "1, 0, 5", "*, -": -5
Evaluate "1, 0, 5", "*, *": 0
SynthesizeExpression Recur for "5 from 105": 10-5, 1*0+5
SynthesizeExpression BetterRecur for "5 from 105": 10-5, 1*0+5
Evaluate "0, 0", "+": 0
Evaluate "0, 0", "-": 0
Evaluate "0, 0", "*": 0
SynthesizeExpression Recur for "0 from 00": 0+0, 0-0, 0*0
SynthesizeExpression BetterRecur for "0 from 00": 0+0, 0-0, 0*0
*/
#endif