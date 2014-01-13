//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MP_CPP
#define _MP_CPP

void MP::executeScriptEffects(effectObj * eptr)
{
	if (eptr==NULL)
		return;

	if (scriptCommands[eptr->effectName]==NULL)
	{
		printf("\nERROR-%s doesnt exist",eptr->effectName);
		return;
	}

	int scriptnum=*scriptCommands[eptr->effectName];

	//below are HARD CODED, DO NOT CHANGE unless also changing exe.cpp -> initvars

	switch(scriptnum)
	{
		//unlock-player
	case 1:
		{
			if (eptr->intList.getCount()!=0)
			{
				printf("\nSCRIPT ERROR-unlock-player has invalid number of parameters");
				return;
			}

			PLAYER.lockmove=0;
			break;
		}

		//lock-player
	case 2:
		{
			if (eptr->intList.getCount()!=0)
			{
				printf("\nSCRIPT ERROR-lock-player has invalid number of parameters");
				return;
			}

			PLAYER.lockmove=1;
			break;
		}

		//move-player-relative
	case 3:
		{
			if (eptr->intList.getCount()!=2||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR-movep has invalid number/type of parameters");
				return;
			}

			int endx=PLAYER.posx+*eptr->intList.headptr->value;
			int endy=PLAYER.posy+*eptr->intList.headptr->nextptr->value;

			if (endx<0||endy<0||endx>=MAPFILES.emapwidth()||endy>=MAPFILES.emapheight())
			{
				printf("\nSCRIPT ERROR- move-player-relative has bad parameters (move player outside array)");
				return;
			}

			MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
			PLAYER.posx=endx;
			PLAYER.posy=endy;
			MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;

			break;
		}

		//move-npc-absolute
	case 4:
		{
			if (eptr->intList.getCount()!=4|eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR-moven has invalid number/type of parameters");
				return;
			}

			int initialx=*eptr->intList.headptr->value;
			int initialy=*eptr->intList.headptr->nextptr->value;

			int endx=*eptr->intList.headptr->nextptr->nextptr->value;
			int endy=*eptr->intList.headptr->nextptr->nextptr->nextptr->value;

			if (initialx<0||initialy<0||endx<0||endy<0||initialx>=MAPFILES.emapwidth()||initialy>=MAPFILES.emapheight()||endx>=MAPFILES.emapwidth()||endy>=MAPFILES.emapheight())
			{
				printf("\nSCRIPT ERROR-moven has bad parameters-positions outside array");
				return;
			}

			if (MAPFILES.MAPFILEENEMY[endy][endx]!=NULL)
			{
				printf("\nSCRIPT ERROR-moven - cannot move npc to occupied tile!");
				return;
			}

			NodeEnemy * temp = MAPFILES.MAPFILEENEMY[initialy][initialx];
			MAPFILES.MAPFILEENEMY[initialy][initialx]=NULL;

			temp->xpos=endx;
			temp->ypos=endy;

			MAPFILES.MAPFILEENEMY[endy][endx]=temp;

			break;
		}

		//msg
	case 5:
		{
			if (eptr->intList.getCount()!=2||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- msg has invalid number/type of parameters");
				return;
			}

			int textnum=*eptr->intList.headptr->value;
			int npcnum=*eptr->intList.headptr->nextptr->value;

			if (textnum<0||npcnum<0)
			{
				printf("\nSCRIPT ERROR- msg has bad parameters - less than 0");
				return;
			}

			if (GLOBAL.soundenabled==1)
				EXEC.loadSound(SND.maximize);
			GLOBAL.loopswitch=LS_TALKING;

			strcpy(INFOS.talknpcbuffer,INFOS.npctext[textnum]);
			strcpy(INFOS.talkingcharacterbuffer2,INFOS.talkingcharacterbuffer[npcnum]);

			break;
		}

		//play-sound
	case 6:
		{
			if (eptr->intList.getCount()!=1||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- play-sound has invalid number/type of parameters");
				return;
			}

			int soundnum=*eptr->intList.headptr->value;

			if (soundnum<0)
			{
				printf("\nSCRIPT ERROR- play-sound has bad parameters - less than 0 input");
				return;
			}

			switch(soundnum)
			{
			case 1: {EXEC.loadSound(SND.arming);break;}
			case 2: {EXEC.loadSound(SND.ouchsound);break;}
			case 3: {EXEC.loadSound(SND.swordhit);break;}
			case 4: {EXEC.loadSound(SND.misssound);break;}
			case 5: {EXEC.loadSound(SND.death1);break;}
			case 6: {EXEC.loadSound(SND.death4);break;}
			case 7: {EXEC.loadSound(SND.aircreate);break;}
			case 8: {EXEC.loadSound(SND.fireballsound);break;}
			case 9: {EXEC.loadSound(SND.icesound);break;}
			case 10: {EXEC.loadSound(SND.lightningsound);break;}
			case 11: {EXEC.loadSound(SND.windsound);break;}
			case 12: {EXEC.loadSound(SND.explosion);break;}
			case 13: {EXEC.loadSound(SND.foodsound);break;}
			case 14: {EXEC.loadSound(SND.goldsound);break;}
			case 15: {EXEC.loadSound(SND.teleportsound);break;}
			case 16: {EXEC.loadSound(SND.punchsound);break;}
			case 17: {EXEC.loadSound(SND.criticalhit);break;}
			case 18: {EXEC.loadSound(SND.buysound);break;}
			case 19: {EXEC.loadSound(SND.healsound);break;}
			case 20: {EXEC.loadSound(SND.dropsound);break;}
			case 21: {EXEC.loadSound(SND.pickupsound);break;}
			case 22: {EXEC.loadSound(SND.opensound);break;}
			case 23: {EXEC.loadSound(SND.closesound);break;}
			case 24: {EXEC.loadSound(SND.levelup);break;}
			default: {printf("\nSCRIPT ERROR-sound invalid");return;}
			}

			break;
		}

		//screen-on
	case 7:
		{
			if (eptr->intList.getCount()!=0)
			{
				printf("\nSCRIPT ERROR- screen-off has invalid number of parameters");
				return;
			}

			GLOBAL.blackscreen=false;
			break;
		}

		//screen-off
	case 8:
		{
			if (eptr->intList.getCount()!=0)
			{
				printf("\nSCRIPT ERROR- screen-off has invalid number of parameters");
				return;
			}

			GLOBAL.blackscreen=true;
			break;
		}

		//addqls
	case 9:
		{
			if (eptr->intList.getCount()!=0)
			{
				printf("\nSCRIPT ERROR- addqls has invalid number of parameters");
				return;
			}

			GLOBAL.questloopswitch++;

			break;
		}

		//play-music
	case 10:
		{
			if (eptr->intList.getCount()!=1||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- play-music has invalid number/type of parameters");
				return;
			}

			int musicnum=*eptr->intList.headptr->value;

			if (musicnum<0)
			{
				printf("\nSCRIPT ERROR- play-music has bad parameters - less than 0 input");
				return;
			}

			switch(musicnum)
			{
			case 1: {EXEC.loadMusic(SND.intro1);break;}
			default: {printf("\nSCRIPT ERROR-music invalid");return;}
			}


			break;
		}

		//stop-music
	case 11:
		{
			if (eptr->intList.getCount()!=1||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- stop-music has invalid number/type of parameters");
				return;
			}

			int musicnum=*eptr->intList.headptr->value;

			if (musicnum<0)
			{
				printf("\nSCRIPT ERROR- stop-music has bad parameters - less than 0 input");
				return;
			}

			switch(musicnum)
			{
			case 1: {EXEC.stopMusic(SND.intro1);break;}
			default: {printf("\nSCRIPT ERROR-music invalid");return;}
			}

			break;
		}

		//fade-in
	case 12:
		{
			if (eptr->intList.getCount()!=0||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- fade-in has invalid number/type of parameters");
				return;
			}

			GLOBAL.blackscreen=false;
			GLOBAL.fadestyle=1;
			GLOBAL.fadeamount=GLOBAL.fadestart;
			break;
		}

		//fade-out
	case 13:
		{
			if (eptr->intList.getCount()!=0||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- fade-out has invalid number/type of parameters");
				return;
			}
			GLOBAL.blackscreen=false;
			GLOBAL.fadestyle=2;
			GLOBAL.fadeamount=GLOBAL.fadestart;

			break;
		}

		//light-level
	case 14:
		{
			if (eptr->intList.getCount()!=1||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- light-level has invalid number/type of parameters");
				return;
			}

			int light=*eptr->intList.headptr->value;

			if (light<0)
			{
				printf("\nSCRIPT ERROR- light-level has bad parameters - less than 0 input");
				return;
			}

			GLOBAL.worldstatus=light;
			break;
		}

		//give-player-item
	case 15:
		{
			if (eptr->intList.getCount()!=1||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- give-player-item has invalid number/type of parameters");
				return;
			}

			int item=*eptr->intList.headptr->value;

			if (item<0)
			{
				printf("\nSCRIPT ERROR-give-player-item has bad parameters, less than 0");
				return;
			}

			EXEC.givehelditems(item);
			break;
		}

		//change-npc-dialog
	case 16:
		{
			if (eptr->intList.getCount()!=3|eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- change-npc-dialog has invalid number/type of parameters");
				return;
			}

			int initialx=*eptr->intList.headptr->value;
			int initialy=*eptr->intList.headptr->nextptr->value;

			int newdialog=*eptr->intList.headptr->nextptr->nextptr->value;

			if (initialx<0||initialy<0||initialx>=MAPFILES.emapwidth()||initialy>=MAPFILES.emapheight()||newdialog<0)
			{
				printf("\nSCRIPT ERROR- change-npc-dialog has bad parameters");
				return;
			}

			MAPFILES.MAPFILEENEMY[initialy][initialx]->talktype=newdialog;

			break;
		}

		//spawn-off
	case 17:
		{
			if (eptr->intList.getCount()!=0||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- spawn-off has invalid number/type of parameters");
				return;
			}
			GLOBAL.spawnenemies=false;
			break;
		}

		//spawn-on
	case 18:
		{
			if (eptr->intList.getCount()!=0||eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- spawn-on has invalid number/type of parameters");
				return;
			}
			GLOBAL.spawnenemies=true;
			break;
		}

		//wait
	case 19:
		{
			if (eptr->intList.getCount()!=1|eptr->usesInts==false)
			{
				printf("\nSCRIPT ERROR- wait has invalid number/type of parameters");
				return;
			}
			int millisec=*eptr->intList.headptr->value;

			if (millisec<0)
			{
				printf("\nSCRIPT ERROR- wait has bad parameters - less than 0");
				return;
			}

			//lock player during sleep, may or may not stop queuing of keyboard commands
			//also flush incase that works
			//because player may be locked before wait, set it to the previous val
			bool preloc=PLAYER.lockmove;
			PLAYER.lockmove=true;
			Sleep(millisec);
			fflush(stdin);
			PLAYER.lockmove=preloc;

			break;
		}

		//addls2
	case 20:
		{
			if (eptr->intList.getCount()!=0)
			{
				printf("\nSCRIPT ERROR- addls2 has invalid number of parameters");
				return;
			}

			GLOBAL.loopswitch2++;
			break;
		}


	default:
		{
			printf("\nSCRIPT ERROR-unknown script ID=%d",scriptnum);
			return;
		}
	}


}

