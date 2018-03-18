/*MEMO*/
#ifndef VALID_NUMBER_H
#define VALID_NUMBER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <regex>
/*
Leetcode: Valid Number
// Validate if a given string is numeric.
//
// Some examples:
// "0" => true
// " 0.1 " => true
// "abc" => false
// "1 a" => false
// "2e10" => true
// Note: It is intended for the problem statement to be ambiguous. You should
// gather all requirements up front before implementing one.
//
// Complexity:
// BruteForce: O(n) time, O(1) space
// Regular Expression: depending on language
// Finite State Machine: O(n) time, O(1) space

follow: �e����
be followed by: �᭱��

Rules:
1.
'+'/'-' must be no '+'/'-'/'.'/number before it, unless it follows 'E'/'e'.
'+'/'-' must be followed by '.'/number.
(+7.e-9 or +.7e-9)
2.
'E'/'e' must be no 'E'/'e' before it.
'E'/'e' must have a number before it.
'E'/'e' must be followed by '+'/'-'/number.
(+9e-3 or +9.e-3 or +9.e3)
3.
'.' must be no 'E'/'e'/'.' before it.
'.' must either follow a number or be followed by a number.
(9. or 9.e-3 or .9 or .9e-3 or +.9 or +.9e-3)
*/
class ValidNumber
{
public:
	ValidNumber(){}
	~ValidNumber(){}

    bool Better(const std::string & s)
    {
        bool res = this->better(s);
        std::cout << "ValidNumber Better for \"" << s << "\": " << res << std::endl;
        return res;
    }
private:
    bool better(const std::string & s)
    {
        int N = s.size();
        if (N == 0)
            return false;

        int i = 0;
        //1. skip leading space
        while(i < N && s[i] == ' ')
            ++i;
        //2. check sign
        if (i < N && (s[i] == '+' || s[i] == '-'))
            ++i;
        //3. check countDigit and countPoint
        int countDigit = 0;
        int countPoint = 0;
        while (i < N && (isdigit(s[i]) || s[i] == '.'))
        {
            s[i] == '.' ? ++countPoint : ++countDigit;
            ++i;
        }
        if (countDigit < 1 || countPoint > 1)
            return false;
        //4. check e
        if (i < N && s[i] == 'e')
        {
            ++i;
            if (i < N && (s[i] == '+' || s[i] == '-'))
                ++i;
            countDigit = 0;
            while (i < N && isdigit(s[i]))
            {
                ++countDigit;
                ++i;
            }
            if (countDigit < 1)
                return false;
        }
        //5. skip trailing space
        while (i < N && s[i] == ' ')
            ++i;

        return i == N;
    }

public:
	bool BruteForce(const std::string & s)
	{
		bool res = this->bruteForce(s);
		std::cout << "ValidNumber BruteForce for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	bool bruteForce(const std::string & s)
	{
		int N = s.size();
		if (N == 0)
			return false;

		bool signFlag = false;
		bool eFlag = false;
		bool dotFlag = false;
		bool numFlag = false;
		bool followedSpaceFlag = false;//a space whose prev is a non-space

		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '+' || s[i] == '-')
			{
				if ((signFlag || dotFlag || numFlag) && (s[i - 1] != 'E' && s[i - 1] != 'e') || followedSpaceFlag ||
					i == N - 1 || s[i + 1] != '.' && (s[i + 1] < '0' || s[i + 1] > '9'))//next is non-dot non-num
					return false;
				signFlag = true;
			}
			else if (s[i] == 'E' || s[i] == 'e')
			{
				if (eFlag || !numFlag || followedSpaceFlag ||
					i == N - 1 || s[i + 1] != '+' && s[i + 1] != '-' && (s[i + 1] < '0' || s[i + 1] > '9'))//next is non-sign non-num
					return false;
				eFlag = true;
			}
			else if (s[i] == '.')
			{
				if (eFlag || dotFlag || followedSpaceFlag)
					return false;
				if ((i == N - 1 || s[i + 1] >= '0' && s[i + 1] <= '9') ||//next is num
					(i == 0 || s[i - 1] >= '0' && s[i - 1] <= '9'))//prev is num
				{}
				else
					return false;
				dotFlag = true;
			}
			else if (s[i] >= '0' && s[i] <= '9')
			{
				if (followedSpaceFlag)
					return false;
				numFlag = true;
			}
			else if (s[i] == ' ')
			{
				if (i == 0 || s[i - 1] == ' ')//leading spaces
					continue;
				followedSpaceFlag = true;
			}
			else
				return false;
		}
		return numFlag;
	}

