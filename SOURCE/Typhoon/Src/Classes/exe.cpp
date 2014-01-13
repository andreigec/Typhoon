//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _EXE_CPP
#define _EXE_CPP

int exe::playerhas(int itemID)
{
	if (helditems.getCount()==0)
		return false;

	LinkedListNode<NodeObject> *newptr= helditems.headptr;

	while (newptr!=NULL)
	{
		if (newptr->value!=NULL)
		{
			if (newptr->value->id==itemID)
				return 1;
		}

		newptr=newptr->nextptr;
	}

	return 0;
}

int exe::mapenemyamount(int faction)
{
	if (NPC.getCount()==0)
		return 0;

	LinkedListNode<NodeEnemy> * newptr=NPC.headptr;
	int count=0;

	while (newptr!=NULL)
	{
		if (newptr->value!=NULL)
		{
			if (newptr->value->faction==faction)
				count++;
		}

		newptr==newptr->nextptr;
	}

	return count;
}



void exe::loadfromfile(mapstore * newptr,int fileDungeonId)
{
	if (newptr==NULL)
	{
		printf("\nerror!, newptr==NULL");
		return;
	}

	//is a dungeon from a saved file
	if (newptr->type==T_DUNGEON&&fileDungeonId!=-1)
	{
		readfromdungeon(newptr->path);
		MAPFILES.loadMAPFILES(DUNGEON.mapsize,DUNGEON.mapsize);
		loaddungeonmapfile("dm.cfg");
		MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
		return;
	}
	//is a generated dungeon
	else if (newptr->type==T_DUNGEON)
	{
		//should only have to reload information about dungeon if this is first generated map
		if (DUNGEON.isdungeon==false)
		{
			readfromdungeon(newptr->path);
			DUNGEON.currentlevel=1;
		}
		MAPFILES.loadMAPFILES(DUNGEON.mapsize,DUNGEON.mapsize);

		mapgen(DUNGEON.mapsize,DUNGEON.mapsize,DUNGEON.maptype);

		PLAYER.posx=MAPFILES.currentmap->startX;
		PLAYER.posy=MAPFILES.currentmap->startY;

		MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
		return;
	}

	//load from file
	else
	{
		int twidth,theight;
		FILE * inputstream=NULL;
		_fopen_s(&inputstream,newptr->path,"r");

		fscanf_s(inputstream,"%d %d",&twidth,&theight);
		MAPFILES.loadMAPFILES(twidth,theight,inputstream);
		_fclose(inputstream);
		//set enemyrates

	}
}


void exe::loadfromfile(mapstore * newptr)
{	
	loadfromfile(newptr,-1);
}



//(EXECUTED) WHEN:
//'e' on square
//force change on stepping on tile
//step on tile, choose to go to map
//load from file
//loaded by default on game init

//POSSIBLE (A)CTIONS:
//A1:First game map, clear mapstack, start afresh
//A2:Push into map
//A3:Pop out of map
//A4:Load game from file-load a map with mapstack
//A5:Load game from file-load a dungeon and mapstack
//A6:When in dungeon, can push down into a lower level, when in tower can push into a higher level
//A7:When in dungeon, can pop to the surface (up),  when in a tower can pop to the surface (down)
//A8:When in dungeon, if reach bottom, can go to a basement level

void exe::loadMapGeneralSteps(mapstore * newmap)
{
	if (MAPFILES.MAPFILEENEMY!=NULL)
		MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
	grounditems.clear();

	MAPFILES.lastmap=MAPFILES.currentmap;
	MAPFILES.currentmap=newmap;

	CONSOLE.pushtext(false,3,TEXT_ENTER);
	CONSOLE.pushtext(false,0,newmap->name);
}

void exe::loadMap(int ladder)
{	
	//A7:When in a dungeon, can pop to the surface (up),  when in a tower can pop to the surface (down)
	if ((ladder==TT_LADDERU&&DUNGEON.isdungeon==true)||(ladder==TT_LADDERD&&DUNGEON.isdungeon==false))
	{	
		NPC.clear();
		mapstore * nextmap=INFOS.MAPSTOREPTR[DUNGEON.firstlevelmapid];
		loadMapGeneralSteps(nextmap);
		loadfromfile(nextmap);
		popposition(&PLAYER.posy,&PLAYER.posx);
		MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
		popenemies();
		DUNGEON.init();
		EXEC.initshop();
		loadpresets();
	}
	else if ((ladder==TT_LADDERU&&DUNGEON.isdungeon==false)||(ladder==TT_LADDERD&&DUNGEON.isdungeon==true))
	{
		//A6:When in dungeon, can push down into a lower level, when in tower can push into a higher level
		if (DUNGEON.currentlevel<DUNGEON.lastlevel)
		{
			mapstore * nextmap=INFOS.MAPSTOREPTR[MAPFILES.currentmap->id];
			loadMapGeneralSteps(nextmap);
			NPC.clear();
			loadfromfile(nextmap);	

			//TODO:using currentmap id here, because dungeon does not know what type it is eg 7=creet, so use current because it should be the same
			loadfromfile(nextmap);
			printf("\ncurrentlevel:%d,",DUNGEON.currentlevel);
			DUNGEON.currentlevel++;
			printf("%d,",DUNGEON.currentlevel);
		}
		//A8:When in dungeon, if reach bottom, can go to a basement level
		else
		{
			mapstore * nextmap=INFOS.MAPSTOREPTR[DUNGEON.lastlevelmapid];
			NPC.clear();
			loadMap(nextmap);			
		}
	}
}


void exe::loadMap(mapstore * loadmap)
{
	loadMapGeneralSteps(loadmap);

	//A5:Load game from file-load a dungeon and mapstack
	if (loadmap->type==T_DUNGEON)
		loadfromfile(loadmap,loadmap->id);
	//A1:First game map, clear mapstack, start afresh
	//A4:Load game from file-load a map with mapstack
	else
	{
		loadfromfile(loadmap);
		PLAYER.posx=MAPFILES.currentmap->startX;
		PLAYER.posy=MAPFILES.currentmap->startY;
	}


	MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;

	EXEC.initshop();
	loadpresets();
	if (MAPFILES.currentmap->id==INFOS.firstMapId)
		MAPFILES.mapSTACK.initstack();
}

void exe::loadMap(exitpoint * exitorig)
{
	if (exitorig==NULL)
		return;

	//copy the exitpoint because it gets razed in load from file
	exitpoint *exitcopy = new exitpoint;
	*exitcopy=exitorig;

	mapstore * mapptr=INFOS.MAPSTOREPTR[exitcopy->id];

	loadMapGeneralSteps(mapptr);
	//A2:Push into map
	if (exitcopy->ispop==false)
	{
		pushposition(PLAYER.posy,PLAYER.posx);
		pushenemies();

		loadfromfile(mapptr);
		//change player positions
		PLAYER.posx=MAPFILES.currentmap->startX;
		PLAYER.posy=MAPFILES.currentmap->startY;	
	}
	//A3:Pop out of map
	else
	{
		loadfromfile(mapptr);
		popposition(&PLAYER.posy,&PLAYER.posx);
		popenemies();

	}

	if (mapptr->id==INFOS.firstMapId)
		MAPFILES.mapSTACK.initstack();

	if (exitcopy->changeX!=0||exitcopy->changeY!=0)
	{
		MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
		PLAYER.posy+=exitcopy->changeY;
		PLAYER.posx+=exitcopy->changeX;
		MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
	}
	EXEC.initshop();
	loadpresets();
	MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;

}

void exe::trimmemory()
{
	if (texturez.count>=HCVARS.TEXTUREUSAGECUTOFF)
		EXEC.clearoldtextures();

	if (soundz.count>=HCVARS.SOUNDUSAGECUTOFF)
		EXEC.clearoldsounds();
}


void exe::printterrain(bool terrainonly)
{
	int lastterrain=-1;
	ANIMATION.tilesizeinit();
	const float tilewidth=ANIMATION.tilesizewidth;
	const float tileheight=ANIMATION.tilesizeheight;

	const float startx=ANIMATION.SCREENSTARTX;
	const float starty=ANIMATION.SCREENSTARTY;
	const float swidth=ANIMATION.SCREENWIDTH;
	const float sheight=ANIMATION.SCREENHEIGHT;

	if (GLOBAL.blackscreen==true)
	{
		glColor3f(0,0,0);
		glBegin(GL_QUADS);
		glVertex2f(startx,starty);
		glVertex2f(swidth+startx,starty);
		glVertex2f(swidth+startx,starty-sheight);
		glVertex2f(startx,starty-sheight);
		glEnd();

		return;
	}
	int a=0;
	int b=0;
	int terrain=0;
	int c=-ANIMATION.getVIEWHEIGHT()/2;
	int d=-ANIMATION.getVIEWWIDTH()/2;

	int e=0;
	int f=0;
	int spellx=0,spelly=0;
	//	int torchs=0,torchx=0,torchy=0;

	MAPFILES.RAYTRACEinit();

	if (MAPFILES.MAPFILE[0][0]<0||MAPFILES.MAPFILE[0][0]>100)
		printf("\nWarning,mapfile has invalid values for 0,0=%d",MAPFILES.MAPFILE[0][0]);
	//check if shadows are needed
	else if (terrainonly==false)
		MAPFILES.rayTraceMain(MAPFILES.RAYTRACE,ANIMATION.getVIEWHEIGHT(),ANIMATION.getVIEWWIDTH(),PLAYER.posx,PLAYER.posy,ANIMATION.getVIEWHEIGHT()/2,ANIMATION.getVIEWWIDTH()/2);

	for (a=0;a<ANIMATION.getVIEWHEIGHT();a++)
	{
		for (b=0;b<ANIMATION.getVIEWWIDTH();b++)
		{
			//show either the player if in game, or the animation position for the opening screen
			if (GLOBAL.loopswitch!=LS_OPENING)
			{
				e=PLAYER.posy+c+a;
				f=PLAYER.posx+d+b;
			}
			else
			{
				e=ANIMATION.POSY+c+a;
				f=ANIMATION.POSX+d+b;

			}

			if (e<0)e=-1;
			if (f<0)f=-1;
			if (e>=MAPFILES.emapheight())e=-1;
			if (f>=MAPFILES.emapwidth())f=-1;

			glColor3f(1.0, 1.0, 1.0);

			if (e<0||f<0)
			{terrain=-2;}
			else
			{
				terrain=MAPFILES.MAPFILE[e][f];
			}
			if (lastterrain==terrain)
			{goto skipload;}
			else
			{lastterrain=terrain;}

			EXEC.loadterraincase(terrain);
skipload:

			float amount=0;
			amount=EXEC.getlightlevel(a,b,false);
			glColor3f(amount,amount,amount);


			drawtile(\
				startx+(b*tilewidth), starty-((a+1)*tileheight),\
				startx+(b*tilewidth), starty-(a*tileheight),\
				startx+((b+1)*tilewidth),starty-(a*tileheight),\
				startx+((b+1)*tilewidth), starty-((a+1)*tileheight));

			if (e!=-1&&f!=-1&&terrainonly==false)
			{
				glColor4f(1,1,1,1);

				bool isspell=false;
				bool isobject=false;
				bool isplayer=false;
				bool isenemy=false;
				float barr=-1;

				if ((MAPFILES.RAYTRACE[a][b]==0&&(ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus]<7||(MAPFILES.currentmap->darknessLevel!=0&&(MAPFILES.currentmap->darknessLevel*2)/7<7)))||(MAPFILES.RAYTRACE[a][b]!=0))
				{

					LinkedListNode<NodeObject>* spellptr=spellz.headptr;

					while (spellptr!=NULL&&(SPELL.active==1||SPELL2.active==1))
					{
						if (spellptr->value->xpos==f&&spellptr->value->ypos==e)
						{
							if (SPELL2.active==0)EXEC.loadTexture(SPELL.image);
							else
								EXEC.loadTexture(SPELL2.image);
							lastterrain=-1;
							//printf("\nSX=%d,tileheight=%d,SP=%s",SPELL.posx,SPELL.posy,SPELL.image);
							isspell=true;
							break;
						}
						spellptr=spellptr->nextptr;
					}


					if (MAPFILES.MAPFILEITEM[e][f]!=NULL)
					{
						isobject=true;
						EXEC.loadTexture(MAPFILES.MAPFILEITEM[e][f]->pic);
						lastterrain=-1;
					}

					if (MAPFILES.MAPFILEENEMY[e][f]!=NULL)
					{
						if (MAPFILES.MAPFILEENEMY[e][f]==(NodeEnemy*)0x01)
						{
							//printf("\nfound player at y=%d, x=%d",e,f);
							isplayer=true;
						}

						else
						{
							barr=MAPFILES.MAPFILEENEMY[e][f]->returnbaramount();isenemy=true;
							EXEC.loadTexture(MAPFILES.MAPFILEENEMY[e][f]->pic);
							lastterrain=-1;
						}
					}
				}

				if (isplayer==true)
				{
					EXEC.loadTexture(PLAYER.image);
					lastterrain=-1;
					barr=(((float)PLAYER.health/(float)PLAYER.maxhealth));
				}

				if (barr>1)
					barr=2;
				else if (barr<0)
					barr=-1;

				//printf("\nt4=%d,t2=%d,t=%d,t3=%d,t5=%d",temp4,temp2,temp,temp3,temp5);

				if 	(isplayer==true||isenemy==true||isobject==true||isspell==true)
				{				
					float amount=0;
					if (f==spellx&&e==spelly&&SPELL.active==1&&(SPELL.type==400||SPELL.type==421||\
						SPELL.type==431||SPELL.type==402||SPELL.type==423||SPELL.type==433))
					{amount=1;goto skipshadows2;}
					else
						amount=EXEC.getlightlevel(a,b,!isplayer);
					glColor3f(amount,amount,amount);

skipshadows2:	
					//lighting problem here			
					glColor4f(1,1,1,amount);
					//drawtile(10+(b*tilewidth), ty-(a*tileheight),10+(b*tilewidth), 470-(a*tileheight),tx+(b*tilewidth), 470-(a*tileheight),tx+(b*tilewidth), ty-(a*tileheight));
					drawtile(\
						startx+(b*tilewidth), starty-((a+1)*tileheight),\
						startx+(b*tilewidth), starty-(a*tileheight),\
						startx+((b+1)*tilewidth),starty-(a*tileheight),\
						startx+((b+1)*tilewidth), starty-((a+1)*tileheight));

					if (barr!=-1)
					{

						glColor4f(1,1,1,1);							
						amount=EXEC.getlightlevel(a,b,!isplayer);

						glColor3f(amount,amount,amount);

						glBegin(GL_QUADS);
						for (int f=0;f<2;f++)
						{
							//for looks dont make bar same width as tile its based on, offset by a bit
							float ma=ANIMATION.tilesizewidth/6;
							if (f==0&&amount>0)
							{
								if (MAPFILES.currentmap->darknessLevel==0||(MAPFILES.currentmap->darknessLevel!=0&&amount!=0))
								{

									glColor3f(0,0,0);
									glVertex2f(startx+(b*tilewidth)+ma, (starty+3)-(a*tileheight));
									glVertex2f(startx+((b+1)*tilewidth)-ma, (starty+3)-(a*tileheight));
									glVertex2f(startx+((b+1)*tilewidth)-ma, starty-(a*tileheight));
									glVertex2f(startx+(b*tilewidth)+ma, starty-(a*tileheight));
								}
							}

							else if (f==1&&amount>0)
							{
								if (barr>1)
								{
									glColor3f(1,1,0);
									glVertex2f(startx+(b*tilewidth)+ma, (starty+3)-(a*tileheight));
									glVertex2f(startx+((b+1)*tilewidth)-ma, (starty+3)-(a*tileheight));
									glVertex2f(startx+((b+1)*tilewidth)-ma, starty-(a*tileheight));
									glVertex2f(startx+(b*tilewidth)+ma, starty-(a*tileheight));
								}
								else
								{
									float base=startx+(b*tilewidth)+ma;
									float max=startx+(((b+1)*tilewidth))-ma;
									float shifted=base+((max-base)*barr);
									glColor3f(amount,0,0);
									glVertex2f(base, (starty+3)-(a*tileheight));
									glVertex2f(shifted, (starty+3)-(a*tileheight));
									glVertex2f(shifted, starty-(a*tileheight));
									glVertex2f(base, starty-(a*tileheight));
								}
							}

						}
					}
					glEnd();
				}


				if (GLOBAL.debugTiles==DTT_RAYTRACE)
				{

					glPushMatrix();

					glTranslatef(startx+(b*tilewidth), starty-(a*tileheight)-(tileheight/2),0);
					glScalef(.15,.10,.15);
					glColor4f(1, 0, 0,1);

					glutStrokeInteger(MAPFILES.RAYTRACE[a][b]);

					glPopMatrix();

					glColor3f(1, 1, 1);
				}

				if (GLOBAL.debugTiles==DTT_PATHFIND)
				{
					glColor4f (1,1,1,1);
					LinkedListNode<NodeEnemy> *playerz=NPC.headptr;
					while (playerz!=NULL)
					{
						if (playerz->value->faction==NT_HOSTILE)
						{break;}
						playerz=playerz->nextptr;
					}				

					glPushMatrix();

					glTranslatef(startx+(b*tilewidth), starty-(a*tileheight)-(tileheight/2),0);
					glScalef(.15,.10,.15);
					glColor3f(1,0,0);

					path * hax=pathz.findpath(f,e);
					glutStrokeInteger(hax->f);
					glPopMatrix();

					glColor4f(1, 1, 1,1);

				}
			}
		}	
	}

	if (GLOBAL.fadestyle!=0)
	{
		int minusamount=20;
		GLOBAL.fadeamount-=minusamount;
		float shade=(float)GLOBAL.fadeamount/(float)GLOBAL.fadestart;
		if (GLOBAL.fadestyle==1)
			glColor4f(0,0,0,shade);
		else
			glColor4f(0,0,0,1-shade);

		glBegin(GL_QUADS);
		glVertex2f(startx,starty);
		glVertex2f(swidth+startx,starty);
		glVertex2f(swidth+startx,starty-sheight);
		glVertex2f(startx,starty-sheight);
		glEnd();
		glColor4f(1,1,1,1);

		//stop animation thread
		if (GLOBAL.fadeamount==0)
		{
			ANIMATION.timerenabled=false;
			GLOBAL.fadestyle=0;
		}

		//start the timer thread for animation
		if (GLOBAL.updateThreadCount==0)
		{
			ANIMATION.timerenabled=true;
			GLOBAL.updateThreadCount++;
			myTimer(150);
		}

	}
}

template <class T>
int searchList(LinkedList<T> * listPtr,int type,int amount)
{
	LinkedListNode<T> * temp=listPtr->headptr;

	while (temp!=NULL)
	{
		if (temp->value->id==type&&temp->value->amount==amount)
			return 0;

		temp=temp->nextptr;
	}

	return 1;
}

template <class T>
int getcountfaction(LinkedList<T> *listPtr,int faction)
{
	LinkedListNode<T> * temp=listPtr->headptr;
	int count=0;
	while (temp!=NULL)
	{
		if (temp->value->faction==faction)
			count++;
		temp=temp->nextptr;
	}
	return count;
}

bool exe::isnear(int atx,int aty,int tgx,int tgy)
{
	if (((aty>=tgy-1)&&(aty<=tgy+1)) && ((atx>=tgx-1)&&(atx<=tgx+1)))
		return true;
	return false;
}


//function that forces a weapon to the player, used in arming player with fists
void exe::giveweapon(int id,bool forlefthand)
{
	int nid=id;
	while (nid>=100)
		nid-=100;

	if (forlefthand==true)
		EQUIPMENT.LARM=INFOS.WEPSTOREPTR[nid];
	else
		EQUIPMENT.RARM=INFOS.WEPSTOREPTR[nid];
}




void exe::findvalues(int px, int py,int tx,int ty,NodeEnemy * player)
{
	if (px==0||py==0)return;

	int a,b;
	int costarr=999;
	int xarr=0;
	int yarr=0;
	for (a=py-1;a!=py+2;a++)
	{
		for (b=px-1;b!=px+2;b++)
		{
			path * temp1=pathz.findpath(b,a);
			path * temp2=pathz.findpath(px,py);

			if (temp1->parent==0)
				temp1->parent=temp2;

			if (a<MAPFILES.emapheight()&&b<MAPFILES.emapheight())
			{
				if (MAPFILES.passable2(a,b,player,false)==false&&MAPFILES.MAPFILE[a][b]!=TT_DOOR)
					temp1->open=2;
			}
			else
				return;

			if (MAPFILES.MAPFILEENEMY[a][b]!=NULL)
			{
				if (a!=ty||b!=tx)
					temp1->open=2;
			}
			int VD=player->viewdist-ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus];

			if ((a<ty-VD||a>ty+VD)||(b<tx-VD||b>tx+VD))
				temp1->open=2;


			if (temp1->open==0)
			{
				temp1->g=10;
				if (b==MAPFILES.lasty&&a==MAPFILES.lastx)
					temp1->f+=915;
				if (MAPFILES.MAPFILE[a][b]==TT_LAVA)
					temp1->g+=10;
				temp1->h=5*(abs(b-tx)+abs(a-ty));
				temp1->f=temp1->g+temp1->h;
				if (temp1->f==0)
					printf("0f");

				if (temp1->f<costarr)
				{
					costarr=temp1->f;
					xarr=temp1->x;
					yarr=temp1->y;
				}
			}
			else if (temp1->f==0)
			{temp1->f=-1;}
		}
	}
	MAPFILES.xy[0]=xarr;
	MAPFILES.xy[1]=yarr;
	//if (MAPFILES.MAPFILEENEMY2[yarr][xarr]==1&&(yarr!=PLAYER.posy&&xarr!=PLAYER.posx))
	//{printf("\n error- enemy pos x=%d, y=%d",xarr,yarr);}
	if (MAPFILES.xy[0]==0&&MAPFILES.xy[1]==0)
		return;
}


int exe::findpath(NodeEnemy * attacker,const int tx,const int ty,int makepath)
{
	//if the target is still near the last position, dont bother remaking
	//first check to see if the path has been 'corrupted'. usually by other npcs walking on this npcs path
	if (attacker->movelisthead.headptr!=NULL)
	{
		if (attacker->isMoveListCorrupted()==false)
		{
			if (isnear(attacker->movelisthead.headptr->value->x,attacker->movelisthead.headptr->value->y,PLAYER.posx,PLAYER.posy))
				return 0;
		}
	}

	//clear all previous paths and path related data
	attacker->movelisthead.clear();
	pathz.clearall();

	int tpx=attacker->xpos;
	int tpy=attacker->ypos;

	//attempt to stop path finding that takes too long
	//less npcs = more cpu
	int count=0;
	int maxcount=400;
	maxcount-=(8*NPC.getCount()-1);
	if (maxcount<attacker->viewdist*3)
		maxcount=attacker->viewdist*3;	

	while(tpx!=tx||tpy!=ty)
	{
		count++;
		//do incomplete path when quitting
		if (count==maxcount)
			break;

		path * temp1=pathz.findpath(tpx,tpy);
		temp1->open=1;
		findvalues(tpx,tpy,tx,ty,attacker);

		//if cant find a path then backtrack using logical parent
		if (MAPFILES.xy[0]==0&&MAPFILES.xy[1]==0)
		{
			if (tpx==attacker->xpos&&tpy==attacker->ypos)
			{
				printf("\nNo Path");
				//CONSOLE.pushtext(true,0,"AI-No Path");
				return 1;
			}
			if (temp1->logicalparent->x!=0&&temp1->logicalparent->y!=0)
			{
				int tpx2=temp1->logicalparent->x;
				int tpy2=temp1->logicalparent->y;
				tpx=tpx2;tpy=tpy2;
			}
		}
		else
		{
			//set the logical parent if a path is found (logical parent being the last tile reached)		
			path * temp2=pathz.findpath(MAPFILES.xy[0],MAPFILES.xy[1]);
			temp2->logicalparent=temp1;
			tpx=MAPFILES.xy[0];tpy=MAPFILES.xy[1];
		}

		//when the tile cant be reached, but the npcs are adjacent, npcs can still melee
		if (MAPFILES.passable2(ty,tx,attacker,false)==false||MAPFILES.MAPFILE[ty][tx]==TT_DOOR)
		{
			path * temp2=pathz.findpath(MAPFILES.xy[0],MAPFILES.xy[1]);
			if (isnear(tpx,tpy,tx,ty))
			{
				path * temp3=pathz.findpath(tx,ty);
				temp3->parent=temp2;

				break;
			}
		}
	}

	//make sure that the npcs terrain position doesnt have itself as a parent
	path * temp=pathz.findpath(attacker->xpos,attacker->ypos);
	temp->parent=NULL;

	if (makepath==1)
	{
		temp=pathz.findpath(tpx,tpy);
		while (temp!=NULL)
		{
			//add all the tiles between the attacker and the target that the attacker can step on.
			if ((temp->x!=attacker->xpos||temp->y!=attacker->ypos)&&(temp->x!=tx||temp->y!=ty))
			{
				//infinite while loop chance here
				movelist * newptr=attacker->movelisthead.insertNode();
				newptr->x=temp->x;
				newptr->y=temp->y;				
			}
			temp=temp->parent;
		}
	}
	return 0;
}




