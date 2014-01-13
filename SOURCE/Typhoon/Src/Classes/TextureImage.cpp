//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _TEXTUREIMAGE_CPP
#define _TEXTUREIMAGE_CPP

void TextureImage::init()
{
	imageData=NULL;
	usage=0;
}

void TextureImage::dinit()
{
	if (imageData!=NULL)
		delete[] imageData;
	//myfree(imageData);
	imageData=NULL;
}

TextureImage::~TextureImage()
{
	dinit();
}

TextureImage::TextureImage()
{
	init();
}

#endif