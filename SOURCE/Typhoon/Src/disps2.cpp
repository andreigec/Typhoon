template <class T> T* getInventoryItem(T* headptr,int count);

void talking()
{
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glColor4f(.2f,.2f,.4f,0.90f);	
	glVertex2f(10, 470);
	glColor4f(.3f,.3f,.5f,0.90f);	
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(10, 118);
	glEnd();

	glColor4f(1,1,1,.9);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(12, 470);
	glVertex2f(12, 118);
	glVertex2f(10, 118);

	glVertex2f(488, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(488, 118);

	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 468);
	glVertex2f(10, 468);

	glVertex2f(10, 118);
	glVertex2f(490, 118);
	glVertex2f(490, 116);
	glVertex2f(10, 116);

	glEnd();
	int temp2=(signed)strlen(INFOS.talkingcharacterbuffer2);
	if (temp2>0)
	{

		glColor4f(.3,.3,.5,.9);
		glBegin(GL_QUADS);
		glVertex2f(12, 468);
		glVertex2f(12+temp2*15, 468);
		glVertex2f(12+temp2*15, 430);
		glVertex2f(12, 430);

		glColor4f(1,1,1,.9);
		glVertex2f(12, 430);
		glVertex2f(12+temp2*15, 430);
		glVertex2f(12+temp2*15, 428);
		glVertex2f(12, 428);

		glVertex2f(12+temp2*15, 468);
		glVertex2f(14+temp2*15, 468);
		glVertex2f(14+temp2*15, 428);
		glVertex2f(12+temp2*15, 428);
		glEnd();

		//persons pic

		glColor3f(1, 1, 1);
		if (INFOS.talkingcharacterpicture!=NULL&&strlen(INFOS.talkingcharacterpicture)!=0)
		{
		EXEC.loadTexture(INFOS.talkingcharacterpicture);
		drawtile(15+temp2*15, 428,15+temp2*15, 468,55+temp2*15, 468,55+temp2*15, 428);
		}


		glDisable(GL_BLEND);
		glLoadIdentity();glTranslatef(20,440,0);glScalef(.2,.15,.2);glColor3f(1,1,1);
		glutStrokeString(INFOS.talkingcharacterbuffer2);
		glEnable(GL_BLEND);

	}
	int temp=(signed)strlen(INFOS.talknpcbuffer);


	//glPushMatrix();

	if (temp==0)
	{glLoadIdentity();glTranslatef(20,130,0);glScalef(.2,.15,.2);glColor3f(.6,.6,1);

	glutStrokeString("*Press any key to continue*");
	}
	else
	{
		glLoadIdentity();glTranslatef(30,400,0);glColor3f(1,1,1);
		glScalef(.15,.10,.15);
		int a;
		int b=40;
		int length=0;
		for (a=0;a<temp;a++)
		{length++;
		if (length>33)
		{
			if (INFOS.talknpcbuffer[a]==' ')
			{
				b+=30;glLoadIdentity();glTranslatef(0,440-b,0);glScalef(.15,.10,.15);
				length=0;
			}
		}

		glutStrokeCharacter(GLUT_STROKE_ROMAN,INFOS.talknpcbuffer[a]);
		}
		glLoadIdentity();glTranslatef(20,130,0);glScalef(.2,.15,.2);glColor3f(.6,.6,1);glutStrokeString("*Press any key to return*");
	}

}
void buyfood()
{
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glColor4f(.4,0,0,.5);
	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(10, 118);
	glEnd();

	glLoadIdentity();
	glColor3f(1,1,1);
	glTranslatef(20,440,0);
	glPushMatrix();
	glScalef(.2,.15,.2);
	glutStrokeString("What do you want to buy?");

	glPopMatrix();
	glTranslatef(0,-40,0);
	glPushMatrix();
	glScalef(.15,.10,.15);
	if (MAPFILES.rearmy==0)glColor3f(1,1,0); else glColor3f(.6,.6,.8);
	glutStrokeString("-Fruit = 100 GP = 40 Food");

	glPopMatrix();
	glTranslatef(0,-40,0);
	glPushMatrix();
	glScalef(.15,.10,.15);
	if (MAPFILES.rearmy==1)glColor3f(1,1,0); else glColor3f(.6,.6,.8);
	glutStrokeString("-Pastries = 200 GP = 90 Food");

	glPopMatrix();
	glTranslatef(0,-40,0);
	glPushMatrix();
	glScalef(.15,.10,.15);
	if (MAPFILES.rearmy==2)glColor3f(1,1,0); else glColor3f(.6,.6,.8);
	glutStrokeString("-Fish = 500 GP = 240 Food");

	glPopMatrix();
	glTranslatef(0,-40,0);
	glPushMatrix();
	glScalef(.15,.10,.15);
	if (MAPFILES.rearmy==3)glColor3f(1,1,0); else glColor3f(.6,.6,.8);
	glutStrokeString("-White Meats = 1000 GP = 500 Food");

	glPopMatrix();
	glTranslatef(0,-40,0);
	glPushMatrix();
	glScalef(.15,.10,.15);
	if (MAPFILES.rearmy==4)glColor3f(1,1,0); else glColor3f(.6,.6,.8);
	glutStrokeString("-Red Meats = 5000 GP = 2500 Food");

	glPopMatrix();
	glTranslatef(0,-40,0);
	//glPushMatrix();
	glScalef(.15,.10,.15);
	if (MAPFILES.rearmy==5)glColor3f(1,1,0); else glColor3f(.6,.6,.8);
	glutStrokeString("Exit shop");
}

void ingamemenu()
{
	glEnable(GL_BLEND);
	glColor4f(.3f,.3f,.3f,0.95f);	
	glBegin(GL_QUADS);
	glVertex2f(10, 460);
	glVertex2f(405, 460);
	glVertex2f(405, 130);
	glVertex2f(10, 130);

	glColor4f(.6f,.6f,.8f,0.8f);	
	glVertex2f(10, 460);
	glVertex2f(405, 460);
	glVertex2f(405, 455);
	glVertex2f(10, 455);

	glVertex2f(10, 460);
	glVertex2f(15, 460);
	glVertex2f(15, 130);
	glVertex2f(10, 130);

	glVertex2f(400, 460);
	glVertex2f(405, 460);
	glVertex2f(405, 130);
	glVertex2f(400, 130);

	glVertex2f(10, 130);
	glVertex2f(405, 130);
	glVertex2f(405, 125);
	glVertex2f(10, 125);

	glVertex2f(10, 160);
	glVertex2f(405, 160);
	glVertex2f(405, 155);
	glVertex2f(10, 155);
	glEnd();

	glLoadIdentity();
	glTranslatef(20,165,0);
	glScalef(.2,.15,.2);
	glPushMatrix();

	CONSOLE.printconsole();
	glPopMatrix();	
	glPushMatrix();
	glTranslatef(0,-190,0);
	glColor3f(1,1,1);

	int length=18;
	int start=CONSOLE.currentconsolecarat-length;
	if (start<0)start=0;
	int a=0;
	for (a=start;a<CONSOLE.currentconsolecarat;a++)
	{glutStrokeCharacter(GLUT_STROKE_ROMAN,CONSOLE.currentconsole[a]);}
	glColor3f(1,1,0);
	glutStrokeString("|");
	glColor3f(1,1,1);
	//printf("\nlen=%d",strlen(CONSOLE.currentconsole));
	int trumax=(signed)strlen(CONSOLE.currentconsole);
	int max=trumax;
	if (max>length)max=length;
	for (a=CONSOLE.currentconsolecarat;a<max;a++)
	{glutStrokeCharacter(GLUT_STROKE_ROMAN,CONSOLE.currentconsole[a]);}

	glPopMatrix();
	glLoadIdentity();
	glColor4f(1,1,1,1);
	glColor3f(1,0,0);

	glBegin(GL_QUADS);
	if (start>0)
	{
		glVertex2f(10, 165);
		glVertex2f(15, 165);
		glVertex2f(15, 150);
		glVertex2f(10, 150);
	}
	if (start+length<trumax)
	{
		glVertex2f(400, 165);
		glVertex2f(405, 165);
		glVertex2f(405, 150);
		glVertex2f(400, 150);
	}
	glEnd();
	glColor3f(1,1,1);
}

void casinochoice()
{
	glColor4f(.3f,.6f,.7f,0.90f);	
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(10, 350);
	glVertex2f(300, 350);
	glVertex2f(300, 225);
	glVertex2f(10, 225);
	glEnd();
	glDisable(GL_BLEND);

	glLoadIdentity();
	glTranslatef(10,300,0);
	glPushMatrix();
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmy==0)glColor3f(1, 1, 0);
	else glColor3f(1, 0, 0);
	glutStrokeString("Play Poker");

	glPopMatrix();
	glTranslatef(0,-50,0);
	//glPushMatrix();
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmy==1)glColor3f(1, 1, 0);
	else glColor3f(1, 0, 0);
	glutStrokeString("Leave");
}



void buyspellspellpotionmenu()
{
	glColor4f(.3f,.6f,.7f,0.90f);	
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(10, 350);
	glVertex2f(100, 350);
	glVertex2f(100, 150);
	glVertex2f(10, 150);
	glEnd();
	glDisable(GL_BLEND);

	if (GLOBAL.loopswitch==LS_BUYSPELLMENU||GLOBAL.loopswitch==LS_POTIONMENU)
	{
		glLoadIdentity();
		glTranslatef(10,300,0);
		glPushMatrix();
		glScalef(.25,.15,.25);
		if (MAPFILES.rearmy==0)glColor3f(1, 1, 0);
		else glColor3f(1, 0, 0);
		glutStrokeString("Buy");

		glPopMatrix();
		glTranslatef(0,-50,0);
		//glPushMatrix();
		glScalef(.25,.15,.25);
		if (MAPFILES.rearmy==1)glColor3f(1, 1, 0);
		else glColor3f(1, 0, 0);
		glutStrokeString("Leave");

	}
	else if (GLOBAL.loopswitch==LS_BUYORSELL)
	{
		glLoadIdentity();
		glTranslatef(10,300,0);
		glPushMatrix();
		glScalef(.25,.15,.25);
		if (MAPFILES.rearmy==0)glColor3f(1, 1, 0);
		else glColor3f(1, 0, 0);
		glutStrokeString("Buy");

		glPopMatrix();
		glTranslatef(0,-50,0);
		glPushMatrix();
		glScalef(.25,.15,.25);
		if (MAPFILES.rearmy==1)glColor3f(1, 1, 0);
		else glColor3f(1, 0, 0);
		glutStrokeString("Sell");		

		glPopMatrix();
		glTranslatef(0,-50,0);
		//glPushMatrix();
		glScalef(.25,.15,.25);
		if (MAPFILES.rearmy==2)glColor3f(1, 1, 0);
		else glColor3f(1, 0, 0);
		glutStrokeString("Leave");
	}
}
void exitmap()
{
	glColor4f(.3f,.6f,.7f,0.90f);	
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(10, 330);
	glVertex2f(150, 330);
	glVertex2f(150, 220);
	glVertex2f(10, 220);
	glEnd();
	glDisable(GL_BLEND);

	glLoadIdentity();
	glTranslatef(10,300,0);
	glPushMatrix();
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmy==0)glColor3f(1, 1, 0);
	else glColor3f(1, 0, 0);
	glutStrokeString("Exit Map");

	glPopMatrix();
	glTranslatef(0,-50,0);
	//glPushMatrix();
	glScalef(.25,.15,.25);
	if (MAPFILES.rearmy==1)glColor3f(1, 1, 0);
	else glColor3f(1, 0, 0);
	glutStrokeString("Stay");

}

