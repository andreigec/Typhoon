//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 

//version numbering in HC

//if possible, overload standard crt functs with secure crt libraries
//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1 
//no deprecated warnings
#define _CRT_NONSTDC_NO_DEPRECATE 1
#define _CRT_SECURE_NO_DEPRECATE 1
//#define _CRT_NONSTDC_NO_DEPRECATE 1


///inbuilt memory leak checker. no stack view, uncomment lines in main as well

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//better,slower method
//#include <vld.h>

// conversion warning ignore
#pragma warning( disable: 4244 )
// truncation warning ignore
#pragma warning( disable: 4305 )
// ignore while(1) loops warning
#pragma warning( disable: 4127 )
// ignore void* to int  warning
#pragma warning( disable: 4311 )

#include "Lib\openglut\openglut.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Lib\fmod\fmod.hpp"
#pragma comment( lib, "fmodex_vc.lib" ) // fmod library

#include <time.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <windows.h>

//Base abstract tree class
#include "Library\TreeNodeAbstract.h"
#include "Library\TreeAbstract.h"
#include "Library\TreeNodeAbstract.cpp"
#include "Library\TreeAbstract.cpp"

//AVL tree data
#include "Library\avltreenode.h"
#include "Library\avltree.h"
#include "Library\avltreenode.cpp"
#include "Library\avltree.cpp"

//LL
#include "Library\LinkedListNode.h"
#include "Library\LinkedList.h"
#include "Library\LinkedListNode.cpp"
#include "Library\LinkedList.cpp"


using namespace std;

//for use with scripting
enum OPERATORS
{
	OP_LESSTHAN = 0, OP_LESSEQUALTHAN = 1, OP_GREATERTHAN = 2, OP_GREATEREQUALSTHAN = 3, OP_EQUALS = 4, OP_NOTEQUALS = 5,
};

//for use with debugging tiles in the game
enum DEBUGTILETYPE
{
	DTT_NONE = 0, DTT_PATHFIND = 1, DTT_RAYTRACE = 2
};

//main finite state automaton value for game
enum LOOPSWITCH
{
	LS_LOOK = 1, LS_ATTACKRS = 2, LS_PICKUP = 3, LS_CAST = 4, LS_TALKOP = 5, LS_OPENDOOR = 6, LS_ATTACKLS = 7, \
	LS_DROP = 10, LS_STATS = 12, LS_SPELLS = 13, LS_USEMENU = 15, LS_POTIONMENU = 16, LS_POTIONSHOP = 17, \
	LS_INGAMEMENU = 20, LS_BUYING = 21, LS_SELLING = 22, LS_HELPSCREEN = 23, LS_BUYSPELL = 25, LS_TALKING = 27, \
	LS_BUYFOOD = 28, LS_BUYORSELL = 50, LS_BUYSPELLMENU = 51, LS_CASINOPOKER = 53, LS_CASINOCHOICE = 54, LS_DEATHSCREEN = 55, \
	LS_EXITMAP = 95, LS_OPTIONS = 96, LS_NORMAL = 97, LS_PASS = 98, LS_OPENING = 99
};

//what faction is the npc?
enum NPCTYPE
{
	NT_NEUTRAL = 0, NT_HOSTILE = 1, NT_FRIENDLY = 2\
};

//setting this changes the type of terrain in a tile 
enum TERRAINTYPE
{
	//<50 = passable
	TT_GRASS = 0, TT_DESERT = 1, TT_MUD = 2, TT_LAVA = 3, TT_TOWN = 5, TT_ODOOR = 6, TT_WATER = 9, \
	TT_MARSH = 41, TT_BRIDGENS = 42, TT_BRIDGEWE = 43, TT_LADDERD = 44, TT_LADDERU = 45, \
	TT_TOWER = 47, TT_DUNGEONTILE = 48, \

	//>=50 <100 = non passable
	TT_FIREPLACE = 50, TT_ROCK = 51, TREE = 52, TT_DTREE = 53, TT_MOUNTAIN = 54, TT_BWALL = 55, TT_SWALL = 56, TT_DOOR = 57, \
	TT_TABLE = 58, TT_BLACK = 98, \