void exe::randomnpc(NodeEnemy * nodeptr)	
{
	int random=0;
	random= rand()%8;

	if (random==0&&MAPFILES.passable(nodeptr->ypos,nodeptr->xpos-1,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=NULL;nodeptr->xpos--;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==1&&MAPFILES.passable(nodeptr->ypos-1,nodeptr->xpos-1,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->xpos--;nodeptr->ypos--;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==2&&MAPFILES.passable(nodeptr->ypos-1,nodeptr->xpos,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->ypos--;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==3&&MAPFILES.passable(nodeptr->ypos-1,nodeptr->xpos+1,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->ypos--;nodeptr->xpos++;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==4&&MAPFILES.passable(nodeptr->ypos,nodeptr->xpos+1,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->xpos++;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==5&&MAPFILES.passable(nodeptr->ypos+1,nodeptr->xpos+1,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->ypos++;nodeptr->xpos++;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==6&&MAPFILES.passable(nodeptr->ypos+1,nodeptr->xpos,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->ypos++;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
	else if (random==7&&MAPFILES.passable(nodeptr->ypos+1,nodeptr->xpos-1,nodeptr)==true)
	{MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=0;nodeptr->ypos++;nodeptr->xpos--;MAPFILES.MAPFILEENEMY[nodeptr->ypos][nodeptr->xpos]=nodeptr;}
}


void exe::moveenemy(NodeEnemy * attacker,NodeEnemy * thetarget)
{
	int cont=findpath(attacker,thetarget->xpos,thetarget->ypos,1);	

	//if the target can be reached, get the last move off the enemy stack
	if (cont==0)
	{
		attacker->deletelastmovelist();
	}
	//otherwise brute force move closer
	else
	{
		//the npc can move a maximum of 1 X and 1 Y tile
		//since there are any alternative ways of getting closer to the npc,
		//must check if npc has moved just 1 y so it can do 1 x, but nothing else etc.
		bool movedY=false;
		bool movedX=false;
		bool moved=false;

		int changeX=0;
		int changeY=0;

		if (attacker->ypos>thetarget->ypos)
		{
			if ((thetarget->xpos==attacker->xpos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos,attacker)==true))
			{changeY--;movedY=true;}
			else if (movedY==false)
			{
				if((attacker->xpos>=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos-1,attacker)==true))
				{changeY--;changeX--;moved=true;}
				else if ((attacker->xpos<=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos+1,attacker)==true))
				{changeY--;changeX++;moved=true;}
				else if (attacker->xpos>=thetarget->xpos&&(MAPFILES.passable(attacker->ypos,attacker->xpos-1,attacker)==true))
				{changeX--;moved=true;}
				else if ((attacker->xpos<=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos+1,attacker)==true))
				{changeX++;moved=true;}
				else if ((attacker->ypos>thetarget->ypos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos,attacker)==true))
				{changeY--;moved=true;}
				else if (((attacker->ypos>thetarget->ypos)&&(attacker->xpos>thetarget->ypos))&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos+1,attacker)==true))
				{changeY--;changeX++;moved=true;}
				else if ((attacker->ypos<thetarget->ypos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos-1,attacker)==true))
				{changeY++;changeX--;moved=true;}
				else if (((attacker->xpos<thetarget->xpos)&&(attacker->ypos>thetarget->ypos))&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;moved=true;}
				else if (((attacker->xpos<=thetarget->xpos)&&(attacker->ypos>thetarget->ypos))&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos-1,attacker)==true))
				{changeY--;changeX--;moved=true;}
				else if (((attacker->xpos>=thetarget->xpos)&&(attacker->ypos>=thetarget->ypos))&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;moved=true;}	
				else
				{if (GLOBAL.debugenabled==true)printf("\nmissing move,ey>py|ey=%d,ex=%d,py=%d,px=%d",attacker->ypos,attacker->xpos,thetarget->ypos,thetarget->xpos);}
			}
		}

		else if (attacker->ypos<thetarget->ypos)
		{
			if ((thetarget->xpos==attacker->xpos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos,attacker)==true)&&movedY==false)
			{changeY++;movedY=true;}
			else if (movedY==false)
			{
				if ((attacker->xpos<=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;moved=true;}
				else if ((attacker->xpos>=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos-1,attacker)==true))
				{changeY++;changeX--;moved=true;}
				else if ((attacker->xpos<=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos+1,attacker)==true))
				{changeX++;moved=true;}
				else if ((attacker->xpos>=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos-1,attacker)==true))
				{changeX--;moved=true;}
				else if ((attacker->ypos<thetarget->ypos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos,attacker)==true))
				{changeY++;moved=true;}
				else if ((attacker->xpos>thetarget->xpos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos-1,attacker)==true))
				{changeY--;changeX--;moved=true;}
				else if (((attacker->xpos<=thetarget->xpos)&&(attacker->ypos<thetarget->ypos))&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos+1,attacker)==true))
				{changeY--;changeX++;moved=true;}
				else if (((attacker->xpos>thetarget->xpos)&&(attacker->ypos<thetarget->ypos))&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;moved=true;}	
				else if (((attacker->xpos<=thetarget->xpos)&&(attacker->ypos<=thetarget->ypos))&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;moved=true;}
				else if (((attacker->xpos>=thetarget->xpos)&&(attacker->ypos<=thetarget->ypos))&&(MAPFILES.passable(attacker->ypos,attacker->xpos+1,attacker)==true))
				{changeX++;moved=true;}
				else if (((attacker->xpos==thetarget->xpos)&&(attacker->ypos<=thetarget->ypos))&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos-1,attacker)==true))
				{changeX--;changeY--;moved=true;}
				else
				{if (GLOBAL.debugenabled==true)printf("\nmissing move,ey<py|ey=%d,ex=%d,py=%d,px=%d",attacker->ypos,attacker->xpos,thetarget->ypos,thetarget->xpos);}
			}
		}

		if (attacker->xpos>thetarget->xpos&&moved==false)
		{
			if ((thetarget->ypos==attacker->ypos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos-1,attacker)==true))
			{changeX--;movedX=true;}
			else if (movedY==false&&movedX==false)
			{
				if ((attacker->ypos>=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos-1,attacker)==true))
				{changeY--;changeX--;}
				else if ((attacker->ypos<=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos-1,attacker)==true))
				{changeY++;changeX--;}
				else if ((attacker->ypos>=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos,attacker)==true))
				{changeY--;}
				else if (attacker->xpos<=thetarget->xpos&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos,attacker)==true))
				{changeY++;}
				else if ((attacker->xpos>=thetarget->xpos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos-1,attacker)==true))
				{changeX--;}
				else if ((attacker->ypos>=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos+1,attacker)==true))
				{changeY--;changeX++;}
				else if (((attacker->xpos>=thetarget->xpos)&&(attacker->ypos==thetarget->ypos))&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos,attacker)==true))
				{changeY++;}
				else
				{if (GLOBAL.debugenabled==true)printf("\nmissing move,ex>px,ey=%d,ex=%d,py=%d,px=%d",attacker->ypos,attacker->xpos,thetarget->ypos,thetarget->xpos);}
			}
		}

		else if (attacker->xpos<thetarget->xpos&&moved==false)
		{
			if ((thetarget->ypos==attacker->ypos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos+1,attacker)==true)&&movedX==false)
			{changeX++;movedX=true;}
			else if (movedY==false&&movedX==false)
			{
				if ((attacker->ypos<=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;}
				else if ((attacker->ypos>=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos+1,attacker)==true))
				{changeY--;changeX--;}
				else if (attacker->xpos<=thetarget->xpos&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos,attacker)==true))
				{changeY++;}
				else if ((attacker->ypos>=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos-1,attacker->xpos,attacker)==true))
				{changeY--;}
				else if ((attacker->xpos<thetarget->xpos)&&(MAPFILES.passable(attacker->ypos,attacker->xpos+1,attacker)==true))
				{changeX++;}
				else if ((attacker->ypos<=thetarget->ypos)&&(MAPFILES.passable(attacker->ypos+1,attacker->xpos+1,attacker)==true))
				{changeY++;changeX++;}
				else
				{if (GLOBAL.debugenabled==true)printf("\nmissing move,ex<px|ey=%d,ex=%d,py=%d,px=%d",attacker->ypos,attacker->xpos,thetarget->ypos,thetarget->xpos);}
			}		
		}	
		if (changeY<-1||changeY>1||changeX<-1||changeX>1)
		{
			printf("\nERROR, brute force non adjacency");
		}
		else
		{
			MAPFILES.MAPFILEENEMY[attacker->ypos][attacker->xpos]=NULL;
			attacker->ypos+=changeY;attacker->xpos+=changeX;
			MAPFILES.MAPFILEENEMY[attacker->ypos][attacker->xpos]=attacker;
		}
	}
}



void exe::inventoryhandle(NodeObject * newptr)
{
	int nid=0;
	char temp[205];temp[0]=0;

	//armour
	if (newptr->type==T_HELMET)
	{
		nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (EQUIPMENT.HELM.id!=0)
		{
			//swap items maybe			
			return;
		}
		else
		{
			EQUIPMENT.HELM=INFOS.ARMSTOREPTR[nid];
			helditems.deleteNode(newptr);
			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
			CONSOLE.pushtext(false,3,temp);
			return;	
		}
	}
	else if (newptr->type==T_CHEST)
	{
		nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (EQUIPMENT.CHEST.id!=0)
		{
			//swap items maybe			
			return;
		}
		else
		{
			EQUIPMENT.CHEST=INFOS.ARMSTOREPTR[nid];
			helditems.deleteNode(newptr);
			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
			CONSOLE.pushtext(false,3,temp);
			return;	
		}
	}
	else if (newptr->type==T_LEGS)
	{
		nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (EQUIPMENT.LEGS.id!=0)
		{
			//swap items maybe			
			return;
		}
		else
		{
			EQUIPMENT.LEGS=INFOS.ARMSTOREPTR[nid];
			helditems.deleteNode(newptr);
			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
			CONSOLE.pushtext(false,3,temp);
			return;	
		}
	}

	else if (newptr->type==T_SHOES)
	{
		nid=newptr->id;
		while (nid>=100)
			nid-=100;
		if (EQUIPMENT.SHOES.id!=0)
		{
			//swap items maybe			
			return;
		}
		else
		{
			EQUIPMENT.SHOES=INFOS.ARMSTOREPTR[nid];
			helditems.deleteNode(newptr);
			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
			CONSOLE.pushtext(false,3,temp);
			return;	
		}
	}

	//potion
	else if (newptr->type==T_HEALTHPOTION)
	{
		int amountheal=newptr->amount;
		helditems.deleteNode(newptr);
		GLOBAL.loopswitch=LS_NORMAL;
		int left=PLAYER.maxhealth-PLAYER.health;
		if (left>amountheal)
			left=amountheal;

		char temp2[50];
		sprintf(temp2,"%d",left);
		strcpy(temp,"The potion heals ");
		strcat(temp,temp2);
		strcat(temp," health");
		CONSOLE.pushtext(false,2,temp);

		PLAYER.health+=left;
		return;
	}
	else if (newptr->type==T_MAGICPOTION)
	{
		int amountheal=newptr->amount;
		helditems.deleteNode(newptr);
		GLOBAL.loopswitch=LS_NORMAL;
		int left=PLAYER.maxmagic-PLAYER.magic;
		if (left>amountheal)
			left=amountheal;

		char temp2[50];
		sprintf(temp2,"%d",left);
		strcpy(temp,"The potion refreshes ");
		strcat(temp,temp2);
		strcat(temp," magic");
		CONSOLE.pushtext(false,2,temp);

		PLAYER.magic+=left;
		return;
	}
	else if (newptr->type==T_STAMINAPOTION)
	{
		int amountheal=newptr->amount;
		helditems.deleteNode(newptr);
		GLOBAL.loopswitch=LS_NORMAL;
		int left=PLAYER.maxstamina-PLAYER.stamina;
		if (left>amountheal)
			left=amountheal;

		char temp2[50];
		sprintf(temp2,"%d",left);
		strcpy(temp,"The potion heals ");
		strcat(temp,temp2);
		strcat(temp," stamina");
		CONSOLE.pushtext(false,2,temp);

		PLAYER.stamina+=left;
		return;
	}
	else if (newptr->type==T_FULLPOTION)
	{
		int amountheal=newptr->amount;
		GLOBAL.loopswitch=LS_NORMAL;
		int left=PLAYER.maxhealth-PLAYER.health;
		if (left>amountheal)
			left=amountheal;

		GLOBAL.loopswitch=LS_NORMAL;
		int left2=PLAYER.maxmagic-PLAYER.magic;
		if (left2>amountheal)
			left2=amountheal;

		GLOBAL.loopswitch=LS_NORMAL;
		int left3=PLAYER.maxstamina-PLAYER.stamina;
		if (left3>amountheal)
			left3=amountheal;

		helditems.deleteNode(newptr);

		char temp2[50];
		sprintf(temp2,"%d",left);
		strcpy(temp,"The potion heals ");
		strcat(temp,temp2);
		strcat(temp," health");
		CONSOLE.pushtext(false,2,temp);

		PLAYER.health+=left;

		sprintf(temp2,"%d",left2);
		strcpy(temp,"The potion refreshes ");
		strcat(temp,temp2);
		strcat(temp," magic");
		CONSOLE.pushtext(false,2,temp);

		PLAYER.magic+=left2;

		sprintf(temp2,"%d",left3);
		strcpy(temp,"The potion heals ");
		strcat(temp,temp2);
		strcat(temp," stamina");
		CONSOLE.pushtext(false,2,temp);

		PLAYER.stamina+=left3;

		return;
	}


	else if (isweapon(newptr->type))
	{
		nid=newptr->id-200;

		if (EQUIPMENT.RARM.type==T_FISTS&&EQUIPMENT.LARM.type==T_FISTS)
		{		
			int tempp=INFOS.WEPSTOREPTR[newptr->id-200]->strengthReq;
			if (GLOBAL.debugenabled==true)
				printf("\n1ps=%d,ws=%d",PLAYERSTATS.strength,tempp);

			EQUIPMENT.RARM=INFOS.WEPSTOREPTR[nid];

			helditems.deleteNode(newptr);

			//playsound
			EXEC.loadSound(SND.arming);

			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->name);
			CONSOLE.pushtext(false,3,temp);

			if (tempp>PLAYERSTATS.strength)
			{CONSOLE.pushtext(false,3,TEXT_PLAYER_STRENGTH);
			CONSOLE.pushtext(false,3,TEXT_PLAYER_BONUS);}

			if (EQUIPMENT.RARM.type==T_TORCHWEP)
			{CONSOLE.pushtext(false,3,TEXT_ITEM_TORCH);}

			return;
		}
		else if (EQUIPMENT.RARM.type!=T_FISTS&&EQUIPMENT.LARM.type==T_FISTS)
		{
			if (INFOS.WEPSTOREPTR[newptr->id-200]->oneHanded)	
			{CONSOLE.pushtext(false,0,TEXT_ITEM_TWOHAND);GLOBAL.loopswitch=LS_NORMAL;return;}
			else	if (INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->oneHanded)	
			{CONSOLE.pushtext(false,0,TEXT_ITEM_TWOHANDARM);GLOBAL.loopswitch=LS_NORMAL;return;}

			int tempp=INFOS.WEPSTOREPTR[newptr->id-200]->strengthReq*2;
			if (GLOBAL.debugenabled==true)printf("\n2ps=%d,ws=%d",PLAYERSTATS.strength,tempp);
			EQUIPMENT.LARM=INFOS.WEPSTOREPTR[nid];
			helditems.deleteNode(newptr);

			//playsound
			EXEC.loadSound(SND.arming);

			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->name);
			CONSOLE.pushtext(false,3,temp);

			if (tempp>PLAYERSTATS.strength)
			{CONSOLE.pushtext(false,3,TEXT_PLAYER_STRENGTH);
			CONSOLE.pushtext(false,3,TEXT_PLAYER_BONUS);}

			if (EQUIPMENT.LARM.type==T_TORCHWEP)
			{CONSOLE.pushtext(false,3,TEXT_ITEM_TORCH);}

			return;
		}
		else if (EQUIPMENT.RARM.type==T_FISTS&&EQUIPMENT.LARM.type!=T_FISTS)
		{
			if (INFOS.WEPSTOREPTR[newptr->id-200]->oneHanded)	
			{CONSOLE.pushtext(false,0,TEXT_ITEM_TWOHAND);GLOBAL.loopswitch=LS_NORMAL;return;}

			else if (INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->oneHanded)	
			{CONSOLE.pushtext(false,0,TEXT_ITEM_TWOHANDARM);GLOBAL.loopswitch=LS_NORMAL;return;}

			int tempp=INFOS.WEPSTOREPTR[newptr->id-200]->strengthReq*2;
			if (GLOBAL.debugenabled==true)printf("\n3ps=%d,ws=%d",PLAYERSTATS.strength,tempp);
			EQUIPMENT.RARM=INFOS.WEPSTOREPTR[nid];

			helditems.deleteNode(newptr);

			//playsound
			EXEC.loadSound(SND.arming);

			if (tempp>PLAYERSTATS.strength)
			{CONSOLE.pushtext(false,0,TEXT_PLAYER_STRENGTHTWO);CONSOLE.pushtext(false,0,TEXT_PLAYER_BONUS);return;}

			strcpy(temp,"Equipped ");
			strcat(temp,INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->name);
			CONSOLE.pushtext(false,3,temp);

			if (EQUIPMENT.RARM.type==T_TORCHWEP)
			{CONSOLE.pushtext(false,3,TEXT_ITEM_TORCH);}

			return;
		}
		else if (EQUIPMENT.RARM.id!=200&&EQUIPMENT.LARM.id!=200)
		{
			if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
			{CONSOLE.pushtext(false,0,TEXT_INV_FULL);GLOBAL.loopswitch=LS_NORMAL;return;} 
			else
				CONSOLE.pushtext(false,0,TEXT_PLAYER_ARM);
			return;
		}
	}
}


void exe::equiphandle(armstore * newptr)
{
	int nid=newptr->id;
	nid-=500;
	char temp[205];temp[0]=0;

	if (newptr->type==T_HELMET)
	{
		helditems.insertNode()->setvalues(1,EQUIPMENT.HELM.id,-1,-1);
		strcpy(temp,"Unequipped ");
		strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
		CONSOLE.pushtext(false,3,temp);
		EQUIPMENT.HELM.init();
		return;		
	}

	else if (newptr->type==T_CHEST)
	{
		helditems.insertNode()->setvalues(1,EQUIPMENT.CHEST.id,-1,-1);
		strcpy(temp,"Unequipped ");
		strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
		CONSOLE.pushtext(false,3,temp);
		EQUIPMENT.CHEST.init();
		return;
	}
	else if (newptr->type==T_LEGS)
	{
		helditems.insertNode()->setvalues(1,EQUIPMENT.LEGS.id,-1,-1);
		strcpy(temp,"Unequipped ");
		strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
		CONSOLE.pushtext(false,3,temp);
		EQUIPMENT.LEGS.init();
	}

	else if (newptr->type==T_SHOES)
	{
		helditems.insertNode()->setvalues(1,EQUIPMENT.SHOES.id,-1,-1);
		strcpy(temp,"Unequipped ");
		strcat(temp,INFOS.ARMSTOREPTR[nid]->name);
		CONSOLE.pushtext(false,3,temp);
		EQUIPMENT.SHOES.init();
		return;
	}
}


void exe::weaponhandle(wepstore * newptr,bool islefthand)
{
	int nid=newptr->id;
	nid-=200;
	char temp[205];temp[0]=0;

	if (islefthand==true)
	{
		helditems.insertNode()->setvalues(1,EQUIPMENT.LARM.id,-1,-1);
		strcpy(temp,"Unequipped ");
		strcat(temp,INFOS.WEPSTOREPTR[nid]->name);
		CONSOLE.pushtext(false,3,temp);
		EQUIPMENT.LARM.init();
		//give 'fist' back
		EQUIPMENT.LARM=INFOS.WEPSTOREPTR[0];
		return;
	}
	else
	{
		helditems.insertNode()->setvalues(1,EQUIPMENT.RARM.id,-1,-1);
		strcpy(temp,"Unequipped ");
		strcat(temp,INFOS.WEPSTOREPTR[nid]->name);
		CONSOLE.pushtext(false,3,temp);
		EQUIPMENT.RARM.init();
		//give 'fist' back
		EQUIPMENT.RARM=INFOS.WEPSTOREPTR[0];
		return;
	}
}

//for health bar and dungeon
float exe::getlightlevel(int a,int b,bool darken)
{
	float amount=0;
	if (MAPFILES.currentmap->darknessLevel<=0)
	{
		if (MAPFILES.RAYTRACE[a][b]!=0)
		{
			amount=1-((float)MAPFILES.RAYTRACE[a][b]*.1);
		}
		else
			amount=1-(ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus])*.1;
	}
	else
	{
		if (MAPFILES.RAYTRACE[a][b]!=0)
		{
			amount=1-((float)MAPFILES.RAYTRACE[a][b]*.1);
		}
		else
		{
			//show terrain on half darkness, but still black out enemies
			if (darken==true)
				amount=1-(ANIMATION.LIGHTLEVELTABLE[MAPFILES.currentmap->darknessLevel*2]*.2);
			else
				amount=1-(ANIMATION.LIGHTLEVELTABLE[MAPFILES.currentmap->darknessLevel*2]*.1);

		}
	}
	return amount;
}

void exe::loaddungeonmapfile(char * filename)
{
	FILE * dungeonmap=NULL;
	char newpath[200];newpath[0]=0;
	strcpy(newpath,"Data/Savegames/");
	strcat(newpath,filename);
	_fopen_s(&dungeonmap,newpath,"r");
	if (dungeonmap==NULL)
	{printf("\nNo Save game!");EXEC.quit("dungeonmap");}
	int MW=0,MH=0;
	fscanf_s(dungeonmap,"%d %d",&MW,&MH);
	MAPFILES.loadMAPFILES(MW,MH,dungeonmap);

	_fclose(dungeonmap);
}



void exe::savedungeonmapfile(char * filename)
{
	FILE * dungeonmap=NULL;
	char newpath[200];newpath[0]=0;
	strcpy(newpath,"Data/Savegames/");
	strcat(newpath,filename);
	_fopen_s(&dungeonmap,newpath,"w");
	if (dungeonmap==NULL)
	{printf("\nNo Save game!");EXEC.quit("dungeonmap");}
	fprintf(dungeonmap,"%d %d ",MAPFILES.emapwidth(),MAPFILES.emapheight());
	for (int a=0;a<MAPFILES.emapheight();a++)
	{
		for (int b=0;b<MAPFILES.emapwidth();b++)
		{fprintf(dungeonmap,"%d ",MAPFILES.MAPFILE[a][b]);}
		fprintf(dungeonmap,"\n");
	}
	_fclose(dungeonmap);
}




