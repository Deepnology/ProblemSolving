#ifndef TOP_K_FREQUENT_STRINGS_H
#define TOP_K_FREQUENT_STRINGS_H
#include "Debug.h"
/*
Leetcode: Top K Frequent Words
Given a non-empty list of words, return the k most frequent elements.
Your answer should be sorted by frequency from highest to lowest.
If two words have the same frequency, then the word with the lower alphabetical order comes first. //for this reason, cannot use QuickSelect
Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 <= k <= number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.
*/
class TopKFrequentStrings
{
public:
	TopKFrequentStrings() {}
private:
	struct Trie
	{
		Trie(bool isWord_ = false) :isWord(isWord_), children(26, NULL) {}
		std::vector<Trie*> children;
		bool isWord;
	};
	Trie * Insert(Trie * root, const std::string & word)
	{
		if (root == NULL)
			root = new Trie();
		Trie * cur = root;
		int N = word.size();
		for (int i = 0; i < N; ++i)
		{
			if (cur->children[word[i] - 'a'] == NULL)
			{
				if (i == N - 1)
					cur->children[word[i] - 'a'] = new Trie(true);
				else
					cur->children[word[i] - 'a'] = new Trie(false);
			}
			else
			{
				if (i == N - 1)
					cur->children[word[i] - 'a']->isWord = true;
			}
			cur = cur->children[word[i] - 'a'];
		}
		return root;
	}
	void CollectRecur(Trie * cur, std::string & path, std::vector<std::string> & res, int k)
	{
		if (cur == NULL) return;
		if (cur->isWord)
			res.push_back(path);
		if ((int)res.size() >= k) return;
		for (int i = 0; i < 26; ++i)
		{
			if (cur->children[i])
			{
				path.push_back(i + 'a');
				CollectRecur(cur->children[i], path, res, k);
				path.pop_back();
			}
		}
	}

public:
	std::vector<std::string> BucketSort_Trie(std::vector<std::string> & words, int k)//O(n) time, O(n) space
	{
		std::unordered_map<std::string, int> map;
		for (auto & s : words)
			++map[s];

		std::vector<std::string> res;
		
		//use Bucket Sort + Trie, where each bucket is an individual Trie tree
		int N = words.size();//max freq will be N
		std::vector<Trie*> buckets(N + 1, NULL);
		for (auto & p : map)
		{
			Trie * root = buckets[p.second];
			root = Insert(root, p.first);
			buckets[p.second] = root;
		}
		for (int i = N; i > 0 && (int)res.size() < k; --i)
		{
			if (buckets[i])
			{
				std::string path;
				CollectRecur(buckets[i], path, res, k);
			}
		}

		std::cout << "TopKFrequentStrings BucketSort_Trie for \"" << Debug::ToStr1D<std::string>()(words) << "\", k=" << k << ": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	struct Greater
	{
		bool operator()(const std::pair<int, std::string> & a, const std::pair<int, std::string> & b) const
		{
			return a.first != b.first ? a.first > b.first : a.second < b.second;
		}
	};
	std::vector<std::string> MinHeap(std::vector<std::string> & words, int k)//O(nlogk) time, O(n) space
	{
		std::unordered_map<std::string,int> map;
        for (auto & s : words)
            ++map[s];
        
        std::vector<std::string> res;
        
        std::priority_queue<std::pair<int,std::string>, std::vector<std::pair<int,std::string>>, Greater> minHeap;
        for (auto & p : map)
        {
            minHeap.push({p.second,p.first});
            if ((int)minHeap.size() > k)
                minHeap.pop();
        }
        while (!minHeap.empty())
            res.push_back(minHeap.top().second), minHeap.pop();
        std::reverse(res.begin(), res.end());

		std::cout << "TopKFrequentStrings MinHeap for \"" << Debug::ToStr1D<std::string>()(words) << "\", k=" << k << ": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
TopKFrequentStrings BucketSort_Trie for "i, love, leetcode, i, love, coding", k=2: i, love
TopKFrequentStrings MinHeap for "i, love, leetcode, i, love, coding", k=2: i, love
*/
#endif
