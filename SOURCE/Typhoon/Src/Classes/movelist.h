//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MOVELIST_H
#define _MOVELIST_H

class movelist
{
public:
	int x;
	int y;
	movelist * nextptr;
	movelist * prevptr;
	//    ~movelist();
	movelist();
	~movelist();	
};

#endif