void MP::runMapScript()
{
	if (MAPFILESSCRIPTS.getCount()==0)
		return;

	LinkedListNode<script> * newptr=MAPFILESSCRIPTS.headptr;

	while (newptr!=NULL)
	{
		//if there arent any conditions raise an error
		if (newptr->value==NULL||newptr->value->conditions.getCount()==0)
		{
			printf("\nSCRIPT ERROR-no conditions found!");
			return;
		}

		//check conditions
		LinkedListNode<condObj> * condptr=newptr->value->conditions.headptr;
		bool matched=true;

		while (condptr!=NULL)
		{
			if (condptr->value==NULL)	
			{
				printf("\nSCRIPT ERROR-no conditions found!");
				return;
			}

			//do hard coded conditions

			if (condptr->value->variableName!=NULL&&(strcmp(condptr->value->variableName,playerhascondition)==0))
			{
				if (EXEC.playerhas(condptr->value->value)==false)
					matched=false;
			}
			else if (condptr->value->variableName!=NULL&&(strcmp(condptr->value->variableName,mapenemyamountcondition)==0))
			{
				if (EXEC.mapenemyamount(NT_HOSTILE)!=condptr->value->value)
					matched=false;

			}
			else
			{
				int * variable=condptr->value->variable;
				int operatorVal=condptr->value->operatorValue;
				int value=condptr->value->value;

				switch (operatorVal)
				{
				case OP_EQUALS:
					{
						if (*variable!=value)
							matched=false;
						break;
					}

				case OP_GREATEREQUALSTHAN:
					{
						if (*variable<value)
							matched=false;
						break;
					}

				case OP_GREATERTHAN:
					{
						if (*variable<=value)
							matched=false;
						break;
					}

				case OP_LESSEQUALTHAN:
					{
						if (*variable>value)
							matched=false;
						break;
					}

				case OP_LESSTHAN:
					{
						if (*variable>=value)
							matched=false;
						break;

					}

				case OP_NOTEQUALS:
					{
						if (*variable==value)
							matched=false;
						break;
					}
				default:
					{
						printf("\nSCRIPT ERROR-unknown operator");
						return;
					}

				}
			}

			if (matched==false)
				break;

			condptr=condptr->nextptr;
		}

		//if here, all conditions are met, do effects, make sure matched
		if (matched)
		{

			//first check if no effects- just continue with scripts and print a warning
			if (newptr->value->effects.getCount()==0)
			{
				printf("\nSCRIPT WARNING-empty script (no effects)");
				continue;
			}

			LinkedListNode<effectObj> * effectptr=newptr->value->effects.headptr;

			while (effectptr!=NULL)
			{
				if (effectptr->value==NULL)
				{
					printf("\nSCRIPT ERROR-no effects found!");
					return;			
				}
				executeScriptEffects(effectptr->value);

				effectptr=effectptr->nextptr;
			}
		}
		newptr=newptr->nextptr;
	}

}

