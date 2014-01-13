//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _DUN_CPP
#define _DUN_CPP

char* DUN::savevals(char * objtype)
{

	char temp[100];temp[0]=0;
	sprintf(temp," %s %d",objtype,DUNGEON.currentlevel);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void DUN::loadvals(FILE * fileptr)
{	fscanf_s(fileptr,"%d",&currentlevel);
}

void DUN::dinit()
{
}


void DUN::init()
{
	currentlevel=0;
	lastlevel=0;
	mapsize=0;
	maptype=0;
	isdungeon=false;
	firstlevelmapid=-1;
	lastlevelmapid=-1;	
}

DUN::DUN()
{
	init();
}

DUN::~DUN()
{
	dinit();
}

#endif