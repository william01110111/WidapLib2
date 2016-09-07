
#include "../../h/UI/StackViewUI.h"
#include "../../h/Math/SimpMath.h"

namespace widap
{

template <typename T>
inline T StackViewUI::mj(const V2<T>& in)
{
	return h?in.x:in.y;
}

template <typename T>
inline T StackViewUI::mn(const V2<T>& in)
{
	return h?in.y:in.x;
}

void StackViewUI::setChildRects()
{
	V2d low=outerBuffer+getLow(), hgh=-outerBuffer+getHgh();
	
	//if there is not enough room for anything, deactivate all views and return
	if (hgh.x<low.x || hgh.y<low.y)
	{
		for (auto i=children.begin(); i!=children.end(); i++)
		{
			(*i)->setActive(false);
		}
		
		return;
	}
	
	double majorSize=0;
	int majorStretchNum=0;
	
	for (auto i=children.begin(); i!=children.end(); i++)
	{
		if (mj((*i)->getStretch()))
			majorStretchNum++;
		
		majorSize+=mj((*i)->getDim());
		majorSize+=innerBuffer;
	}
	
	majorSize-=innerBuffer;
	
	double mjPos=0;
		
	if (majorStretchNum>0)
	{
		mjPos=mj(low);
	}
	else
	{
		switch (majorAlign)
		{
		case LEADING:
			mjPos=mj(low);
			break;
		
		case TRAILING:
			mjPos=mj(hgh)-majorSize;
			break;
			
		case CENTER:
			mjPos=(mj(low)+mj(hgh)-majorSize)/2.0;
			break;
			
		case SPACE:
			mjPos=mj(low);
			break;
			
		case FILL:
			mjPos=mj(low);
			break;
		}
	}
	
	auto i=b ? children.end() : children.begin();
	auto end=b ? children.begin() : children.end();
	
	while (i!=end)
	{
		if (b)
			--i;
		
		double mjLow=0, mjHgh=0, mnLow=0, mnHgh=0;
		double mnSize=mn((*i)->getDim());
		double mjSize=mj((*i)->getDim());
		
		switch (minorAlign)
		{
		case LEADING:
			mnLow=mn(low);
			mnHgh=mnLow+mnSize;
			break;
		
		case TRAILING:
			mnHgh=mn(hgh);
			mnLow=mnHgh-mnSize;
			break;
			
		case CENTER:
		case SPACE:
			mnLow=(mn(low)+mn(hgh)-mnSize)/2.0;
			mnHgh=(mn(low)+mn(hgh)+mnSize)/2.0;
			break;
			
		case FILL:
			mnLow=mn(low);
			mnHgh=mn(hgh);
			break;
		}
		
		mjLow=mjPos;
		
		mjPos+=mjSize;
		
		mjHgh=mjPos;
		
		mjPos+=innerBuffer;
		
		if (h)
			(*i)->setRect(V2d(mjLow, mnLow), V2d(mjHgh, mnHgh));
		else
			(*i)->setRect(V2d(mnLow, mjLow), V2d(mnHgh, mjHgh));
		
		if (!b)
			++i;
	}
}

}



