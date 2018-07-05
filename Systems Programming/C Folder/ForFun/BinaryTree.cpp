#include "BinaryTree.h"

//===================================================
/// @ Description - sets the data value for this Node
///
/// @ param[in] <value> - the value to set
/// @ retunr <void>
//===================================================
void TreeNode::setData(int value)
{
	*this->data = value;
}

//==================================================================
/// @ Description - returns the left_child of the the given TreeNode
///
/// @ param[in] <node> - the node the left child belongs to
/// # return <TreeNode *> - a pointer to the left child
//==================================================================
TreeNode * TreeNode::getLeftChild(TreeNode * node)
{
	TreeNode * left_child;

	if(!node)
		left_child = nullptr;
	else
	{
		if(!node->left_child)
			left_child = nullptr;
		else
			left_child = node->left_child;
				
	}

	return left_child;
}

 
//=====================================================================
/// @ Description - returns the right sibling of the the given TreeNode
///
/// @ param[in] <node> - the node the left child belongs to
/// # return <TreeNode *> - a pointer to the right sibling
//=====================================================================
TreeNode * TreeNode::getRightSibling(TreeNode * node)
{
	TreeNode * right_sibling

	if(!node)
		right_sibling = nullptr;
	else
	{
		if(!node->left_sibling)
			right_sibling = nullptr;
		else
			right_sibling = node->right_sibling;
				
	}

	return right_sibling;
}

//==================================================
/// @ Description - adds a node to the Binary Tree
///
/// @ param[in] <node> - the node to add
/// @ return <void>
//==================================================
void TreeNode::addNode(TreeNode * node)
{
	

}
 
