//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _SOUNDFILE_H
#define _SOUNDFILE_H

class SoundFile
{
public:
	void init();
	void dinit();
	SoundFile();
	~SoundFile();
	int usage;
	FMOD::Sound *soundptr;
	FMUSIC_MODULE *musicptr;
};

#endif