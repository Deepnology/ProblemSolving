#ifndef _FIND_DUPLICATE_ROWS_IN_BINARY_MATRIX_H
#define _FIND_DUPLICATE_ROWS_IN_BINARY_MATRIX_H
#include "Debug.h"
/*
https://www.geeksforgeeks.org/find-duplicate-rows-binary-matrix/
 */
class FindDuplicateRowsInBinaryMatrix
{
public:
    FindDuplicateRowsInBinaryMatrix(){}
    struct Trie
    {
        Trie():children(2, NULL){}
        std::vector<Trie *> children;
    };
    std::vector<int> UseTrie(const std::vector<std::vector<int>> & v)
    {
        std::vector<int> res;
        int N = v.size();
        Trie * root = new Trie;
        Trie * cur = root;
        for (int i = 0; i < N; ++i)
        {
            //insert cur row into Trie
            cur = root;
            int j = 0;
            int M = v[i].size();
            while (j < M)
            {
                if (!cur->children[v[i][j]])
                    cur->children[v[i][j]] = new Trie;
                else
                {
                    if (j == M - 1)//leaf node already exists
                        res.push_back(i);//record cur row idx
                }
                cur = cur->children[v[i][j]];
                ++j;
            }
        }

        Debug::Print2D<int>()(v, false);
        std::cout << "FindDuplicateRowsInBinaryMatrix UseTrie for above matrix: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 1, 1, 0, 1, 0, 1
Row#1	= 0, 0, 1, 0, 0, 1
Row#2	= 1, 0, 1, 1, 0, 0
Row#3	= 1, 1, 0, 1, 0, 1
Row#4	= 0, 0, 1, 0, 0, 1
Row#5	= 0, 0, 1, 0, 0, 1

FindDuplicateRowsInBinaryMatrix UseTrie for above matrix: 3, 4, 5
 */
#endif
