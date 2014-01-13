#ifndef _LINKEDLISTNODE_H
#define _LINKEDLISTNODE_H

template <class T>
class LinkedListNode
{
public:
	T * value;

	LinkedListNode();
	~LinkedListNode();

	
	LinkedListNode<T> * nextptr;
	LinkedListNode<T> * prevptr;
};

#endif