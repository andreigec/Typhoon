//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPENEMIESLIST_CPP
#define _MAPENEMIESLIST_CPP

mapenemieslist::mapenemieslist()
{
nextptr=NULL;
prevptr=NULL;
mapenemies.clear();
}

char * mapenemieslist::saveenemy(char * objtype)
{
	char tempout[10000];tempout[0]=0;
	strcpy(tempout,objtype);	

	if (mapenemies.headptr!=NULL)
	{
		char tempz[20];tempz[0]=0;
		sprintf(tempz,"%d",mapenemies.getCount());
		strcat(tempout," ");strcat(tempout,tempz);

		LinkedListNode<NodeEnemy> * enemyz=mapenemies.headptr;
		while (enemyz!=NULL)
		{
			char * temp=enemyz->value->saveenemy("npc");
			strcat(tempout,temp);
				myfree(&temp);
			enemyz=enemyz->nextptr;
		}
	}
	char * outstr=strdup(tempout);
	return outstr;
}

void mapenemieslist::loadenemy(FILE * fileptr)
{
	int count=0;
		fscanf_s(fileptr,"%d",&count);

		for (int a=0;a<count;a++)
		{
		fscanf_s(fileptr,"%*s");
		NodeEnemy * newptr=mapenemies.insertNode();
		newptr->loadenemy(fileptr,false);
		}		
}

#endif