//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NODEENEMY_CPP
#define _NODEENEMY_CPP

void NodeEnemy::copy(NodeEnemy * copyfrom)
{
	enemyhealth=copyfrom->enemyhealth;
	enemymaxhealth=copyfrom->enemymaxhealth;
	attackbase=copyfrom->attackbase;
	defensebase=copyfrom->defensebase;
	viewdist=copyfrom->viewdist;
	canswim=copyfrom->canswim;
	faction=copyfrom->faction;
	id=copyfrom->id;

	str=strdup(copyfrom->str);
	pic=strdup(copyfrom->pic);
	xpos=copyfrom->xpos;
	ypos=copyfrom->ypos;

	talktype=copyfrom->talktype;
	movetype=copyfrom->movetype;
}


void NodeEnemy::loadenemy(FILE * fileptr,bool setlocation)
{
	int newtype=0;
	int newtalktype=0;
	int newmovetype=0;
	int x=0;
	int y=0;
	int newhp=0;
	int newfaction=0;
	fscanf_s(fileptr,"%d %d %d %d %d %d %d",&newtype,&newtalktype,&newmovetype,&x,&y,&newhp,&newfaction);
	setvalues(newtype,x,y,setlocation);
	talktype=newtalktype;
	movetype=newmovetype;
	enemyhealth=newhp;
	faction=newfaction;
}


char* NodeEnemy::saveenemy(char * objtype)
{
	char temp[100];temp[0]=0;
	sprintf(temp," %s %d %d %d %d %d %d %d",objtype,id,talktype,movetype,xpos,ypos,enemyhealth,faction);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);

	return out;
}

float NodeEnemy::returnbaramount()
{
	if (enemymaxhealth==-1)
		return -1;
	return (((float)enemyhealth/(float)enemymaxhealth));
}

NodeEnemy::~NodeEnemy()
{
	dinitne();
}

NodeEnemy::NodeEnemy()
{
	initne();
}

void NodeEnemy::dinitne()
{
	movelisthead.clear();
}


void NodeEnemy::initne()
{
	talktype=-1;
	movetype=0;
	faction=NT_NEUTRAL;
	enemyhealth=0;
	enemymaxhealth=0;
	attackbase=0;
	defensebase=0;
	canswim=false;
	viewdist=0;
}



void NodeEnemy::initposarray(pathhead * pathptr)
{
	pathptr->clearall();

}

//set information about enemy from databases, set enemy to mapfile
bool NodeEnemy::setvalues(int newid,int x, int y,bool setlocation)
{
	if (newid>=100&&newid<200)
	{
		id=newid;
		//ENEMY DATA INPUT
		if (INFOS.NPCSTOREPTR[id-100]!=NULL)
		{	
			npcstore * npcptr=INFOS.NPCSTOREPTR[id-100];

			type=npcptr->type;
			mystrdup(&str,npcptr->name);
			mystrdup(&pic,npcptr->path);
			attackbase=npcptr->attackbase;
			defensebase=npcptr->defensebase;
			enemyhealth=npcptr->hp;
			enemymaxhealth=npcptr->hp;
			faction=npcptr->faction;
			canswim=npcptr->canswim;

			//set torch light range hardcode!,fix
			if (type==T_TORCH)
				viewdist=3;
			else
				viewdist=20;

			if (x==-1&&y==-1)
				getenemyrandompos();
			else
			{xpos=x;ypos=y;}
			if (setlocation)
				MAPFILES.MAPFILEENEMY[ypos][xpos]=this;
		}
		else
		{printf("\n Enemy not found in ll,%d",id-100);return true;}

	}
	return false;
}

bool NodeEnemy::isMoveListCorrupted()
{
	LinkedListNode<movelist> * newptr=movelisthead.headptr;
	while (newptr!=NULL)
	{
		if (MAPFILES.passable(newptr->value->y,newptr->value->x,this)==false)
		{
			return true;
		}
		newptr=newptr->nextptr;
	}	
	return false;
}

