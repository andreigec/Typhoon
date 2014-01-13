//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _KEYBOARD_CPP
#define _KEYBOARD_CPP

//controls special keyboard keys
void special(int key,int x,int y)
{x;y;
//printf("\nskey=%d",key);

if ((PLAYER.lockmove==1||GLOBAL.fadeamount>0)&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
return;

switch (GLOBAL.loopswitch)
{
case LS_DEATHSCREEN:
	{
	}
case LS_INGAMEMENU:
	{
		if (key==106)
			CONSOLE.currentconsolecarat=0;
		else if (key==107)
			CONSOLE.currentconsolecarat=(signed)strlen(CONSOLE.currentconsole);

		else if (key==GLUT_KEY_UP)
		{if (strcmp(CONSOLE.prevconsole,"\0")!=0){strcpy(CONSOLE.currentconsole,CONSOLE.prevconsole);CONSOLE.currentconsolecarat=(signed)strlen(CONSOLE.currentconsole);}else{;}glutPostRedisplay();}

		else if (key==GLUT_KEY_LEFT&&CONSOLE.currentconsolecarat>=1)
			CONSOLE.currentconsolecarat--;
		else if (key==GLUT_KEY_RIGHT&&CONSOLE.currentconsolecarat<CONSOLE.maxstring&&((signed)strlen(CONSOLE.currentconsole)>CONSOLE.currentconsolecarat))
			CONSOLE.currentconsolecarat++;
		//printf("\nCC=%d",CONSOLE.currentconsolecarat);
		glutPostRedisplay();
		return;
	}
case LS_CASINOPOKER:
	{
		if (GLOBAL.loopswitch2==2)
		{
			if (MAPFILES.rearmy==0)
			{
				if (MAPFILES.rearmx>0&&key==GLUT_KEY_LEFT)
					MAPFILES.rearmx--;
				else if (MAPFILES.rearmx<4&&key==GLUT_KEY_RIGHT)
					MAPFILES.rearmx++;
				else if (MAPFILES.rearmy==0&&key==GLUT_KEY_UP)
					MAPFILES.rearmy=1;
			}
			else
			{
				if (MAPFILES.rearmy==1&&key==GLUT_KEY_DOWN)
					MAPFILES.rearmy=0;

			}

		}
		else if (GLOBAL.loopswitch2==3||GLOBAL.loopswitch2==5)
		{
			if (MAPFILES.rearmx==1&&key==GLUT_KEY_LEFT)
				MAPFILES.rearmx--;
			else if (MAPFILES.rearmx==0&&key==GLUT_KEY_RIGHT)
				MAPFILES.rearmx++;
		}
		else if (GLOBAL.loopswitch2==4)
		{
			if (MAPFILES.rearmx>=1&&key==GLUT_KEY_LEFT)
				MAPFILES.rearmx--;
			else if (MAPFILES.rearmx<=1&&key==GLUT_KEY_RIGHT)
				MAPFILES.rearmx++;
		}
		//printf("\nspecial-cas");
		glutPostRedisplay();
		return;
	}
case LS_POTIONSHOP:
	{
		if (GLOBAL.loopswitch2==0)
		{
			if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>0)
				MAPFILES.rearmx--;
			else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<shoppotions.getCount()-1)
				MAPFILES.rearmx++;
			glutPostRedisplay();
			return;
		}
	}

case LS_EXITMAP:
	{
		if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<1)
			MAPFILES.rearmy++;

		glutPostRedisplay();
		return;
	}
case LS_BUYSPELLMENU:
	{
		if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<1)
			MAPFILES.rearmy++;
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;

		glutPostRedisplay();
		return;
	}
case LS_POTIONMENU:
	{
		if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<1)
			MAPFILES.rearmy++;
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;

		glutPostRedisplay();
		return;
	}
case LS_BUYORSELL:
	{
		if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=1)
			MAPFILES.rearmy++;
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;

		glutPostRedisplay();
		return;
	}

case LS_OPENING:
	{
		if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=1)
		{MAPFILES.rearmx--;if (GLOBAL.runninggame==0&&MAPFILES.rearmx==2)MAPFILES.rearmx-=2;}
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<5)
		{MAPFILES.rearmx++;if (GLOBAL.runninggame==0&&MAPFILES.rearmx==1)MAPFILES.rearmx+=2;}
		glutPostRedisplay();
		return;
	}

case LS_BUYFOOD:
	{
		if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<5)
			MAPFILES.rearmy++;
		glutPostRedisplay();
		return;
	}

case LS_OPTIONS:
	{
		if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<6)
			MAPFILES.rearmy++;
		else if (key==GLUT_KEY_LEFT&&MAPFILES.rearmy>=3&&MAPFILES.rearmy<6)
		{
			int val=0;
			if (MAPFILES.rearmy==3)
			{
				if (GLOBAL.soundvolume>0)
				GLOBAL.soundvolume-=20;
				val=GLOBAL.soundvolume;
			}
			else if (MAPFILES.rearmy==4)
			{
				if (GLOBAL.musicvolume>0)
				GLOBAL.musicvolume-=20;
				val=GLOBAL.musicvolume;
			}
			else if (MAPFILES.rearmy==5)
			{
				if (GLOBAL.mastervolume>0)
				GLOBAL.mastervolume-=20;
				val=GLOBAL.mastervolume;
			}
			EXEC.loadSound(SND.buysound,val);
		}
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmy>=3&&MAPFILES.rearmy<6)
		{
			int val=0;
			if (MAPFILES.rearmy==3)
			{
				if (GLOBAL.soundvolume<100)
				GLOBAL.soundvolume+=20;
				val=GLOBAL.soundvolume;
			}
			else if (MAPFILES.rearmy==4)
			{
				if (GLOBAL.musicvolume<100)
				GLOBAL.musicvolume+=20;
				val=GLOBAL.musicvolume;
			}
			else if (MAPFILES.rearmy==5)
			{
				if (GLOBAL.mastervolume<100)
				GLOBAL.mastervolume+=20;
				val=GLOBAL.mastervolume;
			}
			EXEC.loadSound(SND.buysound,val);
		}
		glutPostRedisplay();
		return;
	}

case LS_BUYING:
	{
		if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=1)
		{MAPFILES.rearmx--;glutPostRedisplay();}
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<=3)
		{MAPFILES.rearmx++;glutPostRedisplay();}
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
		{MAPFILES.rearmy--;glutPostRedisplay();}
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
		{MAPFILES.rearmy++;glutPostRedisplay();}
		glutPostRedisplay();
		return;
	}

case LS_SELLING:
	{
		if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=1)
		{MAPFILES.rearmx--;glutPostRedisplay();}
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<=3)
		{MAPFILES.rearmx++;glutPostRedisplay();}
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
		{MAPFILES.rearmy--;glutPostRedisplay();}
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
		{MAPFILES.rearmy++;glutPostRedisplay();}
		glutPostRedisplay();
		return;
	}

case LS_BUYSPELL:
	{
		if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=1)
		{MAPFILES.rearmx--;glutPostRedisplay();}
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<=3)
		{MAPFILES.rearmx++;glutPostRedisplay();}
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
		{MAPFILES.rearmy--;glutPostRedisplay();}
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
		{MAPFILES.rearmy++;glutPostRedisplay();}
		glutPostRedisplay();
		return;
	}

