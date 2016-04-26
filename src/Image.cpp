#include "../h/Image.h"
#include "../h/SimpMath.h"
#include "../h/StringFuncs.h"
#include "../h/Error.h"

#include <fstream>

namespace widap
{

Image::Image()
{
	drawClr=clr(0, 0, 0);
	err.setPrefix("widap::Image: ");
	data=0;
}

Image::~Image()
{
	makeEmpty();
}

//converts bytes to an int (used for reading bitmap header)
int Image::bytes2num(unsigned char *ptr, int bytesNum)
{
	int otpt=0;
	int i;
	
	for (i=0; i<bytesNum; ++i)
	{
		otpt+=*(ptr+i)*pow(256, i);
	}
	
	return otpt;
}

//converts an int to bytes (used for writing data to bitmap header
void Image::num2bytes(unsigned char *ptr, int byteNum, int num)
{
	int i;
	
	for (i=0; i<byteNum; ++i)
	{
		*(ptr+i)=(num/(int)pow(256, i))%256;
	}
}

//returns true if error occurred (such as file not found)
bool Image::load(string filename)
{
	makeEmpty();
	
	string ext=getFileExtension(filename);
	
	if (ext!="bmp")
		filename+=".bmp";
	
	std::ifstream file(filename);
	
	if (!file.is_open())
	{
		err << "bitmap file '" << filename << "' failed to load (check filename)" << err;
		return 1;
	}
	
	unsigned char header[54];
	
	file.read((char *)header, 54);
	
	dim.x=bytes2num(header+18, 4);
	dim.y=bytes2num(header+22, 4);
	
	if (dim.x%4 || dim.y%4)
		err << "saved bitmap dimensions not divisible by 4\n\tthis is not yet implemented properly, so expect strange results" << err;
	
	try
	{
		data=new ClrBGR[dim.area()];
	}
	catch (std::bad_alloc)
	{
		err << "bad mem alloc while loading image, attempted size was " << dim.area()*sizeof(ClrBGR)/1048576.0 << "mb" << err;
		return 1;
	}
	
	file.read((char *)data, dim.area()*sizeof(ClrBGR));
	
	file.close();
	
	return 0;
}

//deletes any data in this image
void Image::makeEmpty()
{
	if (data)
	{
		delete[] data;
	}
	
	dim=0;
}

//saves the image, returns true on error
bool Image::save(string filename)
{
	string ext=getFileExtension(filename);
	
	if (ext!="bmp")
		filename+=".bmp";
	
	unsigned char header[54];
	
	if (isEmpty())
	{
		err << "tried to save empty image" << err;
		//return 1;
	}
	
	if (dim.x%4 || dim.y%4)
		err << "saved bitmap dimensions not divisible by 4\n\tthis is not yet implemented properly, so expect strange results" << err;
	
	//bitmap header info found at http://www.fastgraph.com/help/bmp_header_format.html
	num2bytes(header+0, 2, 19778); //BM in ASCII
	num2bytes(header+2, 4, dim.x*dim.y*3+54); //size of file
	num2bytes(header+6, 2, 0);
	num2bytes(header+8, 2, 0);
	num2bytes(header+10, 4, 54); //"offset to start of image data in bytes"; not sure what this means
	num2bytes(header+14, 4, 40); //size of remaining header
	num2bytes(header+18, 4, dim.x);
	num2bytes(header+22, 4, dim.y);
	num2bytes(header+26, 2, 1);
	num2bytes(header+28, 2, 24); //bits per pixel
	num2bytes(header+30, 4, 0); //no compression
	num2bytes(header+34, 4, (dim.x/4)*4*(dim.y/4)*4*3); //size of image data in bytes (including padding)
	num2bytes(header+38, 4, 2835); //72 dpi in pixels per meeter
	num2bytes(header+42, 4, 2835); //72 dpi in pixels per meeter
	num2bytes(header+46, 4, 0);
	num2bytes(header+50, 4, 0);
	
	std::ofstream file;
	
	file.open(filename);
	
	if (!file.is_open())
	{
		err << "image failed to save with filename '" << filename << "'" << err;
		return 1;
	}
	
	file.write((char *)header, 54);
	file.write((char *)data, dim.area()*sizeof(ClrBGR));
	
	file.close();
	
	return 0;
}

//sets the value of a single pixel to the predefined drawing color
void Image::set(int x, int y)
{
	if (drawAlpha>=1)
		data[y*dim.x+x]=drawClr;
	else if (drawAlpha>0)
	{
		ClrBGR * ptr=data+y*dim.x+x;
		ptr->r=ptr->r*(1-drawAlpha)+drawClr.r*drawAlpha;
		ptr->g=ptr->g*(1-drawAlpha)+drawClr.g*drawAlpha;
		ptr->b=ptr->b*(1-drawAlpha)+drawClr.b*drawAlpha;
	}
}

//set the draw color with a void pointer that is assumed to be of correct type
void Image::setDrawClr(void * clrIn)
{
	drawClr=*((ClrBGR *)clrIn);
}

//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
void Image::setDrawClr(int clrIn)
{
	switch (clrIn)
	{
	case 1:
		drawClr=clr(255, 255, 255);
		break;
		
	case 2:
		drawClr=clr(0, 16, 32);
		break;
		
	case 3:
		drawClr=clr(192, 255, 0);
		break;
		
	case 4:
		drawClr=clr(255, 0, 128);
		break;
		
	default:
		drawClr=clr(0, 0, 0);
		break;
	}
}

//set the draw color with a ClrRGBA pointer
void Image::setDrawClr(ClrRGBA * clrIn)
{
	drawClr.r=clrIn->r;
	drawClr.g=clrIn->g;
	drawClr.b=clrIn->b;
	drawAlpha=clrIn->a/255.0;
}

//set the draw color with a ClrRGBA value
void Image::setDrawClr(ClrRGBA clrIn)
{
	drawClr.r=clrIn.r;
	drawClr.g=clrIn.g;
	drawClr.b=clrIn.b;
	drawAlpha=clrIn.a/255.0;
}

//set the draw color with a ClrBGR value
void Image::setDrawClr(ClrBGR * clrIn)
{
	drawClr=*clrIn;
}

//set the draw color with a ClrBGR value
void Image::setDrawClr(ClrBGR clrIn)
{
	drawClr=clrIn;
}

/*
void Image::rect(V2d low, V2d hgh)
{
	low.max(V2d());
	hgh.min(dim);
	
	V2i i;
	
	for (i.y=low.y; i.y<hgh.y; ++i.y)
	{
		for (i.x=low.x; i.x<hgh.x; ++i.x)
		{
			data[i.y*dim.x+i.x]=drawClr;
		}
	}
}
*/

}


