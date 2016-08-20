#pragma once

namespace widap
{

struct ConstraintUI
{
public:
	
	bool on;
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
	ConstraintUI left, right, top, btm;
	ConstraintUI centerX, centerY;
	ConstraintUI width, height;
	ConstraintUI aspectRatio;
};

}

