#ifndef _IS_LITTLE_ENDIAN_H
#define _IS_LITTLE_ENDIAN_H
#include "Debug.h"
/*
Facebook Reality Labs
Niantic Labs
 */
class IsLittleEndian
{
public:
    IsLittleEndian(){}

    bool Check()
    {
        int num = 1;
        char * p = (char *) &num;
        bool res;
        if (*p == 1) res = true;
        else res = false;

        std::cout << "IsLittleEndian Check: " << res << std::endl;
        return res;
    }
    int ReverseBytesToConvert(int num)
    {
        int byte0 = (num & 0x000000ff) >> 0;
        int byte1 = (num & 0x0000ff00) >> 8;
        int byte2 = (num & 0x00ff0000) >> 16;
        int byte3 = (num & 0xff000000) >> 24;
        int res = (byte0 << 24)|(byte1 << 16)|(byte2 << 8)|byte3;

        std::cout << "IsLittleEndian ReverseBytesToConvert for " << num << ": " << res << std::endl;
        return res;
    }
    int ReverseBytesToConvert2(int num)
    {
        int byte0 = num & ((1<<8)-1);
        int byte1 = (num >> 8) & ((1 << 8) - 1);
        int byte2 = (num >> 16) & ((1 << 8) - 1);
        int byte3 = (num >> 24) & ((1 << 8) - 1);
        int res = (byte0 << 24)|(byte1 << 16)|(byte2 << 8)|byte3;

        std::cout << "IsLittleEndian ReverseBytesToConvert2 for " << num << ": " << res << std::endl;
        return res;
    }
    int ReverseBytesToConvert3(int num)
    {
        char * p = (char *) &num;
        int res = 0;
        for (int i = 0; i < 4; ++i)
        {
            res <<= 8;
            res |= *p;
            ++p;
        }

        std::cout << "IsLittleEndian ReverseBytesToConvert3 for " << num << ": " << res << std::endl;
        return res;
    }
};
/*
IsLittleEndian Check: 1
IsLittleEndian ReverseBytesToConvert for 255: -16777216
IsLittleEndian ReverseBytesToConvert2 for 255: -16777216
IsLittleEndian ReverseBytesToConvert3 for 255: -16777216
 */
#endif
