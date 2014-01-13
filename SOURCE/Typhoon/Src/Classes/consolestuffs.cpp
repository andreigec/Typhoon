//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _CONSOLESTUFFS_CPP
#define _CONSOLESTUFFS_CPP

char* consolestuffs::savevals(char * objtype)
{
	char temp[100];temp[0]=0;
	char out[1000];out[0]=0;
	//console text
	int a=0;
	while (strlen(CONSOLE.consolearray[a])!=0&&a<15)
	{
		int length=(int)strlen(CONSOLE.consolearray[a]);
		sprintf(temp," %s %d %s",objtype,length,CONSOLE.consolearray[a]);
		strcat(out,temp);
		a++;
	}
	char *out2=new char[strlen(out)+1];
	strcpy(out2,out);
	return out2;
}

void consolestuffs::loadvals(FILE * fileptr,int * console)
{
	int length=0;
	char temps[100];
		fscanf_s(fileptr,"%d",&length);
		int templength=0;
		char supertemp[200];
		supertemp[0]=0;
		while (1)
		{
			fscanf_s(fileptr,"%s",temps,100);
			if (strlen(supertemp)!=0)
			{strcat(supertemp," ");templength++;}

			strcat(supertemp,temps);
			templength=(int)strlen(supertemp);
			if (templength>=length)
			{break;}
		}
		
		strcpy(consolearray[*console],supertemp);

		*console++;


}

void consolestuffs::init()
{
	for (int a=0;a<15;a++)
		strcpy(consolearray[a],"");

	strcpy(currentconsole,"");
	strcpy(prevconsole,"");
	currentconsolecarat=0;
	consolecheats=true;
}


consolestuffs::consolestuffs()
{
	init();
}

consolestuffs::~consolestuffs()
{
	for (int a=0;a<6;a++)
	strcpy(textarray[a],"");
		//consolearray[0][0]=0;
}

//mode
//0=nothing
//1=-=negative
//2=+=positive
//3=*=informative
void consolestuffs::pushtext(bool toconsole,int mode,char * str)
{
	char str2[500];str2[0]=0;
	if (mode==1)
	{
		strcat(str2,"-");
		strcat(str2,str);
	}
	
	else if (mode==2)
	{
		strcat(str2,"+");
		strcat(str2,str);
	}
	
	else if (mode==3)
	{
		strcat(str2,"*");
		strcat(str2,str);
	}
	else
	{
		strcat(str2,"/");
		strcat(str2,str);
	}

	if (toconsole==false)
	{
	int a=0;
	for (a=1;a<5;a++)
	{strcpy(textarray[5-a],textarray[5-(a+1)]);}
	strcpy(textarray[0],str2);return;
	}
	else
	{
		int a=0;
	for (a=1;a<15;a++)
	{strcpy(consolearray[15-a],consolearray[15-(a+1)]);}
	strcpy(consolearray[0],str2);
	return;
	}
}

//push a character onto the currently typed console line
void consolestuffs::pushconsolecurrent(char str,int area,char mode)
{
	//printf("\na=%d,str=%c,mode=%c",area,str,mode);
	area--;
	int a;
	int length=(signed)strlen(currentconsole);
	//printf("\nlength=%d",length);
	length--;

	if (mode=='d')
	{
		if (area<=length&&length>=0)
		{
			for (a=area;a<=maxstring-1;a++)
			{
				if (currentconsole[a+1]!='\0')
					currentconsole[a]=currentconsole[a+1];
				else
				{currentconsole[a]='\0';break;}
			}
		}
		else 
			;
		return;
	}

	else if (mode=='w')
	{
		if (length<=maxstring-2&&area<=maxstring-2&&area<=length)
		{currentconsole[length+1]=currentconsole[length];currentconsole[length+2]='\0';
		for (a=length;a>area;a--)
			currentconsole[a+1]=currentconsole[a];
		currentconsole[a+1]=str;

		}
		else if (length==-1)
		{currentconsole[0]=str;}
		else
			;
		//length=(signed)strlen(currentconsole);
		//printf("%d,%d",currentconsole[length-1],currentconsole[length]);
	}
	else
	{
		char temp[100];
		char temp2[20];
		strcpy(temp,"Warning, Push C error,str=");
		sprintf(temp2,"%d",str);
		strcat(temp,temp2);
		strcat(temp," area=");
		sprintf(temp2,"%c",area);
		strcat(temp,temp2);
		strcat(temp," mode=");
		sprintf(temp2,"%c",mode);
		strcat(temp,temp2);
		pushtext(true,0,temp);
	}

	return;
}

