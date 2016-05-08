#include "../h/ImageBase.h"
#include "../h/SimpMath.h"

namespace widap
{

//a V2i rapper for set()
void ImageBase::set(V2i loc)
{
	set(loc.x, loc.y);
}


///shapes

//fills the ImageBase with the predefined color
void ImageBase::clear()
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

void ImageBase::rect(V2d lowD, V2d hghD)
{
	V2i low=lowD;
	V2i hgh=hghD;
	
	low.max(V2i());
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
void ImageBase::circle(V2d center, double radius)
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

//draws a filled triangle
void ImageBase::tri(V2d * vertsIn)
{
	V2i dim=getDim();
	V2d verts[3];
	int x, y;
	int xLow, xHgh;
	int yLow, yHgh;
	bool middleOnLeft;
	
	//set the array to the verts sorted from bottom to top
	if (vertsIn[0].y<vertsIn[1].y)
	{
		if (vertsIn[0].y<vertsIn[2].y)
		{
			verts[0]=vertsIn[0];
			
			if (vertsIn[1].y<vertsIn[2].y)
			{
				verts[1]=vertsIn[1];
				verts[2]=vertsIn[2];
			}
			else
			{
				verts[1]=vertsIn[2];
				verts[2]=vertsIn[1];
			}
		}
		else
		{
			verts[0]=vertsIn[2];
			verts[1]=vertsIn[0];
			verts[2]=vertsIn[1];
		}
	}
	else
	{
		if (vertsIn[1].y<vertsIn[2].y)
		{
			verts[0]=vertsIn[1];
			
			if (vertsIn[0].y<vertsIn[2].y)
			{
				verts[1]=vertsIn[0];
				verts[2]=vertsIn[2];
			}
			else
			{
				verts[1]=vertsIn[2];
				verts[2]=vertsIn[0];
			}
		}
		else
		{
			verts[0]=vertsIn[2];
			verts[1]=vertsIn[1];
			verts[2]=vertsIn[0];
		}
	}
	
	middleOnLeft=verts[1].x<lerp(verts[1].y, verts[0].y, verts[2].y, verts[0].x, verts[2].x);
	
	yLow=clamp((int)(verts[0].y+0.5), 0, dim.y);
	yHgh=clamp((int)(verts[1].y+0.5), 0, dim.y);
	
	for (y=yLow; y<yHgh; ++y)
	{
		xLow=clamp((int)(lerp(y+0.5, verts[0].y, verts[2-middleOnLeft].y, verts[0].x, verts[2-middleOnLeft].x)+0.5), 0, dim.x);
		xHgh=clamp((int)(lerp(y+0.5, verts[0].y, verts[1+middleOnLeft].y, verts[0].x, verts[1+middleOnLeft].x)+0.5), 0, dim.x);
		
		for (x=xLow; x<xHgh; ++x)
		{
			set(x, y);
		}
	}
	
	yLow=clamp((int)(verts[1].y+0.5), 0, dim.y);
	yHgh=clamp((int)(verts[2].y+0.5), 0, dim.y);
	
	for (y=yLow; y<yHgh; ++y)
	{
		xLow=clamp((int)(lerp(y+0.5, verts[2].y, verts[0+middleOnLeft].y, verts[2].x, verts[0+middleOnLeft].x)+0.5), 0, dim.x);
		xHgh=clamp((int)(lerp(y+0.5, verts[2].y, verts[1-middleOnLeft].y, verts[2].x, verts[1-middleOnLeft].x)+0.5), 0, dim.x);
		
		for (x=xLow; x<xHgh; ++x)
		{
			set(x, y);
		}
	}
}

//draws a line
void ImageBase::line(V2d start, V2d end, double thickness)
{
	V2d b, t;
	V2i dim=getDim();
	double lng=dst(start, end);
	double o=thickness/2.0;
	
	start.x+=0.5;
	start.y+=0.5;
	end.x+=0.5;
	end.y+=0.5;
	
	if (start.y<end.y)
	{
		b=start;
		t=end;
	}
	else
	{
		b=end;
		t=start;
	}
	
	double yo=(b.x-t.x)/lng;
	double xo=(t.y-b.y)/lng;
	
	//b.x+=yo/4;
	//b.y-=xo/4;
	//t.x-=yo/4;
	//t.y+=xo/4;
	
	//lng+=0.5;
	
	double m=(t.x-b.x)/(t.y-b.y);
	double lo=b.x-xo*o-(b.y-yo*o)*m;
	double ro=b.x+xo*o-(b.y+yo*o)*m;
	
	//setDrawClr(clr(255, 255, 255));
	//set(clamp((V2i)b, V2i(), (V2i)getDim()));
	//set(clamp((V2i)t, V2i(), (V2i)getDim()));
	
	double lby=b.y-yo*o, lty=t.y-yo*o, rby=b.y+yo*o, rty=t.y+yo*o;
	
	int btm=clamp((int)(b.y-o+0.5), 0, dim.y), top=clamp((int)(t.y+o+1.5), 0, dim.y);
	
	int x, y, left, right;
	
	for (y=btm; y<top; ++y)
	{
		if (y+0.5<=lby)
			left=clamp((int)(-sqrt(o*o-(y+0.5-b.y)*(y+0.5-b.y))+b.x+0.5), 0, dim.x);
		else if (y+0.5>=lty)
			left=clamp((int)(-sqrt(o*o-(y+0.5-t.y)*(y+0.5-t.y))+t.x+0.5), 0, dim.x);
		else
			left=clamp((int)((y+0.5)*m+lo+0.5), 0, dim.x);
		
		if (y+0.5<=rby)
			right=clamp((int)(sqrt(o*o-(y+0.5-b.y)*(y+0.5-b.y))+b.x+0.5), 0, dim.x);
		else if (y+0.5>=rty)
			right=clamp((int)(sqrt(o*o-(y+0.5-t.y)*(y+0.5-t.y))+t.x+0.5), 0, dim.x);
		else
			right=clamp((int)((y+0.5)*m+ro+0.5), 0, dim.x);
		
		for (x=left; x<right; ++x)
		{
			set(x, y);
		}
	}
	
	//err << yo << err;
	
	//circle((V2i)b, 4, clr(255, 0, 0));
	//circle((V2i)t, 4, clr(255, 128, 0));
	//circle(V2d(lby*m+lo, lby), 6, clr(0, 128, 255));
}

//draws a line using anti aliasing (does not currently work well)
/*void ImageBase::line(V2d start, V2d end, double thickness)
{
	V2d b, t;
	V2i dim=getDim();
	double lng=dst(start, end);
	double o=thickness/2.0;
	
	start.x+=0.5;
	start.y+=0.5;
	end.x+=0.5;
	end.y+=0.5;
	
	if (start.y<end.y)
	{
		b=start;
		t=end;
	}
	else
	{
		b=end;
		t=start;
	}
	
	double yo=(b.x-t.x)/lng;
	double xo=(t.y-b.y)/lng;
	
	//b.x+=yo/4;
	//b.y-=xo/4;
	//t.x-=yo/4;
	//t.y+=xo/4;
	
	//lng+=0.5;
	
	double m=(t.x-b.x)/(t.y-b.y);
	double lo=b.x-xo*o-(b.y-yo*o)*m;
	double ro=b.x+xo*o-(b.y+yo*o)*m;
	
	//setDrawClr(clr(255, 255, 255));
	//set(clamp((V2i)b, V2i(), (V2i)getDim()));
	//set(clamp((V2i)t, V2i(), (V2i)getDim()));
	
	double lby=b.y-yo*o, lty=t.y-yo*o, rby=b.y+yo*o, rty=t.y+yo*o;
	
	int btm=clamp((int)floor(b.y-o), 0, dim.y), top=clamp((int)ceil(t.y+o), 0, dim.y);
	
	int x, y;
	double left, right;
	
	for (y=btm; y<top; ++y)
	{
		if (y+0.5<=lby)
			left=clamp((int)(-sqrt(o*o-(y+0.5-b.y)*(y+0.5-b.y))+b.x+0.5), 0, dim.x);
		else if (y+0.5>=lty)
			left=clamp((int)(-sqrt(o*o-(y+0.5-t.y)*(y+0.5-t.y))+t.x+0.5), 0, dim.x);
		else
			left=max((y+0.5)*m+lo, 0.0);
		
		if (y+0.5<=rby)
			right=clamp((int)(sqrt(o*o-(y+0.5-b.y)*(y+0.5-b.y))+b.x+0.5), 0, dim.x);
		else if (y+0.5>=rty)
			right=clamp((int)(sqrt(o*o-(y+0.5-t.y)*(y+0.5-t.y))+t.x+0.5), 0, dim.x);
		else
			right=min((y+0.5)*m+ro, (double)dim.x);
		
		if (left<right)
		{
			drawAlpha=ceil(left)-left;
			set(floor(left), y);
			
			drawAlpha=1;
			
			for (x=ceil(left); x<floor(right); ++x)
			{
				
				set(x, y);
			}
			
			drawAlpha=right-floor(right);
			set(floor(right), y);
		}
	}
	
	//err << yo << err;
	
	//circle((V2i)b, 4, clr(255, 0, 0));
	//circle((V2i)t, 4, clr(255, 128, 0));
	//circle(V2d(lby*m+lo, lby), 6, clr(0, 128, 255));
}
*/

/*
//draws a line
void ImageBase::line(V2d start, V2d end)
{
	//this line algorithm draws great 1px lines but does terribly with transparency
	V2i a=start, b=end; //int versions
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
				// *sml=grdnt(*big, bigStrt, bigEnd, smlStrt, smlEnd)+0.5+i;
				
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
*/

void ImageBase::drawable(Drawable * other, V2d pos, double alphaIn)
{
	//draw a rectangle with an X as default implementation
	setDrawClr(1, alphaIn);
	rect(pos, pos+other->getDim());
	setDrawClr(0, alphaIn);
	line(pos+V2d(20, 20), pos+other->getDim()-V2d(20, 20), 20);
	line(V2d(pos.x+20, pos.y+other->getDim().y-20), V2d(pos.x+other->getDim().x-20, pos.y+20), 20);
}



}


