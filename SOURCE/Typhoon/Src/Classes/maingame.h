//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAINGAME_H
#define _MAINGAME_H

class maingame
{
public:
	card hand;
	deck Thedeck;

	int bet;
	int random;
	int randomtype;
	virtual void choosecards();
	void swapcards(bool cards[5]);
	virtual void insertcard(int number,int cardtype,int position);
	bool is2kind();
	bool is2pair();
	bool is3kind();
	bool isstraight();
	bool isflush();
	bool isfullhouse();
	bool is4kind();
	bool isstraightflush();
	bool isroyalflush();
	void countandsort();
	int maxbet;
	char temps[20];
	bool cards[5];
	void clearcards();
	void cardcombinations();
	void drawcards();
	void changebet();
	void drawcard(card *hand,int number,int xpos,int ypos);
	//stats
	int numberofgames;
	int netearnings;
	void init();
	maingame();
	~maingame();
};
maingame poker;

#endif