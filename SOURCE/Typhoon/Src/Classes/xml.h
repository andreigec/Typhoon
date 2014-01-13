//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _XML_H
#define _XML_H

class xml
{
public:
	xml();
	bool getfile(char * path,bool removecomments);

	//put tag in root string
	void getroot(string rootname,bool removefromfile);
	
	inline int getinteger(string tagname);
	inline bool getboolean(string tagname);
	inline void getstring(char ** variable,string tagname);
	inline string getstring(string tagname);

	string getparam(string rootname);
	char * stringtochar(string input);

	string root;

	string file;
	//using root string get tag
};

#endif