
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
	ContainerViewUI::update();
	
	for (std::list<StackAction*>::const_iterator i=stackActions.begin(); i!=stackActions.end(); i++)
	{
		if ((*i)->view) //push
		{
			(children.back())->setActive(false);
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
			
			if (!children.empty())
				children.back()->setActive(true);
		}
		
		delete (*i);
	}
	
	stackActions.clear();
}

void NavViewUI::setChildRects()
{
	for (std::list<ViewUI*>::const_iterator i=children.begin(); i!=children.end(); i++)
	{
		(*i)->setRect(getLow(), getHgh());
	}
}

}

