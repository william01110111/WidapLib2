
#include "../../h/UI/ViewUI.h"
#include "../../h/UI/ContainerViewUI.h"

namespace widap
{

void ViewUI::setRect(const V2d& lowIn, const V2d& hghIn)
{
	low=lowIn;
	hgh=hghIn;
}

void ViewUI::setDim(const V2d& in)
{
	//if (dim!=in)
	{
		dim=in;
		
		if (parent)
			parent->calcDim();
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
	}
}

void ViewUI::calcDim()
{
	setDim(V2d(500, 700));
}

}

