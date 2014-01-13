//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SCRIPT_H
#define _SCRIPT_H

#define playerhascondition "playerhas"
#define mapenemyamountcondition "mapenemyamount"

class condObj
	{
	public:
		char * variableName;
		int * variable;
		int operatorValue;
		
		int value;
		condObj();
	};

class effectObj
{
public:
char * effectName;
//if true, variables are in intlist, otherwise are in charlist
bool usesInts;

LinkedList<int> intList;
LinkedList<char *> charList;

effectObj();
};

class script
{
public:
	

	LinkedList<condObj> conditions;
	LinkedList<effectObj> effects;

	//get the information about a condition or effect from a string, and add it into the linked list of the same type
	bool extractCondition(char * str);
	bool extractEffect(char * str);
	
	void init();
	void dinit();
	script();
	~script();
	
	};



#endif