
#pragma once

#include "../Graphics/Surface.h"
#include "../Window/InputSource.h"
#include "../Window/WindowBase.h"

namespace widap
{

class ContainerViewUI;

class ViewUI
{
public:
	
	
	void setSurface(Surface * surfaceIn) {surface=surfaceIn;}
	void setInput(InputSource * inputIn) {input=inputIn;}
	void setIO(Surface * surfaceIn, InputSource * inputIn) {surface=surfaceIn; input=inputIn;}
	void setWindow(WindowBase * windowIn) {surface=windowIn; input=windowIn;}
	
	//draws it to the surface inside the rectangle
	virtual void draw()=0;
	
	//updates input based on the input source inside the rectangle
	virtual void update()=0;
	
	const V2d& getLow() {return low;}
	const V2d& getHgh() {return hgh;}
	
	V2d getDim() {return dim.abs();}
	V2b getStretch() {return V2b(dim.x<0, dim.y<0);}
	
	//calculate the dimensions of a View, automatically called on container views when the dimensions of a child changes
	virtual void calcDim();
	
	//sets the rect the view will be drawn in, also, needs to set the rect on any subviews
	virtual void setRect(const V2d& lowIn, const V2d& hghIn);
	
protected:
	
	void setDim(const V2d& in);
	
	Surface * surface=nullptr;
	InputSource * input=nullptr;
	
	ContainerViewUI * parent=nullptr;
	
private:
	
	//the rectangle where it will be drawn and get input, set by the parent, which is influenced by the constraints
	V2d low, hgh;
	
	//the requested dimensions, either or both can be negitive, meaning as big as possible, but at least the fabs() if it, some container views may not respect dim
	V2d dim={-200, -200};
};

}


