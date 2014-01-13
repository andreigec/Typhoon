//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PATHHEAD_H
#define _PATHHEAD_H

class pathhead
{
public:
	void clearall();
	path * addpath(int x,int y);
	path * findpath(int x,int y);
	int enemypathcount;
	path * enemypathhead;
	path * enemypathtail;
	pathhead();
	~pathhead();
};
pathhead pathz;

#endif