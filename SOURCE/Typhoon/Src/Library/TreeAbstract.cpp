//Coded by Andrei Gec 2008
#ifndef _Tree_CPP
#define _Tree_CPP

template <class T,class Y>
void TreeAbstract<T,Y>::clear()
{
Y * newptr=getfirstnode();
Y * nextptr=NULL;

while (newptr!=NULL)
{
	nextptr=newptr->nextInOrder();
	deleteNode(newptr->key);

newptr=nextptr;
}
}

template <class T,class Y>
bool TreeAbstract<T,Y>::deleteNode(const char * key)
{
	return deleteNode(searchNode(key));
}


template <class T,class Y>
bool TreeAbstract<T,Y>::deleteNode(Y * deletethis)
{
	if (deletethis==NULL)
		return false;
	
	Y * successor=NULL;

	//decrease number of node count
	count--;
	
	//no children
	if (deletethis->leftptr==NULL&&deletethis->rightptr==NULL)
	{
		//is root
		if (deletethis->headptr==NULL)
		{
			rootnode=NULL;
				delete deletethis;
		}
		else
		{
			Y * balptr=deletethis->headptr;
			balptr->setchildkey(deletethis->key,NULL);
				delete deletethis;
		}
	}
	//1 child
	else if ((deletethis->leftptr==NULL&&deletethis->rightptr!=NULL)||(deletethis->rightptr==NULL&&deletethis->leftptr!=NULL))
	{
		successor=NULL;
		if (deletethis->rightptr!=NULL)
			successor=deletethis->rightptr;
		else
			successor=deletethis->leftptr;

		Y * balptr=successor;
		while (balptr->leftptr!=NULL||balptr->rightptr!=NULL)
		{
			if (balptr->leftptr!=NULL)
				balptr=balptr->leftptr;
			else
				balptr=balptr->rightptr;
		}

		//is root
		if (deletethis->headptr==NULL)
		{
			rootnode=successor;
			successor->headptr=NULL;
		}
		else
		{
			deletethis->headptr->setchildkey(deletethis->key,successor);
			successor->headptr=deletethis->headptr;
		}
			delete deletethis;

	}
	//2 children :(
	else
	{
		//either inorder right or left
		Y * bptr=NULL;

		if (deletethis->rightptr->leftptr!=NULL)
		{
			successor=deletethis->rightptr->leftptr;
			while (successor->leftptr!=NULL)
			{
				successor=successor->leftptr;
			}
			bptr=successor->headptr;			
		}
		else if (deletethis->leftptr->rightptr!=NULL)
		{
			successor=deletethis->leftptr->rightptr;
			while (successor->rightptr!=NULL)
			{
				successor=successor->rightptr;
			}
			bptr=successor->headptr;			
		}

		else
		{
			successor=deletethis->leftptr;
		}

		//move sucessor
		if (deletethis->headptr==NULL)
			rootnode=successor;
		else
		{
			deletethis->headptr->setchildkey(deletethis->key,successor);
		}

		if (deletethis->leftptr!=NULL)
			deletethis->leftptr->headptr=successor;
		if (deletethis->rightptr!=NULL)
			deletethis->rightptr->headptr=successor;

		successor->leftptr=deletethis->leftptr;
		successor->rightptr=deletethis->rightptr;
		successor->headptr=deletethis->headptr;

			delete deletethis;
		
	}
return true;
}



template <class T,class Y>
Y* TreeAbstract<T,Y>::searchNode(const char * searchKey)
{
	Y *newptr=rootnode;
	while (newptr!=NULL)
	{
		int type=strcmp(searchKey,newptr->key);

		if (type==0)
			return newptr;
		else if (type<0)
			newptr=newptr->leftptr;
		else if (type>0)
			newptr=newptr->rightptr;
	}
	return NULL;
}


template <class T,class Y>
T* TreeAbstract<T,Y>::insertNode(const char * insertKey)
{
	if (insertKey==NULL)
		return NULL;
	if (searchNode(insertKey)!=NULL)
	{
	if (debugmode)
		printf("\nTree Error:insert node, node with supplied key already exists");
	return NULL;
	}
	
	Y * newnode=new Y;
	Y * newptr=rootnode;
	//increase count
	count++;

	if (newptr==NULL)
		rootnode=newnode;
	else
	{
		while (newptr!=NULL)
		{
			int type=strcmp(insertKey,newptr->key);
			if (type<0)
			{
				//continue traversing
				if (newptr->leftptr!=NULL)
					newptr=newptr->leftptr;
				else
				{
					newptr->leftptr=newnode;
					newnode->headptr=newptr;
					newptr=NULL;
				}	
			}
			else if (type>0)
			{
				if (newptr->rightptr!=NULL)
					newptr=newptr->rightptr;
				else
				{
					newptr->rightptr=newnode;
					newnode->headptr=newptr;
					newptr=NULL;
				}
			}
		}
	}

	T * newptr2=new T;
	newnode->value=newptr2;
	newnode->key=new char[strlen(insertKey)+1];
	strcpy(newnode->key,insertKey);

	return newnode->value;
}


template <class T,class Y>
T* TreeAbstract<T,Y>::operator[](const char *searchKey)
{
	if (searchKey==NULL)
		return NULL;
	Y * newptr=searchNode(searchKey);
	if (newptr!=NULL)
		return newptr->value;
	else
		return NULL;
}



template <class T,class Y>
TreeAbstract<T,Y>::TreeAbstract()
{
	debugmode=false;
	rootnode=NULL;
	count=0;
}

template <class T,class Y>
TreeAbstract<T,Y>::~TreeAbstract()
{
	clear();
}

template <class T,class Y>
Y *TreeAbstract<T,Y>::getfirstnode()
{
	Y * newptr=rootnode;
	if (newptr==NULL)
		return NULL;

	while (newptr->leftptr!=NULL)
		newptr=newptr->leftptr;
	return newptr;
}

template <class T,class Y>
Y *TreeAbstract<T,Y>::getlastnode()
{
	Y * newptr=rootnode;
	if (newptr==NULL)
		return NULL;

	while (newptr->rightptr!=NULL)
		newptr=newptr->rightptr;
	return newptr;
}



#endif