public:
	bool FiniteAutomata(const std::string & s)
	{
		int N = s.size();
		Type type = Type::Invalid;
		int state = 0;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == ' ')
				type = Type::Space;
			else if (s[i] == '+' || s[i] == '-')
				type = Type::Sign;
			else if (s[i] >= '0' && s[i] <= '9')
				type = Type::Digit;
			else if (s[i] == '.')
				type = Type::Dot;
			else if (s[i] == 'e' || s[i] == 'E')
				type = Type::Exp;
			else
			{
				std::cout << "ValidNumber FiniteAutomata for \"" << s << "\": 0" << std::endl;
				return false;
			}
			state = this->table[state][type];
			if (state == -1)
			{
				std::cout << "ValidNumber FiniteAutomata for \"" << s << "\": 0" << std::endl;
				return false;
			}
		}
		bool res = (state == 2 || state == 4 || state == 7 || state == 8);
		std::cout << "ValidNumber FiniteAutomata for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
    static int table[9][6];
    enum Type
    {
        Invalid,//0
        Space,//1
        Sign,//2
        Digit,//3
        Dot,//4
        Exp//5
    };

public:
	bool Regex(const std::string & s)
	{
		std::regex isnum("^(\\s*)[\\+-]?\\d*(\\.\\d+)?([eE][\\+-]?\\d+)?(\\s*)$");
		bool res = std::regex_match(s.begin(), s.end(), isnum);
		std::cout << "ValidNumber Regex for \"" << s << "\": " << res << std::endl;
		return res;
	}
};

int ValidNumber::table[9][6] = 
{
	{ -1, 0, 1, 2, 3, -1 },        // state 0: leading space
	{ -1, -1, -1, 2, 3, -1 },      // state 1: first sign
	{ -1, 8, -1, 2, 4, 5 },        // state 2: integer (123)
	{ -1, -1, -1, 4, -1, -1 },     // state 3: first dot (.)
	{ -1, 8, -1, 4, -1, 5 },       // state 4: decimal (123. or .123 or 123.123)
	{ -1, -1, 6, 7, -1, -1 },      // state 5: e notation
	{ -1, -1, -1, 7, -1, -1 },     // state 6: second sign
	{ -1, 8, -1, 7, -1, -1 },      // state 7: exponent (123)
	{ -1, 8, -1, -1, -1, -1 },     // state 8: trailing space
};

/*
ValidNumber Better for "+7.e-9": 1
ValidNumber Better for "+.7e-9": 1
ValidNumber Better for "+9e-3": 1
ValidNumber Better for "+9.e-3": 1
ValidNumber Better for "+9.e3": 1
ValidNumber Better for "9.": 1
ValidNumber Better for ".9": 1
ValidNumber Better for ".9e-3": 1
ValidNumber Better for "+.9": 1
ValidNumber Better for "+.e9": 0
ValidNumber Better for ".e9": 0
ValidNumber Better for "e9": 0
ValidNumber Better for "  -.18e77  ": 1
ValidNumber BruteForce for "+7.e-9": 1
ValidNumber BruteForce for "+.7e-9": 1
ValidNumber BruteForce for "+9e-3": 1
ValidNumber BruteForce for "+9.e-3": 1
ValidNumber BruteForce for "+9.e3": 1
ValidNumber BruteForce for "9.": 1
ValidNumber BruteForce for ".9": 1
ValidNumber BruteForce for ".9e-3": 1
ValidNumber BruteForce for "+.9": 1
ValidNumber BruteForce for "+.e9": 0
ValidNumber BruteForce for ".e9": 0
ValidNumber BruteForce for "e9": 0
ValidNumber BruteForce for "  -.18e77  ": 1
ValidNumber Regex for "  -.18e77  ": 1
ValidNumber FiniteAutomata for "  -.18e77  ": 1
*/
#endif

