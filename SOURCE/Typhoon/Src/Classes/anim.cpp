//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 

#ifndef _ANIM_CPP
#define _ANIM_CPP

void anim::openinganimationsetup()
{
	MAPFILES.TERRAINLOSinit(20,8);
	POSX=MAPFILES.currentmap->startX;
	POSY=MAPFILES.currentmap->startY;
	SCREENWIDTH=630;
	SCREENHEIGHT=260;
	SCREENSTARTX=5;
	SCREENSTARTY=370;
	timerenabled=true;
	if (GLOBAL.updateThreadCount==0)
	{
		GLOBAL.updateThreadCount++;
		myTimer(150);
	}
}

void anim::openinganimationstep(void)
{
	int mx,my=0;
	mx=POSX;
	my=POSY;

	switch (DIRECTION)
	{
	case 1:	{mx--;my++;break;}
	case 2:	{my++;break;}
	case 3:	{my++;mx++;break;}
	case 4:	{mx--;break;}
	case 6:	{mx++;break;}
	case 7:	{mx--;my--;break;}
	case 8:	{my--;break;}
	case 9:	{my--;mx++;break;}
	};

	//if okay, move camera, else switch direction
	bool ispassable=true;
	if (my>=MAPFILES.emapheight()||my<0||mx>=MAPFILES.emapwidth()||mx<0)
		ispassable=false;
	else if (MAPFILES.MAPFILE[my][mx]==TT_WATER||MAPFILES.MAPFILE[my][mx]==TT_BLACK)
		ispassable=false;

	if (ispassable)
	{POSX=mx;POSY=my;}
	else
	{
		DIRECTION=rand()%10;
		if (DIRECTION==5||DIRECTION==0)
			DIRECTION++;
	}


	if (DIRECTION==0)
		DIRECTION=3;
}


void anim::timestep()
{
	if (GLOBAL.count%ANIMATION.LIGHTLEVELTIME==0&&GLOBAL.count!=0&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS)&&SPELL.active==0)
	{
		if (GLOBAL.nighttend==1)
		{	
			if (GLOBAL.worldstatus<=9)
				GLOBAL.worldstatus++;
			else 
			{GLOBAL.worldstatus--;GLOBAL.nighttend=0;}
		}	
		else
		{
			if (GLOBAL.worldstatus>=1)
				GLOBAL.worldstatus--;
			else 
			{GLOBAL.worldstatus++;GLOBAL.nighttend=1;}
		}
	}
}

int anim::getVIEWHEIGHT()
{
	return VIEWHEIGHT;
}

int anim::getVIEWWIDTH()
{
	return VIEWWIDTH;
}

void anim::setVIEWWIDTH(int value)
{
	VIEWWIDTH=value;
}

void anim::setVIEWHEIGHT(int value)
{
	VIEWHEIGHT=value;
}

void anim::pushview(int globalloopswitch)
{
	if (globalloopswitch==LS_OPTIONS)
		return;
	lastVIEWHEIGHT=VIEWHEIGHT;
	lastVIEWWIDTH=VIEWWIDTH;
}

void anim::popview(int * x,int * y)
{
	if (lastVIEWHEIGHT==-1||lastVIEWWIDTH==-1)
		return;
	*y=lastVIEWHEIGHT;
	*x=lastVIEWWIDTH;
	lastVIEWHEIGHT=-1;
	lastVIEWWIDTH=-1;
}

void anim::setview(int vw,int vh)
{
	VIEWWIDTH=vw;
	VIEWHEIGHT=vh;
}

void anim::tilesizeinit()
{
	tilesizewidth=((float)ANIMATION.SCREENWIDTH/ANIMATION.getVIEWWIDTH());
	tilesizeheight=((float)ANIMATION.SCREENHEIGHT/ANIMATION.getVIEWHEIGHT());
}


char* anim::savevals(char * objtype)
{
	char temp[100];temp[0]=0;
	//console text

	sprintf(temp," %s %d",objtype,minimap);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void anim::loadvals(FILE * fileptr)
{
	fscanf_s(fileptr,"%d",&minimap);
}

void anim::init()
{
	timerenabled=false;
	MAPFILES.TERRAINLOSinit(15,11);

	SCREENSTARTX=5;
	SCREENSTARTY=475;
	SCREENWIDTH=490;
	SCREENHEIGHT=363;

	POSX=0;
	POSY=0;
	DIRECTION=8;
	height=0;
	width=0;
	LIGHTLEVELTABLEINIT(0,0,0,0,1,3,5,7,9,9,9,9);
	LIGHTLEVELLENGTH=12;
	LIGHTLEVELTIME=50;
}

void anim::LIGHTLEVELTABLEINIT(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12)
{
	LIGHTLEVELTABLE[0]=a1;
	LIGHTLEVELTABLE[1]=a2;
	LIGHTLEVELTABLE[2]=a3;
	LIGHTLEVELTABLE[3]=a4;
	LIGHTLEVELTABLE[4]=a5;
	LIGHTLEVELTABLE[5]=a6;
	LIGHTLEVELTABLE[6]=a7;
	LIGHTLEVELTABLE[7]=a8;
	LIGHTLEVELTABLE[8]=a9;
	LIGHTLEVELTABLE[9]=a10;
	LIGHTLEVELTABLE[10]=a11;
	LIGHTLEVELTABLE[11]=a12;
}

void anim::dinit()
{

}

anim::~anim()
{
	dinit();
}
anim::anim()
{
	init();
}


#endif