//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPSTORE_CPP
#define _MAPSTORE_CPP

mapstore::mapstore()
{
nextptr=NULL;
prevptr=NULL;
id=0;
type=0;
startX=0;
startY=0;
enemyCreationRate=0;
minEnemyLevel=0;
darknessLevel=0;
PresetNpcFile=NULL;
PresetItemFile=NULL;
PresetExitFile=NULL;
PresetScriptFile=NULL;
path=NULL;
name=NULL;
}

mapstore::~mapstore()
{
if (name!=NULL)
	delete name;
name=NULL;
if (path!=NULL)
delete path;
path=NULL;

if (PresetNpcFile!=NULL)
delete PresetNpcFile;
PresetNpcFile=NULL;

if (PresetItemFile!=NULL)
delete PresetItemFile;
PresetItemFile=NULL;

if (PresetExitFile!=NULL)
delete PresetExitFile;
PresetExitFile=NULL;

if (PresetScriptFile!=NULL)
delete PresetScriptFile;
PresetScriptFile=NULL;


}

#endif