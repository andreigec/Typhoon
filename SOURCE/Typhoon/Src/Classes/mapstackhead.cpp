//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _MAPSTACKHEAD_CPP
#define _MAPSTACKHEAD_CPP

void mapstackhead::loadmapSTACK(FILE * fileptr)
{
	int a=0;
	int amount=0;
	fscanf_s(fileptr,"%d",&amount);
	for (a=0;a<amount;a++)
	{
		int x=0;
		int y=0;
		int id=0;
		fscanf_s(fileptr,"%d %d %d",&x,&y,&id);
			revpush(id,x,y);
		}
}

char* mapstackhead::savemapSTACK(char * objtype)
{
	char temp[100];temp[0]=0;
	char out[500];out[0]=0;

	sprintf(temp," %s %d",objtype,stackamount);
	strcat(out,temp);

	if (MAPFILES.mapSTACK.stackamount>0)
	{

		mapstax * hax=stackhead;
		mapstax * hax2=NULL;
		while (hax!=NULL)
		{
			hax2=hax->downptr;
			sprintf(temp," %d %d %d",hax->x,hax->y,hax->id);
			strcat(out,temp);
			hax=hax2;
		}
	}

	char *out2=new char[strlen(out)+1];
	strcpy(out2,out);
	return out2;

}



void mapstackhead::initstack()
{
	mapstax * hax=stackhead;
	mapstax * hax2=NULL;
	while (hax!=NULL)
	{
		hax2=hax->downptr;
		delete hax;
		hax=hax2;
	}
	stackhead=NULL;
	stackamount=0;

}


mapstax * mapstackhead::pop()
{
	mapstax * newptr=stackhead;
	stackamount--;

	if (stackhead->downptr==NULL)
	{
		stackhead=NULL;
		return newptr;
	}
	else
	{
		stackhead->downptr->upptr=NULL;
		stackhead=stackhead->downptr;
		return newptr;
	}
}

mapstackhead::mapstackhead()
{
	stackamount=0;
	stackhead=NULL;
}

mapstax * mapstackhead::push(int id,int xx, int yy)
{
	stackamount++;
	mapstax * newptr= new mapstax;
	newptr->id=id;
	newptr->x=xx;
	newptr->y=yy;

	if (stackhead==NULL)
	{stackhead=newptr;}
	else
	{
		stackhead->upptr=newptr;
		newptr->downptr=stackhead;
		stackhead=newptr;
	}
	return newptr;
}


mapstax * mapstackhead::revpush(int id,int xx, int yy)
{
	stackamount++;
	mapstax * newptr= new mapstax;
	newptr->id=id;
	newptr->x=xx;
	newptr->y=yy;
	if (stackhead==NULL)
	{stackhead=newptr;}
	else
	{
		mapstax * hax=stackhead;
		while (hax->downptr!=NULL)
		{
			hax=hax->downptr;
		}
		hax->downptr=newptr;
		newptr->upptr=hax;
	}
	return newptr;
}

#endif