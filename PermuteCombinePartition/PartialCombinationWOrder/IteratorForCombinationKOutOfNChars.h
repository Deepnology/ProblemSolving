#ifndef _ITERATOR_FOR_COMBINATION_K_OUT_OF_N_CHARS_H
#define _ITERATOR_FOR_COMBINATION_K_OUT_OF_N_CHARS_H
#include "Debug.h"
/*
Leetcode: Iterator for Combination
Design an Iterator class, which has:
A constructor that takes a string characters of sorted distinct lowercase English letters and a number combinationLength as arguments.
A function next() that returns the next combination of length combinationLength in lexicographical order.
A function hasNext() that returns True if and only if there exists a next combination.
Example:
CombinationIterator iterator = new CombinationIterator("abc", 2); // creates the iterator.
iterator.next(); // returns "ab"
iterator.hasNext(); // returns true
iterator.next(); // returns "ac"
iterator.hasNext(); // returns true
iterator.next(); // returns "bc"
iterator.hasNext(); // returns false
 */
class IteratorForCombinationKOutOfNChars
{
    struct Greater
    {
        bool operator()(const std::string & a, const std::string & b) const
        {
            return a > b;
        }
    };
    void genRecur(std::string & s, int len, int i, std::string curS, std::priority_queue<std::string, std::vector<std::string>, Greater> & minHeap)
    {
        int N = s.size();
        if (curS.size() == len)
        {
            minHeap.push(curS);
            return;
        }
        for (int j = i; j+(len-curS.size())-1 < N; ++j)
        {
            curS.push_back(s[j]);
            genRecur(s, len, j+1, curS, minHeap);
            curS.pop_back();
        }
    }
    std::priority_queue<std::string, std::vector<std::string>, Greater> minHeap;
public:
    IteratorForCombinationKOutOfNChars(std::string characters, int combinationLength)
    {
        genRecur(characters, combinationLength, 0, "", minHeap);
    }

    std::string next()
    {
        std::string res = minHeap.top();
        minHeap.pop();
        return res;
    }

    bool hasNext()
    {
        return !minHeap.empty();
    }
};
#endif
