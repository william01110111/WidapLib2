#pragma once

#include "ChildSurface.h"
#include <list>

///this is a surface that saves draw commands that then can be drawn to the parent surface with the draw() method

namespace widap
{

class QueuedSurface: public ChildSurface
{
public:
	
	USING_SURFACE;
	
	QueuedSurface(Surface * surfaceIn): ChildSurface(surfaceIn) {}
	QueuedSurface(Surface * surfaceIn, V2d posIn, V2u dimIn): ChildSurface(surfaceIn, posIn, dimIn) {}
	
	void setParent(Surface * surfaceIn);
	void setParent(Surface * surfaceIn, V2d posIn, V2u dimIn);
	
	void textInit();
	
	virtual void setDrawClr(bool clrIn);
	virtual void setDrawClr(char clrIn);
	virtual void setDrawClr(int clrIn);
	virtual void setDrawClr(ClrBGR clrIn);
	virtual void setDrawClr(ClrRGBA clrIn);
	virtual void setDrawClr(ClrHSL clrIn);
	
	//fills the Surface with the predefined color
	void clear();
	
	//draw a rectangle with the preset draw color
	void rect(V2d low, V2d hgh);
	
	//draw a circle with the preset draw color
	void circle(V2d center, double radius);
	
	//draw a triangle
	void tri(V2d * vertsIn);
	
	//draw a line
	void line(V2d start, V2d end, double thick);
	
	//draw another surface, this will only work if the specific combination of types has been implemented
	void surfaceWithAlphaSet(Surface * other, V2d pos);
	
	void setDim(V2u dimIn) {dim=dimIn;}
	
	void draw();
	
private:
	
	class Operation
	{
	public:
		virtual void draw(QueuedSurface * surf)=0;
		virtual ~Operation() {};
	};
	
	template <typename T>
	class SetClrOp;
	
	class ClearOp;
	class RectOp;
	class CircleOp;
	class TriOp;
	class LineOp;
	class SurfaceOp;
	
	std::list<Operation *> operations;
};

}

