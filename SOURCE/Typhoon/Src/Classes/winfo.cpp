//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _WINFO_CPP
#define _WINFO_CPP

int winfo::costofobject(int value)
{
	int cost=value;
	cost-=PLAYERSTATS.luck;
	if (cost<=10)
		cost=20;
	return cost;		
}


void winfo::init()
{

	firstMapId=-1;
	for (int a=0;a<100;a++)
	{
		NPCSTOREPTR[a]=NULL;
		OBJSTOREPTR[a]=NULL;
		ARMSTOREPTR[a]=NULL;
		WEPSTOREPTR[a]=NULL;
		SPLSTOREPTR[a]=NULL;
	}

	NPCSTORE.clear();

	for (int a=0;a<51;a++)
	{
		strcpy(npctext[a],"");
		strcpy(talkingcharacterbuffer[a],"");
	}

	for (int a=0;a<200;a++)
	{
		strcpy(signtext[a],"");
	}

	strcpy(talknpcbuffer,"");
	strcpy(talkingcharacterbuffer2,"");
	strcpy(talkingcharacterpicture,"");

	foodtable[0][0]=100;foodtable[0][1]=40;
	foodtable[1][0]=200;foodtable[1][1]=90;
	foodtable[2][0]=500;foodtable[2][1]=240;
	foodtable[3][0]=1000;foodtable[3][1]=500;
	foodtable[4][0]=5000;foodtable[4][1]=2500;
}

void winfo::dinit()
{

}

winfo::winfo()
{
	init();
}

winfo::~winfo()
{
	dinit();
}

bool winfo::loadpresetscripts(xml * xmlclass)
{
	char pnpctag[]="Script";
	char conditiontag[]="condition";
	char effecttag[]="effect";

	xmlclass->getroot(pnpctag,true);

	MAPFILES.MAPFILESSCRIPTS.clear();

	char * temp = new char[100];temp[0]=0;

	while (xmlclass->root!="")
	{
		//make new script
		script * newptr=MAPFILES.MAPFILESSCRIPTS.insertNode();

		//keep adding conditions while they exist
		while (xmlclass->root.find(conditiontag)!=-1)
		{
			strcpy(temp,"");
			xmlclass->getstring(&temp,conditiontag);

			//extract the details of the new condition from the string
			newptr->extractCondition(temp);
		}

		//keep adding effects while they exist
		while (xmlclass->root.find(effecttag)!=-1)
		{
			strcpy(temp,"");
			xmlclass->getstring(&temp,effecttag);

			//extract the details of the new effect from the string
			newptr->extractEffect(temp);
		}

		xmlclass->getroot(pnpctag,true);
	}
	return true;
}

//specialty class for loading dungeon assist xml files with 'DungeonAssist' tag
bool winfo::loaddungeonassist(xml * xmlclass)
{
	DUNGEON.init();
	char pnpctag[]="DungeonAssist";
	xmlclass->getroot(pnpctag,true);

	while (xmlclass->root!="")
	{
		DUNGEON.lastlevel=xmlclass->getinteger("numberOfGeneratedLevels");

		DUNGEON.mapsize =xmlclass->getinteger("dungeonMapSize");

		DUNGEON.isdungeon=xmlclass->getboolean("isDungeon");

		DUNGEON.maptype=xmlclass->getinteger("mapType");

		DUNGEON.firstlevelmapid=xmlclass->getinteger("entranceMapId");

		DUNGEON.lastlevelmapid=xmlclass->getinteger("lastMapId");

		xmlclass->getroot(pnpctag,true);
	}
	return true;

}


//specialty class for loading maps from xml document with 'MAP' tag
bool winfo::loadmaps(xml * xmlclass)
{
	//have to get rid of the current map
	MAPFILES.dinit(false,true);
	MAPSTORE.clear();
	for (int a=0;a<100;a++)
		MAPSTOREPTR[a]=NULL;

	//get the map id first
	xmlclass->root=xmlclass->file;
	int val=xmlclass->getinteger("firstMapId");
	INFOS.firstMapId=val;

	char enemytag[]="MAP";
	xmlclass->getroot(enemytag,true);

	while (xmlclass->root!="")
	{	
		mapstore * newptr=MAPSTORE.insertNode();

		xmlclass->getstring(&newptr->name,"name");

		xmlclass->getstring(&newptr->path,"path");

		newptr->id=xmlclass->getinteger("id");

		newptr->type=xmlclass->getinteger("type");

		newptr->startX=xmlclass->getinteger("startX");

		newptr->startY=xmlclass->getinteger("startY");

		newptr->enemyCreationRate=xmlclass->getinteger("enemyCreationRate");

		newptr->minEnemyLevel=xmlclass->getinteger("minEnemyLevel");

		newptr->darknessLevel=xmlclass->getinteger("darknessLevel");

		xmlclass->getstring(&newptr->PresetNpcFile,"PresetNpcFile");

		xmlclass->getstring(&newptr->PresetItemFile,"PresetItemFile");

		xmlclass->getstring(&newptr->PresetExitFile,"PresetExitFile");

		xmlclass->getstring(&newptr->PresetScriptFile,"PresetScriptFile");

		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (MAPSTOREPTR[nid]!=NULL)
		{
			printf("\nWARNING! overloading map with id:%d",nid);
		}
		MAPSTOREPTR[nid]=newptr;	

		xmlclass->getroot(enemytag,true);
	}
	return true;
}


