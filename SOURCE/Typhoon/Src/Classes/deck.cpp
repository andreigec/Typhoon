//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _DECK_CPP
#define _DECK_CPP

deck::deck()
{
	int a,b;
	for (a=0;a<4;a++)
	{
		for (b=0;b<13;b++)
		{
			typeofcard[a][b]=false;
		}
	}
}

deck::~deck()
{
typeofcard[0][0]=0;
}

void deck::clear()
{
	int a,b;
	for (a=0;a<4;a++)
	{
		for (b=0;b<13;b++)
		{
			typeofcard[a][b]=false;
		}
	}
}
#endif