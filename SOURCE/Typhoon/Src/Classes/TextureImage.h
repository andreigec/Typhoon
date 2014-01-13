//This Document, Typhoon, and all related Miscellany copyright Andrei Gec. 
#ifndef _TEXTUREIMAGE_H
#define _TEXTUREIMAGE_H

class TextureImage
{
public:
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	void init();
	void dinit();
	TextureImage();
	~TextureImage();
	int usage;
};
#endif