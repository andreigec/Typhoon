//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _EQU_CPP
#define _EQU_CPP

char* EQU::savevals(char * objtype)
{
	char temp[100];temp[0]=0;
	sprintf(temp," %s %d %d %d %d %d %d",objtype,HELM.id,CHEST.id,LEGS.id,SHOES.id,LARM.id,RARM.id);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void EQU::loadvals(FILE * fileptr)
{
	//helm,chest,legs,shoes,larm,rarm
	int hid,cid,lid,sid,larmid,rarmid;
	hid=cid=lid=sid=larmid=rarmid=0;

	fscanf_s(fileptr,"%d %d %d %d %d %d",&hid,&cid,&lid,&sid,&larmid,&rarmid);
	int nid=0;

	if (hid!=0)
	{
		nid=hid;
		while (nid>=100)
			nid-=100;
		EQUIPMENT.HELM=INFOS.ARMSTOREPTR[nid];
	}

	if (cid!=0)
	{
		nid=cid;
		while (nid>=100)
			nid-=100;
		EQUIPMENT.CHEST=INFOS.ARMSTOREPTR[nid];
	}

	if (lid!=0)
	{
		nid=lid;
		while (nid>=100)
			nid-=100;
		EQUIPMENT.LEGS=INFOS.ARMSTOREPTR[nid];
	}

	if (sid!=0)
	{
		nid=sid;
		while (nid>=100)
			nid-=100;
		EQUIPMENT.SHOES=INFOS.ARMSTOREPTR[nid];
	}

	if (rarmid!=0)
	{
		nid=rarmid;
		while (nid>=100)
			nid-=100;
		EQUIPMENT.RARM=INFOS.WEPSTOREPTR[nid];
	}

	if (larmid!=0)
	{
		nid=larmid;
		while (nid>=100)
			nid-=100;
		EQUIPMENT.LARM=INFOS.WEPSTOREPTR[nid];
	}

}

void EQU::init()
{
	EQUIPMENT.HELM.init();
	EQUIPMENT.CHEST.init();
	EQUIPMENT.LEGS.init();
	EQUIPMENT.SHOES.init();
	EQUIPMENT.LARM.init();
	EQUIPMENT.RARM.init();	
}
EQU::EQU()
{
	init();
}

EQU::~EQU()
{
/*
 HELM.dinit();
 CHEST.dinit();
 LEGS.dnit();
 SHOES.dinit();
 LARM.dnit();
 RARM.dnit();
 */
}

#endif