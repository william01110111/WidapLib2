
#include "../../h/UI/ListViewUI.h"
#include "../../h/Math/SimpMath.h"

namespace widap
{

void ListViewUI::setChildRects()
{
	V2d low=buffer+getLow(), hgh=-buffer+getHgh();
	
	double x=low.x, yTop=low.y, yBtm=low.y;
	
	for (auto i=children.begin(); i!=children.end(); i++)
	{
		V2d dim=(*i)->getDim();
		V2b stretch=(*i)->getStretch();
		
		if (x+dim.x>hgh.x && x>low.x)
		{
			x=low.x;
			yBtm=yTop+buffer.y;
		}
		
		V2d lowOut(x, yBtm), hghOut;
		
		if (stretch.x || x+dim.x>hgh.x)
		{
			hghOut.x=hgh.x;
		}
		else
		{
			hghOut.x=x+dim.x;
		}
		
		x=hghOut.x+buffer.x;
		
		if (!stretch.y || dim.y+yBtm>hghOut.y)
		{
			hghOut.y=yBtm+dim.y;
			
			if (hghOut.y>=hgh.y)
				hghOut.y=hgh.y;
			
			yTop=max(yTop, hghOut.y);
		}
		else
		{
			hghOut.y=yTop;
		}
		
		(*i)->setRect(lowOut, hghOut);
	}
}

void ListViewUI::setRectsForRow(std::list<ViewUI*>::const_iterator * i, V2d * low, V2d * hgh)
{
	//auto start=*i;
	
	while (true)
	{
		if (*i==children.end())
			break;
		
		if ((**i)->getStretch().x)
		
		i++;
	}
}

}


