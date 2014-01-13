//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAINGAME_CPP
#define _MAINGAME_CPP

void maingame::init()
{
	maxbet=10;
	numberofgames=0;
	netearnings=0;
}

maingame::maingame()
{
	init();
}

maingame::~maingame()
{
maxbet=0;
}


void maingame::clearcards()
{
	for (int a=0;a<5;a++)
		cards[a]=false;
}

void maingame::countandsort()
{

	int a,b;
	for (a=0;a<5;a++)
		for (b=0;b<3;b++)
			hand.oddshand[a][b]=0;

	//hand.oddshand[0][0]=poker.hand.hand[0][0];
	//hand.oddshand[0][1]=poker.hand.hand[0][1];

	for (a=0;a<5;a++)
	{
		for (b=0;b<5;b++)
		{

			if (poker.hand.hand[a][0]==hand.oddshand[b][0]){hand.oddshand[b][2]++;break;}
			else if (hand.oddshand[b][0]==0)
			{hand.oddshand[b][0]=poker.hand.hand[a][0];hand.oddshand[b][1]=poker.hand.hand[a][1];hand.oddshand[b][2]=1;break;}
		}
	}
	for(a=0;a<5;a++)
	{
		if(hand.oddshand[a][0]==0)
			hand.oddshand[a][0]=666;
	}

	int holder,holder2,holder3;
	for(a=0;a<5;a++)
		for(b=0;b<4;b++)
			if(hand.oddshand[b][0] > hand.oddshand[b+1][0])
			{
				holder = hand.oddshand[b+1][0];
				holder2 = hand.oddshand[b+1][1];
				holder3 = hand.oddshand[b+1][2];
				hand.oddshand[b+1][0] = hand.oddshand[b][0];
				hand.oddshand[b+1][1] = hand.oddshand[b][1];
				hand.oddshand[b+1][2] = hand.oddshand[b][2];
				hand.oddshand[b][0]= holder;
				hand.oddshand[b][1]= holder2;
				hand.oddshand[b][2]= holder3;
			}

			for(a=0;a<5;a++)
			{
				if(hand.oddshand[a][0]==666)
					hand.oddshand[a][0]=0;
			}


}


bool maingame::is2kind()
{
	int a,b;

	for (a=0;a<5;a++)
	{
		for (b=0;b<5;b++)
		{
			if (b!=a)
			{
				if (poker.hand.hand[a][0]==poker.hand.hand[b][0])
					return true;
			}
		}
	}
	return false;
}

bool maingame::is2pair()
{
	int a,b;
	for (a=0;a<5;a++)
	{
		if (hand.oddshand[a][2]==2)
			for (b=0;b<5;b++)
			{
				if (b!=a)
				{

					if(hand.oddshand[b][2]==2)
						return true;

				}
			}
	}


	return false;
}
bool maingame::is3kind()
{
	int a=0;
	for (a=0;a<5;a++)
	{
		if (hand.oddshand[a][2]==3)
			return true;


	}


	return false;
}

bool maingame::isstraight()
{
	if (hand.oddshand[0][0]+1==hand.oddshand[1][0] && hand.oddshand[1][0]+1==hand.oddshand[2][0] && hand.oddshand[2][0]+1==hand.oddshand[3][0] && hand.oddshand[3][0]+1==hand.oddshand[4][0])
		return true;
	return false;

}
bool maingame::isflush()
{
	if (hand.oddshand[0][1]==hand.oddshand[1][1] && hand.oddshand[1][1]==hand.oddshand[2][1] && hand.oddshand[2][1]==hand.oddshand[3][1] && hand.oddshand[3][1]==hand.oddshand[4][1])
		return true;

	return false;
}
bool maingame::isfullhouse()
{

	int a,b;
	for (a=0;a<5;a++)
	{
		if (hand.oddshand[a][2]==3)
			for (b=0;b<5;b++)
			{
				if (b!=a)
				{
					if (hand.oddshand[b][2]==2)
						return true;
				}
			}
	}

	return false;
}

bool maingame::is4kind()
{
	int a;
	for (a=0;a<5;a++)
	{
		if (hand.oddshand[a][2]==4)
			return true;

	}
	return false;
}

bool maingame::isstraightflush()
{
	if ((hand.oddshand[0][0]+1==hand.oddshand[1][0] && hand.oddshand[1][0]+1==hand.oddshand[2][0] && hand.oddshand[2][0]+1==hand.oddshand[3][0] && hand.oddshand[3][0]+1==hand.oddshand[4][0])&&\
		(hand.oddshand[0][1]==hand.oddshand[1][1] && hand.oddshand[1][1]==hand.oddshand[2][1] && hand.oddshand[2][1]==hand.oddshand[3][1] && hand.oddshand[3][1]==hand.oddshand[4][1]))
		return true;
	return false;

}

bool maingame::isroyalflush()
{
	if ((hand.oddshand[0][0]==10&&hand.oddshand[1][0]==11&&hand.oddshand[2][0]==12&&hand.oddshand[3][0]==13&&hand.oddshand[4][0]==14)&&(hand.oddshand[0][1]==hand.oddshand[1][1] && hand.oddshand[1][1]==hand.oddshand[2][1] && hand.oddshand[2][1]==hand.oddshand[3][1] && hand.oddshand[3][1]==hand.oddshand[4][1]))
		return true;
	return false;
}





void maingame::insertcard(int number,int cardtype,int position)
{
	hand.hand[position][0]=2+number; 
	hand.hand[position][1]=cardtype;
	if (hand.hand[position][0]<=0||hand.hand[position][0]>14)
		printf("err");

}


