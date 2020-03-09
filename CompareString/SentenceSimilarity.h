/*CompareString*/
#ifndef SENTENCE_SIMILARITY_H
#define SENTENCE_SIMILARITY_H
#include "Debug.h"
/*
Leetcode: Sentence Similarity
Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
For example, "great acting skills" and "fine drama talent" are similar, if the similar word pairs are pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]].
Note that the similarity relation is not transitive.
For example, if "great" and "fine" are similar, and "fine" and "good" are similar, "great" and "good" are not necessarily similar.
However, similarity is symmetric.
For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar
, even though there are no specified similar word pairs.
Finally, sentences can only be similar if they have the same number of words.
So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
Note:
The length of words1 and words2 will not exceed 1000.
The length of pairs will not exceed 2000.
The length of each pairs[i] will be 2.
The length of each words[i] and pairs[i][j] will be in the range [1, 20].

Leetcode: Sentence Similarity II
Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].
Note that the similarity relation is transitive.
For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.
Similarity is also symmetric.
For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
Also, a word is always similar with itself.
For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.
Finally, sentences can only be similar if they have the same number of words.
So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
Note:
The length of words1 and words2 will not exceed 1000.
The length of pairs will not exceed 2000.
The length of each pairs[i] will be 2.
The length of each words[i] and pairs[i][j] will be in the range [1, 20].
*/
class SentenceSimilarity
{
public:
    SentenceSimilarity(){}

    void Test(const std::vector<std::string> & words1, const std::vector<std::string> & words2, const std::vector<std::pair<std::string, std::string>> & pairs)
    {
        bool res1 = WithoutTransitive(words1, words2, pairs);
        bool res2 = WithTransitive(words1, words2, pairs);
        std::cout << "SentenceSimilarity W/, W/O Transitive for [" << Debug::ToStr1D<std::string>()(words1) << "], [" << Debug::ToStr1D<std::string>()(words2) << "], w/ pairs=[" << Debug::ToStr1D<std::string>()(pairs) << "]: " << res1 << "," << res2 << std::endl;
    }

    bool WithoutTransitive(const std::vector<std::string> & words1, const std::vector<std::string> & words2, const std::vector<std::pair<std::string, std::string>> & pairs)
    {
        if (words1.size() != words2.size()) return false;
        std::unordered_map<std::string, std::unordered_set<std::string>> map;
        for (const auto & p : pairs)
        {
            map[p.first].insert(p.second);
            map[p.second].insert(p.first);
        }
        int N = words1.size();
        for (int i = 0; i < N; ++i)
        {
            if (words1[i] == words2[i]) continue;
            if (map.count(words1[i]) && map[words1[i]].count(words2[i]) == 0) return false;
            if (map.count(words2[i]) && map[words2[i]].count(words1[i]) == 0) return false;
        }
        return true;
    }


    bool WithTransitive(const std::vector<std::string> & words1, const std::vector<std::string> & words2, const std::vector<std::pair<std::string, std::string>> & pairs)
    {
        if (words1.size() != words2.size()) return false;
        std::unordered_map<std::string, std::unordered_set<std::string>> map;
        for (const auto & p : pairs)
        {
            map[p.first].insert(p.second);
            map[p.second].insert(p.first);
        }
        int N = words1.size();
        for (int i = 0; i < N; ++i)
        {
            if (words1[i] == words2[i]) continue;
            if (map.count(words1[i]) == 0) return false;
            if (map.count(words2[i]) == 0) return false;
            std::unordered_set<std::string> visit;
            if (!recur(words1[i], words2[i], visit, map)) return false;
        }
        return true;
    }
    bool recur(const std::string & src, const std::string & tgt, std::unordered_set<std::string> & visit, std::unordered_map<std::string, std::unordered_set<std::string>> & map)
    {
        if (map[src].count(tgt)) return true;
        visit.insert(src);
        for (const auto nxt : map[src])
            if (!visit.count(nxt) && recur(nxt, tgt, visit, map))
                return true;
        return false;
    }
};
/*
SentenceSimilarity W/, W/O Transitive for [great, acting, skills], [fine, drama, talent], w/ pairs=[[great,good], [fine,good], [acting,drama], [skills,talent]]: 0,1
 */
#endif
