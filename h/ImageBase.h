
#pragma once

#include <string>

namespace widap
{

//the virtual base class for images, does not implement drawable but most subclasses will
class ImageBase
{
public:
	virtual bool load(std::string filename)=0; //returns true if error occurred (such as file not found)
	virtual void makeEmpty()=0; //deletes the contents of the image
	virtual bool save(std::string filename)=0; //again, returns true on error
	virtual bool isEmpty()=0; //returns if this image object is empty, or if it actually contains image data
	
	bool load(const char * filename) {return load(std::string(filename));}
	bool save(const char * filename) {return save(std::string(filename));}
};

}

