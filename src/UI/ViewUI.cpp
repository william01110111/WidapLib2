
#include "../../h/UI/ViewUI.h"
#include "../../h/UI/ContainerViewUI.h"

namespace widap
{

void ViewUI::calcSizes()
{
	if (!parent)
	{
		low=V2d();
		
		if (surface)
			hgh=surface->getDim();
		else
			hgh=V2d();
	}
}

}

