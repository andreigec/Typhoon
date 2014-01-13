//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _NODEOBJET_CPP
#define _NODEOBJECT_CPP

void NodeObject::loadobject(FILE * fileptr)
{
	int nid=0;
	int namount=0;
	int x=0;
	int y=0;
	fscanf_s(fileptr,"%d %d %d %d",&namount,&nid,&x,&y);

	if (nid>=300&&nid<=399)
		setvalues(namount,nid,x,y);
	else if (nid!=0)
		setvalues(1,nid,x,y);
	else
		printf("\nWarning! ignoring 0 load object");
}


char* NodeObject::saveobject(char * objtype)
{
	char temp[100];temp[0]=0;
	sprintf(temp," %s %d %d %d %d",objtype,amount,id,xpos,ypos);
	char *out=new char[strlen(temp)+1];
	strcpy(out,temp);
	return out;
}


NodeObject::~NodeObject()
{
	dinitno();
}

void NodeObject::dinitno()
{
	
}



float NodeObject::returnbaramount()
{
	return -1;
}

void NodeObject::initno()
{

}


NodeObject::NodeObject()
{
	amount=0;
	amount2=0;
}

bool NodeObject::setvalues(int newamount,int newid,int x, int y)
{
amount=newamount;
id=newid;
xpos=x;
ypos=y;
this->questitem=false;

	//spell that has been fired
if (newid<=10)
{
	type=T_SPELL;
	mystrdup(&pic,SPELL.image);
	mystrdup(&str,SPELL.name);
}
else if (newid>=200&&newid<300)
{
	wepstore * newptr=INFOS.WEPSTOREPTR[newid-200];
	if (newptr==NULL)
	{
	printf("\nERROR, CANT FIND WEAPON %d",newid);
	return false;
	}

	if (y!=-1&&x!=-1)
	{
	if (MAPFILES.MAPFILEITEM[y][x]!=NULL)
	{printf("\nAlready an item there");return false;}
	else
		MAPFILES.MAPFILEITEM[y][x]=this;
	}
	type=newptr->type;
	mystrdup(&pic,newptr->path);
	mystrdup(&str,newptr->name);
	}

else if  (id>=300&&id<400)
{
	objstore * newptr=INFOS.OBJSTOREPTR[newid-300];
	if (newptr==NULL)
	{
	printf("\nERROR, CANT FIND OBJECT %d",newid);
	return false;
	}

	if (y!=-1&&x!=-1)
	{
	if (MAPFILES.MAPFILEITEM[y][x]!=NULL)
	{printf("\nAlready an item there");return false;}
	else
		MAPFILES.MAPFILEITEM[this->ypos][this->xpos]=this;
	}

	questitem=newptr->questitem;
	type=newptr->type;

	mystrdup(&pic,newptr->path);
	mystrdup(&str,newptr->name);
}
else if (id>=400&&id<500)
{
	splstore * newptr=INFOS.SPLSTOREPTR[id-400];
	if (newptr==NULL)
	{
	printf("\nERROR, CANT FIND SPELL OBJECT %d",id);
	return false;
	}
	
	if (y!=-1&&x!=-1)
	{
	//need to do this?
	if (MAPFILES.MAPFILEITEM[y][x]!=NULL)
	{printf("\nAlready an item there");return false;}
	else
		MAPFILES.MAPFILEITEM[this->ypos][this->xpos]=this;
	}
	
	type=newptr->type;
	mystrdup(&pic,newptr->path);
	mystrdup(&str,newptr->name);
	}
else if (id>=500&&id<599)
{
	armstore * newptr=INFOS.ARMSTOREPTR[id-500];
	if (newptr==NULL)
	{
	printf("\nERROR, CANT FIND ARMOUR OBJECT %d",id);
	return false;
	}

	if (y!=-1&&x!=-1)
	{
	if (MAPFILES.MAPFILEITEM[y][x]!=NULL)
	{printf("\nAlready an item there");return false;}
	else
		MAPFILES.MAPFILEITEM[this->ypos][this->xpos]=this;
	}

	type=newptr->type;
	mystrdup(&pic,newptr->path);
	mystrdup(&str,newptr->name);
	}
return true;	
}

#endif