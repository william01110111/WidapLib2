
#pragma once

#include "../Graphics/Surface.h"
#include "../Window/InputSource.h"

namespace widap
{

class ContainerViewUI;

class ViewUI
{
public:
	
	void setParent(ContainerViewUI * parentIn);
	
	void setSurface(Surface * surfaceIn) {surface=surfaceIn;}
	void setInput(InputSource * inputIn) {input=inputIn;}
	void setIO(Surface * surfaceIn, InputSource * inputIn) {surface=surfaceIn; input=inputIn;}
	
	//draws it to the surface inside the rectangel
	virtual void draw(V2d low, V2d hgh)=0;
	void draw() {draw(V2d(), surface->getDim());}
	
	//updates input based on the input source inside the rectangle
	virtual void update(V2d low, V2d hgh)=0;
	void update() {draw(V2d(), surface->getDim());}
	
	
protected:
	
	Surface * surface=nullptr;
	InputSource * input=nullptr;
	
	ContainerViewUI * parent=nullptr;
};

}


