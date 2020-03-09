#ifndef _LEVENSHTEIN_DISTANCE2_H
#define _LEVENSHTEIN_DISTANCE2_H


#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>
#include <cctype>
#include <sstream>

struct trie2
{
	typedef std::map<std::string, trie2*> next_t;

	trie2(): next(next_t())
	{

	}
	void insert(std::deque<std::string> w)
	{
		w.push_front(std::string("$"));
		int sz = w.size();
		trie2 * n = this;
		for (int i = 0; i < sz; ++i)
		{
			if (n->next.find(w[i]) == n->next.end())
				n->next[w[i]] = new trie2();
			n = n->next[w[i]];
		}
		n->word = w;
	}
	void traverse(int currentLayer)
	{
		std::cout << "=> " << this->convertToString() << std::endl;

		std::ostringstream oss;
		for (int i = 0; i < currentLayer; ++i)
			oss << " ";
		for (next_t::iterator i = next.begin(); i != next.end(); ++i)
		{
			std::cout << oss.str() << "." << (*i).first << std::endl;
			(*i).second->traverse(++currentLayer);
		}
	}

	next_t next;
	std::deque<std::string> word;

private:
	std::string convertToString()
	{
		std::ostringstream oss;
		for (std::deque<std::string>::iterator i = word.begin(); i != word.end(); ++i)
		{
			oss << *i;
			if (i != word.end() - 1)
				oss << " ";
		}
		return oss.str();
	}
};






struct LevenshteinDistance2
{
	LevenshteinDistance2(): tree(), min_cost(0)
	{

	}
	void insert(std::deque<std::string> s)
	{
		tree.insert(s);
	}
	void traverse()
	{
		tree.traverse(0);
	}
	int search(std::deque<std::string> word)
	{
		word.push_front(std::string("$"));
	
		int sz = word.size();
		min_cost = 0x3f3f3f3f;
		//std::cout << "Init min_cost = " << min_cost << std::endl;


		std::vector<int> current_row(sz + 1);

		// Naive DP initialization
		for (int i = 0; i < sz; ++i) 
			current_row[i] = i;
		current_row[sz] = sz;

		// For each letter in the root map wich matches with a
		// 	letter in word, we must call the search
		for (int i = 0 ; i < sz; ++i) 
		{
			if (tree.next.find(word[i]) != tree.next.end()) 
			{
				search_impl(tree.next[word[i]], word[i], current_row, word);
			}
		}

		return min_cost;
	}

private:
	trie2 tree;	
	int min_cost;// The minimum cost of a given word to be changed to a word of the dictionary

	void search_impl(trie2 * tree, std::string ch, std::vector<int> last_row, const std::deque<std::string> & word)
	{
		int sz = last_row.size();

		std::vector<int> current_row(sz);
		current_row[0] = last_row[0] + 1;

		// Calculate the min cost of insertion, deletion, match or substution
		int insert_or_del, replace;
		for (int i = 1; i < sz; ++i) 
		{
			insert_or_del = std::min(current_row[i-1] + 1, last_row[i] + 1);
			replace = (word[i-1].compare(ch) == 0) ? last_row[i-1] : (last_row[i-1] + 1);

			current_row[i] = std::min(insert_or_del, replace);
		}

		// When we find a cost that is less than the min_cost, is because
		// it is the minimum until the current row, so we update
		if ((current_row[sz-1] < min_cost) && (!tree->word.empty())) 
		{
			min_cost = current_row[sz-1];
		}

		// If there is an element wich is smaller than the current minimum cost,
		// 	we can have another cost smaller than the current minimum cost
		if (*min_element(current_row.begin(), current_row.end()) < min_cost) 
		{
			for (trie2::next_t::iterator it = tree->next.begin(); it != tree->next.end(); ++it) 
			{
				search_impl(it->second, it->first, current_row, word);
			}
		}
	}
	
};


#endif