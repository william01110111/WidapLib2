#include "../../h/Graphics/Surface.h"
#include "../../h/Graphics/ChildSurface.h"
#include "../../h/Graphics/QueuedSurface.h"
#include "../../h/Mscl/Error.h"
#include "../../h/Math/ComplexMath.h"

namespace widap
{

Surface::Surface()
{
	drawAlpha=1;
}

Surface::~Surface()
{
	if (textPtr)
		delete textPtr;
}


///mscl

//set the draw color with an bool (black or white for color image
void Surface::setDrawClr(bool clrIn)
{
	err << "attempted to draw to a Surface with unimplemented type of bool" << err;
}

//set the draw color with a char
void Surface::setDrawClr(char clrIn)
{
	err << "attempted to draw to a Surface with unimplemented type of char" << err;
}

//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
void Surface::setDrawClr(int clrIn)
{
	err << "attempted to draw to a Surface with unimplemented type of int" << err;
}

//set the draw color with a ClrBGR, the most common way to draw
void Surface::setDrawClr(ClrBGR clrIn)
{
	err << "attempted to draw to a Surface with unimplemented type of ClrBGR" << err;
}

//set the draw color with a ClrRGBA
void Surface::setDrawClr(ClrRGBA clrIn)
{
	err << "attempted to draw to a Surface with unimplemented type of ClrRGBA" << err;
}

//set the draw color with a ClrHSL
void Surface::setDrawClr(ClrHSL clrIn)
{
	err << "attempted to draw to a Surface with unimplemented type of ClrHSL" << err;
}

//just sets the alpha for drawing
void Surface::setDrawAlpha(double alphaIn)
{
	drawAlpha=alphaIn;
}

void Surface::surfaceWithAlphaSet(Surface * other, V2d pos)
{
	//draw a rectangle with an X as default implementation
	setDrawClr(1, drawAlpha);
	rect(pos, pos+other->getDim());
	setDrawClr(0, drawAlpha);
	line(pos+V2d(20, 20), pos+other->getDim()-V2d(20, 20), 20);
	line(V2d(pos.x+20, pos.y+other->getDim().y-20), V2d(pos.x+other->getDim().x-20, pos.y+20), 20);
}

ChildSurface * Surface::newChildSurface(V2d pos, V2u dim)
{
	return new QueuedSurface(this, pos, dim);
}

void Surface::poly(V2d * vertsIn, int vertNum)
{
	V2d * buffer=new V2d[vertNum];
	int pos, i;
	bool isEar;
	int lastVertNum=vertNum;
	V2d v[3];
	
	for (i=0; i<vertNum; ++i)
	{
		buffer[i]=vertsIn[i];
	}
	
	pos=vertNum;
	
	while (vertNum>2)
	{
		v[0]=buffer[(pos+0)%vertNum];
		v[1]=buffer[(pos+1)%vertNum];
		v[2]=buffer[(pos+2)%vertNum];
		isEar=false;
		
		if (isOnRightSideOfLine(v[1], v[0], v[2]))
		{
			isEar=true;
			
			for (i=pos+3; i<pos+vertNum; ++i)
			{
				if (isInTriangle(buffer[i%vertNum], v[0], v[1], v[2]))
				{
					isEar=false;
					break;
				}
			}
		}
		
		if (isEar)
		{
			tri(v);
			
			for (i=pos+1; (i%vertNum)<vertNum-1; ++i)
			{
				buffer[i%vertNum]=buffer[(i+1)%vertNum];
			}
			
			--vertNum;
		}
		else
		{
			++pos;
			
			if (!(pos%vertNum))
			{
				if (lastVertNum==vertNum)
					break;
				else
					lastVertNum=vertNum;
			}
		}
	}
}

///Text

//void Surface::setTextPos(V2d posIn) {textPtr->setPos(posIn);}

//void Surface::setTextHeight(double heightIn) {textPtr->setHeight(heightIn);}

//void Surface::setTextBold(bool boldIn) {textPtr->setBold(boldIn);}


}
