


///this file contains declarations and implementation of 3D vectors

#pragma once

#include "Vector2D.h"

namespace widap
{

template<typename T>
class V3 //vector 3D
{
public:
	
	T x, y, z;
	
	///constructors
	
	//default constructor
	inline V3() {x=0; y=0; z=0;}
	
	//copy constructor
	inline V3(const V2<T>& in) {x=in.x; y=in.y; z=in.z;}
	
	//constructor with a single value
	inline V3(T in) {x=in; y=in; z=in;}
	
	//constructor with values
	inline V3(T xIn, T yIn, T zIn) {x=xIn; y=yIn; z=zIn;}
	
	inline V3<T> copy() {return V3<T>(x, y, z);}
	
	
	///mscl
	
	//set vars to zero
	inline void zero() {x=0; y=0; z=0;}
	
	//distance from the origin to this point
	inline double dst() {return sqrt(x*x+y*y+z*z);}
	
	//distance to another point
	inline double dst(V3<T> in) {return sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y))+(z-in.z)*(z-in.z);}
	
	//simply return the distance squared
	inline double dstSquared() {return x*x+y*y+z*z;}
	
	//return the area, or x*y
	inline T area() {return x*y*z;}
	
	//returns this vector with a length of 1
	inline V3 normalized()
	{
		T dvdr=dst();
		return Vctr3(x/dvdr, y/dvdr, z/dvdr);
	}
	
	//returns each component clamped
	inline V3 clamp(V3 low, V3 hgh)
	{
		return V3
		(
			x<low.x?low.x:(x>hgh.x?hgh.x:x),
			y<low.y?low.y:(y>hgh.y?hgh.y:y),
			z<low.z?low.z:(z>hgh.z?hgh.z:z)
		);
	}
	
	//returns the minimum of each component
	inline V3 min(V3 in)
	{
		return V3
		(
			x>in.x?in.x:x,
			y>in.y?in.y:y,
			z>in.z?in.z:z
		);
	}
	
	//sets vector to the maximum of each component
	inline V3 max(V3 in)
	{
		return V3
		(
			x<in.x?in.x:x,
			y<in.y?in.y:y,
			z<in.z?in.z:z
		);
	}
	
	
	///convert to 2D
	
	inline V2<T> xy() {return V2<T>(x, y);}
	inline V2<T> xz() {return V2<T>(x, z);}
	inline V2<T> yz() {return V2<T>(y, z);}
	inline V2<T> zy() {return V2<T>(z, y);}
	
	
	///casting
	
	template<typename U>
	inline operator V3<U>() {return V3<U>(x, y, z);}
	
	inline operator bool() {return ((bool)x || (bool)y || (bool)z);}
	
	template<typename U>
	inline operator U(){return dst();}
	
	
	///other operators
	
	template<typename U>
	inline void operator= (V3<U> in) {x=in.x; y=in.y; z=in.z;}
	
	template<typename U>
	inline void operator= (U in) {x=in; y=in; z=in;}
	
	template<typename U>
	inline bool operator== (V3<U> in) {return x==in.x && y==in.y && z==in.z;}
	
	template<typename U>
	inline bool operator!= (V3<U> in) {return x!=in.x || y!=in.y || z!=in.z;}
	
	template<typename U>
	inline V3<T> operator+ (V3<U> in) {return V3<T>(x+in.x, y+in.y, z+in.z);}
	
	template<typename U>
	inline V3<T> operator- (V3<U> in) {return V3<T>(x-in.x, y-in.y, z-in.z);}
	
	template<typename U>
	inline V3<T> operator* (U in) {return V3<T>(x*in, y*in, z*in);}
	
	template<typename U>
	inline V3<T> operator/ (U in) {return V3<T>(x/in, y/in, z/in);}
	
	template<typename U>
	inline void operator+= (V3<U> in) {x+=in.x; y+=in.y; z+=in.z;}
	
	template<typename U>
	inline void operator-= (V3<U> in) {x-=in.x; y-=in.y; z-=in.z;}
	
	template<typename U>
	inline void operator*= (U in) {x*=in; y*=in; z*=in;}
	
	template<typename U>
	inline void operator/= (U in) {x/=in; y/=in; z/=in;}
	
	///3D math
	
	//dot product
	inline T dot(const V3& b)
	{
		return x*b.x+y*b.y+z*b.z;
	}
	
	//cross product
	inline V3<T> cross(const V3& b)
	{
		return Vctr3(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
	}
	
	///special cases
	
	#ifdef __Leap_h__
	operator Leap::Vector() {return Leap::Vector(x, y, z);}
	inline V3(Leap::Vector in) {x=in.x; y=in.y; z=in.z;}
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