inline int MP::emapwidth()
{
	return EXTMAPWIDTH;
}
inline int MP::emapheight()
{
	return EXTMAPHEIGHT;
}

void MP::changeEXTMAP(int MAPWIDTH,int MAPHEIGHT,bool force)
{
	if ((MAPWIDTH!=EXTMAPWIDTH||MAPHEIGHT!=EXTMAPHEIGHT)||force==true)
	{
		MAPFILES.dinit(false,true);
	}
	EXTMAPWIDTH=MAPWIDTH;
	EXTMAPHEIGHT=MAPHEIGHT;

}


void MP::copystack(mapstackhead * copyfrom,mapstackhead * copyto)
{
	copyto->initstack();
	mapstax * hax=copyfrom->stackhead;
	while (hax!=NULL)
	{
		copyto->push(hax->id,hax->x,hax->y);
		hax=hax->downptr;
	}
}

char* MP::savevals(char * objtype)
{
	char temp[100];temp[0]=0;
	sprintf(temp," %s %d %d %d %d",objtype,MAPFILES.currentmap->darknessLevel,currentmap->id,emapwidth(),emapheight());
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void MP::loadvals(FILE * fileptr)
{
	int twidth=0;int theight=0;
	int mid=0;
	fscanf_s(fileptr,"%d %d %d %d",&MAPFILES.currentmap->darknessLevel,&mid,\
		&twidth,&theight);

	MAPFILES.currentmap=INFOS.MAPSTOREPTR[mid];
	MAPFILES.changeEXTMAP(twidth,theight,false);
}


void MP::loadMAPFILES(int mapxsize,int mapysize,FILE *mapfile)
{
	if (mapfile==NULL)
	{
		printf("\nError! loading mapfile null!");
	}
	MAPFILES.changeEXTMAP(mapxsize,mapysize,false);

	MAPFILES.MAPFILEinit(mapfile);

	MAPFILES.MAPFILEENEMYinit();
	MAPFILES.MAPFILEITEMinit();
	MAPFILES.TERRAINLOSinit(ANIMATION.getVIEWWIDTH(),ANIMATION.getVIEWHEIGHT());
	MAPFILES.RAYTRACEinit();
}

void MP::loadMAPFILES(int mapxsize,int mapysize)
{
	MAPFILES.changeEXTMAP(mapxsize,mapysize,false);
	MAPFILES.MAPFILEinit();
	MAPFILES.MAPFILEENEMYinit();
	MAPFILES.MAPFILEITEMinit();
	MAPFILES.TERRAINLOSinit(ANIMATION.getVIEWWIDTH(),ANIMATION.getVIEWHEIGHT());
	MAPFILES.RAYTRACEinit();
}


void MP::applyRayTrace(int ** grid,int xabs,int yabs,int xrel,int yrel,int xdist,int ydist,int maxx,int maxy)
{

	//x_1,y_1=start position of ray from top left corner
	//x_2,y_2=end position of ray from top left corner
	int x_1=xrel;int x_2=xrel+xdist;
	int y_1=yrel;int y_2=yrel+ydist;

	int dx=0,dy=0,py=0,px=0,twody=0,twodx=0,x=0,y=0,xend=0;

	dx=abs(x_1-x_2);
	dy=abs(y_1-y_2);
	twody=2*dy;
	twodx=2*dx;
	py=twody-dx;
	px=twodx-dy;

	x=x_1;
	y=y_1;
	xend=x_2;
	//light start position of ray up
	if ((y>=0&&y<maxy)&&(x>=0&&x<maxx))
	{
		if (MAPFILES.currentmap->darknessLevel<=0)
		{
			if (ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus]>1)
				grid[y][x]=1;
		}
		else
		{
			if (ANIMATION.LIGHTLEVELTABLE[MAPFILES.currentmap->darknessLevel*2]>1)
				grid[y][x]=1;

		}
	}

	int count=1;
	//draw a ray from start to end (continue while not at end)
	while (x!=x_2||y!=y_2)
	{

		if (px<0)
			px+=twodx;
		else
		{
			if (x<x_2)
				x++;
			else if (x>x_2)
				x--;
		}

		if (py<0)
			py+=twody;
		else
		{
			if (y<y_2)
				y++;
			else if (y>y_2)
				y--;

		}

		if ((y>=0&&y<maxy)&&(x>=0&&x<maxx))
		{
			if (MAPFILES.currentmap->darknessLevel<=0)
			{
				if (ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus]>count)
				{
					if (grid[y][x]>count||grid[y][x]==0)
						grid[y][x]=count;
				}
			}
			else
			{
				if (ANIMATION.LIGHTLEVELTABLE[MAPFILES.currentmap->darknessLevel*2]>count)
				{
					if (grid[y][x]>count||grid[y][x]==0)
						grid[y][x]=count;
				}
			}
		}

		count++;

		if (((yabs+(y-y_1)<MAPFILES.emapheight())&&(yabs+(y-y_1)>0))&&(xabs+(x-x_1)<MAPFILES.emapwidth())&&(xabs+(x-x_1)>0))
		{
			if (MAPFILES.MAPFILE[yabs+(y-y_1)][xabs+(x-x_1)]>=51&&MAPFILES.MAPFILE[yabs+(y-y_1)][xabs+(x-x_1)]!=58)
				return;
		}

		if ((yabs+(y-y_1)<0)||(xabs+(x-x_1)<0))
			return;

		else if ((yabs+(y-y_1)>=MAPFILES.emapheight())||(xabs+(x-x_1)>=MAPFILES.emapwidth()))
			return;

		if (MAPFILES.MAPFILE[yabs+(y-y_1)][xabs+(x-x_1)]==TT_TABLE)
			count++;
	}

}

