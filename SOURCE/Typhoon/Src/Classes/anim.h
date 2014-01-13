//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _ANIM_H
#define _ANIM_H

class anim
{
	//opening animations, thread timer functions
public:
	void init();
	void dinit();
	anim();
	~anim();

	//int timer;
	//int timertimer;
	int POSX;
	int POSY;
	int DIRECTION;
	bool minimap;
	int height,width;
	//first element is the day level, last is night
	int LIGHTLEVELTABLE[12];
	void LIGHTLEVELTABLEINIT(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11,int a12);
	//for use with mini time pic
	int LIGHTLEVELLENGTH;
	//how long before each state switches
	int LIGHTLEVELTIME;
	int SCREENWIDTH;
	int SCREENHEIGHT;
	float SCREENSTARTX;
	float SCREENSTARTY;

	void setview(int vw,int vh);	
	int getVIEWWIDTH();
	int getVIEWHEIGHT();
	void setVIEWWIDTH(int value);
	void setVIEWHEIGHT(int value);

	float tilesizeheight;
	float tilesizewidth;
	void tilesizeinit();
	void timestep();
	void openinganimationsetup();
	void openinganimationstep();
	bool timerenabled;

	void pushview(int globalloopswitch);
	void popview(int * x,int * y);

	void loadvals(FILE * fileptr);
	char* savevals(char * objtype);

private:
	int VIEWWIDTH;
	int VIEWHEIGHT;
	int lastVIEWWIDTH;
	int lastVIEWHEIGHT;
};
anim ANIMATION;
#endif
