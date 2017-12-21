#ifndef _LEVENSHTEIN_DISTANCE_H
#define _LEVENSHTEIN_DISTANCE_H
//Levenshtein distance

#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

struct trie
{
	typedef std::map<char, trie*> next_t;

	trie(): next(next_t())
	{

	}
	void insert(std::string w)
	{
		w = std::string("$") + w;
		int sz = w.size();
		trie * n = this;
		for (int i = 0; i < sz; ++i)
		{
			if (n->next.find(w[i]) == n->next.end())
				n->next[w[i]] = new trie();
			n = n->next[w[i]];
		}
		n->word = w;
	}
	void traverse(int currentLayer)
	{
		std::cout << "=> " << word << std::endl;

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
	std::string word;

};






struct LevenshteinDistance
{
	LevenshteinDistance(): tree(), min_cost(0)
	{

	}
	void insert(std::string s)
	{
		tree.insert(s);
	}
	void traverse()
	{
		tree.traverse(0);
	}
	int search(std::string word)
	{
		word = std::string("$") + word;
	
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
	trie tree;
	int min_cost;// The minimum cost of a given word to be changed to a word of the dictionary

	void search_impl(trie* tree, char ch, std::vector<int> last_row, const std::string & word)
	{
		int sz = last_row.size();

		std::vector<int> current_row(sz);
		current_row[0] = last_row[0] + 1;

		// Calculate the min cost of insertion, deletion, match or substution
		int insert_or_del, replace;
		for (int i = 1; i < sz; ++i) 
		{
			insert_or_del = std::min(current_row[i-1] + 1, last_row[i] + 1);
			replace = (word[i-1] == ch) ? last_row[i-1] : (last_row[i-1] + 1);

			current_row[i] = std::min(insert_or_del, replace);
		}

		// When we find a cost that is less than the min_cost, is because
		// it is the minimum until the current row, so we update
		if ((current_row[sz-1] < min_cost) && (tree->word != "")) 
		{
			min_cost = current_row[sz-1];
		}

		// If there is an element wich is smaller than the current minimum cost,
		// 	we can have another cost smaller than the current minimum cost
		if (*min_element(current_row.begin(), current_row.end()) < min_cost) 
		{
			for (trie::next_t::iterator it = tree->next.begin(); it != tree->next.end(); ++it) 
			{
				search_impl(it->second, it->first, current_row, word);
			}
		}
	}
};

/*
=> 
.$
=> 
 .h
=> 
  .o
=> 
   .w
=> 
    . 
=> 
     .a
=> 
      .r
=> 
       .e
=> 
        . 
=> 
         .y
=> 
          .o
=> 
           .u
=> 
            . 
=> 
             .d
=> 
              .o
=> 
               .i
=> 
                .n
=> 
                 .g
=> $how are you doing
LevenshteinDistance = 19
*/
#endif