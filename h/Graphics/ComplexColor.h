
#pragma once

#include "../Math/SimpMath.h"
#include "Color.h"

namespace widap
{

inline ClrBGR toBGR(ClrHSL hsl)
{
	ClrBGR bgr;
	
	//fix potential bad values:
	while (hsl.h<0)
		hsl.h+=1530;
	while (hsl.h>=1530)
		hsl.h-=1530;
	
	hsl.l=clamp(hsl.l, 0, 510);
	hsl.s=clamp(hsl.s, 0, 255-abs(hsl.l-255));
	
	int range=hsl.h/255; //from 0 to 5; the general color; the heigh, mid and low color components can be detirmened from range
	
	unsigned char *hgh, *mid, *low; //pointers that will be set to the 3 RGB components (hgh to the one with the heighest value etc.)
	
	hgh=&bgr.b+((4+range*5)/2)%3;
	mid=&bgr.b+((1+range))%3;
	low=&bgr.b+((1+range*5)/2)%3;
	
	*hgh=(hsl.l+hsl.s)/2;
	*low=(hsl.l-hsl.s)/2;
	*mid=(hsl.h-range*255);
	
	if (range%2)
		*mid=255-*mid;
	
	*mid=(*mid)*hsl.s/255+(*low);
	
	return bgr;
}

inline ClrBGR toBGR(const ClrRGBA& rgba)
{
	return ClrBGR(rgba.r, rgba.g, rgba.b);
}

#define toClr toBGR

inline ClrHSL toHSL(ClrBGR bgr)
{
	ClrHSL hsl;
	
	unsigned char *hgh, *mid, *low; //pointers that will be set to the 3 RGB components (hgh to the one with the heighest value etc.)
	
	int range; //from 0 to 5; the general color; the heigh, mid and low color components can be detirmened from range
	
	//tree format to make it run faster:
	if (bgr.g<bgr.b) {
		if (bgr.g>bgr.r) {
			range=3;
			hgh=&bgr.b;
			mid=&bgr.g;
			low=&bgr.r;
		} else if (bgr.b>bgr.r) {
			range=4;
			hgh=&bgr.b;
			mid=&bgr.r;
			low=&bgr.g;
		} else {
			range=5;
			hgh=&bgr.r;
			mid=&bgr.b;
			low=&bgr.g;
		}
	} else {
		if (bgr.r>bgr.g) {
			range=0;
			hgh=&bgr.r;
			mid=&bgr.g;
			low=&bgr.b;
		} else if (bgr.r>bgr.b) {
			range=1;
			hgh=&bgr.g;
			mid=&bgr.r;
			low=&bgr.b;
		} else {
			range=2;
			hgh=&bgr.g;
			mid=&bgr.b;
			low=&bgr.r;
		}
	}
	
	//this is a slightly slower but cooler way of setting range:
	//range=(bgr.g<bgr.b)*3+1+((bgr.r>bgr.g)-(bgr.b>bgr.r))*(1-(bgr.g>bgr.b)*2);
	
	//this is a slightly slower but cooler way of setting hgh, mid and low:
	/*hgh=&bgr.b+((22+range*5)/2)%3;
	mdl=&bgr.b+((19+range))%3;
	low=&bgr.b+((19+range*5)/2)%3;*/
	
	hsl.s=(*hgh)-(*low);
	
	if (*low==*hgh)
		hsl.h=0;
	else if (range%2)
		hsl.h=range*255+255-((*mid)-(*low))*255/(hsl.s); //this is basicly lerp(...) but may be a bit faster
	else
		hsl.h=range*255+((*mid)-(*low))*255/(hsl.s);
	
	hsl.l=(*hgh)+(*low);
	
	return hsl;
}

inline ClrBGR lerp(double in, double inLow, double inHgh, ClrBGR outLow, ClrBGR outHgh)
{
	double w=inHgh-inLow;
	
	if (w)
	{
		double o=in-inLow;
		
		outLow.r+=((outLow.r-outHgh.r)*o)/w;
		outLow.g+=((outLow.g-outHgh.g)*o)/w;
		outLow.b+=((outLow.b-outHgh.b)*o)/w;
		
		return outLow;
	}
	else
	{
		return outHgh;
	}
}

inline ClrBGR lerp(double in, ClrBGR outLow, ClrBGR outHgh)
{
	outLow.r+=(outLow.r-outHgh.r)*in;
	outLow.g+=(outLow.g-outHgh.g)*in;
	outLow.b+=(outLow.b-outHgh.b)*in;
	
	return outLow;
}

}


