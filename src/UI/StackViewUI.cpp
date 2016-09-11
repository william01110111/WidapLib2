
#include "../../h/UI/StackViewUI.h"
#include "../../h/Math/SimpMath.h"
#include "../../h/Mscl/Error.h"

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

V2d StackViewUI::calcDim()
{
	double majorSize=0;
	int majorStretchNum=0;
	double minorSize=0;
	int minorStretchNum=0;
	
	for (auto i=children.begin(); i!=children.end(); i++)
	{
		if (mj((*i)->getStretch()))
			majorStretchNum++;
		
		majorSize+=mj((*i)->getDim());
		majorSize+=innerBuffer;
		
		if (mn((*i)->getStretch()))
			minorStretchNum++;
		
		minorSize=max(minorSize, mn((*i)->getDim()));
	}
	
	majorSize-=innerBuffer;
	
	V2d dim;
	
	if (h)
		dim=V2d(majorSize*(majorStretchNum>0?-1:1), minorSize*(minorStretchNum>0?-1:1));
	else
		dim=V2d(minorSize*(minorStretchNum>0?-1:1), majorSize*(majorStretchNum>0?-1:1));
	
	dim+=outerBuffer*2;
	
	return dim;
}

void StackViewUI::setChildRects()
{
	V2d low=outerBuffer+getLow(), hgh=-outerBuffer+getHgh();
	
	//if there is not enough room for anything, deactivate all views and return
	if (hgh.x<low.x || hgh.y<low.y)
	{
		for (auto i=children.begin(); i!=children.end(); i++)
		{
			(*i)->deactivate();
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
		double mnSize;
		
		if (mn((*i)->getStretch()))
			mnSize=max(mn(hgh)-mn(low), mn((*i)->getDim()));
		else
			mnSize=mn((*i)->getDim());
		
		double mjSize=mj((*i)->getDim());
		
		if (mj((*i)->getStretch()))
			mjSize+=((mj(hgh)-mj(low))-majorSize)/majorStretchNum;
		
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



