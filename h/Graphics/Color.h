
#pragma once

namespace widap
{

struct ClrRGBA;

//the standard color struct, in the original Widap library the exact same struct was called RGBpix because thats not confusing at all
struct ClrBGR
{
	ClrBGR() {}
	
	ClrBGR(unsigned char rIn, unsigned char gIn, unsigned char bIn)
	{
		r=rIn;
		g=gIn;
		b=bIn;
	}
	
	unsigned char b;
	unsigned char g;
	unsigned char r;
	
	//operator ClrRGBA();
};

typedef ClrBGR Clr; //make it a bit easier to type

inline ClrBGR clr(unsigned char r, unsigned char g, unsigned char b) {return {b, g, r};}

struct ClrRGBA
{
	ClrRGBA() {}
	
	ClrRGBA(unsigned char rIn, unsigned char gIn, unsigned char bIn, unsigned char aIn)
	{
		r=rIn;
		g=gIn;
		b=bIn;
		a=aIn;
	}
	
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

inline ClrRGBA clr(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {return {r, g, b, a};}

//ClrBGR::operator ClrRGBA() {return {r, g, b, 255};}

struct ClrHSL
{
	ClrHSL() {}
	
	ClrHSL(int hIn, int sIn, int lIn)
	{
		h=hIn;
		s=sIn;
		l=lIn;
	}
	
	int h; //hue; from 0 to 1530 (255*6); is the color part
	int s; //saturation; from 0 to 255; the distance between the lowest and highest RGB value; how vivid the color is
	int l; //lightness; 0 to 510; the lowest RGB value added to the highest
};

}

