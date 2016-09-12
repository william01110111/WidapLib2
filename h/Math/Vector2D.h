
///this file contains declarations and implementation of 2D vectors

#pragma once

#include <algorithm>
#include <string>
#include <math.h>

namespace widap
{

template<typename T>
class V2 //vector 2D
{
public:
	
	T x, y;
	
	///constructors
	
	//default constructor
	inline V2() {x=0; y=0;}
	
	//copy constructor
	inline V2(const V2<T>& in) {x=in.x; y=in.y;}
	
	//constructor with a single value
	//this causes a bunch of ambiguous calls when I want another constructor
	//V2(T in) {x=in; y=in;}
	
	//constructor with values
	inline V2(T xIn, T yIn) {x=xIn; y=yIn;}
	
	inline V2<T> copy() {return V2<T>(x, y);}
	
	
	///mscl
	
	//set vars to zero
	inline void zero() {x=0; y=0;}
	
	//distance from the origin to this point
	inline double dst() {return sqrt(x*x+y*y);}
	
	//simply return the distance squared
	inline double dstSquared() {return x*x+y*y;}
	
	//distance to another point
	inline double dst(V2<T> in) {return sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y));}
	
	//return the area, or x*y
	inline T area() {return x*y;}
	
	//return if this vector is in the rectangle created by the other two vectors
	inline bool isInRect(const V2& low, const V2& hgh) {return x>low.x && y>low.y && x<hgh.x && y<hgh.y;}
	
	//returns this vector with a length of 1
	inline V2 normalized()
	{
		T dvdr=dst();
		return V2(x/dvdr, y/dvdr);
	}
	
	//returns each component clamped
	inline V2 clamp(const V2& low, const V2& hgh)
	{
		return V2
		(
			x<low.x?low.x:(x>hgh.x?hgh.x:x),
			y<low.y?low.y:(y>hgh.y?hgh.y:y)
		);
	}
	
	//returns vector that is the minimum of each component
	inline V2 min(V2 in)
	{
		return V2
		(
			x>in.x?in.x:x,
			y>in.y?in.y:y
		);
	}
	
	//returns vector that is the maximum of each component
	inline V2 max(V2 in)
	{
		return V2
		(
			x<in.x?in.x:x,
			y<in.y?in.y:y
		);
	}
	
	//returns the absolute value of each component
	inline V2 abs()
	{
		return V2
		(
			x>=0?x:-x,
			y>=0?y:-y
		);
	}
	
	//dot product
	inline T dot(const V2& b)
	{
		return x*b.x+y*b.y;
	}
	
	///casting
	
	template<typename U>
	inline operator V2<U>() {return V2<U>(x, y);}
	
	inline operator std::string() {return std::string("(") + std::to_string(x) + " " + std::to_string(y) + ")";}
	
	inline operator bool() {return ((bool)x || (bool)y);}
	
	
	///other operators
	
	template<typename U>
	inline void operator= (V2<U> in) {x=in.x; y=in.y;}
	
	template<typename U>
	inline void operator= (U in) {x=in; y=in;}
	
	template<typename U>
	inline bool operator== (V2<U> in) {return x==in.x && y==in.y;}
	
	template<typename U>
	inline bool operator!= (V2<U> in) {return x!=in.x || y!=in.y;}
	
	template<typename U>
	inline V2<T> operator+ (V2<U> in) {return V2<T>(x+in.x, y+in.y);}
	
	template<typename U>
	inline V2<T> operator- (V2<U> in) {return V2<T>(x-in.x, y-in.y);}
	inline V2<T> operator- () {return V2<T>(-x, -y);}
	
	template<typename U>
	inline V2<T> operator* (U in) {return V2<T>(x*in, y*in);}
	
	template<typename U>
	inline V2<T> operator* (V2<U> in) {return V2<T>(x*in.x, y*in.y);}
	
	template<typename U>
	inline V2<T> operator/ (U in) {return V2<T>(x/in, y/in);}
	
	template<typename U>
	inline V2<T> operator/ (V2<U> in) {return V2<T>(x/in.x, y/in.y);}
	
	template<typename U>
	inline void operator+= (V2<U> in) {x+=in.x; y+=in.y;}
	
	template<typename U>
	inline void operator-= (V2<U> in) {x-=in.x; y-=in.y;}
	
	template<typename U>
	inline void operator*= (U in) {x*=in; y*=in;}
	
	template<typename U>
	inline void operator*= (V2<U> in) {x*=in.x; y*=in.y;}
	
	template<typename U>
	inline void operator/= (U in) {x/=in; y/=in;}
	
	template<typename U>
	inline void operator/= (V2<U> in) {x/=in.x; y/=in.y;}
	
};
typedef V2<bool> V2b;
typedef V2<char> V2c;
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
		inLow.x==inHgh.x?outHgh.x:((in.x-inLow.x)*(outHgh.x-outLow.x))/(inHgh.x-inLow.x)+outLow.x,
		inLow.y==inHgh.y?outHgh.y:((in.y-inLow.y)*(outHgh.y-outLow.y))/(inHgh.y-inLow.y)+outLow.y);
}

inline V2d lerp(double in, double inLow, double inHgh, V2d outLow, V2d outHgh)
{
	return ((inLow==inHgh)?outHgh:((outHgh-outLow)*(in-inLow))/(inHgh-inLow)+outLow);
}

inline V2d lerp(double in, V2d outLow, V2d outHgh)
{
	return ((outHgh-outLow)*(in))+outLow;
}

}



