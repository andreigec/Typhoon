//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NPCSTORE_H
#define _NPCSTORE_H

class npcstore
{
public:
	npcstore * nextptr;
	npcstore * prevptr;
	int id;
	int type;
	int level;
	char *name;
	int attackbase;
	int defensebase;
	int hp;
	int exp;
	bool canswim;
	int faction;
	char * path;
	npcstore();
	~npcstore();	
};

#endif