	//>=100 = coasts, passable
	TT_COAST11 = 100, TT_COAST12 = 101, TT_COAST13 = 102, TT_COAST14 = 103, TT_COAST21 = 104, TT_COAST22 = 105, TT_COAST23 = 106, TT_COAST24 = 107, TT_COAST25 = 108, TT_COAST26 = 109, \
	TT_COAST31 = 110, TT_COAST32 = 111, TT_COAST33 = 112, TT_COAST34 = 113, TT_COAST41 = 114, \
	TT_COASTEDGE11 = 115, TT_COASTEDGE12 = 116, TT_COASTEDGE13 = 117, TT_COASTEDGE14 = 118, TT_COASTEDGE21 = 119, TT_COASTEDGE22 = 120, TT_COASTEDGE23 = 121, \
	TT_COASTEDGE24 = 122, TT_COASTEDGE25 = 123, TT_COASTEDGE26 = 124, TT_COASTEDGE31 = 125, TT_COASTEDGE32 = 126, TT_COASTEDGE33 = 127, TT_COASTEDGE34 = 128, \
	TT_COASTEDGE41 = 129, \
};

//use this for general equipment types
enum TYPE {
	\
	T_INVALID = 0, T_OTHER = 1, T_GOLD = 2, T_FOOD = 3, T_HEALTHPOTION = 4, T_MAGICPOTION = 5, T_STAMINAPOTION = 6, T_FULLPOTION = 7, \
	T_WEAPON = 100, T_FISTS = 101, T_TORCHWEP = 102, \
	T_HELMET = 200, T_CHEST = 201, T_LEGS = 202, T_SHOES = 203, \
	T_NPC = 300, T_TORCH = 301, T_SIGN = 302, T_RNPC = 303, \
	T_SPELL = 400, \
	T_MAP = 500, T_DUNGEON = 501,
};

inline bool ismap(int type)
{
	if (type >= 500 && type < 600)
		return true;
	return false;
}

inline bool isspell(int type)
{
	if (type >= 400 && type < 500)
		return true;
	return false;
}

inline bool isnpc(int type)
{
	if (type >= 300 && type < 400)
		return true;
	return false;
}

inline bool isarmour(int type)
{
	if (type >= 200 && type < 300)
		return true;
	return false;
}

inline bool isweapon(int type)
{
	if (type >= 100 && type<200)
		return true;
	return false;
}

inline bool isobject(int type)
{
	if (type>0 && type < 100)
		return true;
	return false;
}


