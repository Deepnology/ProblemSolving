#ifndef _NEXT_GREATER_PRIME_PALINDROME_NUM_H
#define _NEXT_GREATER_PRIME_PALINDROME_NUM_H
#include "Debug.h"
/*
Leetcode: Prime Palindrome
Find the smallest prime palindrome greater than or equal to N.
Recall that a number is prime if it's only divisors are 1 and itself, and it is greater than 1.
For example, 2,3,5,7,11 and 13 are primes.
Recall that a number is a palindrome if it reads the same from left to right as it does from right to left.
For example, 12321 is a palindrome.
Example 1:
Input: 6
Output: 7
Example 2:
Input: 8
Output: 11
Example 3:
Input: 13
Output: 101
 */
class NextGreaterPrimePalindromeNum
{
public:
    bool IsPalindrome(int x)
    {
        int reverse = 0, src = x;
        while (x)
        {
            reverse = reverse * 10 + x % 10;
            x /= 10;
        }
        return reverse == src;
    }

    int NextPalindrome(int x) //x is already a palindrome num
    {
        //ex: 123321 or 12321
        int n = 0;
        while(pow(10, n) <= x)
            ++n;
        //now pow(10, n) = 1000000 or 100000 where n = 6 or 5
        for (int m = (n - 1) / 2; m >= 0; m --)
        {
            int mid = x / (int)pow(10, m) % 10;//right of mid pair for even digit num OR mid for odd digit num, ex: 3 for 123321 and 12321
            if (mid < 9)//can incr mid (on right side) and mid's corresponding digit on left side
            {
                if (n % 2 && m == (n-1)/2)//12321 => 12421
                    return x + pow(10, m);
                return x + pow(10, m+1) + pow(10, m);//123321 => 124421
            }
        }

        //all digits are 9s, e.g., 999999 or 99999, return 1000001 or 100001
        return x + 2;
    }

    bool IsPrime(int n)
    {
        if (n == 1)
            return false;
        if (n == 2 || n == 3)
            return true;
        if (n % 2 == 0)
            return false;
        for (int i = 3; i * i <= n; i += 2)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    int Solve(int N)
    {
        int origin = N;

        while (!IsPalindrome(N))
            ++N;
        while(!IsPrime(N))
            N = NextPalindrome(N);

        std::cout << "NextGreaterPrimePalindromeNum for " << origin << ": " << N << std::endl;
        return N;
    }
};
/*
NextGreaterPrimePalindromeNum for 123321: 1003001
NextGreaterPrimePalindromeNum for 12321: 12421
NextGreaterPrimePalindromeNum for 99: 101
 */
#endif
