//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _TYPHOON_CPP
#define _TYPHOON_CPP

//labels used: (TODO:)?`hard code`: hard coded variables, may become redundant or wrong in the future

//change these per version!!!
//HCVARS.version
//HCVARS.vname
//-----------------------
#include "header.cpp"
//store keyboard status on load, reinit on exit
int KBD=0;
int KBS=0;

void onexit (void)
{
	SystemParametersInfoA(HCVARS.SETKEYBOARDDELAY,KBD,NULL,0);
	SystemParametersInfoA(HCVARS.SETKEYBOARDSPEED,KBS,NULL,0);
}

void changesize(int w, int h )
{
	if (GLOBAL.isfullscreen==false)
		glutReshapeWindow(GLOBAL.xresolution,GLOBAL.yresolution);

	glViewport(50,50,w,h);

	if (GLOBAL.loopswitch==LS_NORMAL)
		GLOBAL.loopswitch=LS_PASS;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	ANIMATION.width=w;ANIMATION.height=h;
	if ( h == 0 ) h = 1;
	glViewport( 0, 0, ANIMATION.width, ANIMATION.height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glutPostRedisplay ();
}


//gets called on each full screen call
void initmode()
{
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(GLOBAL.xresolution,GLOBAL.yresolution);
	if (GLOBAL.isfullscreen==true)
	{	
		glutDestroyWindow(1);
		glutGameModeString("1024x768:32@75" );
		int egm=glutEnterGameMode();
		if (GLOBAL.debugenabled==true)
			printf("\negm=%d",egm);
	}
	else
	{
		if (GLOBAL.firsttime==false)
			glutLeaveGameMode();
		glutInitWindowPosition(10,10); 
		glutCreateWindow(HCVARS.vname); 
	}

	EXEC.rmtexturez();
	GLOBAL.firsttime=false;
	glutDisplayFunc(display);
	glutSpecialFunc(special);	
	glutKeyboardFunc(normal);
	glutReshapeFunc(changesize);
	glDisable(GL_LINE_SMOOTH);
	glutSetCursor( GLUT_CURSOR_NONE);	
	glEnable(GL_BLEND);
	glutPostRedisplay();
}

//main startup function
void main(int argc, char** argv)
{
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetReportMode(_CRT_ERROR,_CRTDBG_MODE_DEBUG);

	SystemParametersInfoA(HCVARS.GETKEYBOARDDELAY,0,&KBD,0);
	SystemParametersInfoA(HCVARS.GETKEYBOARDSPEED,0,&KBS,0);

	atexit (onexit);
	glutInit(&argc,argv); 
	printf("\r-");
	if (FSOUND_GetVersion() < FMOD_VERSION)
	{
		printf("Error : You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
		exit(1);
	}

	if (!FSOUND_Init(44100, 64, 0))
	{EXEC.quit("fsound");}

	printf("\r\\");
	glEnable(GL_CULL_FACE);
	
	printf("\r|");
	EXEC.initlists(true);

	printf("\r/");
	EXEC.initvars();

	printf("\r-");
	initmode();

	printf("\r\\");
	EXEC.initextcfg();

	printf("\r|");
	glutSetCursor(GLUT_CURSOR_NONE);
	EXEC.vinit();

	printf("\r/");
	
	PLAYER.lockmove=false;
	GLOBAL.lockcount=true;
	GLOBAL.soundvolume=100;
	GLOBAL.musicvolume=100;
	GLOBAL.mastervolume=100;

	GLOBAL.loadconfig();
	
	if (GLOBAL.changeKeyboardRepeatSpeed)
	{
		SystemParametersInfoA(HCVARS.SETKEYBOARDDELAY,1,NULL,0);
		SystemParametersInfoA(HCVARS.SETKEYBOARDSPEED,10,NULL,0);
	}
	
	ANIMATION.openinganimationsetup();
	

	printf("\r ");
	glutMainLoop();
}

#endif