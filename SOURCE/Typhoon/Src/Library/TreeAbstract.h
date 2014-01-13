//Coded by Andrei Gec 2008
#ifndef _TREEABSTRACT_H
#define _TREEABSTRACT_H

//Basic TreeAbstract Structure
//no balancing

//main TreeAbstract functions
//T is the item being stored, Y is the inheriting node class
template <class T,class Y>
class TreeAbstract abstract
{
public:
	//number of nodes in TreeAbstract
	int count;
	
	Y *rootnode;

	Y * getfirstnode();
	Y * getlastnode();

	//if true, output what is happening
	bool debugmode;

	//binary insert node function
	virtual T *insertNode(const char * insertKey);

	//search for a node given a key
	virtual Y *searchNode(const char * key);

	//using the [] operator, search for a node, return its value
	virtual T * operator[](const char * key);
	
	//given a key delete a node
	virtual bool deleteNode(const char * key);

	//given a node, delete it
	virtual bool deleteNode(Y * deletethis);

	//delete all nodes
	virtual void clear();

	TreeAbstract();
	~TreeAbstract();
};


#endif