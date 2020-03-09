/*Facebook*/
#ifndef _VERTICAL_PRINT_W_BALANCED_COLUMN_LEN_H
#define _VERTICAL_PRINT_W_BALANCED_COLUMN_LEN_H
#include "Debug.h"
/*
https://codereview.stackexchange.com/questions/188353/vertically-print-a-list-of-strings-to-stdout-into-3-columns-with-column-lengths/188356
 */
class VerticalPrintWBalancedColumnLen
{
public:
    VerticalPrintWBalancedColumnLen(){}

    void Solve(const std::vector<std::string> & words, int numCol)
    {
        int lengthPerColumn = words.size() / numCol;
        int dangling = words.size() % numCol;
        std::vector<std::vector<std::string>> columns;
        auto iter = words.begin();
        for (int i = 0; i < numCol; ++i)//save each column as a row in "columns"
        {
            auto columnEndIter = iter + lengthPerColumn;
            if (dangling > i) // The first "dangling" columns will have one more word
                ++columnEndIter;
            columns.push_back({iter, columnEndIter});
            iter = columnEndIter;
        }
        Debug::Print2D<std::string>()(columns, false);

        auto maxWordSize = std::max_element(words.begin(), words.end(), [](const std::string& a, const std::string& b) {return a.size() < b.size();} )->size();

        std::ostringstream oss;
        for (int i = 0; i < lengthPerColumn; ++i)//for each row except last row
        {
            for (int j = 0; j < numCol; ++j)
            {
                oss << std::setw(maxWordSize) << columns[j][i] << " ";
            }
            oss << std::endl;
        }
        // Last row
        for (int j = 0; j < dangling; ++j)
        {
            oss << std::setw(maxWordSize) << columns[j][lengthPerColumn] << " ";
        }
        oss << std::endl;

        std::cout << "VerticalPrintWBalancedColumnLen for [" << Debug::ToStr1D<std::string>()(words) << "], col=" << numCol << ": " << std::endl;
        std::cout << oss.str() << std::endl;
    }
};
/*
[rY][cX]
Row#0	= a, b, c, d
Row#1	= e, f, g,
Row#2	= h, i, j,

VerticalPrintWBalancedColumnLen for [a, b, c, d, e, f, g, h, i, j], col=3:
a e h
b f i
c g j
d

[rY][cX]
Row#0	= a, bb, cc, d
Row#1	= e, f, gg,
Row#2	= hhh, i, j,

VerticalPrintWBalancedColumnLen for [a, bb, cc, d, e, f, gg, hhh, i, j], col=3:
  a   e hhh
 bb   f   i
 cc  gg   j
  d

[rY][cX]
Row#0	= a, b, ccccccc, dd
Row#1	= e, ffffffff, gg,
Row#2	= h, i, j,

VerticalPrintWBalancedColumnLen for [a, b, ccccccc, dd, e, ffffffff, gg, h, i, j], col=3:
       a        e        h
       b ffffffff        i
 ccccccc       gg        j
      dd

[rY][cX]
Row#0	= a, b, ccccccc
Row#1	= dd, e, ffffffff
Row#2	= gg, h,
Row#3	= i, j,

VerticalPrintWBalancedColumnLen for [a, b, ccccccc, dd, e, ffffffff, gg, h, i, j], col=4:
       a       dd       gg        i
       b        e        h        j
 ccccccc ffffffff

[rY][cX]
Row#0	= a, b
Row#1	= ccccccc, dd
Row#2	= e, ffffffff
Row#3	= gg, h
Row#4	= i, j

VerticalPrintWBalancedColumnLen for [a, b, ccccccc, dd, e, ffffffff, gg, h, i, j], col=5:
       a  ccccccc        e       gg        i
       b       dd ffffffff        h        j

 */
#endif
