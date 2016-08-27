#include "../../h/Graphics/TextBase.h"
#include "../../h/Graphics/Surface.h"
//#include "../../h/Mscl/StringFuncs.h"
#include "../../h/Math/SimpMath.h"

namespace widap
{

TextBase::TextBase()
{
	setHeight(12);
	pos=V2d(0, 0);
	offset=0;
	drawBold=0;
	widthRateo=1;
	drawClr=new ClrType<bool>(1);
	bkndClr=new ClrType<bool>(0);
	drawAlpha=1.0;
	bkndAlpha=0.0;
}

TextBase::~TextBase()
{
	delete drawClr;
	delete bkndClr;
}

void TextBase::draw(char c)
{
	switch (c)
	{
		
	case '\n': //newline
		pos.y-=dim.y;
		offset=0;
		break;
		
	case '\t': //tab
		offset=(floor(offset/(dim.x*TAB_CHARS))+1)*dim.x*TAB_CHARS;
		break;
		
	default: //any other character
		renderGlyph(c);
		offset+=dim.x;
		break;
	}
}

V2d TextBase::getDim(string s, double heightIn)
{
	V2d out(0, heightIn), dim(heightIn*widthRateo, heightIn);
	double offset=0;
	
	for (unsigned i=0; i<s.length(); ++i)
	{
		switch (s[i])
		{
			
		case '\n': //newline
			out.y+=dim.y;
			out.x=max(offset, out.x);
			offset=0;
			break;
			
		case '\t': //tab
			offset=(floor(offset/(dim.x*TAB_CHARS))+1)*dim.x*TAB_CHARS;
			break;
			
		default: //any other character
			offset+=dim.x;
			break;
		}
	}
	
	out.x=max(offset, out.x);
	
	return out;
}

void TextBase::draw(string s)
{
	for (unsigned i=0; i<s.length(); ++i)
	{
		draw(s[i]);
	}
}

template <typename T> void TextBase::ClrType<T>::setDrawClr(Surface * surface) {surface->setDrawClr(data);}

template class TextBase::ClrType<bool>;
template class TextBase::ClrType<int>;
template class TextBase::ClrType<ClrBGR>;
template class TextBase::ClrType<ClrRGBA>;
template class TextBase::ClrType<ClrHSL>;

}

