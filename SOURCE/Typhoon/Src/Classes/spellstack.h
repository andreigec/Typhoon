//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SPELLSTACK_H
#define _SPELLSTACK_H

class spellstack
{
public:
	spellstack * nextptr;
	spellstack * prevptr;
	
	int x;
	int y;
	splstore * SPELL;
	
	spellstack();
	~spellstack();
};

#endif