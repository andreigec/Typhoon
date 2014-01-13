//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _EXITPOINT_CPP
#define _EXITPOINT_CPP
exitpoint::exitpoint()
{
nextptr=NULL;
prevptr=NULL;
id=0;
xpos=0;
ypos=0;
ispop=false;
forceType=0;
changeX=0;
changeY=0;
}

exitpoint::~exitpoint()
{
}

#endif