void spells()
{//draw spell menu
	int temp=0;
	temp+=MAPFILES.rearmx;
	temp+=MAPFILES.rearmy*5;


	splstore * thisspell=INFOS.SPLSTORE[temp];

	int nid=0;
	bool playerhas=false;

	if (thisspell!=NULL)
	{
		nid=thisspell->id;
		while (nid>=100)
			nid-=100;
		if (PLAYER.hasSpellTable[nid]==true)
			playerhas=true;
	}

	int count=-1;

	glEnable(GL_BLEND);
	glColor4f(.0f,.4f,.8f,0.90f);	
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(10, 118);
	glEnd();

	glColor4f(1,1,1,.9);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(12, 470);
	glVertex2f(12, 118);
	glVertex2f(10, 118);

	glVertex2f(488, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(488, 118);

	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 468);
	glVertex2f(10, 468);

	glVertex2f(10, 118);
	glVertex2f(490, 118);
	glVertex2f(490, 116);
	glVertex2f(10, 116);

	glEnd();

	glDisable(GL_BLEND);

	glLoadIdentity();
	glTranslatef(15,450,0);
	glPushMatrix();
	glScalef(.25,.15,.25);
	glColor3f(1, 1, 0);
	glutStrokeString("Spell Menu");
	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.25,.15,.25);
	glutStrokeString("Choose a spell to cast");
	glPopMatrix();
	glTranslatef(0,-30,0);
	glScalef(.25,.15,.25);
	glutStrokeString("ESC/C to exit");

	glColor3f(0, 1, 0);
	glLoadIdentity();
	glTranslatef(20,130,0);
	glPushMatrix();
	glScalef(.20,.10,.20);
	glutStrokeString("Spell:");
	if (playerhas)
		glutStrokeString(thisspell->name);

	glPopMatrix();
	glTranslatef(0,30,0);
	glPushMatrix();
	glScalef(.20,.10,.20);
	glutStrokeString("MP Required:");
	if (playerhas)
		glutStrokeInteger(thisspell->mp);

	glPopMatrix();
	glTranslatef(0,30,0);
	glPushMatrix();
	glScalef(.20,.10,.20);
	glutStrokeString("Base Effect:");
	if (playerhas)
	{
		if (thisspell->id>=420&&thisspell->id<=430)
			glutStrokeInteger(thisspell->basedamage*5);
		else if (thisspell->id>=430&&thisspell->id<=449)
			glutStrokeInteger(thisspell->basedamage*10);
		else
			glutStrokeInteger(thisspell->basedamage);
		if (thisspell->id==499)
			glutStrokeString("% HP");
	}


	glPopMatrix();
	glTranslatef(0,30,0);
	glPushMatrix();
	glScalef(.20,.10,.20);
	if (playerhas)
	{
		if (thisspell->id<450&&thisspell->id>=400)
			glutStrokeString("Ranged Spell");
		else if (thisspell->id>=450&&thisspell->id<500)
			glutStrokeString("Static Spell");
	}

	glPopMatrix();
	glTranslatef(0,30,0);
	glPushMatrix();
	glScalef(.20,.10,.20);
	if (playerhas)
	{
		if (thisspell->id==499)
			glutStrokeString("100% MP Cost");
		else
		{
			if ((thisspell->id>=400&&thisspell->id<421)||thisspell->id>=450)
				glutStrokeString("Initial MP Cost Only");
			else if (thisspell->id>=421&&thisspell->id<431)
				glutStrokeString("5 MP per square");
			else if (thisspell->id>=431&&thisspell->id<450)
				glutStrokeString("20 MP per square");
		}
		if (thisspell->id>=421&&thisspell->id<450)
		{
			glPopMatrix();
			glTranslatef(0,30,0);
			glPushMatrix();
			glScalef(.20,.10,.20);
			glutStrokeString("Max movement:");
			int temp=PLAYER.magic-thisspell->mp;
			int temp2=0;
			if (thisspell->id>=421&&thisspell->id<431)
			{temp2=temp;temp2/=5;if (temp2<=0)temp2=0;glutStrokeInteger(temp2);}
			else if (thisspell->id>=431&&thisspell->id<450)
			{temp2=temp;temp2/=20;if (temp2<=0)temp2=0;glutStrokeInteger(temp2);}
		}
	}


	glPopMatrix();
	glTranslatef(0,30,0);
	//glPushMatrix();
	glScalef(.13,.10,.13);
	//count??
	if (playerhas)
	{
		if (thisspell->mp>PLAYER.maxmagic)
			glutStrokeString("Can't Use, max MP too low");
		else if (thisspell->mp>PLAYER.magic)
			glutStrokeString("Can't Use, MP too low");
	}
	glLoadIdentity();
	glColor3f(.5,.5,.5);
	glBegin(GL_QUADS);
	glVertex2f(285, 323);
	glVertex2f(485, 323);
	glVertex2f(485, 121);
	glVertex2f(285, 121);
	glEnd();

	count=-1;
	temp=0;
	for (int l1=0;l1<5;l1++)
	{
		for (int l2=0;l2<5;l2++)
		{
			count++; 
			temp=l2;temp+=l1*5;

			splstore * thisspell2= INFOS.SPLSTORE[temp];
			int nid2=-1;
			if (thisspell2!=NULL)
			{
				nid2=thisspell2->id;
				while (nid2>=100)
					nid2-=100;
			}

			glColor3f(0,1,0);

			glBegin(GL_QUADS);
			glColor3f(0,1,0);
			glVertex2f(286+(40*l2), 283-(40*l1));
			glVertex2f(286+(40*l2), 321-(40*l1));
			glVertex2f(324+(40*l2), 321-(40*l1));
			glVertex2f(324+(40*l2), 283-(40*l1));
			glEnd();

			if (thisspell2!=NULL&&PLAYER.hasSpellTable[nid2]==true)
			{
				glColor3f(1,1,1);

				glEnable(GL_BLEND);
				EXEC.loadTexture(thisspell2->path);
				drawtile(286+(40*l2), 283-(40*l1),286+(40*l2), 321-(40*l1),324+(40*l2), 321-(40*l1),324+(40*l2), 283-(40*l1));

				//printf("\nmm=%d,mtid=%d",PLAYER.maxmagic,INFOS.magictableid[temp][1]);
				if (PLAYER.maxmagic<thisspell2->mp)
				{
					glBegin(GL_QUADS);
					glColor4f(.3,.3,.3,.3);
					glVertex2f(286+(40*l2), 283-(40*l1));
					glVertex2f(286+(40*l2), 321-(40*l1));
					glVertex2f(324+(40*l2), 321-(40*l1));
					glVertex2f(324+(40*l2), 283-(40*l1));
					glEnd();
				}

				else if (PLAYER.magic<thisspell2->mp)
				{
					glBegin(GL_QUADS);
					glColor4f(.5,.5,.5,.3);
					glVertex2f(286+(40*l2), 283-(40*l1));
					glVertex2f(286+(40*l2), 321-(40*l1));
					glVertex2f(324+(40*l2), 321-(40*l1));
					glVertex2f(324+(40*l2), 283-(40*l1));
					glEnd();
				}




				glDisable(GL_BLEND);


			}

			if (l2==MAPFILES.rearmx&&l1==MAPFILES.rearmy)
			{
				//printf("\nx=%d,y=%d,CX=%d,CY=%d",b,a,MAPFILES.rearmx,MAPFILES.rearmy);

				glEnable(GL_BLEND);
				glColor3f(1,1,1);
				EXEC.loadTexture("Data/Images/Other/zweihander.tga");

				drawtile(286+(40*l2), 283-(40*l1),286+(40*l2), 321-(40*l1),324+(40*l2), 321-(40*l1),324+(40*l2), 283-(40*l1));

				glDisable(GL_BLEND);
			}
		}
		glEnable(GL_BLEND);			}
}


void optionsmenu()
{
	glEnable(GL_BLEND);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(5, 5);
	glVertex2f(5, 475);
	glColor3f(0.0, 1.0, 0.5);
	glVertex2f(635, 475);
	glVertex2f(635, 5);
	glEnd();

	glLoadIdentity();
	glTranslatef(10,420,0);
	glPushMatrix();
	glScalef(.3,.2,.3);
	glColor3f(0.0, 1.0, 0.5);
	glutStrokeString("OPTIONS");

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==0)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);
	glutStrokeString("Sound : ");
	if (GLOBAL.soundenabled==true)
		glutStrokeString("ON");
	else
		glutStrokeString("OFF");

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==1)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);

	glutStrokeString("Console is: ");
	if (GLOBAL.consoleenabled==true)
		glutStrokeString("ON");
	else
		glutStrokeString("OFF");

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==2)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);
	glutStrokeString("Fullscreen is: ");
	if (GLOBAL.isfullscreen==true)
		glutStrokeString("ON");
	else
		glutStrokeString("OFF");

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==3)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);

	char temps[100];temps[0]=0;
	strcpy(temps,"Sound Volume: ");
	char temps2[20];temps2[0]=0;
	sprintf(temps2,"%d",GLOBAL.soundvolume);

	strcat (temps,temps2);
	strcat (temps,"%");
	glutStrokeString(temps);

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==4)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);

	temps[0]=0;
	strcpy(temps,"Music Volume: ");
	temps2[0]=0;
	sprintf(temps2,"%d",GLOBAL.musicvolume);

	strcat (temps,temps2);
	strcat (temps,"%");
	glutStrokeString(temps);

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==5)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);

	temps[0]=0;
	strcpy(temps,"Master Volume: ");
	temps2[0]=0;
	sprintf(temps2,"%d",GLOBAL.mastervolume);

	strcat (temps,temps2);
	strcat (temps,"%");
	glutStrokeString(temps);

	glPopMatrix();
	glTranslatef(0,-30,0);
	//glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==6)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(0.0, 1.0, 0.5);

	glutStrokeString("Return");

}

