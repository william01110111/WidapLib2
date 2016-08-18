#pragma once

#include "../Math/Vector2D.h"
#include "Color.h"
#include "TextBase.h"

#include <string>
using std::string;

///this declares the Surface superclass that you can draw to

namespace widap
{

class Surface
{
	//put USING_SURFACE somewhere in the header of subclasses to get access to all the functions
	//any function that is overloaded with some versions virtual and others not must go here
	
	#define USING_SURFACE			\
		using Surface::setDrawClr;	\
		using Surface::clear;		\
		using Surface::rect;		\
		using Surface::circle;		\
		using Surface::tri;			\
		using Surface::line;		\
		using Surface::surface		\
		
	
public:
	
	Surface();
	~Surface();
	
	///virtual functions
	
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
	
	//set the draw color with a ClrBGR, plus an alpha value, also common
	virtual void setDrawClr(ClrBGR clrIn, double alphaIn);
	
	//set the draw color with a ClrRGBA
	virtual void setDrawClr(ClrRGBA clrIn);
	
	//set the draw color with a ClrHSL
	virtual void setDrawClr(ClrHSL clrIn);
	
	
	///shape pure virtual functions
	
	//fills the Surface with the predefined color
	virtual void clear()=0;
	
	//draw a rectangle with the preset draw color
	virtual void rect(V2d low, V2d hgh)=0;
	
	//draw a circle with the preset draw color
	virtual void circle(V2d center, double radius)=0;
	
	//draw a triangle
	virtual void tri(V2d * vertsIn)=0;
	
	//draw a line
	virtual void line(V2d start, V2d end, double thick)=0;
	
	//draw another surface, this will only work if the specific combination of types has been implemented
	virtual void surface(Surface * other, V2d pos, double alphaIn)=0;
	
	
	///mscl
	
	//sets the draw color and the alpha
	template<typename T>
	void setDrawClr(T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
	}
	
	//just sets the alpha for drawing
	void setDrawAlpha(double alphaIn);
	
	void poly(V2d * vertsIn, int vertNum);
	
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
		circle(center, radius);
	}
	
	//tri
	
	template<typename T>
	void tri(V2d * vertsIn, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		tri(vertsIn);
	}
	
	template<typename T>
	void tri(V2d * vertsIn, T clrIn)
	{
		setDrawClr(clrIn);
		tri(vertsIn);
	}
	
	//line
	
	template<typename T>
	void line(V2d start, V2d end, double thickness, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		line(start, end, thickness);
	}
	
	template<typename T>
	void line(V2d start, V2d end, double thickness, T clrIn)
	{
		setDrawClr(clrIn);
		drawAlpha=1;
		line(start, end, thickness);
	}
	
	//surface
	
	void surface(Surface * other, V2d pos)
	{
		surface(other, pos, 1);
	}
	
	void surface(Surface * other)
	{
		surface(other, V2d(), 1);
	}
	
	//poly
	
	template<typename T>
	void poly(V2d * vertsIn, int vertNum, T clrIn, double alphaIn)
	{
		setDrawClr(clrIn);
		drawAlpha=alphaIn;
		poly(vertsIn, vertNum);
	}
	
	template<typename T>
	void poly(V2d * vertsIn, int vertNum, T clrIn)
	{
		setDrawClr(clrIn);
		poly(vertsIn, vertNum);
	}
	
	
	///text
	
	TextBase * text() {return textPtr;}
	void text(char c);
	void text(string s);
	template <typename T> void text(string s, V2d posIn, double heightIn, T clrIn, double alphaIn=1)
	{
		textPtr->draw(s, posIn, heightIn, clrIn, alphaIn);
	}
	
	///type id
	
	enum Type
	{
		IMAGE_BGR,
		WINDOW_SFML,
		UNKNOWN
	};
	
	virtual Type getType() {return UNKNOWN;}

	
protected:
	
	TextBase * textPtr;
	
	//called only by the constructor, should init the textPtr pointer
	virtual void textInit()=0;
	
	///state variables
	
	double drawAlpha; //0.0-1.0, 0 is fully transparent, 1 is fully opaque
};

}


