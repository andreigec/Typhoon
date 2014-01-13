//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _CONSOLESTUFFS_H
#define _CONSOLESTUFFS_H

class consolestuffs
{
public:
	void pushtext(bool toconsole,int mode,char * str);
	void pushconsolecurrent(char str,int area,char mode);
	void printconsole(void);
	char textarray[6][100];

	~consolestuffs();
	char consolearray[15][100];
	static const int maxstring=40;
	char currentconsole[maxstring+1];
	char prevconsole[maxstring+1];
	int currentconsolecarat;
	bool consolecheats;
	void init();
	consolestuffs();
	void loadvals(FILE * fileptr,int * current);
	char* savevals(char * objtype);
	void printtext();
};
consolestuffs CONSOLE;
#endif