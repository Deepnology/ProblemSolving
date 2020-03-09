#ifndef SET_SUBSTR_BITS_H
#define SET_SUBSTR_BITS_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Cracking the coding interview 5.1
You are given two 32-bit numbers, N and M, and two bit positions, i and j.
Write a method to set all bits between i and j in N equal to M 
(e.g., M becomes a substring of N located at i and starting at j).
EXAMPLE:
Input: N = 10000000000, M = 10101, i = 2, j = 6
Output: N = 10001010100

N: str
M: substr
i: lower
j: higher
*/
class SetSubstrBits
{
public:
	SetSubstrBits(){}
	~SetSubstrBits(){}

	int Solve(int str, int substr, int lower, int higher)
	{
		int max = ~0;//all 1's

		int leftOnes = max - ((1 << higher) - 1);	//11111111111111111111111111000000
		
		int rightOnes = (1 << lower) - 1;			//00000000000000000000000000000011
		
		int maskMiddleZeros = leftOnes | rightOnes;	//11111111111111111111111110000011
		
		int strWithMiddleZeros = str & maskMiddleZeros;
		
		int substrShifted = substr << lower;
		
		int add2 = strWithMiddleZeros | substrShifted;

		std::cout << "SetSubstrBits for \"" << KeyGenAux().UIntToBinStr(str) << "\", \"" << KeyGenAux().UIntToBinStr(substr) << "\", btw \"" << lower << "\", " << higher << "\": " << KeyGenAux().UIntToBinStr(add2) << std::endl;
		return add2;
	}
};
/*
SetSubstrBits for "00000000000000001000000000000000", "00000000000000000000000000010101", btw "2", 6": 00000000000000001000000001010100
*/
#endif