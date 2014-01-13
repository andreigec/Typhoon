//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SOUNDFILE_CPP
#define _SOUNDFILE_CPP

void SoundFile::init()
{
	soundptr=NULL;
	usage=0;
	musicptr=NULL;
}
void SoundFile::dinit()
{
	if (soundptr!=NULL)
	{
		soundptr->release();
		soundptr=NULL;
	}

	if (musicptr!=NULL)
	{
		musicptr->release();
		musicptr=NULL;
	}

}

SoundFile::SoundFile()
{
	init();

}

SoundFile::~SoundFile()
{
	dinit();
}

#endif