void MP::rayTraceMain(int ** grid,int maxy,int maxx,int xabs,int yabs,int yrel,int xrel)
{
	//init
	for (int a=0;a<maxy;a++)
		for (int b=0;b<maxx;b++)
			grid[a][b]=0;

	//check for player view error state
	if (PLAYER.viewdist<0)
		PLAYER.viewdist=0;
	//get size of light around player as default + torch additions
	int dist=PLAYER.viewdist;
	if (EQUIPMENT.LARM.type==T_TORCHWEP)
		dist++;
	if (EQUIPMENT.RARM.type==T_TORCHWEP)
		dist++;

	int counttop=1;
	int x,y;
	x=-dist;
	y=0;

	if (dist==0)
	{applyRayTrace(grid,xabs,yabs,xrel,yrel,0,0,maxx,maxy);}
	else
	{
		while (x<dist+1)
		{
			for (y=-counttop;y!=counttop+1;y++)
			{applyRayTrace(grid,xabs,yabs,xrel,yrel,x,y,maxx,maxy);}

			if (counttop<=dist&&x<-1)
				counttop++;
			else if (counttop<=dist&&x>0)
				counttop--;
			x++;
		}
	}
	if (NPC.headptr!=NULL)
	{
		LinkedListNode<NodeEnemy> *newptr=NPC.headptr;

		while (newptr!=NULL)
		{	//ray tracing, max 3 squares distant?

			//torch light
			if (newptr->value->type==T_TORCH)
			{
				int xrel2=xrel-(PLAYER.posx-newptr->value->xpos);
				int yrel2=yrel-(PLAYER.posy-newptr->value->ypos);

				if (newptr->value->viewdist!=0)
					dist=newptr->value->viewdist;
				else
					dist=PLAYER.viewdist;

				counttop=1;
				x=y=0;
				x=-dist;

				if (dist==0)
				{applyRayTrace(grid,newptr->value->xpos,newptr->value->ypos,xrel2,yrel2,0,0,maxx,maxy);}
				else
				{
					while (x<dist+1)
					{

						for (y=-counttop;y!=counttop+1;y++)
							applyRayTrace(grid,newptr->value->xpos,newptr->value->ypos,xrel2,yrel2,x,y,maxx,maxy);

						if (counttop<=dist&&x<-1)
							counttop++;
						else if (counttop<=dist&&x>0)
							counttop--;
						x++;
					}
				}
			}
			newptr=newptr->nextptr;
		}
	}		

	if (spellz.headptr!=NULL)
	{
		LinkedListNode<NodeObject> *newptr=spellz.headptr;

		while (newptr!=NULL)
		{	//ray tracing, max 3 squares distant?
			//TODO:hard code : fire,zap spells to produce light on ray tracing
			if (SPELL.type>=400&&SPELL.type<450)
			{
				int xrel2=xrel-(PLAYER.posx-newptr->value->xpos);
				int yrel2=yrel-(PLAYER.posy-newptr->value->ypos);

				if (SPELL.type==400||SPELL.type==421||SPELL.type==431||SPELL.type==402||SPELL.type==423||SPELL.type==433)
					dist=1;
				else
					dist=0;

				counttop=1;
				x=y=0;
				x=-dist;

				if (dist==0)
				{applyRayTrace(grid,newptr->value->xpos,newptr->value->ypos,xrel2,yrel2,0,0,maxx,maxy);}
				else
				{
					while (x<dist+1)
					{
						for (y=-counttop;y!=counttop+1;y++)
							applyRayTrace(grid,newptr->value->xpos,newptr->value->ypos,xrel2,yrel2,x,y,maxx,maxy);

						if (counttop<=dist&&x<-1)
							counttop++;
						else if (counttop<=dist&&x>0)
							counttop--;
						x++;
					}
				}
			}
			newptr=newptr->nextptr;
		}
	}
}


