//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _OBJSTORE_CPP
#define _OBJSTORE_CPP

objstore::objstore()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
cost=0;
name=NULL;
questitem=false;
path=NULL;
}

objstore::~objstore()
{
if (name!=NULL)
	delete name;
if (path!=NULL)
delete path;
}

#endif