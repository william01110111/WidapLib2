
#pragma once

#include "../Math/Vector2D.h"
#include "Surface.h"
#include <string>

namespace widap
{

//the virtual base class for images, does not implement surface but most subclasses will
class ImageBase : public Surface
{
public:
	//create a new image of the given size
	virtual void create(V2u dimIn)=0;
	
	//returns true if error occurred (such as file not found)
	virtual bool load(std::string filename)=0;
	
	//deletes the contents of the image
	virtual void makeEmpty()=0;
	
	//again, returns true on error
	virtual bool save(std::string filename)=0;
	
	//returns if this image object is empty, or if it actually contains image data
	virtual bool isEmpty()=0;
	
	///drawing
	
	//sets the value of a single pixel to the predefined drawing color
	//does not use V2i for speed reasons, but there is a V2i rapper
	virtual void set(int x, int y)=0;
	
	//sets the given pixel to the predefined color, probably better to use set(int, int) for speed ans this is just a rapper
	void set(V2i loc);
	
	//fills the Surface with the predefined color
	virtual void clear();
	
	//draw a rectangle with the preset draw color
	virtual void rect(V2d low, V2d hgh);
	
	//draw a circle with the preset draw color
	virtual void circle(V2d center, double radius);
	
	//draw a triangle
	virtual void tri(V2d * vertsIn);
	
	//draw a line
	virtual void line(V2d start, V2d end, double thick);
};

}

