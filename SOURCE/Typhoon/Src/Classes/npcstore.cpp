//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NPCSTORE_CPP
#define _NPCSTORE_CPP


npcstore::npcstore()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
level=0;
name=NULL;
attackbase=0;
defensebase=0;
hp=0;
canswim=false;
faction=0;
path=NULL;
exp=0;
}

npcstore::~npcstore()
{
if (name!=NULL)
	delete name;
if (path!=NULL)
delete path;
}

#endif