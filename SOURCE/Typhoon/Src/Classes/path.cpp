//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PATH_CPP
#define _PATH_CPP

void path::init()
{
	x=0;
	y=0;
	if (parent!=NULL)
		delete parent;
	parent=NULL;

	if (logicalparent!=NULL)
		delete logicalparent;
	logicalparent=NULL;

	open=0; f=0;g=0;h=0;

	nextpath=NULL;
	prevpath=NULL;
	}

path::path()
{
	parent=NULL;
	logicalparent=NULL;
	init();
}


path::~path()
{
	open=0;
	if (x!=0&&y!=0)
		x=0;y=0;parent=0;f=0;g=0;h=0;
	logicalparent=0;
	nextpath=0;
	prevpath=0;
}

#endif