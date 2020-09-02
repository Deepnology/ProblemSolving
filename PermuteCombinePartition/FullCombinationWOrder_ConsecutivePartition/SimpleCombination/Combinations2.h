#ifndef COMBINATIONS_2_H
#define COMBINATIONS_2_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5756808635351040
Print combinations of strings from list of list of strings.
Example: [quick, slow], [brown, red], [fox, dog]
Output:
quick brown fox
quick brown do
quick red fox
quick red dog
slow brown fox
slow brown dog
slow red fox
slow red dog
*/
class Combinations2
{
public:
	Combinations2(){}
	~Combinations2(){}

	void Recur(const std::vector<std::vector<std::string> > & strs)
	{
		std::vector<std::vector<std::string> > res;
		std::vector<std::string> path;
		this->recur(strs, 0, path, res);
		Debug::Print2D<std::string>()(strs, false);
		std::cout << "Combinations2 for the above strs:" << std::endl;
		Debug::Print2D<std::string>()(res, false);
	}
private:
	void recur(const std::vector<std::vector<std::string> > & strs, int start, std::vector<std::string> & path, std::vector<std::vector<std::string> > & res)
	{
		int N = strs.size();
		if (start == N)
		{
			res.push_back(path);
			return;
		}
		int M = strs[0].size();
		for (int i = 0; i < M; ++i)
		{
			path.push_back(strs[start][i]);
			this->recur(strs, start + 1, path, res);
			path.pop_back();
		}
	}
};
/*
[rY][cX]
Row#0	= quick, medium, slow
Row#1	= brown, red, silver
Row#2	= fox, dog, cat

Combinations2 for the above strs:
[rY][cX]
Row#0	= quick, brown, fox
Row#1	= quick, brown, dog
Row#2	= quick, brown, cat
Row#3	= quick, red, fox
Row#4	= quick, red, dog
Row#5	= quick, red, cat
Row#6	= quick, silver, fox
Row#7	= quick, silver, dog
Row#8	= quick, silver, cat
Row#9	= medium, brown, fox
Row#10	= medium, brown, dog
Row#11	= medium, brown, cat
Row#12	= medium, red, fox
Row#13	= medium, red, dog
Row#14	= medium, red, cat
Row#15	= medium, silver, fox
Row#16	= medium, silver, dog
Row#17	= medium, silver, cat
Row#18	= slow, brown, fox
Row#19	= slow, brown, dog
Row#20	= slow, brown, cat
Row#21	= slow, red, fox
Row#22	= slow, red, dog
Row#23	= slow, red, cat
Row#24	= slow, silver, fox
Row#25	= slow, silver, dog
Row#26	= slow, silver, cat
*/
#endif