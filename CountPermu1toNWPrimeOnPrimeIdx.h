#ifndef _COUNT_PERMU_1_TO_N_W_PRIME_ON_PRIME_IDX_H
#define _COUNT_PERMU_1_TO_N_W_PRIME_ON_PRIME_IDX_H
#include "Debug.h"
/*
Leetcode: Prime Arrangements
Return the number of permutations of 1 to n so that prime numbers are at prime indices (1-indexed.)
(Recall that an integer is prime if and only if it is greater than 1, and cannot be written as a product of two positive integers both smaller than it.)
Since the answer may be large, return the answer modulo 10^9 + 7.
Example 1:
Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at index 1.
Example 2:
Input: n = 100
Output: 682289015
 */
class CountPermu1toNWPrimeOnPrimeIdx
{
public:
    int Solve(int n)
    {
        int mod = pow(10,9)+7;
        std::vector<int> primes = Sieve(n);
        int primeCount = primes.size();
        int res = 1;
        //num of permutations for primeCount prime-nums is primeCount!
        for (int i = primeCount; i >= 1; --i)
            res = (1LL*res*i)%mod;
        //num of permutations for (n-primeCount) non-prime-nums is (n-primeCount)!
        for (int i = n-primeCount; i >= 1; --i)
            res = (1LL*res*i)%mod;

        std::cout << "CountPermu1toNWPrimeOnPrimeIdx for " << n << ": " << res << std::endl;
        return res;
    }

    std::vector<int> Sieve(int n)
    {
        std::vector<int> isPrime(n + 1, 1);
        //isPrime[i]: 1 means i is a prime

        for (int i = 2; i * i <= n; ++i)//starting from 2
        {
            if (!isPrime[i])
                continue;

            //now i is a prime: mark all i's multiples as non-prime starting from i^2
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = 0;
        }

        std::vector<int> res;
        for (int i = 2; i <= n; ++i)
            if (isPrime[i])
                res.push_back(i);

        return res;
    }
};
/*
CountPermu1toNWPrimeOnPrimeIdx for 100: 682289015
 */
#endif
