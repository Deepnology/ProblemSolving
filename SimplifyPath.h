#ifndef SIMPLIFY_PATH_H
#define SIMPLIFY_PATH_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
/*
Elements of programming interview, StacksAndQueues: Normalize pathnames (NormalizePath)
Write a function which takes a pathname, and returns the shortest equivalent pathname.
Assume individual directories and files have names that use only alphanumeric characters.
Subdirectory names may be combined using forward slashes (/), the current directory (.), and parent directory (..).

It is natural to process the string from left-to-right, splitting on forward slashes (/).
We record directory and file names.
Each time we encounter a .., we delete the most recent name, which corresponds to going up directory hierarchy.
Since names are processed in a last-in, first-out order, it is natural to store them in a stack.
Individual periods (.) are skipped.

If the string begins with /, then we cannot go up from it.
We record this in the stack.
If the stack does not begin with /, we may encounter an empty stack when processing .., which indicates a path that begins with an ancestor of the current working path.
We need to record this in order to give the shortest equivalent path.
The final state of the stack directly corresponds to the shortest equivalent directory path.

http://coding-exercise.blogspot.tw/2013/03/leetcode-simplify-path.html
https://github.com/anson627/leetcode/blob/master/SimplifyPath/SimplifyPath.cpp
// Given an absolute path for a file (Unix-style), simplify it.
//
// For example,
// path = "/home/", => "/home"
// path = "/a/./b/../../c/", => "/c"
// Corner Cases:
// Did you consider the case where path = "/../"?
// In this case, you should return "/".
// Another corner case is the path might contain multiple slashes '/' together,
// such as "/home//foo/".
// In this case, you should ignore redundant slashes and return "/home/foo".
//
// Vector based, O(n) time, O(n) space

.. means going to the upper folder
. means staying in the current folder
When meeting a .., it must skip the first non-empty non-dot directory name on its left side
When meeting a . or empty directory name, just skip it

SimplifyPath: never keep ..
              always start with a /
NormalizePath: keep .. only if there is no corresponding non-empty non-dot directory name on its left side to skip
               start with a / only when the original path starts with a /
*/
class SimplifyPath
{
public:
	SimplifyPath(){}
	~SimplifyPath(){}

	std::string Stack(std::string path)
	{
		std::vector<std::string> tokenStk;//only "non-dot non-empty directory name" can be put in stk
		std::istringstream iss(path);
		std::string token;
		while (getline(iss, token, '/'))
		{
			std::cout << "token=\"" << token << "\"" << std::endl;

			//1. when meeting a .., it must skip the first non-dot non-empty directory name on its left side
			//never keep ..
			if (token == "..")
			{
				if (!tokenStk.empty())
					tokenStk.pop_back();
			}
			//2. just skip dot and empty directory name
			else if (token == "." || token == "")
			{

			}
			//3. put non-dot non-empty directory name anyway
			else
			{
				tokenStk.push_back(token);
			}
		}

		std::string res;
		res += "/";//always start with a /
		int N = tokenStk.size();
		for (int i = 0; i < N; ++i)
		{
			if (i == 0)
				res += tokenStk[i];
			else
				res += "/" + tokenStk[i];
		}
		std::cout << "SimplifyPath Stack for \"" << path << "\" is: " << res << std::endl;
		return res;
	}
};

class NormalizePath
{
public:
	NormalizePath(){}
	~NormalizePath(){}

	std::string Stack(std::string path)
	{
		std::vector<std::string> tokenStk;//only ".." and "non-dot non-empty directory name" can be put in stk
		std::istringstream iss(path);
		std::string token;
		while (getline(iss, token, '/'))
		{
			std::cout << "token=\"" << token << "\"" << std::endl;

			//1. when meeting a .., it must skip the first non-dot non-empty directory name on its left side
			if (token == "..")
			{
				if (tokenStk.empty() || tokenStk.back() == "..")
					tokenStk.push_back(token);
				else
					tokenStk.pop_back();
			}
			//2. just skip dot and empty directory name
			else if (token == "." || token == "")
			{

			}
			//3. put non-dot non-empty directory name anyway
			else
			{
				tokenStk.push_back(token);
			}
		}

		std::string res;
		if (path.front() == '/')//special case: starts with "/", which is an absolute path
			res += "/";
		int N = tokenStk.size();
		for (int i = 0; i < N; ++i)
		{
			if (i == 0)
				res += tokenStk[i];
			else
				res += "/" + tokenStk[i];
		}
		std::cout << "NormalizePath Stack for \"" << path << "\" is: " << res << std::endl;
		return res;
	}
};
/*
token=""
token="a"
token="."
token="b"
token=".."
token=".."
token="c"
SimplifyPath Stack for "/a/./b/../../c/" is: /c
token=""
token="a"
token="."
token="b"
token=".."
token=".."
token="c"
NormalizePath Stack for "/a/./b/../../c/" is: /c
token=""
token="a"
token="."
token="b"
token="."
token="c"
token=""
token=".."
token=".."
token="d"
SimplifyPath Stack for "/a/./b/./c//../../d/" is: /a/d
token=""
token="a"
token="."
token="b"
token="."
token="c"
token=""
token=".."
token=".."
token="d"
NormalizePath Stack for "/a/./b/./c//../../d/" is: /a/d
token="usr"
token="lib"
token=".."
token="bin"
token="gcc"
SimplifyPath Stack for "usr/lib/../bin/gcc" is: /usr/bin/gcc
token="usr"
token="lib"
token=".."
token="bin"
token="gcc"
NormalizePath Stack for "usr/lib/../bin/gcc" is: usr/bin/gcc
token=""
token="usr"
token="lib"
token=".."
token="bin"
token="gcc"
SimplifyPath Stack for "/usr/lib/../bin/gcc" is: /usr/bin/gcc
token=""
token="usr"
token="lib"
token=".."
token="bin"
token="gcc"
NormalizePath Stack for "/usr/lib/../bin/gcc" is: /usr/bin/gcc
token="xyz"
token="abc"
token=""
token="."
token=".."
token="scripts"
token="awkscripts"
token="."
token="."
SimplifyPath Stack for "xyz/abc//./../scripts/awkscripts/././" is: /xyz/scripts/awkscripts
token="xyz"
token="abc"
token=""
token="."
token=".."
token="scripts"
token="awkscripts"
token="."
token="."
NormalizePath Stack for "xyz/abc//./../scripts/awkscripts/././" is: xyz/scripts/awkscripts
token=".."
token=".."
token="local"
SimplifyPath Stack for "../../local" is: /local
token=".."
token=".."
token="local"
NormalizePath Stack for "../../local" is: ../../local
token="."
token=".."
SimplifyPath Stack for "./../" is: /
token="."
token=".."
NormalizePath Stack for "./../" is: ..
token=""
token=".."
SimplifyPath Stack for "/../" is: /
token=""
token=".."
NormalizePath Stack for "/../" is: /..
*/
#endif