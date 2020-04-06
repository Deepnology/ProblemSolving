#ifndef _POW_OF_10_H
#define _POW_OF_10_H
/*
 *
 */
class PowOf10
{
public:
    PowOf10(){}
    bool IsPowOf10(int i)
    {
        while (i > 9 && i % 10 == 0)
            i /= 10;
        return i == 1;
    }
};
#endif
