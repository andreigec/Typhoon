#ifndef _LINKEDLISTNODE_CPP
#define _LINKEDLISTNODE_CPP

template <class T>
LinkedListNode<T>::LinkedListNode()
{
	nextptr=NULL;
	prevptr=NULL;
	value=NULL;
}

template <class T>
LinkedListNode<T>::~LinkedListNode()
{
}

#endif
