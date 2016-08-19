
#pragma once

#include "ViewUI.h"
#include <vector>

namespace widap
{

class ContainerViewUI: public ViewUI
{
public:
	
	struct ChildView
	{
		V2d low, hgh;
		ViewUI * view;
	};
	
	void removeChild(ViewUI * viewIn);
	
protected:
	
	std::vector<ChildView> children;
};

}

