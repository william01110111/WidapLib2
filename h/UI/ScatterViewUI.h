#pragma once

#include "ContainerViewUI.h"

namespace widap
{

class ScatterViewUI: public ContainerViewUI
{
public:
	
	void addChild(ViewUI * childIn) {addChildToList(childIn);}
	void removeChild(ViewUI * childIn) {removeChildFromList(childIn);}
	
protected:
	
	void setChildRects();
	
};

}