void dropstatsuse(){

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 480);
	glVertex2f(640, 480);
	glVertex2f(640, 0);
	glEnd();	

	if (GLOBAL.loopswitch==LS_STATS)
	{glPushMatrix();EXEC.drawstatsmap(0);glPopMatrix();}
	else
	{
		//info bar
		glColor3f(.5,.5,.5);
		glBegin(GL_QUADS);
		glVertex2f((630-0*(250/5)), 335);
		glVertex2f((630-6*(250/5)), 335);
		glVertex2f((630-6*(250/5)), 315);
		glVertex2f((630-0*(250/5)), 315);
		glEnd();

		glColor3f(1,1,1);
		glBegin(GL_LINE_LOOP);
		glVertex2f((630-0*(250/5)), 335);
		glVertex2f((630-6*(250/5)), 335);
		glVertex2f((630-6*(250/5)), 315);
		glVertex2f((630-0*(250/5)), 315);
		glEnd();
	}

	EXEC.drawstatsinventory();

	glLoadIdentity( );
	glScalef(.25,.15,.25);
	glTranslatef(20 ,3000,0);
	glColor3f(1,1,1);

	if (GLOBAL.loopswitch!=LS_STATS)
	{
		int rearm=0;
		rearm=MAPFILES.rearmy*5;
		rearm+=MAPFILES.rearmx;
		NodeObject * temp=helditems[rearm];
		glPushMatrix();
		glLoadIdentity();
		glColor3f(0.4, 0.4, 0.4);

		if (GLOBAL.loopswitch!=LS_USEMENU)
		{
			glBegin(GL_QUADS);
			glVertex2f(328, 270);
			glVertex2f(328, 290);
			glVertex2f(630, 290);
			glVertex2f(630, 270);
			glEnd();
		}

		glColor3f(1, 1,1);
		if (temp!=NULL||(MAPFILES.rearmx==-1||MAPFILES.rearmy==-1))
		{//draw identity string for weapon/armour

			glLoadIdentity();
			if (GLOBAL.loopswitch!=LS_USEMENU)
				glTranslatef(330,275,0);
			else
				glTranslatef(330,322,0);
			glScalef(.2,.1,.2);

			if (MAPFILES.rearmy==-1)
			{
				if (MAPFILES.rearmx==0)
				{
					if (EQUIPMENT.RARM.type!=T_FISTS)
						glutStrokeString(INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->name);
				}
				else if (MAPFILES.rearmx==1)
				{
					if (EQUIPMENT.LARM.type!=T_FISTS)
						glutStrokeString(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->name);
				}

			}
			else if (MAPFILES.rearmx==-1)
			{
				if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==0)
				{
					if (isarmour(EQUIPMENT.HELM.type))
						glutStrokeString(INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->name);
				}
				else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==1)
				{
					if (isarmour(EQUIPMENT.CHEST.type))
						glutStrokeString(INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->name);
				}
				else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==2)
				{
					if (isarmour(EQUIPMENT.LEGS.type))
						glutStrokeString(INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->name);
				}
				else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==3)
				{
					if (isarmour(EQUIPMENT.SHOES.type))
						glutStrokeString(INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->name);
				}

			}
			else if (temp!=NULL)
			{
				if (isweapon(temp->type))
					glutStrokeString(INFOS.WEPSTOREPTR[temp->id-200]->name);
				else if (isarmour(temp->type))
					glutStrokeString(INFOS.ARMSTOREPTR[temp->id-500]->name);
				else if (isobject(temp->type))
				{
					char temp2[100];temp2[0]=0;
					strcpy(temp2,INFOS.OBJSTOREPTR[temp->id-300]->name);
					strcat(temp2,"x");
					char tempo[20];tempo[0]=0;
					sprintf(tempo,"%d",temp->amount);
					strcat(temp2,tempo);
					glutStrokeString(temp2);
				}
			}
		}
		glPopMatrix();


		if (GLOBAL.loopswitch==LS_DROP)
			glPushMatrix();
		if (GLOBAL.loopswitch==LS_DROP)
		{glPushMatrix();glutStrokeString("Drop - press enter");
		glPopMatrix();glTranslatef(0,-200,0);glPushMatrix();glutStrokeString("to drop item on ground.");
		glPopMatrix();glTranslatef(0,-200,0);glutStrokeString("ESC/D to exit");}


		else if (GLOBAL.loopswitch==LS_USEMENU)
		{glPushMatrix();glutStrokeString("Use - press enter");
		glPopMatrix();glTranslatef(0,-200,0);glPushMatrix();glutStrokeString("to use items");
		glPopMatrix();glTranslatef(0,-200,0);glutStrokeString("ESC/U to exit");}


		if (GLOBAL.loopswitch==LS_DROP)
			glPopMatrix();

		int totalArmour=0;
		if (isarmour(EQUIPMENT.HELM.type))
			totalArmour+=INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->defensePercent;
		if (isarmour(EQUIPMENT.CHEST.type))
			totalArmour+=INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->defensePercent;
		if (isarmour(EQUIPMENT.LEGS.type))
			totalArmour+=INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->defensePercent;
		if (isarmour(EQUIPMENT.SHOES.type))
			totalArmour+=INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->defensePercent;

		if (temp!=NULL&&(MAPFILES.rearmx!=-1&&MAPFILES.rearmy!=-1))
		{
			int nid=temp->id;
			while (nid>=100)
				nid-=100;

			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			if (isweapon(temp->type)&&GLOBAL.loopswitch!=LS_STATS)
			{
				glutStrokeString("Base Damage=");glutStrokeInteger(INFOS.WEPSTOREPTR[nid]->damage);

				glPopMatrix();
				glTranslatef(0,-30,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glutStrokeString("Base Gold Value=");
				glutStrokeInteger(INFOS.WEPSTOREPTR[nid]->cost);

				glPopMatrix();
				glTranslatef(0,-30,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glutStrokeString("Str req'd for Bonus=");
				glutStrokeInteger(INFOS.WEPSTOREPTR[nid]->strengthReq);

				glPopMatrix();
				glTranslatef(0,-30,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glutStrokeString("Total Damage=");
				glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage+INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage);

				glPopMatrix();
				glTranslatef(0,-60,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glutStrokeString("--Str Comparison--");

				if (INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage>INFOS.WEPSTOREPTR[nid]->damage)
				{
					glPopMatrix();
					glTranslatef(0,-30,0);
					glPushMatrix();
					glScalef(.2,.1,.2);
					glColor3f(1,0,0);
					glutStrokeString("Top Weapon > this");
				}
				else if (INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage<INFOS.WEPSTOREPTR[nid]->damage)
				{
					glPopMatrix();
					glTranslatef(0,-30,0);
					glPushMatrix();
					glScalef(.2,.1,.2);
					glColor3f(0,1,0);
					glutStrokeString("Top Weapon < this");
				}
				else
				{
					glPopMatrix();
					glTranslatef(0,-30,0);
					glPushMatrix();
					glScalef(.2,.1,.2);
					glColor3f(1,1,1);
					glutStrokeString("Top Weapon = this");
				}

				if (INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage>INFOS.WEPSTOREPTR[nid]->damage)
				{
					glPopMatrix();
					glTranslatef(0,-30,0);
					glPushMatrix();
					glScalef(.2,.1,.2);
					glColor3f(1,0,0);
					glutStrokeString("Bottom Weapon > this");
				}
				else if (INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage<INFOS.WEPSTOREPTR[nid]->damage)
				{
					glPopMatrix();
					glTranslatef(0,-30,0);
					glPushMatrix();
					glScalef(.2,.1,.2);
					glColor3f(0,1,0);
					glutStrokeString("Bottom Weapon < this");
				}
				else
				{
					glPopMatrix();
					glTranslatef(0,-30,0);
					glPushMatrix();
					glScalef(.2,.1,.2);
					glColor3f(1,1,1);
					glutStrokeString("Bottom Weapon = this");
				}

				glPopMatrix();


			}

			else if (isarmour(temp->type)&&GLOBAL.loopswitch!=LS_STATS)
			{
				glutStrokeString("Base Defense %=");		
				glutStrokeInteger(INFOS.ARMSTOREPTR[temp->id-500]->defensePercent);

				glPopMatrix();
				glTranslatef(0,-30,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glutStrokeString("Base Gold Value=");
				glutStrokeInteger(INFOS.ARMSTOREPTR[temp->id-500]->cost);

				glPopMatrix();
				glTranslatef(0,-30,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glColor3f(1,1,1);
				glutStrokeString("Total Armour %=");
				glutStrokeInteger(totalArmour);
				//asdaasd
				glPopMatrix();
				glTranslatef(0,-60,0);
				glPushMatrix();
				glScalef(.2,.1,.2);
				glutStrokeString("--Def Comparison--");

				if (isarmour(temp->type)&&isarmour(EQUIPMENT.HELM.type))
				{
					if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent<INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,0,0);
						glutStrokeString("Worn > this");
					}
					else if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent>INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(0,1,0);
						glutStrokeString("Worn < this");
					}
					else
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,1,1);
						glutStrokeString("Worn = this");
					}
				}

				else if (temp->type==T_CHEST&&isarmour(EQUIPMENT.CHEST.type))
				{
					if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent<INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,0,0);
						glutStrokeString("Worn > this");
					}
					else if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent>INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(0,1,0);
						glutStrokeString("Worn < this");
					}
					else
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,1,1);
						glutStrokeString("Worn = this");
					}
				}

				else if (temp->type==T_LEGS&&isarmour(EQUIPMENT.LEGS.type))
				{
					if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent<INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,0,0);
						glutStrokeString("Worn > this");
					}
					else if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent>INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(0,1,0);
						glutStrokeString("Worn < this");
					}
					else
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,1,1);
						glutStrokeString("Worn = this");
					}
				}

				else if (temp->type==T_SHOES&&isarmour(EQUIPMENT.SHOES.type))
				{
					if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent<INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,0,0);
						glutStrokeString("Worn > this");
					}
					else if (INFOS.ARMSTOREPTR[temp->id-500]->defensePercent>INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->defensePercent)
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(0,1,0);
						glutStrokeString("Worn < this");
					}
					else
					{
						glPopMatrix();
						glTranslatef(0,-30,0);
						//glPushMatrix();
						glScalef(.2,.1,.2);
						glColor3f(1,1,1);
						glutStrokeString("Worn = this");
					}
				}


				glPopMatrix();


			}
			//else if (GLOBAL.loopswitch==WEAR&&(temp->id>=200&&temp->id<300))
			//	{glutStrokeString("Cannot Wear");glPopMatrix();}
			//else if (GLOBAL.loopswitch==REARM&&(temp->id>=500&&temp->id<600))
			//	{glutStrokeString("Cannot Arm");glPopMatrix();}
			//else
			glPopMatrix();



		}
		else if (MAPFILES.rearmx==1&&MAPFILES.rearmy==-1)
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);


			glutStrokeString("Base Damage=");glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Base Gold Value=");
			glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->cost);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Str req'd for Bonus=");
			glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->strengthReq);

			glPopMatrix();
			glTranslatef(0,-30,0);
			//glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Total Damage=");
			glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage+INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage);
		}

		else if (MAPFILES.rearmx==0&&MAPFILES.rearmy==-1)
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);


			glutStrokeString("Base Damage=");glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Base Gold Value=");
			glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->cost);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Str req'd for Bonus=");
			glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->strengthReq);

			glPopMatrix();
			glTranslatef(0,-30,0);
			//glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Total Damage=");
			glutStrokeInteger(INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage+INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage);

		}

		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==0&&isarmour(EQUIPMENT.HELM.type))
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Base Defense %=");glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->defensePercent);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Base Gold Value=");
			glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->cost);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glColor3f(1,1,1);
			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);


		}
		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==0)
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);

		}

		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==1&&isarmour(EQUIPMENT.CHEST.type))
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);


			glutStrokeString("Base Defense %=");glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->defensePercent);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Base Gold Value=");
			glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->cost);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glColor3f(1,1,1);
			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);

		}
		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==1)
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);

		}

		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==2&&isarmour(EQUIPMENT.LEGS.type))
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Base Defense %=");glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->defensePercent);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Base Gold Value=");
			glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->cost);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glColor3f(1,1,1);
			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);

		}
		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==2)
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);

		}

		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==3&&isarmour(EQUIPMENT.SHOES.type))
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Base Defense %=");glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->defensePercent);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glutStrokeString("Base Gold Value=");
			glutStrokeInteger(INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->cost);

			glPopMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
			glScalef(.2,.1,.2);
			glColor3f(1,1,1);
			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);

		}
		else if (MAPFILES.rearmx==-1&&MAPFILES.rearmy==3)
		{
			glLoadIdentity();
			glTranslatef(20,350,0);
			glPushMatrix();
			glScalef(.2,.1,.2);

			glutStrokeString("Total Armour %=");
			glutStrokeInteger(totalArmour);
		}
		//		else if (temp->id>=500&&temp->id<600)
		//			{glutStrokeString("Weapon Base Defense=");glutStrokeInteger(INFOS.armourtableid[temp->id-500][1]);}

		//draw item id area box thingomatic
	}
	if (PLAYERSTATS.skillpoints>0)
		glPushMatrix();


	if (GLOBAL.loopswitch==LS_STATS)
	{glutStrokeString("Stats. ESC/S to quit");
	if (PLAYERSTATS.skillpoints>0)
	{
		glPopMatrix();
		glTranslatef(0,-200,0);
		glPushMatrix();
		glScalef(.75,.65,.75);
		glutStrokeString("You have skill points, 'enter' to use.");
		glPopMatrix();
		glTranslatef(0,-200,0);
		glScalef(.75,.65,.75);
		glutStrokeString("SP=");
		glutStrokeInteger(PLAYERSTATS.skillpoints);
	}

	glLoadIdentity();
	glTranslatef(20,350,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	glutStrokeString("Level=");
	glutStrokeInteger(PLAYER.level);

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	glutStrokeString("Experience=");
	glutStrokeInteger(PLAYER.exp);
	glutStrokeString("/");
	glutStrokeInteger((PLAYER.level*HCVARS.PLAYEREXPPERLEVEL));

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	glColor3f(1,1,1);
	glutStrokeString("Luck=");
	glutStrokeInteger(PLAYERSTATS.luck);

	glPopMatrix();
	glTranslatef(0,-50,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==0&&PLAYERSTATS.skillpoints>0&&GLOBAL.loopswitch==LS_STATS)glColor3f(1,0,.2);
	else glColor3f(1,1,1);
	glutStrokeString("Strength=");
	glutStrokeInteger(PLAYERSTATS.strength);

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==1&&PLAYERSTATS.skillpoints>0&&GLOBAL.loopswitch==LS_STATS)glColor3f(1,0,.4);
	else glColor3f(1,1,1);
	glutStrokeString("Agility=");
	glutStrokeInteger(PLAYERSTATS.agility);

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==2&&PLAYERSTATS.skillpoints>0&&GLOBAL.loopswitch==LS_STATS)glColor3f(0,1,.5);
	else glColor3f(1,1,1);
	glutStrokeString("Dexterity=");
	glutStrokeInteger(PLAYERSTATS.dexterity);

	glPopMatrix();
	glTranslatef(0,-30,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==3&&PLAYERSTATS.skillpoints>0&&GLOBAL.loopswitch==LS_STATS)glColor3f(.5,0,1);
	else glColor3f(1,1,1);
	glutStrokeString("Intelligence=");
	glutStrokeInteger(PLAYERSTATS.intelligence);

	glPopMatrix();
	glTranslatef(0,-30,0);
	//glPushMatrix();
	glScalef(.2,.1,.2);
	if (MAPFILES.rearmy==4&&PLAYERSTATS.skillpoints>0&&GLOBAL.loopswitch==LS_STATS)glColor3f(0,1,0);
	else glColor3f(1,1,1);
	glutStrokeString("Constitution=");
	glutStrokeInteger(PLAYERSTATS.constitution);
	}

}