case LS_USEMENU:
	{
		int lastxt=MAPFILES.rearmx;int lastyt=MAPFILES.rearmy;
		if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=0)
			MAPFILES.rearmx--;
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<=3)
			MAPFILES.rearmx++;
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=0)
			MAPFILES.rearmy--;
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
			MAPFILES.rearmy++;

		//TODO:hard code bounds
		if ((MAPFILES.rearmx==-1&&MAPFILES.rearmy==-1)||(MAPFILES.rearmx>=2&&MAPFILES.rearmy==-1)||(MAPFILES.rearmx==-1&&MAPFILES.rearmy==4))
		{MAPFILES.rearmx=lastxt;MAPFILES.rearmy=lastyt;}
		else
			glutPostRedisplay();
		return;
	}

case LS_DROP:
	{
		if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=1)
		{MAPFILES.rearmx--;glutPostRedisplay();}
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<=3)
		{MAPFILES.rearmx++;glutPostRedisplay();}
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
		{MAPFILES.rearmy--;glutPostRedisplay();}
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
		{MAPFILES.rearmy++;glutPostRedisplay();}
		return;
	}

case LS_STATS:
	{
		if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
		{MAPFILES.rearmy--;glutPostRedisplay();}
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
		{MAPFILES.rearmy++;glutPostRedisplay();}
		return;
	}

case LS_CASINOCHOICE:
	{
		if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
		{MAPFILES.rearmy--;glutPostRedisplay();}
		else if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=0)
		{MAPFILES.rearmy++;glutPostRedisplay();}
		return;
	}

case LS_SPELLS:
	{
		if (key==GLUT_KEY_DOWN&&MAPFILES.rearmy<=3)
			MAPFILES.rearmy++;
		else if (key==GLUT_KEY_UP&&MAPFILES.rearmy>=1)
			MAPFILES.rearmy--;
		else if (key==GLUT_KEY_RIGHT&&MAPFILES.rearmx<=3)
			MAPFILES.rearmx++;
		else if (key==GLUT_KEY_LEFT&&MAPFILES.rearmx>=1)
			MAPFILES.rearmx--;
		//drawstatsinventory();
		glutPostRedisplay();
		return;
	}

case LS_TALKOP:
	{//printf("\nMP=%d",SPELL.mp);
		if (key==GLUT_KEY_LEFT)
		{CONSOLE.pushtext(true,3,"Talking Left");EXEC.talkfunct(-1,0);}
		else if (key==GLUT_KEY_RIGHT)
		{CONSOLE.pushtext(true,3,"Talking Right");EXEC.talkfunct(1,0);}
		else if (key==GLUT_KEY_UP)
		{CONSOLE.pushtext(true,3,"Talking Up");EXEC.talkfunct(0,-1);}
		else if (key==GLUT_KEY_DOWN)
		{CONSOLE.pushtext(true,3,"Talking Down");EXEC.talkfunct(0,1);}
		else if (key==GLUT_KEY_PAGE_UP)
		{CONSOLE.pushtext(true,3,"Talking Up-Right");EXEC.talkfunct(1,-1);}
		else if (key==GLUT_KEY_PAGE_DOWN)
		{CONSOLE.pushtext(true,3,"Talking Down-Right");EXEC.talkfunct(1,1);}
		else if (key==GLUT_KEY_HOME)
		{CONSOLE.pushtext(true,3,"Talking Up-Left");EXEC.talkfunct(-1,-1);}
		else if (key==GLUT_KEY_END)
		{CONSOLE.pushtext(true,3,"Talking Down-Left");EXEC.talkfunct(-1,1);}
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT);
		GLOBAL.loopswitch=LS_NORMAL;
		}		
		
		glutPostRedisplay();
		return;
	}

case LS_LOOK:
	{
		if (key==GLUT_KEY_LEFT)
		{EXEC.lookfunction(PLAYER.posx-1,PLAYER.posy);}
		else if (key==GLUT_KEY_RIGHT)
		{EXEC.lookfunction(PLAYER.posx+1,PLAYER.posy);}
		else if (key==GLUT_KEY_UP)
		{EXEC.lookfunction(PLAYER.posx,PLAYER.posy-1);}
		else if (key==GLUT_KEY_DOWN)
		{EXEC.lookfunction(PLAYER.posx,PLAYER.posy+1);}
		else if (key==GLUT_KEY_PAGE_UP)
		{EXEC.lookfunction(PLAYER.posx+1,PLAYER.posy-1);}
		else if (key==GLUT_KEY_PAGE_DOWN)
		{EXEC.lookfunction(PLAYER.posx+1,PLAYER.posy+1);}
		else if (key==GLUT_KEY_HOME)
		{EXEC.lookfunction(PLAYER.posx-1,PLAYER.posy-1);}
		else if (key==GLUT_KEY_END)
		{EXEC.lookfunction(PLAYER.posx-1,PLAYER.posy+1);}
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT);
		}
			GLOBAL.loopswitch=LS_NORMAL;
		
		glutPostRedisplay();
		return;
	}

case LS_OPENDOOR:
	{
		if (key==GLUT_KEY_LEFT)
		{EXEC.opendoorfunction(PLAYER.posx-1,PLAYER.posy);}
		else if (key==GLUT_KEY_RIGHT)
		{EXEC.opendoorfunction(PLAYER.posx+1,PLAYER.posy);}
		else if (key==GLUT_KEY_UP)
		{EXEC.opendoorfunction(PLAYER.posx,PLAYER.posy-1);}
		else if (key==GLUT_KEY_DOWN)
		{EXEC.opendoorfunction(PLAYER.posx,PLAYER.posy+1);}
		else if (key==GLUT_KEY_PAGE_UP)
		{EXEC.opendoorfunction(PLAYER.posx+1,PLAYER.posy-1);}
		else if (key==GLUT_KEY_PAGE_DOWN)
		{EXEC.opendoorfunction(PLAYER.posx+1,PLAYER.posy+1);}
		else if (key==GLUT_KEY_HOME)
		{EXEC.opendoorfunction(PLAYER.posx-1,PLAYER.posy-1);}
		else if (key==GLUT_KEY_END)
		{EXEC.opendoorfunction(PLAYER.posx-1,PLAYER.posy+1);}
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT);
		}
		GLOBAL.loopswitch=LS_NORMAL;
			
		glutPostRedisplay();
		return;
	}


case LS_ATTACKRS:
	{
		char lattack[100];
		strcpy(lattack,INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->name);
		if (key==GLUT_KEY_LEFT)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx-1,PLAYER.posy,true);}
		else if (key==GLUT_KEY_RIGHT)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx+1,PLAYER.posy,true);}
		else if (key==GLUT_KEY_UP)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx,PLAYER.posy-1,true);}
		else if (key==GLUT_KEY_DOWN)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx,PLAYER.posy+1,true);}
		else if (key==GLUT_KEY_PAGE_UP)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx+1,PLAYER.posy-1,true);}
		else if (key==GLUT_KEY_PAGE_DOWN)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx+1,PLAYER.posy+1,true);}
		else if (key==GLUT_KEY_HOME)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx-1,PLAYER.posy-1,true);}
		else if (key==GLUT_KEY_END)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx-1,PLAYER.posy+1,true);}
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT2);
		}
		GLOBAL.loopswitch=LS_NORMAL;

		glutPostRedisplay();
		return;
	}

