
///this file contains declarations and implementation of 2D vectors

#pragma once

#include "Vector.h"
#include <algorithm>

namespace widap
{

template<typename T>
class V2 : public V<T> //vector 2D
{
public:
	
	T x, y;
	
	
	///constructors
	
	//default constructor
	V2() {x=0; y=0;}
	
	//copy constructor
	V2(const V2<T>& in) {x=in.x; y=in.y;}
	
	//constructor with a single value
	//this causes a bunch of ambiguous calls when I want another constructor
	//V2(T in) {x=in; y=in;}
	
	//constructor with values
	V2(T xIn, T yIn) {x=xIn; y=yIn;}
	
	
	///mscl
	
	//distance from the origin to this point
	double dst() {return sqrt(x*x+y*y);}
	
	//distance to another point
	double dst(V2<T> in) {return sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y));}
	
	//set all values to 0
	void zero() {x=0; y=0;}
	
	//return the area, or x*y
	T area() {return x*y;}
	
	V2<T> clone() {V2<T>(x, y);}
	
	//clamps each component
	void clamp(V2 low, V2 hgh)
	{
		if (x<low.x)
			x=low.x;
		
		if (y<low.y)
			y=low.y;
		
		if (x>hgh.x)
			x=hgh.x;
		
		if (y>hgh.y)
			y=hgh.y;
	}
	
	//sets vector to the minimum of each component
	void min(V2 in)
	{
		if (x>in.x)
			x=in.x;
		
		if (y>in.y)
			y=in.y;
		
	}
	
	//sets vector to the maximum of each component
	void max(V2 in)
	{
		if (x<in.x)
			x=in.x;
		
		if (y<in.y)
			y=in.y;
	}
	
	
	///casting
	
	template<typename U>
	operator V2<U>() {return V2<U>(x, y);}
	
	operator bool() {return ((bool)x || (bool)y);}
	
	
	///other operators
	
	template<typename U>
	void operator= (V2<U> in) {x=in.x; y=in.y;}
	
	template<typename U>
	void operator= (U in) {x=in; y=in;}
	
	template<typename U>
	bool operator== (V2<U> in) {return x==in.x && y==in.y;}
	
	template<typename U>
	bool operator!= (V2<U> in) {return x!=in.x || y!=in.y;}
	
	template<typename U>
	V2<T> operator+ (V2<U> in) {return V2<T>(x+in.x, y+in.y);}
	
	template<typename U>
	V2<T> operator- (V2<U> in) {return V2<T>(x-in.x, y-in.y);}
	
	template<typename U>
	V2<T> operator* (U in) {return V2<T>(x*in, y*in);}
	
	template<typename U>
	V2<T> operator* (V2<U> in) {return V2<T>(x*in.x, y*in.y);}
	
	template<typename U>
	V2<T> operator/ (U in) {return V2<T>(x/in, y/in);}
	
	template<typename U>
	V2<T> operator/ (V2<U> in) {return V2<T>(x/in.x, y/in.y);}
	
	template<typename U>
	void operator+= (V2<U> in) {x+=in.x; y+=in.y;}
	
	template<typename U>
	void operator-= (V2<U> in) {x-=in.x; y-=in.y;}
	
	template<typename U>
	void operator*= (U in) {x*=in; y*=in;}
	
	template<typename U>
	void operator*= (V2<U> in) {x*=in.x; y*=in.y;}
	
	template<typename U>
	void operator/= (U in) {x/=in; y/=in;}
	
	template<typename U>
	void operator/= (V2<U> in) {x/=in.x; y/=in.y;}
	
};
typedef V2<int> V2i;
typedef V2<unsigned int> V2u;
typedef V2<double> V2d;

//returns the distance between the two vectors
template<typename T>
inline double dst(V2<T>& a, V2<T>& b)
{
	return (a-b).dst();
}

//returns the first vector clamped between the other two
template<typename T>
inline V2<T> clamp(V2<T> in, V2<T> low, V2<T> hgh)
{
	if (in.x>hgh.x)
		in.x=hgh.x;
	else if (in.x<low.x)
		in.x=low.x;
	
	if (in.y>hgh.y)
		in.y=hgh.y;
	else if (in.y<low.y)
		in.y=low.y;
	
	return in;
}

//return a new vector with the minimum of each component
template<typename T>
inline V2<T> min(V2<T> a, V2<T> b)
{
	return V2<T>(a.x<b.x?a.x:b.x, a.y<b.y?a.y:b.y);
}

//return a new vector with the maximum of each component
template<typename T>
inline V2<T> max(V2<T> a, V2<T> b)
{
	return V2<T>(a.x>b.x?a.x:b.x, a.y>b.y?a.y:b.y);
}

//return a new vector floored
template<typename T>
inline V2<T> floor(V2<T> a)
{
	return V2<T>(std::floor(a.x), std::floor(a.y));
}

//return a new vector ceilinged
template<typename T>
inline V2<T> ceil(V2<T> a)
{
	return V2<T>(std::ceil(a.x), std::ceil(a.y));
}


//return a new vector that is in
inline V2d lerp(V2d in, V2d inLow, V2d inHgh, V2d outLow, V2d outHgh)
{
	return V2d(
		inLow.x==inHgh.x?outHgh.x:((in.x-inLow.x)*(outLow.x-outHgh.x))/(inLow.x-inHgh.x)+outLow.x,
		inLow.y==inHgh.y?outHgh.y:((in.y-inLow.y)*(outLow.y-outHgh.y))/(inLow.y-inHgh.y)+outLow.y);
}

}



