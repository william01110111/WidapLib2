
#pragma once

#include "ViewUI.h"
#include <vector>

namespace widap
{

class ContainerViewUI: public ViewUI
{
public:
	
	void addChild(ViewUI * childIn);
	void removeChild(ViewUI * childIn);
	
protected:
	
	std::vector<ViewUI *> children;
};

}

