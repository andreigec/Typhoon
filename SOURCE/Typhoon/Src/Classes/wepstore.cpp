//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _WEPSTORE_CPP
#define _WEPSTORE_CPP

void wepstore::init()
{
nextptr=NULL;
prevptr=NULL;
id=0;
cost=0;
damage=0;
strengthReq=0;
oneHanded=false;

dinit();
}

wepstore::wepstore()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
cost=0;
damage=0;
strengthReq=0;
oneHanded=false;

name=NULL;
path=NULL;

}

void wepstore::dinit()
{
	if (name!=NULL)
	delete name;
if (path!=NULL)
delete path;
name=NULL;
path=NULL;
}

wepstore::~wepstore()
{
dinit();
}

#endif