void exe::savefunction()
{
	PLAYER.lockmove=true;
	char * saver;saver = new char[10000];
	saver[0]=0;
	strcpy(saver,"");

	if (HCVARS.version==NULL)
	{
		myfree(&saver);
		EXEC.quit("savegames");
	}

	if (MAPFILES.currentmap->type==501)
	{
		savedungeonmapfile("dm.cfg");
	}

	char tempsave[500];
	char * temp;

	sprintf(saver,"%s %d",HCVARS.version,MAPFILES.currentmap->id);

	//save the view resolution of the game, currently it is the menu res which
	//is different, so pop the values, and copy
	int xv,yv;
	ANIMATION.popview(&xv,&yv);
	sprintf(tempsave," VIEW %d %d",xv,yv);strcat(saver,tempsave);
	//might as well change the res here, as goes straight back to the game
	MAPFILES.TERRAINLOSinit(xv,yv);

	temp=PLAYER.savevals("PLAY");
	strcat(saver,temp);
	myfree(&temp);

	temp=PLAYERSTATS.savevals("PLAYSTATS");
	strcat(saver,temp);
	myfree(&temp);

	temp=GLOBAL.savevals("GLO");
	strcat(saver,temp);
	myfree(&temp);

	temp=MAPFILES.savevals("CMAP");
	strcat(saver,temp);
	myfree(&temp);

	temp=SPELL.savevals("SP");
	strcat(saver,temp);
	myfree(&temp);

	temp=DUNGEON.savevals("DUN");
	strcat(saver,temp);
	myfree(&temp);

	temp=ANIMATION.savevals("ANIM");
	strcat(saver,temp);
	myfree(&temp);

	if (mapnpcs.headptr!=NULL)
	{
		LinkedListNode<mapenemieslist> * enemyz=mapnpcs.headptr; 
		while (enemyz!=NULL)
		{
			//save mapnpc even if there arent any enemies to avoid borking up the stack
			if (enemyz->value->mapenemies.headptr!=NULL)
			{
				char * temp=enemyz->value->saveenemy("mapnpc");
				strcat(saver,temp);
				myfree(&temp);
			}
			else
			{
				strcat(saver," mapnpc 0 ");
			}
			enemyz=enemyz->nextptr;
		}
	}

	if (NPC.headptr!=NULL)
	{
		LinkedListNode<NodeEnemy> * enemyz=NPC.headptr; 
		while (enemyz!=NULL)
		{
			char * temp=enemyz->value->saveenemy("npc");
			strcat(saver,temp);
			myfree(&temp);
			enemyz=enemyz->nextptr;
		}
	}


	if (grounditems.headptr!=NULL)
	{
		LinkedListNode<NodeObject> * grounditemz=grounditems.headptr;
		while (grounditemz!=NULL)
		{
			char * temp=grounditemz->value->saveobject("gi");
			strcat(saver,temp);
			myfree(&temp);

			grounditemz=grounditemz->nextptr;
		}
	}

	if (helditems.headptr!=NULL)
	{
		LinkedListNode<NodeObject> * invitemz=helditems.headptr;
		while (invitemz!=NULL)
		{
			temp=invitemz->value->saveobject("ii");
			strcat(saver,temp);
			myfree(&temp);

			invitemz=invitemz->nextptr;
		}
	}


	temp=CONSOLE.savevals("ca");
	strcat(saver,temp);
	myfree(&temp);

	//armours
	temp=EQUIPMENT.savevals("as");
	strcat(saver,temp);
	myfree(&temp);


	//map stacks
	temp=MAPFILES.mapSTACK.savemapSTACK("ps");
	strcat(saver,temp);
	myfree(&temp);

	int num=0;
	for (int a=0;a<100;a++)
	{
		if (PLAYER.hasSpellTable[a])
			num++;
	}


	sprintf(tempsave," gs %d",num);
	strcat(saver,tempsave);

	for (int a=0;a<100;a++)
	{
		if (PLAYER.hasSpellTable[a])	
		{
			sprintf(tempsave," %d %d",a,PLAYER.hasSpellTable[a]);strcat(saver,tempsave);	
		}
	}

	FILE * savefile=NULL;
	char savename[100];
	strcpy(savename,"Data/Savegames/");
	strcat(savename,PLAYER.name);
	strcat(savename,".dat");
	_fopen_s(&savefile,savename,"w");
	if (savefile==NULL)
	{
		CONSOLE.pushtext(true,0,TEXT_ERROR_SAVEGAME);
		delete[] saver;
		return;
	}
	fprintf(savefile,"%s",saver);
	_fclose(savefile);


	CONSOLE.pushtext(true,3,"Saved Game");
	delete[] saver;
	PLAYER.lockmove=false;
}


void exe::loadfunction(char * name)
{
	PLAYER.lockmove=true;
	//get input

	FILE * loader=NULL;
	char loadname[100];
	strcpy(loadname,"Data/Savegames/");
	strcat(loadname,name);
	strcat(loadname,".dat");
	_fopen_s(&loader,loadname,"r");
	if (loader==NULL)
	{
		printf("\nno save file!");
		return;
	}

	//get version from save file of save file
	char temp[100];temp[0]=0;
	fscanf_s(loader,"%s",temp,98);
	if (strcmp(HCVARS.version,temp)!=0)
	{printf("\nIncorrect version save file!");return;}

	//game is currently not running
	MAPFILES.lastx=0;MAPFILES.lasty=0;
	GLOBAL.runninggame=0;

	//load databases, init variables
	EXEC.initgame();

	//load the map
	int id=0;
	fscanf_s(loader,"%d",&id);
	EXEC.loadMap(INFOS.MAPSTOREPTR[id]);

	temp[0]=0;
	int current=0;

	//main loop
	while (fscanf_s(loader,"%s",temp,100)==1)
	{
		if (strcmp(temp,"ca")==0)
		{
			CONSOLE.loadvals(loader,&current);
		}

		else if (strcmp(temp,"VIEW")==0)
		{
			int vw,vy;
			fscanf_s(loader,"%d %d",&vw,&vy);
			MAPFILES.TERRAINLOSinit(vw,vy);
		}

		else if (strcmp(temp,"mapnpc")==0)
		{
			mapnpcs.insertNode()->loadenemy(loader);
		}

		else if (strcmp(temp,"PLAY")==0)
		{
			PLAYER.loadvals(loader);
		}

		else if (strcmp(temp,"PLAYSTATS")==0)
		{
			PLAYERSTATS.loadvals(loader);
		}

		else if (strcmp(temp,"GLO")==0)
		{
			GLOBAL.loadvals(loader);
		}

		else if (strcmp(temp,"CMAP")==0)
		{
			MAPFILES.loadvals(loader);
		}

		else if (strcmp(temp,"SP")==0)
		{
			SPELL.loadvals(loader);
		}

		else if (strcmp(temp,"DUN")==0)
		{
			DUNGEON.loadvals(loader);
		}

		else if (strcmp(temp,"npc")==0)
		{
			NPC.insertNode()->loadenemy(loader,true);
		}

		else if (strcmp(temp,"gi")==0)
		{
			grounditems.insertNode()->loadobject(loader);

		}
		else if (strcmp(temp,"ii")==0)
		{
			helditems.insertNode()->loadobject(loader);
		}

		else if (strcmp(temp,"as")==0)
		{
			EQUIPMENT.loadvals(loader);
		}

		else if (strcmp(temp,"ps")==0)
		{
			MAPFILES.mapSTACK.loadmapSTACK(loader);
		}

		else if (strcmp(temp,"ANIM")==0)
		{
			ANIMATION.loadvals(loader);
		}

		else if (strcmp(temp,"gs")==0)
		{
			for (int a=0;a<100;a++)
				PLAYER.hasSpellTable[a]=false;

			int num=0;
			int boolint=0;
			fscanf_s(loader," %d",&num);
			for (int a=0;a<num;a++)
			{
				int b=0;
				fscanf_s(loader," %d",&b);
				fscanf_s(loader," %d",&boolint);
				if (boolint==0)
					PLAYER.hasSpellTable[b]=false;
				else
					PLAYER.hasSpellTable[b]=true;
			}			
		}
		else
			break;
	}

	_fclose(loader);

	loader=NULL;

	if (GLOBAL.isfullscreen==true)
		initmode();
	GLOBAL.loadconfig();
	GLOBAL.loopswitch=LS_PASS;
	//make sure that player is on map
	MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
	//make sure shop items are loaded
	EXEC.initshop();
	//delete all pushed enemies in case in dungeon
	GLOBAL.runninggame=1;
	CONSOLE.pushtext(true,3,"Loaded Game");	
	//		delete[] savefile;
	PLAYER.lockmove=false;
}


void exe::executecommand(void)
{
	variablePointers.insertNode("enemy")->ptr=NULL;
	variablePointers.insertNode("friend")->ptr=NULL;
	variablePointers.insertNode("npc")->ptr=NULL;
	variablePointers.insertNode("gi")->ptr=NULL;
	variablePointers.insertNode("hi")->ptr=NULL;
	variablePointers.insertNode("si")->ptr=NULL;

	strcpy(CONSOLE.prevconsole,CONSOLE.currentconsole);
	char one[100];
	one[0]=' ';
	char two[100]="-";
	char three[100]="-";
	char sp1[100];
	int temp=0;
	if (strlen(CONSOLE.currentconsole)!=0)
	{
		char * haxptr=&CONSOLE.currentconsole[0];
		while (*haxptr==32)
			haxptr++;

		sscanf_s(haxptr,"%s",one,98);
	}
	else
		one[0]=0;
	one[strlen(one)]=0;
	//	int length=(int)strlen(CONSOLE.currentconsole);
	int a=0;
	while (one[a]!=0)
	{
		if (one[a]>='A'&&one[a]<='Z')
			one[a]+=32;
		a++;
	}
	//char temp2[200];
	//strcpy(temp2,consolez.find(one)->first.c_str());
	//sprintf(temp2,"%d",a);
	int consoleid=-1;

	if (consolez[one]!=0)
		consoleid=(int)consolez[one]->ptr;
	if (consoleid==-1&&one[0]==0)
		return;
	if (consoleid==-1)
	{
		if (strcmp(one,"lol")==0)
			CONSOLE.pushtext(true,0,"(thats) hax");
		else
			CONSOLE.pushtext(true,0,TEXT_ERROR_SYNTAX);
		return;
	}

	if (consoleid>=100&&consoleid<199)
	{
		if (consoleid==100)
		{EXEC.quit("");}
		else if (consoleid==101)
		{//dbpl
			strcpy(one,"X=");
			sprintf(two,"%d",PLAYER.posx);
			strcat(one,two);
			strcat(one," Y=");
			sprintf(two,"%d",PLAYER.posy);
			strcat(one,two);
			CONSOLE.pushtext(true,0,one);
			return;
		}
		else if (consoleid==102)
		{//save
			savefunction();
			return;
		}
		else if (consoleid==103)
		{//load
			loadfunction(PLAYER.name);
			GLOBAL.loopswitch=LS_INGAMEMENU;
			return;
		}
		else if (consoleid==104)
		{
			spawnenemy();
		}

	}
	else if (consoleid>=200&&consoleid<=299)
	{
		sscanf_s(CONSOLE.currentconsole,"%*s %s",two,98);
		a=0;
		while (two[a]!=0)
		{
			if (two[a]>=65&&two[a]<=90)
				two[a]+=32;
			a++;
		}
		two[strlen(two)]=0;

		if (consoleid==299)
		{
			int tempo=-1;
			if (two[0]=='1')
				tempo=1;
			else if (two[0]=='0')
				tempo=0;
			if (two[0]=='-'||tempo==-1)
				CONSOLE.pushtext(true,3,"CC X(0/1):Toggles cheat mode");
			else
			{
				if (tempo==0)
				{CONSOLE.pushtext(true,3,"Cheat mode OFF");CONSOLE.consolecheats=false;}
				else if (tempo==1)
				{CONSOLE.pushtext(true,3,"Cheat mode ON");CONSOLE.consolecheats=true;}
			}
		}

		if (consoleid==200)
		{
			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}
			if (two[0]=='-')
				CONSOLE.pushtext(true,3,"DBPV X:Prints variable X");
			else
			{
				if (variablePointers[two]!=NULL)
				{
					strcpy(one,"var=");
					sprintf(sp1,"%d",*(int*)variablePointers[two]->ptr);
					strcat(one,sp1);
					CONSOLE.pushtext(true,0,one);
				}
				else
					CONSOLE.pushtext(true,0,TEXT_ERROR_VARIABLE);
			}
		}
		else if (consoleid==201)
		{
			variablePointers["npc"]->ptr = (void*) &NPC;

			variablePointers["gi"]->ptr = (void*) &grounditems;
			variablePointers["hi"]->ptr = (void*) &helditems;
			variablePointers["si"]->ptr = (void*) &shopitems;


			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}
			if (two[0]=='-')
				CONSOLE.pushtext(true,3,"DBPN X:Prints Linked List/Node X");
			else
			{
				if (strcmp(two,"npc")==0)
				{
					LinkedListNode<NodeEnemy> * newptr=NPC.headptr;
					CONSOLE.pushtext(true,1,"--------");
					while (newptr!=NULL)
					{
						char tempo[100];tempo[0]=0;
						char tempoz[20];tempoz[0]=0;
						strcpy(tempo,"ID=");
						sprintf(tempoz,"%d",newptr->value->id);
						strcat(tempo,tempoz);

						strcat(tempo," STR=");
						strcat(tempo,newptr->value->str);

						strcat(tempo," X=");
						sprintf(tempoz,"%d",newptr->value->xpos);
						strcat(tempo,tempoz);

						strcat(tempo," Y=");
						sprintf(tempoz,"%d",newptr->value->ypos);
						strcat(tempo,tempoz);

						CONSOLE.pushtext(true,2,tempo);

						newptr=newptr->nextptr;
					}

					char tempo[100];tempo[0]=0;
					char tempoz[20];tempoz[0]=0;
					strcpy(tempo,"Count=");
					sprintf(tempoz,"%d",NPC.getCount());
					strcat(tempo,tempoz);

					CONSOLE.pushtext(true,3,tempo);
					CONSOLE.pushtext(true,1,"--------");
				}
				else
					CONSOLE.pushtext(true,0,TEXT_ERROR_VARIABLE);
			}
		}

		else if (consoleid==202)
		{
			CONSOLE.pushtext(true,3,"--Help--");
			CONSOLE.pushtext(true,2,"CC=Toggles Cheats");
			CONSOLE.pushtext(true,2,"quit/rage=Quit, save/load for save/load");
			CONSOLE.pushtext(true,2,"clear=Clears the console and game history");
			CONSOLE.pushtext(true,2,"DBPL=Prints the current location of the player");
			CONSOLE.pushtext(true,2,"RESTART=Restarts game");
			CONSOLE.pushtext(true,1,"DBTM=Debug game tiles");
			CONSOLE.pushtext(true,1,"DBPV=Prints a variable");
			CONSOLE.pushtext(true,1,"DBCV=Changes a variable");
			CONSOLE.pushtext(true,1,"DBFC=Forces creation of an object");
			CONSOLE.pushtext(true,1,"DBNPC=Forces creation of an NPC DBSE=spawn an enemy");
			CONSOLE.pushtext(true,1,"DBCVT=Change number of displayed tiles around Player");
			CONSOLE.pushtext(true,3,"Type above commands in for more info");
		}

		else if (consoleid==203)
		{
			if (strcmp(two,"1")==0)
			{
				EXEC.initgame();
				GLOBAL.loopswitch=LS_PASS;CONSOLE.pushtext(false,0,TEXT_WELCOME);GLOBAL.runninggame=1;}
			else

			{
				CONSOLE.pushtext(true,3,"Restart 1=restart");
			}
		}


		else if (consoleid==204)
		{
			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}
			if (strcmp(two,"0")==0)
				GLOBAL.debugTiles=DTT_NONE;
			else if (strcmp(two,"1")==0)
				GLOBAL.debugTiles=DTT_PATHFIND; 
			else if (strcmp(two,"2")==0)
				GLOBAL.debugTiles=DTT_RAYTRACE; 
			else
			{
				CONSOLE.pushtext(true,3,"DBT =Change tile debugging");
				CONSOLE.pushtext(true,3,"DBT 0=No debugging");
				CONSOLE.pushtext(true,3,"DBT 1=Path Finding");
				CONSOLE.pushtext(true,3,"DBT 2=Ray Trace");
			}
		}

		else if (consoleid==207)
		{
			if ((strcmp(two,"0")==0)||(strcmp(two,"1")==0))
			{
				for (a=0;a<15;a++)
					strcpy(CONSOLE.consolearray[a],"");
			}

			if ((strcmp(two,"0")==0)||(strcmp(two,"2")==0))
			{
				for (a=0;a<5;a++)
					strcpy(CONSOLE.textarray[a],"");
			}

			if ((strcmp(two,"0")!=0)&&(strcmp(two,"1")!=0)&&(strcmp(two,"2")!=0))
				CONSOLE.pushtext(true,3,"CLEAR (0/1/2) 0=all 1=console 2=history");
		}


		else if (consoleid>=300&&consoleid<399)
		{
			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}
			sscanf_s(CONSOLE.currentconsole,"%*s %s %s",two,98,three,98);
			a=0;
			while (two[a]!=0)
			{
				if (two[a]>=65&&two[a]<=90)
					two[a]+=32;

				a++;
			}
			a=0;
			while (three[a]!=0)
			{
				if (three[a]>=65&&three[a]<=90)
					three[a]+=32;

				a++;
			}

			if (consoleid==300)
			{
				if (two[0]=='-'||three[0]=='-')
					CONSOLE.pushtext(true,3,"DBCV X Y:Changes variable X to Y");
				else if (atoi(three)<0)
					CONSOLE.pushtext(true,1,"New Var is too small");
				else if (atoi(three)>10000000)
					CONSOLE.pushtext(true,1,"New Var is too big");	
				else
				{
					if (variablePointers[two]!=NULL)
					{
						strcpy(one,"PrevVar=");
						sprintf(sp1,"%d",*(int*)variablePointers[two]->ptr);
						strcat(one,sp1);
						strcat(one," NewVar=");

						if (three[0]<'0'||three[0]>'9')
						{
							a=0;

							if (variablePointers.searchNode(three)!=variablePointers.getlastnode())
							{
								int * sas=(int*)variablePointers[three]->ptr;
								temp=*sas;
							}
						}
						else
							temp=atoi(three);
						int cpps=0;
						if (strcmp(two,"p.px")==0||strcmp(two,"p.py")==0)
						{cpps=1;MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;}
						*(int*)variablePointers[two]->ptr=temp;
						if (cpps==1)
						{
							MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
						}
						sprintf(sp1,"%d",*(int*)variablePointers[two]->ptr);
						strcat(one,sp1);
						CONSOLE.pushtext(true,0,one);
					}
					else
						CONSOLE.pushtext(true,0,TEXT_ERROR_VARIABLE);
				}
			}
		}

		else if (consoleid==301)
		{
			//dbfc enemy 102
			//variablePointers["spell"] = (void*) &spellz;

			variablePointers["gi"]->ptr = (void*) &grounditems;
			variablePointers["hi"]->ptr = (void*) &helditems;
			variablePointers["si"]->ptr = (void*) &shopitems;

			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}

			temp=atoi(three);

			if (two[0]=='-'||three[0]=='-')
				CONSOLE.pushtext(true,3,"DBFC X Y:Creates numbered type Y of type X");
			else
			{
				bool success=false; 

				if (strcmp(two,"npc")==0&&(temp>=100&&temp<=200))
				{CONSOLE.pushtext(true,0,"Please use DBNPC for creation of NPC's");}
				else if (strcmp(two,"gi")==0&&(temp>=200&&temp<=499))
				{success=grounditems.insertNode()->setvalues(1,temp,PLAYER.posx,PLAYER.posy);}
				else if (strcmp(two,"hi")==0&&((temp>=200&&temp<=299&&temp<=INFOS.WEPSTORE.getCount()+199)||(temp>=300&&temp<=400)))
					givehelditems(temp);
				else if (strcmp(two,"si")==0&&(temp>=200&&temp<=99&&temp<=INFOS.WEPSTORE.getCount()+199))
				{success=shopitems.insertNode()->setvalues(1,temp,0,0);}
				else
					CONSOLE.pushtext(true,0,TEXT_ERROR_POINTER);
			}
		}


		else if (consoleid==303)
		{
			//dbfc enemy 102
			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}

			int temp2=atoi(three);
			temp=atoi(two);

			if (temp2<0||temp2>2)
				CONSOLE.pushtext(true,3,"Invalid Faction");
			else if (two[0]=='-'||three[0]=='-')
				CONSOLE.pushtext(true,3,"DBNPC X Y:Create NPC of type X, faction Y");
			else
			{
				NodeEnemy * newptr=NPC.insertNode();
				newptr->setvalues(temp,-1,-1,true);

				newptr->faction=temp2;
			}
		}



		else if (consoleid==302)
		{

			if (CONSOLE.consolecheats==false)
			{CONSOLE.pushtext(true,3,"This is a cheat command, CC to enable");return;}

			temp=atoi(three);

			if (two[0]=='-'||three[0]=='-')
				CONSOLE.pushtext(true,3,"DBCVT X Y:Change number of viewable tiles around player");
			else
			{
				int t1=atoi(two);
				int t2=atoi(three);
				if (t1<=0||t2<=0)
				{CONSOLE.pushtext(true,1,"Invalid parameters, must be >0");return;}

				MAPFILES.TERRAINLOSinit(t1,t2);		
			}
		}
	}
}


void exe::popposition(int * y, int * x)
{
	CONSOLE.pushtext(true,0,"Pop Position");
	mapstax * hax= MAPFILES.mapSTACK.pop();
	if (hax !=NULL)
	{
		*y=hax->y;
		*x=hax->x;
		delete hax;
	}
	else
	{printf("\nNo elements to pop");return;}
}


void exe::pushposition(int y, int x)
{
	CONSOLE.pushtext(true,0,"Push Position");
	MAPFILES.mapSTACK.push(MAPFILES.currentmap->id,x,y);
}


void exe::pushenemies()
{
	//NPC->mapenemies

	CONSOLE.pushtext(true,0,"Push Enemies");

	mapenemieslist * thisobj=mapnpcs.insertNode();

	LinkedListNode<NodeEnemy> * newptr=NPC.headptr;
	while (newptr!=NULL)
	{
		MAPFILES.MAPFILEENEMY[newptr->value->ypos][newptr->value->xpos]=NULL;
		NodeEnemy* newptr2=thisobj->mapenemies.insertNode();
		newptr2->copy(newptr->value);
		newptr=newptr->nextptr;
	}
	NPC.clear();
}


void exe::popenemies()
{
	//mapenemies->NPC
	CONSOLE.pushtext(true,0,"Pop Enemies");
	NPC.clear();
	if (mapnpcs.tailptr==NULL)
	{
		printf("\ncant pop enemies");
		return;
	}
	LinkedListNode<mapenemieslist> * thisobj=mapnpcs.tailptr;

	LinkedListNode<NodeEnemy> * npclist=thisobj->value->mapenemies.headptr;
	while (npclist!=NULL)
	{
		NodeEnemy * newenemy=NPC.insertNode();
		newenemy->copy(npclist->value);
		MAPFILES.MAPFILEENEMY[newenemy->ypos][newenemy->xpos]=newenemy;
		npclist=npclist->nextptr;
	}
	mapnpcs.deleteNode(thisobj);
}

void exe::loadpresets()
{
	xml *xmlc=new xml();
	//checked if npc head == null

	char filestart[100];filestart[0]=0;
	strcpy(filestart,"Data/Maps/");

	char tempo[20];tempo[0]=0;
	sprintf(tempo,"%d",MAPFILES.currentmap->id);

	strcat(filestart,tempo);

	//use this
	char path[100];path[0]=0;

	if (MAPFILES.currentmap->PresetNpcFile!=NULL)
	{	
		xmlc->getfile(MAPFILES.currentmap->PresetNpcFile,true);
		INFOS.loadpresetnpcs(xmlc);
	}

	if (MAPFILES.currentmap->PresetNpcFile!=NULL)
	{
		xmlc->getfile(MAPFILES.currentmap->PresetNpcFile,true);
		INFOS.loadpresetitems(xmlc);
	}

	if (MAPFILES.currentmap->PresetExitFile!=NULL)
	{
		xmlc->getfile(MAPFILES.currentmap->PresetExitFile,true);
		INFOS.loadpresetexits(xmlc);
	}

	//load map scripts
	if (MAPFILES.currentmap->PresetScriptFile!=NULL)
	{
		xmlc->getfile(MAPFILES.currentmap->PresetScriptFile,true);
		INFOS.loadpresetscripts(xmlc);
	}

	delete xmlc;

}


void exe::mapjoinpoint(int x1,int y1,int x2, int y2)
{
	//printf("\n");
	int pathtile=TT_GRASS;
	int walltile=TT_BWALL;
	//x1;y1;x2;y2;pathtile;walltile;
	int cx=x1,cy=y1;

	while(cx!=x2||cy!=y2)
	{
		float dy=((float)cy/(float)y2);
		float dx=((float)cx/(float)x2);
		if (dy>1)dy*=.01;
		if (dx>1)dx*=.01;
		if (dy<dx&&cy!=y2)
		{
			if (cy>y2)
				cy--;
			else
				cy++;
		}
		else if (dy>=dx&&cx!=x2)
		{
			if (cx>x2)
				cx--;
			else
				cx++;
		}
		//printf(".");
		if (MAPFILES.MAPFILE[cy][cx]==walltile)
			MAPFILES.MAPFILE[cy][cx]=pathtile;
	}

	//printf("bail\n");
}


