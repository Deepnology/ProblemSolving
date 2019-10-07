#ifndef _STREAM_CHARACTER_CHECKER_H
#define _STREAM_CHARACTER_CHECKER_H
#include "Debug.h"
/*
Leetcode: Stream of Characters
Implement the StreamChecker class as follows:
StreamChecker(words): Constructor, init the data structure with the given words.
query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.
Example:
StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
streamChecker.query('a');          // return false
streamChecker.query('b');          // return false
streamChecker.query('c');          // return false
streamChecker.query('d');          // return true, because 'cd' is in the wordlist
streamChecker.query('e');          // return false
streamChecker.query('f');          // return true, because 'f' is in the wordlist
streamChecker.query('g');          // return false
streamChecker.query('h');          // return false
streamChecker.query('i');          // return false
streamChecker.query('j');          // return false
streamChecker.query('k');          // return false
streamChecker.query('l');          // return true, because 'kl' is in the wordlist
Note:
1 <= words.length <= 2000
1 <= words[i].length <= 2000
Words will only consist of lowercase English letters.
Queries will only consist of lowercase English letters.
The number of queries is at most 40000.
 */
class StreamCharacterChecker
{
    struct Trie
    {
        std::vector<Trie*> children;
        bool isKey;
        Trie():children(26,NULL), isKey(false){}
    };
    void Insert(Trie * root, const std::string & s)
    {
        int N = s.size();
        int cur = 0;
        while (true)
        {
            if (!root->children[s[cur]-'a'])
                root->children[s[cur]-'a'] = new Trie;
            if (cur == N-1)
            {
                root->children[s[cur]-'a']->isKey = true;
                break;
            }
            root = root->children[s[cur]-'a'];
            ++cur;
        }
    }
    bool Search(Trie * root, std::string & s)
    {
        if (root == NULL) return false;
        int N = s.size();
        int cur = 0;
        while (cur < N)
        {
            root = root->children[s[cur]-'a'];
            if (!root) return false;
            if (root->isKey) return true; //return true as long as meets a key
            ++cur;
        }
        return false;
    }
    Trie * root;
    int maxWordLen = 0;
    std::string cachedStr;
public:
    StreamCharacterChecker(std::vector<std::string> & words)
    {
        root = new Trie;
        for (auto s : words)
        {
            std::reverse(s.begin(), s.end());
            Insert(root, s);
            maxWordLen = std::max(maxWordLen, (int)s.size());
        }
    }

    bool query(char letter)
    {
        cachedStr = letter + cachedStr;
        if (cachedStr.size() > maxWordLen)
            cachedStr.pop_back();
        return Search(root, cachedStr);
    }
};
#endif
