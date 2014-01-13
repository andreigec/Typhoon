//Coded by Andrei Gec 2008
#ifndef _TREENODEABSTRACT_H
#define _TREENODEABSTRACT_H

//node operations

//T is the item being stored, Y is the inheriting node class
template <class T,class Y>
class TreeNodeAbstract abstract
{
public:
	T * value;

	TreeNodeAbstract();
	~TreeNodeAbstract();

	Y * headptr;
	Y * leftptr;
	Y * rightptr;

	Y * nextInOrder();
	Y * prevInOrder();

	char *key;

	int getbalance();

	int Lheight;
	int Rheight;

	//-1=left,1=right,0=not found
	bool setchildkey(char * key,Y * newptr);

};


#endif