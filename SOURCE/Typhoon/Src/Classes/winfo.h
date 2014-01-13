//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _WINFO_H
#define _WINFO_H

class winfo
{
	//info for weps,enemy,armour,magic
public:

	//all npcs
	LinkedList<npcstore> NPCSTORE;
	npcstore * NPCSTOREPTR[100];
	
	LinkedList<objstore> OBJSTORE;
	objstore * OBJSTOREPTR[100];
	
	LinkedList<armstore> ARMSTORE;
	armstore * ARMSTOREPTR[100];
	
	LinkedList<wepstore> WEPSTORE;
	wepstore * WEPSTOREPTR[100];

	//for the players inventory of spells, the ordering is the ordering of splstore
	LinkedList<splstore> SPLSTORE;
	splstore * SPLSTOREPTR[100];

	LinkedList<mapstore> MAPSTORE;
	mapstore * MAPSTOREPTR[100];
		
	//load tags of type type, from file path
	bool loadnpcs(xml * xmlclass);
	bool loadobjects(xml * xmlclass);
	bool loadarmour(xml * xmlclass);
	bool loadweapons(xml * xmlclass);
	bool loadspells(xml * xmlclass);
	bool loadmaps(xml * xmlclass);

	
	bool loadpresetnpcs(xml * xmlclass);
	bool loadpresetitems(xml * xmlclass);
	bool loadpresetexits(xml * xmlclass);
	bool loadpresetscripts(xml * xmlclass);

	bool loaddungeonassist(xml * xmlclass);

	char signtext[100][200];
	char npctext[51][500];
	char talknpcbuffer[500];
	char talkingcharacterbuffer[51][100];
	char talkingcharacterbuffer2[100];
	char talkingcharacterpicture[100];
	int foodtable[5][2];
	int firstMapId;
	int costofobject(int value);
	
	void init();
	void dinit();
	winfo();
	~winfo();
};

winfo INFOS;

#endif