//specialty class for loading preset npcs from map files with 'PresetNPC' tag
bool winfo::loadpresetnpcs(xml * xmlclass)
{
	char pnpctag[]="PresetNPC";
	xmlclass->getroot(pnpctag,true);
	while (xmlclass->root!="")
	{
		NodeEnemy * newptr=NPC.insertNode();

		newptr->id=xmlclass->getinteger("id");

		newptr->xpos=xmlclass->getinteger("xpos");

		newptr->ypos=xmlclass->getinteger("ypos");

		newptr->movetype=xmlclass->getinteger("movetype");

		newptr->talktype=xmlclass->getinteger("talktype");

		newptr->faction=xmlclass->getinteger("faction");

		newptr->setvalues(newptr->id,newptr->xpos,newptr->ypos,true);

		xmlclass->getroot(pnpctag,true);
	}
	return true;
}

//specialty class for loading preset exits from map files with 'MapExit' tag
bool winfo::loadpresetexits(xml * xmlclass)
{
	char pnpctag[]="MapExit";
	xmlclass->getroot(pnpctag,true);
	MAPFILES.exitpoints.clear();

	while (xmlclass->root!="")
	{
		exitpoint * newptr=MAPFILES.exitpoints.insertNode();

		newptr->id=xmlclass->getinteger("id");

		newptr->xpos=xmlclass->getinteger("xpos");

		newptr->ypos=xmlclass->getinteger("ypos");

		newptr->ispop=xmlclass->getboolean("ispop");

		newptr->forceType=xmlclass->getinteger("forceType");

		newptr->changeX=xmlclass->getinteger("changeX");

		newptr->changeY=xmlclass->getinteger("changeY");

		xmlclass->getroot(pnpctag,true);
	}
	return true;
}


//specialty class for loading preset items from map files with 'PresetItem' tag
bool winfo::loadpresetitems(xml * xmlclass)
{
	char pitem[]="PresetItem";
	xmlclass->getroot(pitem,true);
	while (xmlclass->root!="")
	{
		NodeObject * newptr=grounditems.insertNode();

		newptr->id=xmlclass->getinteger("id");

		newptr->xpos=xmlclass->getinteger("xpos");

		newptr->ypos=xmlclass->getinteger("ypos");

		newptr->amount=xmlclass->getinteger("amount");

		newptr->setvalues(newptr->amount,newptr->id,newptr->xpos,newptr->ypos);

		xmlclass->getroot(pitem,true);
	}
	return true;
}


//specialty class for loading objects from xml document with 'OBJ' tag
bool winfo::loadobjects(xml * xmlclass)
{
	OBJSTORE.clear();
	for (int a=0;a<100;a++)
		OBJSTOREPTR[a]=NULL;

	char objtag[]="OBJ";
	xmlclass->getroot(objtag,true);
	while (xmlclass->root!="")
	{
		objstore * newptr=OBJSTORE.insertNode();

		newptr->id=xmlclass->getinteger("id");

		newptr->type=xmlclass->getinteger("type");

		newptr->cost=xmlclass->getinteger("cost");

		xmlclass->getstring(&newptr->name,"name");

		xmlclass->getstring(&newptr->path,"path");

		newptr->questitem=xmlclass->getboolean("questitem");

		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (OBJSTOREPTR[nid]!=NULL)
		{
			printf("\nWARNING! overloading obj with id:%d",nid);
		}
		OBJSTOREPTR[nid]=newptr;	

		xmlclass->getroot(objtag,true);
	}
	return true;
}


