#ifndef BINARY_TREE_NODE_WITH_LOCK_H
#define BINARY_TREE_NODE_WITH_LOCK_H
/*
Elements of programming interview, BinaryTrees: Implement locking in a binary tree
This problem is concerned with the design of an API for setting the state of nodes in a binary tree to lock or unlock.
A node's state cannot be set to lock if any of its descendants or ancestors are in lock.
Changing a node's state to lock does not change the state of any other nodes.

Write the following methods for a binary tree node class: bool IsLocked(), bool Lock(), and void Unlock().
The lock() method should return a boolean indicating if the call changed the node's state from unlock to lock.
The time complexities should be O(1), O(h), and O(h) respectively, where h is the height of the binary tree the node belongs to.
*/
class BinaryTreeNodeWithLock
{
	BinaryTreeNodeWithLock * left;
	BinaryTreeNodeWithLock * right;
	BinaryTreeNodeWithLock * parent;
	bool locked;
	int lockedChildrenCount;
public:
	BinaryTreeNodeWithLock() : left(nullptr), right(nullptr), parent(nullptr), locked(false), lockedChildrenCount(0)
	{}
	~BinaryTreeNodeWithLock(){}

	bool IsLocked() const
	{
		return locked;
	}

	/*
	The requirements that a node is able to be locked:
	1. it has 0 locked children
	2. all its ancestors all the way up to the root must not have been locked
	*/
	bool Lock()
	{
		if (lockedChildrenCount == 0 && !locked)
		{
			//check all its ancestors
			BinaryTreeNodeWithLock * cur = parent;
			while (cur)
			{
				if (cur->locked)
					return false;
				cur = cur->parent;
			}

			locked = true;

			//update all its ancestors' lockedChildrenCount
			cur = parent;
			while (cur)
			{
				++cur->lockedChildrenCount;
				cur = cur->parent;
			}
			return true;
		}
		return false;
	}

	void Unlock()
	{
		if (locked)
		{
			locked = false;

			//update all its ancestors' lockedChildrenCount
			BinaryTreeNodeWithLock * cur = parent;
			while (cur)
			{
				--cur->lockedChildrenCount;
				cur = cur->parent;
			}
		}
	}
};
#endif