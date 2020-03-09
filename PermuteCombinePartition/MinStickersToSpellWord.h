#ifndef _MIN_STICKERS_TO_SPELL_WORD_H
#define _MIN_STICKERS_TO_SPELL_WORD_H
#include "Debug.h"
/*
Leetcode: Stickers To Spell Word
We are given N different types of stickers.
Each sticker has a lowercase English word on it.
You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.
You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.
Example 1:
Input:
["with", "example", "science"], "thehat"
Output:
3
Explanation:
We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
Example 2:
Input:
["notice", "possible"], "basicbasic"
Output:
-1
Explanation:
We can't form the target "basicbasic" from cutting letters from the given stickers.
Note:
stickers has length in the range [1, 50].
stickers consists of lowercase English words (without apostrophes).
target has length in the range [1, 15], and consists of lowercase English letters.
In all test cases, all words were chosen randomly from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.
The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be solved within 35ms on average.
 */
class MinStickersToSpellWord
{
public:
    MinStickersToSpellWord(){}

    int BFS(const std::vector<std::string> & stickers, std::string target)
    {
        int N = stickers.size();
        std::vector<std::vector<int>> charCount(N, std::vector<int>(26, 0));
        for (int i = 0; i < N; ++i)
            for (auto & c : stickers[i])
                ++charCount[i][c-'a'];
        std::unordered_set<std::string> visit;
        std::string empty = ToStr(std::vector<int>(26, 0));
        std::vector<int> curTgt(26, 0);
        for (auto & c : target)
            ++curTgt[c-'a'];
        visit.insert(ToStr(curTgt));
        std::queue<std::vector<int>> que;
        que.push(curTgt);
        int res = 0;
        while(!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                curTgt = que.front(); que.pop();
                for (int i = 0; i < N; ++i)
                {
                    bool applied = false;
                    std::vector<int> nxtTgt(26, 0);
                    for (int j = 0; j < 26; ++j)
                        if (curTgt[j])
                        {
                            if (charCount[i][j])
                            {
                                applied = true;
                                if (curTgt[j]-charCount[i][j] > 0)
                                    nxtTgt[j] = curTgt[j]-charCount[i][j];
                            }
                            else
                                nxtTgt[j] = curTgt[j];
                        }
                    if (!applied) continue;
                    std::string nxtTgtStr = ToStr(nxtTgt);
                    if (nxtTgtStr == empty) return res+1;
                    if (!visit.count(nxtTgtStr))
                    {
                        visit.insert(nxtTgtStr);
                        que.push(nxtTgt);
                    }
                }
            }
            ++res;
        }
        return -1;
    }

    int DFS_DP(const std::vector<std::string> & stickers, std::string target)
    {
        int N = stickers.size();
        std::vector<std::vector<int>> charCount(N, std::vector<int>(26, 0));
        for (int i = 0; i < N; ++i)
            for (auto & c : stickers[i])
                ++charCount[i][c-'a'];
        std::unordered_map<std::string,int> dp;//<wordConfig,minNumOfSticks>
        std::string empty = ToStr(std::vector<int>(26, 0));
        dp[empty] = 0;//base case
        std::vector<int> curTgt(26, 0);
        for (auto & c : target)
            ++curTgt[c-'a'];

        int res = recur(charCount, curTgt, dp);
        std::cout << "MinStickersToSpellWord DFS_DP for \"" << target << "\" from [" << Debug::ToStr1D<std::string>()(stickers) << "]: " << res << std::endl;
        return res;
    }
private:
    int recur(std::vector<std::vector<int>> & charCount, std::vector<int> & curTgt, std::unordered_map<std::string,int> & dp)
    {
        std::string curTgtStr = ToStr(curTgt);
        if (dp.count(curTgtStr)) return dp[curTgtStr];
        int N = charCount.size();
        int res = INT_MAX;
        for (int i = 0; i < N; ++i)
        {
            bool applied = false;

            std::vector<int> nxtTgt(26, 0);
            for (int j = 0; j < 26; ++j)
                if (curTgt[j])
                {
                    if (charCount[i][j])
                    {
                        applied = true;
                        if (curTgt[j] - charCount[i][j] > 0)//has leftover
                            nxtTgt[j] = curTgt[j] - charCount[i][j];
                    }
                    else
                        nxtTgt[j] = curTgt[j];
                }

            if (!applied) continue;
            int count = recur(charCount, nxtTgt, dp);
            if (count != -1)
                res = std::min(res, count + 1);
        }
        return dp[curTgtStr] = res == INT_MAX ? -1 : res;
    }
    std::string ToStr(const std::vector<int> & charCount)
    {
        std::ostringstream oss;
        for (auto & i : charCount)
            oss << i << ",";
        return oss.str();
    }
};
/*
MinStickersToSpellWord DFS_DP for "thehat" from [with, example, science]: 3
 */
#endif
