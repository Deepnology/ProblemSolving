#ifndef PRINT_BINARY_TREE_H
#define PRINT_BINARY_TREE_H
#include <math.h>
#include <iomanip> // For std::setw()
#include <string>
#define NODE_WIDTH 2

template<class NODE, class OSS>
class PrintBinaryTree
{
public:
	PrintBinaryTree(NODE * root, OSS & oss)
	{
		if (root == nullptr)
		{
			oss << std::endl << std::endl;
			return;
		}
		int rowCount = this->RowCount(root);
		int curIndex = 0;
		int indexTmp = 0;

		//loop through, print each row one by one
		for (int depthY = 1; depthY <= rowCount; ++depthY)
		{
			int rowNodeCount = (int)pow(2.0, (depthY - 1));
			int rowSpaceCount = (int)pow(2.0, (rowCount - depthY)) - 1;
			int rowSpaceCountNext = 0;
			if (depthY < rowCount)
				rowSpaceCountNext = (int)pow(2.0, (rowCount - (depthY + 1))) - 1;
			else
				rowSpaceCountNext = 0;

			indexTmp = curIndex;

			for (int z = 0; z <= 2; ++z)/* z=0: print / and \; z=1: print (node's val2); z=2: print _(node's val)_ */
			{
				for (int rowNodeX = 1; rowNodeX <= rowNodeCount; ++rowNodeX)
				{
					if (rowNodeX == 1)//first node of each level
					{
						if (z == 2 && depthY != rowCount)//z=2, print:   __(node's val)
						{
							this->Spacer((rowSpaceCount - rowSpaceCountNext)*NODE_WIDTH, oss);
							this->Underscore(rowSpaceCountNext*NODE_WIDTH, oss);
						}
						if (z == 2 && depthY == rowCount)
						{
							this->Spacer(rowSpaceCount*NODE_WIDTH, oss);
						}
						if (z == 0 || z == 1)
						{
							this->Spacer(rowSpaceCount*NODE_WIDTH, oss);
						}
					}
					else//after first node
					{
						if (z == 2 && depthY != rowCount)//z=2, print: (node's val)__  __(node's val)
						{
							this->Underscore(rowSpaceCountNext*NODE_WIDTH, oss);
							this->Spacer((rowSpaceCount - rowSpaceCountNext)*NODE_WIDTH + NODE_WIDTH +
								(rowSpaceCount - rowSpaceCountNext)*NODE_WIDTH, oss);
							this->Underscore(rowSpaceCountNext*NODE_WIDTH, oss);
						}
						if (z == 2 && depthY == rowCount)//z=2, last row
						{
							this->Spacer(NODE_WIDTH, oss);
						}
						if ((z == 0 || z == 1) && (depthY != rowCount))
						{
							this->Spacer(rowSpaceCountNext*NODE_WIDTH, oss);
							this->Spacer((rowSpaceCount - rowSpaceCountNext)*NODE_WIDTH + NODE_WIDTH +
								(rowSpaceCount - rowSpaceCountNext)*NODE_WIDTH, oss);
							this->Spacer(rowSpaceCountNext*NODE_WIDTH, oss);
						}
						if ((z == 0 || z == 1) && (depthY == rowCount))
						{
							this->Spacer(NODE_WIDTH, oss);
						}
					}

					if (z == 0)
					{
						if (depthY != 1)
						{
							if (rowNodeX % 2 != 0)
								oss << std::setw(NODE_WIDTH) << "/";
							else
								oss << std::setw(NODE_WIDTH) << "\\";
						}
					}
					if (z == 1)
					{
						++curIndex;
						NODE * n = this->Seek(root, curIndex, rowNodeCount, (rowNodeCount * 2) - 1, 1, depthY);

						if (n == 0)
							oss << std::setw(NODE_WIDTH) << "X";
						else
							oss << std::setw(NODE_WIDTH) << this->selectVal2(depthY, n);//replace it with n->val2
					}
					if (z == 2)
					{
						++indexTmp;
						NODE * n = this->Seek(root, indexTmp, rowNodeCount, (rowNodeCount * 2) - 1, 1, depthY);

						if (n == 0)
							oss << std::setw(NODE_WIDTH) << "N";
						else
							oss << std::setw(NODE_WIDTH) << this->getVal(n);//n->val

						if (rowNodeX == rowNodeCount && depthY != rowCount)//add (node's val)___ for the last node of each row
							this->Underscore(rowSpaceCountNext*NODE_WIDTH, oss);
					}

				}//end for rowNodeX
				if (z == 0 || z == 1)
					oss << std::endl;
			}//end for z
			oss << std::endl;
		}
		oss << std::endl;
	}
	~PrintBinaryTree(){}
private:
	//specialize this member function (cannot be inlined)
	std::string selectVal2(int depthY, NODE * n);

	std::string getVal(NODE * n);
	NODE * getLeft(NODE * n);
	NODE * getRight(NODE * n);

private:
	void Spacer(int count, OSS & oss)
	{
		for (int i = 0; i < count; ++i)
			oss << " ";
	}
	void Underscore(int count, OSS & oss)
	{
		for (int i = 0; i < count; ++i)
			oss << "_";
	}
	int RowCount(NODE * root)
	{
		int leftRow = 0;
		int rightRow = 0;
		if (this->getLeft(root) != 0)
			leftRow = this->RowCount(this->getLeft(root));
		if (this->getRight(root) != 0)
			rightRow = this->RowCount(this->getRight(root));

		if (leftRow > rightRow)
			return leftRow + 1;
		else
			return rightRow + 1;
	}
	NODE * Seek(NODE * root, int index, int a, int b, int curRow, int seekRow)
	{
		if (root == 0)
			return 0;

		int c = (int)floor(double((a + b) / 2));

		NODE * curNode = 0;
		if (index <= c)
		{
			curNode = this->getLeft(root);
			b = c;
		}
		else
		{
			curNode = this->getRight(root);
			a = c + 1;
		}

		if (seekRow == 1)
		{
			return root;
		}
		else if (curRow == (seekRow - 1))
		{
			if (curNode == 0)
				return 0;
			else
				return curNode;
		}
		else
		{
			return this->Seek(curNode, index, a, b, curRow + 1, seekRow);
		}

	}
};

template<class NODE, class OSS>
std::string PrintBinaryTree<NODE, OSS>::selectVal2(int depth, NODE * n)
{
	std::ostringstream oss;
	oss << depth;//by default
	return oss.str();
}

template<class NODE, class OSS>
std::string PrintBinaryTree<NODE, OSS>::getVal(NODE * n)
{
	std::ostringstream oss;
	oss << n->val;//by default
	return oss.str();
}
template<class NODE, class OSS>
NODE * PrintBinaryTree<NODE, OSS>::getLeft(NODE * n)
{
	return n->left;//by default
}
template<class NODE, class OSS>
NODE * PrintBinaryTree<NODE, OSS>::getRight(NODE * n)
{
	return n->right;//by default
}

#endif