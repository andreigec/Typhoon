//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _HC_H
#define _HC_H

class HC
{
public:
	static const char *version;
	static const char *vname;

	static const int STARTFOOD=100;
	static const int STARTGOLD=100;
	static const int STARTLEVEL=1;
	static const int MAXPLAYERHEALTH=999;
	static const int MAXPLAYERMAGIC=999;
	
	static const int PLAYERSKILLPOINTGAIN=5;
	static const int PLAYEREXPPERLEVEL=250;
	
	static const int marshstamdec=5;
	static const int scriptslength=2000;
	static const int GETKEYBOARDDELAY = 22;
	static const int SETKEYBOARDDELAY = 23;
	static const int GETKEYBOARDSPEED = 10;
	static const int SETKEYBOARDSPEED = 11;
	
	static const int TEXTUREUSAGEMAX=100000;
	static const int SOUNDUSAGEMAX=100000;

	static const int TEXTUREUSAGEMIN=500;
	static const int SOUNDUSAGEMIN=500;
	
	static const int TEXTUREUSAGECUTOFF=100;
	static const int SOUNDUSAGECUTOFF=100;
	
	static const int MAXINVENTORYITEMS=25;
	HC();
};
HC HCVARS;

const char *HC::version=
{
	"V-0.4.0"
};

const char *HC::vname=
{
	"Typhoon V-0.4.0 - Andrei Gec"
};

#endif