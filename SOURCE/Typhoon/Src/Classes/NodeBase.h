//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NODEBASE_H
#define _NODEBASE_H

class NodeBase abstract
{
public:
	void initnb();
	NodeBase();
	void dinitnb();
	~NodeBase();

	//TYPES
	//0=no image item
	//1-8=fired spell
	//678
	//4 5
	//123
	//9-99=misc ground items
	//100-199=enemies
	//200-299=weapons
	//300-399=items
	//400-449=ranged spells
	//400-420=initial cost
	//421-430=5 per square
	//431-449=20 per square
	//450-499=ground spells
	//500-599=armour
	//---------------
	//global id of item
	int id;

	//the type of the object
	//0=invalid
	//1-99=object
	//1=object
	//2=gold
	//3=food
	//4=health potion
	//5=magic potion
	//6=stamina potion
	//7=full potion
	//100-199=weapon
	//100=weapon
	//101=fists
	//200-299=armour
	//200=helmet
	//201=chest armour
	//202=leg armour
	//203=shoes
	//300-399=npc
	//300=NPC
	//301=torch
	//302=sign
	//303=ranged npc
	//400-499=spell
	//400=spell
	//500-599=map
	//500=map
	int type;

	//npcs name
	char *str;

	//path to npcs pic
	char *pic;

	//x position
	int xpos;

	//y position
	int ypos;
};

#endif