#ifndef RAND_WO_MODULO_BIAS_H
#define RAND_WO_MODULO_BIAS_H
#include <stdlib.h>
#include <time.h>
#include <iostream>
/*
Elements of programming interview, Array: Sample offline data
http://stackoverflow.com/questions/10984974/why-do-people-say-there-is-modulo-bias-when-using-a-random-number-generator
Modulo Bias:
rand() is a pseudo-random number generator which chooses a natural number between 0 and RAND_MAX, which is a constant defined in stdlib.h.
If we want to generate a random number between 0 and 2, we can use rand()%3 to get a random number in [0,3), where RAND_MAX is 10 (a number that is not divisble by 3) for example.
The generated random number is in the expected range, but it is not uniformly distributed (with equal probability).
When rand() returns 0,3,6,9, rand()%3 == 0.
When rand() returns 1,4,7,10, rand()%3 == 1.
When rand() returns 2,5,8, rand()%3 == 2.

The ways to generate a random number with equal probability in [0,upperBound) with rand() which gives random number in [0, RAND_MAX]:
1. discard all numbers that are greater than or equal to upperBound and repeat calling rand()
2. discard all numbers that are greater than or equal to a max number that is divisible by upperBound and repeat calling rand(), then let the result number modulo upperBound
*/
class RandWoModuloBias
{
public:
	RandWoModuloBias(){}
	~RandWoModuloBias(){}

	int BruteForce(int upperBound)
	{
		int res = rand();
		int count = 1;
		while (res >= upperBound)
		{
			res = rand();
			++count;
		}

		std::cout << "RandWoModuloBias BruteForce for \"" << upperBound << "\": " << res << ", count=" << count << std::endl;
		return res;
	}

	int Faster(int upperBound)
	{
		int res = rand();
		int count = 1;
		/*
		upperBound = (0, RAND_MAX]
		res = [0, upperBound)
		rand() = [0, RAND_MAX]
		We want to generate a random number in [0, a_max_num_that_is_divisible_by_upperBound)
		, i.e., [a_number_that_modulo_upperBound_is_0, a_number_that_modulo_upperBound_is_0)
		, so that "the generated random number modulo upperBound" can be uniformly distributed in [0, upperBound].

		The max num that is divisible by upperBound = RAND_MAX - (RAND_MAX % upperBound)
		*/
		while (upperBound < RAND_MAX && res >= RAND_MAX - (RAND_MAX % upperBound))
		{
			res = rand();
			++count;
		}
		/*now res is in [0, a_max_num_that_is_divisible_by_upperBound)*/
		res %= upperBound;

		std::cout << "RandWoModuloBias Faster for \"" << upperBound << "\": " << res << ", count=" << count << std::endl;
		return res;
	}
};
/*
RandWoModuloBias BruteForce for "101": 53, count=396
RandWoModuloBias Faster for "101": 35, count=1
*/
#endif