//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PLAY2_CPP
#define _PLAY2_CPP

char * PLAY2::savevals(char * objtype)
{
	char temp[100];temp[0]=0;

			sprintf(temp," %s %d %d %d %d %d %d %d %d %d",objtype,\
		strength,luck,canswim,survival,dexterity,agility,constitution,intelligence,skillpoints);

	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void PLAY2::loadvals(FILE * fileptr)
{
	fscanf_s(fileptr,"%d %d %d %d %d %d %d %d %d",\
	&strength,&luck,&canswim,&survival,&dexterity,&agility,&constitution,&intelligence,&skillpoints);
	}




void PLAY2::init()
{
	strength=1;
	luck=5;
	canswim=true;
	survival=1;
	maxsurvival=2;
	dexterity=1;
	agility=1;
	intelligence=1;
	constitution=5;
	skillpoints=3;
}
PLAY2::~PLAY2()
{
	skillpoints=0;
}

PLAY2::PLAY2()
{
	init();
}


#endif