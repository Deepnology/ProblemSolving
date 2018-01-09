/*Design*/
#ifndef EXCEL_SUM_FORMULA_H
#define EXCEL_SUM_FORMULA_H
#include "Debug.h"
/*
Leetcode: Design Excel Sum Formula
Your task is to design the basic function of Excel and implement the function of sum formula. Specifically, you need to implement the following functions:
Excel(int H, char W): This is the constructor.
 The inputs represents the height and width of the Excel form. H is a positive integer, range from 1 to 26.
 It represents the height.
 W is a character range from 'A' to 'Z'.
 It represents that the width is the number of characters from 'A' to W.
 The Excel form content is represented by a height * width 2D integer array C, it should be initialized to zero.
 You should assume that the first row of C starts from 1, and the first column of C starts from 'A'.

void Set(int row, char column, int val): Change the value at C(row, column) to be val.
int Get(int row, char column): Return the value at C(row, column).

int Sum(int row, char column, List of Strings : numbers): This function calculate and set the value at C(row, column), where the value should be the sum of cells represented by numbers.
This function return the sum result at C(row, column). This sum formula should exist until this cell is overlapped by another value or another sum formula.
numbers is a list of strings that each string represent a cell or a range of cells.
If the string represent a single cell, then it has the following format : ColRow.
For example, "F7" represents the cell at (7, F).
If the string represent a range of cells, then it has the following format : ColRow1:ColRow2.
The range will always be a rectangle, and ColRow1 represent the position of the top-left cell, and ColRow2 represents the position of the bottom-right cell.

Example 1:
Excel(3,"C");
// construct a 3*3 2D array with all zero.
//   A B C
// 1 0 0 0
// 2 0 0 0
// 3 0 0 0

Set(1, "A", 2);
// set C(1,"A") to be 2.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 0

Sum(3, "C", ["A1", "A1:B2"]);
// set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the rectangle range whose top-left cell is C(1,"A") and bottom-right cell is C(2,"B"). Return 4.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 4

Set(2, "B", 2);
// set C(2,"B") to be 2. Note C(3, "C") should also be changed.
//   A B C
// 1 2 0 0
// 2 0 2 0
// 3 0 0 6
Note:
You could assume that there won't be any circular sum reference. For example, A1 = sum(B1) and B1 = sum(A1).
The test cases are using double-quotes to represent a character.
Please remember to RESET your class variables declared in class Excel, as static/class variables are persisted across multiple test cases. Please see here for more details.
*/
class ExcelSumFormula
{
    int rowCount;
    int colCount;
    std::vector<std::vector<int>> Exl;
    std::unordered_map<int, std::unordered_set<int>> bwardDAG;//<curNode, <preNode>>. note: preNode can appear only one time
    std::unordered_map<int, std::unordered_map<int, int>> fwardDAG;//<curNode, <nxtNode, count>>. note: nxtNode can appear multiple times for multiple formulas
    int toKey(int row, char col)//note: key is 0 based
    {
        return (row-1)*rowCount+(col-'A');
    }
    int toRow(int key)//note: row is 1 based
    {
        return key / rowCount + 1;
    }
    char toCol(int key)//note: col is 1 based
    {
        return key % rowCount + 'A';
    }

public:
    ExcelSumFormula(int rowMax, char colMax) : rowCount(rowMax), colCount(colMax-'A'+1), Exl(rowCount, std::vector<int>(colCount, 0))
    {
        std::cout << "ExcelSumFormula Ctor for [" << rowCount << "," << colCount << "]:" << std::endl;
        Debug::Print2D<int>()(Exl, false);
    }

    void set(int r, char c, int v)
    {
        //1. update all cells' values starting from (r,c)
        updateAllValuesBFS(r, c, v);
        //2. clean all formulas that involve (r,c)
        cleanFormulas(r, c);

        std::cout << "ExcelSumFormula set [" << r << "," << c << "]=" << v << ":" << std::endl;
        Debug::Print2D<int>()(Exl, false);
    }

