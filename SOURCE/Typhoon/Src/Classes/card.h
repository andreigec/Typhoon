//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _CARD_H
#define _CARD_H

class card
{
public:
	int hand[5][2];

	int oddshand[5][3];
	//2-10,J, Q, K, A
	//2-10,11,12,13,14
	//int card[x][0]=valueofcard;

	//spade, club, diamond, heart
	//0,      1,     2,      3
	//int card[x][1]=typeofcard;

	card();
	~card();

	void clear();
};
#endif