void exe::mapgen(int maxx,int maxy,int maptype)
{
	//any vars with var +1 size, 1 is the first element
	//1 = rooms
	int roomtile=TT_MUD;
	int walltile=TT_BWALL;

	MAPFILES.loadMAPFILES(maxx,maxy);

	//set mapfile to all wall (style of generated map)
	for (int a=0;a<maxy;a++)
		for (int b=0;b<maxx;b++)
			MAPFILES.MAPFILE[a][b]=walltile;

	if (maptype==1)
	{
		int maxroomx=15;//(maxx/5)-1;
		int maxroomy=15;//(maxy/5)-1;
		int maxrooms=(maxroomx+maxroomy)/4;
		int maxpath=(5*maxrooms)/4;
		int maxpathperroom=4;

		//first room=0
		int room=0;
		//ra 0=x 1=y

		//room array, 0 is first element
		int **roomarray;
		roomarray=new int*[maxrooms];
		for (int a=0;a<maxrooms;a++)
			roomarray[a]=new int[2];

		for (int a=0;a<maxrooms;a++)
			for (int b=0;b<2;b++)
				roomarray[a][b]=0;

		//generate rooms and positions
		while (room<maxrooms)
		{
			int randx=1+rand()%(maxx-1);
			int randy=1+rand()%(maxy-1);

			//change if want random room size
			if (((randx+maxroomx+1)<maxx)&&((randy-maxroomy-1)>0)&&((randx-1)>0)&&((randy+1)<maxy)&&\
				(MAPFILES.MAPFILE[randy][randx]==walltile)&&(MAPFILES.MAPFILE[randy-1][randx-1]==walltile)&&(MAPFILES.MAPFILE[randy][randx-1]==walltile)&&(MAPFILES.MAPFILE[randy+1][randx-1]==walltile)&&(MAPFILES.MAPFILE[randy+1][randx]==walltile)&&(MAPFILES.MAPFILE[randy+1][randx+1]==walltile)&&\
				(MAPFILES.MAPFILE[randy][randx+maxroomx]==walltile)&&(MAPFILES.MAPFILE[randy-1][randx+maxroomx-1]==walltile)&&(MAPFILES.MAPFILE[randy][randx+maxroomx-1]==walltile)&&(MAPFILES.MAPFILE[randy+1][randx+maxroomx-1]==walltile)&&(MAPFILES.MAPFILE[randy][randx+maxroomx+1]==walltile)&&(MAPFILES.MAPFILE[randy+1][randx+maxroomx+1]==walltile)&&\
				(MAPFILES.MAPFILE[randy-maxroomy][randx]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy-1][randx-1]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy][randx-1]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy+1][randx-1]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy+1][randx]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy+1][randx+1]==walltile)&&\
				(MAPFILES.MAPFILE[randy-maxroomy][randx+maxroomx]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy-1][randx+maxroomx-1]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy][randx+maxroomx-1]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy+1][randx+maxroomx-1]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy+1][randx+maxroomx]==walltile)&&(MAPFILES.MAPFILE[randy-maxroomy+1][randx+maxroomx+1]==walltile)\
				)
			{
				roomarray[room][0]=randx;
				roomarray[room][1]=randy;
				for (int a=randy;a>randy-maxroomy;a--)
					for (int b=randx;b<randx+maxroomx;b++)
						MAPFILES.MAPFILE[a][b]=roomtile;
				//////////////////
				//printf("\nroom %d/%d complete",room+1,maxrooms);
				room++;
			}
		}
		//add start,end ladders to roomz
		int start=0;
		int end=0;
		while (start==0||end==0||start==end)
		{
			start=rand()%maxrooms;
			end=rand()%maxrooms;
		}

		int randx=0;
		int randy=0;
		while (randx==0||randy==0)
		{
			randx=rand()%maxroomx;
			randy=rand()%maxroomy;
		}

		MAPFILES.MAPFILE[roomarray[start][1]-randy][roomarray[start][0]+randx]=TT_LADDERD;

		randx=0;
		randy=0;
		while (randx==0||randy==0)
		{
			randx=rand()%maxroomx;
			randy=rand()%maxroomy;
		}

		MAPFILES.MAPFILE[roomarray[end][1]-randy][roomarray[end][0]+randx]=TT_LADDERU;

		////////////////


		//generate paths
		int path=1;

		int *pathcount;
		pathcount= new int[maxrooms+1];

		int **pathlist;
		pathlist=new int* [maxpath+1];
		for (int a=0;a<maxpath+1;a++)
			pathlist[a]=new int[2];

		int pathlistcount=1;
		//int pathlist[maxrooms+1][maxrooms+1];
		//printf("\nfirst path pass");
		while (path-1<maxrooms)
		{
			int randy=0;
			while (randy==0||(randy==path||pathcount[path]>=(maxpathperroom+1)&&pathcount[randy]>=(maxpathperroom+1)))
			{
				randy=rand()%(maxrooms+1);
			}

			pathcount[path]++;pathcount[randy]++;
			pathlist[pathlistcount][0]=path-1;
			pathlist[pathlistcount][1]=randy-1;
			pathlistcount++;

			//printf("\nstart=%d, dest=%d path %d/%d",path,randy,path,maxpath);
			path++;
		}

		//printf("\nsecond path pass");
		while (path-1<maxpath)
		{
			int rand1=0;
			int rand2=0;
			while ((rand1==0||rand2==0)||(rand2==rand1||pathcount[rand1]>=(maxpathperroom+1)&&pathcount[rand2]>=(maxpathperroom+1)))
			{
				rand1=rand()%(maxrooms+1);
				rand2=rand()%(maxrooms+1);
			}


			pathcount[rand1]++;
			pathcount[rand2]++;
			pathlist[pathlistcount][0]=rand1-1;
			pathlist[pathlistcount][1]=rand2-1;
			pathlistcount++;

			//printf("\nstart=%d, dest=%d path %d/%d",rand1,rand2,path,maxpath);
			path++;
		}
		//////////////////

		//x,y

		printf("\n");

		for (int a=1;a<pathlistcount;a++)
		{	
			printf("\npath %d, init=%d dest=%d",a,pathlist[a][0]+1,pathlist[a][1]+1);
			mapjoinpoint(roomarray[pathlist[a][0]][0]+(maxroomx/2),roomarray[pathlist[a][0]][1]-(maxroomy/2),\
				roomarray[pathlist[a][1]][0]+(maxroomx/2),roomarray[pathlist[a][1]][1]-(maxroomy/2));

		}

		//set current map starting position
		MAPFILES.currentmap->startX=roomarray[end][0]+randx;
		MAPFILES.currentmap->startY=roomarray[end][1]-randy;		

		//delete all created arrays
		delete[] pathcount;
		pathcount=NULL;

		for (int a=0;a<maxpath+1;a++)
			delete[] pathlist[a];
		delete[] pathlist;
		pathlist=NULL;

		for (int a=0;a<maxrooms;a++)
			delete[] roomarray[a];
		delete[] roomarray;
		roomarray=NULL;
	}
}

void exe::getdungeoninfo(char * path)
{
	xml *xmlc=new xml();
	xmlc->getfile(path,true);
	INFOS.loaddungeonassist(xmlc);
	delete xmlc;
}


void exe::readfromdungeon(char * path)
{
	getdungeoninfo(path);
	return;
}

void swap1(int table1[1][2],int table2[1][2])
{
	int temp1=table1[0][0];
	int temp2=table1[0][1];

	table1[0][0]=table2[0][0];
	table1[0][1]=table2[0][1];

	table2[0][0]=temp1;
	table2[0][1]=temp2;
}


bool bsort1(int table[200][2],int count,bool forward)
{
	int a=0;
	while (a<count-1)
	{
		if (table[a][1]>table[a+1][1]&&forward)
		{
			swap1(&table[a],&table[a+1]);
			if (a>0)
				a--;
		}

		else if (table[a+1][1]>table[a][1]&&(forward==false))
		{
			swap1(&table[a],&table[a+1]);
			if (a>0)
				a--;
		}

		else
			a++;

	}
	return true;
}

void exe::dropitem(int id,int x,int y)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_GROUND);
		return;
	}

	if (MAPFILES.MAPFILEITEM[y][x]!=NULL)
	{CONSOLE.pushtext(true,0,TEXT_ITEM_NOROOM);return;}

	//get value of enemy killed, atm = exp
	int nid=id;
	while (nid>=100)
		nid-=100;

	int value=INFOS.NPCSTOREPTR[nid]->exp;

	//percentages
	//60% drop
	//luck changes drop
	//100 luck=80% drop
	float dropPercentage=rand()%100;
	float dropcount=60;
	dropcount+=((float)PLAYERSTATS.luck/5);

	if (dropPercentage>ceil(dropcount))
		return;

	EXEC.loadSound(SND.dropsound);

	int droptype=rand()%100;
	//int droptype=65;

	//30% gold
	//15% food
	//55% wep/arm 
	//gold
	if (droptype<=30)
	{
		int dropvalue=2+(rand()%(value/4));
		grounditems.insertNode()->setvalues(dropvalue,300,x,y);
	}

	//food
	else if (droptype<=45)
	{
		int dropvalue=2+(rand()%(value/4));
		grounditems.insertNode()->setvalues(dropvalue,301,x,y);

	}
	//item
	else
	{
		int dropvalue=value;
		//	int dropvalue=1000;

		//build a table of all possible items < value
		int count=0;

		//[0]=id [1]=cost
		int table[200][2];
		for (int a=0;a<200;a++)
		{
			table[a][0]=0;table[a][1]=0;
		}

		//candidates= armour, weapons
		LinkedListNode<armstore> * newptr=INFOS.ARMSTORE.headptr;
		while (newptr!=NULL)
		{
			if (newptr->value->cost<dropvalue&&newptr->value->cost>0)
			{
				table[count][0]=newptr->value->id;
				table[count][1]=newptr->value->cost;
				count++;
			}
			newptr=newptr->nextptr;	
		}

		LinkedListNode<wepstore> * newptr2=INFOS.WEPSTORE.headptr;
		while (newptr2!=NULL)
		{
			if (newptr2->value->cost<dropvalue&&newptr2->value->cost>0)
			{
				table[count][0]=newptr2->value->id;
				table[count][1]=newptr2->value->cost;
				count++;
			}
			newptr2=newptr2->nextptr;	
		}

		bsort1(table,count,false);

		if (count>10)
			count=0;

		//get a random number to 1 decimal place
		int dropper=rand()%100;
		//int dropper=100;

		//hard code values in since a formula didnt work nicely
		float table2[10];
		table2[9]=30;
		table2[8]=40;
		table2[7]=50;
		table2[6]=60;
		table2[5]=65;
		table2[4]=70;
		table2[3]=75;
		table2[2]=80;
		table2[1]=85;
		table2[0]=100;

		//put luck into the equation
		//at 100 luck, it should be ~80% likely to get the best item
		for (int a=0;a<10;a++)
		{
			table2[a]=table2[a]-(table2[a]*((float)PLAYERSTATS.luck/600));
		}

		int choose=-1;
		for (int a=9;a>-1;a--)
		{
			if (dropper<=table2[a])
			{
				choose=a;break;
			}
		}

		if (choose==-1)
			choose=0;

		//if there arent enough items, choose the next best
		while (table[choose][0]==0)
		{
			if (choose==0)
				break;
			choose--;
		}
		if (table[choose][0]==0)
		{printf("\nWARNING! NO ITEMS TO SPAWN!");return;}
		grounditems.insertNode()->setvalues(1,table[choose][0],x,y);
	}
}

void exe::pickupfunction(int x, int y)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_NOITEM);
		return;
	}
	if (MAPFILES.MAPFILEENEMY[y][x]!=NULL&&MAPFILES.MAPFILEENEMY[y][x]!=(NodeEnemy*)0x01&&MAPFILES.MAPFILEENEMY[y][x]->faction==NT_HOSTILE)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_NOACCESS);
		return;
	}
	char temp[200];
	char temp2[100];
	if (MAPFILES.MAPFILEITEM[y][x]==NULL)
	{CONSOLE.pushtext(false,0,TEXT_ITEM_NOITEM);return;}
	NodeObject * newptr=MAPFILES.MAPFILEITEM[y][x];
	if (newptr==NULL)
		return;

	//printf("\nIx=%d,Iy=%d,IPX=%d,IPY=%d",x,y,newptr->xpos,newptr->ypos);
	if (newptr->type==T_GOLD)
	{
		//playsound
		EXEC.loadSound(SND.goldsound);

		sprintf(temp2," %d ",newptr->amount);
		strcpy(temp,"You found");
		strcat(temp,temp2);
		strcat(temp,"Gold");
		CONSOLE.pushtext(false,2,temp);
		PLAYER.gold+=newptr->amount;
		MAPFILES.MAPFILEITEM[y][x]=NULL;
		grounditems.deleteNode(newptr);
		return;
	}
	else if (newptr->type==T_FOOD)
	{
		if (PLAYER.food<PLAYER.maxfood)
		{
			//playsound
			EXEC.loadSound(SND.foodsound);

			sprintf(temp2," %d ",newptr->amount);
			strcpy(temp,"You found");
			strcat(temp,temp2);
			strcat(temp,"Food");
			CONSOLE.pushtext(false,2,temp);
			PLAYER.food+=newptr->amount;
			MAPFILES.MAPFILEITEM[y][x]=NULL;
			grounditems.deleteNode(newptr);
			return;
		}
		else
		{
			int temp3=newptr->amount;
			temp3-=(PLAYER.food+temp3)-PLAYER.maxfood;
			sprintf(temp2," %d ",temp3);
			strcpy(temp,"You found");
			strcat(temp,temp2);
			strcat(temp,"Food");
			CONSOLE.pushtext(false,2,temp);
			strcpy(temp,"You have max food");
			CONSOLE.pushtext(false,3,temp);
			PLAYER.food=PLAYER.maxfood;
			MAPFILES.MAPFILEITEM[y][x]=NULL;
			grounditems.deleteNode(newptr);
			return;
		}
	}

	else if (isweapon(newptr->type))
	{
		if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
		{CONSOLE.pushtext(false,0,TEXT_INV_FULL);return;}
		//playsound
		EXEC.loadSound(SND.pickupsound);

		strcpy(temp,"You found a ");
		strcat(temp,INFOS.WEPSTOREPTR[newptr->id-200]->name);
		CONSOLE.pushtext(false,2,temp);
		helditems.insertNode()->setvalues(1,newptr->id,-1,-1);
		MAPFILES.MAPFILEITEM[y][x]=NULL; 
		grounditems.deleteNode(newptr);
		return;
	}
	//magic spell pick up
	else if (isspell(newptr->type))
	{
		char temp[200];
		strcpy(temp,"You have gained the knowledge of ");
		strcat(temp,newptr->str);
		CONSOLE.pushtext(false,2,temp);
		int nid=newptr->id;
		while (nid>=100)
			nid-=100;
		PLAYER.hasSpellTable[nid]=true;
		MAPFILES.MAPFILEITEM[y][x]=NULL; 
		grounditems.deleteNode(newptr);
		return;
	}

	else if (isarmour(newptr->type))
	{
		if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
		{CONSOLE.pushtext(false,0,TEXT_INV_FULL);return;}
		strcpy(temp,"You found a ");
		strcat(temp,INFOS.ARMSTOREPTR[newptr->id-500]->name);
		CONSOLE.pushtext(false,2,temp);
		helditems.insertNode()->setvalues(1,newptr->id,-1,-1);
		MAPFILES.MAPFILEITEM[y][x]=NULL; 
		grounditems.deleteNode(newptr);
		return;
	}

	else
	{
		printf("\nUtype=%d",newptr->id);

		if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
		{CONSOLE.pushtext(false,0,TEXT_INV_FULL);return;}
		//playsound
		EXEC.loadSound(SND.pickupsound);

		strcpy(temp,"You found a ");
		strcat(temp,newptr->str);
		CONSOLE.pushtext(false,2,temp);
		helditems.insertNode()->setvalues(1,newptr->id,-1,-1);
		MAPFILES.MAPFILEITEM[y][x]=NULL; 
		grounditems.deleteNode(newptr);
		return;
	}
}

void exe::drawstatsmap(int pos)
{
	float xpos,ypos;
	if (pos==0)
	{xpos=483;ypos=467;}
	else
	{xpos=9;ypos=472;}

	int a=0,b=0;
	int terrain; 

	//number of tiles
	int minx,maxx,miny,maxy;

	//size of stats window
	float sizex=0;
	float sizey=0;

	float tilex=0;
	float tiley=0;

	if (pos==0)	
	{
		sizex=150;
		sizey=150;
		minx=PLAYER.posx-50;
		maxx=PLAYER.posx+50;

		miny=PLAYER.posy-50;
		maxy=PLAYER.posy+50;
	}
	else 
	{
		sizex=125;
		sizey=125;
		minx=PLAYER.posx-25;
		maxx=PLAYER.posx+25;

		miny=PLAYER.posy-23;
		maxy=PLAYER.posy+23;
	}

	tilex=sizex/((float)maxx-(float)minx);
	tiley=sizey/((float)maxy-(float)miny);

	float alpha=0;

	if (pos==1)
		alpha=.6;
	else
		alpha=1;

	int counta=-1,countb=-1;

	for (a=miny;a<maxy;a++)
	{
		counta++;countb=0;
		for (b=minx;b<maxx;b++)
		{
			countb++;

			if ((a<0||a>=MAPFILES.emapheight())||(b<0||b>=MAPFILES.emapwidth()))
				terrain=TT_BLACK;
			else
				terrain=MAPFILES.MAPFILE[a][b];

			glColor4f(1,1,1,1);

			if (a==PLAYER.posy&&b==PLAYER.posx)
				glColor3f(1, 0, 0);
			else
				EXEC.loadterraincase(terrain,alpha);




			glBegin(GL_QUADS);
			glVertex2f(xpos+(tilex*countb),			ypos-(tiley*counta) );
			glVertex2f(xpos+tilex+(tilex*countb),	ypos-(tiley*counta)  );
			glVertex2f(xpos+tilex+(tilex*countb),	(ypos-tiley)-(tiley*  counta) );
			glVertex2f(xpos+(tilex*countb),			(ypos-tiley)-(tiley*counta));
			glEnd();
		}
	}
	glColor4f(1,1,1,1);
}



void exe::drawopeningtext(void)
{
	glLoadIdentity();
	glEnable(GL_LINE_SMOOTH);
	glTranslatef(165,380,0);
	glPushMatrix();
	glTranslatef(45,0,0);
	glScalef(.25,.15,.25);
	glColor3f(1.0, 0, 0);
	glutStrokeString("--Typhoon--");
	glPopMatrix();
	glTranslatef(0,-290,0);
	glScalef(.25,.15,.25);
	glColor3f(1.0, 0, 0);
	glutStrokeString("(C)2008-Andrei Gec");

	glDisable(GL_LINE_SMOOTH);
	glLoadIdentity();
	glTranslatef(25,50,0);
	glScalef(.25,.15,.25);
	glPushMatrix();
	if (MAPFILES.rearmx==0)glColor3f(1, 1, 0);else{glColor3f(1, 0,0);}
	glutStrokeString("New");
	glPopMatrix();
	glTranslatef(0,-180,0);
	glutStrokeString("Game");

	glLoadIdentity();
	glTranslatef(100,50,0);
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmx==1)glColor3f(1, 1, 0);else{glColor3f(1.0, 0, 0);}
	if (GLOBAL.runninggame==0)glColor3f(0, 0, 0);
	glutStrokeString("Continue");

	glLoadIdentity();
	glTranslatef(220,50,0);
	glScalef(.25,.15,.25);
	glPushMatrix();
	if (MAPFILES.rearmx==2)glColor3f(1, 1, 0);else{glColor3f(1.0, 0, 0);}
	if (GLOBAL.runninggame==0)glColor3f(0, 0, 0);
	glutStrokeString(" Save");
	glPopMatrix();
	glTranslatef(0,-180,0);
	glutStrokeString("Game");

	glLoadIdentity();
	glTranslatef(330,50,0);
	glScalef(.25,.15,.25);
	glPushMatrix();
	if (MAPFILES.rearmx==3)glColor3f(1, 1, 0);else{glColor3f(1.0, 0, 0);}
	glutStrokeString("Load");
	glPopMatrix();
	glTranslatef(0,-180,0);
	glutStrokeString("Game");

	glLoadIdentity();
	glTranslatef(430,50,0);
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmx==4)glColor3f(1, 1, 0);else{glColor3f(1.0, 0, 0);}
	glutStrokeString("Options");

	glLoadIdentity();
	glTranslatef(555,50,0);
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmx==5)glColor3f(1, 1, 0);else{glColor3f(1.0, 0, 0);}
	glutStrokeString("Quit");
}

void exe::drawopeningscreen(void)
{
	//overall size box tomfoolery
	glColor3f(0.1530,0.2824,0.6275);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 480);
	glVertex2f(640, 480);
	glVertex2f(640, 0);
	glEnd();

	//top box shenanigans
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex2f(5, 475);
	glVertex2f(635, 475);
	glVertex2f(635, 400);
	glVertex2f(5, 400);

	glVertex2f(5, 400);
	glVertex2f(635, 400);
	glVertex2f(635, 370);
	glVertex2f(5, 370);

	glColor3f(0.1530,0.2824,0.6275);
	glVertex2f(120, 370);
	glColor3f(0.2294,0.7373,0.9412);
	glVertex2f(145, 400);
	glVertex2f(630-125, 400);
	glColor3f(0.1530,0.2824,0.6275);
	glVertex2f(630-100,370);
	glEnd();

	//bottom box hiijinks
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex2f(5, 110);
	glVertex2f(635, 110);
	glVertex2f(635, 5);
	glVertex2f(5, 5);

	glColor3f(0.1530,0.2824,0.6275);
	glVertex2f(120, 110);
	glColor3f(0.2294,0.7373,0.9412);
	glVertex2f(145, 80);
	glVertex2f(630-125, 80);
	glColor3f(0.1530,0.2824,0.6275);
	glVertex2f(630-100, 110);
	glEnd();

	//menu brouhaha
	glBegin(GL_QUADS);
	glColor3f(0.2294,0.7373,0.9412);
	glVertex2f(20, 70);
	glVertex2f(620, 70);
	glColor3f(0,0,0);
	glVertex2f(620, 20);
	glVertex2f(20, 20);

	glEnd();
}


