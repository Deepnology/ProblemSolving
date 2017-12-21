#ifndef FLATTEN_BINARY_TREE_TO_LINKED_LIST_H
#define FLATTEN_BINARY_TREE_TO_LINKED_LIST_H
/*
Leetcode: Tree To Linked List
// Flatten Binary Tree to Linked List
// Given a binary tree, flatten it to a linked list in-place.
//
// For example,
// Given
//
//         1
//        / \
//       2   5
//      / \   \
//     3   4   6
// The flattened tree should look like:
//   1
//    \
//     2
//      \
//       3
//        \
//         4
//          \
//           5
//            \
//             6
// Hints:
// If you notice carefully in the flattened tree, each node's right child
// points to the next node of a pre-order traversal.
//
// Complexity:
// O(n) time, O(1) space

//         1
//        / \
//       2   5 <- cut
//      / \   \
//     3   4   6

//         1
//          \
//           2 <- move from left to right
//          / \
//         3   4 <- cut
//              \
//               5 <- paste
//                \
//                 6

//         1
//          \
//           2
//            \
//             3 <- move from left to right
//              \
//               4 <- paste
//                \
//                 5
//                  \
//                   6
*/

class FlattenBinaryTreeToLinkedList
{
public:
	FlattenBinaryTreeToLinkedList(){}
	~FlattenBinaryTreeToLinkedList(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL){}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	void GO(TreeNode * root)
	{
		while (root != NULL)
		{
			if (root->left != NULL)
			{
				//1. cut right child
				TreeNode * right = root->right;
				//2. move left child to right child
				root->right = root->left;
				root->left = NULL;
				//3. past right child to the rightmost child
				TreeNode * Rmost = root;
				while (Rmost->right)
					Rmost = Rmost->right;
				Rmost->right = right;
			}

			//move root down to right child
			root = root->right;
		}
	}


	static void DeleteTree(TreeNode * root)
	{
		if (root == 0)
			return;

		DeleteTree(root->left);
		DeleteTree(root->right);

		//post order
		delete root;
		root = 0;
	}
};
/*
FlattenBinaryTreeToLinkedList:
      
       1
    __ 1__
   /       \
   2       2
   2       5
 /   \   /   \
 3   3   X   3
 3   4   N   6

                                                              
                                                               1
                                ______________________________ 1______________________________
                               /                                                               \
                               X                                                               2
                ______________ N______________                                  ______________ 2______________
               /                               \                               /                               \
               X                               X                               X                               3
        ______ N______                  ______ N______                  ______ N______                  ______ 3______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               X               X               4
    __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ 4__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       5
   N       N       N       N       N       N       N       N       N       N       N       N       N       N       N       5
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   6

*/
#endif