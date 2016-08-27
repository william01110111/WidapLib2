
#include "../../h/UI/ScatterViewUI.h"
#include "../../h/Math/SimpMath.h"

namespace widap
{

void ScatterViewUI::setRect(const V2d& lowIn, const V2d& hghIn)
{
	ViewUI::setRect(lowIn, hghIn);
	const V2d& low=lowIn, hgh=hghIn;
	
	double x=low.x, yTop=low.y, yBtm=low.y;
	
	for (unsigned i=0; i<children.size(); ++i)
	{
		V2d dim=children[i]->getDim();
		V2d stretch=children[i]->getStretch();
		
		if (x+dim.x>hgh.x && x>low.x)
		{
			x=low.x;
			yBtm=yTop;
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
		
		x=hghOut.x;
		
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
		
		children[i]->setRect(lowOut, hghOut);
	}
}

}

