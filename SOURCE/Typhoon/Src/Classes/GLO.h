//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _GLO_H
#define _GLO_H

class GLO
{
	//global game variables
public:
	int xresolution;
	int yresolution;
	
	bool soundenabled;
	bool consoleenabled;
	bool debugenabled;
	bool isfullscreen;
	bool changeKeyboardRepeatSpeed;
	
	//number of update screen threads running - should be singleton (1)
	int updateThreadCount;

	//seed value for game, to easily reproduce bugs
	int seed;
	int count;
	int firsttime;
	//int enemyrate;
	int loopswitch;
	int loopswitch2;
	int runninggame;
	int worldstatus;
	int nighttend;
	//int minenemylevel;
	//use this to debug tiles:
	int debugTiles;
	
	bool lockcount;
	int questloopswitch;
	bool blackscreen;
	bool spawnenemies;
	//0=no 1=in 2=out
	int fadestyle;
	int fadeamount;
	int fadestart;
	int soundvolume;
	int musicvolume;
	int mastervolume;
	void init();
	void saveconfig();
	void loadconfig();
	GLO();	
	~GLO();
	char * savevals(char * objtype);
	void loadvals(FILE * fileptr);
	};
GLO GLOBAL;

#endif