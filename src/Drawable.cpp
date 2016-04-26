#include "../h/Drawable.h"
#include "../h/Error.h"
#include "../h/SimpMath.h"

namespace widap
{

Drawable::Drawable()
{
	drawAlpha=1;
	drawThick=1;
}

///mscl

//a V2i rapper for set()
void Drawable::set(V2i loc)
{
	set(loc.x, loc.y);
}

void Drawable::setDrawAlpha(double alphaIn)
{
	drawAlpha=alphaIn;
}

void Drawable::setDrawThick(double thickIn)
{
	drawThick=thickIn;
}

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

//set the draw color with a ClrRGBA, the most common way to draw
void Drawable::setDrawClr(ClrRGBA clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of ClrRGBA" << err;
}

//set the draw color with a ClrHSL, the most common way to draw
void Drawable::setDrawClr(ClrHSL clrIn)
{
	err << "attempted to draw to a Drawable with unimplemented type of ClrHSL" << err;
}


///shapes

//fills the Drawable with the predefined color
void Drawable::clear()
{
	V2i i, dim=getDim();
	
	for (i.y=0; i.y<dim.y; ++i.y)
	{
		for (i.x=0; i.x<dim.x; ++i.x)
		{
			set(i.x, i.y);
		}
	}
}

void Drawable::rect(V2d low, V2d hgh)
{
	low.max(V2d());
	hgh.min(getDim());
	
	V2i i;
	
	for (i.y=low.y; i.y<hgh.y; ++i.y)
	{
		for (i.x=low.x; i.x<hgh.x; ++i.x)
		{
			set(i.x, i.y);
		}
	}
}

//draws a filled circle
void Drawable::circle(V2d center, double radius)
{
	
	///WARNING: this function is vital for drawn lines to look right. Do not fuck it up without testing it with line()
	
	//radius-=0.1; //makes circles look less polygony
	
	V2i i, low, hgh, offset, dim, centerInt;
	int width;
	
	centerInt=center;
	dim=getDim();
	offset=V2i(radius, radius);
	
	low=max(centerInt-offset, V2i());
	hgh=min(centerInt+offset, dim);
	
	for (i.y=low.y; i.y<hgh.y; ++i.y)
	{
		width=sqrt(radius*radius-(i.y-center.y)*(i.y-center.y));
		low.x=max(centerInt.x-width+1, 0);
		hgh.x=min(centerInt.x+width, dim.x);
		
		for (i.x=low.x; i.x<hgh.x; ++i.x)
		{
			set(i.x, i.y);
		}
	}
}

//draws a line
void Drawable::line(V2d start, V2d end)
{
	V2i a(start), b(end); //int versions
	int x, y, i;
	int xShft, yShft, shftSum;;
	int xOfst, yOfst;
	int *big, *sml;
	int bigStrt, bigEnd, smlStrt, smlEnd;
	V2i dim=getDim();
	
	xShft=floor((drawThick-1)*(a.y-b.y)/dst(a, b)+0.5);
	yShft=floor(-(drawThick-1)*(a.x-b.x)/dst(a, b)+0.5);
	shftSum=abs(xShft)+abs(yShft);
	
	//if (thick<2)
		//shftSum=1;
	
	//std::cout << "xShift: " << xShft << ", yShft: " << yShft << "\n";
	
	//printf(txt, "xShft: %d, yShft: %d", xShft, yShft);
	
	if (fabs(a.y-b.y)>fabs(a.x-b.x))
	{
		big=&y;
		sml=&x;
		if (a.y<b.y)
		{
			bigStrt=a.y;
			bigEnd=b.y;
			smlStrt=a.x;
			smlEnd=b.x;
		}
		else
		{
			bigStrt=b.y;
			bigEnd=a.y;
			smlStrt=b.x;
			smlEnd=a.x;
		}
	}
	else
	{
		big=&x;
		sml=&y;
		if (a.x<b.x)
		{
			bigStrt=a.x;
			bigEnd=b.x;
			smlStrt=a.y;
			smlEnd=b.y;
		}
		else
		{
			bigStrt=b.x;
			bigEnd=a.x;
			smlStrt=b.y;
			smlEnd=a.y;
		}
	}
	
	if (bigStrt!=bigEnd)
	{
		xOfst=floor(-xShft/2.0+0.5);
		yOfst=floor(-yShft/2.0+0.5);
		
		for (i=0; i<=shftSum; ++i)
		{
			for (*big=bigStrt; *big<=bigEnd; ++*big)
			{
				//((inpt-strtI)*(strtO-endO))/(strtI-endI)+strtO;
				*sml=((*big-bigStrt)*(smlStrt-smlEnd)+(bigStrt-bigEnd)*0.5)/(bigStrt-bigEnd)+smlStrt;
				//*sml=grdnt(*big, bigStrt, bigEnd, smlStrt, smlEnd)+0.5+i;
				
				if (x+xOfst>=0 && x+xOfst<dim.x && y+yOfst>=0 && y+yOfst<dim.y)
				{
					set(x+xOfst, y+yOfst);
					//bits[(x+xOfst)+(y+yOfst)*dim.x]=clr;
				}
			}
			
			if (abs(xOfst-floor(xShft/2.0+0.5))>abs(yOfst-floor(yShft/2.0+0.5)))
			{
				if (xOfst<floor(xShft/2.0+0.5))
					xOfst++;
				else
					xOfst--;
			}
			else
			{
				if (yOfst<floor(yShft/2.0+0.5))
					yOfst++;
				else
					yOfst--;
			}
		}
	}
	
	//blend(pix(a.x+xShft, a.y+yShft), ::clr(255, 255, 255), 0.5);
	//blend(pix(a.x-xShft, a.y-yShft), ::clr(255, 255, 255), 0.5);
	
	//if (shftSum>1)
	{
		circle(a, drawThick/2.0-0.5, clr(0, 128, 255), 0.5);
		circle(b, drawThick/2.0-0.5, clr(0, 128, 255), 0.5);
		
		//circle(a, drawThick/2.0-0.5); //continues to use the already set color
		//circle(b, drawThick/2.0-0.5);
	}
}


}
