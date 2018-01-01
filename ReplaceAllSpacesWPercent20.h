#ifndef REPLACE_ALL_SPACES_W_PERCENT_20_H
#define REPLACE_ALL_SPACES_W_PERCENT_20_H
#include <iostream>
#include <string>
#include <vector>
/*
Cracking the coding interview: Array and String

*/
class ReplaceAllSpacesWPercent20
{
public:
	ReplaceAllSpacesWPercent20(){}
	~ReplaceAllSpacesWPercent20(){}

	void InPlace(std::string && s)
	{
		std::string before = s;
		int N = s.size();
		int spaceCount = 0;
		for (int i = 0; i < N; ++i)
			if (s[i] == ' ')
				++spaceCount;
		int M = N + spaceCount * 2;
		s.resize(M);

		int newEnd = M - 1;
		for (int oldCur = N - 1; oldCur >= 0; --oldCur)
		{
			if (s[oldCur] == ' ')
			{
				s[newEnd--] = '0';
				s[newEnd--] = '2';
				s[newEnd--] = '%';
			}
			else
			{
				s[newEnd--] = s[oldCur];
			}
		}

		std::cout << "ReplaceAllSpacesWPercent20 for \"" << before << "\": " << s << std::endl;
	}
};
/*
ReplaceAllSpacesWPercent20 for " the sky is blue! hello world ": %20the%20sky%20is%20blue!%20hello%20world%20
*/
#endif