
///this file contains declarations and implementation the vector base class

#pragma once

#include <math.h>

namespace widap
{

template<typename T>
class V //vector base class
{
public:
	
	//use the distance formula
	virtual double dst()=0;
	
	//set all vars to zero
	virtual void zero()=0;
};

}