case LS_ATTACKLS:
	{
		char lattack[100];
		strcpy(lattack,INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->name);
		if (key==GLUT_KEY_LEFT)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx-1,PLAYER.posy,false);}
		else if (key==GLUT_KEY_RIGHT)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx+1,PLAYER.posy,false);}
		else if (key==GLUT_KEY_UP)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx,PLAYER.posy-1,false);}
		else if (key==GLUT_KEY_DOWN)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx,PLAYER.posy+1,false);}
		else if (key==GLUT_KEY_PAGE_UP)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx+1,PLAYER.posy-1,false);}
		else if (key==GLUT_KEY_PAGE_DOWN)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx+1,PLAYER.posy+1,false);}
		else if (key==GLUT_KEY_HOME)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx-1,PLAYER.posy-1,false);}
		else if (key==GLUT_KEY_END)
		{CONSOLE.pushtext(true,3,"Attacking with:");CONSOLE.pushtext(true,0,lattack);EXEC.attackenemyfunction(PLAYER.posx-1,PLAYER.posy+1,false);}
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT);
			GLOBAL.loopswitch=LS_NORMAL;
		}

		if (GLOBAL.loopswitch!=LS_NORMAL&&EQUIPMENT.RARM.id!=200)
		{
			GLOBAL.loopswitch=LS_ATTACKRS;
			char tempstr[100];
			strcpy(tempstr,"Press direction to attack with ");
			strcat(tempstr,INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->name);
			CONSOLE.pushtext(false,0,tempstr);
		}
		else
			GLOBAL.loopswitch=LS_NORMAL;

		glutPostRedisplay();
		return;
	}

