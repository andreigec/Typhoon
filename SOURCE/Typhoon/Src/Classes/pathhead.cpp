//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _PATHHEAD_CPP
#define _PATHHEAD_CPP

void pathhead::clearall()
{
	path * temp1=enemypathhead;
	path * temp2=NULL;
	while (temp1!=NULL)
	{
		temp2=temp1->nextpath;
		delete temp1;
		temp1=temp2;
	}
	enemypathhead=NULL;
	enemypathtail=NULL;
	enemypathcount=0;
}


pathhead::pathhead()
{
	enemypathcount=0;
	enemypathhead=NULL;
	enemypathtail=NULL;
}
pathhead::~pathhead()
{
	clearall();
}

path * pathhead::addpath(int x,int y)
{
	if (enemypathhead==NULL)
	{
		path * temp=new path;
		enemypathhead=temp;
		enemypathtail=temp;
		temp->x=x;
		temp->y=y;
		enemypathcount++;
		return temp;
	}
	else
	{
		path * temp=new path;
		enemypathtail->nextpath=temp;
		temp->prevpath=enemypathtail;
		enemypathtail=temp;
		temp->x=x;
		temp->y=y;
		enemypathcount++;
		return temp;
	}

}

path * pathhead::findpath(int x,int y)
{
	path* temp=enemypathhead;
	
	while (temp!=NULL)
	{
		if (temp->x==x&&temp->y==y)
			return temp;
		temp=temp->nextpath;
	}
	//printf("\nDidnt find path-%d,%d,creating",x,y);

	path * newpath =addpath(x,y);
	return newpath;
}

#endif