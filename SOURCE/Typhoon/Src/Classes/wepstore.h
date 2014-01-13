//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _WEPSTORE_H
#define _WEPSTORE_H

class wepstore
{
public:
	wepstore * nextptr;
	wepstore * prevptr;
	int id;
	int type;
	char *name;
	int cost;
	int damage;
	int strengthReq;
	bool oneHanded;
	char * path;
	wepstore();
	~wepstore();
	
	void operator= (wepstore *v)
	{
		if (v==NULL)
		{
		CONSOLE.pushtext(true,0,"ERROR! Trying to copy weapon value from nothing!");
		return;
		}
	id=v->id;
	type=v->type;
	mystrdup(&name,v->name);
	cost=v->cost;
	damage=v->damage;
	strengthReq=v->strengthReq;
	oneHanded=v->oneHanded;
	mystrdup(&path,v->path);
	}

	void init();
	void dinit();

};

#endif