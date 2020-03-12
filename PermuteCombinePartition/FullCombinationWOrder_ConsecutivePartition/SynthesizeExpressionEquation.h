/*Facebook*/
#ifndef _SYNTHESIZE_EXPRESSION_EQUATION_H
#define _SYNTHESIZE_EXPRESSION_EQUATION_H
#include "Debug.h"
/*
Given a string, ex: 12345=67, where you can add binary operators +,-,*,/.
Return all possible equations.
See also SynthesizeExpression.h
 */
class SynthesizeExpressionEquation
{
public:
    SynthesizeExpressionEquation(){}

    std::vector<std::string> Solve(const std::string & s)
    {
        size_t idx = s.find('=');
        std::string left = s.substr(0, idx);
        std::string right = s.substr(idx+1);
        std::unordered_map<int,std::vector<std::string>> lmap = Recur(left);
        std::unordered_map<int,std::vector<std::string>> rmap = Recur(right);
        std::vector<std::string> res;
        for (const auto & p : lmap)
        {
            if (rmap.count(p.first))
            {
                for (const auto & ls : p.second)
                    for (const auto & rs : rmap[p.first])
                        res.push_back(ls + "=" + rs);
            }
        }
        Debug::Print2D<int,std::string>()(lmap);
        Debug::Print2D<int,std::string>()(rmap);
        std::cout << "SynthesizeExpressionEquation for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
        return res;
    }
private:
    std::unordered_map<int,std::vector<std::string>> Recur(std::string num)
    {
        std::unordered_map<int,std::vector<std::string>> res;
        if (num.empty()) return res;
        std::string path;
        recur(num, 0, "", path, res);
        return res;
    }
    void recur(const std::string & num, int begin, std::string curNum, std::string & path, std::unordered_map<int,std::vector<std::string>> & res)
    {
        if (!curNum.empty() && curNum[0] == '0') return;
        curNum.push_back(num[begin]);
        if (std::stoll(curNum) > INT_MAX || -std::stoll(curNum) < INT_MIN) return;
        int N = num.size();
        if (begin == N-1)
        {
            path += curNum;
            int val = Eval(path);
            res[val].push_back(path);
            path = path.substr(0, path.size()-curNum.size());
            return;
        }
        recur(num, begin+1, curNum, path, res);

        path += curNum;
        path.push_back('+');
        recur(num, begin+1, "", path, res);
        path.pop_back();

        path.push_back('-');
        recur(num, begin+1, "", path, res);
        path.pop_back();

        path.push_back('*');
        recur(num, begin+1, "", path, res);
        path.pop_back();

        path.push_back('/');
        recur(num, begin+1, "", path, res);
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
};
/*
Row#0	= 16: 7/3*8
Row#1	= 10: 7/3+8
Row#2	= -6: 7/3-8
Row#3	= 0: 7/38, 7/3/8
Row#4	= 29: 7*3+8
Row#5	= 13: 7*3-8
Row#6	= 266: 7*38
Row#7	= -4: 7-3-8
Row#8	= 738: 738
Row#9	= 2: 7+3-8, 7*3/8
Row#10	= -31: 7-38
Row#11	= 168: 7*3*8
Row#12	= 7: 7+3/8, 7-3/8
Row#13	= 18: 7+3+8
Row#14	= 31: 7+3*8
Row#15	= 584: 73*8
Row#16	= 9: 73/8
Row#17	= 45: 7+38
Row#18	= 65: 73-8
Row#19	= -17: 7-3*8
Row#20	= 12: 7-3+8
Row#21	= 81: 73+8

Row#0	= 0: 4/97, 4/9*7, 4/9/7
Row#1	= -7: 4/9-7
Row#2	= 252: 4*9*7
Row#3	= 3: 4-9/7
Row#4	= -59: 4-9*7
Row#5	= -12: 4-9-7
Row#6	= 2: 4-9+7
Row#7	= -93: 4-97
Row#8	= 5: 4+9/7, 4*9/7
Row#9	= 29: 4*9-7
Row#10	= 6: 4+9-7
Row#11	= 101: 4+97
Row#12	= 497: 497
Row#13	= 343: 49*7
Row#14	= 67: 4+9*7
Row#15	= 56: 49+7
Row#16	= 7: 49/7, 4/9+7
Row#17	= 43: 4*9+7
Row#18	= 388: 4*97
Row#19	= 20: 4+9+7
Row#20	= 42: 49-7

SynthesizeExpressionEquation for "738=497": 7/38=4/97, 7/38=4/9*7, 7/38=4/9/7, 7/3/8=4/97, 7/3/8=4/9*7, 7/3/8=4/9/7, 7*3+8=4*9-7, 7+3-8=4-9+7, 7*3/8=4-9+7, 7+3/8=49/7, 7+3/8=4/9+7, 7-3/8=49/7, 7-3/8=4/9+7
 */
#endif
