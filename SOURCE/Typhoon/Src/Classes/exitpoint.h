//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _EXITPOINT_H
#define _EXITPOINT_H

class exitpoint
{
public:
exitpoint * nextptr;
exitpoint * prevptr;

int id;
int xpos;
int ypos;
bool ispop;
int forceType;
int changeX;
int changeY;

void operator= (exitpoint *v)
	{
		if (v==NULL)
		{
		CONSOLE.pushtext(true,0,"ERROR! Trying to copy exit value from nothing!");
		return;
		}
	id=v->id;
	xpos=v->xpos;
	ypos=v->ypos;
	ispop=v->ispop;
	forceType=v->forceType;
	changeX=v->changeX;
	changeY=v->changeY;
	}

exitpoint();
~exitpoint();

};

#endif
