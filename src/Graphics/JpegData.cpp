
///must include the following in linker settings to use the jpeg module
//obviously you must also have the turbojpeg library installed, which will obviously be a huge pain on windows
/**

-lturbojpeg

**/


#include "../../h/Graphics/JpegData.h"
#include "../../h/Mscl/Error.h"
#include "../../h/Mscl/Timer.h"

#include <turbojpeg.h>

//this class was wretten with help from stackoverflow.com/a/17671012

namespace widap
{

JpegData::JpegData()
{
	compressor=tjInitCompress();
	decompressor=tjInitDecompress();
}

JpegData::~JpegData()
{
	makeEmpty();
	tjDestroy(compressor);
	tjDestroy(decompressor);
}

void JpegData::fromImage(Image * img)
{
	makeEmpty();
	
	dim=img->getDim();
	
	tjCompress2(compressor, (unsigned char *)img->getData(), dim.x, 0, dim.y, TJPF_BGR, &data, &dataSize, TJSAMP_444, quality, TJFLAG_BOTTOMUP);
	
	//err << "compressed jpeg to " << 100.0*dataSize/(img->getDim().area()*sizeof(ClrBGR)) << "% the original size" << err;
}

void JpegData::toImage(Image * img, bool makeEmptyAfter)
{
	int subsamp;
	
	tjDecompressHeader2(decompressor, data, dataSize, &dim.x, &dim.y, &subsamp);
	
	img->create(dim);
	
	tjDecompress2(decompressor, data, dataSize, (unsigned char *)img->getData(), dim.x, 0, dim.y, TJPF_BGR, TJFLAG_BOTTOMUP);
	
	if (makeEmptyAfter)
		makeEmpty();
}

void JpegData::makeEmpty()
{
	if (data)
	{
		tjFree(data);
		data=nullptr;
	}
	
	dim.zero();
}

}

