//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SP_H
#define _SP_H

//400-499=spells
class SP
{
public:
	int active;
	int basedamage;
	int mp;
	char image[100];
	char name[100];
	int type;
	void init();
	SP();	
	~SP();
	char * savevals(char * objtype);
	void loadvals(FILE * fileptr);
};

SP SPELL;
SP SPELL2;

#endif