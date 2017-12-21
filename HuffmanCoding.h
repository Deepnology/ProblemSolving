#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <functional>
#include "PrintBinaryTree.h"
#include "Debug.h"
/*
Elements of programming interview, Greedy: Implement Huffman coding
One way to compress a large text is by building a code book which maps each character to a bit string, referred to as its code word.
For the compression to be reversible, it is sufficient that the code words have the property that no code word is a prefix of another.
Since the objective is to compress the text, we want to assign the shorter strings to more common characters and the longer strings to less common characters.
Given a set of symbols with corresponding frequencies, find a code book that has the smallest average code length.

first.first: character, first.second: frequency, second: HuffmanCode
{ { 'a', 8.17 }, "1110" }, { { 'b', 1.49 }, "110000" }, { { 'c', 2.78 }, "01001" }, { { 'd', 4.25 }, "11111" }, { { 'e', 12.70 }, "100" }, { { 'f', 2.23 }, "00101" },
{ { 'g', 2.02 }, "110011" }, { { 'h', 6.09 }, "0110" }, { { 'i', 6.97 }, "1011" }, { { 'j', 0.15 }, "001001011" }, { { 'k', 0.77 }, "0010011" }, { { 'l', 4.03 }, "11110" },
{ { 'm', 2.41 }, "00111" }, { { 'n', 6.75 }, "1010" }, { { 'o', 7.51 }, "1101" }, { { 'p', 1.93 }, "110001" }, { { 'q', 0.10 }, "001001001" }, { { 'r', 5.99 }, "0101" },
{ { 's', 6.33 }, "0111" }, { { 't', 9.06 }, "000" }, { { 'u', 2.76 }, "01000" }, { { 'v', 0.98 }, "001000" }, { { 'w', 2.36 }, "00110" }, { { 'x', 0.15 }, "001001010" },
{ { 'y', 1.97 }, "110010" }, { { 'z', 0.07 }, "001001000" }

1. Sort characters in increasing order of frequencies and create a binary tree node for each character.
   Denote the set just created by S.
2. Create a new node n whose children are the two nodes with smallest frequencies and assign n's frequency to be the sum of the frequencies of its children.
3. Remove the children from S and add n to S.
   Repeat from step2 till S consists of a single node, which is the root.
Mark all the left edges with 0 and the right edges with 1.
The path from the root to a leaf node yields the bit string encodeding the corresponding character.

The reasoning behind the Huffman algorithm yielding the minimum average code length is based on a induction on the number of symbols.
The induction step itself makes use of proof by contradition, with the two leaves in the Huffman tree corresponding to the rarest symbols playing a central role.

UseMinHeap: O(nlogn) time, bounded by insertion of minHeap
*/
class HuffmanCoding
{
public:
	HuffmanCoding(){}
	~HuffmanCoding(){}
	typedef std::pair<std::pair<char, double>, std::string> Symbol;//first.first: character, first.second: frequency, second: HuffmanCode
	struct TreeNode
	{
		TreeNode() : val(0), symbol(nullptr), left(nullptr), right(nullptr){}
		TreeNode(double freq, Symbol * s, TreeNode * l, TreeNode * r) : val(freq), symbol(s), left(l), right(r){}
		~TreeNode(){}
		double val;//frequency
		Symbol * symbol;
		TreeNode * left;
		TreeNode * right;
	};
	struct TreeNodeGreater
	{
		bool operator()(const TreeNode * a, const TreeNode * b) const
		{
			return a->val > b->val;//frequency
		}
	};
	void Encode(std::vector<Symbol> & v)
	{
		//1. generate leaf nodes and push in minHeap associated with frequency
		std::priority_queue<TreeNode *, std::vector<TreeNode *>, TreeNodeGreater> minHeap;
		int N = v.size();
		for (int i = 0; i < N; ++i)
		{
			minHeap.push(new TreeNode(v[i].first.second, &v[i], nullptr, nullptr));
		}

		//2. bottom-up build the tree from leaf nodes (similar to construct binary tree from preorder traversal w/ null nodes using stack from right to left)
		while (minHeap.size() > 1)
		{
			TreeNode * left = minHeap.top();
			minHeap.pop();
			TreeNode * right = minHeap.top();
			minHeap.pop();
			TreeNode * parent = new TreeNode(left->val + right->val, nullptr, left, right);
			minHeap.push(parent);
		}
		//now minHeap.top() is the root

		//3. in-order traversal to assign Huffman code
		this->AssignHuffmanCode(minHeap.top(), std::string());

		std::ostringstream oss;
		PrintBinaryTree<TreeNode, std::ostringstream>(minHeap.top(), oss);
		//std::cout << oss.str() << std::endl;
		std::cout << "HuffmanCoding Encode: " << Debug::ToStr1D_<char, double, std::string>()(v) << std::endl;
	}
private:
	void AssignHuffmanCode(const TreeNode * root, const std::string & code)
	{
		if (root)
		{
			if (root->symbol)//leaf node
			{
				root->symbol->second = code;
			}
			else//non-leaf node
			{
				this->AssignHuffmanCode(root->left, code + '0');
				this->AssignHuffmanCode(root->right, code + '1');
			}
		}
	}
};

template<>
std::string PrintBinaryTree<HuffmanCoding::TreeNode, std::ostringstream>::selectVal2(int depth, HuffmanCoding::TreeNode * n)
{
	if (n->symbol)
		return std::to_string(n->symbol->first.first);
	else
		return "N";
}
/*
HuffmanCoding Encode: [(a,8.17),1110], [(b,1.49),110000], [(c,2.78),01001], [(d,4.25),11111], [(e,12.7),100], [(f,2.23),00101], [(g,2.02),110011], [(h,6.09),0110], [(i,6.97),1011], [(j,0.15),001001011], [(k,0.77),0010011], [(l,4.03),11110], [(m,2.41),00111], [(n,6.75),1010], [(o,7.51),1101], [(p,1.93),110001], [(q,0.1),001001001], [(r,5.99),0101], [(s,6.33),0111], [(t,9.06),000], [(u,2.76),01000], [(v,0.98),001000], [(w,2.36),00110], [(x,0.15),001001010], [(y,1.97),110010], [(z,0.07),001001000]
*/
#endif