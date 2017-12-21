#ifndef _PERMUTATIONS_H
#define _PERMUTATIONS_H
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
print all permutations of a given string
http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
check the tree diagram
1. Find all from a no duplicate array
Given a collection of numbers, return all possible permutations.
A string of length n has n! permutation
O(n*n!)
A: string
n: ending index of the string
depth: starting index of the string

2. Find all unique permutations from a duplicate array
Given a collection of numbers that might contain duplicates, return all possible unique permutations.
*/

class Permutations
{
public:
	Permutations(){}
	~Permutations(){}

	
	std::vector<std::string> FindAll_FromNoDupArray_InPlace_Recur(char A[], int n)
	{
		std::vector<std::string> res;
		this->permute_FromNoDupArray_Recur(A, n, 0, res);
		std::cout << "Permutations FindAll_FromNoDupArray_InPlace_Recur for \"" << Debug::ToStr1D<char>()(A, n) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	void permute_FromNoDupArray_Recur(char A[], int n, int depth, std::vector<std::string> & res)
	{
		if (depth == n)//the next level of depth
		{
			res.push_back(std::string(A));
		}
		else
		{
			//when depth == 0: swap A[0] with the remaining chars
			//when depth > 0: A[0]~A[depth-1] are fixed, swap A[depth] with the remaining chars
			for (int i = depth; i < n; ++i)
			{
				std::swap(A[depth], A[i]);
				this->permute_FromNoDupArray_Recur(A, n, depth + 1, res);
				std::swap(A[depth], A[i]);//backtrack: swap back
			}
		}
	}




public:
	
	std::vector<std::string> FindAllUnique_FromDupArray_InPlace_Recur(char A[], int n)
	{
		std::vector<std::string> res;
		std::pair<char, char> rootSwapPair(0, 0);
		std::list<std::pair<char, char> > leftSiblingSwapPairList;
		//no need to sort the string because now we check all the left siblings' swap pairs
		this->permute_FromDupArray_Recur(A, n, 0, rootSwapPair, leftSiblingSwapPairList, res);
		std::cout << "Permutations FindAllUnique_FromDupArray_InPlace_Recur for \"" << Debug::ToStr1D<char>()(A, n) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	//return a pair of chars that are swapped in this call at current depth
	std::pair<char, char> permute_FromDupArray_Recur(char A[], int n, int depth,
		std::pair<char, char> thisSwapPair, std::list<std::pair<char, char> > leftSiblingSwapPairList,
		std::vector<std::string> & res)
	{
		if (leftSiblingSwapPairList.size() > 0 && 
			(std::find(leftSiblingSwapPairList.begin(), leftSiblingSwapPairList.end(), thisSwapPair)) != leftSiblingSwapPairList.end())
		{
			//skip: has left sibling and one of left sibling swap pair is equal to this swap pair
			return thisSwapPair;
		}
		if (depth == n)//the next level of depth
		{
			res.push_back(std::string(A));
			return thisSwapPair;
		}
		std::list<std::pair<char, char> > leftSiblingSwapListCurDepth;
		for (int i = depth; i < n; ++i)
		{
			std::pair<char, char> nextPair;//the next pair of (smallerChar, biggerChar) that is going to be swapped
			if (A[depth] <= A[i])
				nextPair = std::pair<char, char>(A[depth], A[i]);
			else
				nextPair = std::pair<char, char>(A[i], A[depth]);

			std::swap(A[depth], A[i]);
			leftSiblingSwapListCurDepth.push_back(
				this->permute_FromDupArray_Recur(A, n, depth + 1, nextPair, leftSiblingSwapListCurDepth, res));
			std::swap(A[depth], A[i]);
		}
		return thisSwapPair;
	}
};
/*
Permutations FindAll_FromNoDupArray_InPlace_Recur for "A, B, C": ABC, ACB, BAC, BCA, CBA, CAB
Permutations FindAllUnique_FromDupArray_InPlace_Recur for "A, B, A, B": ABAB, ABBA, AABB, BAAB, BABA, BBAA
*/

#endif