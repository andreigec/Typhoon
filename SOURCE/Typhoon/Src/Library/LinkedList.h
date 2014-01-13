//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

template <class T>
class LinkedList
{
public:
	
	LinkedListNode<T> * headptr;
	LinkedListNode<T> * tailptr;

	T *insertNode();

	T * operator[](int iteration);
	LinkedListNode<T> * getIteration(int iteration);

	LinkedListNode<T> *reverseGetNode(T * val);

	bool deleteNode(LinkedListNode<T> * deletethis);
	bool deleteNode(T * deletethis);

	//delete all nodes
	void clear();
	int getCount();

	LinkedList();
	~LinkedList();

private:
	int count;
};


#endif