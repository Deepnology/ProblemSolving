#ifndef _COMPARE_STRETCHY_WORDS_H
#define _COMPARE_STRETCHY_WORDS_H
#include "Debug.h"
/*
Leetcode: Expressive Words
Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".
In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".
For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation:
choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.
For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has size less than 3.
Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".
If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = S.
Given a list of query words, return the number of words that are stretchy.
Example:
Input:
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation:
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.

Leetcode: Long Pressed Name
Your friend is typing his name into a keyboard.
Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.
You examine the typed characters of the keyboard.
Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.
Example 1:
Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.
Example 2:
Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed output.
Example 3:
Input: name = "leelee", typed = "lleeelee"
Output: true
Example 4:
Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.
 */
class CompareStretchyWords
{
public:
    CompareStretchyWords(){}
    ~CompareStretchyWords(){}

    //same as Long Pressed Names
    int Count(std::string S, std::vector<std::string> && words)
    {
        int res = 0;
        for (auto & s : words)
        {
            if (CompareStretchy(S, s))
                ++res;
        }
        std::cout << "CompareStretchyWords for [" << S << "] from [" << Debug::ToStr1D<std::string>()(words) << "]: " << res << std::endl;
        return res;
    }
    bool CompareStretchy(const std::string & a, const std::string & b)
    {
        int N = a.size();
        int M = b.size();
        int i = 0;
        int j = 0;
        while (i < N && j < M)
        {
            if (a[i] != b[j])
                return false;
            int ii = i;
            while (ii < N && a[ii] == a[i])
                ++ii;
            int jj = j;
            while (jj < M && b[jj] == b[j])
                ++jj;
            int lenA = ii-i;
            int lenB = jj-j;
            if ((lenA < 3 && lenA != lenB) || //1 or 2 repeated chars must be exactly same
                (lenA >= 3 && !(lenA >= lenB))) //3 or more repeated chars must be equal or more
                return false;
            i = ii;
            j = jj;
        }
        return i == N && j == M;
    }

    bool IsLongPressedName(std::string name, std::string typed)
    {
        //same as Expressive Words
        int N = typed.size();
        int M = name.size();
        int i = 0;
        int j = 0;
        while (i < N && j < M)
        {
            if (typed[i] != name[j])
                return false;
            int ii = i;
            while (ii < N && typed[ii] == typed[i])
                ++ii;
            int jj = j;
            while (jj < M && name[jj] == name[j])
                ++jj;
            int lenA = ii-i;
            int lenB = jj-j;
            if ((lenA < 2 && lenA != lenB) || //1 char must be exactly same
                (lenA >= 2 && !(lenA >= lenB))) //2 or more repeated chars must be equal or more
                return false;
            i = ii;
            j = jj;
        }
        std::cout << "CompareStretchyWords IsLongPressedName for [" << name << "], [" << typed << "]: " << (i==N&&j==M) << std::endl;
        return i == N && j == M;
    }
};
/*
CompareStretchyWords for [heeellooo] from [hello, hi, helo]: 1
CompareStretchyWords IsLongPressedName for [leelee], [lleeelee]: 1
 */
#endif
