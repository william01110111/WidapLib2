
#pragma once

#include "ImageBase.h"
#include "Drawable.h"
#include "Error.h"
#include "Color.h"
#include "Vector.h"

namespace widap
{

class Image : public ImageBase, public Drawable
{
public:
	
	//constructors/destructor
	Image();
	Image(std::string filename) {Image(); load(filename);}
	Image(const char * filename) {Image(std::string(filename));}
	~Image();
	
	///getters and setters
	
	V2u getDim() {return dim;}
	
	
	///from ImageBase
	
	//returns true if error occurred (such as file not found)
	bool load(std::string filename);
	
	//deletes the contents of the image
	void makeEmpty();
	
	//save the image as a bitmap, returns true on error
	bool save(std::string filename);
	
	//returns if this image object is empty, or if it actually contains image data
	bool isEmpty() {return !data;}
	
	
	///from Drawable
	
	USING_DRAWABLE;
	
	//sets the value of a single pixel to the predefined drawing color
	void set(int x, int y);
	
	//set the draw color with a void pointer that is assumed to be of correct type
	void setDrawClr(void * clrIn);
	
	//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
	void setDrawClr(int clrIn);
	
	//set the draw color with a ClrRGBA pointer
	void setDrawClr(ClrRGBA * clrIn);

	//set the draw color with a ClrRGBA value
	void setDrawClr(ClrRGBA clrIn);
	
	//set the draw color with a ClrBGR pointer
	void setDrawClr(ClrBGR * clrIn);
	
	//set the draw color with a ClrBGR value
	void setDrawClr(ClrBGR clrIn);
	
	//draw a rectangle with the preset draw color
	//void rect(V2d low, V2d hgh);
	
	//draw a circle with the preset draw color
	//void circle(V2d center, double radius);
	
private:
	Clr * data; //contains a pointer to the image data, an empty image is
	V2u dim; //the dimensions of the image
	
	Clr drawClr;
	
	//used for encoding and decoding bitmaps
	void num2bytes(unsigned char *ptr, int byteNum, int num);
	int bytes2num(unsigned char *ptr, int bytesNum);
	
	Error err;
};

}

