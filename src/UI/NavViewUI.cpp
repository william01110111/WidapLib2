
#include "../../h/UI/NavViewUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

struct StackAction
{
	StackAction(ViewUI * in)
	{
		view=in;
	}
	
	ViewUI * view;
};

void NavViewUI::pushView(ViewUI * viewIn)
{
	if (viewIn)
		stackActions.push_back(new StackAction(viewIn));
}

void NavViewUI::popView()
{
	stackActions.push_back(new StackAction(nullptr));
}

void NavViewUI::update()
{
	if (!stackActions.empty())
	{
		for (std::list<StackAction*>::iterator i=stackActions.begin(); i!=stackActions.end(); ++i)
		{
			if ((*i)->view) //push
			{
				addChildToList((*i)->view);
			}
			else //pop
			{
				if (children.empty())
				{
					err << "nav view empty when trying to pop" << err;
					return;
				}
				
				removeChildFromList(children.back());
			}
			
			delete *i;
		}
		
		stackActions.clear();
	}
	
	ContainerViewUI::update();
}

void NavViewUI::setChildRects()
{
	if (children.empty())
	{
		return;
	}
	
	auto i=children.end();
	i--;
	
	(*i)->setRect(getLow(), getHgh());
	
	while (i!=children.begin())
	{
		i--;
		(*i)->deactivate();
	}
	
}

}

