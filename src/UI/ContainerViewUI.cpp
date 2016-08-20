#include "../../h/UI/ContainerViewUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

void ContainerViewUI::addChild(ViewUI * childIn)
{
	children.push_back(childIn);
	calcSizes();
}

void ContainerViewUI::removeChild(ViewUI * childIn)
{
	std::vector<ViewUI *>::const_iterator i=children.begin();
	
	while ((*i)!=childIn)
	{
		if (i==children.end())
		{
			err << "attempted to remove child frim ViewUI, but couldn't find it" << err;
			return;
		}
		
		++i;
	}
	
	children.erase(i);
	
	calcSizes();
}

}


