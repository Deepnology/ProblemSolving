/*MUST*/
#ifndef CONVERT_EXCEL_COLUMN_ID_H
#define CONVERT_EXCEL_COLUMN_ID_H
#include <iostream>
#include <string>
/*
https://leetcode.com/problems/excel-sheet-column-number/
Elements of programming interview, PrimitiveTypes: Compute the spreadsheet column encoding
Widely deployed spreadsheets use an alphabetical encoding of the successive columns.
Specifically, consecutive columns are identified by "A", "B", "C", ..., "X", "Y", "Z", "AA", "AB", ..., "ZZ", "AAA", "AAB", ....
Implement a function that converts Excel column ids to the corresponding integer, with "A" corresponding to 1.
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28

O(n) time

Excel sheet column title
https://leetcode.com/problems/excel-sheet-column-title/
http://betterpoetrythancode.blogspot.tw/2014/12/excel-sheet-column-title-leetcode-math.html
Given a positive integer, return its corresponding column title as appear in an Excel sheet.
1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB

O(n) time
*/
class ConvertExcelColumnId
{
public:
	ConvertExcelColumnId(){}
	~ConvertExcelColumnId(){}

	int Decode(const std::string & col)
	{
		int res = 0;
		for (const char & c : col)
			res = res * 26 + (c - 'A' + 1);

		std::cout << "ConvertExcelColumnId Decode for \"" << col << "\": " << res << std::endl;
		return res;
	}

	std::string Encode(int n)
	{
		int before = n;
		std::string res;
		while (n)
		{
			res.insert(res.begin(), (n - 1) % 26 + 'A');
			n = (n - 1) / 26;
		}

		std::cout << "ConvertExcelColumnId Encode for \"" << before << "\": " << res << std::endl;
		return res;
	}
};
/*
ConvertExcelColumnId Decode for "ABC": 731
*/
#endif