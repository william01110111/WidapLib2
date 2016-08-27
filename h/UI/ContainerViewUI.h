
#pragma once

#include "ViewUI.h"
#include <vector>

namespace widap
{

class ContainerViewUI: public ViewUI
{
public:
	
	void draw();
	void update();
	
	void addChild(ViewUI * childIn);
	void removeChild(ViewUI * childIn);
	
protected:
	
	//sets the rect the view will be drawn in, also, needs to set the rect on any subviews
	virtual void setRect(const V2d& lowIn, const V2d& hghIn)=0;
	
	virtual void drawFrame() {}
	virtual void updateFrame() {}
	
	std::vector<ViewUI *> children;
};

}

