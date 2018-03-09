#ifndef _BASIC_CALCULATOR_2_H
#define _BASIC_CALCULATOR_2_H
#include "Debug.h"
/*
Leetcode: Basic Calculator III
Implement a basic calculator to evaluate a simple expression string.
The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
The expression string contains only non-negative integers, +, -, *, / operators , open ( and closing parentheses ) and empty spaces .
The integer division should truncate toward zero.
You may assume that the given expression is always valid.
All intermediate results will be in the range of [-2147483648, 2147483647].
Some examples:
"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12
 */
class BasicCalculator2
{
public:
    BasicCalculator2(){}

    int Recur(std::string s)//BasicCalculator, BasicCalculatorIII
    {
        int i = 0;
        int res = recur(s, i);
        std::cout << "BasicCalculator2 Recur for \"" << s << "\": " << res << std::endl;
        return res;
    }
private:
    long recur(const std::string & s, int & i)
    {
        int N = s.size();
        std::vector<long> nums;
        char op = '+';//default
        while (i < N)
        {
            if (s[i] == ')')
            {
                ++i;
                break;
            }
            else if (s[i] == '(')
            {
                long nxt = recur(s, ++i);//go down only when '('
                Add(nums, nxt, op);
            }
            else if (isdigit(s[i]))
            {
                int begin = i;
                while (i < N && isdigit(s[i]))
                    ++i;
                long nxt = stol(s.substr(begin, i-begin));
                Add(nums, nxt, op);
            }
            else if (s[i] == ' ')
                ++i;
            else//+,-.*,/
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
    int WithoutParenthesis(std::string s)//BasicCalculatorII
    {
        int N = s.size();
        std::vector<long> nums;
        char op = '+';
        int i = 0;
        while (i < N)
        {
            if (s[i] == ' ') ++i;
            else if (isdigit(s[i]))
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
};
/*
BasicCalculator2 Recur for "((2 + 1) * 3)": 9
BasicCalculator2 Recur for "(4 + (13 / 5))": 6
BasicCalculator2 Recur for "(7)-(0)+(4)": 11
BasicCalculator2 Recur for "3+2*2": 7
BasicCalculator2 Recur for "3/2 ": 1
BasicCalculator2 Recur for "3+5 / 2 ": 5
 */
#endif