//attacker as 0x01=allow swim
inline bool MP::passable(int y,int x,NodeEnemy * moveme)
{	
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
		return false;

	//fast terrain check
	if (moveme!=(NodeEnemy*)0x01&&MAPFILES.MAPFILE[y][x]==TT_DOOR)
		;
	else if (MAPFILES.MAPFILE[y][x]>=50&&MAPFILES.MAPFILE[y][x]<100)
		return false;

	//player attacking
	bool isplayer=false;
	if (moveme==(NodeEnemy*)0x01)
		isplayer=true;

	//npc attacking
	bool targetplayer=false;
	if (MAPFILES.MAPFILEENEMY[y][x]==(NodeEnemy*)0x01)
		targetplayer=true;

	//npc attacking
	if (moveme!=NULL&&isplayer==false)
	{	
		if (MAPFILES.MAPFILE[y][x]==TT_WATER&&moveme->canswim==false)
			return false;

		//if the tile isnt empty
		if (MAPFILES.MAPFILEENEMY[y][x]!=NULL)
		{
			//if attacking the player and the faction isnt NT_FRIENDLY (since the player can swap with friendlies)
			if (targetplayer==true&&moveme->faction!=NT_FRIENDLY)
				return false;

			//if not attacking the player
			else if (targetplayer==false)
			{
				//not possible for npcs to cross each other atm, maybe later swap if str+def is greater than other
				return false;
			}
		}
	}

	else if (isplayer==true)
	{
		if (MAPFILES.MAPFILE[y][x]==TT_WATER&&PLAYERSTATS.canswim==false)
			return false;
		if (MAPFILES.MAPFILEENEMY[y][x]!=NULL)
		{
			if (MAPFILES.MAPFILEENEMY[y][x]->faction!=NT_FRIENDLY)
				return false;
		}		
	}
	return true;
}


