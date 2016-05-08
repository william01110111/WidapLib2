

///this file contains declarations and implementation of 3D vectors

#pragma once

#include "Vector2D.h"

namespace widap
{

template<typename T>
class V3 : public V<T> //vector 3D
{
public:
	
	T x, y, z;
	
	
	///constructors
	
	//default constructor
	V3() {x=0; y=0; z=0;}
	
	//copy constructor
	V3(const V2<T>& in) {x=in.x; y=in.y; z=in.z;}
	
	//constructor with a single value
	V3(T in) {x=in; y=in; z=in;}
	
	//constructor with values
	V3(T xIn, T yIn, T zIn) {x=xIn; y=yIn; z=zIn;}
	
	
	///mscl
	
	//distance from the origin to this point
	double dst() {return sqrt(x*x+y*y+z*z);}
	
	//distance to another point
	double dst(V3<T> in) {return sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y))+(z-in.z)*(z-in.z);}
	
	//set all values to 0
	void zero() {x=0; y=0; z=0;}
	
	//return the area, or x*y
	T area() {return x*y*z;}
	
	//clamps each component
	void clamp(V3 low, V3 hgh)
	{
		if (x<low.x)
			x=low.x;
		
		if (y<low.y)
			y=low.y;
		
		if (z<low.z)
			z=low.z;
		
		if (x>hgh.x)
			x=hgh.x;
		
		if (y>hgh.y)
			y=hgh.y;
		
		if (z>hgh.z)
			z=hgh.z;
	}
	
	//sets vector to the minimum of each component
	void min(V3 in)
	{
		if (x>in.x)
			x=in.x;
		
		if (y>in.y)
			y=in.y;
		
		if (z>in.z)
			z=in.z;
		
	}
	
	//sets vector to the maximum of each component
	void max(V3 in)
	{
		if (x<in.x)
			x=in.x;
		
		if (y<in.y)
			y=in.y;
		
		if (z<in.z)
			z=in.z;
	}
	
	
	///convert to 2D
	
	V2<T> xy() {return V2<T>(x, y);}
	V2<T> xz() {return V2<T>(x, z);}
	V2<T> yz() {return V2<T>(y, z);}
	V2<T> zy() {return V2<T>(z, y);}
	
	
	///casting
	
	template<typename U>
	operator V3<U>() {return V3<U>(x, y, z);}
	
	operator bool() {return ((bool)x || (bool)y || (bool)z);}
	
	template<typename U>
	operator U(){return dst();}
	
	
	///other operators
	
	template<typename U>
	void operator= (V3<U> in) {x=in.x; y=in.y; z=in.z;}
	
	template<typename U>
	void operator= (U in) {x=in; y=in; z=in;}
	
	template<typename U>
	bool operator== (V3<U> in) {return x==in.x && y==in.y && z==in.z;}
	
	template<typename U>
	bool operator!= (V3<U> in) {return x!=in.x || y!=in.y || z!=in.z;}
	
	template<typename U>
	V3<T> operator+ (V3<U> in) {return V3<T>(x+in.x, y+in.y, z+in.z);}
	
	template<typename U>
	V3<T> operator- (V3<U> in) {return V3<T>(x-in.x, y-in.y, z-in.z);}
	
	template<typename U>
	V3<T> operator* (U in) {return V3<T>(x*in, y*in, z*in);}
	
	template<typename U>
	V3<T> operator/ (U in) {return V3<T>(x/in, y/in, z/in);}
	
	template<typename U>
	void operator+= (V3<U> in) {x+=in.x; y+=in.y; z+=in.z;}
	
	template<typename U>
	void operator-= (V3<U> in) {x-=in.x; y-=in.y; z-=in.z;}
	
	template<typename U>
	void operator*= (U in) {x*=in; y*=in; z*=in;}
	
	template<typename U>
	void operator/= (U in) {x/=in; y/=in; z/=in;}
	
	
	///special cases
	
	#ifdef __Leap_h__
	operator Leap::Vector() {return Leap::Vector(x, y, z);}
	V3(Leap::Vector in) {x=in.x; y=in.y; z=in.z;}
	#endif // __Leap_h__
	
};
typedef V3<int> V3i;
typedef V3<unsigned int> V3u;
typedef V3<double> V3d;

//returns the distance between the two vectors
template<typename T>
inline double dst(V3<T>& a, V3<T>& b)
{
	return (a-b).dst();
}

//returns the first vector clamped between the other two
template<typename T>
inline V3<T> clamp(V3<T> in, V3<T> low, V3<T> hgh)
{
	if (in.x>hgh.x)
		in.x=hgh.x;
	else if (in.x<low.x)
		in.x=low.x;
	
	if (in.y>hgh.y)
		in.y=hgh.y;
	else if (in.y<low.y)
		in.y=low.y;
	
	if (in.z>hgh.z)
		in.z=hgh.z;
	else if (in.z<low.z)
		in.z=low.z;
	
	return in;
}

//return a new vector with the minimum of each component
template<typename T>
inline V3<T> min(V3<T> a, V3<T> b)
{
	return V3<T>(a.x<b.x?a.x:b.x, a.y<b.y?a.y:b.y, a.z<b.z?a.z:b.z);
}

//return a new vector with the maximum of each component
template<typename T>
inline V3<T> max(V3<T> a, V3<T> b)
{
	return V3<T>(a.x>b.x?a.x:b.x, a.y>b.y?a.y:b.y, a.z>b.z?a.z:b.z);
}

//return a new vector that is in
inline V3d lerp(V3d in, V3d inLow, V3d inHgh, V3d outLow, V3d outHgh)
{
	return V3d(
		inLow.x==inHgh.x?outHgh.x:((in.x-inLow.x)*(outLow.x-outHgh.x))/(inLow.x-inHgh.x)+outLow.x,
		inLow.y==inHgh.y?outHgh.y:((in.y-inLow.y)*(outLow.y-outHgh.y))/(inLow.y-inHgh.y)+outLow.y,
		inLow.z==inHgh.z?outHgh.z:((in.z-inLow.z)*(outLow.z-outHgh.z))/(inLow.z-inHgh.z)+outLow.z);
}

}



