//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _EXE_H
#define _EXE_H
#include "string"

//important global functions
class exe
{
public:
void quit(char * string2);
void playerdeath();
void spawnenemy();
void initvars();
void globalcount();
void initlists(bool ignoreshopinit);
void npcmain();

NodeEnemy* findnearest(NodeEnemy * attacker);
void vinit();
void initshop();
//initext-load all xml files for the game from files
void initextcfg();
void initweapons();
void initgame();
void initsigns();
void loadterraincase(int terrain);
void loadterraincase(int terrain,float alpha);
void loadlastvars();
void attackenemyfunction(int x, int y,bool israrm);
bool attacktype(NodeEnemy * attacker,NodeEnemy * thetarget);
void buypotion(objstore * newptr,int amount);
void buyspellhead(int y,int x);
void caststaticspell(int id,int manacost,int basedamage);
void castrangedspell();
void loadspell(int type,int direction,int ypos,int xpos,int fromplayer);
//void changecurrentmap(char * path);
void dealdamage(NodeEnemy * foundenemy,bool israrm);
bool dealdamagefunction(NodeEnemy * attacker, NodeEnemy * target);
void drawopeningscreen(void);
void drawstatsinventory(void);
void drawopeningtext(void);
void drawstatsmap(int pos);
void dropitem(int id,int x,int y);
void pickupfunction(int x, int y);
void inventoryhandle(NodeObject * newptr);
void equiphandle(armstore * newptr);
void weaponhandle(wepstore * newptr,bool islefthand);
float getlightlevel(int a,int b,bool darken);
void savefunction();
void loadfunction(char * name);
void executecommand(void);
void popposition(int * y, int * x);
void pushposition(int y, int x);
void pushenemies();
void popenemies();
//void dungeonassist();
void loadpresets();

bool isnear(int atx,int aty,int tgx,int tgy);
void giveweapon(int id,bool forlefthand);
void findvalues(int px, int py,int tx,int ty,NodeEnemy * player);
int findpath(NodeEnemy * attacker,const int tx,const int ty,int makepath);
void randomnpc(NodeEnemy * nodeptr);
void moveenemy(NodeEnemy * attacker,NodeEnemy * thetarget);
void givehelditems(int id);
void talkfunct(int x,int y);
void opendoorfunction(int x,int y);
void lookfunction(int x, int y);

inline void loadTexture(char *filename);
bool loadTexture(TextureImage *texture, char *filename);
void clearoldtextures();
void rmtexturez();

inline void FMUSIC_StopSong(FMOD::Sound * mptr);
inline void FSOUND_Init(int a, int b, int c);

inline void PlaySound(FMOD::Sound * mptr);
inline void loadSound(const char *filename);
inline void loadSound(const char *filename,int volume);
bool loadSound(SoundFile *sound, const char *filename);

bool loadMusic(const char *filename);
bool loadMusic(SoundFile *sound, const char *filename);
bool stopMusic(const char * filename);
bool stopMusic(FMOD::Sound * mptr);
void clearoldsounds();
void rmsoundz();

bool moveplayer(int &px,int &py,int key);
bool testsquareexit(void);
void printterrain(bool terrainonly);

void trimmemory();

void mapjoinpoint(int x1,int y1,int x2, int y2);
void mapgen(int maxx,int maxy,int maptype);

//given coords, return the exitpoint on the current map to another map
exitpoint * findmap(int xpos,int ypos);

//save the current dungeon to a file
void savedungeonmapfile(char * filename);
//load dungeon and related tidbits from dungeon file
void loaddungeonmapfile(char * filename);

void loadMap(mapstore * loadmap);
void loadMap(exitpoint * loadmappoint);
void loadMap(int ladder);
void loadMapGeneralSteps(mapstore * newmap);

void loadfromfile(mapstore * newptr,int fileDungeonId);
void loadfromfile(mapstore * newptr);

void loadmapcurrenttile();

void getdungeoninfo(char * path);
void readfromdungeon(char * path);

static int playerhas(int itemID);
static int mapenemyamount(int faction);

};
exe EXEC;

#endif