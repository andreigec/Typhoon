//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NODEBASE_CPP
#define _NODEBASE_CPP

void NodeBase::dinitnb()
{
	if (id<0)
		return;

		myfree(&str);
		myfree(&pic);
	
}
NodeBase::~NodeBase()
{
	dinitnb();
}

void NodeBase::initnb()
{
	id=0;
	xpos=0;
	ypos=0;
	str=0;
	pic=0;
	type=0;
}

NodeBase::NodeBase()
{
	initnb();
}

#endif