void deathscreen()
{
	//do death menu
	glEnable(GL_BLEND);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(5, 5);
	glVertex2f(5, 475);
	glColor3f(0.0, 1.0, 0.5);
	glVertex2f(635, 475);
	glVertex2f(635, 5);
	glEnd();

	glTranslatef(10,420,0);
	glPushMatrix();
	glScalef(.2,.1,.2);
	glColor4f(1.0, 1.0, 0.0,1);
	glutStrokeString("You Died! BL!");

	glPopMatrix();
	glTranslatef(0,-60,0);
	glScalef(.15,.15,.15);
	glColor4f(1.0, 1.0, 0.0,1);
	glutStrokeString("Press Enter to return to the Opening Screen");

}
void casinopoker()
{
	glColor4f(.3f,.6f,.7f,0.90f);	
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glColor4f(0,0,0,.9);	
	glVertex2f(490, 118);
	glVertex2f(10, 118);
	glEnd();

	glColor4f(1,1,1,.9);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(12, 470);
	glVertex2f(12, 118);
	glVertex2f(10, 118);

	glVertex2f(488, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(488, 118);

	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 468);
	glVertex2f(10, 468);

	glVertex2f(10, 118);
	glVertex2f(490, 118);
	glVertex2f(490, 116);
	glVertex2f(10, 116);

	glEnd();

	glDisable(GL_BLEND);
	glColor4f(1,1,1,1);
	glColor3f(1,1,1);

	glLoadIdentity();

	if (poker.hand.hand[0][0]!=poker.hand.hand[1][0]&&GLOBAL.loopswitch2==0)
		poker.hand.clear();

	if (GLOBAL.loopswitch2==1)
	{poker.choosecards();poker.countandsort();GLOBAL.loopswitch2=2;poker.clearcards();}

	glTranslatef(15,450,0);
	glPushMatrix();	
	glScalef(.25,.15,.25);
	glColor3f(1, 1, 0);
	glutStrokeString("Casino");
	if (GLOBAL.loopswitch2==0)
		glutStrokeString(" ESC to leave");

	if (GLOBAL.loopswitch2!=1)
	{
		glTranslatef(250,0,0);
		glutStrokeString("Bet:");
		if (poker.bet>=0)
			glutStrokeInteger(poker.bet);
		else
			glutStrokeInteger(0);
	}

	glPopMatrix();

	if (GLOBAL.loopswitch2==0)
	{
		glTranslatef(10,-30,0);
		glScalef(.15,.10,.15);
		glColor3f(1, 1, 0);
		glutStrokeString("Choose amount to bet. Max=");
		glutStrokeInteger(poker.maxbet);
	}
	else if (GLOBAL.loopswitch2==2)
	{
		glTranslatef(10,-30,0);
		glScalef(.15,.10,.15);
		glColor3f(1, 1, 0);
		glutStrokeString("What cards will you swap?");
	}

	else if (GLOBAL.loopswitch2==3)
	{
		if (poker.bet>0)
		{
			glTranslatef(10,-30,0);
			glScalef(.15,.10,.15);
			glColor3f(1, 1, 0);
			glutStrokeString("Will you play Double or Nothing?");

		}
		else
		{
			glTranslatef(10,-30,0);
			glScalef(.15,.10,.15);
			glColor3f(1, 1, 0);
			glutStrokeString("Play Poker again?");

		}


	}
	else if (GLOBAL.loopswitch2==4)
	{

		glTranslatef(10,-30,0);
		glScalef(.15,.10,.15);
		glColor3f(1, 1, 0);
		glutStrokeString("Choose what you think the next card will be");
	}
	else if (GLOBAL.loopswitch2==5)
	{
		if (poker.bet>0)
		{
			glTranslatef(10,-30,0);
			glScalef(.15,.10,.15);
			glColor3f(1, 1, 0);
			glutStrokeString("You Win! Double or Nothing Again?");

		}
		else
		{
			glTranslatef(10,-30,0);
			glScalef(.15,.10,.15);
			glColor3f(1, 1, 0);
			if (poker.bet==0)glutStrokeString("You lose. ");
			glutStrokeString("Play poker again?");
		}
	}
	glLoadIdentity();
	//0=bet 1=random cards 2=change cards 3=show cards/ what happnd 
	//4=play double, or again


	if (GLOBAL.loopswitch2==0)
	{
		glColor3f(.4,.4,.4);
		glBegin(GL_QUADS);
		glVertex2f(20, 370);
		glVertex2f(150, 370);
		glVertex2f(150, 340);
		glVertex2f(20, 340);
		glEnd();

		glTranslatef(20,340,0);
		glScalef(.15,.10,.15);
		glColor3f(1, 0, 0);
		glutStrokeString(poker.temps);
	}

	else if (GLOBAL.loopswitch2==2)
	{
		poker.drawcards();
		poker.cardcombinations();

		int xpos=330;int ypos=300;	

		if (MAPFILES.rearmy==0)glColor3f(1,0,0);
		else
			glColor3f(0,1,0);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();

		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+30,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1, 1, 0);
		glutStrokeString("OK");
		glPopMatrix();
	}

	else if (GLOBAL.loopswitch2==3)
	{
		poker.cardcombinations();
		poker.drawcards();

		if (MAPFILES.rearmx==0)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		int xpos=130;int ypos=300;
		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();


		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+30,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1, 1, 0);
		glutStrokeString("Yes");
		glPopMatrix();
		xpos=330;

		if (MAPFILES.rearmx==1)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();


		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+30,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1, 1, 0);
		glutStrokeString("No");
		glPopMatrix();
	}

	else if (GLOBAL.loopswitch2==4)
	{

		poker.drawcard(&poker.hand,0,200,300);
		int xpos=80;int ypos=150;
		if (MAPFILES.rearmx==0)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();


		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+5,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1,1,1);

		glutStrokeString("Higher");
		glPopMatrix();

		xpos+=120;

		if (MAPFILES.rearmx==1)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();

		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+5,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1,1,1);
		glutStrokeString("Same");
		glPopMatrix();

		xpos+=120;
		if (MAPFILES.rearmx==2)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();

		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+5,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1,1,1);

		glutStrokeString("Lower");
		glPopMatrix();
	}

	else if (GLOBAL.loopswitch2==5)
	{

		poker.drawcard(&poker.hand,0,200,300);
		int xpos=80;int ypos=150;
		if (MAPFILES.rearmx==0)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();


		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+5,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1,1,1);

		glutStrokeString("Yes");
		glPopMatrix();

		xpos+=120;

		if (MAPFILES.rearmx==1)glColor3f(0,1,0);
		else
			glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
		glVertex2f(xpos, ypos);
		glVertex2f(xpos+100, ypos);
		glVertex2f(xpos+100, ypos+40);
		glVertex2f(xpos, ypos+40);
		glEnd();

		glColor3f(.4,.2,0);
		glBegin(GL_QUADS);
		glVertex2f(xpos+1, ypos+1);
		glVertex2f(xpos+99, ypos+1);
		glVertex2f(xpos+99, ypos+39);
		glVertex2f(xpos+1, ypos+39);
		glEnd();

		glPushMatrix();	
		glTranslatef(xpos+5,ypos+20,0);
		glScalef(.25,.15,.25);
		glColor3f(1,1,1);
		glutStrokeString("No");
		glPopMatrix();
	}
	else
		printf("\ndis-cas");
}


