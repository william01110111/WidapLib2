#pragma once

namespace widap
{

struct ConstraintUI
{
public:
	
	//if this constraint is active
	bool on;
	
	//if it is a rateo of the parent view, otherwise it is assumed to be in pixels (not valid for every value)
	bool relative;
	
	//the value of this constraint
	double val;
	
	ConstraintUI()
	{
		on=false;
		val=0;
	}
	
	ConstraintUI(double valIn)
	{
		on=true;
		val=valIn;
	}
	
	double get(double base)
	{
		if (relative)
		{
			return val*base;
		}
		else
		{
			return val;
		}
	}
	
	operator bool()
	{
		return on;
	}
	
	operator double()
	{
		return val;
	}
	
	operator int()
	{
		return val;
	}
	
	operator float()
	{
		return val;
	}
};

struct ConstraintsUI
{
	ConstraintUI left, right, btm, top;
	ConstraintUI rightSpace, topSpace;
	ConstraintUI centerX, centerY;
	ConstraintUI width, height;
	ConstraintUI aspectRatio;
};

}

