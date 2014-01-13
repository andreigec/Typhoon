//Coded by Andrei Gec 2008
#ifndef _AVLTREE_H
#define _AVLTREE_H

//AVL TreeAbstract implementation
//when depth of nodes of a leaf is imbalanced over 1 or -1, rotate the TreeAbstract to make them even.
template <class T>
//inherit from the basic TreeAbstract class
class AVLTree:public TreeAbstract< T,AVLTreeNode<T> >
{
public:
	//insert a node into the TreeAbstract, but all
	T *insertNode(const char * key);

	bool deleteNode(const char * key);
	bool deleteNode(AVLTreeNode<T> * deletethis);

	AVLTree();
	~AVLTree();

private:

	//globally stop rotating the TreeAbstract (will turn into a stardard binary TreeAbstract)
	bool AVLrotations;	

	//delete node, allow for non rotations, and non deletions(set all pointers to null etc, but dont delete the target in the end)
	void PdeleteNode(AVLTreeNode<T> * deletethis,bool actuallydelete,bool rotate);
	
	void balancetree(AVLTreeNode<T> * bptr);
	void balancenode(AVLTreeNode<T> * bptr);

	void rotatenode(AVLTreeNode<T> * newptr);
	void rotatetree(AVLTreeNode<T> * newptr);

	void rightRotation(AVLTreeNode<T> * newptr);
	void rightRotation2(AVLTreeNode<T> * newptr);
	void leftRotation(AVLTreeNode<T> * newptr);
	void leftRotation2(AVLTreeNode<T> * newptr);	
};

#endif