void drawGUI(bool drawMapAndMinimap)
{
	glEnable(GL_BLEND);
	float bar,red,green,blue;
	red=bar=green=blue=0;
	int a=0;
	//background
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 480);
	glVertex2f(640, 480);
	glVertex2f(640, 0);
	glEnd();

	//stats box
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex2f(505, 475);
	glVertex2f(635, 475);
	glVertex2f(635, 205);
	glVertex2f(505, 205);
	glEnd();

	//stats label
	glColor3f(.4, .4, .4);
	glBegin(GL_QUADS);
	glVertex2f(510, 470);
	glVertex2f(630, 470);
	glVertex2f(630, 450);
	glVertex2f(510, 450);
	glEnd();

	//hp	
	glColor3f(.5, .5, .5);
	glBegin(GL_QUADS);
	glVertex2f(510, 440);
	glVertex2f(630, 440);
	glVertex2f(630, 410);
	glVertex2f(510, 410);
	glEnd();

	glColor3f(.6, .6, .6);
	glBegin(GL_QUADS);
	glVertex2f(515, 420);
	glVertex2f(625, 420);
	glVertex2f(625, 414);
	glVertex2f(515, 414);
	glEnd();
	//magic
	glColor3f(.5, .5, .5);
	glBegin(GL_QUADS);
	glVertex2f(510, 405);
	glVertex2f(630, 405);
	glVertex2f(630, 375);
	glVertex2f(510, 375);
	glEnd();

	glColor3f(.6, .6, .6);
	glBegin(GL_QUADS);
	glVertex2f(515, 385);
	glVertex2f(625, 385);
	glVertex2f(625, 379);
	glVertex2f(515, 379);
	glEnd();
	//air
	glColor3f(.5, .5, .5);
	glBegin(GL_QUADS);
	glVertex2f(510, 370);
	glVertex2f(630, 370);
	glVertex2f(630, 340);
	glVertex2f(510, 340);
	glEnd();

	glColor3f(.6, .6, .6);
	glBegin(GL_QUADS);
	glVertex2f(515, 349);
	glVertex2f(625, 349);
	glVertex2f(625, 344);
	glVertex2f(515, 344);
	glEnd();
	//dash bar
	if (PLAYER.dash==1)
		glColor3f(.0, .0, 1.0);
	if (PLAYER.dash==0)
		glColor3f(.5, .5, .5);

	glBegin(GL_QUADS);
	glVertex2f(510, 335);
	glVertex2f(630, 335);
	glVertex2f(630, 315);
	glVertex2f(510, 315);
	glEnd();
	//stamina
	glColor3f(.5, .5, .5);
	glBegin(GL_QUADS);
	glVertex2f(510, 310);
	glVertex2f(630, 310);
	glVertex2f(630, 280);
	glVertex2f(510, 280);
	glEnd();

	glColor3f(.6, .6, .6);
	glBegin(GL_QUADS);
	glVertex2f(515, 290);
	glVertex2f(625, 290);
	glVertex2f(625, 284);
	glVertex2f(515, 284);
	glEnd();

	//gold1
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex2f(510, 275);
	glColor3f(0,0,1);
	glVertex2f(600, 275);
	glVertex2f(600, 245);
	glColor3f(0,0,0);
	glVertex2f(510, 245);
	glEnd();

	//gold2
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(600, 275);
	glVertex2f(630, 275);
	glVertex2f(630, 245);
	glVertex2f(600, 245);
	glEnd();
	glColor3f(1, 1, 1);

	EXEC.loadTexture("Data/Images/Items/gold.tga");

	drawtile( 600, 245,600, 275,630, 275,630, 245);


	//food1
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex2f(510, 240);
	glColor3f(.5, 0, 1);
	glVertex2f(600, 240);
	glVertex2f(600, 210);
	glColor3f(0,0,0);
	glVertex2f(510, 210);
	glEnd();

	//food2
	glColor3f(.5, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(600, 240);
	glVertex2f(630, 240);
	glVertex2f(630, 210);
	glVertex2f(600, 210);
	glEnd();
	glColor3f(1, 1, 1);
	EXEC.loadTexture("Data/Images/Items/food.tga");

	drawtile(600, 210,600, 240,630, 240,630, 210);

	//console
	glColor3f(.2, .2,.2);
	glBegin(GL_QUADS);
	glVertex2f(5, 102);
	glVertex2f(495, 102);
	glVertex2f(495, 5);
	glVertex2f(5, 5);
	glEnd();

	//equipment inventory
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex2f(505, 200);
	glVertex2f(635, 200);
	glVertex2f(635, 5);
	glVertex2f(505, 5);
	glEnd();

	//inventory stripe
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glVertex2f(505, 195);
	glVertex2f(635, 195);
	glVertex2f(635, 175);
	glVertex2f(505, 175);
	glEnd();

	if (ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus]==ANIMATION.LIGHTLEVELTABLE[0])
		EXEC.loadTexture("Data/Images/Other/day.tga");
	else if (ANIMATION.LIGHTLEVELTABLE[GLOBAL.worldstatus]==ANIMATION.LIGHTLEVELTABLE[ANIMATION.LIGHTLEVELLENGTH-1])
		EXEC.loadTexture("Data/Images/Other/night.tga");
	else if (GLOBAL.nighttend==1)
		EXEC.loadTexture("Data/Images/Other/evening.tga");
	else if (GLOBAL.nighttend==0)
		EXEC.loadTexture("Data/Images/Other/morning.tga");

	glColor3f(1,1,1);

	drawtile(505, 5,505,22,522,22,522,5);

	//TOD stripe
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.4, 0.4);
	glVertex2f(522, 22);
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(635, 22);
	glVertex2f(635, 5);
	glColor3f(0.6, 0.4, 0.4);
	glVertex2f(522, 5);
	glEnd();

	//inventory
	//left

	if (EQUIPMENT.LARM.type!=T_FISTS)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(510, 133);
	glVertex2f(542, 133);
	glVertex2f(542, 101);
	glVertex2f(510, 101);
	glEnd();

	if (EQUIPMENT.RARM.type!=T_FISTS)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(598, 133);
	glVertex2f(630, 133);
	glVertex2f(630, 101);
	glVertex2f(598, 101);
	glEnd();

	glColor3f(1, 1, 1);


	EXEC.loadTexture(EQUIPMENT.LARM.path);

	drawtile(510, 101,510, 133,542, 133,542, 101);

	EXEC.loadTexture(EQUIPMENT.RARM.path);

	drawtile(598, 101,598, 133,630, 133,630, 101);

	glColor3f(0.5, 0.5, 0.5);

	//amulet possibly
	glBegin(GL_QUADS);
	glVertex2f(598, 170);
	glVertex2f(630, 170);
	glVertex2f(630, 138);
	glVertex2f(598, 138);
	glEnd();

	//head
	if (EQUIPMENT.HELM.type==T_HELMET)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(554, 170);
	glVertex2f(586, 170);
	glVertex2f(586, 138);
	glVertex2f(554, 138);

	//chest
	if (EQUIPMENT.CHEST.type==T_CHEST)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(554, 133);
	glVertex2f(586, 133);
	glVertex2f(586, 101);
	glVertex2f(554, 101);

	//legs
	if (EQUIPMENT.LEGS.type==T_LEGS)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(554, 96);
	glVertex2f(586, 96);
	glVertex2f(586, 64);
	glVertex2f(554, 64);

	//shoes
	if (EQUIPMENT.SHOES.type==T_SHOES)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(554, 59);
	glVertex2f(586, 59);
	glVertex2f(586, 27);
	glVertex2f(554, 27);
	glEnd();

	//current spell

	if (SPELL.type==T_SPELL)
		glColor3f(.3, 0.8, 0.5);
	else
		glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
	glVertex2f(510, 170);
	glVertex2f(542, 170);
	glVertex2f(542, 138);
	glVertex2f(510, 138);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);

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

	drawtile(554, 138,554, 170,586, 170,586, 138);

	if (SPELL.type==0)
	{
		glColor4f(.5,.5,.5,.5);
		EXEC.loadTexture("Data/Images/Spells/fireball.tga");
	}
	else
	{
		glColor3f(1,1,1);
		EXEC.loadTexture(SPELL.image);
	}

	drawtile(510, 138,510, 170,542, 170,542, 138);


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

	drawtile(554, 101,554, 133,586, 133,586, 101);


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

	drawtile(554, 64,554, 96,586, 96,586, 64);


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

	drawtile(554, 27,554, 59,586, 59,586, 27);

	bar=((float)PLAYER.health/(float)PLAYER.maxhealth)*10;
	if (bar>10)
	{
		bar=10;
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
		glVertex2f(515, 420);
		glVertex2f(627, 420);
		glVertex2f(627, 414);
		glVertex2f(515, 414);
		glEnd();
	}
	else
	{
		red=1;green=0;blue=0;
		for (a=0;a<bar;a++)
		{
			glColor3f(red, green, blue);
			glBegin(GL_QUADS);
			glVertex2f(515+(a*11), 420);
			glVertex2f(527+(a*11), 420);
			glVertex2f(527+(a*11), 414);
			glVertex2f(515+(a*11), 414);
			glEnd();
			red-=.1;
			green+=.1;
		}
	}

	bar=((float)PLAYER.magic/(float)PLAYER.maxmagic)*10;
	if (bar>10)
	{
		bar=10;
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
		glVertex2f(515, 385);
		glVertex2f(627, 385);
		glVertex2f(627, 379);
		glVertex2f(515, 379);
		glEnd();
	}
	else
	{
		red=0;green=0;blue=0;
		for (a=0;a<bar;a++)
		{
			glColor3f(red, green, blue);
			glBegin(GL_QUADS);
			glVertex2f(515+(a*11), 385);
			glVertex2f(527+(a*11), 385);
			glVertex2f(527+(a*11), 379);
			glVertex2f(515+(a*11), 379);
			glEnd();
			blue+=.1;
			green+=.1;
			red+=.1;
		}
	}

	bar=((float)PLAYER.air/(float)PLAYER.maxair)*10;
	if (bar>10)
	{
		bar=10;
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
		glVertex2f(515, 350);
		glVertex2f(627, 350);
		glVertex2f(627, 344);
		glVertex2f(515, 344);
		glEnd();
	}
	else
	{
		red=0;green=0;blue=1;
		for (a=0;a<bar;a++)
		{
			glColor3f(red, green, blue);
			glBegin(GL_QUADS);
			glVertex2f(515+(a*11), 350);
			glVertex2f(527+(a*11), 350);
			glVertex2f(527+(a*11), 344);
			glVertex2f(515+(a*11), 344);
			glEnd();
			green+=.1;
			blue-=.1;
		}
	}

	bar=((float)PLAYER.stamina/(float)PLAYER.maxstamina)*10;
	if (bar>10)
	{
		bar=10;
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
		glVertex2f(515, 290);
		glVertex2f(627, 290);
		glVertex2f(627, 284);
		glVertex2f(515, 284);
		glEnd();
	}
	else
	{
		red=0;green=1;blue=1;

		for (a=0;a<bar;a++)
		{
			glColor3f(red, green, blue);
			glBegin(GL_QUADS);
			glVertex2f(515+(a*11), 290);
			glVertex2f(527+(a*11), 290);
			glVertex2f(527+(a*11), 284);
			glVertex2f(515+(a*11), 284);
			glEnd();
			red+=.1;
			blue-=.1;
		}
	}

	//draw the game map and minimap
	if (drawMapAndMinimap)
	{
		EXEC.printterrain(false);
		CONSOLE.printtext();

		if (ANIMATION.minimap==true)
		{
			glLoadIdentity();
			if (GLOBAL.loopswitch==LS_NORMAL||GLOBAL.loopswitch==LS_PASS||GLOBAL.loopswitch==LS_LOOK||\
				GLOBAL.loopswitch==LS_ATTACKRS||GLOBAL.loopswitch==LS_ATTACKLS||GLOBAL.loopswitch==LS_CAST||GLOBAL.loopswitch==LS_OPENDOOR||\
				GLOBAL.loopswitch==LS_DROP||GLOBAL.loopswitch==LS_PICKUP||GLOBAL.loopswitch==LS_TALKOP||GLOBAL.loopswitch==LS_EXITMAP)
				EXEC.drawstatsmap(1);
		}

	}

	else
	{
		const float startx=ANIMATION.SCREENSTARTX;
	const float starty=ANIMATION.SCREENSTARTY;
	const float swidth=ANIMATION.SCREENWIDTH;
	const float sheight=ANIMATION.SCREENHEIGHT;

	glColor3f(0,0,0);
		glBegin(GL_QUADS);
		glVertex2f(startx,starty);
		glVertex2f(swidth+startx,starty);
		glVertex2f(swidth+startx,starty-sheight);
		glVertex2f(startx,starty-sheight);
		glEnd();

		CONSOLE.printtext();
	}
	//text

	glColor4f(1,1,1,1);
	glLoadIdentity();
	glColor3f(0,.5,1);	
	glTranslatef(530,452,0);
	glPushMatrix();
	glScalef(.25,.15,.25);
	glutStrokeString("Stats");

	glPopMatrix();
	glTranslatef(-16,-28,0);
	glPushMatrix();
	glScalef(.12,.08,.12);

	bar=((float)PLAYER.health/(float)PLAYER.maxhealth)*10;
	red=2;green=0;blue=0;
	for (a=0;a<bar;a++)
	{
		red-=0.2;
		blue+=0.05;
		green+=0.1;
	}

	glColor3f(red,green,blue);

	glutStrokeString("HP ");
	glutStrokeInteger(PLAYER.health);
	glutStrokeString("/");
	glutStrokeInteger(PLAYER.maxhealth);


	glPopMatrix();
	glTranslatef(0,-35,0);
	glPushMatrix();
	glScalef(.12,.08,.12);

	bar=((float)PLAYER.magic/(float)PLAYER.maxmagic)*10;
	red=2;green=0;blue=0;
	for (a=0;a<bar;a++)
	{
		red-=.2;
		blue+=.05;
		green+=.1;
	}
	glColor3f(red,green,blue);

	glutStrokeString("MP ");
	glutStrokeInteger(PLAYER.magic);
	glutStrokeString("/");
	glutStrokeInteger(PLAYER.maxmagic);


	glPopMatrix();
	glTranslatef(0,-35,0);
	glPushMatrix();
	glScalef(.12,.08,.12);

	bar=((float)PLAYER.air/(float)PLAYER.maxair)*10;
	red=2;green=0;blue=0;
	for (a=0;a<bar;a++)
	{
		red-=.2;
		blue+=.05;
		green+=.1;
	}
	glColor3f(red,green,blue);

	glutStrokeString("Air ");
	glutStrokeInteger(PLAYER.air);
	glutStrokeString("/");
	glutStrokeInteger(PLAYER.maxair);


	glPopMatrix();
	glTranslatef(0,-32,0);
	glPushMatrix();
	glScalef(.12,.08,.12);

	if (PLAYER.dash==1)
	{glColor3f(0,1,1);glutStrokeString("Dash is ON");}
	else
	{glColor3f(1,1,1);glutStrokeString("Dash is OFF");}


	glPopMatrix();
	glTranslatef(0,-28,0);
	glPushMatrix();
	glScalef(.12,.08,.12);

	bar=((float)PLAYER.stamina/(float)PLAYER.maxstamina)*10;
	red=2;green=0;blue=0;
	for (a=0;a<bar;a++)
	{
		red-=.2;
		blue+=.05;
		green+=.1;
	}
	glColor3f(red,green,blue);
	glutStrokeString("Stamina ");
	glutStrokeInteger(PLAYER.stamina);
	glutStrokeString("/");
	glutStrokeInteger(PLAYER.maxstamina);

	glPopMatrix();
	glTranslatef(0,-35,0);
	glPushMatrix();
	glScalef(.12,.08,.12);
	glColor3f(0,1,.5);
	glutStrokeInteger(PLAYER.gold);

	glPopMatrix();
	glTranslatef(0,-35,0);
	glPushMatrix();
	glScalef(.12,.08,.12);
	glColor3f(0,1,.5);
	glutStrokeInteger(PLAYER.food);

	glPopMatrix();
	glTranslatef(5,-43,0);
	glPushMatrix();
	glScalef(.20,.12,.20);
	glColor3f(0,.5,1);
	glutStrokeString("Inventory");

	glPopMatrix();
	glTranslatef(7,-170,0);
	//glPushMatrix();
	glScalef(.12,.08,.12);
	glColor3f(0,1,.5);
	glutStrokeString("Time of Day");

	glLoadIdentity();
}


