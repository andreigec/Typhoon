//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _OBJSTORE_H
#define _OBJSTORE_H

class objstore
{
public:
	objstore * nextptr;
	objstore * prevptr;
	int id;
	int type;
	int cost;
	char *name;
	bool questitem;
	char * path;
	objstore();
	~objstore();
	
};

#endif