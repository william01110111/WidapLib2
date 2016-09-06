
///must include the following in linker settings to use the jpeg module
//obviously you must also have the turbojpeg library installed, which will obviously be a huge pain on windows
/**

-lturbojpeg

**/

#pragma once
#include <string>
#include "Image.h"

namespace widap
{

class JpegData
{
	
public:
	
	JpegData();
	~JpegData();
	
	void fromImage(Image * img);
	
	void toImage(Image * img, bool makeEmptyAfter=false);
	
	//free any image data
	void makeEmpty();
	
private:
	
	int quality=50;
	static const int colorComponents=3;
	V2i dim;
	long unsigned int dataSize=0; //not sure what this is
	void * compressor; //this should be of type tjhandle, which is just a typedef of void pointer
	void * decompressor;
	
	unsigned char * data=nullptr;
};

}


