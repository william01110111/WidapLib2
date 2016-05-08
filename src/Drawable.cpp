#include "../h/Drawable.h"
#include "../h/Error.h"
#include "../h/SimpMath.h"

namespace widap
{

Drawable::Drawable()
{
	drawAlpha=1;
}

Drawable::~Drawable()
{
	delete textPtr;
}


///mscl

//set the draw color with a void pointer that is assumed to be of correct type for whatever this image is
void Drawable::setDrawClr(void * clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of void *" << err;
}

//set the draw color with an bool (black or white for color image
void Drawable::setDrawClr(bool clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of bool" << err;
}

//set the draw color with a char
void Drawable::setDrawClr(char clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of char" << err;
}

//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
void Drawable::setDrawClr(int clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of int" << err;
}

//set the draw color with a ClrBGR, the most common way to draw
void Drawable::setDrawClr(ClrBGR clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of ClrBGR" << err;
}

//set the draw color with a ClrBGR and alpha
void Drawable::setDrawClr(ClrBGR clrIn, double alpha)
{
	err << "attempted to draw to a Drawable with unimplemented type of ClrBGR + alpha" << err;
}

//set the draw color with a ClrRGBA
void Drawable::setDrawClr(ClrRGBA clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of ClrRGBA" << err;
}

//set the draw color with a ClrHSL
void Drawable::setDrawClr(ClrHSL clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of ClrHSL" << err;
}

//just sets the alpha for drawing
void Drawable::setDrawAlpha(double alphaIn)
{
	drawAlpha=alphaIn;
}


///Text

//void Drawable::setTextPos(V2d posIn) {textPtr->setPos(posIn);}

//void Drawable::setTextHeight(double heightIn) {textPtr->setHeight(heightIn);}

//void Drawable::setTextBold(bool boldIn) {textPtr->setBold(boldIn);}

void Drawable::text(char c) {textPtr->draw(c);}

void Drawable::text(string s) {textPtr->draw(s);}

}
