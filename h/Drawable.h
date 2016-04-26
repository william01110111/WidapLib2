#include "Vector.h"
#include "Color.h"

#include <string>
using std::string;

///this declares the Drawable superclass that you can draw to

#pragma once

namespace widap
{

class Drawable
{
	//put USING_DRAWABLE somewhere in the header of subclasses to get access to all the functions
	//any function that is overloaded with some versions virtual and others not must go here
	
	#define USING_DRAWABLE			\
		using Drawable::set;		\
		using Drawable::setDrawClr;	\
		using Drawable::clear;		\
		using Drawable::rect;		\
		using Drawable::circle;		\
		using Drawable::line;		\
		
	
public:
	
	Drawable();
	
	///virtual functions
	
	//sets the value of a single pixel to the predefined drawing color
	//does not use V2i for speed reasons, but there is a V2i rapper
	virtual void set(int x, int y)=0;
	
	virtual V2u getDim()=0;
	
	//you only have to implement the setDrawClr funcs you want, if you try to use one you don't implement a runtime error will be called
	
	//set the draw color with a void pointer that is assumed to be of correct type for whatever this image is
	virtual void setDrawClr(void * clrIn);
	
	//set the draw color with an bool (black or white for color image
	virtual void setDrawClr(bool clrIn);
	
	//set the draw color with a char
	virtual void setDrawClr(char clrIn);
	
	//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
	virtual void setDrawClr(int clrIn);
	
	//set the draw color with a ClrBGR, the most common way to draw
	virtual void setDrawClr(ClrBGR clrIn);
	
	//set the draw color with a ClrRGBA, the most common way to draw
	virtual void setDrawClr(ClrRGBA clrIn);
	
	//set the draw color with a ClrHSL, the most common way to draw
	virtual void setDrawClr(ClrHSL clrIn);
	
	
	///shape virtual functions
	//these have implementation that use set() but you may want to implement them differently for faster speed
	
	//fills the Drawable with the predefined color
	virtual void clear();
	
	//draw a rectangle with the preset draw color
	virtual void rect(V2d low, V2d hgh);
	
	//draw a circle with the preset draw color
	virtual void circle(V2d center, double radius);
	
	//draw a line
	virtual void line(V2d start, V2d end);
	
	//draw text
	//virtual void text(string str, V2d pos, )
	
	
	///mscl
	
	//sets the given pixel to the predefined color, probably better to use set(int, int) for speed ans this is just a rapper
	void set(V2i loc);
	
	//sets the draw color and the alpha
	template<typename T>
	void setDrawClr(T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
	}
	
	//just sets the alpha for drawing
	void setDrawAlpha(double alphaIn);
	
	//sets the thickness of lines drawn
	void setDrawThick(double alphaIn);
	
	///shapes:
	
	//clear
	
	template<typename T>
	void clear(T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		clear();
	}
	
	template<typename T>
	void clear(T clrIn)
	{
		setDrawClr(clrIn);
		drawAlpha=1;
		clear();
	}
	
	//rect
	
	template<typename T>
	void rect(V2d low, V2d hgh, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		rect(low, hgh);
	}
	
	template<typename T>
	void rect(V2d low, V2d hgh, T clrIn)
	{
		setDrawClr(clrIn);
		drawAlpha=1;
		rect(low, hgh);
	}
	
	//circle
	
	template<typename T>
	void circle(V2d center, double radius, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		circle(center, radius);
	}
	
	template<typename T>
	void circle(V2d center, double radius, T clrIn)
	{
		setDrawClr(clrIn);
		drawAlpha=1;
		circle(center, radius);
	}
	
	//line
	
	template<typename T>
	void line(V2d start, V2d end, double thickness, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		drawThick=thickness;
		line(start, end);
	}
	
	template<typename T>
	void line(V2d start, V2d end, double thickness, T clrIn)
	{
		setDrawClr(clrIn);
		drawAlpha=1;
		drawThick=thickness;
		line(start, end);
	}
	
	template<typename T>
	void line(V2d start, V2d end, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		line(start, end);
	}
	
	template<typename T>
	void line(V2d start, V2d end, T clrIn)
	{
		setDrawClr(clrIn);
		drawAlpha=1;
		line(start, end);
	}
	
protected:
	
	///state variables
	
	double drawAlpha; //0.0-1.0, 0 is fully transparent, 1 is fully opaque
	double drawThick; //the thickness of lines drawn
};

}