void helpscreen()
{
	glColor4f(.3f,.6f,.7f,0.90f);	
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(5, 5);
	glVertex2f(5, 475);
	glColor4f(0,0,0,.9);	
	glVertex2f(635, 475);
	glVertex2f(635, 5);
	glEnd();

	glLoadIdentity();
	glTranslatef(15,450,0);
	glScalef(.20,.15,.20);

	glPushMatrix();
	glColor3f(1, 1, 0);
	glutStrokeString("     ESC to return to the game");

	glPopMatrix();
	glTranslatef(0,-300,0);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glutStrokeString("HELP MANUAL");

	glPopMatrix();
	glTranslatef(0,-150,0);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("f=cast-spell c=ready spell g=get");

	glPopMatrix();
	glTranslatef(0,-150,0);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("u=use items s=stat/levelup v=dash");

	glPopMatrix();
	glTranslatef(0,-150,0);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("d=drop items z=swim");

	glPopMatrix();
	glTranslatef(0,-150,0);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("o=toggle door alt+enter=fullscreen");

	glPopMatrix();
	glTranslatef(0,-150,0);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("l=look a=attack t=talk");

	glPopMatrix();
	glTranslatef(0,-150,0);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("e=enter arrows=move tab=minimap toggle");

	glPopMatrix();
	glTranslatef(0,-150,0);
	//glPushMatrix();
	glColor3f(1, 1, 1);
	glutStrokeString("numpad/directional keys=move");
}