inline bool MP::passable2(int y,int x,NodeEnemy * attacker,bool checkfornpc)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
		return false;

	if (checkfornpc==true)
	{
		if (MAPFILES.MAPFILEENEMY[y][x]!=NULL)
			return false;		
	}	
	if (MAPFILES.MAPFILE[y][x]==TT_WATER&&attacker->canswim==false)
		return false;

	if (MAPFILES.MAPFILE[y][x]<50||MAPFILES.MAPFILE[y][x]>=100)
		return true;
	return false;
}

void MP::dinit(bool docompare,bool justarrays)
{
	if (MAPFILES.currentmap!=NULL)
	{
		if (docompare==true)
		{
			if (MAPFILES.lastmap==MAPFILES.currentmap)
				return;
		}
	}

	MAPFILEdinit();	
	MAPFILEITEMdinit();
	MAPFILEENEMYdinit();
	RAYTRACEdinit();
	exitpoints.clear();

	if (justarrays==false)
	{

		mapSTACK.initstack();
	}
}

void MP::init()
{
	if (emapheight()!=0&&emapwidth()!=0)
	{
		MAPFILEinit(NULL);
		MAPFILEITEMinit();
		MAPFILEENEMYinit();
		RAYTRACEinit();
	}

	STARTX=0;
	STARTY=0;
	rearmx=0;
	rearmy=0;

	if (MAPFILE==NULL)
	{
		EXTMAPWIDTH=0;
		EXTMAPHEIGHT=0;
	}
	xy[0]=0;xy[1]=0;
	//int moves[200][3]; //0=active, 1=x, 2=y
	mapSTACK.initstack();
	MAPFILESSCRIPTS.clear();
}


