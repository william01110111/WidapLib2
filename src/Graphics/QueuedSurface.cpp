#include "../../h/Graphics/QueuedSurface.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

template <typename T>
class QueuedSurface::SetClrOp: public QueuedSurface::Operation
{
public:
	SetClrOp(T in, double alphaIn)
	{
		data=in;
		alpha=alphaIn;
	}
	
	void draw(QueuedSurface * queued)
	{
		queued->parent->setDrawClr(data, alpha);
	}
	
private:
	T data;
	double alpha;
};

class QueuedSurface::ClearOp: public QueuedSurface::Operation
{
public:
	ClearOp()
	{}
	
	void draw(QueuedSurface * queued)
	{
		if (!queued->pos && queued->dim==queued->parent->getDim())
			queued->parent->clear();
		else
			queued->parent->rect(queued->pos, queued->pos+queued->dim);
	}
};

class QueuedSurface::RectOp: public QueuedSurface::Operation
{
public:
	RectOp(V2d lowIn, V2d hghIn)
	{
		low=lowIn;
		hgh=hghIn;
	}
	
	void draw(QueuedSurface * queued)
	{
		queued->parent->rect(low+queued->pos, hgh+queued->pos);
	}
	
private:
	V2d hgh, low;
};

class QueuedSurface::CircleOp: public QueuedSurface::Operation
{
public:
	CircleOp(V2d centerIn, double radiusIn)
	{
		center=centerIn;
		radius=radiusIn;
	}
	
	void draw(QueuedSurface * queued)
	{
		queued->parent->circle(center+queued->pos, radius);
	}
	
private:
	V2d center;
	double radius;
};

class QueuedSurface::TriOp: public QueuedSurface::Operation
{
public:
	TriOp(V2d * vertsIn)
	{
		//class must use its own array in case the pointers become invalid
		verts[0]=*(vertsIn+0);
		verts[1]=*(vertsIn+1);
		verts[2]=*(vertsIn+2);
	}
	
	void draw(QueuedSurface * queued)
	{
		verts[0]+=queued->pos;
		verts[1]+=queued->pos;
		verts[2]+=queued->pos;
		queued->parent->tri(verts);
	}
	
private:
	V2d verts[3];
};

class QueuedSurface::LineOp: public QueuedSurface::Operation
{
public:
	LineOp(V2d startIn, V2d endIn, double thickIn)
	{
		start=startIn;
		end=endIn;
		thick=thickIn;
	}
	
	void draw(QueuedSurface * queued)
	{
		queued->parent->line(start+queued->pos, end+queued->pos, thick);
	}
	
private:
	V2d start;
	V2d end;
	double thick;
};

class QueuedSurface::SurfaceOp: public QueuedSurface::Operation
{
public:
	SurfaceOp(Surface * surfaceIn, V2d posIn)
	{
		surface=surfaceIn;
		pos=posIn;
	}
	
	void draw(QueuedSurface * queued)
	{
		queued->parent->surfaceWithAlphaSet(surface, pos+queued->pos);
	}
	
private:
	Surface * surface;
	V2d pos;
};

void QueuedSurface::setParent(Surface * surfaceIn)
{
	parent=surfaceIn;
	pos=V2d();
	dim=surfaceIn->getDim();
}

void QueuedSurface::setParent(Surface * surfaceIn, V2d posIn, V2u dimIn)
{
	parent=surfaceIn;
	pos=posIn;
	dim=dimIn;
}

void QueuedSurface::textInit() {}

void QueuedSurface::setDrawClr(bool clrIn)
{
	operations.push_back(new SetClrOp<bool>(clrIn, drawAlpha));
}

void QueuedSurface::setDrawClr(char clrIn)
{
	operations.push_back(new SetClrOp<char>(clrIn, drawAlpha));
}

void QueuedSurface::setDrawClr(int clrIn)
{
	operations.push_back(new SetClrOp<int>(clrIn, drawAlpha));
}

void QueuedSurface::setDrawClr(ClrBGR clrIn)
{
	operations.push_back(new SetClrOp<ClrBGR>(clrIn, drawAlpha));
}

void QueuedSurface::setDrawClr(ClrRGBA clrIn)
{
	operations.push_back(new SetClrOp<ClrRGBA>(clrIn, drawAlpha));
}

void QueuedSurface::setDrawClr(ClrHSL clrIn)
{
	operations.push_back(new SetClrOp<ClrHSL>(clrIn, drawAlpha));
}

void QueuedSurface::clear()
{
	operations.push_back(new ClearOp());
}

void QueuedSurface::rect(V2d low, V2d hgh)
{
	operations.push_back(new RectOp(low, hgh));
}

void QueuedSurface::circle(V2d center, double radius)
{
	operations.push_back(new CircleOp(center, radius));
}

void QueuedSurface::tri(V2d * vertsIn)
{
	operations.push_back(new TriOp(vertsIn));
}

void QueuedSurface::line(V2d start, V2d end, double thick)
{
	operations.push_back(new LineOp(start, end, thick));
}

void QueuedSurface::surfaceWithAlphaSet(Surface * other, V2d pos)
{
	operations.push_back(new SurfaceOp(other, pos));
}

void QueuedSurface::draw()
{
	std::list<Operation *>::const_iterator i;
	
	for (i=operations.begin(); i!=operations.end(); ++i)
	{
		(*i)->draw(this);
		delete (*i);
		
		//err << "list item" << err;
	}
	
	//err << "clearing list" << err;
	
	operations.clear();
}

}


