#ifndef LOG_H
#define LOG_H
#include <iostream>
/*
http://graphics.stanford.edu/~seander/bithacks.html
aka the position of the highest bit set
*/
class Log
{
public:
	Log(){}
	~Log(){}

	/*O(N) time*/
	unsigned int Base2_MSB(unsigned int v)
	{
		int res = 0;
		int n = v;
		while (n >>= 1)
			++res;

		std::cout << "Log Base2_MSB for \"" << v << "\": " << res << std::endl;
		return res;
	}

	/*O(logN) time*/
	unsigned int Base2_Binary(unsigned int v)
	{
		static const unsigned int b[] = { 0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000 };
		static const unsigned int S[] = { 1, 2, 4, 8, 16 };

		unsigned int res = 0;
		int n = v;
		for (int i = 4; i >= 0; --i)
		{
			if (n & b[i])
			{
				n >>= S[i];
				res |= S[i];
			}
		}

		std::cout << "Log Base2_Binary for \"" << v << "\": " << res << std::endl;
		return res;
	}

	unsigned int Base10(unsigned int v)
	{
		int res = 0;
		res = (v >= 1000000000) ? 9 : (v >= 100000000) ? 8 : (v >= 10000000) ? 7 :
			(v >= 1000000) ? 6 : (v >= 100000) ? 5 : (v >= 10000) ? 4 :
			(v >= 1000) ? 3 : (v >= 100) ? 2 : (v >= 10) ? 1 : 0;

		std::cout << "Log Base10 for \"" << v << "\": " << res << std::endl;
		return res;
	}
};
#endif