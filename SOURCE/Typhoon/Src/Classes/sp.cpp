//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SP_CPP
#define _SP_CPP

char* SP::savevals(char * objtype)
{
	char temp[100];temp[0]=0;
	sprintf(temp," %s %d",objtype,type);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void SP::loadvals(FILE * fileptr)
{
	fscanf_s(fileptr,"%d",&type);
	EXEC.loadspell(SPELL.type,-1,PLAYER.posy,PLAYER.posx,-1);
}


void SP::init()
{
	active=0;
	basedamage=0;
	mp=0;
	strcpy(image,"");
	strcpy(name,"");
	type=0;
}
SP::SP()
{
	init();
}
SP::~SP()
{
	mp=0;
}

#endif