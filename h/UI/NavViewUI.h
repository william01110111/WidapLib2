#pragma once

#include "ContainerViewUI.h"
#include <list>

namespace widap
{

struct StackAction;

class NavViewUI: public ContainerViewUI
{
public:
	
	void pushView(ViewUI * viewIn);
	void popView();
	virtual void update();
	
protected:
	
	virtual void setChildRects();
	
	std::list<StackAction*> stackActions;
};

}

