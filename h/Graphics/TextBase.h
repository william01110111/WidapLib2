#pragma once

#include "../Math/Vector2D.h"

#include <string>
using std::string;

namespace widap
{

class Surface;

class TextBase
{
	
public:
	
	TextBase();
	virtual ~TextBase();
	
	void setPos(V2d posIn) {pos=posIn; offset=0;}
	void setHeight(double heightIn) {dim.y=heightIn; dim.x=heightIn*widthRateo;}
	void setBold(bool boldIn) {drawBold=boldIn;}
	
	template <typename T> void setDrawClr(T clrIn, double alphaIn=1)
	{
		drawAlpha=alphaIn;
		delete drawClr;
		drawClr=new ClrType<T>(clrIn);
	}
	
	template <typename T> void setBkndClr(T clrIn, double alphaIn=1)
	{
		bkndAlpha=alphaIn;
		delete bkndClr;
		bkndClr=new ClrType<T>(clrIn);
	}
	
	template <typename T> void setVals(V2d posIn, double heightIn, T clrIn, double alphaIn=1)
	{
		pos=posIn; offset=0;
		dim.y=heightIn; dim.x=heightIn*widthRateo;
		drawAlpha=alphaIn;
		delete drawClr;
		drawClr=new ClrType<T>(clrIn);
	}
	
	void draw(string s);
	
	template <typename T> void draw(string s, V2d posIn, double heightIn, T clrIn, double alphaIn=1)
	{
		setVals(posIn, heightIn, clrIn, alphaIn);
		draw(s);
	}
	
	//returns the dimensions of the rectangle the string would take up, taking into account newlines and tabs
	V2d getDim(string s, double heightIn);
	V2d getDim(string s) {return getDim(s, dim.y);}
	
protected:
	static const int TAB_CHARS=4; //max characters in a tab, min is 1
	double widthRateo=1; //should be set by the constructor, what width is relative to height
	V2d dim; //the width and height in pixels of a character
	V2d pos; //the current y position of the top of the text line and the left margin x position
	double offset; //the x offset in pixels from basePos of the left side of the next character
	bool drawBold; //if to draw the text bold
	
	//render a glyph (aka a character) (should not be called for special characters like tab or newline)
	virtual void renderGlyph(char c)=0;
	
private:
	
	class ClrTypeBase
	{
	public:
		virtual void setDrawClr(Surface * surface)=0;
		virtual ~ClrTypeBase() {}
	};
	
	//this class stores any type to use as a color
	template<typename T>
	class ClrType : public ClrTypeBase
	{
	public:
		ClrType(T in) {data=in;}
		void setDrawClr(Surface * surface);
		T data;
	};
	
	void draw(char c);
	
protected:
	
	ClrTypeBase * drawClr, * bkndClr;
	double drawAlpha, bkndAlpha;
};

}

