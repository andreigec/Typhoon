//Coded by Andrei Gec 2008
#ifndef _TreeNode_CPP
#define _TreeNode_CPP


template <class T,class Y>
int TreeNodeAbstract<T,Y>::getbalance()
{
	return (Rheight-Lheight);
}

template <class T,class Y>
Y * TreeNodeAbstract<T,Y>::nextInOrder()
{		
	Y * newptr=(Y*)this;
	Y * last=(Y*)this;

	while (newptr!=NULL)
	{
		if (newptr->leftptr==last)
			return newptr;

		else if (rightptr!=NULL)
		{
			newptr=newptr->rightptr;
			while (newptr->leftptr!=NULL)
				newptr=newptr->leftptr;
			return newptr;
		}

		last=newptr;
		newptr=newptr->headptr;
	}
	return NULL;		
}

template <class T,class Y>
Y * TreeNodeAbstract<T,Y>::prevInOrder()
{
	Y * newptr=this;
	Y * last=this;

	while (newptr!=NULL)
	{
		if (newptr->rightptr==last)
			return newptr;

		else if (leftptr!=NULL)
		{
			newptr=newptr->leftptr;
			while (newptr->rightptr!=NULL)
				newptr=newptr->rightptr;
			return newptr;
		}

		last=newptr;
		newptr=newptr->headptr;
	}
	return NULL;		
}

template <class T,class Y>
TreeNodeAbstract<T,Y>::TreeNodeAbstract()
{
	leftptr=NULL;
	rightptr=NULL;
	headptr=NULL;
	Lheight=0;
	Rheight=0;
	value=NULL;
	key=NULL;
}

//find the child with the parameter key, and set it to newptr
template <class T,class Y>
bool TreeNodeAbstract<T,Y>::setchildkey(char * key,Y * newptr)
{
	if (leftptr!=NULL&&strcmp(key,leftptr->key)==0)
	{
		leftptr=newptr;
		if (leftptr==NULL)
			Lheight=0;
		return true;
	}

	else if (rightptr!=NULL&&strcmp(key,rightptr->key)==0)
	{
		rightptr=newptr;
		if (rightptr==NULL)
			Rheight=0;
		return true;
	}

	return false;
}

template <class T,class Y>
TreeNodeAbstract<T,Y>::~TreeNodeAbstract()
{
	delete value;
	delete[] key;
}


#endif