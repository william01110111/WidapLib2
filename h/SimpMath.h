
#pragma once

#include <math.h> //lots if math stuff
#include <cstdlib> //rand
#include <algorithm> //min/max and probably other stuff

namespace widap
{

const double PI=3.14159265358979323846;

using std::min;
using std::max;

//distance from the origin to a point
inline double dst (double in0, double in1)
{
    return sqrt(in0*in0+in1*in1);
}

//converts degrees to radians
inline double deg2rad(double inpt)
{
	return inpt*PI/180;
}

//converts radians to degrees
inline double rad2deg(double inpt)
{
	return inpt*180/PI;
}

//lerp (linear interpolation (formally called grdnt)) returns a number between outLow and outHgh in proportion to where in is between inLow and inHgh (output is not clamped)
inline double lerp(double in, double inLow, double inHgh, double outLow, double outHgh)
{
	if (inLow==inHgh) //stop a possible divide by 0
		return outHgh; //making this outHgh is arbitrary, but its as good as anything
	else
		return ((in-inLow)*(outLow-outHgh))/(inLow-inHgh)+outLow;
}

//simply clamps the output between two inputs, assumes low is less then hgh
template <typename T>
T clamp(T in, T low, T hgh)
{
	if (in>=low && in<=hgh)
		return in;
	else if (in>hgh)
		return hgh;
	else
		return low;
}

//returns a random number between 0 and 1 (uses rand so fast as hell but no guarantee of even distribution)
inline double drand(double low, double hgh)
{
	//uses rand() but returns a double between low and high
	if (low==hgh)
		return low;

	else
		return (double)rand()/(RAND_MAX/(hgh-low))+low;
}

}

