
#include "../../h/UI/ViewUI.h"
#include "../../h/UI/ContainerViewUI.h"

namespace widap
{

void ViewUI::setRect(const V2d& lowIn, const V2d& hghIn)
{
	low=lowIn;
	hgh=hghIn;
	rectChanged();
}

bool ViewUI::setDim(const V2d& in)
{	
	if (dim==in)
	{
		return false;
	}
	else
	{
		dim=in;
		
		if (parent)
		{
			parent->childChanged();
		}
		else
		{
			if (surface)
			{
				setRect(V2d(), surface->getDim());
			}
			else
			{
				setRect(V2d(), V2d());
			}
		}
		
		return true;
	}
}

V2d ViewUI::calcDim()
{
	return V2d(500, 700);
}

}

