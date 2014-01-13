//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MP_H
#define _MP_H

class MP
{
public:

	//normal pass
	inline bool passable(int y,int x,NodeEnemy * attacker);
	//special pass just for path finding, no NT_FRIENDLY allowing
	inline bool passable2(int y,int x,NodeEnemy * attacker,bool checkfornpc);
	
	int **MAPFILE;
	void MAPFILEdinit();


	int **RAYTRACE;
	//0x1 for player
	NodeEnemy ***MAPFILEENEMY;
	NodeObject ***MAPFILEITEM;

	
	//scripts for the current map
	LinkedList<script> MAPFILESSCRIPTS;
	void runMapScript();
	void executeScriptEffects(effectObj * eptr);

	void RAYTRACEdinit();
	void RAYTRACEinit();
	

	//custom param
	void TERRAINLOSinit(int vw,int vh);
	//pass current viewwidth/height to above function
	void TERRAINLOSinit();

	
	//sets all mapfile arrays
	//mapxsize and mapysize are the new sizes of the map
	//null as mapfile does not load mapfile
	void loadMAPFILES(int mapxsize,int mapysize,FILE * mapfile);
	void loadMAPFILES(int mapxsize,int mapysize);

	void init();
	void dinit(bool docompare,bool justarrays);
	
	//apply ray tracing to a point from a point
	//xabs,yabs=position of player
	//xrel,yrel=offset of light from top left corner of screen
	//xdist,ydist=from player, what is the targetted tile
	//maxx,maxy=from top left corner of screen, how many squares to do light tracing on
	void applyRayTrace(int ** grid,int xabs,int yabs,int xrel,int yrel,int xdist,int ydist,int maxx,int maxy);
	
	//get lightmap for different lighting types
	//maxy,maxx=from top left corner of screen, how many squares to do light tracing on
	//xabs,yabs=position of player
	//yrel,xrel=offset of light from top left corner
	void rayTraceMain(int ** grid,int maxy,int maxx,int xabs,int yabs,int yrel,int xrel);

	inline int emapwidth();
	inline int emapheight();
	void changeEXTMAP(int MAPWIDTH,int MAPHEIGHT,bool force);

	//int mapdarklevel;

	int xy[2];
	int lastx;
	int lasty;

	void copystack(mapstackhead * copyfrom,mapstackhead * copyto);
	mapstackhead mapSTACK;
	
	mapstore * currentmap;
	mapstore * lastmap;
	
	LinkedList<exitpoint> exitpoints;

	
	int rearmx;
	int rearmy;
	int STARTX;
	int STARTY;	
	char * savevals(char * objtype);
	void loadvals(FILE * fileptr);

	~MP();
	MP();
private:
	//dinit deletes arrays
	//init deletes arrays, then creates new array to size of mapfiles.emapwidth/emapheight
	void MAPFILEITEMdinit();
	void MAPFILEinit();
	//with mapfile, can directly load into array - easier
	void MAPFILEinit(FILE * inputstreamz);
	void MAPFILEENEMYinit();
	void MAPFILEENEMYdinit();
	void MAPFILEITEMinit();
	int	EXTMAPWIDTH;
	int	EXTMAPHEIGHT;
};
MP MAPFILES;

#endif