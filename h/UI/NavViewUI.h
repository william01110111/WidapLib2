#pragma once

#include "ContainerViewUI.h"

#include <functional>

namespace widap
{

struct StackAction;

class NavViewUI: public ContainerViewUI
{
public:
	
	void pushView(ViewUI * viewIn);
	void popView();
	
	std::function<void ()> pushViewLambda(ViewUI * in) {return [=]()->void{pushView(in);};}
	std::function<void ()> popViewLambda() {return [this](){popView();};}
	
	virtual void update();
	
protected:
	
	virtual void setChildRects();
	
	std::list<StackAction*> stackActions;
};

}