MP::~MP()
{
	dinit(false,false);
}


MP::MP()
{
	init();
}

void MP::MAPFILEinit(FILE * inputstreamz)
{
	MAPFILEdinit();

	if (inputstreamz==NULL)
		return;
	MAPFILE = new int*[MAPFILES.emapheight()];
	for (int a=0;a<MAPFILES.emapheight();a++)
	{
		MAPFILE[a]=new int[MAPFILES.emapwidth()];
		for (int b=0;b<MAPFILES.emapwidth();b++)
			fscanf_s(inputstreamz,"%d",&MAPFILE[a][b]);
	}
}

void MP::MAPFILEinit()
{
	MAPFILEdinit();
	MAPFILE = new int*[MAPFILES.emapheight()];
	for (int a=0;a<MAPFILES.emapheight();a++)
	{
		MAPFILE[a]=new int[MAPFILES.emapwidth()];
		for (int b=0;b<MAPFILES.emapwidth();b++)
			MAPFILE[a][b]=0;
	}
}

void MP::MAPFILEENEMYinit()

{
	MAPFILEENEMYdinit();
	MAPFILEENEMY = new NodeEnemy**[MAPFILES.emapheight()];
	for (int a=0;a<MAPFILES.emapheight();a++)
	{
		MAPFILEENEMY[a]=new NodeEnemy*[MAPFILES.emapwidth()];
		for (int b=0;b<MAPFILES.emapwidth();b++)
			MAPFILEENEMY[a][b]=0;
	}

}