void exe::drawstatsinventory(void)
{
	int count=-1;
	int x=0,y=0;

	glColor3f(.4,.4, .4);
	glBegin(GL_QUADS);
	glVertex2f(630-5*(250/5), 10);
	glVertex2f(630-5*(250/5), 260);
	glVertex2f(630, 260);
	glVertex2f(630, 10);
	glEnd();

	glColor3f(0, 1 , 1);
	glBegin(GL_LINES);
	glVertex2f(630-5*(250/5), 10);
	glVertex2f(630, 10);
	glVertex2f(630-5*(250/5), 10+1*(250/5));
	glVertex2f(630, 10+1*(250/5));
	glVertex2f(630-5*(250/5), 10+2*(250/5));
	glVertex2f(630, 10+2*(250/5));
	glVertex2f(630-5*(250/5), 10+3*(250/5));
	glVertex2f(630, 10+3*(250/5));
	glVertex2f(630-5*(250/5), 10+4*(250/5));
	glVertex2f(630, 10+4*(250/5));
	glVertex2f(630-5*(250/5), 10+5*(250/5));
	glVertex2f(630, 10+5*(250/5));
	glVertex2f(630, 260);
	glVertex2f(630, 10);
	glVertex2f(630-1*(250/5), 260);
	glVertex2f(630-1*(250/5), 10);
	glVertex2f(630-2*(250/5), 260);
	glVertex2f(630-2*(250/5), 10);
	glVertex2f(630-3*(250/5), 260);
	glVertex2f(630-3*(250/5), 10);
	glVertex2f(630-4*(250/5), 260);
	glVertex2f(630-4*(250/5), 10);
	glVertex2f(630-5*(250/5), 260);
	glVertex2f(630-5*(250/5), 10);
	//glVertex2f(630-6*(250/5), 260);
	//glVertex2f(630-6*(250/5), 10);
	glEnd();

	//glColor3f(1, 1 , 1);


	if (GLOBAL.loopswitch==LS_USEMENU)
	{
		glColor3f(.5,.5, .5);
		glBegin(GL_QUADS);
		glVertex2f((630-6*(250/5)), 260);
		glVertex2f((630-5*(250/5)), 260);
		glVertex2f((630-5*(250/5)), 60);
		glVertex2f((630-6*(250/5)), 60);
		glEnd();	

		glColor3f(1, 1 , 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f((630-6*(250/5)), 260);
		glVertex2f((630-5*(250/5)), 260);
		glVertex2f((630-5*(250/5)), 60);
		glVertex2f((630-6*(250/5)), 60);
		//glVertex2f((630-6*(250/5)), 260);
		glEnd();	


		//weps
		glColor3f(.5,.5,.5);
		glBegin(GL_QUADS);
		glVertex2f((630-3*(250/5)), 310);
		glVertex2f((630-5*(250/5)), 310);
		glVertex2f((630-5*(250/5)), 260);
		glVertex2f((630-3*(250/5)), 260);
		glEnd();

		glColor3f(1,1,1);
		glBegin(GL_LINE_LOOP);
		glVertex2f((630-3*(250/5)), 310);
		glVertex2f((630-5*(250/5)), 310);
		glVertex2f((630-5*(250/5)), 260);
		glVertex2f((630-3*(250/5)), 260);
		glEnd();
		/////////		



		glColor3f(1, 1 , 0);
		glBegin(GL_QUADS);
		glVertex2f((630-5*(250/5))+MAPFILES.rearmx*50, 260-MAPFILES.rearmy*50);
		glVertex2f((630-4*(250/5))+MAPFILES.rearmx*50, 260-MAPFILES.rearmy*50);
		glVertex2f((630-4*(250/5))+MAPFILES.rearmx*50, 210-MAPFILES.rearmy*50);
		glVertex2f((630-5*(250/5))+MAPFILES.rearmx*50, 210-MAPFILES.rearmy*50);
		glEnd();	

		if (EQUIPMENT.HELM.id==0)
		{
			glColor4f(.5,.5,.5,.5);
			EXEC.loadTexture("Data/Images/Armour/cap.tga");
		}
		else
		{
			glColor3f(1,1,1);
			EXEC.loadTexture(EQUIPMENT.HELM.path);
		}


		drawtile((630-6*(250/5)), 210,(630-6*(250/5)), 260,(630-5*(250/5)), 260,(630-5*(250/5)), 210);


		if (EQUIPMENT.CHEST.id==0)
		{
			glColor4f(.5,.5,.5,.5);
			EXEC.loadTexture("Data/Images/Armour/bodyarmour.tga");
		}
		else
		{
			glColor3f(1,1,1);
			EXEC.loadTexture(EQUIPMENT.CHEST.path);
		}

		drawtile((630-6*(250/5)), 160,(630-6*(250/5)), 210,(630-5*(250/5)), 210,(630-5*(250/5)), 160);


		if (EQUIPMENT.LEGS.id==0)
		{
			glColor4f(.5,.5,.5,.5);
			EXEC.loadTexture("Data/Images/Armour/pants.tga");
		}
		else
		{
			glColor3f(1,1,1);
			EXEC.loadTexture(EQUIPMENT.LEGS.path);
		}

		drawtile((630-6*(250/5)), 110,(630-6*(250/5)), 160,(630-5*(250/5)), 160,(630-5*(250/5)), 110);


		if (EQUIPMENT.SHOES.id==0)
		{
			glColor4f(.5,.5,.5,.5);
			EXEC.loadTexture("Data/Images/Armour/boots.tga");
		}
		else
		{
			glColor3f(1,1,1);
			EXEC.loadTexture(EQUIPMENT.SHOES.path);
		}

		drawtile((630-6*(250/5)), 60,(630-6*(250/5)), 110,(630-5*(250/5)), 110,(630-5*(250/5)), 60);

		glColor3f(1,1,1);

		glBegin(GL_LINES);
		glVertex2f((630-6*(250/5)), 210);
		glVertex2f((630-5*(250/5)), 210);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f((630-6*(250/5)), 160);
		glVertex2f((630-5*(250/5)), 160);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f((630-6*(250/5)), 110);
		glVertex2f((630-5*(250/5)), 110);
		glEnd();



		///////////////////////////////////////////////////////////////


		glColor3f(1,1,1);
		EXEC.loadTexture(EQUIPMENT.RARM.path);

		drawtile((630-5*(250/5)), 260,(630-5*(250/5)), 310,(630-4*(250/5)), 310,(630-4*(250/5)), 260);


		EXEC.loadTexture(EQUIPMENT.LARM.path);

		drawtile((630-4*(250/5)), 260,(630-4*(250/5)), 310,(630-3*(250/5)), 310,(630-3*(250/5)), 260);


		//line between boxes
		glBegin(GL_LINES);
		glVertex2f((630-4*(250/5)), 310);
		glVertex2f((630-4*(250/5)), 260);
		glEnd();

		/////////////////////////////////////////////////

	}

	else if (GLOBAL.loopswitch==LS_DROP)
	{
		glColor3f(1, 1 , 0);
		glBegin(GL_QUADS);
		glVertex2f((630-5*(250/5))+MAPFILES.rearmx*50, 260-MAPFILES.rearmy*50);
		glVertex2f((630-4*(250/5))+MAPFILES.rearmx*50, 260-MAPFILES.rearmy*50);
		glVertex2f((630-4*(250/5))+MAPFILES.rearmx*50, 210-MAPFILES.rearmy*50);
		glVertex2f((630-5*(250/5))+MAPFILES.rearmx*50, 210-MAPFILES.rearmy*50);
		glEnd();	
	}

	LinkedListNode<NodeObject> * newptr=helditems.headptr;
	while (newptr!=NULL)
	{
		count++;
		//printf("\nc=%d",count);
		if (count%5==0&&count!=0)
		{x=0;y+=50;}
		else if (count!=0)
			x+=50;
		glColor3f(1, 1 , 1);

		EXEC.loadTexture(newptr->value->pic);

		drawtile(380+x, 210-y,380+x, 260-y,430+x, 260-y,430+x, 210-y);
		newptr=newptr->nextptr; 
	}


	glPopMatrix();

}



bool exe::dealdamagefunction(NodeEnemy * attacker, NodeEnemy * target)
{	
	int basedamage=0;
	char string[300];
	char tempp[300];
	float random=0;
	int switch1=0;
	basedamage+=attacker->attackbase;

	random=rand()%basedamage;
	switch1=rand()%1;
	if (switch1==0)
		basedamage+=random;
	if (switch1==1)
		basedamage-=random;
	basedamage-=target->defensebase;
	if (attacker==target)//ensures that no misshaps can occur
	{printf("a=t exit");return false;}
	if (basedamage<=-1)
		basedamage*=-1;
	target->enemyhealth-=basedamage;
	if (target->enemyhealth<0)
		target->enemyhealth=0;
	if (target->enemyhealth>0)
	{
		strcpy(string,attacker->str);
		strcat(string," attacked ");
		strcat(string,target->str);
		strcat(string," for");
		sprintf(tempp," %d",basedamage);
		strcat(string,tempp);
		CONSOLE.pushtext(false,3,string);
	}
	else
	{
		//playsound
		EXEC.loadSound(SND.death1);

		printf("\nattack=%s,tgt=%s",attacker->str,target->str);
		strcpy(string,attacker->str);
		strcat(string," killed ");
		strcat(string,target->str);
		CONSOLE.pushtext(false,3,string);
		MAPFILES.MAPFILEENEMY[target->ypos][target->xpos]=NULL;
		NPC.deleteNode(target);
		target=NULL;

		glutPostRedisplay();
		return true;
	}
	return false;
}


//deal damage from player to supplied node
//attack the target with the spellptr, pass in whether the target is an npc
template <class T>
void spellattack(NodeEnemy * target2,LinkedListNode<T> *spellptr2)
{
	LinkedListNode<NodeEnemy> * target=NPC.reverseGetNode(target2);
	LinkedListNode<NodeObject> * spellptr=spellptr2;
	//NodeEnemy * target=*target;
	char stringz[100];
	char targetp[100];
	//int count=0;

	if (spellptr==NULL)
	{
		printf("\nSpellptr==NULL!");return;
	}

	else if (target->value->type==T_TORCH||target->value->type==T_SIGN)
	{
		CONSOLE.pushtext(false,0,TEXT_SPELL_MISSED); 
		spellz.deleteNode(spellptr);
		return;
	}
	int random=rand()%100;

	if (target->value->faction!=NT_HOSTILE)
	{
		strcpy(targetp,target->value->str);
		strcat(targetp,": Now you've done it!");
		target->value->faction=NT_HOSTILE;
		CONSOLE.pushtext(false,0,targetp);
	}

	if (random<=20&&(spellptr->value->id<=490))
	{
		if (SPELL2.active==0)CONSOLE.pushtext(false,1,TEXT_PLAYER_MISS);
		else if (SPELL2.active==0)CONSOLE.pushtext(false,0,TEXT_SPELL_MISSED);

		//spellptr=spellptr->value->nextptr;
		//dont delete spell if miss
		//deleteNode(&spellz,spellcount);
		//TODO:comment out, h

		if (spellz.headptr==NULL)
		{SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
		else
			spellptr=spellptr->prevptr;
	}

	else
	{
		int basedamage=SPELL.basedamage;

		if (SPELL.type>=421&&SPELL.type<431)
		{basedamage*=5;basedamage+=PLAYERSTATS.intelligence;}
		else if (SPELL.type>=431&&SPELL.type<450)
		{basedamage*=10;basedamage+=PLAYERSTATS.intelligence;}


		target->value->enemyhealth-=basedamage;
		if (target->value->enemyhealth>0)
		{
			if (SPELL2.active==0)strcpy(stringz,"You deal ");
			else strcpy(stringz,"Spell deals ");
			strcat(stringz,target->value->str);
			sprintf(targetp," %d",basedamage);
			strcat(stringz,targetp);
			strcat(stringz," damage");
			CONSOLE.pushtext(false,2,stringz);

			if ((SPELL.type==403||SPELL.type==424||SPELL.type==434)&&SPELL.basedamage>=2)
			{
				MAPFILES.MAPFILEENEMY[target->value->ypos][target->value->xpos]=NULL;
				if (spellptr->value->id==1&&MAPFILES.MAPFILE[target->value->ypos+1][target->value->xpos-1]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos+1][target->value->xpos-1]==NULL)
				{target->value->xpos--;target->value->ypos++;}
				else if (spellptr->value->id==2&&MAPFILES.MAPFILE[target->value->ypos+1][target->value->xpos]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos+1][target->value->xpos]==NULL)
					target->value->ypos++;
				else if (spellptr->value->id==3&&MAPFILES.MAPFILE[target->value->ypos+1][target->value->xpos+1]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos+1][target->value->xpos+1]==NULL)
				{target->value->ypos++;target->value->xpos++;}
				else if (spellptr->value->id==4&&MAPFILES.MAPFILE[target->value->ypos][target->value->xpos-1]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos][target->value->xpos-1]==NULL)
					target->value->xpos--;
				else if (spellptr->value->id==6&&MAPFILES.MAPFILE[target->value->ypos][target->value->xpos+1]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos][target->value->xpos+1]==NULL)
					target->value->xpos++;
				else if (spellptr->value->id==7&&MAPFILES.MAPFILE[target->value->ypos-1][target->value->xpos-1]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos-1][target->value->xpos-1]==NULL)
				{target->value->ypos--;target->value->xpos--;}
				else if (spellptr->value->id==8&&MAPFILES.MAPFILE[target->value->ypos-1][target->value->xpos]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos-1][target->value->xpos]==NULL)
					target->value->ypos--;
				else if (spellptr->value->id==9&&MAPFILES.MAPFILE[target->value->ypos-1][target->value->xpos+1]<9&&MAPFILES.MAPFILEENEMY[target->value->ypos-1][target->value->xpos+1]==NULL)
				{target->value->ypos--;target->value->xpos++;}
				MAPFILES.MAPFILEENEMY[target->value->ypos][target->value->xpos]=target->value;
				SPELL.basedamage/=2;

			}
			else
			{
				spellz.deleteNode(spellptr);
				if (spellz.headptr==NULL)
				{
					SPELL.active=0;SPELL2.active=0;
					GLOBAL.loopswitch=LS_NORMAL;
					if (target->value->faction!=NT_HOSTILE&&target->value->type!=T_SIGN&&target->value->type!=T_TORCH)
					{
						target->value->faction=NT_HOSTILE;
					}

					return;
				}
				else
				{
					if (spellz.headptr!=NULL)
						spellptr=spellptr->prevptr;

				}
			}
		}

		else if (target->value->enemyhealth<=0)
		{
			//playsound
			EXEC.loadSound(SND.death1);

			int nid=target->value->id;
			while (nid>=100)
				nid-=100;
			npcstore * newptr=INFOS.NPCSTOREPTR[nid];
			if (newptr==NULL)
			{
				printf("\nERROR! NPC ID %d = NULL!",nid);
				return;
			}

			if (SPELL2.active==0)
				strcpy(stringz,"You kill ");
			else strcpy(stringz,"Spell kills ");
			strcat(stringz,newptr->name);
			strcat(stringz," with");
			sprintf(targetp," %d",basedamage);
			strcat(stringz,targetp);
			strcat(stringz," damage");
			CONSOLE.pushtext(false,2,stringz);

			if (SPELL2.active==0)
			{
				PLAYER.exp+=newptr->exp;
				strcpy(stringz,"You gain");
				sprintf(targetp," %d",newptr->exp);
				strcat(stringz,targetp);
				strcat(stringz," EXP");
				CONSOLE.pushtext(false,2,stringz);
			}
			EXEC.dropitem(target->value->id,spellptr->value->xpos,spellptr->value->ypos);
			MAPFILES.MAPFILEENEMY[spellptr->value->ypos][spellptr->value->xpos]=0;

			LinkedListNode<NodeEnemy> * target2=target->prevptr;
			NPC.deleteNode(target);
			target=target2;
			//kill enemy only							
			LinkedListNode<NodeObject> * target3=spellptr->prevptr;
			spellz.deleteNode(spellptr);
			spellptr=target3;
			if (spellz.headptr==NULL)
			{SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
		}
	}

	//if (SPELL.type!=403&&SPELL.type!=424&&SPELL.type!=434)
	//	{SPELL.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
	if (SPELL.type==403&&SPELL.type==424&&SPELL.type==434)
	{
		if (SPELL.basedamage<=1)
		{SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
		else
			SPELL.basedamage/=2;
	}		

}


void exe::dealdamage(NodeEnemy * foundenemy,bool israrm)
{
	int random=0;
	char string[300];
	if (PLAYERSTATS.agility<=29)
	{
		random=rand()%100;
		if (random<=30-PLAYERSTATS.agility)
		{
			//playsound
			EXEC.loadSound(SND.misssound);

			strcpy(string,"You missed ");
			strcat(string,foundenemy->str);
			CONSOLE.pushtext(false,1,string);
			//GLOBAL.loopswitch=LS_PASS;
			glutPostRedisplay();
			return;
		}
	}

	float wtv;
	char tempp[300];
	int basedamage=0;
	int weapon2=0;
	//calculate damage dealt
	if (israrm==true)
	{
		wtv=INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->strengthReq;
		weapon2=0;
		weapon2+=INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage;
		if (wtv<=PLAYERSTATS.strength)
			weapon2+=(PLAYERSTATS.strength-wtv);
		if (GLOBAL.debugenabled==true)printf("\nrbd=%d",weapon2);
		basedamage+=weapon2;	
	}
	else
	{
		wtv=INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->strengthReq;
		basedamage+=INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage;
		if (wtv<=PLAYERSTATS.strength)
			basedamage+=(PLAYERSTATS.strength-wtv);
		if (GLOBAL.debugenabled==true)printf("\nlbd=%d",basedamage);
	}

	if (GLOBAL.debugenabled==true)printf("\ntotal=%d",basedamage);

	//damage varies with a mean of 15%
	random=rand()%30;
	if (random<=14)
	{basedamage*=1-(random/100.0);if (GLOBAL.debugenabled==true)printf("\n-bd=%d,rand=%f",basedamage,1-(random/100.0));}
	else if (random>=16)
	{random-=15;basedamage*=1+(random/100.0);if (GLOBAL.debugenabled==true)printf("\n+bd=%d,rand=%f",basedamage,1+(random/100.0));}

	basedamage-=((float)basedamage*.5)*((float)foundenemy->defensebase/100);
	if (basedamage<=0)
		basedamage=0;
	random=rand()%100;
	if (random<=(PLAYERSTATS.luck/3))
	{basedamage*=2;random=1;}
	else
		random=0;
	foundenemy->enemyhealth-=basedamage;
	if (foundenemy->enemyhealth<0)
		foundenemy->enemyhealth=0;

	if (foundenemy->enemyhealth>0)
	{

		if (random==1)
		{
			//playsound
			EXEC.loadSound(SND.criticalhit);
			CONSOLE.pushtext(false,2,TEXT_CRITICALHIT);
		}
		//playsound
		if (GLOBAL.soundenabled==true)
		{
			if ((israrm&&EQUIPMENT.RARM.type==T_FISTS)||(israrm==false&&EQUIPMENT.LARM.type==T_FISTS))
				EXEC.loadSound(SND.punchsound);
			else
				EXEC.loadSound(SND.swordhit);
		}

		strcpy(string,"You deal ");
		strcat(string,foundenemy->str);
		sprintf(tempp," %d",basedamage);
		strcat(string,tempp);
		strcat(string," damage");
		CONSOLE.pushtext(false,2,string);
		return;
	}
	else if (foundenemy->enemyhealth<=0)
	{
		if (random==1)
		{
			//playsound
			EXEC.loadSound(SND.criticalhit);
			CONSOLE.pushtext(false,2,TEXT_CRITICALHIT);
		}

		//playsound
		EXEC.loadSound(SND.death1);
		int nid=foundenemy->id;
		while (nid>=100)
			nid-=100;
		npcstore * newptr=INFOS.NPCSTOREPTR[nid];
		if (newptr==NULL)
		{
			printf("\nERROR! NPC ID %d = NULL!",nid);
			return;
		}
		strcpy(string,"You kill ");
		strcat(string,newptr->name);
		strcat(string," with");
		sprintf(tempp," %d",basedamage);
		strcat(string,tempp);
		strcat(string," damage");
		CONSOLE.pushtext(false,2,string);
		//bonus exp for fist kill
		if ((israrm&&EQUIPMENT.RARM.type==T_FISTS)||(israrm==false&&EQUIPMENT.LARM.type==T_FISTS))
		{
			int exp=newptr->exp+(newptr->hp/10);
			PLAYER.exp+=exp;
			strcpy(string,"Beatdown!");
			strcat(string," You gain");
			sprintf(tempp," %d",exp);
			strcat(string,tempp);

			strcat(string," experience for using fists");
			CONSOLE.pushtext(false,2,string);
		}
		else
		{
			PLAYER.exp+=newptr->exp;
			strcpy(string,"You gain ");
			sprintf(tempp," %d",newptr->exp);
			strcat(string,tempp);
			strcat(string," EXP");
			CONSOLE.pushtext(false,2,string);
		}

		dropitem(foundenemy->id,foundenemy->xpos,foundenemy->ypos);
		MAPFILES.MAPFILEENEMY[foundenemy->ypos][foundenemy->xpos]=NULL;
		NPC.deleteNode(foundenemy);
	}
}

void exe::loadmapcurrenttile()
{

	exitpoint * newptr=findmap(PLAYER.posx,PLAYER.posy);

	//if an exit is there, use it
	if (newptr!=NULL)
		loadMap(newptr);
	//otherwise if its a dungeon, call
	else if (MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]==TT_LADDERD)
		loadMap(TT_LADDERD);
	else if (MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]==TT_LADDERU)
		loadMap(TT_LADDERU);


	return;
}

//quit function with error calls
void exe::quit(char * string2)
{
	//make sure that the map file copy optimization is ignored for class dectruction, clear texturezs
	rmtexturez();
	rmsoundz();

	texturez.clear();
	variablePointers.clear();
	MAPFILES.dinit(false,true);

	//if there is a reason for the quit, display a long enough pause to read it
	if (strlen(string2)!=0)
	{
		printf("\nquit, error=%s",string2);
		Sleep(3000);
	}
	exit(0);
}

//when the player dies
void exe::playerdeath()
{
	GLOBAL.runninggame=0;
	GLOBAL.loopswitch=LS_DEATHSCREEN;
	//	ANIMATION.timer=1;
	ANIMATION.POSX=MAPFILES.currentmap->startX;
	ANIMATION.POSY=MAPFILES.currentmap->startY;
	if (MAPFILES.currentmap->darknessLevel==0)
		GLOBAL.worldstatus=0;
	MAPFILES.rearmx=0;
	glutPostRedisplay();
	return;
}

//inits vars before play
void exe::initvars(void)
{
	ANIMATION.init();
	pathz.clearall();
	MAPFILES.rearmx=0;
	INFOS.init();
	SPELL.init();
	GLOBAL.init();
	CONSOLE.init();
	PLAYERSTATS.init();
	PLAYER.init();
	EQUIPMENT.init();
	poker.init();

	//variable memory mapping for use with the console

	consolez.insertNode("quit")->ptr= (void*)100;
	consolez.insertNode("rage")->ptr= (void*)100;

	consolez.insertNode("dbpl")->ptr= (void*)101;
	consolez.insertNode("save")->ptr= (void*)102;
	consolez.insertNode("load")->ptr= (void*)103;
	consolez.insertNode("dbse")->ptr= (void*)104;

	consolez.insertNode("clear")->ptr= (void*)207;
	consolez.insertNode("dbpv")->ptr= (void*)200;
	consolez.insertNode("dbpn")->ptr= (void*)201;
	consolez.insertNode("help")->ptr= (void*)202;
	consolez.insertNode("restart")->ptr= (void*)203;
	consolez.insertNode("dbtm")->ptr= (void*)204;
	consolez.insertNode("cc")->ptr= (void*)299;
	consolez.insertNode("dbcv")->ptr= (void*)300;
	consolez.insertNode("dbfc")->ptr= (void*)301;
	consolez.insertNode("dbcvt")->ptr= (void*)302;
	consolez.insertNode("dbnpc")->ptr= (void*)303;

	variablePointers.insertNode("gb.c")->ptr= (void*) &GLOBAL.count;
	//	variablePointers.insertNode("gb.er")->ptr= (void*) &GLOBAL.enemyrate;
	variablePointers.insertNode("gb.d")->ptr= (void*) &GLOBAL.debugenabled;
	variablePointers.insertNode("gb.s")->ptr= (void*) &GLOBAL.soundenabled;
	variablePointers.insertNode("gb.cs")->ptr= (void*) &GLOBAL.consoleenabled;
	variablePointers.insertNode("gb.fs")->ptr= (void*) &GLOBAL.isfullscreen;
	variablePointers.insertNode("gb.qls")->ptr= (void*) &GLOBAL.questloopswitch;
	variablePointers.insertNode("gb.ls")->ptr= (void*) &GLOBAL.loopswitch;
	variablePointers.insertNode("gb.ls2")->ptr= (void*) &GLOBAL.loopswitch2;
	variablePointers.insertNode("gb.se")->ptr= (void*) &GLOBAL.spawnenemies;

	variablePointers.insertNode("cm.mdl")->ptr= (void*) &MAPFILES.currentmap->darknessLevel;

	variablePointers.insertNode("p.px")->ptr= (void*) &PLAYER.posx;
	variablePointers.insertNode("p.py")->ptr= (void*) &PLAYER.posy;
	variablePointers.insertNode("p.m")->ptr= (void*) &PLAYER.magic;
	variablePointers.insertNode("p.mm")->ptr= (void*) &PLAYER.maxmagic;
	variablePointers.insertNode("p.h")->ptr= (void*) &PLAYER.health;
	variablePointers.insertNode("p.mh")->ptr= (void*) &PLAYER.maxhealth;

	variablePointers.insertNode("p.a")->ptr= (void*) &PLAYER.air;
	variablePointers.insertNode("p.ma")->ptr= (void*) &PLAYER.maxair;
	variablePointers.insertNode("p.f")->ptr= (void*) &PLAYER.food;
	variablePointers.insertNode("p.g")->ptr= (void*) &PLAYER.gold;
	variablePointers.insertNode("p.s")->ptr= (void*) &PLAYER.stamina;
	variablePointers.insertNode("p.lm")->ptr= (void*) &PLAYER.lockmove;
	variablePointers.insertNode("p.d")->ptr= (void*) &PLAYER.direction;
	
	variablePointers.insertNode("ps.a")->ptr= (void*) &PLAYERSTATS.agility;
	variablePointers.insertNode("ps.c")->ptr= (void*) &PLAYERSTATS.constitution;
	variablePointers.insertNode("ps.d")->ptr= (void*) &PLAYERSTATS.dexterity;
	variablePointers.insertNode("ps.i")->ptr= (void*) &PLAYERSTATS.intelligence; 
	variablePointers.insertNode("ps.l")->ptr= (void*) &PLAYERSTATS.luck;
	variablePointers.insertNode("ps.s")->ptr= (void*) &PLAYERSTATS.strength;
	
	//below are HARD CODED, DO NOT CHANGE unless also changing MP.cpp -> executeScriptEffects
	*scriptCommands.insertNode("unlock-player")=1;
	*scriptCommands.insertNode("lock-player")=2;
	*scriptCommands.insertNode("move-player-relative")=3;
	*scriptCommands.insertNode("move-npc-absolute")=4;
	*scriptCommands.insertNode("msg")=5;
	*scriptCommands.insertNode("play-sound")=6;
	*scriptCommands.insertNode("screen-on")=7;
	*scriptCommands.insertNode("screen-off")=8;
	*scriptCommands.insertNode("addqls")=9;
	*scriptCommands.insertNode("play-music")=10;
	*scriptCommands.insertNode("stop-music")=11;
	*scriptCommands.insertNode("fade-in")=12;
	*scriptCommands.insertNode("fade-out")=13;
	*scriptCommands.insertNode("light-level")=14;
	*scriptCommands.insertNode("give-player-item")=15;
	*scriptCommands.insertNode("change-npc-dialog")=16;
	*scriptCommands.insertNode("spawn-off")=17;
	*scriptCommands.insertNode("spawn-on")=18;
	*scriptCommands.insertNode("wait")=19;
	*scriptCommands.insertNode("addls2")=20;
}

