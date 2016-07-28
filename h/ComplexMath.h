
#pragma once

#include "SimpMath.h"
#include "Vector2D.h"
#include "Vector3D.h"

namespace widap
{

//finds the prime factors and returns the number of them, it allocates the array but you must delete it
int findPrimeFactors(int num, int **answerArray);

//determins if the first point is in the triangle made by the other three points, order of the triangle doesn't matter
bool isInTriangle(V2d pt, V2d a, V2d b, V2d c);

//returns if the two line segments intersect
bool linesIntersect(V2d a, V2d b, V2d c, V2d d);

//returns if the first point is on the right side of the line when looking from the 2nd point to the third
bool isOnRightSideOfLine(V2d pt, V2d lStrt, V2d lEnd);

//return the distance to the closest point on a line
double dstToLine(V2d pt0, V2d pt1, V2d pt2);
double dstToLine(V3d pt0, V3d pt1, V3d pt2);

//find the position on the line (0-1 if between start and end) closest to the point
double posOnLine(V2d pt, V2d pt0, V2d pt1);
double posOnLine(V3d point, V3d lineStrt, V3d lineEnd);
 
//quickly solves a cubic equation (a*x^3 + b*x^2 + c*x + d) and returns the number of real roots. they are stored in the answer array
int solveCubic(double a, double b, double c, double d, double answer[3]);

}

