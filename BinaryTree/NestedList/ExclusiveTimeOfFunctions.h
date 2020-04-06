#ifndef _EXCLUSIVE_TIME_OF_FUNCTIONS_H
#define _EXCLUSIVE_TIME_OF_FUNCTIONS_H
#include "Debug.h"
/*
Leetcode: Exclusive Time Of Functions
On a single threaded CPU, we execute some functions.
Each function has a unique id between 0 and N-1.
We store logs in timestamp order that describe when a function is entered or exited.
Each log is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}".
For example, "0:start:3" means the function with id 0 started at the beginning of timestamp 3.  "1:end:2" means the function with id 1 ended at the end of timestamp 2.
A function's exclusive time is the number of units of time spent in this function.
Note that this does not include any recursive calls to child functions.
The CPU is single threaded which means that only one function is being executed at a given time unit.
Return the exclusive time of each function, sorted by their function id.
 */
class ExclusiveTimeOfFunctions
{
public:
    std::vector<int> Recur(int n, std::vector<std::string> & logs)
    {
        std::vector<int> res(n, 0);//total time for each function
        int cur = 0;
        int N = logs.size();
        while (cur < N)
        {
            recur(logs, cur, res);
        }
        return res;
    }
private:
    int recur(std::vector<std::string> & logs, int & cur, std::vector<int> & res)
    {
        std::vector<int> v = parse(logs[cur]);//must be a start
        int begin = v[2];
        ++cur;
        while (true)
        {
            std::vector<int> v2 = parse(logs[cur]);
            if (v2[1] == 1)//end of v
            {
                res[v[0]] += (v2[2]-begin+1);//include end
                //std::cout << v[0] << ":+end" << (v2[2]-begin+1) << std::endl;
                ++cur;
                return v2[2];
            }
            else//start
            {
                res[v[0]] += (v2[2]-begin);//exclude start
                //std::cout << v[0] << ":+start" << (v2[2]-begin) << std::endl;
                int end = recur(logs, cur, res);
                begin = end+1;
            }
        }

        return 0;//doesn't matter
    }

    std::vector<int> parse(const std::string & s)
    {
        int N = s.size();
        std::vector<int> res(3, 0);
        int i = 0;
        while (isdigit(s[i]))
            ++i;
        //std::cout << s.substr(0, i) << std::endl;
        res[0] = stoi(s.substr(0, i));
        ++i;
        if (s[i] == 's')
            res[1] = 0;
        else
            res[1] = 1;
        while (s[i] != ':')
            ++i;
        ++i;
        int begin = i;
        while (isdigit(s[i]))
            ++i;
        //std::cout << "->" << begin << i << s.substr(begin, i-begin) << std::endl;
        res[2] = stoi(s.substr(begin, i-begin));
        //std::cout << res[0] << "," << res[1] << "," << res[2] << std::endl;
        return res;
    }
};
#endif
