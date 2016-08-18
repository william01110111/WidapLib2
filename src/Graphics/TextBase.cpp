#include "../../h/Graphics/TextBase.h"
#include "../../h/Graphics/Surface.h"
#include "../../h/Mscl/StringFuncs.h"
#include "../../h/Math/SimpMath.h"
#include "../../h/Mscl/Error.h"

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

