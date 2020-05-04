#ifndef _LOGIN_COUNT_FROM_UNORDERED_STREAM_H
#define _LOGIN_COUNT_FROM_UNORDERED_STREAM_H
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Uber
see also IntersectionOfIntervals.h
 */
class LoginCountFromUnorderedStream_PrefixSum
{
    std::vector<std::pair<int,int>> sorted;//<time, prefixSum of Login> sorted by time
public:
    LoginCountFromUnorderedStream_PrefixSum(){}

    void Insert(int time, int loginOrOut)//O(logN + N) time
    {
        if (sorted.empty())
        {
            sorted.push_back({time, loginOrOut});
            std::cout << "Insert [" << time << "," << loginOrOut << "]: " << Debug::ToStr1D<int>()(sorted) << std::endl;
            return;
        }
        //binary search lower bound index to insert time
        int left = 0;
        int right = sorted.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (sorted[mid].first >= time)
                right = mid - 1;
            else
                left = mid + 1;
        }
        //update sorted[idx:N-1]
        if (left == sorted.size())
        {
            sorted.push_back({time, sorted.back().second + loginOrOut});
        }
        else
        {
            if (sorted[left].first != time)
                sorted.insert(sorted.begin()+left, {time, left == 0 ? 0 : sorted[left-1].second});
            while (left < sorted.size())
                sorted[left++].second += loginOrOut;
        }

        std::cout << "Insert [" << time << "," << loginOrOut << "]: " << Debug::ToStr1D<int>()(sorted) << std::endl;
    }
    int QueryLoginCount(int time)//O(logN) time
    {
        if (sorted.empty())
        {
            std::cout << "Query " << time << ": 0" << std::endl;
            return 0;
        }
        int left = 0;
        int right = sorted.size() - 1;
        while (left <= right)//find upper bound of time
        {
            int mid = (left + right) / 2;
            if (sorted[mid].first <= time)
                left = mid + 1;
            else
                right = mid - 1;
        }
        //now left is upper bound
        left -= 1;

        std::cout << "Query " << time << ": " << sorted[left].second << std::endl;
        return sorted[left].second;
    }
};
class LoginCountFromUnorderedStream_BST
{
public:
    struct TreeNode
    {
        int val;//timestamp
        int sum;
        int leftSum;
        TreeNode * left;
        TreeNode * right;
        std::string GetSum()
        {
            return std::to_string(leftSum) + "," + std::to_string(sum);
        }
        TreeNode(int v, int s):val(v), sum(s), leftSum(0), left(NULL), right(NULL){}
    };
private:
    int Insert(TreeNode *& root, int timestamp, int loginOrOut)
    {
        if (root == NULL)
        {
            root = new TreeNode(timestamp, loginOrOut);
            return loginOrOut;
        }
        if (root->val > timestamp)
        {
            int tmp = Insert(root->left, timestamp, loginOrOut);
            root->leftSum += tmp;
            return tmp;
        }
        else if (root->val < timestamp)
        {
            return Insert(root->right, timestamp, loginOrOut);
        }
        else
        {
            root->sum += loginOrOut;
            return loginOrOut;
        }
    }
    int Search(TreeNode * root, int timestamp) //return prefixSum
    {
        int res = 0;
        while (root)
        {
            if (root->val > timestamp)
            {
                root = root->left;
            }
            else if (root->val < timestamp)
            {
                res += root->leftSum + root->sum;
                root = root->right;
            }
            else
            {
                res += root->leftSum + root->sum;
                break;
            }
        }
        return res;
    }
    TreeNode * m_root;
public:
    LoginCountFromUnorderedStream_BST():m_root(NULL){}

    void Insert(int time, int loginOrOut) //O(logN) time
    {
        Insert(m_root, time, loginOrOut);

        std::cout << "Insert [" << time << "," << loginOrOut << "]:" << std::endl;
        std::ostringstream oss;
        PrintBinaryTree<LoginCountFromUnorderedStream_BST::TreeNode, std::ostringstream>(m_root, oss);
        std::cout << oss.str() << std::endl;
    }
    int QueryLoginCount(int time) //O(logN) time
    {
        int res = Search(m_root, time);
        std::cout << "Query " << time << ": " << res << std::endl;
        return res;
    }
};
template<>
std::string PrintBinaryTree<LoginCountFromUnorderedStream_BST::TreeNode, std::ostringstream>::selectVal2(int depthY, LoginCountFromUnorderedStream_BST::TreeNode * n)
{
    std::ostringstream oss;
    oss << n->GetSum();
    return oss.str();
};

