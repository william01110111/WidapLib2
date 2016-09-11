
#include "../../h/UI/ViewUI.h"
#include "../../h/UI/ContainerViewUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

void ViewUI::setRect(const V2d& lowIn, const V2d& hghIn)
{
	low=lowIn;
	hgh=hghIn;
	setActive(true);
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
				deactivate();
			}
		}
		
		return true;
	}
}

void ViewUI::setActive(bool in)
{
	if (active!=in)
	{
		active=in;
		
		activeChanged(in);
	}
}

V2d ViewUI::calcDim()
{
	return V2d(-100, -100);
}

}

