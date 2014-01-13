//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _ARMSTORE_CPP
#define _ARMSTORE_CPP

void armstore::init()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
cost=0;
defensePercent=0;

dinit();
}

armstore::armstore()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
name=NULL;
cost=0;
defensePercent=0;
path=NULL;
}

armstore::~armstore()
{
dinit();
}

void armstore::dinit()
{
if (name!=NULL)
	delete name;
if (path!=NULL)
delete path;

name=NULL;
path=NULL;
}
#endif