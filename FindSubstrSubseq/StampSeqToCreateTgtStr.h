#ifndef _STAMP_SEQ_TO_CREATE_TGT_STR_H
#define _STAMP_SEQ_TO_CREATE_TGT_STR_H
#include "Debug.h"
/*
Leetcode: Stamping The Sequence
You want to form a target string of lowercase letters.
At the beginning, your sequence is target.length '?' marks.  You also have a stamp of lowercase letters.
On each turn, you may place the stamp over the sequence, and replace every letter in the sequence with the corresponding letter from the stamp.  You can make up to 10 * target.length turns.
For example, if the initial sequence is "?????", and your stamp is "abc",  then you may make "abc??", "?abc?", "??abc" in the first turn.  (Note that the stamp must be fully contained in the boundaries of the sequence in order to stamp.)
If the sequence is possible to stamp, then return an array of the index of the left-most letter being stamped at each turn.  If the sequence is not possible to stamp, return an empty array.
For example, if the sequence is "ababc", and the stamp is "abc", then we could return the answer [0, 2], corresponding to the moves "?????" -> "abc??" -> "ababc".
Also, if the sequence is possible to stamp, it is guaranteed it is possible to stamp within 10 * target.length moves.  Any answers specifying more than this number of moves will not be accepted.
Example 1:
Input: stamp = "abc", target = "ababc"
Output: [0,2]
([1,0,2] would also be accepted as an answer, as well as some other answers.)
Example 2:
Input: stamp = "abca", target = "aabcaca"
Output: [3,0,1]
 */
class StampSeqToCreateTgtStr
{
public:
    std::vector<int> GetStampIndices(std::string stamp, std::string target)
    {
        int N = target.size();
        int M = stamp.size();
        int numReplace = 0;
        std::vector<int> visit(N, 0);
        std::vector<int> res;
        while (numReplace < N) //greedy replace target substr that match stamp w/ *
        {
            int curReplace = 0;
            for (int i = 0; i <= N-M; ++i)
            {
                if (!visit[i] && canReplaceAt(stamp, target, i))
                {
                    visit[i] = 1;
                    curReplace += replaceAt(stamp, target, i);
                    res.push_back(i);
                }
            }
            if (curReplace == 0) return std::vector<int>();
            numReplace += curReplace;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
private:
    bool canReplaceAt(const std::string & stamp, const std::string & target, int idx)
    {
        int M = stamp.size();
        for (int i = 0; i < M; ++i)
            if (target[idx+i] != '*' && stamp[i] != target[idx+i])
                return false;
        return true;
    }
    int replaceAt(const std::string & stamp, std::string & target, int idx)
    {
        int M = stamp.size();
        int count = 0;
        for (int i = idx; i < idx+M; ++i)
            if (target[i] != '*')
            {
                ++count;
                target[i] = '*';
            }
        return count;
    }
};
#endif
