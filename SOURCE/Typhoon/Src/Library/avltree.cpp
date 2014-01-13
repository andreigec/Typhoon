//Coded by Andrei Gec 2008
#ifndef _AVLTREE_CPP
#define _AVLTREE_CPP

template <class T>
AVLTree<T>::AVLTree()
{
	AVLrotations=true;
}

template <class T>
AVLTree<T>::~AVLTree()
{
	clear();
}


template <class T>
void AVLTree<T>::balancenode(AVLTreeNode<T> * bptr)
{
	if (bptr==NULL)
		return;

	if (bptr->leftptr==NULL&&bptr->rightptr==NULL)
	{
		bptr->Lheight=0;
		bptr->Rheight=0;
	}

	else if (bptr->leftptr!=NULL&&bptr->rightptr!=NULL)
	{
		int L=bptr->leftptr->Lheight;
		if (bptr->leftptr->Rheight>L)
			L=bptr->leftptr->Rheight;

		int R=bptr->rightptr->Lheight;
		if (bptr->rightptr->Rheight>R)
			R=bptr->rightptr->Rheight;

		bptr->Lheight=L+1;	
		bptr->Rheight=R+1;
	}

	else if (bptr->leftptr!=NULL)
	{
		bptr->Rheight=0;

		int L=bptr->leftptr->Lheight;
		if (bptr->leftptr->Rheight>L)
			L=bptr->leftptr->Rheight;

		bptr->Lheight=L+1;
	}

	else if (bptr->rightptr!=NULL)
	{
		bptr->Lheight=0;

		int R=bptr->rightptr->Lheight;
		if (bptr->rightptr->Rheight>R)
			R=bptr->rightptr->Rheight;

		bptr->Rheight=R+1;
	}	
}

template <class T>
void AVLTree<T>::balancetree(AVLTreeNode<T> * bptr)
{
	if (bptr==NULL)
	{
		return;
	}

	while (bptr!=NULL)
	{
		balancenode(bptr);
		bptr=bptr->headptr;
	}
}

template <class T>
bool AVLTree<T>::deleteNode(AVLTreeNode<T> * deletethis)
{
	if (deletethis!=NULL)
	{
		PdeleteNode(deletethis,true,true);
		return true;
	}
	return false;
}

template <class T>
bool AVLTree<T>::deleteNode(const char * searchKey)
{
	AVLTreeNode<T> * deletethis=searchNode(searchKey);
	if (deletethis!=NULL)
	{
		PdeleteNode(deletethis,true,true);
		return true;
	}
	return false;
}


