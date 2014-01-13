//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _DUN_H
#define _DUN_H

class DUN
{
public:
	int currentlevel;
	int lastlevel;
	int firstlevelmapid;
	int lastlevelmapid;
	int mapsize;
	int maptype; 
	bool isdungeon;

	void init();
	DUN();
	void dinit();
	~DUN();
	char * savevals(char * objtype);
	void loadvals(FILE * fileptr);
};
DUN DUNGEON;
#endif