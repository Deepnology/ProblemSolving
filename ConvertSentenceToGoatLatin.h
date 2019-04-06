#ifndef _CONVERT_SENTENCE_TO_GOAT_LATIN_H
#define _CONVERT_SENTENCE_TO_GOAT_LATIN_H
#include "Debug.h"
/*
Leetcode: Goat Latin
A sentence S is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.
We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)
The rules of Goat Latin are as follows:
If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
For example, the word 'apple' becomes 'applema'.
If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
Return the final sentence representing the conversion from S to Goat Latin.
Example 1:
Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:
Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 */
class ConvertSentenceToGoatLatin
{
public:
    ConvertSentenceToGoatLatin(){}
    ~ConvertSentenceToGoatLatin(){}

    std::string Solve(std::string S)
    {
        std::istringstream iss(S);
        std::string cur;
        std::unordered_set<char> vowel({'a','e','i','o','u'});
        std::string append("ma");
        std::string res;
        while (iss >> cur)
        {
            if (!vowel.count(tolower(cur[0])))
                cur = cur.substr(1) + cur.substr(0, 1);
            append += "a";
            cur = cur + append;
            res += cur + " ";

        }
        res = res.substr(0, res.size()-1);
        std::cout << "ConvertSentenceToGoatLatin for [" << S << "]: " << res << std::endl;
        return res;
    }
};
/*
ConvertSentenceToGoatLatin for [The quick brown fox jumped over the lazy dog]: heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa
 */
#endif
