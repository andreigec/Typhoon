//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SCRIPT_CPP
#define _SCRIPT_CPP

condObj::condObj()
{
	variable=NULL;
	operatorValue=0;
	value=0;
	variableName=NULL;
}

effectObj::effectObj()
{
	effectName=NULL;
	intList.clear();
	charList.clear();
	usesInts=true;
}

bool script::extractCondition(char *str)
{
	if (str==NULL)
		return false;

	const int MAXCOND=102;
	char cond[MAXCOND];
	strcpy(cond,"");
	int condint=0;
	int length=strlen(str);
	if (length==0)
		return false;

	//variable
	int pos=0;

	while (pos<length)
	{
		//make sure isnt overflowing
		if (condint>=MAXCOND)
			return false;
		//add to condition
		if (str[pos]!=' '&&str[pos]!='	')
		{
			cond[condint]=str[pos];
			cond[condint+1]=0;

			condint++;
		}
		// if white space and condition length isnt blank, have finished condition
		else if (condint!=0)
			break;

		pos++;
	}
	//if condition is empty - error
	if (condint==0)
		return false;

	bool ishardcoded=false;
	if (strcmp(cond,playerhascondition)==0||strcmp(cond,mapenemyamountcondition)==0)
	{
		ishardcoded=true;
	}

	//sign
		const int MAXSIGN=4;
		char sign[MAXSIGN];strcpy(sign,"");
		int signint=0;

	if (ishardcoded==false)
	{
		//hard code in < > != = <= >=
		while (pos<length)
		{
			//make sure isnt overflowing
			if (signint>=MAXSIGN)
				return false;

			if (str[pos]!=' '&&str[pos]!='	')
			{
				sign[signint]=str[pos];
				sign[signint+1]=0;

				signint++;
			}
			// if white space and condition length isnt blank, have finished condition
			else if (signint!=0)
				break;

			pos++;
		}
	}

	//value
	const int MAXVAL=4;
	char value[MAXVAL];strcpy(value,"");
	int valueint=0;

	//hard code in < > != = <= >=
	while (pos<length)
	{
		//make sure isnt overflowing
		if (valueint>=MAXVAL)
			return false;

		if (str[pos]!=' '&&str[pos]!='	')
		{
			value[valueint]=str[pos];
			value[valueint+1]=0;

			valueint++;
		}
		// if white space and condition length isnt blank, have finished condition
		else if (valueint!=0)
			break;

		pos++;
	}

	//add into variable
	condObj * newcondition= conditions.insertNode();


	//hard code playerhas,mapenemyamount
	//if a hard coded condition, no sign, only a variable
	if (ishardcoded)
	{
	}
	//otherwise its a variable, check
	else if (variablePointers[cond]==NULL)
	{
		conditions.deleteNode(conditions.tailptr);
		printf("\nSCRIPT ERROR - condition variable does not exist - %s",cond);
		return false;
	}
	else
	{
		newcondition->variable=(int*)variablePointers[cond]->ptr;
	}

	newcondition->variableName=strdup(cond);

	if (ishardcoded==false)
	{
		//sign
		if (strcmp(sign,"<")==0)
		{
			newcondition->operatorValue=OP_LESSTHAN; 
		}
		else if (strcmp(sign,">")==0)
		{
			newcondition->operatorValue=OP_GREATERTHAN;
		}
		else if (strcmp(sign,"<=")==0)
		{
			newcondition->operatorValue=OP_LESSEQUALTHAN;
		}
		else if (strcmp(sign,">=")==0)
		{
			newcondition->operatorValue=OP_GREATEREQUALSTHAN;
		}
		else if (strcmp(sign,"=")==0)
		{
			newcondition->operatorValue=OP_EQUALS;
		}
		else if (strcmp(sign,"!=")==0)
		{
			newcondition->operatorValue=OP_NOTEQUALS;
		}
	}

	//value
	newcondition->value=atoi(value);

	return true;
}


bool script::extractEffect(char *str)
{
	if (str==NULL)
		return false;

	const int MAXEFFECT=102;
	char effectname[MAXEFFECT];
	strcpy(effectname,"");
	int effectint=0;
	int length=strlen(str);
	if (length==0)
		return false;

	int pos=0;


	while (pos<length)
	{
		//make sure isnt overflowing
		if (effectint>=MAXEFFECT)
			return false;
		//add to condition
		if (str[pos]!=' '&&str[pos]!='	')
		{
			effectname[effectint]=str[pos];
			effectname[effectint+1]=0;

			effectint++;
		}
		// if white space and condition length isnt blank, have finished condition
		else if (effectint!=0)
			break;

		pos++;
	}
	//if condition is empty - error
	if (effectint==0)
		return false;

	//init linked list for effect
	effectObj * neweffect = effects.insertNode();
	neweffect->effectName=strdup(effectname);

	//get the rest of the variables
	//if -1, set to 0 for string and 1 for ints
	//if the value is set for a string, but an int comes up, its an error
	//-each script command can only take a list of strings, or a list of ints, no mixing
	int areInts=-1;

	const int MAXVAL=102;
	char value[MAXVAL];strcpy(value,"");
	int valueint=0;

	//hard code in < > != = <= >=
	while (pos<length||valueint!=0)
	{
		//make sure isnt overflowing
		if (valueint>=MAXVAL)
			return false;

		if (str[pos]!=' '&&str[pos]!='	'&&pos<length)
		{
			//set type of variables
			if (areInts==-1)
			{
				if (str[pos]>='0'&&str[pos]<='9')
				{
					areInts=1;
					neweffect->usesInts=true;
				}
				else
				{
					areInts=0;
					neweffect->usesInts=false;
				}

			}

			else if (areInts==0&&str[pos]>='0'&&str[pos]<='9')
			{
				printf("\nError - int script cannot mix with string");
				return false;
			}

			else if (areInts==1&&(str[pos]<'0'||str[pos]>'9'))
			{
				printf("\nError - string script cannot mix with ints");
				return false;
			}

			value[valueint]=str[pos];
			value[valueint+1]=0;
			valueint++;
		}
		//white space - add to linked list
		else if (valueint!=0)
		{
			if (areInts==1)
			{
				int val=atoi(value);
				strcpy(value,"");
				valueint=0;

				int * valptr=neweffect->intList.insertNode();
				*valptr=val;
			}
			else
			{
				char **temp=neweffect->charList.insertNode();
				*temp = strdup(value);

				int a=0;
				a=0;
			}
		}
		pos++;
	}

	return false;
}


void script::init()
{
	if (conditions.getCount()!=0||effects.getCount()!=0)
		dinit();
}

void script::dinit()
{
	conditions.clear();
	effects.clear();
}

script::~script()
{
	dinit();
}

script::script()
{

	init();
}





#endif