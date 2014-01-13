//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NODEOBJECT_H
#define _NODEOBJECT_H

class NodeObject:public NodeBase
{
public:
	NodeObject();	
	~NodeObject();
	void initno();
	void dinitno();
	bool setvalues(int newamount,int newid,int x, int y);
	float returnbaramount();
	bool questitem; //item only
	char * saveobject(char * objtype);
	void loadobject(FILE * fileptr);
	int amount;
	int amount2;
};

#endif