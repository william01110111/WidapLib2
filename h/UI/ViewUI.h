
#pragma once

#include "../Graphics/Surface.h"
#include "../Window/InputSource.h"
#include "../Window/WindowBase.h"

namespace widap
{

class ContainerViewUI;

class ViewUI
{
	
///for clients to use
	
public:
	
	//sets the surface and input source that will be used for input/output, is automatically called on children of this view
	void setIO(Surface * surfaceIn, InputSource * inputIn) {surface=surfaceIn; input=inputIn; ioChanged();}
	void setWindow(WindowBase * windowIn) {setIO(windowIn, windowIn);}
	
	bool getIfActive() {return active;}
	
	//get the rect that this view is in
	const V2d& getLow() {return low;}
	const V2d& getHgh() {return hgh;}
	
	//get the dimensions this view wants to have
	V2d getDim() {return dim.abs();}
	V2b getStretch() {return V2b(dim.x<0, dim.y<0);}
	
	
///for subclasses to override
	
public:
	
	//draws it to the surface inside the rectangle
	virtual void drawBknd() {};
	virtual void draw()=0;
	
	//updates input based on the input source inside the rectangle
	virtual void update() {}
	
	//calculates and returns the dimensions of a view
	virtual V2d calcDim();
	
private:
	
	//called after the rect is changed with setRect
	virtual void rectChanged() {}
	
	virtual void activeChanged(bool active) {}
	

///for subclasses to use

public:
	
	//calculate and sets the dimensions of a View, returns false if the dimensions were already set correctly
	bool calcAndSetDim() {return setDim(calcDim());}
	
	virtual bool calcAndSetDimRecursive() {return setDim(calcDim());}
	
	//deactivates a view, currently should only be called by the view's parent, view is reactivated whenever setRect is called
	void deactivate() {setActive(false);}
	
protected:
	
	Surface * surface=nullptr;
	InputSource * input=nullptr;
	
///internal

public:
	
	virtual ~ViewUI() {}
	
	//sets the rect the view will be drawn in, also
	void setRect(const V2d& lowIn, const V2d& hghIn);
	
protected:
	
	//sets the dimensions, returns false if the dimensions were already set to the input
	bool setDim(const V2d& in);
	
	ContainerViewUI * parent=nullptr;
	
private:
	
	void setActive(bool in);
	
	//if this view will get input and be drawn
	bool active=false;
	
	//the rectangle where it will be drawn and get input, set by the parent, which is influenced by the constraints
	V2d low, hgh;
	
	//the requested dimensions, either or both can be negitive, meaning as big as possible, but at least the fabs() if it, some container views may not respect dim
	V2d dim={120, 120};
	
	virtual void ioChanged() {}
};

}


