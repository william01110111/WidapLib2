
#include "../../h/Graphics/DirectDrawSurface.h"
#include "../../h/Mscl/Error.h"

namespace widap
{


void DirectDrawSurface::setParent(Surface * surfaceIn)
{
	parent=surfaceIn;
	pos=V2d();
	dim=surfaceIn->getDim();
}

void DirectDrawSurface::setParent(Surface * surfaceIn, V2d posIn, V2u dimIn)
{
	parent=surfaceIn;
	pos=posIn;
	dim=dimIn;
}

void DirectDrawSurface::textInit() {}

void DirectDrawSurface::setDrawClr(bool clrIn)
{
	parent->setDrawClr(clrIn);
}

void DirectDrawSurface::setDrawClr(char clrIn)
{
	parent->setDrawClr(clrIn);
}

void DirectDrawSurface::setDrawClr(int clrIn)
{
	parent->setDrawClr(clrIn);
}

void DirectDrawSurface::setDrawClr(ClrBGR clrIn)
{
	parent->setDrawClr(clrIn);
}

void DirectDrawSurface::setDrawClr(ClrRGBA clrIn)
{
	parent->setDrawClr(clrIn);
}

void DirectDrawSurface::setDrawClr(ClrHSL clrIn)
{
	parent->setDrawClr(clrIn);
}

void DirectDrawSurface::clear()
{
	parent->clear();
}

void DirectDrawSurface::rect(V2d low, V2d hgh)
{
	parent->rect(low, hgh);
}

void DirectDrawSurface::circle(V2d center, double radius)
{
	parent->circle(center, radius);
}

void DirectDrawSurface::tri(V2d * vertsIn)
{
	parent->tri(vertsIn);
}

void DirectDrawSurface::line(V2d start, V2d end, double thick)
{
	parent->line(start, end, thick);
}

void DirectDrawSurface::surfaceWithAlphaSet(Surface * other, V2d pos)
{
	parent->surfaceWithAlphaSet(other, pos);
}

}


