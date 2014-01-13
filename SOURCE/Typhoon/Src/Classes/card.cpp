//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _CARD_CPP
#define _CARD_CPP

card::card()
{
	int a,b;
	for (a=0;a<5;a++)
	{
		for (b=0;b<3;b++)
		{
			oddshand[5][3]=0;
			hand[a][b]=0;
		}
	}
}

card::~card()
{
hand[0][0]=0;
}

void card::clear()
{
	int a,b;
	for (a=0;a<5;a++)
	{
		for (b=0;b<3;b++)
		{
			oddshand[5][3]=0;
			hand[a][b]=0;
		}
	}
}
#endif