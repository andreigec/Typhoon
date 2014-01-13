//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PLAY_CPP
#define _PLAY_CPP

void PLAY::levelup()
{
	while (PLAYER.exp>=PLAYER.maxexp)
		{
			PLAYERSTATS.skillpoints+=HCVARS.PLAYERSKILLPOINTGAIN;
			PLAYER.exp-=PLAYER.maxexp;
			PLAYER.level++;
				PLAYERSTATS.luck++;
			PLAYER.maxexp=(PLAYER.level*HCVARS.PLAYEREXPPERLEVEL);
			//playsound
				EXEC.loadSound(SND.levelup);

			CONSOLE.pushtext(false,2,TEXT_PLAYER_LEVEL);
		}
}

char * PLAY::savevals(char * objtype)
{
	char temp[300];temp[0]=0;

	sprintf(temp," %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",objtype,\
		posx,posy,gold,maxgold,food,maxfood,level,maxlevel,exp,maxexp,\
		health,maxhealth,air,maxair,stamina,maxstamina,magic,maxmagic,\
		viewdist);

	char temp2[200];temp2[0]=0;
	sprintf(temp2," %s %s %s %d %d %d %d %d %d",name,race,image,direction,regen,maxregen,lastx,lasty,dash);

	strcat(temp,temp2);

	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void PLAY::loadvals(FILE * fileptr)
{
	MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
	fscanf_s(fileptr,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",\
		&posx,&posy,&gold,&maxgold,&food,&maxfood,&level,&maxlevel,&exp,&maxexp,\
		&health,&maxhealth,&air,&maxair,&stamina,&maxstamina,&magic,&maxmagic,\
		&viewdist);

	fscanf_s(fileptr," %s %s %s %d %d %d %d %d %d",name,98,race,98,image,98,&direction,&regen,&maxregen,&lastx,&lasty,&dash);
}


//Checks for environmental effects on player
void PLAY::checkenv(void)
{
	int minusair=0;
	if (GLOBAL.loopswitch==LS_NORMAL)
	{
		if (MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]==TT_WATER)
		{
			PLAYER.dash=0;
			PLAYER.regen=0;
			minusair=1;
		}
		else if (MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]==TT_MARSH)
		{
			PLAYER.dash=0;
			PLAYER.regen=0;

			if (PLAYER.stamina>=HCVARS.marshstamdec)
			{
				PLAYER.stamina-=HCVARS.marshstamdec;
				CONSOLE.pushtext(false,1,TEXT_PLAYER_MARSH);
			}
			else if (PLAYER.stamina>0)
			{PLAYER.stamina=0;CONSOLE.pushtext(false,1,TEXT_PLAYER_MARSH);}
		}

		else if (MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]==TT_LAVA)
		{
			PLAYER.dash=0;
			PLAYER.regen=0;

			CONSOLE.pushtext(false,1,TEXT_PLAYER_LAVA);
			char temp[100];
			char temp2[20];
			strcpy(temp,"Player stepped in type Lava, x:");
			sprintf(temp2,"%d",PLAYER.posx);
			strcat(temp,temp2);
			strcat(temp," y:");
			sprintf(temp2,"%d",PLAYER.posy);
			strcat(temp,temp2);
			CONSOLE.pushtext(true,1,temp);
			PLAYER.health-=PLAYER.maxhealth/3;
		}
		else 
		{ 
			int mpregen=2;
			int hpregen=4;
			
			if (PLAYER.air<PLAYER.maxair)
			{
				if (PLAYER.regen!=0)
				{
					PLAYER.air++;
					if (PLAYER.air<=0)
						PLAYER.air=1;
				}
			}

			if (PLAYER.air>PLAYER.maxair&&MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]!=TT_WATER)
				PLAYER.air--;


			if ((PLAYER.stamina<PLAYER.maxstamina)&&PLAYER.dash==0)
			{
				if (PLAYER.regen!=0)
					PLAYER.stamina++;
			}

			if (PLAYER.stamina>PLAYER.maxstamina)
						PLAYER.stamina--;

			if (PLAYER.magic<PLAYER.maxmagic)
			{
				if (PLAYER.regen%mpregen==0&&PLAYER.regen!=0)
					PLAYER.magic++;
			}

			if (PLAYER.health<PLAYER.maxhealth)
			{
				if (PLAYER.regen%hpregen==0&&PLAYER.regen!=0)
					PLAYER.health++;
			}
		}

		if (PLAYER.air<=0)
		{
			CONSOLE.pushtext(false,1,TEXT_PLAYER_DROWN);
			PLAYER.health-=PLAYER.maxhealth/5;
			char temp[100];
			char temp2[20];
			strcpy(temp,"Player 1 drowning, x:");
			sprintf(temp2,"%d",PLAYER.posx);
			strcat(temp,temp2);
			strcat(temp," y:");
			sprintf(temp2,"%d",PLAYER.posy);
			strcat(temp,temp2);
			CONSOLE.pushtext(true,1,temp);
			PLAYER.dash=0;
			PLAYER.regen=0;
		} 

		if (PLAYER.health<=0)
		{
			CONSOLE.pushtext(true,0,"die3");//died
			EXEC.loadSound(SND.death4);

			EXEC.playerdeath();
		}

		//minus air after check
		if (minusair==1)
		{
			if (PLAYER.air>=1)
			{PLAYER.air--;}
		}
	}
	//loop regen
	if (PLAYER.regen>=PLAYER.maxregen||PLAYER.dash==1)
		PLAYER.regen=1;
	else
		PLAYER.regen++;

	if (GLOBAL.loopswitch==LS_NORMAL)
	{EXEC.npcmain();}
}

void PLAY::init()
{
	direction=5;
	regen=0;
	maxregen=4;
	health=PLAYERSTATS.constitution*10;
	maxhealth=PLAYERSTATS.constitution*10;
	air=ceil((float)PLAYERSTATS.constitution/10);
	maxair=ceil((float)PLAYERSTATS.constitution/10);
	posx=0;
	posy=0;
	lastx=0;
	lasty=0;
	dash=0;
	stamina=PLAYERSTATS.constitution;
	maxstamina=PLAYERSTATS.constitution;
	strcpy(name,"Default");
	strcpy(race,"Proletariat");
	strcpy(image,"Data/Images/Tiles/man.tga");
	gold=HCVARS.STARTGOLD;
	maxgold=1000000;
	food=HCVARS.STARTFOOD;
	maxfood=10000;
	magic=1;
	maxmagic=1;
	level=1;
	maxlevel=100;
	exp=0;
	maxexp=HCVARS.PLAYEREXPPERLEVEL;
	lockmove=false;
	viewdist=3;
	for (int a=0;a<100;a++)
		hasSpellTable[a]=false;
}
PLAY::PLAY()
{
	init();
}
PLAY::~PLAY()
{
	//exp=0;
}

#endif