    int get(int r, char c)
    {
        std::cout << "ExcelSumFormula get [" << r << "," << c << "]: " << Exl[r-1][c-'A'] << std::endl;
        return Exl[r-1][c-'A'];
    }

    int sum(int r, char c, std::vector<std::string> strs)
    {
        //1. clean all formulas that involve (r,c)
        cleanFormulas(r, c);
        //2. add cur formula that sum to (r,c); compute formula sum to (r,c)
        int curKey = toKey(r,c);
        int res = 0;
        std::vector<int> keys = getAllCellKeys(strs);
        for (const auto & key : keys)
        {
            res += Exl[toRow(key)-1][toCol(key)-'A'];
            bwardDAG[curKey].insert(key);
            ++fwardDAG[key][curKey];
        }
        //3. update all cells' values starting from (r,c)
        updateAllValuesBFS(r, c, res);

        std::cout << "ExcelSumFormula sum [" << r << "," << c << "] with [" << Debug::ToStr1D<std::string>()(strs) << "]: " << res << std::endl;
        Debug::Print2D<int>()(Exl, false);
        return res;
    }

private:
    void updateAllValuesBFS(int row, char col, int val)//update all cell values in fwardDAG starting from (row,col)
    {
        int diff = val - Exl[row-1][col-'A'];
        Exl[row-1][col-'A'] = val;
        std::queue<int> que;
        std::queue<int> diffQue;
        que.push(toKey(row,col));
        diffQue.push(diff);
        while (!que.empty())
        {
            int curKey = que.front();
            que.pop();
            int curDiff = diffQue.front();
            diffQue.pop();
            if (fwardDAG.count(curKey))
            {
                for (const auto & p : fwardDAG[curKey])
                {
                    int nxtKey = p.first;
                    int count = p.second;
                    que.push(nxtKey);
                    diffQue.push(curDiff*count);
                    Exl[toRow(nxtKey)-1][toCol(nxtKey)-'A'] += curDiff*count;
                }
            }
        }
    }
    void cleanFormulas(int row, char col)//when updating value at (row,col)
    {
        int key = toKey(row, col);
        if (bwardDAG.count(key))
        {
            //clean all formulas starting from (row,col)
            for (const auto & preKey : bwardDAG[key])
            {
                fwardDAG[preKey].erase(key);
            }
            //clean all formulas ending at (row,col)
            bwardDAG.erase(key);
        }
    }
    std::vector<int> getAllCellKeys(const std::vector<std::string> & strs)
    {
        std::vector<int> res;
        for (const auto & s : strs)
        {
            int N = s.size();
            char col1 = s[0];
            int i = 1;
            while (i < N && isdigit(s[i]))
                ++i;
            int row1 = stoi(s.substr(1,i));
            if (i == N)
            {
                res.push_back(toKey(row1,col1));
                continue;
            }
            ++i;//skip ':'
            char col2 = s[i];
            ++i;
            int row2 = stoi(s.substr(i,N-i));
            for (int row = row1; row <= row2; ++row)
                for (char col = col1; col <= col2; ++col)
                {
                    res.push_back(toKey(row,col));
                }
        }
        return res;
    }
};
/*
ExcelSumFormula Ctor for [3,3]:
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 0, 0
Row#2	= 0, 0, 0

ExcelSumFormula set [1,A]=2:
[rY][cX]
Row#0	= 2, 0, 0
Row#1	= 0, 0, 0
Row#2	= 0, 0, 0

ExcelSumFormula sum [3,C] with [A1, A1:B2]: 4
[rY][cX]
Row#0	= 2, 0, 0
Row#1	= 0, 0, 0
Row#2	= 0, 0, 4

ExcelSumFormula set [2,B]=2:
[rY][cX]
Row#0	= 2, 0, 0
Row#1	= 0, 2, 0
Row#2	= 0, 0, 6
*/
#endif
