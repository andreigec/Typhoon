//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SPLSTORE_H
#define _SPLSTORE_H

class splstore
{
public:
	splstore * nextptr;
	splstore * prevptr;
	int id;
	int type;
	char *name;
	int cost;
	int mp;
	int basedamage;
	char * path;
	splstore();
	~splstore();	
};

#endif