void potionshop()
{
	glColor4f(.3f,.6f,.7f,0.90f);	
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glColor4f(0,0,0,.9);	
	glVertex2f(490, 118);
	glVertex2f(10, 118);
	glEnd();

	glColor4f(1,1,1,.9);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(12, 470);
	glVertex2f(12, 118);
	glVertex2f(10, 118);

	glVertex2f(488, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(488, 118);

	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 468);
	glVertex2f(10, 468);

	glVertex2f(10, 118);
	glVertex2f(490, 118);
	glVertex2f(490, 116);
	glVertex2f(10, 116);

	glEnd();

	glDisable(GL_BLEND);
	glColor4f(1,1,1,1);
	glColor3f(1,1,1);

	glLoadIdentity();

	glTranslatef(15,455,0);
	glPushMatrix();
	glScalef(.18,.10,.20);
	glColor4f(1,1,1,1);
	glutStrokeString("You are buying potions.");
	if (GLOBAL.loopswitch2==0)
		glutStrokeString("ESC to quit");
	else if (GLOBAL.loopswitch2==1)
		glutStrokeString("ESC to go back");

	glPopMatrix();
	glTranslatef(0,-30,0);
	glScalef(.15,.10,.20);
	if (GLOBAL.loopswitch2==0)
		glutStrokeString("-Select a potion to buy");
	else if (GLOBAL.loopswitch2==1)
		glutStrokeString("-Select an amount >0");

	glLoadIdentity();

	//number of potions in the slider
	const int potionsnum=2;

	//draw potion slider
	int current=MAPFILES.rearmx;
	int minx=0;
	int maxx=0;
	
	bool iscentre=false;
	//start
	if (current==0)
	{
		minx=0;
		maxx=potionsnum;
	}
	//middle
	else if (current>0&&current<=potionsnum)
	{
		minx=current-1;
		maxx=current+1;
		iscentre=true;
	}
	//end
	else
	{
		minx=current-potionsnum;
		maxx=current;
	}
//	printf("\nnum=%d, min=%d,max=%d",current,minx,maxx);

	int potionslider[potionsnum+1];
	for (int a=0;a<potionsnum;a++)
		potionslider[a]=-1;

	LinkedListNode<NodeObject> * temp=shoppotions.getIteration(minx);

	int thispotion=0;
	for (int c=0;c<=potionsnum;c++)
	{
		if (temp==NULL)
			break;

		potionslider[c]=temp->value->id;			
		while (potionslider[c]>=100)
			potionslider[c]-=100;
		temp=temp->nextptr;
	}

	//get current
	temp=shoppotions.getIteration(current);
	thispotion=temp->value->id;

	while (thispotion>=100)
		thispotion-=100;

	objstore * thisobj=INFOS.OBJSTOREPTR[thispotion];

	int a=0;
	if (iscentre)
		a=1;
	else
		a=current%3;


	glColor3f(1,1,1);
	glColor4f(.4,.4,.4,.4);

	glBegin(GL_QUADS);
	glVertex2f(286,450);
	glVertex2f(460,450);
	glVertex2f(460,430);
	glVertex2f(286,430);
	glEnd();

	glLoadIdentity();
	glTranslatef(286,430,0);
	glScalef(.15,.15,.15);
	glColor3f(.7,.7,1);

	glutStrokeString(thisobj->name);
	glLoadIdentity();
	int startx=286;
	int endx=324;
	int starty=342;
	int endy=382;

	//start=0,mid=1,max=2
	int c=0;
	if (current==minx)
		c=0;
	else if (current==maxx)
		c=2;
	else
		c=1;

		glColor4f(.6,.6,0,1);
		glBegin(GL_QUADS);
		glVertex2f(startx+(40*c),endy);
		glVertex2f(endx+(40*c),endy);
		glVertex2f(endx+(40*c),starty);
		glVertex2f(startx+(40*c),starty);
		glEnd();
	//draw potions 
	for (int a=0;a<=potionsnum;a++)
	{
		if (potionslider[a]!=-1)
		{
			glColor4f(1,1,1,1);
			glEnable(GL_BLEND);
			EXEC.loadTexture(INFOS.OBJSTOREPTR[potionslider[a]]->path);
			drawtile(startx+(40*a), starty,startx+(40*a), endy,endx+(40*a), endy,endx+(40*a), starty);
			glDisable(GL_BLEND);
		}		
	}

	//draw amount menu

	startx-=50;
	endx+=120;
	starty-=45;
	endy-=55;

	if (GLOBAL.loopswitch2==0)
		glColor4f(.4,.4,.4,1);
	else
		glColor4f(1,1,0,1);

	glBegin(GL_QUADS);
	glVertex2f(startx,endy);
	glVertex2f(endx,endy);
	glVertex2f(endx,starty);
	glVertex2f(startx,starty);
	glEnd();

	glLoadIdentity();
	glTranslatef(startx,starty,0);
	glPushMatrix();
	glScalef(.15,.15,.15);
	if (GLOBAL.loopswitch2==0)
		glColor3f(.7,.7,1);
	else
		glColor3f(0,0,0);
	glutStrokeString(potiontemp);

	glPopMatrix();
	glTranslatef(0,-40,0);
	glScalef(.15,.15,.15);
	glColor4f(1,1,1,1);

	char tempo[100];tempo[0]=0;
	char tempo2[100];tempo2[0]=0;

	strcpy(tempo,"Cost=");
	int cost=atoi(potiontemp);
	cost*=INFOS.OBJSTOREPTR[thispotion]->cost;
	sprintf(tempo2,"%d",cost);			
	strcat(tempo,tempo2);
	glutStrokeString(tempo);
}