void NodeEnemy::deletelastmovelist()
{
	//no moves,warning
	if (movelisthead.getCount()==0)
	{
		printf("\nWARNING! movelist is empty!");
		return;
	}

	//next move
	LinkedListNode<movelist> * temp=movelisthead.tailptr;

	//no adjacent,error,init
	if (EXEC.isnear(xpos,ypos,temp->value->x,temp->value->y)==false)
	{
		CONSOLE.pushtext(true,0,"AI-Not Adjacent Error!");
		//initposarray(movies);
		movelisthead.clear();
		return;
	}

	//cannot move to,error,init
	if (MAPFILES.passable(temp->value->y,temp->value->x,this)==false)
	{
		CONSOLE.pushtext(true,0,"AI-Cannot move to tile, not passable Error!");

		movelisthead.clear();
		//initposarray(movies);
		return;
	}

	//if the tile is a door, open it first
	if (MAPFILES.MAPFILE[temp->value->y][temp->value->x]==TT_DOOR)
	{
		EXEC.loadSound(SND.opensound);
		MAPFILES.MAPFILE[temp->value->y][temp->value->x]=TT_ODOOR;
	}

	MAPFILES.MAPFILEENEMY[ypos][xpos]=NULL;
	ypos=temp->value->y;xpos=temp->value->x;	
	MAPFILES.MAPFILEENEMY[ypos][xpos]=this;
	//clear out the temporary data for calculating the path, as other npcs will need it.	
	//initposarray(movies);
	//remove last element
	movelisthead.deleteNode(temp);
}

void NodeEnemy::getenemyrandompos()
{
	int xmin=0,xmax=0,ymin=0,ymax=0;
	int direction=0;
	int a;
	int totaltries=0;
	int xx=0,yy=0;
REDOES:			
	direction=rand()%5;
	//printf("\ndirection=%d",direction);
	if (direction<=0)direction=1;
	//1,2,3,4 //down up left right
	xx=0;yy=0;a=0;
REDOEZ:
	if (totaltries>=20)
	{
		printf("\nWARNING-Get enemy random position has failed multiple times");
		return;
	}
	totaltries++;
	if (direction==1)
	{xmin=PLAYER.posx-10,xmax=PLAYER.posx+10,ymin=PLAYER.posy+6,ymax=PLAYER.posy+12;}
	else if (direction==2)
	{xmin=PLAYER.posx-10,xmax=PLAYER.posx+10,ymin=PLAYER.posy-12,ymax=ymin=PLAYER.posy-6;}
	else if (direction==3&&PLAYER.posx>=16)
	{xmin=PLAYER.posx-16,xmax=PLAYER.posx-10,ymin=PLAYER.posy-12,ymax=ymin=PLAYER.posy+12;}
	else if (direction==4&&(PLAYER.posx<MAPFILES.emapwidth()-16))
	{xmin=PLAYER.posx+10,xmax=PLAYER.posx+16,ymin=PLAYER.posy-12,ymax=ymin=PLAYER.posy+12;}
	else
	{direction++;if (direction>=5)direction=1;goto REDOEZ;}
	if (xmax>=MAPFILES.emapwidth())
		xmax=MAPFILES.emapwidth()-1;
	else if (xmax<0)
		xmax=0;
	if (ymax>=MAPFILES.emapheight())
		ymax=MAPFILES.emapheight()-1;
	else if (ymax<0)
		ymax=0;

	if (xmin>=MAPFILES.emapwidth())
		xmin=MAPFILES.emapwidth()-1;
	else if (xmin<0)
		xmin=0;
	if (ymin>=MAPFILES.emapheight())
		ymin=MAPFILES.emapheight()-1;
	else if (ymin<0)
		ymin=0;

	a=0;	
	while (a<50)
	{		
		xpos=xmin;
		if (xmax!=xmin)xpos+=(rand()%(xmax-xmin));
		if (xpos>=xmin&&xpos<=xmax)
			break;
		a++;
	}
	a=0;
	while (a<50)
	{		
		ypos=ymin;
		if (ymax!=ymin)ypos+=(rand()%(ymax-ymin));
		if (ypos>=ymin&&ypos<=ymax)
			break;
		a++;
	}

	if (MAPFILES.passable2(ypos,xpos,this,true)==false)
		goto REDOES;


	if (MAPFILES.MAPFILEENEMY[ypos][xpos]==NULL)
		MAPFILES.MAPFILEENEMY[ypos][xpos]=this;
	else
	{CONSOLE.pushtext(true,0,"Error in creation");}
}

