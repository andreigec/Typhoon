//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _DISPLAYFUNCT_CPP
#define _DISPLAYFUNCT_CPP
#include "disps2.cpp"
void display(void)
{
	glLoadIdentity( );
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ANIMATION.timestep();
	EXEC.trimmemory();
	//ensure that player is on mapfile, shouldnt be needed to be used in future
	//MAPFILES.MAPFILEENEMY[PLAYER.posy][PLAYER.posx]=(NodeEnemy*)0x01;
	//check player pos
	PLAYER.levelup();

	if (GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS)
	{
		EXEC.globalcount();
		EXEC.castrangedspell();
		if (SPELL.active==0&&SPELL2.active==0)
			PLAYER.checkenv();
	
		MAPFILES.runMapScript();
	}
	
	
	switch (GLOBAL.loopswitch)
	{

	case LS_CASINOPOKER:
		{
			drawGUI(false);
			casinopoker();
			break;
		}
	case LS_HELPSCREEN:
		{
			helpscreen();
			break;		
		}

	case LS_DEATHSCREEN:
		{
			deathscreen();
			break;
		}


	case LS_OPENING:
		{
			//openinganimationstep()
			glEnable(GL_BLEND);
			glClearColor(1.0, 1.0, 1.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			EXEC.drawopeningscreen();
			EXEC.printterrain(true);
			EXEC.drawopeningtext();
			break;
		}

	case LS_DROP:
		{
			dropstatsuse();
			break;
		}

	case LS_STATS:
		{
			dropstatsuse();
			break;
		}

	case LS_USEMENU:
		{
			dropstatsuse();
			break;
		}

	case LS_OPTIONS:
		{
			optionsmenu();
			break;
		}

	case LS_POTIONSHOP:
		{
			drawGUI(false);
			potionshop();
			break;

		}

	case LS_BUYING:
		{
			drawGUI(false);
			glLoadIdentity();

			buysellbuyspell();
			break;
		}

	case LS_SELLING:
		{
			drawGUI(false);
			glLoadIdentity();

			buysellbuyspell();
			break;
		}

	case LS_BUYSPELL:
		{
			drawGUI(false);
			glLoadIdentity();

			buysellbuyspell();
			break;
		}

	case LS_SPELLS:
		{
			drawGUI(false);
			glLoadIdentity();
			spells();
			break;
		}
	case LS_EXITMAP:
		{
			drawGUI(true);
			glLoadIdentity();

			exitmap();
			break;
		}

	case LS_BUYORSELL:
		{
			drawGUI(true);
			glLoadIdentity();
			buyspellspellpotionmenu();
			break;
		}

	case LS_BUYSPELLMENU:
		{
			drawGUI(true);
			glLoadIdentity();
			buyspellspellpotionmenu();
			break;
		}

	case LS_POTIONMENU:
		{
			drawGUI(true);
			glLoadIdentity();
			buyspellspellpotionmenu();
			break;
		}
	case LS_CASINOCHOICE:
		{
			drawGUI(true);
			glLoadIdentity();
			casinochoice();
			break;
		}

	case LS_INGAMEMENU:
		{
			drawGUI(true);
			glLoadIdentity();
			ingamemenu();
			break;
		}

	case LS_BUYFOOD:
		{
			drawGUI(false);
			glLoadIdentity();
			buyfood();
			break;
		}

	case LS_TALKING:
		{
			drawGUI(false);
			glLoadIdentity();
			talking();
			break;
		}

	default:
		{
			drawGUI(true);

			break;
		}
	}
	if (SPELL.active==1||SPELL2.active==1)
	{Sleep(80);}

	glutSwapBuffers();	
}

#endif