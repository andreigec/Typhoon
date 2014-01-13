//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPSTACKHEAD_H
#define _MAPSTACKHEAD_H

class mapstackhead
{
public:
	mapstackhead();
	int stackamount;
	mapstax * stackhead;
	mapstax * push(int id,int xx, int yy);
	mapstax * revpush(int id,int xx, int yy);
	mapstax * pop();
	void initstack();
	char * savemapSTACK(char * objtype);
	void loadmapSTACK(FILE * fileptr);
};

#endif