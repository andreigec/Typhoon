//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _GLO_CPP
#define _GLO_CPP

char* GLO::savevals(char * objtype)
{
	
	char temp[100];temp[0]=0;
	sprintf(temp," %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",objtype,\
	worldstatus,nighttend,isfullscreen,count,spawnenemies,loopswitch,loopswitch2,\
	lockcount,questloopswitch,fadestyle,fadeamount,fadestart,blackscreen,seed);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}

void GLO::loadvals(FILE * fileptr)
{
	fscanf_s(fileptr,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d",\
		&worldstatus,&nighttend,&isfullscreen,&count,&spawnenemies,&loopswitch,&loopswitch2,\
		&lockcount,&questloopswitch,&fadestyle,&fadeamount,&fadestart,&blackscreen,&seed);
	srand(seed);
}


void GLO::saveconfig()
{
FILE * newfile;
fopen_s(&newfile,"Data/CFG/config.cfg","w");
fprintf_s(newfile,"xresolution %d \nyresolution %d \nautochangekeyboardrepeatspeed  %d \ndebug %d \nsound %d \nconsole %d \nsfxvolume %d \nmusicvolume %d \nmastervolume %d \n",xresolution,yresolution,changeKeyboardRepeatSpeed,debugenabled,soundenabled,consoleenabled,soundvolume,musicvolume,mastervolume);
_fclose(newfile);
}

void GLO::loadconfig()
{
FILE * resolution=NULL;
	fopen_s(&resolution,"Data/CFG/config.cfg","r");
	fscanf_s(resolution,"%*s %d %*s %d %*s",&xresolution,&yresolution);
	fscanf_s(resolution,"%d %*s %d %*s %d %*s",&changeKeyboardRepeatSpeed,&debugenabled,&soundenabled);
	fscanf_s(resolution,"%d %*s %d %*s",&consoleenabled,&soundvolume);
	fscanf_s(resolution,"%d %*s %d",&musicvolume,&mastervolume);
	_fclose(resolution);

}

void GLO::init()
{
	updateThreadCount=0;

	seed=7;
	ANIMATION.tilesizeinit();
	spawnenemies=true;
	count=0;
	firsttime=true;
	//enemyrate=0;
	loopswitch=LS_OPENING;
	loopswitch2=0;
	runninggame=0;
	worldstatus=0;
	nighttend=1;
	//minenemylevel=0;
	debugTiles=0;
	lockcount=false;
	questloopswitch=1;
	blackscreen=false;
	fadestyle=0;
	fadeamount=0;
	fadestart=200;
}
GLO::GLO()
{
	init();
}
GLO::~GLO()
{
	fadestart=0;
}

#endif