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
	
	enum AlignX {LEFT, CENTER_X, RIGHT};
	enum AlignY {TOP, CENTER_Y, BOTTOM};
	//enum Overflow {ALLOW, CHOP, SHRINK, WRAP};
	enum Overflow {ALLOW_ALLOW, WRAP_ALLOW, CHOP_ALLOW, ALLOW_CHOP, WRAP_CHOP, CHOP_CHOP, SHRINK_TO_BOUNDS};
	
	TextBase(Surface * surfaceIn);
	virtual ~TextBase();
	
	//void setPos(V2d posIn);
	//void setPos(V2d posIn, Align alignIn);
	void setPos(V2d posIn, AlignX alignXIn, AlignY alignYIn);
	
	void setPos(V2d lowIn, V2d hghIn, AlignX alignInX, AlignY alignInY, Overflow overflowIn);
	
	void setHeight(double heightIn) {cDim=V2d(heightIn*widthRateo, heightIn);}
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
	
	void draw(const string& s);
	
	/*template <typename T> void draw(const string& s, V2d posIn, double heightIn, T clrIn, double alphaIn=1)
	{
		setPos(posIn);
		setHeight(heightIn);
		drawAlpha=alphaIn;
		delete drawClr;
		drawClr=new ClrType<T>(clrIn);
		draw(s);
	}*/
	
	//returns the dimensions of the rectangle the string would take up, taking into account newlines and tabs
	V2d getBounds(const string& s, double heightIn, double maxWidth=-1);
	V2d getBounds(const string& s) {return getBounds(s, cDim.y);}
	
	//get the width of the line starting at the i location in the string
	//when function returns, i will be the first char after \n or one greater then the size of the string
	double getLineWidth(const string& s, int * i, double heightIn, double maxWidth=-1);
	double getLineWidth(const string& s, int * i) {return getLineWidth(s, i, cDim.y);}
	
protected:
	static const int TAB_CHARS=4; //max characters in a tab, min is 1
	double widthRateo=1; //should be set by the constructor, what width is relative to height
	V2d cDim; //the width and height in pixels of a character
	V2d pos; //the current location of the upper left of the next character
	V2d lowBound, hghBound; //the bounding rectangle the text bust stay in
	bool drawBold=false; //if to draw the text bold
	AlignX alignX=LEFT;
	AlignY alignY=TOP; //the allignment
	//Overflow overflowX=ALLOW, overflowY=ALLOW; //the overflow method
	Overflow overflow=ALLOW_ALLOW; //the overflow method
	
	Surface * surface; // the surface that the text will be drawn to
	
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
	
protected:
	
	ClrTypeBase * drawClr, * bkndClr;
	double drawAlpha, bkndAlpha;
};

}

