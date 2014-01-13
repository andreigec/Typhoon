//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _XML_CPP
#define _XML_CPP

xml::xml()
{
	root="";
	file="";
}

inline void xml::getstring(char ** variable,string tagname)
{
	string current=getparam(tagname);
	mystrdup(variable,current.c_str());
}

inline string xml::getstring(string tagname)
{
	return getparam(tagname);
}

int xml::getinteger(string tagname)
{
	string current=getparam(tagname);
	return atoi(current.c_str());
}

bool xml::getboolean(string tagname)
{
		string current=getparam(tagname);
	if (strcmp(current.c_str(),"true")==0)
		return true;
	else 
		return false;
}


bool xml::getfile(char * path,bool removecomments)
{
	root="";
	file="";
	ifstream filep(path);

	if (filep.is_open()==false)
	{
		if (GLOBAL.debugenabled)
			printf("\nWARNING! file %s couldn't be opened",path);
		return false;
	}

	string line;
	while (!filep.eof())
	{
		getline(filep,line);
		file+=line;
	}
	filep.close();

	int start=0;
	int end=0;

	if (removecomments==true)
	{
		start=0;
		end=0;

		start=(int)file.find("<!--");
		end=(int)file.find("-->",start);

		if (start>end||start>(int)file.length())
		{
			printf("\nXML script-%s is malformed,comment ends before it starts",path);
			file="";return false;
		}

		if (start!=-1&&end!=-1)
		{
			do
			{
				file.erase(start,(end-start)+3);
				start=(int)file.find("<!--");
				end=(int)file.find("-->",start);

			}while(start!=-1&&end!=-1);

			if ((start==-1&&end!=-1)||(start!=-1&&end==-1)||(start>end))
			{
				printf("\nXML script-%s is malformed,comment ends before it starts",path);
				file="";return false;
			}
		}

		//comments end block
	}

	//remove everything outside of TML tags
	start=-1;
	end=-1;
	start=(int)file.find("<TML>");
	end=(int)file.find("</TML>",start);
	if (end==-1||start>end||start>(int)file.length())
	{
		printf("\nXML script-%s is malformed,TML block may not close",path);
		file="";
		return false;
	}

	file.erase(end+6,file.length());
	file.erase(0,start);
	return true;
}

void xml::getroot(string rootname,bool removefromfile)
{
	string outstr="";
	//<start>  </end>
	int starttaglength=(int)rootname.length()+2;
	int endtaglength=(int)rootname.length()+3;

	int start=-1;
	int end=-1;
	start=(int)file.find("<"+rootname+">");
	end=(int)file.find("</"+rootname+">",start);
	int length=(end)-(start+starttaglength);
	if (start==-1||start>(int)file.length())
	{root="";return;}
	outstr=file.substr(start+starttaglength,length);
	root=outstr;
	if (removefromfile)
		file.erase(start,(end-start)+endtaglength);
}

string xml::getparam(string paramname)
{
	int start=-1;
	int end=-1;
	int starttaglength=(int)paramname.length()+2;
	start=(int)root.find("<"+paramname+">");
	end=(int)root.find("</"+paramname+">",start);
	int length=(end)-(start+starttaglength);
	if (start==-1||start>(int)root.length())
		return "";
	string outstr="";
	outstr=root.substr(start+starttaglength,length);

	int endstart=(int)outstr.find("\"");
	int endend=(int)outstr.find("\"",endstart+1);
	int endlength=endend-(endstart+1);
	
	if (endstart==-1||endstart>(int)outstr.length())
		return "";

	//delete found from root
	int totalstart=start;
	int totalend=((end+starttaglength+1)-start);

	string root2=root.substr(totalstart,totalend);
	root.erase(totalstart,totalend);
	//root=root2;

	return outstr.substr(endstart+1,endlength);	
}

char * xml::stringtochar(string instr)
{
	char * outstr=new char[instr.length()+1];
	outstr[instr.length()]=0;
	for (int a=0;a<(int)instr.length();a++)
	{
		outstr[a]=instr[a];
	}
	return outstr;
}


#endif