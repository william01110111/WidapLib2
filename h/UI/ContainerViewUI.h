
#pragma once

#include "ViewUI.h"
#include <list>

namespace widap
{

class ContainerViewUI: public ViewUI
{

///for clients to use

public:
	
	void addChild(ViewUI * childIn);
	void removeChild(ViewUI * childIn);

///for subclasses to override

protected:
	
	//sets the rects of all the children
	virtual void setChildRects()=0;
	
	virtual void drawFrame() {}
	virtual void updateFrame() {}
	

///for subclasses to use

protected:
	
	std::list<ViewUI*> children;
	

///internal

public:
	
	void draw();
	void update();
	
	void childChanged()
	{
		if (!calcAndSetDim())
			setChildRects();
	}
	
protected:
	
	void rectChanged() {setChildRects();};
	
private:
	
	void ioChanged();
};

}

