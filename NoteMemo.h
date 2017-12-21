#ifndef NOTE_MEMO_H
#define NOTE_MEMO_H
/*
coding sense!
要有本事一天看完看懂所有題目!
目標：每一題看起來都要是最"簡單精簡"的, 一想到題目就要想到那個簡單的解
我只有現在啊!!

見山是山
見山不是山
見山還是山 ~ 柯文哲

神之技術! 手術前在屋頂上的準備 ~ 朝田龍太郎
題目看的多了，就會歸納! ~ 蕭宇宏、王國川
失意的時候是在為得意的時候做準備
台大人都有的精神:不管做任何事都要追根究底，鍥而不捨 ~ 做題目一定要把它弄懂弄熟

繞遠路是成功的捷徑 ~ 鈴木一朗

我"絕不"去低薪小公司!

一切就只是"基本功"而已
"基本功"的function要"不用想可以閉著眼睛直接寫出來"

Google = 資優班 (我要進資優班!)

最大的敵人是自己-->不要輸給自己

最後衝刺~
最終目標：憑空把所有"分類、題目、解法"回想一遍, Exciting!!!

要有強大的心智腦力及毅力
手寫過一遍，再讀自己寫過的東西，會有記憶深刻的魔力，或是會有global picture的view
你最大的問題就是沒辦法看過(理解)一次後印相深刻的記起來!!
*/
/*
special data structures
Trie: each node keeps an array of 26 next node ptrs and a bool isKey. 
	insertRecur: takes ptr ref to curNode, keep track of curBegin of the input string, mark isKey when current node is end.
	getNodeRecur: return NULL if cur node is null, return cur node when reaches end.
	deleteRecur: takes ptr ref to curNode, if cur node is null, just return, if reaches end, mark isKey to false, postorder delete all null next node ptrs and then delete self and mark NULL if self's isKey==false and next node ptrs are empty.
Segment tree: 1D array of level order traversal. built from leaf nodes. non-leaf nodes are sum of its left and right child. height=ceil(log2(N))+1. size=pow(2,height)-1. left=2*i+1. right=2*i+2. parent=(i-1)/2. postorder recur: keep track of an index (left, right, parent) in segment tree array, keep track of a pair of (start, end) indices of the input leaf array, early return segmentTree[index]=v[left] if index is a leaf (left==right), otherwise return segmentTree[index] = leftChildSum+rightChildSum.
Segment tree 2D: rowRecur: keep track of topRowY and bottomRowY of matrix, keep track of rowY (topChild=rowY*2+1, bottomChild=rowY*2+2) of segmentTree. colRecur: keep fixed rowY, topRowY, bottomRowY from rowRecur. keep track of leftColX and rightColX of matrix, keep track of colX (leftChild=colX*2+1, rightChild=colX*2+2) of segmentTree.
				when seeing a leaf (topRowY==bottomRowY && leftColX==rightColX), return segmentTree[rowY][colX]=matrix[topRowY][leftColX]. otherwise, it must be a parent node with 2 leaves, return segmentTree[rowY][colX]=topChildSum+bottomChildSum or segmentTree[rowY][colX]=leftChildSum+rightChildSum.
Tournament tree:
Binary indexed tree:
Cartesian tree: a binary tree with "heap property" (parent node's val is less than both of its left and right children) and whose inorder traversal represents the original array.
				BruteForce construct: Recur keeps track of left and right indices, in [left,right], find the minVal and minIdx, new a root node with the minVal. If it is a leaf (left==right), return the root node. If it is NULL (left>right), return NULL. Otherwise, assign root->left=recur(left,minIdx-1), root->right=recur(minIdx+1,right), and return root.
				SortedStack construct: keep a nodes array tha maps indices to node instances. keep a sorted stack that keeps indices in increasing order by value (actually keeps track of the rightmost path nodes starting from root). For each val in array, new a curNode in nodes array, pop out all indices with greater vals in sortedStk to get the leftmost greater node, which must be the left child of curNode. If sortedStk is non-empty, curNode must be the right child of the top(rightmost) node. Update root to curNode if curNode's val is less. Push curNode index to sortedStk.
				RangeMinQuery: Recur to find LCA of 2 given nodes. LeftPair<foundCount,LCA>=recur(root->left,a,b), RightPair<foundCount,LCA>=recur(root->right,a,b), foundCount = LeftPair.foundCount+RightPair.foundCount+(root==a||root==b), return {foundCount,foundCount==2?root:NULL}.
Treap: node's val satisfies BST property (parent node's val greater than left children and less than right children), node's priority val satisfies heap property (parent node's priority val is less equal than both of its left and right children)
		need to keep a m_nullNode ptr with priority INT_MAX for rotation. rotateWithLeftChildRecur: (V). rotateWithRightChildRecur: )V(.
		insertRecur: insert a val based on BST property, after insertRecur, adjust priority between curNode and curNode->left (or curNode->right) by rotateWLeftChildRecur (rotateWRightChildRecur)
		contains: assign m_nullNode's val to target val, perform BST binary search
		removeRecur: binary search, when val==root->val, rotateWLeftChild(root) if leftChild has a less priority, otherwise, rotateWRightChild(root), after rotation, if root!=m_nullNode, removeRecur down, otherwise, delete root->left (not understood)
AA tree:


Splay tree: a BST with recently accessed node moved to root. need to keep a m_nullNode for rotation. rotateWithLeftChildRecur: (V). rotateWithRightChildRecur: )V(.
			splayRecur(val, & curNode): left left (splayRecur(val, curNode->left->left), rotateWLeft(curNode), rotateWLeft(curNode)), left right (splayRecur(val, curNode->left->right), rotateWLeft(curNode-right), rotateWRight(curNode)), right left (splayRecur(val, curNode->right->left), rotateWLeft(curNode->right), rotateWLeft(curNode)), right right (splayRecur(val, curNode->right->right), rotateWLeft(curNode), rotateWLeft(curNode))
			insert a val: splayRecur to move closest val to root, if new root isn't the target val, new a node with the target val to be the root and move old root to its left or right child
			contains a val: splayRecur to move closest val to root, check if root's val equal to target val
			remove a val: splayRecur to move closest val to root, check if root's val equal to target val, if equal, make new root point to old root's left child, splayRecur(val, new root) such that new root will contain the max val of all old root's left children so that new root's right child must be null, then assign old root's right to new root's right, then finally delete old root
Red black tree:
Binary min heap:
BST:
*/
/*
sorted stack
CartesianTree construct: sorted stack in increasing order
Max rectangle in histogram: sorted stack in increasing order
All stock span: sorted stack in decreasing order
BuildingsViewSunset: sorted stack in decreasing order
Verify preorder traversal BST: sorted stack in decreasing order
*/
/*
ReverseWords.h
ValidNumber.h
RegexMatching.h
ExtendedSimpleRegexMatching.h
WildcardMatching.h

*/
/*
special formula:
+ Permutations2.h
Permutation FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of permutations.
n!

Permutation FromDupArray:
Given a collection of n numbers that might contain duplicates, count the number of permutations.
                                      n!
-----------------------------------------------------------------------------------
(dupCount_1)! * (dupCount_2)! * (dupCount_3)! * ... * (dupCount_DistinctNumCount)!



Combination NoRepeat FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of combinations of k-distinct numbers out of n.
    n!
------------
k! * (n-k)!

Combination AllowRepeat FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of combinations of k-may-repeat numbers out of n.
  (n+k-1)!
------------
k! * (n-1)!

Combination-NoRepeat-FromNoDupArray Plus Permutation-FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of DISTINCT ORDER combinations of k-distinct numbers out of n.
    n!                 k!               n!
------------ * ------------------  =  ------
k! * (n-k)!    1! * 1! * ... * 1!     (n-k)!

Combination-AllowRepeat-FromNoDupArray Plus Permutation-FromDupArray:
Given a collection of n numbers that don't contain duplicates, count the number of DISTINCT ORDER combinations of k-may-repeat numbers out of n.
n^k

+ CatalanNumber.h
Recurion formula:
C0 = 1
            n
Cn+1 = Sigma     Ci*Cn-i
            i=0

DP1D formula:
          n-1
Tn = Sigma     Ti*Tn-i
          i=0

UseBinomialCoefficient formula:
      1     / 2n \      1           (2n)!         (2n)!
Cn = --- * |      | = ----- * -------------- = ----------
     n+1    \  n /     n+1     n! * (2n-n)!     (n+1)!*n!

+ BinomialCoefficient.h
  / n \        n!
 |     | = -----------
  \ k /    k! * (n-k)!

Recursion:
C(n, k) = C(n-1, k-1) + C(n-1, k)
C(n, 0) = C(n, n) = 1

Formula:
C(n, k) = n! / [(n-k)! * k!]
        = [n * (n-1) *....* 1]  / [ ( (n-k) * (n-k-1) * .... * 1) * ( k * (k-1) * .... * 1 ) ]
After simplifying, we get
C(n, k) = [n * (n-1) * .... * (n-k+1)] / [k * (k-1) * .... * 1]
        = [n * (n-1) * .... * (n-k+1)] / k!
Also, C(n, k) = C(n, n-k)  // we can change r to n-r if r > n-r 

Arranging binomial coefficients into rows for successive values of n, and in which k ranges from 0 to n, gives a trianglar array called Pascal's triangle.
n
0:                 1
1:               1   1
2:             1   2   1
3:           1   3   3   1
4:         1   4   6   4   1
5:       1   5  10   10  5   1
6:     1   6  15   20  15  6   1
7:   1   7  21  35   35  21  7   1
8: 1   8  28  56  70   56  28  8   1

for n=5: (x+y)^5 = 1*x^5 + 5*x^4*y + 10*x^3*y^2 + 10*x^2*y^3 + 5*x*y^4 + 1*y^5

+ IsPrime.h
Only numbers that are not multiples of 2 and 3, and are also in the form of 6*i-1 or 6*i+1 are primes.
+ FibonacciNumber.h
A number is Fibonacci if and only if one or both of (5*n^2+4) or (5*n^2-4) is a perfect square.
*/
/*
idx: 0, 1, 2, 3
(0+3)/2 = 1
4/2 = 2

1.
mid = (left + right) / N
mid points to the LEFT of middle pair for even N (middle for odd N)
2.
mid = N / 2
mid points to the RIGHT of middle pair for even N (middle for odd N) => BEGIN of 2nd half
3. mid = (N - 1) / 2, for N >= 1
mid points to the LEFT of middle pair for even N, or the NEXT LEFT of middle for odd N => END of 1st half
*/
/*
ListNode * slow = head;
ListNode * fast = head;
ListNode * preSlow = NULL;
while (fast && fast->next)
{
	preSlow = slow;
	slow = slow->next;
	fast = fast->next->next;
}

now slow is the middle node for an odd list,
OR the right node of middle node pair for an even list.
(Aka the first node of the 2nd half list.)

preSlow is the left node of the middle node for an odd list,
OR the left node of middle node pair for an even list.
(Aka the last node of the 1st half list.)
*/
/*
EnumerateSubRangeConsecuPartitions:
recur:
keep a left, right pointers
if (left > or == right)
	return corner case
for (mid = left+1; mid < right; ++mid)
	recur(left, mid)
	recur(mid, right)
	compute all enumerations or optimum result
return dp[left][right] = all enumerations or optimum result

DP:
for (len = 2; len < N; ++len)
	for (left = 0; left < N - len + 1; ++left)
		right = left + len - 1
		for (mid = left + 1; mid < right; ++mid)
			dp[left][right] = dp[left][mid] some operation dp[mid][right]
*/
/*
                      ----> QuickSelect, std::nth_element (KthSmallestElement) (O(n) time in avg, O(n^2) time in worst case)
                     /
partition (O(n) time)
                     \
		              ----> QuickSort (O(nlogn) time)
*/
/*
get array size template function:
http://stackoverflow.com/questions/1500363/compile-time-sizeof-array-without-using-a-macro
http://blogs.msdn.com/b/the1/archive/2004/05/07/128242.aspx


template<typename T,int N>
//template argument deduction
unsigned int mycountof1(T (&arr1)[N]) //the array size must be known in compile time so that template can be specialized
{
unsigned int size;
size=sizeof(arr1)/sizeof(arr1[0]);
return size;
}

template<typename T, unsigned int N>
char ( &_ArraySizeHelper( T (&Array) [N] ) ) [N];
#define mycountof( Array ) (sizeof( _ArraySizeHelper( Array ) ))//the array size must be known in compile time so that template can be specialized


*/

/*
To Do:
Generate maze
*/
#endif