void consolestuffs::printconsole(void)
{
	glColor3f(1,1,1);			
	for (int a=0;a<15;a++)
	{
		//glColor3f(1,1,1);
		glPushMatrix();
		if (consolearray[a][0]=='+')
			glColor3f(0,1,0);
		else if (consolearray[a][0]=='-')
			glColor3f(1,0,0);
		else if (consolearray[a][0]=='*')
			glColor3f(0,0.8,1);
		else if (consolearray[a][0]=='(')
		{
			int openb=0;int closedb=0;
			int counter2=0;
			while (consolearray[a][counter2]!=0)
			{
				if (consolearray[a][counter2]=='(')
					openb++;
				else if (consolearray[a][counter2]==')')
					closedb++;
				counter2++;
			}
			if (openb==1&&closedb==1)
			{
				char * tempo=NULL;
				tempo=strstr(consolearray[a],")");
				if (tempo!=NULL)
					glColor3f(1,1,0);
			}
		}

		else
			glColor3f(1,1,1);
		int len=(int)strlen(consolearray[a]);
		if (len<=30)
			glScalef(.8,.8,.8);
		else if (len<=40)
			glScalef(.6,.6,.6);
		else
			glScalef(.5,.5,.5);

		char printy[300];printy[0]=0;
		int b=1;
		for (;b<(int)strlen(consolearray[a]);b++)
			printy[b-1]=consolearray[a][b];
		printy[b-1]=0;

		glutStrokeString(printy);
		glPopMatrix();
		glTranslatef(0,130,0);
	}
}

//prints text on screen
void consolestuffs::printtext(void)
{
	int a;
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(5,7,0);
	glScalef(.2,.15,.2);
	glColor3f(1,1,1);
	for (a=0;a<5;a++)
	{
		//glColor3f(1,1,1);
		glPushMatrix();
		if (CONSOLE.textarray[a][0]=='+')
			glColor3f(0,1,0);
		else if (CONSOLE.textarray[a][0]=='-')
			glColor3f(1,0,0);
		else if (CONSOLE.textarray[a][0]=='*')
			glColor3f(0,.8,1);
		else if (CONSOLE.textarray[a][0]=='(')
		{
			int openb=0;int closedb=0;
			int counter2=0;
			while (CONSOLE.textarray[a][counter2]!=0)
			{
				if (CONSOLE.textarray[a][counter2]=='(')
					openb++;
				else if (CONSOLE.textarray[a][counter2]==')')
					closedb++;
				counter2++;
			}
			if (openb==1&&closedb==1)
			{
				char * tempo=NULL;
				tempo=strstr(CONSOLE.textarray[a],")");
				if (tempo!=NULL)
					glColor3f(1,1,0);
			}
		}
		else
			glColor3f(1,1,1);
		if (strlen(CONSOLE.textarray[a])>=30&&strlen(CONSOLE.textarray[a])<40)
			glScalef(.8,.8,.8);
		else if (strlen(CONSOLE.textarray[a])>=40)
			glScalef(.6,.6,.6);

		char printy[300];printy[0]=0;
		int b=1;
		for (;b<(int)strlen(textarray[a]);b++)
			printy[b-1]=textarray[a][b];
		printy[b-1]=0;		
	
		glutStrokeString(printy);
		glPopMatrix();
		glTranslatef(0,130,0);
	}
glPopMatrix();
}
#endif