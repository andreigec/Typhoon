//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _CONTROL_CPP
#define _CONTROL_CPP

template <class T>
void dropitemhead(LinkedList<T> * listptr,int y,int x)
{
	if (x<0||x>=MAPFILES.emapwidth()||y<0||y>=MAPFILES.emapheight())
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_NOROOM);
		GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;
	}

	if (MAPFILES.MAPFILEITEM[PLAYER.posy][PLAYER.posx]!=NULL)
	{CONSOLE.pushtext(false,0,TEXT_ITEM_GROUND);GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;}

	int temp=0;
	char tmp[100];tmp[0]=0;
	temp+=x;
	temp+=y*5;
	LinkedListNode<NodeObject> * newptr=listptr->getIteration(temp);
	if (newptr==NULL)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_DROP);
		GLOBAL.loopswitch=LS_NORMAL;
		glutPostRedisplay();
		return;
	}

	if (newptr->value->questitem==1)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_QUEST);
		GLOBAL.loopswitch=LS_NORMAL;
		glutPostRedisplay();
		return;
	}
	//printf("same");

	grounditems.insertNode()->setvalues(1,newptr->value->id,PLAYER.posx,PLAYER.posy);
	GLOBAL.loopswitch=LS_NORMAL;
	//playsound
	EXEC.loadSound(SND.dropsound);
	strcpy(tmp,"You dropped a ");
	if (isweapon(newptr->value->type))
		strcat(tmp,INFOS.WEPSTOREPTR[newptr->value->id-200]->name);
	else if (isarmour(newptr->value->type))
		strcat(tmp,INFOS.ARMSTOREPTR[newptr->value->id-500]->name);
	else
		strcat(tmp,newptr->value->str);

	CONSOLE.pushtext(false,3,tmp);

	helditems.deleteNode(newptr);
	glutPostRedisplay();
	return;
}

template <class T>
void buyitemhead(LinkedList<T> * listptr,int y,int x)
{
	if (helditems.getCount()>=HCVARS.MAXINVENTORYITEMS)
	{CONSOLE.pushtext(false,0,TEXT_INV_FULL);GLOBAL.loopswitch=LS_NORMAL;glutPostRedisplay();return;}

	int temp=0;
	temp+=x;
	temp+=y*5;
	LinkedListNode<NodeObject> * newptr=listptr->getIteration(temp);

	if (newptr==NULL)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_BUY);
		GLOBAL.loopswitch=LS_NORMAL;
		glutPostRedisplay();
		return;
	}

	int cost=0;
	if (isweapon(newptr->value->type))
		cost=INFOS.WEPSTOREPTR[newptr->value->id-200]->cost;
	else if (isarmour(newptr->value->type))
		cost=INFOS.ARMSTOREPTR[newptr->value->id-500]->cost;
	cost-=PLAYERSTATS.luck;
	if (cost<=10)
		cost=20;
	char tempp[20];char tmp[100];
	//GLOBAL.loopswitch=LS_NORMAL;
	if (PLAYER.gold<cost)
	{CONSOLE.pushtext(false,0,TEXT_ITEM_AFFORD);glutPostRedisplay();return;}
	else
		PLAYER.gold-=cost;
	//playsound
	EXEC.loadSound(SND.buysound);

	strcpy(tmp,"You bought a ");
	if (isweapon(newptr->value->type))
		strcat(tmp,INFOS.WEPSTOREPTR[newptr->value->id-200]->name);
	else if (isarmour(newptr->value->type))
		strcat(tmp,INFOS.ARMSTOREPTR[newptr->value->id-500]->name);

	strcat(tmp," for");
	sprintf(tempp," %d",cost);
	strcat(tmp,tempp);
	CONSOLE.pushtext(false,3,tmp);
	helditems.insertNode()->setvalues(1,newptr->value->id,-1,-1);
	//deleteNode(&shopitems,count-1); 
	glutPostRedisplay();
	return;
}


template <class T>
void sellitemhead(LinkedList<T> * listptr,int y,int x)
{
	int temp=0;
	temp+=x;
	temp+=y*5;

	LinkedListNode<NodeObject> * newptr=listptr->getIteration(temp);

	if (newptr==NULL)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_SELL);
		glutPostRedisplay();
		return;
	}
	if (newptr->value->questitem==1)
	{
		CONSOLE.pushtext(false,0,TEXT_ITEM_QUEST);
		glutPostRedisplay();
		return;
	}
	////printf("same");
	int cost=0;
	if (isweapon(newptr->value->type))
		cost=INFOS.WEPSTOREPTR[newptr->value->id-200]->cost;

	else if (isarmour(newptr->value->type))
		cost=INFOS.ARMSTOREPTR[newptr->value->id-500]->cost;
	cost/=2;
	cost+=PLAYERSTATS.luck;
	char tempp[20];char tmp[100];
	if (isweapon(newptr->value->type))
	{
		if (cost>((float)INFOS.WEPSTOREPTR[newptr->value->id-200]->cost/.75))
			cost=(float)INFOS.WEPSTOREPTR[newptr->value->id-200]->cost/.75;
	}
	//GLOBAL.loopswitch=LS_NORMAL;

	//playsound
	EXEC.loadSound(SND.buysound);
	strcpy(tmp,"You sold a ");
	if (isweapon(newptr->value->type))
		strcat(tmp,INFOS.WEPSTOREPTR[newptr->value->id-200]->name);
	else if (isarmour(newptr->value->type))
		strcat(tmp,INFOS.ARMSTOREPTR[newptr->value->id-500]->name);
	strcat(tmp," for");
	sprintf(tempp," %d",cost);
	strcat(tmp,tempp);
	CONSOLE.pushtext(false,3,tmp);
	listptr->deleteNode(newptr);
	if (PLAYER.gold<PLAYER.maxgold)PLAYER.gold+=cost;

	glutPostRedisplay();
	return;
}


inline void glutStrokeString(char *string)
{
	int length=(signed)strlen(string);
	for (int a=0;a<length;a++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,string[a]);
}

//prints out integers	
inline void glutStrokeInteger(int temp)
{
	char string[20];string[0]=0;
	sprintf(string,"%d", temp);glutStrokeString(string);
}

#endif