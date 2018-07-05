#include <stdio.h>

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

//====================================================================
/// @ Description - the TreeNode class acts as the basis for 
/// 		    our tree
/// @ Private-Field: <data>          - the integer data to store
/// @ Private-Field: <left_child>    - the reference to the left_child
/// @ Private-Field: <right_sibling> - reference to the right_sibling
//====================================================================
class TreeNode
{
	private:
	{
		int * data;
		TreeNode * left_child;
		TreeNode * right_sibling;
	}

	public:
	{
		void setData(int);

		TreeNode * getLeftChild(TreeNode *);
		TreeNode * getRightSibling(TreeNode *);

		void addNode(TreeNode *);

		TreeNode * findNode(int);		
		
		void removeNode(int);
	}
};

class BinaryTree
{
	private:
	{

	}

	public:
	{

	}
};
#endif