//2  3
//  
//1  4
inline void drawtile(float ONEX, float ONEY, float TWOX, float TWOY, float THREEX, float THREEY, float FOURX, float FOURY)
{
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(ONEX, ONEY);
	glTexCoord2f(1, 0);
	glVertex2f(FOURX, FOURY);
	glTexCoord2f(1, 1);
	glVertex2f(THREEX, THREEY);
	glTexCoord2f(0, 1);
	glVertex2f(TWOX, TWOY);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void myfree(char ** pointer)
{
	if ((*pointer) != NULL)
		free(*pointer);
	*pointer = NULL;
}

void mystrdup(char ** pointer, const char *dup)
{
	if ((*pointer) != NULL)
		myfree(pointer);
	*pointer = strdup(dup);
}

//xml file loading
#include "Classes\xml.h"

//localisation
#include "Classes\localisation.cpp"
//stores and handles console + ingame text log
#include "Classes\consolestuffs.h"

//classes for serialized information from files
#include "Classes\npcstore.h"
#include "Classes\objstore.h"
#include "Classes\armstore.h"
#include "Classes\wepstore.h"
#include "Classes\splstore.h"
#include "Classes\mapstore.h"
#include "Classes\exitpoint.h"

//stores and handles music and SFX
#include "Classes\SN.h"

//class to hold each tiles path values 
#include "Classes\path.h"

//controls path classes
#include "Classes\pathhead.h"

//holds hard coded variables that the game relies on, may load from file
#include "Classes\HC.h"

//holds maps for entering and leaving maps
#include "Classes\mapstax.h"

//controls mapstax class
#include "Classes\mapstackhead.h"

//TGA class
#include "Classes\TextureImage.h"

//Sound class
#include "Classes\SoundFile.h"

//handles animation and light levels for map
//look at, and compact ->mp class
#include "Classes\anim.h"

//holds game wide variables
#include "Classes\GLO.h"

//holds player stats
//look at, and compact -> play class
#include "Classes\PLAY2.h"

//holds player details sans stats
#include "Classes\PLAY.h"

//hold a spell instance
#include "Classes\SP.h"

//hold information about dungeon instances
#include "Classes\DUN.h"

//controls eq classes for player equipment 
//look at, and compact -> player
#include "Classes\EQU.h"


//holds serialized information from files
#include "Classes\winfo.h"

//holds the deck of cards
#include "Classes\deck.h"

//holds players hand
#include "Classes\card.h"

//controls card and deck classes
#include "Classes\maingame.h"

//contains a position for NPC movelist
#include "Classes\movelist.h"

//base class for a node
#include "Classes\NodeBase.h"

//base class for an object
#include "Classes\NodeObject.h"

//base class for an enemy/NPC
#include "Classes\NodeEnemy.h"

//store enemies LL
#include "Classes\mapenemieslist.h"

//script
#include "Classes\script.h"

//contains map,enemy,object maps
#include "Classes\MP.h"

//simple class to map string to memory
#include "Classes\commandmapping.h"

//contains functions that arent specifically in any other area
#include "Classes\exe.h"

//AVL trees 
FMOD::System     *fmodsystem; //handle to FMOD engine
AVLTree<SoundFile> soundz;
FMOD::Channel *channel;

//key:char *, value = variable pointer
AVLTree<commandmapping> variablePointers;

//link script names to an int, to use switch instead of comparing for every script command
//key:char *, value = int
AVLTree<int> scriptCommands;

AVLTree<commandmapping> consolez;
AVLTree<TextureImage> texturez;

LinkedList<NodeObject> helditems;
LinkedList<NodeObject> grounditems;
LinkedList<NodeObject> shopitems;
LinkedList<NodeObject> shopspells;
LinkedList<NodeObject> shoppotions;

//potiontemps is for use in setting the amount to buy in potionshop
char potiontemp[20];
LinkedList<NodeEnemy> NPC;
LinkedList<NodeObject> spellz;
//used to save npcs when entering a map
LinkedList<mapenemieslist> mapnpcs;

//function prototypes
void drawingame(int callfuncts);
int testsquareexit(void);
void initmode();
void glutStrokeInteger(int temp);
void glutStrokeString(char *string);

void myTimer(int value)
{
	if (ANIMATION.timerenabled&&GLOBAL.updateThreadCount == 1)
	{
		ANIMATION.openinganimationstep();
		glutTimerFunc(value, myTimer, value);
	}
	else
		GLOBAL.updateThreadCount = 0;

	glutPostRedisplay();
}

void _fclose(FILE * fpointer)
{
	if (fpointer == NULL)
	{
		//printf("\nPointer is NULL, cant close");
		return;
	}
	int val = fclose(fpointer);
	if (val != 0 && GLOBAL.debugenabled == true)
	{
		printf("\nWARNING! fclose returned non 0 value!:%d", val);
	}
}

int _fopen_s(FILE ** fpointer, char * path, char * type)
{
	_fclose(*fpointer);
	int val = fopen_s(fpointer, path, type);
	if (val != 0 && GLOBAL.debugenabled == true)
	{
		printf("\nWARNING! fopen returned non 0 value!:%d", val);
		if (val == 2)
			printf("\n2=Cant find file!");
		return -1;
	}
	return 0;
}

//below classes use parts so include here
#include "displayfunct.cpp"
#include "control.cpp"
#include "keyboard.cpp"

//cpps
#include "Classes\xml.cpp"
#include "Classes\path.cpp"
#include "Classes\pathhead.cpp"
#include "Classes\HC.cpp"
#include "Classes\mapstax.cpp"
#include "Classes\mapstackhead.cpp"
#include "Classes\TextureImage.cpp"
#include "Classes\SoundFile.cpp"

#include "Classes\anim.cpp"
#include "Classes\GLO.cpp"
#include "Classes\PLAY2.cpp"
#include "Classes\PLAY.cpp"

#include "Classes\SP.cpp"
#include "Classes\DUN.cpp"
#include "Classes\EQU.cpp"

#include "Classes\npcstore.cpp"
#include "Classes\objstore.cpp"
#include "Classes\armstore.cpp"
#include "Classes\wepstore.cpp"
#include "Classes\splstore.cpp"
#include "Classes\mapstore.cpp"
#include "Classes\exitpoint.cpp"

#include "Classes\winfo.cpp"
#include "Classes\deck.cpp"
#include "Classes\card.cpp"
#include "Classes\maingame.cpp"
#include "Classes\script.cpp"

#include "Classes\MP.cpp"
#include "Classes\consolestuffs.cpp"
#include "Classes\mapenemieslist.cpp"

#include "Classes\movelist.cpp"

#include "Classes\NodeBase.cpp"
#include "Classes\NodeObject.cpp"
#include "Classes\NodeEnemy.cpp"

#include "Classes\commandmapping.cpp"

#include "Classes\exe.cpp"





