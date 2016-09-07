#pragma once

#include "Surface.h"

///this is a surface that is retrieved from another
//this can be usefull for drawing to a specific part of the surface
//(preferably with clipping but that may not always be supported)
//or changing the order of draw commands

namespace widap
{

class ChildSurface: public Surface
{
public:
	
	USING_SURFACE;
	
	ChildSurface(Surface * surfaceIn) {parent=surfaceIn; pos=V2d(); dim=surfaceIn->getDim();}
	ChildSurface(Surface * surfaceIn, V2d posIn, V2u dimIn) {parent=surfaceIn; pos=posIn; dim=dimIn;}
	
	virtual ~ChildSurface() {}
	
	V2u getDim() {return dim;}
	V2d getPos() {return pos;}
	V2d getOffset() {return offset;}
	bool getLocalOrigin() {return localOrigin;}
	
	void setPos(V2d posIn)
	{
		pos=posIn;
		if (localOrigin)
			offset=posIn;
	}
	
	void setLocalOrigin(bool in)
	{
		localOrigin=in;
		
		if (in)
			offset=pos;
	}
	virtual void setDim(V2u dimIn)=0;
	void setRect(V2d low, V2d hgh) {setPos(low); setDim(ceil(hgh-low));}
	
	virtual void draw()=0;
	
protected:
	
	V2d pos; //where the lower left should be drawn
	V2d offset; //the offset applied to draw operations, (0, 0) means same as drawing to parent, same as pos means use its local origin
	V2u dim; //the dimensions of this child surface
	bool localOrigin=false; //if to set offset to pos whenever pos changes, otherwise offset will not change (default is 0)
	
	Surface * parent;
};

}

