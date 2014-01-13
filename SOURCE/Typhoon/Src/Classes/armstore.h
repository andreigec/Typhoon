//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _ARMSTORE_H
#define _ARMSTORE_H

class armstore
{
public:
	armstore * nextptr;
	armstore * prevptr;
	int id;
	int type;
	char *name;
	int cost;
	int defensePercent;
	char * path;
	armstore();
	~armstore();

	void operator= (armstore *v)
	{
		if (v==NULL)
		{
		CONSOLE.pushtext(true,0,"ERROR! Trying to copy armour value from nothing!");
		return;
		}
	id=v->id;
	type=v->type;
	mystrdup(&name,v->name);
	cost=v->cost;
	defensePercent=v->defensePercent;
	mystrdup(&path,v->path);
	}

	void init();
	void dinit();
	
};
#endif