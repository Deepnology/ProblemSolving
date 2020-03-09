#ifndef DELETE_BINARY_TREE_H
#define DELETE_BINARY_TREE_H
#include <string>
#include <iostream>
/*
http://www.keithschwarz.com/interesting/code/?dir=inplace-tree-delete
Inorder/Postorder Recursive Delete:
O(n) time
O(height) space, O(n) space in worst case for a degenerate tree (where most or all of the nodes contain only one sub node)

Left Rotation Iterative Delete:
1. If the tree root is NULL, we are done.
2. If the tree root has a left child, apply a left rotation.
3. If the tree root has no left child, delete the root and make its right
   child the root of the tree.
4. Go to (1)
O(n) time, O(1) space
*/
template<class NODE>
class DeleteBinaryTree
{
public:
	DeleteBinaryTree(){}
	~DeleteBinaryTree(){}
	void InOrder_Recur(NODE * root)
	{
		if (root == nullptr)
			return;
		this->InOrder_Recur(this->GetLeft(root));
		NODE * right = this->GetRight(root);
		std::cout << "Delete " << this->GetVal(root) << std::endl;
		delete root;//in-order visiting the node
		root = nullptr;
		this->InOrder_Recur(right);
	}
	void PostOrder_Recur(NODE * root)
	{
		if (root == nullptr)
			return;
		this->PostOrder_Recur(this->GetLeft(root));
		this->PostOrder_Recur(this->GetRight(root));
		std::cout << "Delete " << this->GetVal(root) << std::endl;
		delete root;//post-order visiting the node
		root = nullptr;
	}
	void LeftRotate_Iterate(NODE * root)
	{
		while (root != nullptr)
		{
			/*left rotate if there is a left child*/
			if (this->GetLeft(root) != nullptr)
			{
				NODE * left = this->GetLeft(root);
				this->SetLeft(root, this->GetRight(this->GetLeft(root)));
				this->SetRight(left, root);
				root = left;
			}
			else
			{
				NODE * right = this->GetRight(root);
				std::cout << "Delete " << this->GetVal(root) << std::endl;
				delete root;
				root = right;
			}
		}
	}

private:
	NODE * GetLeft(NODE * root);
	NODE * GetRight(NODE * root);
	void SetLeft(NODE * root, NODE * node);
	void SetRight(NODE * root, NODE * node);
	std::string GetVal(NODE * root);
};

template<class NODE>
NODE * DeleteBinaryTree<NODE>::GetLeft(NODE * root)
{
	return root->left;//by default
}
template<class NODE>
NODE * DeleteBinaryTree<NODE>::GetRight(NODE * root)
{
	return root->right;//by default
}
template<class NODE>
void DeleteBinaryTree<NODE>::SetLeft(NODE * root, NODE * node)
{
	root->left = node;//by default
}
template<class NODE>
void DeleteBinaryTree<NODE>::SetRight(NODE * root, NODE * node)
{
	root->right = node;//by default
}

template<class NODE>
std::string DeleteBinaryTree<NODE>::GetVal(NODE * root)
{
	return std::to_string(root->val);//by default
}
#endif