//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPENEMIESLIST_H
#define _MAPENEMIESLIST_H

class mapenemieslist
{
public:
	LinkedList<NodeEnemy> mapenemies;
	mapenemieslist * nextptr;
	mapenemieslist * prevptr;
	mapenemieslist();
	char * saveenemy(char * objtype);
	void loadenemy(FILE * fileptr);
};

#endif