template <class T>
void AVLTree<T>::PdeleteNode(AVLTreeNode<T> * deletethis,bool actuallydelete,bool rotate)
{
	if (rotate)
	{
		if (AVLrotations==false)
			rotate=false;
	}

	if (deletethis==NULL)
	{
		if (debugmode)
			printf("\nCan't delete NULL");
		return;
	}

	AVLTreeNode<T> * successor=NULL;

	if (debugmode)
		printf("\nDeleting Node %s delete=%d",deletethis->key,actuallydelete);
	if (actuallydelete)
		count--;
	//no children
	if (deletethis->leftptr==NULL&&deletethis->rightptr==NULL)
	{
		if (debugmode)
			printf("\n0 children");
		//is root
		if (deletethis->headptr==NULL)
		{
			rootnode=NULL;
			if (actuallydelete)
				delete deletethis;
		}
		else
		{
			AVLTreeNode<T> * balptr=deletethis->headptr;
			balptr->setchildkey(deletethis->key,NULL);
			if (actuallydelete)
				delete deletethis;
			if (AVLrotations)
				balancetree(balptr);

			if (rotate)
			{
				if (actuallydelete)
					rotatetree(balptr);
				else
					rotatenode(balptr);
			}
		}
	}
	//1 child
	else if ((deletethis->leftptr==NULL&&deletethis->rightptr!=NULL)||(deletethis->rightptr==NULL&&deletethis->leftptr!=NULL))
	{
		if (debugmode)
			printf("\n1 child");
		successor=NULL;
		if (deletethis->rightptr!=NULL)
			successor=deletethis->rightptr;
		else
			successor=deletethis->leftptr;

		AVLTreeNode<T> * balptr=successor;
		while (balptr->leftptr!=NULL||balptr->rightptr!=NULL)
		{
			if (balptr->leftptr!=NULL)
				balptr=balptr->leftptr;
			else
				balptr=balptr->rightptr;
		}

		//is root
		if (deletethis->headptr==NULL)
		{
			rootnode=successor;
			successor->headptr=NULL;
		}
		else
		{
			deletethis->headptr->setchildkey(deletethis->key,successor);
			successor->headptr=deletethis->headptr;
		}
		if (actuallydelete)
			delete deletethis;

		if (AVLrotations)
			balancetree(balptr);		
		if (rotate)
		{
			if (actuallydelete)
				rotatetree(balptr);
			else
				rotatenode(balptr);
		}
	}
	//2 children :(
	else
	{
		if (debugmode)
			printf("\n2 children");
		//either inorder right or left
		AVLTreeNode<T> * bptr=NULL;

		if (deletethis->rightptr->leftptr!=NULL)
		{
			successor=deletethis->rightptr->leftptr;
			while (successor->leftptr!=NULL)
			{
				successor=successor->leftptr;
			}
			bptr=successor->headptr;			
		}
		else if (deletethis->leftptr->rightptr!=NULL)
		{
			successor=deletethis->leftptr->rightptr;
			while (successor->rightptr!=NULL)
			{
				successor=successor->rightptr;
			}
			bptr=successor->headptr;			
		}

		else
		{
			successor=deletethis->leftptr;
		}

		//move sucessor
		if (deletethis->headptr==NULL)
			rootnode=successor;
		else
		{
			deletethis->headptr->setchildkey(deletethis->key,successor);
		}

		PdeleteNode(successor,false,true);

		if (deletethis->leftptr!=NULL)
			deletethis->leftptr->headptr=successor;
		if (deletethis->rightptr!=NULL)
			deletethis->rightptr->headptr=successor;

		successor->leftptr=deletethis->leftptr;
		successor->rightptr=deletethis->rightptr;
		successor->headptr=deletethis->headptr;

		if (actuallydelete)
			delete deletethis;
		if (AVLrotations)
		{		
			balancetree(bptr);
			balancetree(successor);
		}
		if (rotate)
		{
			if (actuallydelete)
				rotatetree(bptr);
			else
				rotatenode(bptr);
		}
	}
	if (debugmode)
		printf("\nDone Deletion");
}

template <class T>
void AVLTree<T>::rightRotation(AVLTreeNode<T> * newptr)
{
	AVLTreeNode<T> * base=newptr->headptr;

	AVLTreeNode<T> * A=newptr->rightptr;
	AVLTreeNode<T> * B=NULL;
	AVLTreeNode<T> * C=NULL;
	AVLTreeNode<T> * D=NULL;

	AVLTreeNode<T> * one=newptr;
	AVLTreeNode<T> * two=newptr->leftptr;
	AVLTreeNode<T> * three=NULL;

	if (newptr->leftptr!=NULL)	
	{
		B=newptr->leftptr->rightptr;
		three=newptr->leftptr->leftptr;

		if (newptr->leftptr->leftptr!=NULL)
		{
			C=newptr->leftptr->leftptr->rightptr;
			D=newptr->leftptr->leftptr->leftptr;
		}
	}	

	//headptr
	if (base==NULL)
		rootnode=two;
	else
	{
		if (one->headptr->setchildkey(one->key,two)==false)
		{
			if (debugmode)
				printf("\nCOULD NOT FIND ROOT NODE!");
			return;
		}
	}

	two->leftptr=three;
	two->rightptr=one;
	two->headptr=base;

	three->leftptr=D;
	three->rightptr=C;
	three->headptr=two;

	one->headptr=two;
	one->leftptr=B;
	one->rightptr=A;

	if (A!=NULL)
	{A->headptr=one;balancenode(A);}

	if (B!=NULL)
	{B->headptr=one;balancenode(B);}

	if (C!=NULL)
	{C->headptr=three;balancenode(C);}

	if (D!=NULL)
	{D->headptr=three;balancenode(D);}

	balancenode(one);
	balancenode(three);
	balancetree(two);
}

