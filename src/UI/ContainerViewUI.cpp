#include "../../h/UI/ContainerViewUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

void ContainerViewUI::draw()
{
	for (unsigned i=0; i<children.size(); ++i)
	{
		children[i]->draw();
	}
	
	drawFrame();
}

void ContainerViewUI::update()
{
	for (unsigned i=0; i<children.size(); ++i)
	{
		children[i]->update();
	}
	
	updateFrame();
}

void ContainerViewUI::addChild(ViewUI * childIn)
{
	children.push_back(childIn);
	childIn->setIO(surface, input);
	
	((ContainerViewUI *)childIn)->parent=this;
	//thats right, I cast childIn to a type its not so I can get at a protected member of the base class
	//You think thats one of the worst C++ hacks you've ever seen? Well, fuck you!
	
	childIn->calcAndSetDim();
	
	childChanged();
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
	
	childIn->calcAndSetDim();
	
	childChanged();
}

void ContainerViewUI::ioChanged()
{
	for (unsigned i=0; i<children.size(); ++i)
	{
		children[i]->setIO(surface, input);
	}
}

}


