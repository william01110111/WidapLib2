
#pragma once

#include "ContainerViewUI.h"

namespace widap
{

class ListViewUI: public ContainerViewUI
{
public:
	
	void addChild(ViewUI * childIn) {addChildToList(childIn);}
	void removeChild(ViewUI * childIn) {removeChildFromList(childIn);}
	
	void setCenter(V2b centerIn) {center=centerIn; setChildRects();}
	void setBuffer(V2d in) {buffer=in; setChildRects();}
	
protected:
	
	void setChildRects();
	void setRectsForRow(std::list<ViewUI*>::const_iterator * i, V2d * low, V2d * hgh);
	
	V2b center={false, false}; //if to center on either axis (y center centers indevidual components on a row, the whole list can not be centered)
	
	V2d buffer={12, 12}; //the buffer between items
};

}