template <class T>
void AVLTree<T>::leftRotation(AVLTreeNode<T> * newptr)
{
	AVLTreeNode<T> * base=newptr->headptr;

	AVLTreeNode<T> * A=newptr->leftptr;
	AVLTreeNode<T> * B=NULL;
	AVLTreeNode<T> * C=NULL;
	AVLTreeNode<T> * D=NULL;

	AVLTreeNode<T> * one=newptr;
	AVLTreeNode<T> * two=newptr->rightptr;
	AVLTreeNode<T> * three=NULL;

	if (newptr->rightptr!=NULL)
	{
		B=newptr->rightptr->leftptr;
		three=newptr->rightptr->rightptr;

		if (newptr->rightptr->rightptr!=NULL)
		{
			C=newptr->rightptr->rightptr->leftptr;
			D=newptr->rightptr->rightptr->rightptr;
		}
	}

	//headptr
	if (base==NULL)
		rootnode=two;
	else
	{
		if (one->headptr->setchildkey(one->key,two)==false)
		{
			if (debugmode)
				printf("\nCOULD NOT FIND ROOT NODE!");
			return;
		}
	}
	one->leftptr=A;
	one->rightptr=B;
	one->headptr=two;

	two->leftptr=one;
	two->rightptr=three;
	two->headptr=base;

	three->leftptr=C;
	three->rightptr=D;
	three->headptr=two;

	if (A!=NULL)
		A->headptr=one;balancenode(A);

	if (B!=NULL)
		B->headptr=one;balancenode(B);

	if (C!=NULL)
		C->headptr=three;balancenode(C);

	if (D!=NULL)
		D->headptr=three;balancenode(D);

	balancenode(one);
	balancenode(three);
	balancetree(two);
}

template <class T>
void AVLTree<T>::leftRotation2(AVLTreeNode<T> * newptr)
{
	AVLTreeNode<T> * base=newptr->headptr;
	AVLTreeNode<T> * A=newptr->rightptr;
	AVLTreeNode<T> * B=NULL;
	AVLTreeNode<T> * C=NULL;
	AVLTreeNode<T> * D=NULL;

	AVLTreeNode<T> * one=newptr;
	AVLTreeNode<T> * two=newptr->leftptr;
	AVLTreeNode<T> * three=NULL;

	if (newptr->leftptr!=NULL)
	{
		B=newptr->leftptr->leftptr;
		three=newptr->leftptr->rightptr;

		if (newptr->leftptr->rightptr!=NULL)
		{
			C=newptr->leftptr->rightptr->leftptr;
			D=newptr->leftptr->rightptr->rightptr;
		}
	}

	//headptr
	if (base==NULL)
		rootnode=three;
	else
	{
		if (one->headptr->setchildkey(one->key,three)==false)
		{
			if (debugmode)
				printf("\nCOULD NOT FIND ROOT NODE!");
			return;
		}
	}

	three->headptr=base;
	three->leftptr=two;
	three->rightptr=one;

	two->leftptr=B;
	two->rightptr=C;
	two->headptr=three;

	one->headptr=three;
	one->leftptr=D;
	one->rightptr=A;

	if (A!=NULL)
	{A->headptr=one;balancenode(A);}

	if (B!=NULL)
	{B->headptr=two;balancenode(B);}

	if (C!=NULL)
	{C->headptr=two;balancenode(C);}

	if (D!=NULL)
	{D->headptr=one;balancenode(D);}

	balancenode(one);
	balancenode(two);
	balancetree(three);
}

