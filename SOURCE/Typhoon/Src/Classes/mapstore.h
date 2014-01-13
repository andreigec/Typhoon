//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPSTORE_H
#define _MAPSTORE_H

class mapstore
{
public:
mapstore * nextptr;
mapstore * prevptr;
char * name;
char * path;
int id;
int type;
int startX;
int startY;
int enemyCreationRate;
int minEnemyLevel;
int darknessLevel;
char * PresetNpcFile;
char * PresetItemFile;
char * PresetExitFile;
char * PresetScriptFile;

mapstore();
~mapstore();
};

#endif