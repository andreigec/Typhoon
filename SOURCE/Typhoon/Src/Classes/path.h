//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PATH_H
#define _PATH_H

class path
{
public:
	int x;
	int y;
	path * parent;
	path * logicalparent;
	int open;	
	int f;
	int g;
	int h;
	~path();
	path();
	void init();

	path *nextpath;
	path *prevpath;

};

#endif