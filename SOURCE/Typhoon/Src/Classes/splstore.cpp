//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SPLSTORE_CPP
#define _SPLSTORE_CPP

splstore::splstore()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
name=NULL;
cost=0;
mp=0;
basedamage=0;
path=NULL;
}

splstore::~splstore()
{
if (name!=NULL)
	delete name;
if (path!=NULL)
delete path;
}

#endif