case LS_CAST:
	{//printf("\nMP=%d",SPELL.mp);
		if (key==GLUT_KEY_LEFT)
		{CONSOLE.pushtext(true,3,"Casting Left");EXEC.loadspell(SPELL.type,4,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_RIGHT)
		{CONSOLE.pushtext(true,3,"Casting Right");EXEC.loadspell(SPELL.type,6,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_UP)
		{CONSOLE.pushtext(true,3,"Casting Up");EXEC.loadspell(SPELL.type,8,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_DOWN)
		{CONSOLE.pushtext(true,3,"Casting Down");EXEC.loadspell(SPELL.type,2,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_PAGE_UP)
		{CONSOLE.pushtext(true,3,"Casting Up-Right");EXEC.loadspell(SPELL.type,9,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_PAGE_DOWN)
		{CONSOLE.pushtext(true,3,"Casting Down-Right");EXEC.loadspell(SPELL.type,3,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_HOME)
		{CONSOLE.pushtext(true,3,"Casting Up-Left");EXEC.loadspell(SPELL.type,7,PLAYER.posy,PLAYER.posx,1);}
		else if (key==GLUT_KEY_END)
		{CONSOLE.pushtext(true,3,"Casting Down-Left");EXEC.loadspell(SPELL.type,1,PLAYER.posy,PLAYER.posx,1);}
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT);
		}
		GLOBAL.loopswitch=LS_NORMAL;
				
		glutPostRedisplay();
		return;
	}

case LS_PICKUP:
	{	
		if (key==GLUT_KEY_LEFT)
			EXEC.pickupfunction(PLAYER.posx-1,PLAYER.posy);
		else if (key==GLUT_KEY_RIGHT)
			EXEC.pickupfunction(PLAYER.posx+1,PLAYER.posy);
		else if (key==GLUT_KEY_UP)
			EXEC.pickupfunction(PLAYER.posx,PLAYER.posy-1);
		else if (key==GLUT_KEY_DOWN)
			EXEC.pickupfunction(PLAYER.posx,PLAYER.posy+1);
		else if (key==GLUT_KEY_PAGE_UP)
			EXEC.pickupfunction(PLAYER.posx+1,PLAYER.posy-1);
		else if (key==GLUT_KEY_PAGE_DOWN)
			EXEC.pickupfunction(PLAYER.posx+1,PLAYER.posy+1);
		else if (key==GLUT_KEY_HOME)
			EXEC.pickupfunction(PLAYER.posx-1,PLAYER.posy-1);
		else if (key==GLUT_KEY_END)
			EXEC.pickupfunction(PLAYER.posx-1,PLAYER.posy+1);
		else
		{
			CONSOLE.pushtext(false,3,TEXT_ABORT);
		}
		GLOBAL.loopswitch=LS_NORMAL;
				
		glutPostRedisplay();
		return;
	}
case LS_HELPSCREEN:
	{
		glutPostRedisplay();
		return;
	}

default:
	{
		//help screen
		if (key==GLUT_KEY_F1)
		{
			GLOBAL.loopswitch=LS_HELPSCREEN;
			glutPostRedisplay();
			return;
		}
		
		//movement
		else if (key==GLUT_KEY_LEFT||key==GLUT_KEY_RIGHT||key==GLUT_KEY_UP||key==GLUT_KEY_DOWN||key==GLUT_KEY_HOME||key==GLUT_KEY_END||key==GLUT_KEY_PAGE_UP||key==GLUT_KEY_PAGE_DOWN)
		{
			if (SPELL.active==0&&SPELL2.active==0)
			{
			GLOBAL.loopswitch=LS_NORMAL;
			PLAYER.lastx=PLAYER.posx;
			PLAYER.lasty=PLAYER.posy;
			EXEC.moveplayer(PLAYER.posx,PLAYER.posy,key);
			
			}
		}

		glutPostRedisplay();
		return;
	}
}
}

//regular keyboard commands
void normal(unsigned char key, int x, int y)
{
	//first check for fullscreening
	if (key==13)
	{
		int mod=glutGetModifiers();
		if (mod == (GLUT_ACTIVE_ALT))
		{
			if ((GLOBAL.isfullscreen)==false)
			{CONSOLE.pushtext(false,3,TEXT_ENABLEFULLSCREEN);GLOBAL.isfullscreen=true;}
			else
			{CONSOLE.pushtext(false,3,TEXT_DISABLEFULLSCREEN);GLOBAL.isfullscreen=false;}

			initmode();
			glutPostRedisplay();		
			return;
		}
	}

	switch (GLOBAL.loopswitch)
	{
	
	case LS_DEATHSCREEN:
		{
			if (key==13)
			{
				ANIMATION.openinganimationsetup();
				GLOBAL.loopswitch=LS_OPENING;
				glutPostRedisplay();
			}
			return;
		}

	case LS_BUYORSELL:
		{
			if (key==27)
				GLOBAL.loopswitch=LS_PASS;
			if (key==13)
			{
				if (MAPFILES.rearmy==0)
				{GLOBAL.loopswitch=LS_BUYING;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}
				else if (MAPFILES.rearmy==1)
				{GLOBAL.loopswitch=LS_SELLING;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}
				else if (MAPFILES.rearmy==2)
				{CONSOLE.pushtext(false,0,TEXT_TY);GLOBAL.loopswitch=LS_PASS;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}

			}
			glutPostRedisplay();return;
		}

	case LS_POTIONMENU:
		{
			if (key==27)
				GLOBAL.loopswitch=LS_PASS;
			if (key==13)
			{
				if (MAPFILES.rearmy==0)
				{GLOBAL.loopswitch=LS_POTIONSHOP;potiontemp[0]=0;GLOBAL.loopswitch2=0;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}
				else if (MAPFILES.rearmy==1)
				{CONSOLE.pushtext(false,0,TEXT_TY);GLOBAL.loopswitch=LS_PASS;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}

			}
			glutPostRedisplay();return;
		}

	case  LS_POTIONSHOP:
		{
			if (key==27)
			{
				if (GLOBAL.loopswitch2==0)
				{GLOBAL.loopswitch=LS_PASS;CONSOLE.pushtext(false,0,TEXT_TY);}
				else if (GLOBAL.loopswitch2==1)
					GLOBAL.loopswitch2=0;
			}
			else if (key==8&&GLOBAL.loopswitch2==1)
			{
				potiontemp[strlen(potiontemp)-1]=0;
			}

			else if (GLOBAL.loopswitch2==1&&key>='0'&&key<='9')
			{
				char tempo[20];tempo[0]=0;
				if (strlen(potiontemp)<=10)
				{
					sprintf(tempo,"%d",key-48);
					strcat(potiontemp,tempo);
				}
				else
				{
					CONSOLE.pushtext(false,3,TEXT_LENGTH);
				}

				int amount=atoi(potiontemp);
				if (amount>HCVARS.MAXPLAYERHEALTH)
				{
					char tempo2[20];tempo2[0];
					char tempo[100];tempo[0]=0;
					sprintf(tempo2,"%d",HCVARS.MAXPLAYERHEALTH);


					strcpy(potiontemp,tempo2);

					strcpy(tempo,"Max Potion amount is ");
					strcat(tempo,tempo2);

					CONSOLE.pushtext(false,3,tempo);			
				}
			}	

			else if (key==13)
			{
				if (GLOBAL.loopswitch2==0)
					GLOBAL.loopswitch2=1;
				else if (GLOBAL.loopswitch2==1)
				{

					NodeObject * thisitem1=shoppotions[MAPFILES.rearmx];

					int nid=thisitem1->id;
					while (nid>=100)
						nid-=100;
					objstore * thisitem=INFOS.OBJSTOREPTR[nid];
					int ap=atoi(potiontemp);
					if (ap<=0)
					{
						CONSOLE.pushtext(false,3,TEXT_POTION_AMOUNT);
						GLOBAL.loopswitch=LS_PASS;
					}
					else if (ap>HCVARS.MAXPLAYERHEALTH)
					{
						char tempo2[20];tempo2[0];
						char tempo[100];tempo[0]=0;
						sprintf(tempo2,"%d",HCVARS.MAXPLAYERHEALTH);
						strcpy(tempo,"Max Potion amount is ");
						strcat(tempo,tempo2);

						CONSOLE.pushtext(false,3,tempo);
						GLOBAL.loopswitch=LS_PASS;
					}
					else
					{
						EXEC.buypotion(thisitem,ap);			
						GLOBAL.loopswitch2=0;
						potiontemp[0]=0;
					}
				}
			}		

			glutPostRedisplay();return;
		}

	case LS_BUYSPELLMENU:
		{
			if (key==27)
				GLOBAL.loopswitch=LS_PASS;
			else
			{
				if (MAPFILES.rearmy==0)
				{GLOBAL.loopswitch=LS_BUYSPELL;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}
				else if (MAPFILES.rearmy==1)
				{GLOBAL.loopswitch=LS_PASS;MAPFILES.rearmx=0;MAPFILES.rearmy=0;}
			}
			glutPostRedisplay();return;
		}

	case LS_HELPSCREEN:
		{
			if (key==27||key==GLUT_KEY_F1)
			{
				GLOBAL.loopswitch=LS_PASS;
				glutPostRedisplay();
			}

			return;
		}

	case LS_EXITMAP:
		{		
		if (key==13)
			{
				if (MAPFILES.rearmy==0)
				{
					MAPFILES.rearmy=0;GLOBAL.loopswitch=LS_PASS;
					EXEC.loadmapcurrenttile();
				}
				//go back
				else if (PLAYER.lastx!=0&&PLAYER.lasty!=0)
				{
					MAPFILES.rearmy=0;MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=0;
					PLAYER.posx=PLAYER.lastx;
					PLAYER.posy=PLAYER.lasty;
					GLOBAL.loopswitch=LS_PASS;
					MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;}
				else 
				{
					printf("err");
				}

			}
			else if (key==27)
			{GLOBAL.loopswitch=LS_PASS;MAPFILES.rearmy=0;
			MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=NULL;
			PLAYER.posx=PLAYER.lastx;PLAYER.posy=PLAYER.lasty;GLOBAL.loopswitch=LS_PASS;
			MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;}

			glutPostRedisplay();return;
		}

	case LS_SPELLS:
		{
			if (key==27||key=='c'||key=='C')
			{
				GLOBAL.loopswitch=LS_PASS;
			glutPostRedisplay();
			return;
			}

			else if (key==13)
			{
				int temp=0;
				temp+=MAPFILES.rearmx;
				temp+=MAPFILES.rearmy*5;
				splstore * thisspell=INFOS.SPLSTORE[temp];
				int nid=thisspell->id;
				while (nid>=100)
					nid-=100;

				if (PLAYER.hasSpellTable[nid])
				{
					SPELL.basedamage=thisspell->basedamage;
					SPELL.mp=thisspell->mp;
					SPELL.type=thisspell->id;
					strcpy(SPELL.image,thisspell->path);
					strcpy(SPELL.name,thisspell->name);
					glutPostRedisplay();return;
				}
				else
				{
					SPELL.basedamage=0;
					SPELL.mp=0;
					SPELL.type=0;
					strcpy(SPELL.image,"");
					strcpy(SPELL.name,"");
					strcpy(SPELL.image,"");
					strcpy(SPELL.name,"");

					glutPostRedisplay();return;
				}
			}
			return;
		}

	case LS_PICKUP:
		{
			if (key==13)
				EXEC.pickupfunction(PLAYER.posx,PLAYER.posy);
			else
			CONSOLE.pushtext(false,0,TEXT_ABORT);

			GLOBAL.loopswitch=LS_NORMAL;
			glutPostRedisplay();return;
		}

	case LS_LOOK:
		{
			if (key==13)
				EXEC.lookfunction(PLAYER.posx,PLAYER.posy);
			else
			CONSOLE.pushtext(false,0,TEXT_ABORT);

			GLOBAL.loopswitch=LS_NORMAL;
			glutPostRedisplay();return;
		}

	case LS_BUYING:
		{
			if (key==13&&GLOBAL.loopswitch==LS_BUYING)
			{buyitemhead(&shopitems,MAPFILES.rearmy ,MAPFILES.rearmx);}
			else if (key==13&&GLOBAL.loopswitch==LS_SELLING)
			{sellitemhead(&helditems,MAPFILES.rearmy ,MAPFILES.rearmx);}
			else if (key==27&&GLOBAL.runninggame==1)
			{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}

			return;
		}

	case LS_SELLING:
		{
			if (key==13&&GLOBAL.loopswitch==LS_BUYING)
			{buyitemhead(&shopitems,MAPFILES.rearmy ,MAPFILES.rearmx);}
			else if (key==13&&GLOBAL.loopswitch==LS_SELLING)
			{sellitemhead(&helditems,MAPFILES.rearmy ,MAPFILES.rearmx);}
			else if (key==27&&GLOBAL.runninggame==1)
			{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}

			return;
		}

	case LS_BUYSPELL:
		{
			if (key==13&&GLOBAL.loopswitch==LS_BUYSPELL)
				EXEC.buyspellhead(MAPFILES.rearmy ,MAPFILES.rearmx);

			else if (key==27&&GLOBAL.runninggame==1)
			{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}
			return;
		}

	case  LS_CASINOPOKER:
		{
			if (GLOBAL.loopswitch2==0)
			{
				if (key==8)
				{
					int a=0;
					while (poker.temps[a]!=0)
						a++;
					if (a!=0)
						poker.temps[a-1]=0;

				}
				else if (key==27)
				{
					PLAYER.gold+=poker.bet;poker.netearnings+=poker.bet;poker.bet=0;
					GLOBAL.loopswitch=LS_PASS;CONSOLE.pushtext(false,2,TEXT_TYPLAY);
				}


				else if (key>='0'&&key<='9'&&strlen(poker.temps)<=10)
				{
					int a=0;
					while (poker.temps[a]!=0)
						a++;

					if (a==0)
					{poker.temps[0]=key;poker.temps[1]=0;}
					else
					{poker.temps[a]=key;poker.temps[a+1]=0;}

				}
				else if (key==13)
				{
					if (strlen(poker.temps)!=0)
					{
						int temp=0;
						temp=atoi(poker.temps);
						strcpy(poker.temps,"");
						if (temp<=PLAYER.gold&&temp<=poker.maxbet)
						{
							GLOBAL.loopswitch2=1;poker.bet=temp;PLAYER.gold-=temp;poker.netearnings-=temp;

							EXEC.loadSound(SND.goldsound);

						}
						else if (temp>poker.maxbet)
							CONSOLE.pushtext(false,3,TEXT_BET);
						else if (temp>PLAYER.gold)
							CONSOLE.pushtext(false,3,TEXT_PLAYER_MONEY);
					}
				}
			}

			else if (GLOBAL.loopswitch2==2)
			{
				if (key==13)
				{
					if (MAPFILES.rearmy==0)
						poker.cards[MAPFILES.rearmx]=!poker.cards[MAPFILES.rearmx];
					else
					{poker.swapcards(poker.cards);poker.countandsort();poker.changebet();GLOBAL.loopswitch2=3;MAPFILES.rearmy=1;MAPFILES.rearmx=0;}
				}

			}
			else if (GLOBAL.loopswitch2==3)
			{
				if (key==13)
				{
					if (MAPFILES.rearmx==1&&MAPFILES.rearmy==1)
					{if (poker.bet>0)
					{PLAYER.gold+=poker.bet;poker.netearnings+=poker.bet;poker.bet=0;}
					else

					{GLOBAL.loopswitch=LS_PASS;CONSOLE.pushtext(false,2,TEXT_TYPLAY);}

					}

					else if (MAPFILES.rearmx==0&&poker.bet==0)
					{GLOBAL.loopswitch2=0;MAPFILES.rearmy=0;MAPFILES.rearmx=0;
					poker.clearcards();
					poker.hand.clear();
					poker.numberofgames++;
					}
					else if (MAPFILES.rearmx==0&&poker.bet>0)
					{
						GLOBAL.loopswitch2=4;MAPFILES.rearmx=0;MAPFILES.rearmy=0;
						poker.clearcards();
						poker.hand.clear();
						int random =rand()%13;
						int randomtype =rand()%4;
						poker.insertcard(random,randomtype,0);

					}
					{
					}
				}
			}
			else if (GLOBAL.loopswitch2==4)
			{
				if (key==13)
				{
					int random =rand()%13;
					int randomtype =rand()%4;
					int temp=poker.hand.hand[0][0];
					poker.insertcard(random,randomtype,0);

					if ((MAPFILES.rearmx==0&&temp<poker.hand.hand[0][0])||(MAPFILES.rearmx==1&&temp==poker.hand.hand[0][0])||(MAPFILES.rearmx==2&&temp>poker.hand.hand[0][0]))
						poker.bet*=2;
					else
						poker.bet=0;
					GLOBAL.loopswitch2=5;
					MAPFILES.rearmx=0;
					MAPFILES.rearmy=0;
				}
			}
			else if (GLOBAL.loopswitch2==5)
			{
				if (key==13)
				{
					if (MAPFILES.rearmx==0&&poker.bet>0)
					{
						GLOBAL.loopswitch2=4;MAPFILES.rearmx=0;MAPFILES.rearmy=0;
						poker.clearcards();
						poker.hand.clear();
						int random =rand()%13;
						int randomtype =rand()%4;
						poker.insertcard(random,randomtype,0);
					}
					else if (MAPFILES.rearmx==0&&poker.bet<=0)
					{
						poker.bet=0;
						GLOBAL.loopswitch2=0;MAPFILES.rearmx=0;MAPFILES.rearmy=0;
						poker.numberofgames++;
						poker.clearcards();
						poker.hand.clear();			
					}
					else if (MAPFILES.rearmx==1&&poker.bet>0)
					{
						PLAYER.gold+=poker.bet;poker.netearnings+=poker.bet;poker.bet=-1;
					}
					else
					{
						GLOBAL.loopswitch=LS_PASS;
					}

				}

			}
			//printf("\nnorm-cas");
			glutPostRedisplay();
			return;
		}

	case  LS_CASINOCHOICE:
		{
			if (key==27)
			{
				GLOBAL.loopswitch=LS_PASS;
			}		
			else if (key==13)
			{
				if (MAPFILES.rearmy==1)
				{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}
				else if (MAPFILES.rearmy==0)
				{
					poker.init();
					poker.clearcards();
					poker.temps[0]=0;

					GLOBAL.loopswitch2=0;
					GLOBAL.loopswitch=LS_CASINOPOKER;

				}
			}
			glutPostRedisplay();
			return;
		}

	case LS_OPENING:
		{
			if (key==13)
			{//hard code start screen size
				if (MAPFILES.rearmx==0)
				{
					ANIMATION.init();
					MAPFILES.TERRAINLOSinit(15,11);
					GLOBAL.runninggame=1;
					EXEC.initgame();
					GLOBAL.loopswitch=LS_PASS;CONSOLE.pushtext(false,2,TEXT_WELCOME);}
				else if (MAPFILES.rearmx==1&&GLOBAL.runninggame==1)
				{
					ANIMATION.init();
					ANIMATION.popview(&x,&y);
					MAPFILES.TERRAINLOSinit(x,y);

					GLOBAL.loopswitch=LS_PASS;GLOBAL.runninggame=1;}
				else if (MAPFILES.rearmx==2&&GLOBAL.runninggame==1)
				{ANIMATION.init();EXEC.savefunction();GLOBAL.loopswitch=LS_PASS;CONSOLE.pushtext(false,3,TEXT_SAVEGAME);}
				else if (MAPFILES.rearmx==3)
				{ANIMATION.init();EXEC.loadfunction(PLAYER.name);CONSOLE.pushtext(false,3,TEXT_LOADGAME);}
				else if (MAPFILES.rearmx==4)
				{GLOBAL.loopswitch=LS_OPTIONS;MAPFILES.rearmy=0;}
				else if (MAPFILES.rearmx==5)
				{EXEC.quit("");}
				glutPostRedisplay();
				return;
			}
			
			return;
		}

	case LS_OPTIONS:
		{
			if (key==13)
			{
				if (MAPFILES.rearmy==0)
				{
					if (GLOBAL.soundenabled==true)
						GLOBAL.soundenabled=false;
					else 
						GLOBAL.soundenabled=true;
				}
				else if (MAPFILES.rearmy==1)
				{
					if (GLOBAL.consoleenabled==true)
						GLOBAL.consoleenabled=false;
					else 
						GLOBAL.consoleenabled=true;
				}
				else if (MAPFILES.rearmy==2)
				{
					if (GLOBAL.isfullscreen==true)
						GLOBAL.isfullscreen=false;
					else 
						GLOBAL.isfullscreen=true;
					GLOBAL.firsttime=false;
				initmode();
				}
				else if (MAPFILES.rearmy==6)
				{
					ANIMATION.openinganimationsetup();
					GLOBAL.loopswitch=LS_OPENING;
					//MAPFILES.TERRAINLOSinit(21,8);
//					ANIMATION.timer=1;
				}
				GLOBAL.saveconfig();
				glutPostRedisplay();
			}
return;
		}

	case LS_BUYFOOD:
		{
			if (key==13)
			{
				if (PLAYER.food>=PLAYER.maxfood)
				{CONSOLE.pushtext(false,3,TEXT_FOOD);glutPostRedisplay();return;}
				if (MAPFILES.rearmy==0)
				{if (PLAYER.gold>=INFOS.foodtable[0][0]){PLAYER.gold-=INFOS.foodtable[0][0];PLAYER.food+=INFOS.foodtable[0][1];}else CONSOLE.pushtext(false,3,TEXT_ITEM_AFFORD);}
				else if (MAPFILES.rearmy==1)
				{if (PLAYER.gold>=INFOS.foodtable[1][0]){PLAYER.gold-=INFOS.foodtable[1][0];PLAYER.food+=INFOS.foodtable[1][1];}else CONSOLE.pushtext(false,3,TEXT_ITEM_AFFORD);}
				else if (MAPFILES.rearmy==2)
				{if (PLAYER.gold>=INFOS.foodtable[2][0]){PLAYER.gold-=INFOS.foodtable[2][0];PLAYER.food+=INFOS.foodtable[2][1];}else CONSOLE.pushtext(false,3,TEXT_ITEM_AFFORD);}
				else if (MAPFILES.rearmy==3)
				{if (PLAYER.gold>=INFOS.foodtable[3][0]){PLAYER.gold-=INFOS.foodtable[3][0];PLAYER.food+=INFOS.foodtable[3][1];}else CONSOLE.pushtext(false,3,TEXT_ITEM_AFFORD);}
				else if (MAPFILES.rearmy==4)
				{if (PLAYER.gold>=INFOS.foodtable[4][0]){PLAYER.gold-=INFOS.foodtable[4][0];PLAYER.food+=INFOS.foodtable[4][1];}else CONSOLE.pushtext(false,3,TEXT_ITEM_AFFORD);}
				else if (MAPFILES.rearmy==5)
				{CONSOLE.pushtext(false,0,TEXT_TY);GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}
				if (PLAYER.food>PLAYER.maxfood)
				{
					PLAYER.food=PLAYER.maxfood;
					CONSOLE.pushtext(false,3,TEXT_FOOD);
				}
				glutPostRedisplay();
				return;
			}
			else if (key==27)
			{GLOBAL.loopswitch=LS_PASS;
			glutPostRedisplay();
			return;
			}
			return;
		}

	case LS_INGAMEMENU:
		{
			if (((key>=33&&key<=95)||(key>=97&&key<=125))&&(strlen(CONSOLE.currentconsole)<=CONSOLE.maxstring-1))
			{CONSOLE.pushconsolecurrent(key,CONSOLE.currentconsolecarat,'w');CONSOLE.currentconsolecarat++;glutPostRedisplay();return;} 
			else if ((key==32)&&(strlen(CONSOLE.currentconsole)<=CONSOLE.maxstring-1))
			{CONSOLE.pushconsolecurrent(' ',CONSOLE.currentconsolecarat,'w');CONSOLE.currentconsolecarat++;glutPostRedisplay();return;} 
			else if ((key==8)&&CONSOLE.currentconsolecarat>=1)
			{CONSOLE.pushconsolecurrent('s',CONSOLE.currentconsolecarat,'d');CONSOLE.currentconsolecarat--;glutPostRedisplay();return;} 
			else if ((key==127)&&CONSOLE.currentconsolecarat<=CONSOLE.maxstring-1)
			{CONSOLE.pushconsolecurrent('s',CONSOLE.currentconsolecarat+1,'d');glutPostRedisplay();return;} 
			else if (key==27)
			{
				GLOBAL.loopswitch=LS_PASS;
				glutPostRedisplay();
				return;
			} 
			else if (key==13)
			{
				CONSOLE.pushtext(true,0,CONSOLE.currentconsole);
				EXEC.executecommand();
				for (int a=0;a<CONSOLE.maxstring-1;a++)
					CONSOLE.currentconsole[a]='\0';
				CONSOLE.currentconsolecarat=0;
				glutPostRedisplay();
				return;
			}

			else if ((key=='`'||key=='~')&&GLOBAL.consoleenabled==true)
			{
				if (GLOBAL.loopswitch==LS_INGAMEMENU)
				{GLOBAL.loopswitch=LS_PASS;
				for (int a=0;a<CONSOLE.maxstring-1;a++)CONSOLE.currentconsole[a]='\0';
				CONSOLE.currentconsolecarat=0;
				}
				else
				{GLOBAL.loopswitch=LS_INGAMEMENU;CONSOLE.currentconsolecarat=0;}

				glutPostRedisplay();
				return;
			}

			glutPostRedisplay();
			return;
		}

	case LS_DROP:
		{
			if (key==27)
			{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}
			else if (key==13)
				dropitemhead(&helditems,MAPFILES.rearmy ,MAPFILES.rearmx);
			else
			{
				if ((key=='d'||key=='D'))
				{GLOBAL.loopswitch=LS_PASS;MAPFILES.rearmx=0;MAPFILES.rearmy=0;glutPostRedisplay();return;}
				else if (key=='u'||key=='U')
				{
					GLOBAL.loopswitch=LS_USEMENU;

					if (MAPFILES.rearmx==-1||MAPFILES.rearmy==-1)
					{
						MAPFILES.rearmx=0;MAPFILES.rearmy=0;
					}
				}

				else if (key=='s'||key=='S')
				{
					GLOBAL.loopswitch=LS_STATS;

					if (MAPFILES.rearmx==-1||MAPFILES.rearmy==-1)
					{
						MAPFILES.rearmx=0;MAPFILES.rearmy=0;
					}
				}
			}
			glutPostRedisplay();return;
		}

	case LS_STATS:
		{
			if (key==27)
			{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}

			if (key==13&&PLAYERSTATS.skillpoints>=1)
			{
				if (MAPFILES.rearmy==0)
				{PLAYERSTATS.strength++;PLAYERSTATS.skillpoints--;}
				else if (MAPFILES.rearmy==1)
				{PLAYERSTATS.agility++;PLAYERSTATS.skillpoints--;}
				else if (MAPFILES.rearmy==2)
				{PLAYERSTATS.dexterity++;PLAYERSTATS.skillpoints--;}
				else if (MAPFILES.rearmy==3)
				{
					PLAYERSTATS.intelligence++;
					PLAYER.maxmagic=PLAYERSTATS.intelligence*10;
					PLAYERSTATS.skillpoints--;
				}
				else if (MAPFILES.rearmy==4)
				{
					PLAYERSTATS.constitution++;				
					PLAYER.maxhealth=PLAYERSTATS.constitution*10;
					PLAYER.maxair=ceil((float)PLAYERSTATS.constitution/10);
					PLAYER.maxstamina=PLAYERSTATS.constitution;

					if (PLAYER.maxhealth>HCVARS.MAXPLAYERHEALTH)
						PLAYER.maxhealth=HCVARS.MAXPLAYERHEALTH;
					if (PLAYER.maxmagic>HCVARS.MAXPLAYERMAGIC)
						PLAYER.maxmagic=HCVARS.MAXPLAYERMAGIC;
					PLAYERSTATS.skillpoints--;
				}

				glutPostRedisplay();
				return;
			}
			else
			{
				if (key=='s'||key=='S')
				{
					MAPFILES.rearmy=1;
					GLOBAL.loopswitch=LS_PASS;
					MAPFILES.rearmx=0;MAPFILES.rearmy=0;
				}
				else if (key=='d'||key=='D')
				{
					GLOBAL.loopswitch=LS_DROP;

					if (MAPFILES.rearmx==-1||MAPFILES.rearmy==-1)
					{
						MAPFILES.rearmx=0;MAPFILES.rearmy=0;
					}
				}

				else if (key=='u'||key=='U')
				{
					GLOBAL.loopswitch=LS_USEMENU;

					if (MAPFILES.rearmx==-1||MAPFILES.rearmy==-1)
					{
						MAPFILES.rearmx=0;MAPFILES.rearmy=0;
					}

				}

			}
			glutPostRedisplay();return;
		}

	case LS_USEMENU:
		{
			if (key==27)
			{GLOBAL.loopswitch=LS_PASS;glutPostRedisplay();return;}

			if (key==13)
			{
				//handle armour interactions here
				if (MAPFILES.rearmx==-1)
				{
					if (helditems.getCount()>=25)
					{
						CONSOLE.pushtext(false,3,TEXT_INV_FULL);
						GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;
					}

					if (MAPFILES.rearmy==0)
						EXEC.equiphandle(&EQUIPMENT.HELM);
					else if (MAPFILES.rearmy==1)
						EXEC.equiphandle(&EQUIPMENT.CHEST);
					else if (MAPFILES.rearmy==2)
						EXEC.equiphandle(&EQUIPMENT.LEGS);
					else if (MAPFILES.rearmy==3)
						EXEC.equiphandle(&EQUIPMENT.SHOES);
				}
				//handle weapon interactions here
				else if (MAPFILES.rearmy==-1)
				{
					if (helditems.getCount()>=25)
					{
						CONSOLE.pushtext(false,3,TEXT_INV_FULL);
						GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;
					}

					if (MAPFILES.rearmx==0&&EQUIPMENT.RARM.id!=200)
						EXEC.weaponhandle(&EQUIPMENT.RARM,false);
					else if (EQUIPMENT.LARM.id!=200)
						EXEC.weaponhandle(&EQUIPMENT.LARM,true);

				}
				//handle item interactions here
				else
				{
					int temp=0;
					temp+=MAPFILES.rearmx;
					temp+=MAPFILES.rearmy*5;

					NodeObject * newptr=helditems[temp];
					if (newptr!=NULL)
						EXEC.inventoryhandle(newptr);

					glutPostRedisplay();
					return;
				}
			}
			else
			{
			if (key=='u'||key=='U')
			{
				GLOBAL.loopswitch=LS_PASS;
				MAPFILES.rearmx=0;MAPFILES.rearmy=0;
			}

			else if (key=='d'||key=='D')
			{
				GLOBAL.loopswitch=LS_DROP;

				if (MAPFILES.rearmx==-1||MAPFILES.rearmy==-1)
				{
					MAPFILES.rearmx=0;MAPFILES.rearmy=0;
				}

			}
			else if (key=='s'||key=='S')
			{
				GLOBAL.loopswitch=LS_STATS;

				if (MAPFILES.rearmx==-1||MAPFILES.rearmy==-1)
				{
					MAPFILES.rearmx=0;MAPFILES.rearmy=0;
				}

			}

			}
			glutPostRedisplay();return;
		}

	case LS_TALKING:
		{
			GLOBAL.loopswitch=LS_PASS;
			MAPFILES.rearmx=0;
			MAPFILES.rearmy=0;

			EXEC.loadSound(SND.minimize);
			glutPostRedisplay();
			return;
		}

	case LS_ATTACKLS:
		{
			MAPFILES.rearmx=0;MAPFILES.rearmy=0;
			GLOBAL.loopswitch=LS_NORMAL;
			CONSOLE.pushtext(false,0,TEXT_ABORT);
			glutPostRedisplay();
			return;
		}

	case LS_ATTACKRS:
		{
			GLOBAL.loopswitch=LS_NORMAL;MAPFILES.rearmx=0;MAPFILES.rearmy=0;
			CONSOLE.pushtext(false,0,TEXT_ABORT);
			glutPostRedisplay();
			return;
		}

	case LS_OPENDOOR:
		{
			GLOBAL.loopswitch=LS_NORMAL;
			CONSOLE.pushtext(false,0,TEXT_ABORT);
			glutPostRedisplay();
			return;
		}

	case LS_CAST:
		{
			GLOBAL.loopswitch=LS_NORMAL;
			CONSOLE.pushtext(false,0,TEXT_ABORT);
			
			glutPostRedisplay();
			return;
		}
		
	default:
		{
			if ((key=='`'||key=='~')&&GLOBAL.consoleenabled==true&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
			{
				GLOBAL.loopswitch=LS_INGAMEMENU;
				glutPostRedisplay();
				return;
			}

			else if (key==27)
			{
				if (GLOBAL.runninggame==1)
					MAPFILES.rearmx=1;
				else
					MAPFILES.rearmx=0;
				
				ANIMATION.pushview(GLOBAL.loopswitch);
				ANIMATION.openinganimationsetup();
				GLOBAL.loopswitch=LS_OPENING;
				//MAPFILES.TERRAINLOSinit(21,8);
				//	ANIMATION.timer=1;
				ANIMATION.DIRECTION=rand()%10;
				if (ANIMATION.DIRECTION==0||ANIMATION.DIRECTION==5)
					ANIMATION.DIRECTION++;
				ANIMATION.POSX=MAPFILES.currentmap->startX;
				ANIMATION.POSY=MAPFILES.currentmap->startY;
				glutPostRedisplay();
				return;
			}

			if ((PLAYER.lockmove==true||GLOBAL.fadeamount>0)&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
				return;

			else if (key=='='&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
			{
				MAPFILES.TERRAINLOSinit(ANIMATION.getVIEWWIDTH()-2,ANIMATION.getVIEWHEIGHT()-2);
				GLOBAL.loopswitch=LS_PASS;
			}

			else if (key=='-'&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
			{
				MAPFILES.TERRAINLOSinit(ANIMATION.getVIEWWIDTH()+2,ANIMATION.getVIEWHEIGHT()+2);
				GLOBAL.loopswitch=LS_PASS;
			}

			else if (key=='0'&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
			{
				MAPFILES.TERRAINLOSinit(15,11);
				GLOBAL.loopswitch=LS_PASS;
			}

			else if (key=='9'&&(GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS))
			{
				GLOBAL.blackscreen=!GLOBAL.blackscreen;
				printf("\nWS=%d NE=%d TT=%d",GLOBAL.worldstatus,GLOBAL.nighttend,ANIMATION.LIGHTLEVELTIME);
			}

			else if (key==9)
				ANIMATION.minimap=!ANIMATION.minimap;

			else if (key=='1')
			{
				glutPostRedisplay();

				//PLAYER.viewdist--;
				//glutPostRedisplay();
			}
			else if (key=='2')
			{printf("\nRT\n");
			for (int a=0;a<ANIMATION.getVIEWHEIGHT();a++)
			{

				for (int b=0;b<ANIMATION.getVIEWWIDTH();b++)
				{
					printf("%d",MAPFILES.RAYTRACE[a][b]);
				}
				printf("\n");
			}


			//PLAYER.viewdist++;
			printf("\nStop! Grammar Time!");
			}

			else if (key=='t'||key=='T')
			{
				MAPFILES.rearmx=0;MAPFILES.rearmy=0;
				CONSOLE.pushtext(false,0,TEXT_DIRECTION_TALK);
				GLOBAL.loopswitch=LS_TALKOP;
			}
			else if (key=='e'||key=='E')
			{
				EXEC.loadmapcurrenttile();
				MAPFILES.lastx=0;
				MAPFILES.lasty=0;
				GLOBAL.loopswitch=LS_PASS;
			}

			else if (key=='f'||key=='F')
			{
				int nid=SPELL.type;
				while (nid>=100)
					nid-=100;

				if (SPELL.type<400||SPELL.type>500||INFOS.SPLSTOREPTR[nid]==NULL||PLAYER.hasSpellTable[nid]==false)
				{CONSOLE.pushtext(false,0,TEXT_SPELL_NOSPELL);GLOBAL.loopswitch=LS_PASS;}

				if (PLAYER.magic<SPELL.mp)
				{CONSOLE.pushtext(false,3,TEXT_PLAYER_MP);GLOBAL.loopswitch=LS_PASS;}
				else
				{
					GLOBAL.loopswitch=LS_PASS;
					if (SPELL.type>=450&&SPELL.type<500&&SPELL.type!=453&&SPELL.type!=454)
					{EXEC.caststaticspell(SPELL.type,SPELL.mp,SPELL.basedamage);}
					else if (SPELL.type==420)
					{EXEC.loadspell(SPELL.type,9,PLAYER.posy,PLAYER.posx,1);}
					else if (((SPELL.type>=400&&SPELL.type<=450)||(SPELL.type==453||SPELL.type==454))&&PLAYER.magic>=SPELL.mp)
					{CONSOLE.pushtext(false,0,TEXT_DIRECTION_SPELL);GLOBAL.loopswitch=LS_CAST;}
				}

				glutPostRedisplay();return;
			}
			else if (key=='s'||key=='S')
			{MAPFILES.rearmy=0;MAPFILES.rearmx=0;GLOBAL.loopswitch=LS_STATS;}
			else if (key=='u'||key=='U')
			{MAPFILES.rearmy=0;MAPFILES.rearmx=0;GLOBAL.loopswitch=LS_USEMENU;}
			else if (key=='d'||key=='D')
			{MAPFILES.rearmy=0;MAPFILES.rearmx=0;GLOBAL.loopswitch=LS_DROP;}
			else if (key=='l'||key=='L')
			{
				CONSOLE.pushtext(false,0,TEXT_DIRECTION_LOOK);
				GLOBAL.loopswitch=LS_LOOK;
			}
			else if (key=='a'||key=='A')
			{
				if (EQUIPMENT.LARM.type==T_FISTS&&EQUIPMENT.RARM.type==T_FISTS)
				{
					CONSOLE.pushtext(false,0,TEXT_DIRECTION_ATTACKFIST);
					GLOBAL.loopswitch=LS_ATTACKLS;
				}

				else if (EQUIPMENT.LARM.type==T_FISTS&&EQUIPMENT.RARM.type!=T_FISTS)
				{
					char tempstr[100];
					strcpy(tempstr,"Press direction to attack with ");
					strcat(tempstr,INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->name);
					CONSOLE.pushtext(false,0,tempstr);GLOBAL.loopswitch=LS_ATTACKRS;
				}

				else
				{
					char tempstr[100];
					strcpy(tempstr,"Press direction to attack with ");
					strcat(tempstr,INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->name);

					CONSOLE.pushtext(false,0,tempstr);GLOBAL.loopswitch=LS_ATTACKLS;
				}

			}
			//{CONSOLE.pushtext(false,0,"Press direction to attack with left weapon");GLOBAL.loopswitch=LS_ATTACKRS;}
			else if (key=='g'||key=='G')
			{CONSOLE.pushtext(false,0,TEXT_DIRECTION_GET);GLOBAL.loopswitch=LS_PICKUP;}
			else if (key=='c'||key=='C')
			{MAPFILES.rearmy=0;MAPFILES.rearmx=0;
			GLOBAL.loopswitch=LS_SPELLS;
			glutPostRedisplay();
			return;
			}
			else if (key=='o'||key=='O')
			{
				CONSOLE.pushtext(false,0,TEXT_DIRECTION_OPEN);
				GLOBAL.loopswitch=LS_OPENDOOR;
			}

			else if (key=='h'||key=='H')
			{
				CONSOLE.pushtext(false,0,TEXT_F1);
				GLOBAL.loopswitch=LS_PASS;
			}

			else if (key=='v'||key=='V')
			{
				if (PLAYER.dash==0){PLAYER.dash=1;}else{PLAYER.dash=0;}
				GLOBAL.loopswitch=LS_PASS;
			}
			//space
			else if ((key==32)&&SPELL.active==0&&SPELL2.active==0)
			{
				GLOBAL.loopswitch=LS_NORMAL; 
				if (MAPFILES.MAPFILE[PLAYER.posy][PLAYER.posx]==TT_WATER)
					CONSOLE.pushtext(false,0,TEXT_TREAD);
				else 
					CONSOLE.pushtext(false,0,TEXT_WAIT);				

				if (MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]==NULL)
				{
					MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
				}
			}
			else
				GLOBAL.loopswitch=LS_PASS;

			glutPostRedisplay();
		}
	}
	}
	
#endif