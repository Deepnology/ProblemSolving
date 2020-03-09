#ifndef UNIFORM_RANDOM_H
#define UNIFORM_RANDOM_H
//#include <ctime>
#include <iostream>
#include <chrono>
#include <cmath>
#include <random>
#include <functional>
/*
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/UniformRandom.h
*/
// UniformRandom class
//
// CONSTRUCTION: with (a) no initializer or (b) a long
//     that specifies the initial state of the generator.
//     This random number generator is similar to 
//     drand48 in C/C++.
//
// ******************PUBLIC OPERATIONS*********************
//     Return a random number according to some distribution:
// int nextInt( )                          --> Uniform
// int nextDouble( )                       --> Uniform, [0 to 1)
// int nextInt( int high )                 --> Uniform [0..high)
// int nextInt( int low, int high )        --> Uniform [low..high)
// long nextLong( )                        --> Uniform

/**
* Uniform Random Number generator class, using a 48-bit
* linear congruential generator.
*/
class Random48
{
private:
	static long long currentTimeMicroSeconds()
	{
		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		return (std::chrono::duration_cast<std::chrono::microseconds>(now)).count();
	}
public:
	/**
	* Construct this Random object with specified initial state
	*/
	Random48(long long initialValue = currentTimeMicroSeconds())
	{
		m_state = initialValue & MASK;
	}
	/**
	* Return a pseudorandom int, and change the
	* internal state.
	*/
	int nextInt()
	{
		return this->next(32);
	}
	/**
	* Return a pseudorandom int in range [0..high),
	* and change the internal state.
	*/
	int nextInt(int high)
	{
		return static_cast<int>(abs(this->nextLong() % high));
	}
	/**
	* Return a pseudorandom double in the range [0..1)
	* and change the internal state.
	*/
	double nextDouble()
	{
		return ((static_cast<long long>((this->next(26))) << 27) + this->next(27))
			/ static_cast<double>(1LL << 53);
	}
	/**
	* Return an int in the closed range [low,high], and
	* change the internal state.
	*/
	int nextInt(int low, int high)
	{
		return nextInt(high - low + 1) + low;
	}
	/**
	* Return a 64-bit long, and change the internal state.
	* Note that all longs can be generated.
	*/
	long long nextLong()
	{
		return ((static_cast<long long>(this->next(32))) << 32) + this->next(32);
	}
private:
	long long m_state;

	static const long long A = 25214903917LL;
	static const long long C = 11;
	static const long long M = (1LL << 48);
	static const long long MASK = M - 1;

	/**
	* Return specified number of random bits
	*/
	int next(int bits)
	{
		m_state = (A * m_state + C) & MASK;

		return (int)(m_state >> (48 - bits));
	}
};

// UniformRandom class
//
// CONSTRUCTION: with (a) no initializer or (b) a int
//     that specifies the initial state of the generator.
//     This random number generator uses the 32-bit Mersenne Twister
//
// ******************PUBLIC OPERATIONS*********************
//     Return a random number according to some distribution:
// int nextInt( )                          --> Uniform
// int nextDouble( )                       --> Uniform, [0 to 1)
// int nextInt( int high )                 --> Uniform [0..high)
// int nextInt( int low, int high )        --> Uniform [low..high)


static int currentTimeSeconds()
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
	return (int)std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

/**
* Uniform Random Number generator class, using C++ Mersenne Twister.
*/
class UniformRandom
{
public:
	UniformRandom(int seed = currentTimeSeconds()) : m_generator( seed )
	{}
	/**
	* Return a pseudorandom int.
	*/
	int nextInt()
	{
		static std::uniform_int_distribution<unsigned int> distribution;
		return distribution(m_generator);
	}
	/**
	* Return a pseudorandom int in range [0..high).
	*/
	int nextInt(int high)
	{
		return this->nextInt(0, high - 1);
	}
	/**
	* Return a pseudorandom double in the range [0..1).
	*/
	double nextDouble()
	{
		static std::uniform_real_distribution<double> distribution(0, 1);
		return distribution(m_generator);
	}
	/**
	* Return an int in the closed range [low,high].
	*/
	int nextInt(int low, int high)
	{
		std::uniform_int_distribution<int> distribution(low, high);
		return distribution(m_generator);
	}
private:
	std::mt19937 m_generator;
};
#endif

