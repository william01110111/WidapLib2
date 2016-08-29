#include "../../h/Graphics/TextBase.h"
#include "../../h/Graphics/Surface.h"
//#include "../../h/Mscl/StringFuncs.h"
#include "../../h/Math/SimpMath.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

TextBase::TextBase(Surface * surfaceIn)
{
	surface=surfaceIn;
	setHeight(12);
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

void TextBase::setPos(V2d posIn, AlignX alignXIn, AlignY alignYIn)
{
	lowBound=posIn;
	hghBound=posIn;
	alignX=alignXIn;
	alignY=alignYIn;
	overflow=ALLOW_ALLOW;
	pos=posIn;
}

void TextBase::setPos(V2d lowIn, V2d hghIn, AlignX alignXIn, AlignY alignYIn, Overflow overflowIn)
{
	lowBound=lowIn;
	hghBound=hghIn;
	alignX=alignXIn;
	alignY=alignYIn;
	overflow=overflowIn;
	pos=V2d(lowIn.x, hghIn.y);
}

void TextBase::setStyle(const TextStyle& style)
{
	cDim=V2d(style.height*widthRateo, style.height);
	drawBold=style.bold;
	drawAlpha=style.alpha;
	delete drawClr;
	drawClr=new ClrType<Clr>(style.color);
	if (style.bkndAlpha>0)
	{
		delete bkndClr;
		bkndAlpha=style.bkndAlpha;
		bkndClr=new ClrType<Clr>(style.bkndColor);
	}
}

V2d TextBase::getBounds(const string& s, double heightIn, double maxWidth)
{
	V2d out;
	double w=0;
	int i=0;
	
	do
	{
		w=getLineWidth(s, &i, heightIn, maxWidth);
		
		if (fabs(w)>fabs(out.x))
			out.x=w;
		
		out.y+=heightIn;
	}
	while (i<(int)s.length());
	
	return out;
}

double TextBase::getLineWidth(const string& s, int * i, double heightIn, double maxWidth)
{
	double cw=heightIn*widthRateo, w=0;
	
	while (true)
	{
		if ((*i)>=(int)s.size())
		{
			break;
		}
		
		if (s[*i]=='\n')
		{
			++(*i);
			break;
		}
		
		if (maxWidth>=0 && w+cw>maxWidth && w>0)
		{
			break;
		}
		
		++(*i);
		w+=cw;
	}
	
	return w;
}

void TextBase::draw(const string& s)
{
	double wrapWidth=((overflow==WRAP_ALLOW || overflow==WRAP_CHOP)?hghBound.x-lowBound.x:-1);
	
	bool wrap=(overflow==WRAP_ALLOW || overflow==WRAP_CHOP);
	bool chopX=(overflow==CHOP_ALLOW || overflow==CHOP_CHOP);
	bool chopY=(overflow==ALLOW_CHOP || overflow==WRAP_CHOP || overflow==CHOP_CHOP);
	
	if (alignY!=TOP || overflow==SHRINK_TO_BOUNDS)
	{
		V2d dim=getBounds(s, cDim.y, wrapWidth);
		
		if (overflow==SHRINK_TO_BOUNDS)
		{
			if (cDim.y<0 || dim.y>hghBound.y-lowBound.y)
			{
				double scale=(hghBound.y-lowBound.y)/dim.y;
				cDim*=scale;
				dim*=scale;
			}
			
			if (dim.x>hghBound.x-lowBound.x)
			{
				double scale=(hghBound.x-lowBound.x)/dim.x;
				cDim*=scale;
				dim*=scale;
			}
		}
		
		if (chopY && dim.y>hghBound.y-lowBound.y)
			dim.y=floor((hghBound.y-lowBound.y)/cDim.y)*cDim.y;
		
		if (alignY==BOTTOM)
		{
			pos.y=dim.y+lowBound.y;
		}
		else if (alignY==CENTER_Y)
		{
			pos.y=(dim.y+lowBound.y+hghBound.y)/2.0;
		}
	}
	
	if ((wrap || chopX) && hghBound.x-lowBound.x<cDim.x)
		return;
	
	if (chopY && hghBound.y-lowBound.y<cDim.y)
		return;
	
	if (alignX!=LEFT)
	{
		double w=0;
		
		int i=0, j=0;
		
		do
		{
			w=getLineWidth(s, &i, cDim.y, wrapWidth);
			
			if (chopX && w>hghBound.x-lowBound.x)
				w=floor((hghBound.x-lowBound.x)/cDim.x)*cDim.x;
			
			if (alignX==RIGHT)
			{
				pos.x=hghBound.x-w;
			}
			else //CENTER
			{
				pos.x=(hghBound.x+lowBound.x-w)/2.0;
			}
			
			int l=i-(i>0 && s[i-1]=='\n'?1:0);
			
			if (chopX)
				l=min(l, (int)((hghBound.x-lowBound.x)/cDim.x)+j);
			
			for (int k=j; k<l; ++k)
			{
				renderGlyph(s[k]);
				pos.x+=cDim.x;
			}
			
			j=i;
			pos.y-=cDim.y;
			pos.x=lowBound.x;
			
			if (chopY && pos.y-cDim.y<lowBound.y)
						return;
		}
		while (i<(int)s.length());
	}
	else
	{
		for (int i=0; i<(int)s.length(); ++i)
		{
			if (s[i]=='\n')
			{
				pos.y-=cDim.y;
				pos.x=lowBound.x;
				
				if (chopY && pos.y-cDim.y<lowBound.y)
					return;
			}
			else if ((wrap || chopX) && pos.x+cDim.x>hghBound.x)
			{
				if (wrap)
				{
					pos.y-=cDim.y;
					pos.x=lowBound.x;
					
					if (chopY && pos.y-cDim.y<lowBound.y)
						return;
					
					renderGlyph(s[i]);
					pos.x+=cDim.x;
				}
				else if (chopX)
				{
					while (i<(int)s.length() && s[i]!='\n')
					{
						++i;
					}
					
					pos.y-=cDim.y;
					pos.x=lowBound.x;
					
					if (chopY && pos.y-cDim.y<lowBound.y)
						return;
				}
			}
			else
			{
				renderGlyph(s[i]);
				pos.x+=cDim.x;
			}
		}
	}
}

template <typename T> void TextBase::ClrType<T>::setDrawClr(Surface * surface) {surface->setDrawClr(data);}

template class TextBase::ClrType<bool>;
template class TextBase::ClrType<int>;
template class TextBase::ClrType<ClrBGR>;
template class TextBase::ClrType<ClrRGBA>;
template class TextBase::ClrType<ClrHSL>;

}

