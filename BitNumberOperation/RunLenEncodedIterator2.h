#ifndef _RUN_LEN_ENCODED_ITERATOR_2_H
#define _RUN_LEN_ENCODED_ITERATOR_2_H
#include "Debug.h"
/*
Leetcode: Design Compressed String Iterator
Design and implement a data structure for a compressed string iterator. It should support the following operations: next and hasNext.
The given compressed string will be in the form of each letter followed by a positive integer representing the number of this letter existing in the original uncompressed string.
next() - if the original string still has uncompressed characters, return the next letter; Otherwise return a white space.
hasNext() - Judge whether there is any letter needs to be uncompressed.
Note:
Please remember to RESET your class variables declared in StringIterator, as static/class variables are persisted across multiple test cases. Please see here for more details.
Example:
StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");
iterator.next(); // return 'L'
iterator.next(); // return 'e'
iterator.next(); // return 'e'
iterator.next(); // return 't'
iterator.next(); // return 'C'
iterator.next(); // return 'o'
iterator.next(); // return 'd'
iterator.hasNext(); // return true
iterator.next(); // return 'e'
iterator.hasNext(); // return false
iterator.next(); // return ' '
 */
class RunLenEncodedIterator2
{
    std::string s;
    int curIdx;
    int curCount;
    int curTotal;
    int curLen;
public:
    RunLenEncodedIterator2(std::string compressedString) : s(compressedString), curIdx(0), curCount(0), curTotal(0), curLen(0)
    {
        int end = curIdx+1;
        while (end < s.size() && isdigit(s[end]))
            ++end;
        curLen = end-curIdx-1;
        curTotal = stoi(s.substr(curIdx+1,curLen));
    }

    char Next()
    {
        while (curIdx < s.size())
        {
            if (curCount == curTotal)
            {
                curCount = 0;
                curIdx += curLen+1;
                if (curIdx == s.size())
                    break;
                int end = curIdx+1;
                while (end < s.size() && isdigit(s[end]))
                    ++end;
                curLen = end-curIdx-1;
                curTotal = stoi(s.substr(curIdx+1,curLen));
            }
            else
            {
                ++curCount;
                std::cout << "RunLenEncodedIterator2 Next: " << s[curIdx] << std::endl;
                return s[curIdx];
            }
        }
        std::cout << "RunLenEncodedIterator2 Next: " << std::endl;
        return ' ';
    }

    bool HasNext()
    {
        bool res = !(curIdx+curLen+1 == s.size() && curCount==curTotal || curIdx == s.size());
        std::cout << "RunLenEncodedIterator2 HasNext: " << res << std::endl;
        return res;
    }
};
/*
RunLenEncodedIterator2 Next: L
RunLenEncodedIterator2 Next: e
RunLenEncodedIterator2 Next: e
RunLenEncodedIterator2 Next: t
RunLenEncodedIterator2 Next: C
RunLenEncodedIterator2 Next: o
RunLenEncodedIterator2 Next: d
RunLenEncodedIterator2 HasNext: 1
RunLenEncodedIterator2 Next: e
RunLenEncodedIterator2 HasNext: 0
RunLenEncodedIterator2 Next:
 */
#endif
