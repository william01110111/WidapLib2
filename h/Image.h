
#pragma once

#include "ImageBase.h"
#include "Drawable.h"
#include "Error.h"
#include "Color.h"
#include "Vector.h"

namespace widap
{

class Image : public ImageBase
{
public:
	
	//constructors/destructor
	Image() {init();}
	Image(V2u dimIn) {init(); create(dimIn);}
	Image(std::string filename) {init(); load(filename);}
	~Image();
	
	
	///getters and setters
	
	//return the dimensions
	V2u getDim() {return dim;}
	
	//turn on and off data management for the current data
	void manageData() {managingData=1;}
	void unmanageData() {managingData=0;}
	
	//get the raw data
	Clr * getData() {return data;}
	
	//set the data, dimensions and automatically turn off data management
	void setData(Clr * dataIn, V2u dimIn);
	
	
	///from ImageBase
	
	//create a new image of the given size
	void create(V2u dimIn);
	
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
	
	//set the draw color with an bool
	void setDrawClr(bool clrIn) {setDrawClr((int)clrIn);}
	
	//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
	void setDrawClr(int clrIn);

	//set the draw color with a ClrRGBA value
	void setDrawClr(ClrRGBA clrIn);
	
	//set the draw color with a ClrBGR value
	void setDrawClr(ClrBGR clrIn);
	
	//set the draw color with a ClrBGR and an alpha value
	void setDrawClr(ClrBGR clrIn, double alpha);
	
	//draw a rectangle with the preset draw color
	//void rect(V2d low, V2d hgh);
	
	//draw a circle with the preset draw color
	//void circle(V2d center, double radius);
	
	Type getType() {return IMAGE_BGR;}
	
	//draw a drawable
	void drawable(Drawable * other, V2d pos, double alphaIn);
	
	//draw an image onto the window (is used by drawable(), so that works just as well)
	//pointer type must be to an image
	void image(Drawable * img, V2d pos, double alphaIn);
	
private:
	//this should be done by the constructor, but I was having an odd issue with constructor chaining
	void init();
	
	void textInit();
	
	bool managingData; //if the data is being controlled by this class, otherwise it will not be deleted
	Clr * data; //contains a pointer to the image data, an empty image is
	V2u dim; //the dimensions of the image
	
	Clr drawClr;
	
	//used for encoding and decoding bitmaps
	void num2bytes(unsigned char *ptr, int byteNum, int num);
	int bytes2num(unsigned char *ptr, int bytesNum);
	
	Error err;
};

}