void exe::spawnenemy()
{
	int table[200][2];
	for (int a=0;a<200;a++)
	{
		table[a][0]=0;table[a][1]=0;
	}

	int count=0;
	LinkedListNode<npcstore> * newptr=INFOS.NPCSTORE.headptr;
	while (newptr!=NULL)
	{

		if (newptr->value->level<=PLAYER.level&&newptr->value->faction==NT_HOSTILE)
		{
			table[count][0]=newptr->value->id;
			table[count][1]=newptr->value->level;
			count++;
		}

		newptr=newptr->nextptr;
	}
	bsort1(table,count,true);

	float table2[10];
	table2[9]=30;
	table2[8]=40;
	table2[7]=50;
	table2[6]=60;
	table2[5]=65;
	table2[4]=70;
	table2[3]=75;
	table2[2]=80;
	table2[1]=85;
	table2[0]=100;

	int dropper=rand()%100;
	int choose=-1;
	for (int a=9;a>-1;a--)
	{
		if (dropper<=table2[a])
		{
			choose=a;break;
		}
	}

	if (choose==-1)
		choose=0;

	//if there arent enough npcs, choose the next best
	while (table[choose][0]==0)
	{
		if (choose==0)
			break;
		choose--;
	}
	if (table[choose][0]==0)
	{printf("\nWARNING! NO ITEMS TO SPAWN!");return;}

	NodeEnemy * newptr2=NPC.insertNode();
	newptr2->setvalues(table[choose][0],-1,-1,true);
	newptr2->faction=NT_HOSTILE;
}

//function which controls global events using global timer(count)
void exe::globalcount(void)
{
	//printf("\nS=%d",GLOBAL.loopswitch);
	if (GLOBAL.loopswitch==LS_NORMAL)
	{
		int temp=0;temp;

		//Food depletion
		if (PLAYERSTATS.survival==0)
			temp=50;
		else temp=50+PLAYERSTATS.survival*5;

		if ((GLOBAL.count%temp==0&&GLOBAL.count!=0)||PLAYER.food<=0)
		{
			if (PLAYER.food>=1)
				PLAYER.food--;
			else
			{
				if ((GLOBAL.count%10)==0&&GLOBAL.count!=0)
				{PLAYER.health-=PLAYER.maxhealth/4;CONSOLE.pushtext(false,0,TEXT_PLAYER_STARVE);}
			}
		}

		int ER=MAPFILES.currentmap->enemyCreationRate;
		//		int MEL=MAPFILES.currentmap->minEnemyLevel;

		//spawn enemy
		if (ER>=1&&GLOBAL.spawnenemies==true&&(GLOBAL.count%ER==0&&GLOBAL.count!=0))
		{
			spawnenemy();			
		}
		if (GLOBAL.count<=1000&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
		{GLOBAL.count++;}
		else 
			GLOBAL.count=0;
	}

}

//inits camera for use with game
void exe::vinit()
{
	//init display
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode( GL_MODELVIEW );
}

//inits the shop if it hasnt been done already - to be changed
void exe::initshop()
{//declare shop items
	shopitems.clear();
	shopspells.clear();
	shoppotions.clear();
	//	int a=0;
	char temp[200];
	FILE * itemz=NULL;
	_fopen_s(&itemz,"Data/CFG/shopitems.cfg","r");
	if (itemz==NULL)
	{EXEC.quit("itemzinit");}

	while (fscanf_s(itemz,"%s",temp,100)!=EOF)
	{
		char * commptr=NULL;
		commptr=strstr(temp,"//");
		if (commptr==NULL)
		{
			//make sure MAPFILES.currentmap->name/temp are both in same case, check for that
			if (strcmp(temp,MAPFILES.currentmap->name)!=0)
				break;

			while (fscanf_s(itemz,"%s",temp,100)!=EOF)
			{
				commptr=NULL;
				commptr=strstr(temp,"//");
				if (commptr==NULL)
				{
					if (strcmp(temp,"Weapons")==0)
					{
						int weaponid;
						while (fscanf_s(itemz,"%d",&weaponid,100)!=EOF)
						{
							if (weaponid==0)
								break;

							shopitems.insertNode()->setvalues(1,weaponid,-1,-1);

						}
					}
					else if (strcmp(temp,"Magic")==0)
					{
						int spellid;
						while (fscanf_s(itemz,"%d",&spellid,100)!=EOF)
						{
							if (spellid==0)
								break;
							shopspells.insertNode()->setvalues(1,spellid,-1,-1);
						}
					}

					else if (strcmp(temp,"Potions")==0)
					{
						int potionid;
						while (fscanf_s(itemz,"%d",&potionid,100)!=EOF)
						{
							if (potionid==0)
								break;
							shoppotions.insertNode()->setvalues(1,potionid,-1,-1);
						}
					}
				}
				else
				{
					while (1)
					{
						char b=1;
						fscanf_s(itemz,"%c",&b);
						if (b=='\n')
							break;
						fscanf_s(itemz,"*%s");
					}
				}
			}
		}
		else
		{
			while (1)
			{
				char b=1;
				fscanf_s(itemz,"%c",&b);
				if (b=='\n')
					break;
				fscanf_s(itemz,"*%s");
			}
		}
	}
	_fclose(itemz);
}

//inits linked lists
void exe::initlists(bool ignoreshopinit)
{
	//void readin(List *strings,char *input,int amount, int type,int x,int y)
	grounditems.clear();
	helditems.clear();
	NPC.clear();
	shopitems.clear();
	spellz.clear();

	mapnpcs.clear();
	if (shopitems.headptr==NULL&&ignoreshopinit==false)
		EXEC.initshop();
	SPELL.type=310;
	//ensures that no spell is usable before it is armed
	SPELL.mp=200000;
}

//inits cfg files
void exe::initextcfg()
{
	//check for comments and triple check for buffer overflows
	//	int b=0;

	//xml class instantiation
	xml *xmlc=new xml();
	xmlc->getfile("Data/CFG/NPCS.xml",true);
	INFOS.loadnpcs(xmlc);

	xmlc->getfile("Data/CFG/OBJECTS.xml",true);
	INFOS.loadobjects(xmlc);

	xmlc->getfile("Data/CFG/ARMOUR.xml",true);
	INFOS.loadarmour(xmlc);

	xmlc->getfile("Data/CFG/WEAPONS.xml",true);
	INFOS.loadweapons(xmlc);

	xmlc->getfile("Data/CFG/SPELLS.xml",true);
	INFOS.loadspells(xmlc);

	xmlc->getfile("Data/Maps/MAPCFG.xml",true);
	INFOS.loadmaps(xmlc);

	delete xmlc;

	if (INFOS.firstMapId==-1)
	{
		quit("\nError, firstMap not defined in mapcfg.xml");
	}
	EXEC.loadMap(INFOS.MAPSTOREPTR[INFOS.firstMapId]);


}

//gives 'fists' to player, and a bronze dagger
void exe::initweapons(void)
{
	giveweapon(200,false);
	giveweapon(201,true);
}

//inits all the signs to be used in the game
void exe::initsigns(void)
{
	int a=0;
	for (a=0;a<100;a++)
		strcpy(INFOS.signtext[a],"");
	for (a=0;a<51;a++)
		strcpy(INFOS.npctext[a],"");
	for (a=0;a<51;a++)
		strcpy(INFOS.talkingcharacterbuffer[a],"");


	FILE * texts=NULL;
	_fopen_s(&texts,"Data/CFG/signtext.cfg","r");
	if (texts==NULL)
	{EXEC.quit("signtext");}
	fscanf_s(texts,"%*s");

	char teststring[200];
	char teststring2[200];

	int count=-1;
	strcpy(teststring,"");
	while (fscanf_s(texts,"%s",teststring2,200)==1)
	{
		if (strcmp(teststring2,"-")==0)
		{
			if (count==0)strcat(INFOS.signtext[count],"\0");
			count++;
		}
		else if (strcmp(teststring2,"-")!=0)
		{
			strcat(INFOS.signtext[count],teststring2);strcat(INFOS.signtext[count]," ");
		}
	}

	_fopen_s(&texts,"Data/CFG/npctext.cfg","r");
	if (texts==NULL)
	{EXEC.quit("npctext");}
	fscanf_s(texts,"%*s");

	count=-1;

	strcpy(teststring,"");
	while (fscanf_s(texts,"%s",teststring2,200)==1)
	{
		if (strcmp(teststring2,"-")==0)
		{
			if (count==0)strcat(INFOS.npctext[count],"\0");
			count++;
		}
		else if (strcmp(teststring2,"-")!=0)
		{
			strcat(INFOS.npctext[count],teststring2);strcat(INFOS.npctext[count]," ");
		}
	}

	_fopen_s(&texts,"Data/CFG/talkingcharacter.cfg","r");
	if (texts==NULL)
	{EXEC.quit("talkingcharacter");}
	fscanf_s(texts,"%*s");

	count=-1;

	strcpy(teststring,"");
	while (fscanf_s(texts,"%s",teststring2,200)==1)
	{
		if (strcmp(teststring2,"-")==0)
		{
			if (count==0)strcat(INFOS.talkingcharacterbuffer[count],"\0");
			count++;
		}
		else if (strcmp(teststring2,"-")!=0)
		{
			strcat(INFOS.talkingcharacterbuffer[count],teststring2);strcat(INFOS.talkingcharacterbuffer[count]," ");
		}
	}
}

//called on a new game
void exe::initgame(void)
{
	int a;
	//running game gets reset in initvar, reinit it to the prev value
	int gbrg=GLOBAL.runninggame;
	strcpy(SPELL.image,"");
	strcpy(SPELL.image,"");

	initlists(false);
	initvars();
	if (gbrg==1)
		GLOBAL.runninggame=1;
	glutIgnoreKeyRepeat(0);	
	initextcfg();

	initweapons();
	initsigns();
	//inittextures();

	for (a=0;a<5;a++)
		strcpy(CONSOLE.textarray[a],"");
	vinit();
}

exitpoint * exe::findmap(int xpos,int ypos)
{
	if (MAPFILES.currentmap->PresetExitFile==NULL)
		return NULL;

	LinkedListNode<exitpoint> * newptr=MAPFILES.exitpoints.headptr;
	if (newptr==NULL)
		return false;

	while (newptr!=NULL)
	{
		if (newptr->value->xpos==xpos&&newptr->value->ypos==ypos)
			return newptr->value;
		newptr=newptr->nextptr;
	}

	return NULL;
}

//return the nearest enemy to attacker
NodeEnemy* exe::findnearest(NodeEnemy * attacker)
{
	LinkedListNode<NodeEnemy> * newptr=NPC.headptr;
	int lowdistance=1000;
	LinkedListNode<NodeEnemy>* lowptr=NULL;

	while (newptr!=NULL)
	{		
		if (newptr->value!=attacker&&newptr->value->faction!=attacker->faction&&newptr->value->faction!=NT_NEUTRAL)
		{
			int x=abs(attacker->xpos-newptr->value->xpos);
			int y=abs(attacker->ypos-newptr->value->ypos);
			if (lowdistance>(x+y))
			{lowdistance=x+y;lowptr=newptr;}
		}
		newptr=newptr->nextptr;
	}

	//check against player dist
	if (attacker->faction==NT_HOSTILE||(attacker->faction==NT_FRIENDLY&&lowdistance==1000))
	{
		int x=abs(attacker->xpos-PLAYER.posx);
		int y=abs(attacker->ypos-PLAYER.posy);
		if (lowdistance>(x+y))
		{
			//delete far enemies
			if ((x+y)>(attacker->viewdist*5))
				return NULL;
			return ((NodeEnemy*)0x01);
		}
	}
	//delete far enemies
	if (lowdistance>(attacker->viewdist*5))
		return NULL;
	return lowptr->value;
}

void exe::npcmain(void)
{
	int random=0;
	LinkedListNode<NodeEnemy> * attacker=NPC.headptr;
	LinkedListNode<NodeEnemy> * attacker2=NULL;
	while (attacker!=NULL)
	{
		attacker2=attacker->nextptr;
		if (attacker->value->faction==NT_NEUTRAL)
		{
			if (attacker->value->movetype==1)
			{
				random=rand()%100;
				if (random>65)
					;
				else
					randomnpc(attacker->value);
			}
		}
		else
		{
			NodeEnemy * target=findnearest(attacker->value);
			if (target==(NodeEnemy*)0x01)
			{	
				//return if player died
				if (attacker->value->enemymoveplayer(attacker->value)==false)
					return;
			}
			else if (target!=NULL)
			{
				LinkedListNode<NodeEnemy> * next=attacker2;
				if (next!=NULL)
				{
					if (next==attacker||next->value==target)
						next=next->nextptr;
				}

				bool killed=attacktype(attacker->value,target);								
				if ((attacker2->value==target||attacker2==attacker)&&killed)
					attacker2=next;

			}
			//possibly have counter for max static moves before delete, for now just delete
			else
			{
				CONSOLE.pushtext(true,3,"Enemy out of range, deleting");
				NPC.deleteNode(attacker);
				attacker=NULL;				
			}
			if (attacker!=NULL)
				attacker->value->checkenvenemy(attacker->value);
		}
		attacker=attacker2;
	}
}

void exe::rmsoundz()
{
	AVLTreeNode<SoundFile> * iter=soundz.getfirstnode();
	AVLTreeNode<SoundFile> * iter2=NULL;

	while (iter!=NULL)
	{
		SoundFile * hax=iter->value;

		if (hax->musicptr!=NULL)
		{
			EXEC.stopMusic(hax->musicptr);
			FMUSIC_FreeSong(hax->musicptr);
			hax->musicptr=NULL;
		}

		if (hax->soundptr!=NULL)
		{
			FSOUND_Sample_Free(hax->soundptr);
			hax->soundptr=NULL;
		}


		iter=iter2;
		if (iter==NULL)
			break;
		iter2=iter->nextInOrder();
	}
	soundz.clear();
}

void exe::rmtexturez()
{
	AVLTreeNode<TextureImage> * iter=texturez.getfirstnode();
	AVLTreeNode<TextureImage> * iter2=NULL;

	while (iter!=NULL)
	{
		if (iter->value->imageData!=NULL)
			free(iter->value->imageData);
		iter->value->imageData=NULL;

		iter=iter2;
		if (iter==NULL)
			break;
		iter2=iter->nextInOrder();
	}
	texturez.clear();
}

void exe::loadterraincase(int terrain,float alpha)
{
	switch(terrain)
	{
	case TT_GRASS: {glColor4f(0, 1, 0,alpha);break;}
	case TT_WATER: {glColor4f(0, 0, 1,alpha);break;}
	case TT_LAVA:{		glColor4f(1, 0, 0,alpha);break;}
	case TT_DESERT:{glColor4f(1, 1, 0,alpha);break;}
	case TREE:{glColor4f(.2, .6, .2,alpha);break;}
	case TT_DTREE:{glColor4f(.2, .6, .2,alpha);break;}
	case TT_MARSH:{glColor4f(.2, .6, .2,alpha);break;}
	case TT_MOUNTAIN:{glColor4f(.542,.269,.074,alpha);break;}
	case TT_SWALL:{glColor4f(.542,.269,.074,alpha);break;}
	case TT_BWALL:{glColor4f(.542,.269,.074,alpha);break;}
	case TT_MUD:{glColor4f(.642,.369,.174,alpha);break;}
	case TT_TOWN:{glColor4f(1,1,1,alpha);break;}
	case TT_BLACK:{glColor4f(0, 0, 0,alpha);break;}
	case TT_ROCK:{glColor4f(.4, .4, .4,alpha);break;}
	default:
		{
			if (terrain>=TT_COAST11&&terrain<=TT_COASTEDGE41)
				glColor4f(1, 1, 0,alpha);
			else
				glColor4f(0, .5, 1,alpha);
			break;
		}
	}
}

void exe::loadterraincase(int terrain)
{
	switch(terrain)
	{
	case TT_GRASS : {EXEC.loadTexture("Data/Images/Tiles/grass.tga");break;}
	case TT_WATER : {EXEC.loadTexture("Data/Images/Tiles/water.tga");break;}
	case TT_COAST11:{EXEC.loadTexture("Data/Images/Tiles/coast11.tga");break;}
	case TT_COAST12:{EXEC.loadTexture("Data/Images/Tiles/coast12.tga");break;}
	case TT_COAST13:{EXEC.loadTexture("Data/Images/Tiles/coast13.tga");break;}
	case TT_COAST14:{EXEC.loadTexture("Data/Images/Tiles/coast14.tga");break;}
	case TT_COAST21:{EXEC.loadTexture("Data/Images/Tiles/coast21.tga");break;}
	case TT_COAST22:{EXEC.loadTexture("Data/Images/Tiles/coast22.tga");break;}
	case TT_COAST23:{EXEC.loadTexture("Data/Images/Tiles/coast23.tga");break;}
	case TT_COAST24:{EXEC.loadTexture("Data/Images/Tiles/coast24.tga");break;}
	case TT_COAST25:{EXEC.loadTexture("Data/Images/Tiles/coast25.tga");break;}
	case TT_COAST26:{EXEC.loadTexture("Data/Images/Tiles/coast26.tga");break;}
	case TT_COAST31:{EXEC.loadTexture("Data/Images/Tiles/coast31.tga");break;}
	case TT_COAST32:{EXEC.loadTexture("Data/Images/Tiles/coast32.tga");break;}
	case TT_COAST33:{EXEC.loadTexture("Data/Images/Tiles/coast33.tga");break;}
	case TT_COAST34:{EXEC.loadTexture("Data/Images/Tiles/coast34.tga");break;}
	case TT_COAST41:{EXEC.loadTexture("Data/Images/Tiles/coast41.tga");break;}

	case TT_COASTEDGE11:{EXEC.loadTexture("Data/Images/Tiles/coastedge11.tga");break;}
	case TT_COASTEDGE12:{EXEC.loadTexture("Data/Images/Tiles/coastedge12.tga");break;}
	case TT_COASTEDGE13:{EXEC.loadTexture("Data/Images/Tiles/coastedge13.tga");break;}
	case TT_COASTEDGE14:{EXEC.loadTexture("Data/Images/Tiles/coastedge14.tga");break;}
	case TT_COASTEDGE21:{EXEC.loadTexture("Data/Images/Tiles/coastedge21.tga");break;}
	case TT_COASTEDGE22:{EXEC.loadTexture("Data/Images/Tiles/coastedge22.tga");break;}
	case TT_COASTEDGE23:{EXEC.loadTexture("Data/Images/Tiles/coastedge23.tga");break;}
	case TT_COASTEDGE24:{EXEC.loadTexture("Data/Images/Tiles/coastedge24.tga");break;}
	case TT_COASTEDGE25:{EXEC.loadTexture("Data/Images/Tiles/coastedge25.tga");break;}
	case TT_COASTEDGE26:{EXEC.loadTexture("Data/Images/Tiles/coastedge26.tga");break;}
	case TT_COASTEDGE31:{EXEC.loadTexture("Data/Images/Tiles/coastedge31.tga");break;}
	case TT_COASTEDGE32:{EXEC.loadTexture("Data/Images/Tiles/coastedge32.tga");break;}
	case TT_COASTEDGE33:{EXEC.loadTexture("Data/Images/Tiles/coastedge33.tga");break;}
	case TT_COASTEDGE34:{EXEC.loadTexture("Data/Images/Tiles/coastedge34.tga");break;}
	case TT_COASTEDGE41:{EXEC.loadTexture("Data/Images/Tiles/coastedge41.tga");break;}

	case TREE:{EXEC.loadTexture("Data/Images/Tiles/tree.tga");break;}
	case TT_DTREE:{EXEC.loadTexture("Data/Images/Tiles/dtree.tga");break;}
	case TT_ROCK:{EXEC.loadTexture("Data/Images/Tiles/rock.tga");break;}
	case TT_MUD:{EXEC.loadTexture("Data/Images/Tiles/mud.tga");break;}
	case TT_LAVA:{EXEC.loadTexture("Data/Images/Tiles/lava.tga");break;}
	case TT_DESERT:{EXEC.loadTexture("Data/Images/Tiles/desert.tga");break;}
	case TT_MOUNTAIN:{EXEC.loadTexture("Data/Images/Tiles/mountain.tga");break;}
	case TT_MARSH:{EXEC.loadTexture("Data/Images/Tiles/marsh.tga");break;}
	case TT_BWALL:{EXEC.loadTexture("Data/Images/Tiles/bwall.tga");break;}
	case TT_SWALL:{EXEC.loadTexture("Data/Images/Tiles/swall.tga");break;}
	case TT_TOWN:{EXEC.loadTexture("Data/Images/Tiles/town.tga");break;}
	case TT_BLACK:{EXEC.loadTexture("Data/Images/Tiles/black.tga");break;}
	case TT_DOOR:{EXEC.loadTexture("Data/Images/Other/doorclosed.tga");break;}
	case TT_ODOOR:{EXEC.loadTexture("Data/Images/Other/dooropen.tga");break;}
	case TT_TABLE:{EXEC.loadTexture("Data/Images/Other/table.tga");break;}
	case TT_BRIDGENS:{EXEC.loadTexture("Data/Images/Tiles/bridge_ns.tga");break;}
	case TT_BRIDGEWE:{EXEC.loadTexture("Data/Images/Tiles/bridge_we.tga");break;}
	case TT_LADDERU:{EXEC.loadTexture("Data/Images/Tiles/ladder_up.tga");break;}
	case TT_LADDERD:{EXEC.loadTexture("Data/Images/Tiles/ladder_down.tga");break;}
	case TT_FIREPLACE:{EXEC.loadTexture("Data/Images/Other/fireplace.tga");break;}
	case TT_DUNGEONTILE:{EXEC.loadTexture("Data/Images/Other/dungeon.tga");break;}
	case TT_TOWER:{EXEC.loadTexture("Data/Images/Tiles/tower.tga");break;}

	default:
		{EXEC.loadTexture("Data/Images/Tiles/black.tga");break;}
	}
}

//attack the coords x,y change npc to enemy if hit
void exe::attackenemyfunction(int x, int y,bool israrm)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_NOONE);
		return;
	}
	if (MAPFILES.MAPFILEENEMY[y][x]==NULL)
	{
		if (MAPFILES.MAPFILE[y][x]>=51)
		{CONSOLE.pushtext(false,0,TEXT_PLAYER_CANTATTACK);
		EXEC.loadSound(SND.misssound);return;}

		CONSOLE.pushtext(false,0,TEXT_NOONE);
		//playsound
		EXEC.loadSound(SND.misssound);
		return;
	}

	NodeEnemy * newptr=NULL;
	newptr=MAPFILES.MAPFILEENEMY[y][x];

	if (newptr==NULL)
	{
		CONSOLE.pushtext(false,0,TEXT_NOONE);return;
	}
	if (newptr->type==T_SIGN||newptr->type==T_TORCH)
	{
		CONSOLE.pushtext(false,0,TEXT_PLAYER_CANTATTACK);
		EXEC.loadSound(SND.misssound);
		return;
	}

	if (newptr->faction!=NT_HOSTILE)
		newptr->faction=NT_HOSTILE;
	dealdamage(newptr,israrm);
}

