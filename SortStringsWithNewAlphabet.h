#ifndef _SORT_STRINGS_WITH_NEW_ALPHABET_H
#define _SORT_STRINGS_WITH_NEW_ALPHABET_H
#include "Debug.h"
/*
Lintcode: Word Sorting
Give a new alphabet, such as {c,b,a,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}.
Sort the string array according to the new alphabet.
Given Alphabet = {c,b,a,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}, String array = {cab,cba,abc}, return {cba,cab,abc}.
Explanation:
According to the new dictionary order, output the sorted result {cba, cab, abc}.
Given Alphabet = {z,b,a,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,c}, String array = {bca,czb,za,zba,ade}, return {zba,za,bca,ade,czb}.
Explanation:
According to the new dictionary order, output the sorted result {zba,za,bca,ade,czb}.
 */
class SortStringsWithNewAlphabet
{
public:
    SortStringsWithNewAlphabet(){}

    std::string SortString(const std::string & alpha, const std::string & word)
    {
        std::vector<int> count(26, 0);
        for (const auto & c : word)
            ++count[c-'a'];
        std::string res;
        for (const auto & c : alpha)
        {
            while (count[c-'a']--)
                res.push_back(c);
        }
        std::cout << "SortStringsWithNewAlphabet for alpha=[" << alpha << "], word=[" << word << "]: " << res << std::endl;
        return res;
    }

    std::vector<std::string> SortStringArr(const std::string & alpha, const std::vector<std::string> & words)
    {
        int N = alpha.size();
        std::unordered_map<char,int> toIdx;
        for (int i = 0; i < N; ++i)
            toIdx[alpha[i]] = i;
        std::vector<std::string> res(words);
        std::sort(res.begin(), res.end(), [&](const std::string & s1, const std::string & s2)
        {
            int N = s1.size();
            int M = s2.size();
            int minLen = std::min(N, M);
            int i = 0;
            while (i < minLen)
            {
                int idx1 = toIdx[s1[i]];
                int idx2 = toIdx[s2[i]];
                if (idx1 < idx2)
                    return true;
                else if (idx1 > idx2)
                    return false;
                else
                    ++i;
            }
            if (i == N)
                return true;
            return false;
        });
        std::cout << "SortStringsWithNewAlphabet for alpha=[" << alpha << "], words=[" << Debug::ToStr1D<std::string>()(words) << "]: " << Debug::ToStr1D<std::string>()(res) << std::endl;
        return res;
    }

    std::vector<std::string> SortStringArr_Trie(const std::string & alpha, const std::vector<std::string> & words)//best
    {
        //1. build a trie with every word in words
        //where the trie node has children in new alphabet order

        //2. traverse the trie to output all words

        return std::vector<std::string>();
    }
};
/*
SortStringsWithNewAlphabet for alpha=[zyxwvutsr], word=[xrxuvwztvxzyurz]: zzzyxxxwvvuutrr
SortStringsWithNewAlphabet for alpha=[zyxwvutsr], words=[suzwy, rux, yrwu, tyzvx, rt, xvyr, r, uv, vs, w, y, z]: z, y, yrwu, xvyr, tyzvx, w, vs, uv, rt, suzwy, r, rux
 */
#endif
