//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NODEENEMY_H
#define _NODEENEMY_H

class NodeEnemy:public NodeBase
{
public:
	void initposarray(pathhead * pathptr);
	void dinitne();
	float returnbaramount();
	void getenemyrandompos();
	bool setvalues(int newid,int x, int y,bool setlocation);

	void copy(NodeEnemy * copyfrom);

	//false if player is killed
	bool attackplayerfunction();
	bool enemymoveplayer(NodeEnemy * attacker2);

	int checkenvenemy(NodeEnemy * target);
	~NodeEnemy();	
	NodeEnemy();
	void initne();

	int enemyhealth;
	int enemymaxhealth;
	int attackbase;
	int defensebase;
	int viewdist; //enemy only
	bool canswim;
	
	//1=enemy 2=NT_NEUTRAL 3=NT_FRIENDLY
	int faction;
	
	//<100 is linked to file,-1=cant talk
	//100+ are hard coded shops
	//100=weapons
	//101=magic
	//102=inn
	//103=grocer
	//104=casino
	//105=potion
	int talktype;

	//0=static, 1=randommove, 2=followplayer
	//movetype only affects NT_NEUTRAL, NT_HOSTILE and NT_FRIENDLY npcs disregard it
	int movetype;

	//movelist for hax;
	LinkedList<movelist> movelisthead;
	bool isMoveListCorrupted();
	
	//movelistheadbase *movelisthead;
	void deletelastmovelist();
	char * saveenemy(char * objtype);
	void loadenemy(FILE * fileptr,bool setlocation);
};

#endif