void MP::RAYTRACEinit()
{
	RAYTRACEdinit();

	RAYTRACE = new int*[ANIMATION.getVIEWHEIGHT()];
	for (int a=0;a<ANIMATION.getVIEWHEIGHT();a++)
	{
		RAYTRACE[a]=new int[ANIMATION.getVIEWWIDTH()+1];
		for (int b=0;b<ANIMATION.getVIEWWIDTH()+1;b++)
			RAYTRACE[a][b]=0;
	}
}


void MP::TERRAINLOSinit()
{
	TERRAINLOSinit(ANIMATION.getVIEWWIDTH(),ANIMATION.getVIEWHEIGHT());
}


void MP::TERRAINLOSinit(int vw,int vh)
{
	int oldw=ANIMATION.getVIEWWIDTH();
	int oldh=ANIMATION.getVIEWHEIGHT();
	//if old and new sizes are the same, ignore
	if (vw==oldw&&vh==oldh)
		return;

	//if new sizes are invalid, ignore
	if (vw<=0||vh<=0)
		return;

	//delete arrays using old size
	RAYTRACEdinit();

	//set viewheight,width and the size of the tiles to the new vars
	//init array using new sizes
	ANIMATION.setview(vw,vh);
	ANIMATION.tilesizeinit();
}

void MP::MAPFILEITEMinit()
{
	MAPFILEITEMdinit();
	MAPFILES.MAPFILEITEM = new NodeObject**[MAPFILES.emapheight()];
	for (int a=0;a<MAPFILES.emapheight();a++)
	{
		MAPFILES.MAPFILEITEM[a]=new NodeObject*[MAPFILES.emapwidth()];
		for (int b=0;b<MAPFILES.emapwidth();b++)
			MAPFILES.MAPFILEITEM[a][b]=NULL;
	}
}

void MP::RAYTRACEdinit()
{
	if (RAYTRACE==NULL)
		return;
	for (int a=0;a<ANIMATION.getVIEWHEIGHT();a++)
		delete[] RAYTRACE[a];
	delete[] RAYTRACE;
	RAYTRACE=NULL;
}

void MP::MAPFILEdinit()
{
	if (MAPFILE==NULL)
		return;
	for (int a=0;a<MAPFILES.emapheight();a++)
		delete[] MAPFILE[a];
	delete[] MAPFILE;
	MAPFILE=NULL;
}


void MP::MAPFILEENEMYdinit()
{
	//printf("\nMPE DINIT");
	if (MAPFILEENEMY==NULL)
		return;
	for (int a=0;a<MAPFILES.emapheight();a++)
		delete[] MAPFILEENEMY[a];
	delete[] MAPFILEENEMY;
	MAPFILEENEMY=NULL;
}

void MP::MAPFILEITEMdinit()
{
	if (MAPFILEITEM==NULL)
		return;
	for (int a=0;a<MAPFILES.emapheight();a++)
		delete[] MAPFILEITEM[a];
	delete[] MAPFILEITEM;
	MAPFILEITEM=NULL;
}

#endif