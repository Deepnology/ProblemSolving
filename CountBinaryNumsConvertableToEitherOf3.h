#ifndef _COUNT_BINARY_NUMS_CONVERTABLE_TO_EITHER_OF_3_H
#define _COUNT_BINARY_NUMS_CONVERTABLE_TO_EITHER_OF_3_H
#include "Debug.h"
/*
Jump Trading
Integer A is convertible to integer B if and only if all the set bits' positions in B are also set bits in A.

ex:
11 1111 1111 1111 1111 1111 1001 1111 (1073741727)
can be converted by
11 1111 1111 1111 1111 1111 1001 1111
11 1111 1111 1111 1111 1111 1011 1111
11 1111 1111 1111 1111 1111 1101 1111
11 1111 1111 1111 1111 1111 1111 1111

11 1111 1111 1111 1111 1111 0011 1111 (1073741631)
can be converted by
11 1111 1111 1111 1111 1111 0011 1111
11 1111 1111 1111 1111 1111 0111 1111
11 1111 1111 1111 1111 1111 1011 1111
11 1111 1111 1111 1111 1111 1111 1111

11 1111 1111 1111 1111 1111 0110 1111 (1073741535)
can be converted by
11 1111 1111 1111 1111 1111 0110 1111
11 1111 1111 1111 1111 1111 0111 1111
11 1111 1111 1111 1111 1111 1110 1111
11 1111 1111 1111 1111 1111 1111 1111

Given 3 non-negative integers with 30 bits, count total number of integers that can be converted to either one of them.
(the answer cannot include duplicates)
For the above example, there are 8 numbers in total.

ex:
11 1111 1111 1111 1111 1111 1111 0001 (1073741809)
11 1111 1111 1111 1111 1111 1111 0000 (1073741808)
11 1111 1111 1111 1111 1111 1111 0001 (1073741809)
there are 16 numbers in total.

 */
class CountBinaryNumsConvertableToEitherOf3
{
public:
    CountBinaryNumsConvertableToEitherOf3(){}
private:
    std::string ToBin(int n)
    {
        std::string res;
        for (int i = 0; i <= 29; ++i)
        {
            int cur = (n >> i);
            res = ((cur & 1) ? "1" : "0") + res;
        }
        return res;
    }
public:
    int Solve(int A, int B, int C)
    {
        std::string a = ToBin(A);
        std::string b = ToBin(B);
        std::string c = ToBin(C);

        int count0abc = 0;
        for (int i = 0; i <= 29; ++i)
            if (a[i] == '0' && b[i] == '0' && c[i] == '0')
                ++count0abc;
        int totalabc = pow(2, count0abc);

        int count0ab = 0;
        for (int i = 0; i <= 29; ++i)
            if (a[i] == '0' && b[i] == '0')
                ++count0ab;
        int totalab = pow(2, count0ab);

        int count0bc = 0;
        for (int i = 0; i <= 29; ++i)
            if (b[i] == '0' && c[i] == '0')
                ++count0bc;
        int totalbc = pow(2, count0bc);

        int  count0ac = 0;
        for (int i = 0; i <= 29; ++i)
            if (a[i] == '0' && c[i] == '0')
                ++count0ac;
        int totalac = pow(2, count0ac);

        int count0a = 0;
        for (int i = 0; i <= 29; ++i)
            if (a[i] == '0')
                ++count0a;
        int totala = pow(2, count0a);

        int count0b = 0;
        for (int i = 0; i <= 29; ++i)
            if (b[i] == '0')
                ++count0b;
        int totalb = pow(2, count0b);

        int count0c = 0;
        for (int i = 0; i <= 29; ++i)
            if (c[i] == '0')
                ++count0c;
        int totalc = pow(2, count0c);

        int res = totala + totalb + totalc - totalab - totalbc - totalac + totalabc;

        std::cout << "CountBinaryNumsConvertableToEitherOf3 for [" << A << "," << B << "," << C << "]: " << std::endl;
        std::cout << totala << "+" << totalb << "+" << totalc << "-" << totalab << "-" << totalbc << "-" << totalac << "+" << totalabc << "=" << res << std::endl;
        return res;
    }
};
/*
CountBinaryNumsConvertableToEitherOf3 for [1073741727,1073741631,1073741535]:
4+4+4-2-1-2+1=8
CountBinaryNumsConvertableToEitherOf3 for [1073741809,1073741808,1073741809]:
8+16+8-8-8-8+8=16
 */
#endif