//move enemy towards player
//returns if the target was killed
bool exe::attacktype(NodeEnemy * attacker,NodeEnemy * thetarget)
{

	if (isnear(attacker->xpos,attacker->ypos,thetarget->xpos,thetarget->ypos))
	{
		if (MAPFILES.MAPFILE[attacker->ypos][attacker->xpos]==TT_LAVA)
			CONSOLE.pushtext(true,0,"moving attacker out of lava");
		else
		{
			//printf("npc attack");
			if (GLOBAL.loopswitch==LS_NORMAL)
			{
				return dealdamagefunction(attacker,thetarget);
			}			
		}
	}
	else
		moveenemy(attacker,thetarget);
	return false;
}

void exe::buypotion(objstore * newptr,int amount)
{
	if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
	{CONSOLE.pushtext(false,0,TEXT_INV_FULL);GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;}
	if (amount<=0)
	{CONSOLE.pushtext(false,0,TEXT_SPELL_EMPTY);GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;}

	int cost=newptr->cost*amount;
	if (PLAYER.gold<cost)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_AFFORD);
		glutPostRedisplay();
		return;
	}
	else
		PLAYER.gold-=cost;
	EXEC.loadSound(SND.buysound);

	char tmp[100];tmp[0]=0;
	char tempp[20];tempp[0]=0;
	strcpy(tmp,"You bought a ");
	strcat(tmp,newptr->name);

	strcat(tmp," for");
	sprintf(tempp," %d",cost);
	strcat(tmp,tempp);
	CONSOLE.pushtext(false,3,tmp);
	helditems.insertNode()->setvalues(amount,newptr->id,-1,-1);
	//deleteNode(&shopitems,count-1); 
	glutPostRedisplay();
	return;
}


void exe::buyspellhead(int y,int x)
{//initspell init spell
	int temp=0;
	temp+=x;
	temp+=y*5;


	NodeObject * thisspell1=shopspells[temp];
	splstore * thisspell=NULL;
	int nid=0;
	if (thisspell1!=NULL)
	{
		nid=thisspell1->id;
		while (nid>=100)
			nid-=100;
		thisspell=INFOS.SPLSTOREPTR[nid];

	}	

	if (PLAYER.hasSpellTable[nid])
	{
		CONSOLE.pushtext(false,0,TEXT_SPELL_HAVE);
		//GLOBAL.loopswitch=LS_NORMAL;
		glutPostRedisplay();return;}
	if (thisspell==NULL)
	{CONSOLE.pushtext(false,0,TEXT_SPELL_NOSPELL);glutPostRedisplay();return;}

	int cost=thisspell->cost;
	cost-=PLAYERSTATS.luck;
	if (cost<=10)
		cost=10;
	char tempp[20];char tmp[100];
	//GLOBAL.loopswitch=LS_NORMAL;
	if (PLAYER.gold<cost)
	{CONSOLE.pushtext(false,0,TEXT_ITEM_AFFORD);glutPostRedisplay();return;}
	else
	{		
		PLAYER.gold-=cost;
		//playsound
		EXEC.loadSound(SND.buysound);

		strcpy(tmp,"You bought ");
		strcat(tmp,thisspell->name);
		strcat(tmp," for");
		sprintf(tempp," %d",cost);
		strcat(tmp,tempp);
		CONSOLE.pushtext(false,3,tmp);
		PLAYER.hasSpellTable[nid]=true;		
	}

	glutPostRedisplay();
}

void exe::caststaticspell(int id,int manacost,int basedamage)
{
	PLAYER.regen=0;
	int amount=basedamage;
	char temp[100];
	char sp[20];
	if (id==499)
	{//black hole, damages all players/enemies in radius statically
		if (PLAYER.magic<manacost)
		{CONSOLE.pushtext(false,0,TEXT_SPELL_MISSED);return;}
		else PLAYER.magic=0;
		float amount2=(float)basedamage+((float)PLAYERSTATS.intelligence/4);
		amount2/=100;

		//all possible black hole damage squares, link to the enemy if its in it
		NodeEnemy *closearray[8];
		for (int a=0;a<8;a++)
			closearray[a]=NULL;
		int hitenemies=0;

		LinkedListNode<NodeEnemy> * newptr=NPC.headptr;
		while (newptr!=NULL)
		{		
			if ((newptr->value->xpos>=PLAYER.posx-1&&newptr->value->xpos<=PLAYER.posx+1)&&(newptr->value->ypos>=PLAYER.posy-1&&newptr->value->ypos<=PLAYER.posy+1))
			{
				closearray[hitenemies]=newptr->value;
				hitenemies++;	
			}

			newptr=newptr->nextptr;
		}

		if (hitenemies==0)
		{
			CONSOLE.pushtext(true,0,"bkhole cast, no enemies to hit!");
			return;
		}

		for (int a=0;a<hitenemies;a++)
		{
			basedamage=int(closearray[a]->enemymaxhealth*amount2);
			closearray[a]->enemyhealth-=basedamage;

			if (closearray[a]->enemyhealth<=0)
			{
				//playsound
				EXEC.loadSound(SND.death1);

				int nid=closearray[a]->id;
				while (nid>=100)
					nid-=100;
				npcstore * newptr=INFOS.NPCSTOREPTR[nid];
				if (newptr==NULL)
				{
					printf("\nERROR! NPC %d = NULL",nid);
					return;
				}

				char string[100];
				char tempp[100];
				//it is possible for a npc to off another npc with a spell, so check here
				if (SPELL2.active==0)
				{
					strcpy(string,"You killed ");
					strcat(string,newptr->name);
					strcat(string," with");
					sprintf(tempp," %d",basedamage);
					strcat(string,tempp);
					strcat(string," damage");
					CONSOLE.pushtext(false,2,string);
				}
				else
				{
					strcpy(string,newptr->name);
					strcat(string," killed with");
					sprintf(tempp," %d",basedamage);
					strcat(string,tempp);
					strcat(string," damage");
					CONSOLE.pushtext(false,3,string);
				}



				if (SPELL2.active==0)
				{					
					PLAYER.exp+=newptr->exp;
					strcpy(string,"You gain");
					sprintf(tempp," %d",newptr->exp);
					strcat(string,tempp);
					strcat(string," EXP");
					CONSOLE.pushtext(false,2,string);
				}

				dropitem(closearray[a]->id,closearray[a]->xpos,closearray[a]->ypos);
				MAPFILES.MAPFILEENEMY[closearray[a]->ypos][closearray[a]->xpos]=NULL;

				NPC.deleteNode(closearray[a]);
				closearray[a]=NULL;
			}
		}
		SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;
		return;
	}
	else if (id==450)
	{
		amount=basedamage;
		amount+=(((float)PLAYERSTATS.intelligence/100)*((float)PLAYER.maxhealth/2));
		if (PLAYER.health+amount==PLAYER.maxhealth+amount)
			amount=0;
		else if (PLAYER.health+amount>PLAYER.maxhealth)
		{
			amount=amount-(abs((PLAYER.health+amount)-PLAYER.maxhealth));
			if (amount<0)amount=0;
			else
				PLAYER.health=PLAYER.maxhealth;
		}
		else{PLAYER.health+=amount;}
		//playsound
		EXEC.loadSound(SND.healsound);

		PLAYER.magic-=manacost;
		strcpy(temp,"You healed ");
		sprintf(sp,"%d",amount);
		strcat(temp,sp);
		strcat(temp," HP");
		CONSOLE.pushtext(false,2,temp);
	}

	else if (id==451)
	{
		//playsound	
		EXEC.loadSound(SND.aircreate);

		amount=basedamage;
		amount+=PLAYERSTATS.intelligence/5;
		if ((PLAYER.air+amount)>PLAYER.maxair)
			amount=0;
		PLAYER.air+=amount;
		PLAYER.magic-=manacost;
		strcpy(temp,"You gained ");
		sprintf(sp,"%d",amount);
		strcat(temp,sp);
		strcat(temp," Air");
		CONSOLE.pushtext(false,2,temp);
	}

	else if (id==452)
	{
		amount=basedamage;
		amount+=PLAYERSTATS.intelligence/5;
		if (PLAYER.food+amount>PLAYER.maxfood*10)
			amount=0;
		else
			;
		PLAYER.food+=amount;
		PLAYER.magic-=manacost;
		//playsound
		EXEC.loadSound(SND.foodsound);

		strcpy(temp,"You created ");
		sprintf(sp,"%d",amount);
		strcat(temp,sp);
		strcat(temp," Food");
		CONSOLE.pushtext(false,2,temp);
	}
	spellz.clear();
	SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;
	glutPostRedisplay();			
}

void exe::castrangedspell()
{
	if (SPELL.active==0&&SPELL2.active==0)
		return;

	char stringz[100];char tempp[100];int random=0;
	PLAYER.regen=0;
	LinkedListNode<NodeObject> * spellptr=spellz.headptr;

	if (((SPELL.type<450&&SPELL.type>=400)||(SPELL.type>=490&&SPELL.type<=498)&&SPELL.active==1)||((SPELL2.type<450&&SPELL2.type>=400)||(SPELL2.type>=490&&SPELL2.type<=498)&&SPELL2.active==1))
	{
		if ((SPELL.type>=421&&SPELL.type<450)&&(PLAYER.magic<=4)&&spellptr->value->amount==1)
		{
			PLAYER.magic=0;
			CONSOLE.pushtext(false,0,TEXT_SPELL_DISINTEGRATE);
			spellz.clear();
			SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;
			glutPostRedisplay();
			return;
		}

		//		int count=-1;
		LinkedListNode<NodeObject> * spellptr=spellz.headptr;
		LinkedListNode<NodeObject> * nextspell=NULL;

		while (spellptr!=NULL)
		{
			nextspell=spellptr->nextptr;

			//printf("\nsx=%d,sy=%d",spellptr->value->xpos,spellptr->value->ypos);

			if (spellptr->value->id==1)
			{spellptr->value->xpos--;spellptr->value->ypos++;}
			else if (spellptr->value->id==2)
				spellptr->value->ypos++;
			else if (spellptr->value->id==3)
			{spellptr->value->xpos++;spellptr->value->ypos++;}
			else if (spellptr->value->id==4)
				spellptr->value->xpos--;
			else if (spellptr->value->id==6)
				spellptr->value->xpos++;
			else if (spellptr->value->id==7)
			{spellptr->value->xpos--;spellptr->value->ypos--;}
			else if (spellptr->value->id==8)
				spellptr->value->ypos--;
			else if (spellptr->value->id==9)
			{spellptr->value->xpos++;spellptr->value->ypos--;}
			//printf("\nsy=%d,sx=%d",spellptr->value->ypos,spellptr->value->xpos);

			//hard code hax
redoplayertest:
			if (spellptr->value->ypos==PLAYER.posy&&spellptr->value->xpos==PLAYER.posx&&SPELL2.active==1)
			{
				random=rand()%100;
				if (random<=20&&(spellptr->value->id<=490))
				{
					CONSOLE.pushtext(false,0,TEXT_PLAYER_SPELLMISSED);
					spellz.deleteNode(spellptr);
					spellptr=NULL;
				}

				else
				{
					int basedamage;
					if (SPELL2.active==1)
					{
						basedamage=SPELL2.basedamage;
						if (SPELL2.type>=421&&SPELL2.type<431)
						{basedamage*=5;}
						else if (SPELL2.type>=431&&SPELL2.type<450)
						{basedamage*=10;}
					}
					else
					{
						basedamage=SPELL.basedamage;
						if (SPELL.type>=421&&SPELL.type<431)
						{basedamage*=5;}
						else if (SPELL.type>=431&&SPELL.type<450)
						{basedamage*=10;}
					}
					PLAYER.health-=basedamage;
					if (PLAYER.health<=0){CONSOLE.pushtext(true,0,"die1");
					EXEC.loadSound(SND.death4);
					EXEC.playerdeath();}//died
					if (PLAYER.health>0)
					{
						strcpy(stringz,"You were dealt");
						sprintf(tempp," %d",basedamage);
						strcat(stringz,tempp);
						strcat(stringz," damage");
						CONSOLE.pushtext(false,1,stringz);

						if ((SPELL2.type==403||SPELL2.type==424||SPELL2.type==434)&&(SPELL2.basedamage>=2&&SPELL2.active==1))
						{
							MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
							if (spellptr->value->id==1&&MAPFILES.MAPFILE[PLAYER.posy+1][PLAYER.posx-1]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy+1][PLAYER.posx-1]==NULL)
							{PLAYER.posx--;PLAYER.posy++;}
							else if (spellptr->value->id==2&&MAPFILES.MAPFILE[PLAYER.posy+1][PLAYER.posx]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy+1][PLAYER.posx]==NULL)
								PLAYER.posy++;
							else if (spellptr->value->id==3&&MAPFILES.MAPFILE[PLAYER.posy+1][PLAYER.posx+1]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy+1][PLAYER.posx+1]==NULL)
							{PLAYER.posy++;PLAYER.posx++;}
							else if (spellptr->value->id==4&&MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx-1]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx-1]==NULL)
								PLAYER.posx--;
							else if (spellptr->value->id==6&&MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx+1]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx+1]==NULL)
								PLAYER.posx++;
							else if (spellptr->value->id==7&&MAPFILES.MAPFILE[PLAYER.posy-1][PLAYER.posx-1]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy-1][PLAYER.posx-1]==NULL)
							{PLAYER.posy--;PLAYER.posx--;}
							else if (spellptr->value->id==8&&MAPFILES.MAPFILE[PLAYER.posy-1][PLAYER.posx]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy-1][PLAYER.posx]==NULL)
								PLAYER.posy--;
							else if (spellptr->value->id==9&&MAPFILES.MAPFILE[PLAYER.posy-1][PLAYER.posx+1]<9&&MAPFILES.MAPFILEENEMY[PLAYER.posy-1][PLAYER.posx+1]==NULL)
							{PLAYER.posy--;PLAYER.posx++;}
							MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
							SPELL2.basedamage/=2;
						}

						else
						{
							spellz.deleteNode(spellptr);
							spellptr=NULL;
						}
					}

					if (SPELL.type==403&&SPELL.type==424&&SPELL.type==434)
					{
						if (SPELL.basedamage<=1)
						{SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
						else
							SPELL.basedamage/=2;
					}
				}
			}

			//delete node if it is heading off the map
			if (spellptr!=NULL&&((spellptr->value->ypos<=0&&spellptr->value->id>=7)||(spellptr->value->ypos>=MAPFILES.emapheight()&&spellptr->value->id<=3)||\
				(spellptr->value->xpos<=0&&(spellptr->value->id==1||spellptr->value->id==4||spellptr->value->id==7))||\
				(spellptr->value->xpos>=MAPFILES.emapwidth()&&(spellptr->value->id==3||spellptr->value->id==6||spellptr->value->id==9))))
			{
				CONSOLE.pushtext(false,0,TEXT_SPELL_MISSED);
				spellz.deleteNode(spellptr);
				spellptr=NULL;

			}

			//attack an enemy if there is one there
			else if (spellptr!=NULL&&MAPFILES.MAPFILEENEMY[spellptr->value->ypos][spellptr->value->xpos]!=NULL&&MAPFILES.MAPFILEENEMY[spellptr->value->ypos][spellptr->value->xpos]!=(NodeEnemy*)0x01)
			{
				spellattack(MAPFILES.MAPFILEENEMY[spellptr->value->ypos][spellptr->value->xpos],spellptr);
			}

			//stupid
			else if (spellptr!=NULL&&(spellptr->value->ypos==PLAYER.posy&&spellptr->value->xpos==PLAYER.posx&&SPELL2.active==1))
				goto redoplayertest;
			//delete the spell if it hits non passable terrain
			else if (spellptr!=NULL&&((MAPFILES.MAPFILE[spellptr->value->ypos][spellptr->value->xpos]==TT_TOWN||MAPFILES.passable(spellptr->value->ypos,spellptr->value->xpos,(NodeEnemy*)0x01)==false)&&(SPELL.active==1||SPELL2.active==1)))
			{
				CONSOLE.pushtext(false,0,TEXT_SPELL_MISSED);
				spellz.deleteNode(spellptr);
				spellptr=NULL;
			}

			//players spells can only last a certain distance, delete if it gets too far away
			else if (spellptr!=NULL&&((PLAYER.posx-15>spellptr->value->xpos||PLAYER.posx+15<spellptr->value->xpos)||(PLAYER.posy-15>spellptr->value->ypos||PLAYER.posy+15<spellptr->value->ypos)&&(SPELL.active==1||SPELL2.active==1)))
			{
				CONSOLE.pushtext(false,0,TEXT_SPELL_MISSED);
				spellz.deleteNode(spellptr);
				spellptr=NULL;
			}

			if (spellptr!=NULL)
			{
				if (SPELL.type>=421&&SPELL.type<431&&spellptr->value->amount==1)
					PLAYER.magic-=5;
				if (SPELL.type>=431&&SPELL.type<450&&spellptr->value->amount==1)
					PLAYER.magic-=20;

				if ((PLAYER.magic<=0)&&(SPELL.type>=421&&SPELL.type<450)&&spellptr->value->amount==1)
				{
					PLAYER.magic=0;
					CONSOLE.pushtext(false,0,TEXT_SPELL_DISINTEGRATE);
					SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;
					glutPostRedisplay();
					return;
				}

				//printf("\ncount=%d,%d",spellz.count,spellcount);
				if (spellz.headptr==NULL||spellptr==NULL)
				{SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
			}
			spellptr=nextspell;
		}
	}
	else
	{SPELL.active=0;return;}
	if (spellz.headptr==NULL){SPELL.active=0;SPELL2.active=0;GLOBAL.loopswitch=LS_NORMAL;return;}
	//printf("\nsp=%d,sp2=%d",SPELL.active,SPELL2.active);
	glutPostRedisplay();
}

void exe::loadspell(int type,int direction,int ypos,int xpos,int fromplayer)
{
	if (SPELL.active==1||SPELL2.active==1)
	{CONSOLE.pushtext(false,0,"already active");return;}
	spellz.clear();

	int nid=type;
	while (nid>=100)
		nid-=100;
	if (strcmp(SPELL.image,"")==0&&(fromplayer==1||fromplayer==-1))
	{
		if (type==0)
		{
			strcpy(SPELL.image,"");
			strcpy(SPELL.name,"");
			return;
		}
		else
		{
			strcpy(SPELL.image,INFOS.SPLSTOREPTR[nid]->path);
			strcpy(SPELL.name,INFOS.SPLSTOREPTR[nid]->name);
			SPELL.mp=INFOS.SPLSTOREPTR[nid]->mp;
			SPELL.basedamage=INFOS.SPLSTOREPTR[nid]->basedamage;
			if (direction==-1&&fromplayer==-1)return;
		}
	}

	if (type==453&&fromplayer==1)
	{
		int nid=53;
		int manacost=INFOS.SPLSTOREPTR[nid]->mp;
		//amount is cost and multipliers, so just call amount
		int amount=INFOS.SPLSTOREPTR[nid]->cost;
		if (fromplayer==1)
			amount+=PLAYERSTATS.intelligence/2;else amount+=50;
		int directionx=0;
		int directiony=0;
		if (direction==1)
		{directionx=-1;directiony=+1;}
		else if (direction==2)
		{directiony=+1;}
		else if (direction==3)
		{directionx=+1;directiony=+1;}
		else if (direction==4)
		{directionx=-1;}
		else if (direction==6)
		{directionx=+1;}
		else if (direction==7)
		{directionx=-1;directiony=-1;}
		else if (direction==8)
		{directiony=+1;}
		else if (direction==9)
		{directionx=+1;directiony=-1;}
		char sp[20];
		char temp[120];
		NodeObject * newptr=MAPFILES.MAPFILEITEM[ypos+directiony][xpos+directionx];
		if (newptr==NULL)
		{CONSOLE.pushtext(false,0,TEXT_ITEM_NOOBJECT);return;}
		if (newptr->type==T_GOLD||newptr->type==T_FOOD)
		{CONSOLE.pushtext(false,0,TEXT_ITEM_CONVERT);return;}

		nid=newptr->id;
		while (nid>=100)
			nid-=100;

		float cost=INFOS.WEPSTOREPTR[nid]->cost;
		cost/=2;
		cost=cost*((float)amount/100);

		if (direction!=0)PLAYER.magic-=manacost;
		PLAYER.gold+=(int)cost;
		MAPFILES.MAPFILEITEM[newptr->ypos][newptr->xpos]=NULL;
		//playsound
		EXEC.loadSound(SND.goldsound);

		strcpy(temp,"You converted ");
		sprintf(sp,"%d",(int)cost);
		strcat(temp,sp);
		strcat(temp," gold from a ");
		strcat(temp,newptr->str);
		CONSOLE.pushtext(false,2,temp);
		grounditems.deleteNode(newptr);
		return;
	}

	else if (type==454&&fromplayer==1)
	{
		int nid=54;
		int manacost=INFOS.SPLSTOREPTR[nid]->mp;
		//check mana
		if (PLAYER.magic<manacost)
		{
			CONSOLE.pushtext(false,1,TEXT_PLAYER_MP);
			return;
		}

		//amount is cost and multipliers, so just call amount
		int amount=INFOS.SPLSTOREPTR[nid]->cost;
		char temp[100];
		char sp[50];

		int xdir=0;
		int ydir=0;

		switch(direction)
		{
		case 1:{xdir-=amount;ydir+=amount;break;}
		case 2:{ydir+=amount;break;}
		case 3:{xdir+=amount;ydir+=amount;break;}
		case 4:{xdir-=amount;break;}
		case 6:{xdir+=amount;break;}
		case 7:{xdir-=amount;ydir-=amount;break;}
		case 8:{ydir-=amount;break;}
		case 9:{xdir+=amount;ydir-=amount;break;}
		default:
			{
				printf("\nTELEPORT ERROR!");
				return;
			}
		};

		const int xcomb=xpos+xdir;
		const int ycomb=ypos+ydir;


		//check borders first
		if ((xcomb<0||xcomb>=MAPFILES.emapwidth())||(ycomb<0||ycomb>=MAPFILES.emapheight()))
		{
			CONSOLE.pushtext(false,1,TEXT_PLAYER_MOVE);
			return;
		}

		//check if passable + not water
		else if (MAPFILES.passable(ycomb,xcomb,NULL)==false||MAPFILES.MAPFILE[ycomb][xcomb]==TT_WATER)
		{
			CONSOLE.pushtext(false,1,TEXT_PLAYER_MOVE);
			return;
		}

		//cant teleport around maps other than world map
		else if (MAPFILES.currentmap->id!=INFOS.firstMapId)
		{
			EXEC.loadSound(SND.misssound);
			CONSOLE.pushtext(false,0,TEXT_SPELL_CANTCAST);
		}
		//make it so
		else
		{
			EXEC.loadSound(SND.teleportsound);
			strcpy(temp,"You moved ");
			sprintf(sp,"%d",amount);
			strcat(temp,sp);
			strcat(temp," Spaces");
			CONSOLE.pushtext(false,2,temp);

			MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
			PLAYER.posy=ycomb;
			PLAYER.posx=xcomb;
			MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
			PLAYER.magic-=manacost;
			ypos;
		}
		return;
	}
	else
	{
		int nid=type;
		while (nid>=100)
			nid-=100;
		//printf("*");
		char stype[10];sprintf(stype,"%d",type);
		if (fromplayer==1)
		{
			SPELL.type=type;
			SPELL.mp=INFOS.SPLSTOREPTR[nid]->mp;
			strcpy(SPELL.image,INFOS.SPLSTOREPTR[nid]->path);
			strcpy(SPELL.name,INFOS.SPLSTOREPTR[nid]->name);
		}
		if (fromplayer==0)
		{
			SPELL2.type=type;
			SPELL2.mp=INFOS.SPLSTOREPTR[nid]->mp;
			SPELL2.basedamage=INFOS.SPLSTOREPTR[nid]->basedamage;
			strcpy(SPELL2.image,INFOS.SPLSTOREPTR[nid]->path);
			strcpy(SPELL2.name,INFOS.SPLSTOREPTR[nid]->name);
		}


		if ((SPELL.type==420&&fromplayer==1)||(SPELL2.type==420&&fromplayer==0))
		{
			int loop;
			for (loop=1;loop<=9;loop++)
			{if (loop!=5)
			spellz.insertNode()->setvalues(fromplayer,loop,xpos,ypos);
			}
		}
		else
		{
			spellz.insertNode()->setvalues(fromplayer,direction,xpos,ypos);
			if (((SPELL.type==422||SPELL.type==432)&&fromplayer==1)||((SPELL2.type==422||SPELL2.type==432)&&fromplayer==0))
			{
				if (direction==1)
					spellz.insertNode()->setvalues(fromplayer,2,xpos,ypos);
				else if (direction==2)
					spellz.insertNode()->setvalues(fromplayer,3,xpos,ypos);
				else if (direction==3)
					spellz.insertNode()->setvalues(fromplayer,6,xpos,ypos);
				else if (direction==6)
					spellz.insertNode()->setvalues(fromplayer,9,xpos,ypos);
				else if (direction==9)
					spellz.insertNode()->setvalues(fromplayer,8,xpos,ypos);
				else if (direction==8)
					spellz.insertNode()->setvalues(fromplayer,7,xpos,ypos);
				else if (direction==7)
					spellz.insertNode()->setvalues(fromplayer,4,xpos,ypos);
				else if (direction==4)
					spellz.insertNode()->setvalues(fromplayer,1,xpos,ypos);

				if ((SPELL.type==432&&fromplayer==1)||(SPELL2.type==432&&fromplayer==0))
				{
					if (direction==1)
						spellz.insertNode()->setvalues(fromplayer,4,xpos,ypos);
					else if (direction==2)
						spellz.insertNode()->setvalues(fromplayer,1,xpos,ypos);
					else if (direction==3)
						spellz.insertNode()->setvalues(fromplayer,2,xpos,ypos);
					else if (direction==6)
						spellz.insertNode()->setvalues(fromplayer,3,xpos,ypos);
					else if (direction==9)
						spellz.insertNode()->setvalues(fromplayer,6,xpos,ypos);
					else if (direction==8)
						spellz.insertNode()->setvalues(fromplayer,9,xpos,ypos);
					else if (direction==7)
						spellz.insertNode()->setvalues(fromplayer,8,xpos,ypos);
					else if (direction==4)
						spellz.insertNode()->setvalues(fromplayer,7,xpos,ypos);
				}
			}
		}

		nid=type;
		while (nid>=100)
			nid-=100;
		if (fromplayer==1)SPELL.active=1;else SPELL2.active=1;
		SPELL.basedamage=INFOS.SPLSTOREPTR[nid]->basedamage;

		//printf("\nSP=%d,M=%d",SPELL.mp,PLAYER.magic);
		if (direction==0||direction==5)
		{if (GLOBAL.debugenabled==true)printf("direction error");SPELL.active=0;SPELL2.active=0;return;}
		if (PLAYER.magic>=SPELL.mp&&direction!=0&&fromplayer==1)
			PLAYER.magic-=SPELL.mp;

	}
	//printf("\nsa=%d,spellza=%d",SPELL2.active,spellz.count);	
	if (SPELL.type==400||SPELL.type==421||SPELL.type==431)
	{EXEC.loadSound(SND.fireballsound);}
	if (SPELL.type==401||SPELL.type==422||SPELL.type==432)
	{EXEC.loadSound(SND.icesound);}
	if (SPELL.type==402||SPELL.type==423||SPELL.type==433)
	{EXEC.loadSound(SND.lightningsound);}
	if (SPELL.type==403||SPELL.type==424||SPELL.type==434)
	{EXEC.loadSound(SND.windsound);}
}

