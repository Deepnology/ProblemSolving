#ifndef _VOWEL_SPELL_CHECKER_H
#define _VOWEL_SPELL_CHECKER_H
#include "Debug.h"
/*
Leetcode: Vowel Spellchecker
Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
For a given query word, the spell checker handles two categories of spelling mistakes:
Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
In addition, the spell checker operates under the following precedence rules:
When the query exactly matches a word in the wordlist (case-sensitive), you should return the same word back.
When the query matches a word up to capitlization, you should return the first such match in the wordlist.
When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
If the query has no matches in the wordlist, you should return the empty string.
Given some queries, return a list of words answer, where answer[i] is the correct word for query = queries[i].
Example 1:
Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
 */
class VowelSpellChecker
{
public:
    VowelSpellChecker(){}
    ~VowelSpellChecker(){}

    std::vector<std::string> UseHashMaps(std::vector<std::string> && wordlist, std::vector<std::string> && queries)
    {
        std::unordered_set<std::string> words(wordlist.begin(), wordlist.end());
        std::unordered_map<std::string,std::string> lowerToWord;
        std::unordered_map<std::string,std::string> deVowelToWord;
        for (const auto & s : wordlist)
        {
            lowerToWord.insert({toLower(s),s});//insert only for the 1st occcurrence
            deVowelToWord.insert({deVowel(s),s});//insert only for the 1st occurrence
        }
        std::vector<std::string> res;
        for (auto & s : queries)
        {
            std::string r;
            if (words.count(s)) r = s;
            else if (lowerToWord.count(toLower(s))) r = lowerToWord[toLower(s)];
            else if (deVowelToWord.count(deVowel(s))) r = deVowelToWord[deVowel(s)];
            else r = "";
            res.push_back(r);
        }
        std::cout << "VowelSpellChecker for [" << Debug::ToStr1D<std::string>()(wordlist) << "], [" << Debug::ToStr1D<std::string>()(queries) << "]: " << Debug::ToStr1D<std::string>()(res) << std::endl;
        return res;
    }
    std::string toLower(const std::string & s)
    {
        std::string res(s);
        for (auto & c : res)
            c = std::tolower(c);
        return res;
    }
    std::string deVowel(const std::string & s)
    {
        std::string res = toLower(s);
        for (auto & c : res)
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                c = '#';
        return res;
    }
};
/*
VowelSpellChecker for [KiTe, kite, hare, Hare], [kite, Kite, KiTe, Hare, HARE, Hear, hear, keti, keet, keto]: kite, KiTe, KiTe, Hare, hare, , , KiTe, , KiTe
 */
#endif
