//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPSTAX_H
#define _MAPSTAX_H

class mapstax
{
public:
	mapstax * upptr;
	mapstax * downptr;
	int x;
	int y;
	int id;
	mapstax();
	~mapstax();
};

#endif