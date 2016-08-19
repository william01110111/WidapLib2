
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
	
	
	//recalculate the size of all subviews
	virtual void calcSizes();
	
	//draws it to the surface inside the rectangle
	virtual void draw()=0;
	
	//updates input based on the input source inside the rectangle
	virtual void update()=0;
	
	
protected:
	
	Surface * surface=nullptr;
	InputSource * input=nullptr;
	
	//the rectangle where it will be drawn and get input, set by the parent
	V2d low, hgh;
	
	ContainerViewUI * parent=nullptr;
};

}

#include "ContainerViewUI.h"