void buysellbuyspell()
{
	glColor3f(1, 1, 1);
	if (GLOBAL.loopswitch==LS_BUYING||GLOBAL.loopswitch==LS_BUYSPELL)
		glColor4f(.3f,.6f,.7f,0.90f);	
	else
		glColor4f(.3f,.7f,.6f,0.90f);	

	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(10, 118);
	glEnd();

	glColor4f(1,1,1,.9);
	glBegin(GL_QUADS);
	glVertex2f(10, 470);
	glVertex2f(12, 470);
	glVertex2f(12, 118);
	glVertex2f(10, 118);

	glVertex2f(488, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 118);
	glVertex2f(488, 118);

	glVertex2f(10, 470);
	glVertex2f(490, 470);
	glVertex2f(490, 468);
	glVertex2f(10, 468);

	glVertex2f(10, 118);
	glVertex2f(490, 118);
	glVertex2f(490, 116);
	glVertex2f(10, 116);

	glEnd();

	glDisable(GL_BLEND);
	glColor3f(.5,.5,.5);
	glBegin(GL_QUADS);
	glVertex2f(285, 323);
	glVertex2f(485, 323);
	glVertex2f(485, 123);
	glVertex2f(285, 123);

	glVertex2f(15, 323);
	glVertex2f(215, 323);
	glVertex2f(215, 123);
	glVertex2f(15, 123);
	glEnd();

	glLoadIdentity();
	glTranslatef(15,450,0);
	glScalef(.20,.10,.20);
	glColor3f(0, 1, 0);
	glutStrokeString("You are");
	if (GLOBAL.loopswitch==LS_BUYING||GLOBAL.loopswitch==LS_BUYSPELL)
		glutStrokeString(" Buying");
	else
		glutStrokeString(" Selling");

	glutStrokeString(". ESC to quit");

	glLoadIdentity();
	glTranslatef(20,420,0);
	glScalef(.20,.10,.20);
	glColor3f(1, .5, 0);
	//int position=MAPFILES.rearmx;position+=MAPFILES.rearmy*5;

	NodeObject * thisitem=NULL;
	int temp=MAPFILES.rearmx;
	temp+=MAPFILES.rearmy*5;

	if (shopitems.headptr==NULL)
	{
		EXEC.initshop();
		CONSOLE.pushtext(true,0,"nullfinditem");
	}

	if (GLOBAL.loopswitch==LS_BUYING)
		thisitem=shopitems[temp];
	else if (GLOBAL.loopswitch==LS_SELLING)
		thisitem=helditems[temp];
	else
		thisitem=shopspells[temp];

	if (GLOBAL.loopswitch==LS_BUYING&&thisitem!=NULL)
	{
		NodeObject * findweapon=thisitem;

		if (isweapon(findweapon->type))
		{
			if (INFOS.WEPSTOREPTR[findweapon->id-200]->cost>PLAYER.gold)
				glColor3f(1, 0, 0);
			else
				glColor3f(0, 1, 0);
		}
		else if (isarmour(findweapon->type))
		{
			if (INFOS.ARMSTOREPTR[findweapon->id-500]->cost>PLAYER.gold)
				glColor3f(1, 0, 0);
			else
				glColor3f(0, 1, 0);
		}
		glutStrokeString("Item cost:");
		if (isweapon(findweapon->type))
		{

			int cost=INFOS.costofobject(INFOS.WEPSTOREPTR[findweapon->id-200]->cost);
			glutStrokeInteger(cost);
			glutStrokeString(" ");
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(220,300,0);
			glPushMatrix();
			glScalef(.15,.10,.15);

			int ldg=0;
			if (EQUIPMENT.LARM.id!=0)
			{
				if (INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]!=NULL)
					ldg=INFOS.WEPSTOREPTR[EQUIPMENT.LARM.id-200]->damage;
			}


			if (INFOS.WEPSTOREPTR[findweapon->id-200]->damage>ldg)
			{glColor3f(0, 1, 0);glutStrokeString(">Larm");}
			else if (INFOS.WEPSTOREPTR[findweapon->id-200]->damage<ldg)
			{glColor3f(1, 0, 0);glutStrokeString("<Larm");}
			else
			{glColor3f(1, 1, 1);glutStrokeString("=Larm");}
			glPopMatrix();
			glTranslatef(0,-50,0);
			glScalef(.15,.10,.15);

			int rdg=0;
			if (EQUIPMENT.RARM.id!=0)
			{
				if (INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]!=NULL)
					rdg=INFOS.WEPSTOREPTR[EQUIPMENT.RARM.id-200]->damage;
			}

			if (INFOS.WEPSTOREPTR[findweapon->id-200]->damage>rdg)
			{glColor3f(0, 1, 0);glutStrokeString(">Rarm");}
			else if (INFOS.WEPSTOREPTR[findweapon->id-200]->damage<rdg)
			{glColor3f(1, 0, 0);glutStrokeString("<Rarm");}
			else
			{glColor3f(1, 1, 1);glutStrokeString("=Rarm");}
			glPopMatrix();
		}
		else if (isarmour(findweapon->type))
		{
			int cost=INFOS.ARMSTOREPTR[findweapon->id-500]->cost;
			glutStrokeInteger(cost);
			glutStrokeString(" ");
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(220,300,0);
			//glPushMatrix();
			glScalef(.15,.10,.15);
			if (findweapon->type==T_HELMET)
			{
				int dp=0;
				if (EQUIPMENT.HELM.id!=0)
				{
					if (INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]!=NULL)
						dp=INFOS.ARMSTOREPTR[EQUIPMENT.HELM.id-500]->defensePercent;
				}

				if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent>dp)
				{glColor3f(0, 1, 0);glutStrokeString(">Held");}
				else if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent<dp)
				{glColor3f(1, 0, 0);glutStrokeString("<Held");}
				else
				{glColor3f(1, 1, 1);glutStrokeString("=Held");}
			}
			else if (findweapon->type==T_CHEST)
			{
				int dp=0;
				if (EQUIPMENT.CHEST.id!=0)
				{
					if (INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]!=NULL)
						dp=INFOS.ARMSTOREPTR[EQUIPMENT.CHEST.id-500]->defensePercent;
				}

				if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent>dp)
				{glColor3f(0, 1, 0);glutStrokeString(">Held");}
				else if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent<dp)
				{glColor3f(1, 0, 0);glutStrokeString("<Held");}
				else
				{glColor3f(1, 1, 1);glutStrokeString("=Held");}
			}
			else if (findweapon->type==T_LEGS)
			{
				int dp=0;
				if (EQUIPMENT.LEGS.id!=0)
				{
					if (INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]!=NULL)
						dp=INFOS.ARMSTOREPTR[EQUIPMENT.LEGS.id-500]->defensePercent;
				}

				if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent>dp)
				{glColor3f(0, 1, 0);glutStrokeString(">Held");}
				else if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent<dp)
				{glColor3f(1, 0, 0);glutStrokeString("<Held");}
				else
				{glColor3f(1, 1, 1);glutStrokeString("=Held");}
			}
			else if (findweapon->type==T_SHOES)
			{
				int dp=0;
				if (EQUIPMENT.SHOES.id!=0)
				{
					if (INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]!=NULL)
						dp=INFOS.ARMSTOREPTR[EQUIPMENT.SHOES.id-500]->defensePercent;
				}

				if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent>dp)
				{glColor3f(0, 1, 0);glutStrokeString(">Held");}
				else if (INFOS.ARMSTOREPTR[findweapon->id-500]->defensePercent<dp)
				{glColor3f(1, 0, 0);glutStrokeString("<Held");}
				else
				{glColor3f(1, 1, 1);glutStrokeString("=Held");}
			}
			glPopMatrix();			
		}
		glPopMatrix();
	}			

	else if (GLOBAL.loopswitch==LS_SELLING)
	{
		NodeObject * findweapon=thisitem;

		glColor3f(0, 1, 0);
		if (findweapon!=NULL)
		{
			if (isweapon(findweapon->type))
			{
				glutStrokeString("Item Worth:");
				int cost=INFOS.costofobject(INFOS.WEPSTOREPTR[findweapon->id-200]->cost);
				glutStrokeInteger(cost);
				glutStrokeString(" ");
			}
			else if (isarmour(findweapon->type))
			{
				glutStrokeString("Item Worth:");
				int cost=INFOS.costofobject(INFOS.WEPSTOREPTR[findweapon->id-500]->cost);
				glutStrokeInteger(cost);
				glutStrokeString(" ");
			}
		}
	}

	else if (GLOBAL.loopswitch==LS_BUYSPELL)
	{
		int cost=0;
		if (thisitem!=NULL)
			cost=INFOS.SPLSTOREPTR[thisitem->id-400]->cost;
		if (cost>PLAYER.gold)
			glColor3f(1, 0, 0);
		else glColor3f(0, 1, 0);

		glutStrokeString("Item cost:");
		glutStrokeInteger(cost);
		glutStrokeString(" ");
	}

	glLoadIdentity();
	glTranslatef(300,420,0);
	glScalef(.20,.10,.20);
	glColor3f(1, 1, 0);
	glutStrokeString("Your Gold:");
	glutStrokeInteger(PLAYER.gold); 

	glLoadIdentity();
	glTranslatef(20,400,0);
	glScalef(.20,.10,.20);
	glColor3f(1, .5, 0);
	char tempo[100];

	if (thisitem!=NULL)
	{
		if (GLOBAL.loopswitch==LS_SELLING)
		{
			strcpy(tempo,thisitem->str);
		}
		if (thisitem->questitem==0)
			glutStrokeString("Item:"); 
		else
			glutStrokeString("Quest Item, can't exchange"); 
		if (GLOBAL.loopswitch==LS_BUYING||GLOBAL.loopswitch==LS_SELLING)
		{
			//printf("\ny=%d,x=%d,%d",MAPFILES.rearmy,MAPFILES.rearmx,temptype);
			if (isweapon(thisitem->type))
			{
				if (GLOBAL.loopswitch==LS_BUYING)
					glutStrokeString(INFOS.WEPSTOREPTR[thisitem->id-200]->name);
				else {glutStrokeString(tempo);}}
			else if (isarmour(thisitem->type))
				glutStrokeString(INFOS.ARMSTOREPTR[thisitem->id-500]->name);

		}
		else if (GLOBAL.loopswitch==LS_BUYSPELL)
		{
			if (thisitem!=NULL)
				glutStrokeString(thisitem->str);
		}
	}
	tempo[0]=0;

	if (thisitem!=NULL)
	{
		char chartemp[20];chartemp[0]=0;
		//get strength of objects for comparison
		if (isweapon(thisitem->type))
		{strcpy(tempo,"Strength=");strcat(tempo,itoa(INFOS.WEPSTOREPTR[thisitem->id-200]->damage,chartemp,10));}
		else if (isarmour(thisitem->type))
		{strcpy(tempo,"Strength=");strcat(tempo,itoa(INFOS.ARMSTOREPTR[thisitem->id-500]->defensePercent,chartemp,10));}
	}

	glLoadIdentity();
	glTranslatef(20,380,0);
	glScalef(.20,.10,.20);
	glColor3f(1, .5, 0);
	glutStrokeString(tempo);




	glLoadIdentity();
	glTranslatef(285,330,0);
	glPushMatrix();
	glScalef(.25,.15,.25);
	glColor3f(0, 1, 0);
	glutStrokeString("You");

	glPopMatrix();
	glTranslatef(-265,0,0);
	//glPushMatrix();
	glScalef(.25,.15,.25);
	glutStrokeString("Shop");

	glLoadIdentity();

	int a=0,b=0,count=-1;
	if (GLOBAL.loopswitch==LS_BUYSPELL)
	{
		//put pictures of all spells up
		for (a=0;a<5;a++)
		{
			for (b=0;b<5;b++)
			{
				int temp=0;
				temp+=b;
				temp+=a*5;
				NodeObject * thisspell1=shopspells[temp];
				splstore * thisspell2=INFOS.SPLSTORE[temp];
				splstore * thisspell=NULL;

				if (thisspell1!=NULL)
				{
					int nid=thisspell1->id;
					while (nid>=100)
						nid-=100;
					thisspell=INFOS.SPLSTOREPTR[nid];
				}
				count++;
				glColor3f(0,1,0);

				glBegin(GL_QUADS);
				glVertex2f(286+(40*b), 284-(40*a));
				glVertex2f(286+(40*b), 322-(40*a));
				glVertex2f(324+(40*b), 322-(40*a));
				glVertex2f(324+(40*b), 284-(40*a));

				if (b==MAPFILES.rearmx&&a==MAPFILES.rearmy&&GLOBAL.loopswitch==LS_BUYSPELL)
					glColor3f(1,1,0);
				else
					glColor3f(0,1,0);

				glVertex2f(16+(40*b), 284-(40*a));
				glVertex2f(16+(40*b), 322-(40*a));
				glVertex2f(54+(40*b), 322-(40*a));
				glVertex2f(54+(40*b), 284-(40*a));
				glEnd();

				if (thisspell2!=NULL&&PLAYER.hasSpellTable[thisspell2->id-400]==true)
				{
					//player inv
					glColor3f(1,1,1);
					glEnable(GL_BLEND);
					EXEC.loadTexture(thisspell2->path);
					drawtile(286+(40*b), 284-(40*a),286+(40*b), 322-(40*a),324+(40*b), 322-(40*a),324+(40*b), 284-(40*a));
					glDisable(GL_BLEND);
				}

				if (thisspell!=NULL&&count<INFOS.SPLSTORE.getCount())
				{
					//store
					glColor3f(1,1,1);
					glEnable(GL_BLEND);

					EXEC.loadTexture(thisspell->path);
					drawtile(16+(40*b), 284-(40*a),16+(40*b), 322-(40*a),54+(40*b), 322-(40*a),54+(40*b), 284-(40*a));

					glDisable(GL_BLEND);
				}
			}
		}
	}

	else if (GLOBAL.loopswitch==LS_BUYING||GLOBAL.loopswitch==LS_SELLING)
	{
		LinkedListNode<NodeObject> * hip=helditems.headptr;
		LinkedListNode<NodeObject> * sip=shopitems.headptr;
		for (a=0;a<5;a++)
		{
			for (b=0;b<5;b++)
			{
				count++;
				if (b==MAPFILES.rearmx&&a==MAPFILES.rearmy&&GLOBAL.loopswitch==LS_SELLING)
					glColor3f(1,1,0);
				else
					glColor3f(0,1,0);

				glBegin(GL_QUADS);
				glVertex2f(286+(40*b), 284-(40*a));
				glVertex2f(286+(40*b), 322-(40*a));
				glVertex2f(324+(40*b), 322-(40*a));
				glVertex2f(324+(40*b), 284-(40*a));

				if (b==MAPFILES.rearmx&&a==MAPFILES.rearmy&&GLOBAL.loopswitch==LS_BUYING)glColor3f(1,1,0);
				else
					glColor3f(0,1,0);

				glVertex2f(16+(40*b), 284-(40*a));
				glVertex2f(16+(40*b), 322-(40*a));
				glVertex2f(54+(40*b), 322-(40*a));
				glVertex2f(54+(40*b), 284-(40*a));
				glEnd();

				if (count<helditems.getCount())
				{
					glColor3f(1,1,1);
					glEnable(GL_BLEND);

					EXEC.loadTexture(hip->value->pic);
					drawtile(286+(40*b), 284-(40*a),286+(40*b), 322-(40*a),324+(40*b), 322-(40*a),324+(40*b), 284-(40*a));

					glDisable(GL_BLEND);
					hip=hip->nextptr;
				}

				if (count<shopitems.getCount())
				{
					glColor3f(1,1,1);
					glEnable(GL_BLEND);

					EXEC.loadTexture(sip->value->pic);
					drawtile(16+(40*b), 284-(40*a),16+(40*b), 322-(40*a),54+(40*b), 322-(40*a),54+(40*b), 284-(40*a));

					glDisable(GL_BLEND);
					sip=sip->nextptr;
				}
			}
		}
	}
}