template <class T>
void AVLTree<T>::rightRotation2(AVLTreeNode<T> * newptr)
{
	AVLTreeNode<T> * base=newptr->headptr;
	AVLTreeNode<T> * A=newptr->leftptr;
	AVLTreeNode<T> * B=NULL;
	AVLTreeNode<T> * C=NULL;
	AVLTreeNode<T> * D=NULL;

	AVLTreeNode<T> * one=newptr;
	AVLTreeNode<T> * two=newptr->rightptr;
	AVLTreeNode<T> * three=NULL;

	if (newptr->rightptr!=NULL)
	{
		B=newptr->rightptr->rightptr;
		three=newptr->rightptr->leftptr;

		if (newptr->rightptr->leftptr!=NULL)
		{
			C=newptr->rightptr->leftptr->rightptr;
			D=newptr->rightptr->leftptr->leftptr;
		}	
	}

	//headptr
	if (base==NULL)
		rootnode=three;
	else
	{
		if (one->headptr->setchildkey(one->key,three)==false)
		{
			if (debugmode)
				printf("\nCOULD NOT FIND ROOT NODE!");
			return;
		}
	}

	three->headptr=base;
	three->leftptr=one;
	three->rightptr=two;

	one->headptr=three;
	one->leftptr=A;
	one->rightptr=D;

	two->headptr=three;
	two->leftptr=C;
	two->rightptr=B;

	if (A!=NULL)
	{A->headptr=one;balancenode(A);}

	if (B!=NULL)
	{B->headptr=two;balancenode(B);}

	if (C!=NULL)
	{C->headptr=two;balancenode(C);}

	if (D!=NULL)
	{D->headptr=one;balancenode(D);}

	balancenode(one);
	balancenode(two);
	balancetree(three);
}

template <class T>
void AVLTree<T>::rotatetree(AVLTreeNode<T> * newptr)
{
	if (newptr==NULL)
		return;
	AVLTreeNode<T> * newptr2=newptr->headptr;
	while (newptr!=NULL)
	{
		if (newptr->getbalance()<-1||newptr->getbalance()>1)
		{
			rotatenode(newptr);
		}

		if (newptr2==NULL)
			return;
		newptr=newptr2;
		newptr2=newptr->headptr;
	}
}

template <class T>
void AVLTree<T>::rotatenode(AVLTreeNode<T> * newptr)
{
	if (newptr==NULL)
		return;
	//determine type
	//-2=left left (RR)
	//-1=left right (LR,RR)

	//1=right left (RR,LR)
	//2=right right(LR)
	if (debugmode)
		printf("\nunbal,%s %d\n",newptr->key,newptr->getbalance());

	if (newptr->getbalance()<-1)
	{
		//ll (RR)
		if (newptr->leftptr!=NULL&&newptr->leftptr->getbalance()<=0)
		{
			if (debugmode)
				printf("LR(RR)");
			rightRotation(newptr);
		}

		//lr (LR,RR)
		else if (newptr->leftptr!=NULL&&newptr->leftptr->getbalance()>0)
		{
			if (debugmode)
				printf("LR(LR,RR)");
			leftRotation2(newptr);
		}
	}
	else if (newptr->getbalance()>1)
	{
		//rl (RR,LR)
		if (newptr->rightptr!=NULL&&newptr->rightptr->getbalance()<0)
		{
			if (debugmode)
				printf("RL(RR,LR)");	

			rightRotation2(newptr);
		}

		//rr (LR)
		else if (newptr->rightptr!=NULL&&newptr->rightptr->getbalance()>=0)
		{
			if (debugmode)
				printf("RR(LR)");
			leftRotation(newptr);
		}
	}
}

template <class T>
T* AVLTree<T>::insertNode(const char * searchKey)
{
	TreeAbstract::insertNode(searchKey);
	AVLTreeNode<T> * newnode=searchNode(searchKey);

if (newnode!=NULL&&AVLrotations)
	{
		//balance the TreeAbstract
		balancetree(newnode);

		//sort nodes
		rotatetree(newnode->headptr);
	}
return newnode->value;
}

#endif