class LoginCountFromUnorderedStream_PrefixSum_Map
{
    std::map<int,int> balance;
public:
    void Insert(int time, int loginOrOut)
    {
        balance[time] += loginOrOut;
    }
    int QueryLoginCount(int time)
    {
        int res = 0;
        for(auto itr = balance.begin(); itr != balance.end() && itr->first <= time; ++itr)
        {
            //std::cout << itr->first << ":" << itr->second << std::endl;
            res += itr->second;
        }
        std::cout << "Query " << time << ": " << res << std::endl;
        return res;
    }
};
/*
Insert [2,1]: [2,1]
Insert [10,1]: [2,1], [10,2]
Insert [5,1]: [2,1], [5,2], [10,3]
Insert [6,-1]: [2,1], [5,2], [6,1], [10,2]
Insert [20,-1]: [2,1], [5,2], [6,1], [10,2], [20,1]
Insert [6,1]: [2,1], [5,2], [6,2], [10,3], [20,2]
Insert [13,-1]: [2,1], [5,2], [6,2], [10,3], [13,2], [20,1]
Insert [8,-1]: [2,1], [5,2], [6,2], [8,1], [10,2], [13,1], [20,0]
Insert [11,1]: [2,1], [5,2], [6,2], [8,1], [10,2], [11,3], [13,2], [20,1]
Insert [30,1]: [2,1], [5,2], [6,2], [8,1], [10,2], [11,3], [13,2], [20,1], [30,2]
Insert [40,1]: [2,1], [5,2], [6,2], [8,1], [10,2], [11,3], [13,2], [20,1], [30,2], [40,3]
Insert [25,-1]: [2,1], [5,2], [6,2], [8,1], [10,2], [11,3], [13,2], [20,1], [25,0], [30,1], [40,2]
Insert [50,-1]: [2,1], [5,2], [6,2], [8,1], [10,2], [11,3], [13,2], [20,1], [25,0], [30,1], [40,2], [50,1]
Query 45: 2
Query 20: 1
Query 70: 1
Query 15: 2
Insert [2,1]:

0,1
 2


Insert [10,1]:

  0,1
   2
 /   \
 X  0,1
 N  10


Insert [5,1]:

      0,1
    __ 2__
   /       \
   X      1,1
   N      10
 /   \   /   \
 X   X  0,1   X
 N   N   5   N


Insert [6,-1]:

              0,1
        ______ 2______
       /               \
       X              0,1
    __ N__          __10__
   /       \       /       \
   X       X      0,1       X
   N       N       5       N
 /   \   /   \   /   \   /   \
 X   X   X   X   X  0,-1   X   X
 N   N   N   N   N   6   N   N


Insert [20,-1]:

              0,1
        ______ 2______
       /               \
       X              0,1
    __ N__          __10__
   /       \       /       \
   X       X      0,1      0,-1
   N       N       5      20
 /   \   /   \   /   \   /   \
 X   X   X   X   X  0,-1   X   X
 N   N   N   N   N   6   N   N


Insert [6,1]:

              0,1
        ______ 2______
       /               \
       X              1,1
    __ N__          __10__
   /       \       /       \
   X       X      0,1      0,-1
   N       N       5      20
 /   \   /   \   /   \   /   \
 X   X   X   X   X  0,0   X   X
 N   N   N   N   N   6   N   N


Insert [13,-1]:

              0,1
        ______ 2______
       /               \
       X              1,1
    __ N__          __10__
   /       \       /       \
   X       X      0,1      -1,-1
   N       N       5      20
 /   \   /   \   /   \   /   \
 X   X   X   X   X  0,0  0,-1   X
 N   N   N   N   N   6  13   N


Insert [8,-1]:

                              0,1
                ______________ 2______________
               /                               \
               X                              0,1
        ______ N______                  ______10______
       /               \               /               \
       X               X              0,1              -1,-1
    __ N__          __ N__          __ 5__          __20__
   /       \       /       \       /       \       /       \
   X       X       X       X       X      0,0      0,-1       X
   N       N       N       N       N       6      13       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X  0,-1   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   8   N   N   N   N


Insert [11,1]:

                              0,1
                ______________ 2______________
               /                               \
               X                              0,1
        ______ N______                  ______10______
       /               \               /               \
       X               X              0,1              0,-1
    __ N__          __ N__          __ 5__          __20__
   /       \       /       \       /       \       /       \
   X       X       X       X       X      0,0      1,-1       X
   N       N       N       N       N       6      13       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X  0,-1  0,1   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   8  11   N   N   N


Insert [30,1]:

                              0,1
                ______________ 2______________
               /                               \
               X                              0,1
        ______ N______                  ______10______
       /               \               /               \
       X               X              0,1              0,-1
    __ N__          __ N__          __ 5__          __20__
   /       \       /       \       /       \       /       \
   X       X       X       X       X      0,0      1,-1      0,1
   N       N       N       N       N       6      13      30
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X  0,-1  0,1   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   8  11   N   N   N


Insert [40,1]:

                              0,1
                ______________ 2______________
               /                               \
               X                              0,1
        ______ N______                  ______10______
       /               \               /               \
       X               X              0,1              0,-1
    __ N__          __ N__          __ 5__          __20__
   /       \       /       \       /       \       /       \
   X       X       X       X       X      0,0      1,-1      0,1
   N       N       N       N       N       6      13      30
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X  0,-1  0,1   X   X  0,1
 N   N   N   N   N   N   N   N   N   N   N   8  11   N   N  40


Insert [25,-1]:

                              0,1
                ______________ 2______________
               /                               \
               X                              0,1
        ______ N______                  ______10______
       /               \               /               \
       X               X              0,1              0,-1
    __ N__          __ N__          __ 5__          __20__
   /       \       /       \       /       \       /       \
   X       X       X       X       X      0,0      1,-1      -1,1
   N       N       N       N       N       6      13      30
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X  0,-1  0,1   X  0,-1  0,1
 N   N   N   N   N   N   N   N   N   N   N   8  11   N  25  40


Insert [50,-1]:

                                                              0,1
                                ______________________________ 2______________________________
                               /                                                               \
                               X                                                              0,1
                ______________ N______________                                  ______________10______________
               /                               \                               /                               \
               X                               X                              0,1                              0,-1
        ______ N______                  ______ N______                  ______ 5______                  ______20______
       /               \               /               \               /               \               /               \
       X               X               X               X               X              0,0              1,-1              -1,1
    __ N__          __ N__          __ N__          __ N__          __ N__          __ 6__          __13__          __30__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       X      0,-1      0,1       X      0,-1      0,1
   N       N       N       N       N       N       N       N       N       N       N       8      11       N      25      40
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X  0,-1
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  50


Query 45: 2
Query 20: 1
Query 70: 1
Query 15: 2
Query 45: 2
Query 20: 1
Query 70: 1
Query 15: 2
 */
#endif