bool NodeEnemy::enemymoveplayer(NodeEnemy * attacker2)
{
	if (GLOBAL.loopswitch!=LS_NORMAL||attacker2==NULL)
		return true;

	if (EXEC.isnear(attacker2->xpos,attacker2->ypos,PLAYER.posx,PLAYER.posy))
	{
		if (MAPFILES.MAPFILE[attacker2->ypos][attacker2->xpos]==TT_LAVA)
			CONSOLE.pushtext(true,0,"moving enemy out of lava");
		else
		{
			if (GLOBAL.debugenabled==true)
			{printf("\nSkipping");printf("\nex=%d,ey=%d,px=%d,py=%d",attacker2->xpos,attacker2->ypos,PLAYER.posx,PLAYER.posy);}

			//before attacker2, check faction
			if (GLOBAL.loopswitch==LS_NORMAL&&attacker2->faction==NT_HOSTILE)
			{
				if (attacker2->attackplayerfunction()==false)
					return false;
				goto skipenemy;
			}
		}
		if (\
			(PLAYER.posx>=(attacker2->xpos+attacker2->viewdist))||\
			(PLAYER.posx<=(attacker2->xpos-attacker2->viewdist))||\
			(PLAYER.posy>=(attacker2->ypos+attacker2->viewdist))||\
			(PLAYER.posy<=(attacker2->ypos-attacker2->viewdist)))
		{EXEC.randomnpc(attacker2);}
	}
	else
	{
		//magic users
		if ((attacker2->type==T_RNPC&&(SPELL2.active==0&&SPELL.active==0))&&GLOBAL.loopswitch==LS_NORMAL&&attacker2->faction==NT_HOSTILE)
		{
			int random=rand()%100;
			int location=abs(abs(attacker2->ypos-PLAYER.posy)-abs(attacker2->xpos-PLAYER.posx));
			int spell=0;
			spell=rand()%4;
			spell+=400;
			if (random<=40)
			{
				if (attacker2->ypos==PLAYER.posy&&attacker2->xpos<PLAYER.posx)
				{EXEC.loadspell(spell,6,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}
				else if (attacker2->ypos<PLAYER.posy&&attacker2->xpos==PLAYER.posx)
				{EXEC.loadspell(spell,2,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}
				else if (attacker2->ypos==PLAYER.posy&&attacker2->xpos>PLAYER.posx)
				{EXEC.loadspell(spell,4,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}
				else if (attacker2->ypos>PLAYER.posy&&attacker2->xpos==PLAYER.posx)
				{EXEC.loadspell(spell,8,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}
				else if (attacker2->ypos<PLAYER.posy&&attacker2->xpos<PLAYER.posx&&location==0)
				{EXEC.loadspell(400,3,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}

				else if (attacker2->ypos<PLAYER.posy&&attacker2->xpos>PLAYER.posx&&location==0)
				{EXEC.loadspell(400,1,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}

				else if (attacker2->ypos>PLAYER.posy&&attacker2->xpos<PLAYER.posx&&location==0)
				{EXEC.loadspell(400,9,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}

				else if (attacker2->ypos>PLAYER.posy&&attacker2->xpos>PLAYER.posx&&location==0)
				{EXEC.loadspell(400,7,attacker2->ypos,attacker2->xpos,0);glutPostRedisplay();return true;}
			}
		}


		///////

		//create a dummy enemy just to move towards if attacking player
		NodeEnemy * newenemy=new NodeEnemy;
		newenemy->xpos=PLAYER.posx;
		newenemy->ypos=PLAYER.posy;

		EXEC.moveenemy(attacker2,newenemy);
		delete newenemy;
	}

skipenemy:
	;
	return true;	
}



//Checks for environmental effects on enemy
int NodeEnemy::checkenvenemy(NodeEnemy * target)
{
	if (MAPFILES.MAPFILEENEMY[ypos][xpos]==NULL)
		return 0;
	if (enemyhealth<=0)
		return 0;
	if (MAPFILES.MAPFILE[ypos][xpos]==TT_LAVA)
		enemyhealth-=10;
	else if (MAPFILES.MAPFILE[ypos][xpos]==TT_WATER&&canswim==false)
		enemyhealth-=10;
	if (enemyhealth<=0)
	{
		//playsound
		EXEC.loadSound(SND.death1);

		CONSOLE.pushtext(false,0,TEXT_ENVDEAD);
		MAPFILES.MAPFILEENEMY[ypos][xpos]=NULL;
		NPC.deleteNode(target);
		return 1;
	}
	return 0;
}



bool NodeEnemy::attackplayerfunction()
{
	if (MAPFILES.MAPFILEENEMY[ypos][xpos]==NULL)
		MAPFILES.MAPFILEENEMY[ypos][xpos]=this;

	int random;
	random=rand()%100;
	char string[300];
	char tempp[300];

	if (random<=(PLAYERSTATS.agility/2)+PLAYERSTATS.luck/4)
	{
		//playsound
		EXEC.loadSound(SND.misssound);

		strcpy(string,str);
		strcat(string," missed you");
		CONSOLE.pushtext(false,2,string);
		GLOBAL.loopswitch=LS_PASS;
		glutPostRedisplay();
		return true;
	}

	int basedamage;
	int result=0;

	basedamage=attackbase;
	basedamage-=basedamage*((.3*PLAYERSTATS.dexterity)/100);
	if (EQUIPMENT.HELM.id!=0)
		result+=INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->defensePercent;
	if (EQUIPMENT.CHEST.id!=0)
		result+=INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->defensePercent;
	if (EQUIPMENT.LEGS.id!=0)
		result+=INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->defensePercent;
	if (EQUIPMENT.SHOES.id!=0)
		result+=INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->defensePercent;

	basedamage-=basedamage*((.3*result)/100);
	if (GLOBAL.debugenabled==true)printf("\nBD=%d,AP=%d",basedamage,result);

	if (basedamage<=0)
		basedamage=0;
	//printf("\nHP=%d",foundenemy->enemyhealth);
	random=rand()%30;
	if (random<=14)
	{basedamage*=1-(random/50.0);}
	else if (random>=16)
	{random-=15;basedamage*=1+(random/50.0);}

	random=rand()%100;
	if (random<=5)
	{basedamage*=2;random=1;}
	else
		random=0;
	PLAYER.health-=basedamage;
	if (PLAYER.health<=0)
	{
		CONSOLE.pushtext(true,0,"die4");
		EXEC.loadSound(SND.death4);
		EXEC.playerdeath();
		return false;
	}//died

	else
	{
		if (random==1)
		{
			//playsound
			EXEC.loadSound(SND.criticalhit);
			CONSOLE.pushtext(false,1,TEXT_CRITICALHIT);
		}
		//playsound
		EXEC.loadSound(SND.ouchsound);

		strcpy(string,"Dealt");
		sprintf(tempp," %d ",basedamage);
		strcat(string,tempp);
		strcat(string,"damage from ");
		strcat(string,str);
		CONSOLE.pushtext(false,1,string);
		PLAYER.regen=0;
		return true;
	}
}

#endif