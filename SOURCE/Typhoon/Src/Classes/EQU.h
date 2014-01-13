//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _EQU_H
#define _EQU_H

class EQU
{
public:
	wepstore LARM;
	wepstore RARM;
	armstore SHOES;
	armstore CHEST;
	armstore HELM;
	armstore LEGS;
	EQU();
	~EQU();
	void init();
	void loadvals(FILE * fileptr);
	char* savevals(char * objtype);
	};
EQU EQUIPMENT;
#endif

