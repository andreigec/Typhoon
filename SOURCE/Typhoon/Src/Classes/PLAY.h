//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PLAY_H
#define _PLAY_H

class PLAY{
public:
	//directions
	//  8
	//4 5 6
	//  2
	int direction;
	//int points;
	//int maxpoints;
	int regen;
	int maxregen;
	int health;
	int maxhealth;
	int air;
	int maxair;
	int posx;
	int posy;
	int lastx;
	int lasty;
	int dash;
	int stamina;
	int maxstamina;
	char name[100];
	char race[100];
	char image[100];
	long int gold;
	long int maxgold;
	int food;
	int maxfood;
	int magic;
	int maxmagic;
	int level;
	int maxlevel;
	int exp;
	int maxexp;
	bool lockmove;
	int viewdist;
	void init();
	void checkenv();
	void levelup();
	PLAY();	
	~PLAY();
	char * savevals(char * objtype);
	void loadvals(FILE * fileptr);
	//save this out of savevals
	bool hasSpellTable[100];

};
PLAY PLAYER;

#endif