//specialty class for loading spells from xml document with 'SPL' tag
bool winfo::loadspells(xml * xmlclass)
{
	SPLSTORE.clear();
	for (int a=0;a<100;a++)
		SPLSTOREPTR[a]=NULL;

	char enemytag[]="SPL";
	xmlclass->getroot(enemytag,true);
	while (xmlclass->root!="")
	{	
		splstore * newptr=SPLSTORE.insertNode();
		newptr->id=xmlclass->getinteger("id");

		newptr->type=xmlclass->getinteger("type");

		xmlclass->getstring(&newptr->name,"name");

		newptr->cost=xmlclass->getinteger("cost");

		newptr->mp=xmlclass->getinteger("mp");

		newptr->basedamage=xmlclass->getinteger("basedamage");		

		xmlclass->getstring(&newptr->path,"path");

		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (SPLSTOREPTR[nid]!=NULL)
		{
			printf("\nWARNING! overloading spl with id:%d",nid);
		}
		SPLSTOREPTR[nid]=newptr;	

		xmlclass->getroot(enemytag,true);
	}
	return true;
}



//specialty class for loading weapons from xml document with 'WEP' tag
bool winfo::loadweapons(xml * xmlclass)
{
	WEPSTORE.clear();
	for (int a=0;a<100;a++)
		WEPSTOREPTR[a]=NULL;

	char enemytag[]="WEP";
	xmlclass->getroot(enemytag,true);
	while (xmlclass->root!="")
	{
		wepstore * newptr=WEPSTORE.insertNode();

		newptr->id=xmlclass->getinteger("id");

		newptr->type=xmlclass->getinteger("type");

		xmlclass->getstring(&newptr->name,"name");

		newptr->cost=xmlclass->getinteger("cost");

		newptr->damage=xmlclass->getinteger("damage");

		newptr->strengthReq=xmlclass->getinteger("strengthReq");

		newptr->oneHanded=xmlclass->getboolean("oneHanded");

		xmlclass->getstring(&newptr->path,"path");

		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (WEPSTOREPTR[nid]!=NULL)
		{
			printf("\nWARNING! overloading wep with id:%d",nid);
		}
		WEPSTOREPTR[nid]=newptr;	

		xmlclass->getroot(enemytag,true);
	}
	return true;
}




//specialty class for loading armour objects from xml document with 'ARM' tag
bool winfo::loadarmour(xml * xmlclass)
{
	ARMSTORE.clear();
	for (int a=0;a<100;a++)
		ARMSTOREPTR[a]=NULL;

	char enemytag[]="ARM";
	xmlclass->getroot(enemytag,true);
	while (xmlclass->root!="")
	{
		armstore * newptr=ARMSTORE.insertNode();
		newptr->id=xmlclass->getinteger("id");

		newptr->type=xmlclass->getinteger("type");

		xmlclass->getstring(&newptr->name,"name");

		newptr->cost=xmlclass->getinteger("cost");

		newptr->defensePercent=xmlclass->getinteger("defensePercent");

		xmlclass->getstring(&newptr->path,"path");

		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (ARMSTOREPTR[nid]!=NULL)
		{
			printf("\nWARNING! overloading arm with id:%d",nid);
		}
		ARMSTOREPTR[nid]=newptr;	

		xmlclass->getroot(enemytag,true);
	}
	return true;
}


//specialty class for loading objects from xml document with 'NPC' tag
bool winfo::loadnpcs(xml * xmlclass)
{
	NPCSTORE.clear();
	for (int a=0;a<100;a++)
		NPCSTOREPTR[a]=NULL;

	char enemytag[]="NPC";
	xmlclass->getroot(enemytag,true);
	while (xmlclass->root!="")
	{
		npcstore * newptr=NPCSTORE.insertNode();

		newptr->id=xmlclass->getinteger("id");

		newptr->type=xmlclass->getinteger("type");

		newptr->level=xmlclass->getinteger("level");

		xmlclass->getstring(&newptr->name,"name");

		newptr->attackbase=xmlclass->getinteger("attackbase");

		newptr->defensebase=xmlclass->getinteger("defensebase");

		newptr->hp=xmlclass->getinteger("hp");

		newptr->exp=xmlclass->getinteger("exp");

		newptr->faction=xmlclass->getinteger("faction");

		xmlclass->getstring(&newptr->path,"path");

		newptr->canswim=xmlclass->getboolean("canswim");

		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (NPCSTOREPTR[nid]!=NULL)
		{
			printf("\nWARNING! overloading npc with id:%d",nid);
		}
		NPCSTOREPTR[nid]=newptr;	
		xmlclass->getroot(enemytag,true);
	}
	return true;
}

#endif