void exe::givehelditems(int id)
{
	if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
		CONSOLE.pushtext(true,0,TEXT_INV_FULL);
	else
	{
		bool success=helditems.insertNode()->setvalues(1,id,-1,-1);	

		if (success==false)
			helditems.deleteNode(helditems.tailptr);
	}
}

void exe::talkfunct(int x,int y)
{
	if (PLAYER.posx+x<0||PLAYER.posx+x>=MAPFILES.emapwidth()||PLAYER.posy+y<0||PLAYER.posy+y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_NOTALK);
		GLOBAL.loopswitch=LS_NORMAL;
		glutPostRedisplay();return;
	}
	//double talk distance if talking over a counter
	if (MAPFILES.MAPFILE[PLAYER.posy+y][PLAYER.posx+x]==TT_TABLE&&MAPFILES.MAPFILEENEMY[PLAYER.posy+y][PLAYER.posx+x]==NULL)
	{x*=2;y*=2;}

	NodeEnemy * newptr=MAPFILES.MAPFILEENEMY[PLAYER.posy+y][PLAYER.posx+x];
	if (newptr==NULL)
		CONSOLE.pushtext(false,0,TEXT_NOTALK);
	else if (newptr->type==T_SIGN||newptr->type==T_TORCH)
		CONSOLE.pushtext(false,0,TEXT_CANTTALK);
	else if (newptr->faction==NT_HOSTILE)
		CONSOLE.pushtext(false,0,TEXT_NORESPONSE);
	else if (newptr->faction==NT_FRIENDLY)
		CONSOLE.pushtext(false,0,TEXT_NOTHING);
	else
	{
		//printf("found");
		switch (newptr->talktype)
		{
		case -1: 
			{
				CONSOLE.pushtext(false,0,TEXT_CANTTALK);
				break;
			}

		case 100:
			{
				CONSOLE.pushtext(false,0,TEXT_SHOP_WEAPON);
				GLOBAL.loopswitch=LS_BUYORSELL;
				glutPostRedisplay();
				return;
			}
		case 101: 
			{
				CONSOLE.pushtext(false,0,TEXT_SHOP_MAGIC);
				GLOBAL.loopswitch=LS_BUYSPELLMENU;
				glutPostRedisplay();
				return;
			}

		case 103: 
			{
				CONSOLE.pushtext(false,0,TEXT_SHOP_GROCER);
				GLOBAL.loopswitch=LS_BUYFOOD;
				glutPostRedisplay();
				return;
			}

		case 104: 
			{
				CONSOLE.pushtext(false,0,TEXT_SHOP_CASINO);
				GLOBAL.loopswitch=LS_CASINOCHOICE;
				glutPostRedisplay();
				return;
			}

		case 105: 
			{
				CONSOLE.pushtext(false,0,TEXT_SHOP_POTION);
				GLOBAL.loopswitch=LS_POTIONMENU;
				glutPostRedisplay();
				return;
			}

		default: {

			if (newptr->talktype>=0&&newptr->talktype<100)
			{
				EXEC.loadSound(SND.maximize);
				GLOBAL.loopswitch=LS_TALKING;
				strcpy(INFOS.talknpcbuffer,INFOS.npctext[newptr->talktype]);
				strcpy(INFOS.talkingcharacterbuffer2,INFOS.talkingcharacterbuffer[newptr->talktype]);
				strcpy(INFOS.talkingcharacterpicture,newptr->pic);

				glutPostRedisplay();return;
			}
			break;
				 }
		}
	}
	GLOBAL.loopswitch=LS_NORMAL;
	glutPostRedisplay();return;
}



void exe::opendoorfunction(int x,int y)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_NOTDOOR);
	}
	else
	{

		if (MAPFILES.MAPFILEENEMY[y][x]!=NULL&&(MAPFILES.MAPFILE[y][x]==TT_DOOR||MAPFILES.MAPFILE[y][x]==TT_ODOOR))
		{CONSOLE.pushtext(false,0,TEXT_DOORFORCED);return;}

		if (MAPFILES.MAPFILE[y][x]==TT_DOOR)
		{

			//playsound
			EXEC.loadSound(SND.opensound);
			MAPFILES.MAPFILE[y][x]=TT_ODOOR;CONSOLE.pushtext(false,0,TEXT_OPENDOOR);
		}

		else if (MAPFILES.MAPFILE[y][x]==TT_ODOOR)
		{
			//playsound
			EXEC.loadSound(SND.closesound);
			MAPFILES.MAPFILE[y][x]=TT_DOOR;CONSOLE.pushtext(false,0,TEXT_CLOSEDDOOR);
		}

		else
			CONSOLE.pushtext(false,0,TEXT_NOTDOOR);
	}
	GLOBAL.loopswitch=LS_NORMAL;
	glutPostRedisplay();return;
}


void exe::lookfunction(int x, int y)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_NOTALK);
	}
	else
	{
		char temp[200];

		if (MAPFILES.MAPFILEENEMY[y][x]!=NULL&&MAPFILES.MAPFILEENEMY[y][x]!=(NodeEnemy*)0x01)
		{
			NodeEnemy * newptr=MAPFILES.MAPFILEENEMY[y][x];

			//sign
			if (newptr->type==T_SIGN)
			{
				CONSOLE.pushtext(false,0,TEXT_SIGN);
				CONSOLE.pushtext(false,0,INFOS.signtext[newptr->talktype]);
				return;
			}

			else
			{
				strcpy(temp,"You see: ");
				strcat(temp,newptr->str);
				CONSOLE.pushtext(false,0,temp);
				return;
			}
		}
		else if (MAPFILES.MAPFILEITEM[y][x]!=NULL)
		{

			NodeObject * newptr=MAPFILES.MAPFILEITEM[y][x];

			strcpy(temp,"You see: ");
			strcat(temp,newptr->str);
			CONSOLE.pushtext(false,0,temp);
			glutPostRedisplay();
			return;
		}

		int temp2=MAPFILES.MAPFILE[y][x];
		strcpy(temp,"You see: ");

		if (temp2==TT_GRASS)
			strcat(temp,"Grass");
		else if (temp2>=TT_COAST11&&temp2<=TT_COASTEDGE41)
			strcat(temp,"Shore line");
		else if (temp2==TT_DESERT)
			strcat(temp,"Sand");
		else if (temp2==TT_MUD)
			strcat(temp,"A Path");
		else if (temp2==TT_LAVA)
			strcat(temp,"Lava");
		else if (temp2==TT_TOWN)
			strcat(temp,"A town");
		else if (temp2==TT_WATER)
			strcat(temp,"Water");
		else if (temp2==TT_ROCK)
			strcat(temp,"Rock");
		else if (temp2==TREE)
			strcat(temp,"A Tree");
		else if (temp2==TT_DTREE)
			strcat(temp,"A Desert Tree");
		else if (temp2==TT_MOUNTAIN)
			strcat(temp,"A Mountain Range");
		else if (temp2==TT_BWALL)
			strcat(temp,"A Brick Wall");
		else if (temp2==TT_SWALL)
			strcat(temp,"A Stone Wall");
		else if (temp2==TT_DOOR||temp2==TT_ODOOR)
			strcat(temp,"A Door");
		else if (temp2==TT_BRIDGENS||temp2==TT_BRIDGEWE)
			strcat(temp,"A Bridge");
		else if (temp2==TT_LADDERU||temp2==TT_LADDERD)
			strcat(temp,"A Ladder");
		else if (temp2==TT_TABLE)
			strcat(temp,"A Table");
		else if (temp2==TT_MARSH)
			strcat(temp,"Marsh");
		else if (temp2==TT_BLACK)
			strcat(temp,"The End of the Universe");
		else if (temp2==TT_FIREPLACE)
			strcat(temp,"A Fireplace");
		else if (temp2==TT_TOWER)
			strcat(temp,"A Tower");
		else if (temp2==TT_DUNGEONTILE)
			strcat(temp,"A Dungeon");
		else	
			strcat(temp,"Ground");
		CONSOLE.pushtext(false,0,temp);
	}
}

void exe::clearoldtextures()
{
	AVLTreeNode<TextureImage> * iterator=texturez.getfirstnode();
	AVLTreeNode<TextureImage> * iterator2=NULL;
	//stop rotations while clearing tree

	//get the average usage of each of the textures, cut any textures below the average
	int averagecount=0;
	int averagenum=0;

	iterator2=iterator->nextInOrder();
	while (iterator!=NULL)
	{	
		TextureImage * hax=iterator->value;

		averagecount+=hax->usage;
		averagenum++;

		iterator=iterator2;
		if (iterator==NULL)
			break;
		iterator2=iterator->nextInOrder();
	}

	//if average < min, then return, dont bother
	int average=averagecount/averagenum;
	if (average<=HCVARS.TEXTUREUSAGEMIN)
		return;

	iterator=texturez.getfirstnode();
	iterator2=iterator->nextInOrder();
	while (iterator!=NULL)
	{	
		TextureImage * hax=iterator->value;
		//trim old/unused sounds

		if (hax->usage<=average)
		{
			if (hax->imageData!=NULL)
				free(hax->imageData);
			hax->imageData=NULL;
			texturez.deleteNode(iterator->key);
		}
		else
			hax->usage=0;

		iterator=iterator2;
		if (iterator==NULL)
			break;
		iterator2=iterator->nextInOrder();
	}
}

void exe::clearoldsounds()
{
	AVLTreeNode<SoundFile> * iterator=soundz.getfirstnode();
	AVLTreeNode<SoundFile> * iterator2=NULL;


	//get the average usage of each of the textures, cut any textures below the average
	int averagecount=0;
	int averagenum=0;

	iterator2=iterator->nextInOrder();
	while (iterator!=NULL)
	{	
		SoundFile * hax=iterator->value;
		//trim old/unused sounds

		averagecount+=hax->usage;
		averagenum++;


		iterator=iterator2;
		if (iterator==NULL)
			break;
		iterator2=iterator->nextInOrder();
	}

	//if average < min, then return, dont bother
	int average=averagecount/averagenum;
	if (average<=HCVARS.SOUNDUSAGEMIN)
		return;

	iterator=soundz.getfirstnode();
	iterator2=iterator->nextInOrder();
	while (iterator!=NULL)
	{	
		SoundFile * hax=iterator->value;
		//trim old/unused sounds

		if (hax->usage<=average)
		{
			if (hax->musicptr!=NULL)
			{
				EXEC.stopMusic(hax->musicptr);
				FMUSIC_FreeSong(hax->musicptr);
				hax->musicptr=NULL;
			}

			if (hax->soundptr!=NULL)
			{
				FSOUND_Sample_Free(hax->soundptr);
				hax->soundptr=NULL;
			}
			soundz.deleteNode(iterator->key);			
		}
		else
			hax->usage=0;

		iterator=iterator2;
		if (iterator==NULL)
			break;
		iterator2=iterator->nextInOrder();
	}
}

inline void exe::FSOUND_Init(int a, int b, int c)
{
	//init FMOD
	FMOD::System_Create(&fmodsystem);// create an instance of the game engine
	fmodsystem->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

inline void exe::FMUSIC_StopSong(FMOD::Sound * mptr)
{
	fmodsystem->
}

bool exe::stopMusic(const char * filename)
{
	SoundFile * sas=soundz[filename];
	FMUSIC_StopSong (sas->musicptr);
	return true;
}

bool exe::stopMusic(FMUSIC_MODULE * mptr)
{
	FMUSIC_StopSong (mptr);
	return true;
}


inline void exe::loadSound(const char *filename)
{
	if (GLOBAL.soundenabled==false)
		return;
	SoundFile * sas=NULL;
	sas=soundz[filename];
	//if texture is here, good, otherwise nuke it if its old
	int volume=((float)GLOBAL.mastervolume/100)*(float)GLOBAL.soundvolume;
	loadSound(filename,volume);	
}

inline void exe::loadSound(const char *filename,int volume)
{
	SoundFile * sas=NULL;
	sas=soundz[filename];
	//if texture is here, good, otherwise nuke it if its old
	FSOUND_SetSFXMasterVolume(volume*2); 

	if (sas!=NULL)
	{
		FSOUND_PlaySound(FSOUND_FREE, sas->soundptr);
		//set an arbitrary cap
		if (sas->usage<HCVARS.SOUNDUSAGEMAX)
			sas->usage++;
	}
	else
	{		
		soundz.insertNode(filename);
		EXEC.loadSound(soundz[filename],filename);
	}
}


bool exe::loadSound(SoundFile *sound, const char *filename)
{
	sound->soundptr = FSOUND_Sample_Load(FSOUND_UNMANAGED, filename, FSOUND_NORMAL | FSOUND_HW2D, 0, 0);  
	if (!sound->soundptr)
	{
		printf("\nDidnt load sound successfully!");
		return false;
	}
	FSOUND_PlaySound(FSOUND_FREE, sound->soundptr);
	return true;
}


inline bool exe::loadMusic(const char *filename)
{
	SoundFile * sas=NULL;
	sas=soundz[filename];

	if (sas!=NULL)
	{
		//if texture is here, good, otherwise nuke it if its old
		int volume=((float)GLOBAL.mastervolume/100)*(float)GLOBAL.musicvolume;
		FMUSIC_SetMasterVolume (sas->musicptr, volume);
	}

	if (sas!=NULL)
	{

		FMUSIC_SetLooping (sas->musicptr, true);
		FMUSIC_PlaySong(sas->musicptr);

		if (sas->usage<HCVARS.SOUNDUSAGEMAX)
			sas->usage++;
	}
	else
	{
		soundz.insertNode(filename);
		EXEC.loadMusic(soundz[filename],filename);
	}
	return true;
}


bool exe::loadMusic(SoundFile *sound, const char *filename)
{
	sound->musicptr=FMUSIC_LoadSong(filename);
	if (!sound->musicptr)
	{
		printf("\ndidnt load music successfully");
		return false;
	}

	int volume=((float)GLOBAL.mastervolume/100)*(float)GLOBAL.musicvolume;
	FMUSIC_SetMasterVolume (sound->musicptr, volume);
	FMUSIC_SetLooping (sound->musicptr, true);
	FMUSIC_PlaySong(sound->musicptr);
	return true;
}


inline void exe::loadTexture(char *filename)
{
	if (filename==NULL)
		return;
	else if (*filename==NULL)
	{
		printf("\nnon valid filename!");
		return;
	}

	TextureImage * sas=NULL;
	sas=texturez[filename];
	//if texture is here, use it, otherwise load it
	if (sas!=NULL)
	{
		glBindTexture(GL_TEXTURE_2D, sas->texID);
		//set an arbitrary cap
		if (sas->usage<HCVARS.TEXTUREUSAGEMAX)
			sas->usage++;
	}
	else
	{
		TextureImage * currtex=texturez.insertNode(filename);
		if (texturez[filename]==NULL)
		{
			printf("\n----------");

			AVLTreeNode<TextureImage> * bok=texturez.getfirstnode();
			while (bok!=NULL)
			{
				printf("\nSK=%s",bok->key);
				bok=bok->nextInOrder();
			}

			printf("\nERROR,cant find %s",filename);
			return;
		}

		EXEC.loadTexture(currtex,filename);
		printf("");
	}
}


bool exe::loadTexture(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{   
	char * F2=NULL;
	mystrdup(&F2,filename);
	if (texture==NULL)
	{
		printf("\nERROR! COULD NOT FIND TEXTURE!");

		myfree(&F2);
		return false;
	}
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

redo:
	FILE *file = NULL;
	_fopen_s(&file,F2, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		//if cant be found, load it with texture error anyway
		printf("\nWARNING! TEXTURE %s NOT FOUND",F2);	
		mystrdup(&F2,"Data/Images/Other/texerror.tga");
		goto redo;		
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		_fclose(file);	
		myfree(&F2);
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	if (texture->imageData!=NULL)
		delete[] texture->imageData;
	texture->imageData=new GLubyte[imageSize];


	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			delete[] texture->imageData;						// If So, Release The Image Dat

		_fclose(file);										// Close The File
		myfree(&F2);
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture->texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture->texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture->bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture->width, texture->height, 0, type, GL_UNSIGNED_BYTE, texture->imageData);
	myfree(&F2);
	return true;											// Texture Building Went Ok, Return True
}

bool exe::moveplayer(int &px,int &py,int key)
{
	//temp x and y position for player
	int tx,ty;
	//relative movement
	int rx,ry;
	tx=ty=0;
	rx=ry=0;

	tx=px;
	ty=py;

	int direction=5;

	if (key==GLUT_KEY_LEFT)
	{direction=4;tx--;rx--;}
	else if (key==GLUT_KEY_RIGHT)
	{direction=6;tx++;rx++;}
	else if (key==GLUT_KEY_UP)
	{direction=8;ty--;ry--;}
	else if (key==GLUT_KEY_DOWN)
	{direction=2;ty++;ry++;}
	else if (key==GLUT_KEY_HOME)
	{direction=4;tx--;ty--;rx--;ry--;}
	else if (key==GLUT_KEY_PAGE_DOWN)
	{direction=6;tx++;ty++;rx++;ry++;}
	else if (key==GLUT_KEY_END)
	{direction=4;tx--;ty++;rx--;ry++;}
	else if (key==GLUT_KEY_PAGE_UP)
	{direction=6;tx++;ty--;rx++;ry--;}
	else 
	{GLOBAL.loopswitch=LS_PASS;return false;}

	if (tx<0||tx>=MAPFILES.emapwidth()||ty<0||ty>=MAPFILES.emapheight())
	{GLOBAL.loopswitch=LS_PASS;return false;}

	if (MAPFILES.MAPFILE[ty][tx]==TT_MARSH)
	{
		if (PLAYER.stamina>=HCVARS.marshstamdec)
		{PLAYER.stamina-=HCVARS.marshstamdec;CONSOLE.pushtext(false,1,TEXT_PLAYER_MARSH);}
		else if (PLAYER.stamina>0)
		{PLAYER.stamina=0;CONSOLE.pushtext(false,1,TEXT_PLAYER_MARSH);}
	}

	if (tx<0||ty<0||tx>=MAPFILES.emapwidth()||ty>=MAPFILES.emapheight())
	{GLOBAL.loopswitch=LS_PASS;return false;}

	if (MAPFILES.passable(ty,tx,(NodeEnemy*)0x01)==false)
	{GLOBAL.loopswitch=LS_PASS;return false;}

	//swap NT_FRIENDLY players 
	bool isfriend=false;
	if (MAPFILES.MAPFILEENEMY[ty][tx]!=NULL)
	{
		if (MAPFILES.MAPFILEENEMY[ty][tx]->faction!=NT_FRIENDLY)
		{GLOBAL.loopswitch=LS_PASS;return false;}
		else if (MAPFILES.MAPFILEENEMY[ty][tx]->faction==NT_FRIENDLY)
		{
			isfriend=true;
			CONSOLE.pushtext(true,3,"Swapping pos with non-NT_HOSTILE");
		}
	}

	//only take stamina away if can dash, else do normal step
	//cant dash in water
	//stop dashing if there are npcs in the way
	if (MAPFILES.MAPFILE[ty][tx]==TT_WATER)
		PLAYER.dash=0;
	else if (PLAYER.dash==1&&(MAPFILES.MAPFILEENEMY[ty][tx]!=NULL||MAPFILES.MAPFILEENEMY[ty+ry][tx+rx]!=NULL))
		PLAYER.dash=0;

	if (MAPFILES.passable(ty+ry,tx+rx,(NodeEnemy*)0x01)&&PLAYER.dash==1&&MAPFILES.MAPFILE[ty+ry][tx+rx]!=TT_WATER)
	{
		//can do dash, check for stam
		if (PLAYER.stamina<=0)
		{
			CONSOLE.pushtext(false,1,TEXT_PLAYER_TIRED);
			PLAYER.dash=0;
		}
		else
		{
			tx+=rx;ty+=ry;PLAYER.stamina--;
		}
	}

	GLOBAL.loopswitch=LS_NORMAL;

	while (px!=tx||py!=ty)
	{
		MAPFILES.MAPFILEENEMY[py][px]=NULL;

		if (isfriend==true)
		{
			MAPFILES.MAPFILEENEMY[ty][tx]->xpos=px;
			MAPFILES.MAPFILEENEMY[ty][tx]->ypos=py;
			MAPFILES.MAPFILEENEMY[py][px]=MAPFILES.MAPFILEENEMY[ty][tx];
		}

		if (px<tx)px++;
		else if (px>tx)px--;

		if (py<ty)py++;
		else if (py>ty)py--;

		//px=tx;py=ty;

		MAPFILES.MAPFILEENEMY[py][px]=(NodeEnemy*)0x01;

		if (testsquareexit())
			break;
	}
	PLAYER.direction=direction;
	glutPostRedisplay();
	return true;
}

bool exe::testsquareexit(void)
{
	exitpoint * newptr=findmap(PLAYER.posx,PLAYER.posy);
	if (newptr==NULL)
		return false;

	if (newptr->forceType==1)
	{
		MAPFILES.rearmx=0;
		MAPFILES.rearmy=0;
		GLOBAL.loopswitch=LS_EXITMAP;
		return true;
	}

	else if (newptr->forceType==2)
	{
		MAPFILES.rearmy=0;
		GLOBAL.loopswitch=LS_PASS;

		EXEC.loadmapcurrenttile();
		return true;
	}

	return false;
}
#endif
