//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PLAY2_H
#define _PLAY2_H

class  PLAY2
{
public:
	int strength;
	int luck;
	bool canswim;
	int survival;
	int maxsurvival;
	int dexterity;
	int agility;
	int intelligence;
	int constitution;
	int skillpoints;
	void init();
	PLAY2();
	~PLAY2();
	char * savevals(char * objtype);
	void loadvals(FILE * fileptr);

};
PLAY2 PLAYERSTATS;

#endif