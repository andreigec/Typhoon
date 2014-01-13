//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _LINKEDLIST_CPP
#define _LINKEDLIST_CPP

template <class T>
int LinkedList<T>::getCount()
{
	return count;
}

template <class T>
LinkedListNode<T> * LinkedList<T>::getIteration(int iteration)
{
	if (iteration<0||iteration>count)
		return NULL;
	bool forwards=true;
	//if in end half of array start from end, if in first half start from front
	//ie, try for O(n/2) search in a linked list
	LinkedListNode<T> * newptr=NULL;
	int valCount=0;
	if (iteration<=(count/2))
	{
		newptr=headptr;
		valCount=0;
	}
	else
	{
		newptr=tailptr;
		valCount=count-1;
		forwards=false;
	}

	while (newptr!=NULL)
	{
		if (valCount==iteration)
			return newptr;

		if (forwards)
		{
			newptr=newptr->nextptr;
			valCount++;
		}
		else
		{
			newptr=newptr->prevptr;
			valCount--;
		}

	}
	return NULL;
}

template <class T>
T* LinkedList<T>::operator[](int iteration)
{
	LinkedListNode<T> * val=getIteration(iteration);
	if (val==NULL)
		return NULL;
	else
	return val->value;
}

template <class T>
LinkedListNode<T> *LinkedList<T>::reverseGetNode(T * val)
{
	LinkedListNode<T> * newptr=headptr;
	while (newptr!=NULL)
	{
		if (newptr->value==val)
			return newptr;
		newptr=newptr->nextptr;
	}
	return NULL;
}


template <class T>
T* LinkedList<T>::insertNode()
{
	LinkedListNode<T> * newnode = new LinkedListNode<T>;
	if (newnode==NULL)
		return NULL;
	count++;
	if (tailptr==NULL)
	{
	headptr=newnode;
	tailptr=newnode;
	}
	else
	{
	tailptr->nextptr=newnode;
	newnode->prevptr=tailptr;
	tailptr=newnode;
	}
	newnode->value= new T;
	return newnode->value;
}

template <class T>
bool LinkedList<T>::deleteNode(LinkedListNode<T> * deletethis)
{
	if (deletethis==NULL)
		return false;
	if (deletethis==headptr)
		headptr=deletethis->nextptr;
	if (deletethis==tailptr)
		tailptr=deletethis->prevptr;

	if (deletethis->prevptr!=NULL)
	{
	deletethis->prevptr->nextptr=deletethis->nextptr;
	}
	if (deletethis->nextptr!=NULL)
	{
	deletethis->nextptr->prevptr=deletethis->prevptr;
	}
	count--;
	delete deletethis;
	return true;
	
} 

template <class T>
bool LinkedList<T>::deleteNode(T * deletethis)
{
	//unless given a specific node, have to find it in O(n) time :(
	if (deletethis==NULL)
		return false;
LinkedListNode<T> * newptr=headptr;
while (newptr!=NULL)
{
if (newptr->value==deletethis)
{
deleteNode(newptr);
return true;
}
newptr=newptr->nextptr;

}
return false;
}


template <class T>
void LinkedList<T>::clear()
{
	LinkedListNode<T> * newptr=headptr;
	LinkedListNode<T> * nextptr=NULL;
	while (newptr!=NULL)
	{
	nextptr=newptr->nextptr;
	delete newptr;
	newptr=nextptr;
	}
	headptr=NULL;
	tailptr=NULL;
	count=0;

}

template <class T>
LinkedList<T>::LinkedList()
{
	tailptr=NULL;
	headptr=NULL;
	count=0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
}



#endif