void maingame::swapcards(bool cards[5])
{
	int a=0;


	while(a<5)
	{
		if (cards[a]==true)
		{
			Thedeck.typeofcard[poker.hand.hand[a][1]][poker.hand.hand[a][0]]=false;
		}
		a++;
	}

	a=0;
	while (a<5)
	{				
		if (cards[a]==true)
		{
			random =rand()%13;
			randomtype =rand()%4;

			if (Thedeck.typeofcard[randomtype][random]==false)
			{
				insertcard(random,randomtype,a);	
				Thedeck.typeofcard[randomtype][random]=true;
				a++;
			}
		}
		else
			a++;

	}


}


void maingame::choosecards()
{
	poker.hand.clear();
	poker.Thedeck.clear();
	int cardnum=0;
	while (cardnum<5)
	{

		random =rand()%13;
		randomtype =rand()%4;

		if (Thedeck.typeofcard[randomtype][random]==false)
		{
			insertcard(random,randomtype,cardnum);
			Thedeck.typeofcard[randomtype][random]=true;
			cardnum++;
		}
	}


}

void maingame::drawcard(card *hand,int number,int xpos,int ypos)
{


	glBegin(GL_LINE_LOOP);
	glVertex2d(xpos, ypos);
	glVertex2d(xpos+50, ypos);
	glVertex2d(xpos+50, ypos+80);
	glVertex2d(xpos, ypos+80);
	glEnd();


	glColor3f(.4,.2,0);
	glBegin(GL_QUADS);
	glVertex2d(xpos+1, ypos+1);
	glVertex2d(xpos+49, ypos+1);
	glVertex2d(xpos+49, ypos+79);
	glVertex2d(xpos+1, ypos+79);
	glEnd();


	glPushMatrix();
	glTranslated(xpos+15,ypos+5,0);
	glScalef(.2,.15,.2);
	glColor3f(1,1, 1);
	if (hand->hand[number][0]==0)
	{glutStrokeString("*");}
	else
	{
		if (hand->hand[number][0]<=10)
		{glutStrokeInteger(hand->hand[number][0]);}
		else if (hand->hand[number][0]==11)
		{glutStrokeString("J");}
		else if (hand->hand[number][0]==12)
		{glutStrokeString("Q");}
		else if (hand->hand[number][0]==13)
		{glutStrokeString("K");}
		else if (hand->hand[number][0]==14)
		{glutStrokeString("A");}

	}

	glPopMatrix();
	glPushMatrix();

	glTranslated(xpos+15,ypos+55,0);
	glScalef(.2,.15,.2);
	glColor3f(1,1, 1);

	if (hand->hand[number][1]==0)
	{glutStrokeString("S");}
	//{glutStrokeString("?");}
	else if (hand->hand[number][1]==1)
	{glutStrokeString("C");}
	//{glutStrokeString("?");}
	else if (hand->hand[number][1]==2)
	{glutStrokeString("D");}
	//{glutStrokeString("?");}
	else if (hand->hand[number][1]==3)
	{glutStrokeString("H");}
	//{glutStrokeString("?");}
	else
	{glutStrokeString("*");}

	glPopMatrix();
}

void maingame::changebet()
{
	if (poker.isroyalflush()==true)
	{poker.bet*=5000;}
	else if (poker.isstraightflush()==true)
	{poker.bet*=2000;}
	else if (poker.is4kind()==true)
	{poker.bet*=400;}
	else if (poker.isfullhouse()==true)
	{poker.bet*=200;}
	else if (poker.isflush()==true)
	{poker.bet*=160;}
	else if (poker.isstraight()==true)
	{poker.bet*=80;}
	else if (poker.is3kind()==true)
	{poker.bet*=20;}
	else if (poker.is2pair()==true)
	{poker.bet*=10;}
	else if (poker.is2kind()==true)
	{poker.bet*=2;}
	else
	{poker.bet=0;}


}

void maingame::cardcombinations()
{
	char output[200];
	strcpy(output,"This is a: ");
	if (poker.isroyalflush()==true)
	{strcat(output,"Royal Flush");}
	else if (poker.isstraightflush()==true)
	{strcat(output,"Straight Flush");}
	else if (poker.is4kind()==true)
	{strcat(output,"4 of a kind");}
	else if (poker.isfullhouse()==true)
	{strcat(output,"Full house");}
	else if (poker.isflush()==true)
	{strcat(output,"Flush");}
	else if (poker.isstraight()==true)
	{strcat(output,"Straight");}
	else if (poker.is3kind()==true)
	{strcat(output,"3 of a kind");}
	else if (poker.is2pair()==true)
	{strcat(output,"2 pairs");}
	else if (poker.is2kind()==true)
	{strcat(output,"pair");}
	else
	{strcat(output,"Nothing Special Hand");}

	glPushMatrix();	
	glTranslatef(20,220,0);
	glScalef(.2,.15,.2);
	glColor3f(1, 1, 0);
	glutStrokeString(output);
	glPopMatrix();
}


void maingame::drawcards()
{
	glLoadIdentity();
	int a;
	int xpos=60;
	int ypos=130;
	for (a=0;a<5;a++)
	{
		if (GLOBAL.loopswitch2!=3)
		{
			if (poker.cards[a]==true)glColor3f(1,1,0);else glColor3f(1,0,0);
			if (MAPFILES.rearmx==a&&MAPFILES.rearmy==0)
			{if (poker.cards[a]==true)glColor3f(1,0,1); else glColor3f(0,1,0);}
		}
		else
			glColor3f(1,1,1);

		drawcard(&poker.hand,a,xpos,ypos);
		xpos+=80;
	}
}

#endif