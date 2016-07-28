
#include "../h/ComplexMath.h"
#include <vector>

namespace widap
{

using std::vector;

int findPrimeFactors(int num, int **factorArray) //finds the prime factors and returns the number of them, it allocates the array but you must delete it
{
	int i;
	int dividedNum=num;
	int iMax=ceil(sqrt(dividedNum));
	vector<int> factors;
	int factorNum;
	
	while (!(dividedNum%2))
	{
		dividedNum/=2;
		factors.push_back(2);
		iMax=ceil(sqrt(dividedNum));
	}
	
	i=3;
	
	while (i<=iMax)
	{
		while (!(dividedNum%i))
		{
			dividedNum/=i;
			factors.push_back(i);
			iMax=ceil(sqrt(dividedNum));
		}
		
		i++;
	}
	
	if (dividedNum>1)
		factors.push_back(dividedNum);
	
	factorNum=factors.size();
	
	(*factorArray)=new int[factorNum];
	
	for (i=0; i<factorNum; ++i)
		(*factorArray)[i]=factors[i];
	
	return factorNum;
}

bool linesIntersect(V2d a, V2d b, V2d c, V2d d)
{
	double ab=(b.y-a.y)/(b.x-a.x);
	double cd=(d.y-c.y)/(d.x-c.x);
	V2d pt;
	double pos0, pos1;
	
	//cd*(x-c.x)+c.y=ab*(x-a.x)+a.y;
	
	pt.x=(cd*c.x-c.y-ab*a.x+a.y)/(cd-ab);
	pt.y=ab*(pt.x-a.x)+a.y;
	
	pos0=posOnLine(pt, a, b);
	pos1=posOnLine(pt, c, d);
	
	return (pos0>=0 && pos0<=1 && pos1>=0 && pos1<=1);
}

bool isInTriangle(V2d pt, V2d a, V2d b, V2d c)
{
	bool ab=isOnRightSideOfLine(pt, a, b);
	bool bc=isOnRightSideOfLine(pt, b, c);
	bool ca=isOnRightSideOfLine(pt, c, a);
	
	return (ab==bc && bc==ca);
}

bool isOnRightSideOfLine(V2d pt, V2d lStrt, V2d lEnd)
{
	return (lEnd.x-lStrt.x)*(lStrt.y-pt.y)-(lStrt.x-pt.x)*(lEnd.y-lStrt.y)>0;
}

double dstToLine(V2d pt, V2d lStrt, V2d lEnd)
{
	double lng=dst(lStrt, lEnd);
	
	if (!lng)
		return dst(pt, lStrt);
	
	return fabs((lEnd.x-lStrt.x)*(lStrt.y-pt.y)-(lStrt.x-pt.x)*(lEnd.y-lStrt.y))/lng;
}

double dstToLine(V3d pt, V3d lStrt, V3d lEnd)
{
	///I wrote this function based on this:
		///	http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
	
	V3d pointOffset=pt-lStrt;
	V3d lineOffset=lStrt-lEnd;
	
	if (lineOffset.dst())
		return pointOffset.dst();
	else
		return (pointOffset)-(lineOffset)*(((pointOffset).dot(lineOffset))/(lineOffset).dstSquared());
}

double posOnLine(V2d pt, V2d lStrt, V2d lEnd)
{
	return -((lStrt.y-lEnd.y)*(pt.y-lStrt.y)+(lStrt.x-lEnd.x)*(pt.x-lStrt.x))/(lEnd-lStrt).dstSquared();
}

double posOnLine(V3d pt, V3d lStrt, V3d lEnd)
{
	///I wrote this function based on this:
		///	http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
	
	//dont worry about devide by zero, it will just return infinity
	
	return -((lStrt-pt).dot(lEnd-lStrt))/(lEnd-lStrt).dstSquared();
}

int solveCubic(double a, double b, double c, double d, double answer[3])
{
	///I got most of the math for salving this at
		///http://www.1728.org/cubic2.htm
	
	int rootsFound=0;
	
	if (!d) //make 0 a root and turn it into a quadratic
	{
		if (!c)
		{
			if (!b)
			{
				if (!a)
				{
					answer[rootsFound]=NAN; //the equation runs along the x axis, so its basically all real numbers
					++rootsFound;
					//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
					
					return rootsFound;
				}
				else
				{
					answer[rootsFound]=0;
					++rootsFound;
					//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
					
					return rootsFound;

				}
			}
			else
			{
				d=b;
				c=a;
				b=0;
				a=0;
				
				answer[rootsFound]=0;
				++rootsFound;
				//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			}
		}
		else
		{
			//cout << "d is 0, turning into quadratic\n";
			
			d=c;
			c=b;
			b=a;
			a=0;
			
			answer[rootsFound]=0;
			++rootsFound;
			//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
		}
	}
	
	if (!a) //it is a quadratic or below
	{
		if (!b) //it is linear or lower
		{
			if (!c) //we can assume d is not 0 because that would be handled above
			{
				//cout << "there are no more roots";
			}
			else
			{
				//cout << "a and b are 0, solving as a linear equation\n";
				
				answer[rootsFound]=-d/c;
				++rootsFound;
				//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			}
		}
		else //is is quadratic
		{
			double p;
			
			//cout << "a is 0, using quad form\n";
			
			p=c*c-4*b*d;
			
			if (p==0) //sqrt(0) is 0 so there is only one more root
			{
				//cout << "p=0, there is only one root\n";
				
				answer[rootsFound]=-c/(2*a);
				++rootsFound;
				//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			}
			else if (p>0) //use quad form
			{
				double q;
				
				//cout << "p>0, there will be two real roots\n";
				
				q=sqrt(p);
				//cout << "q=" << q << "\n";
				
				answer[rootsFound]=(-c+q)/(2*b);
				++rootsFound;
				//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
				
				answer[rootsFound]=(-c-q)/(2*b);
				++rootsFound;
				//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			}
			else //both roots are imaginary and nothing has to be done
			{
				//cout << "p<0, there are no real roots\n";
			}
		}
	}
	else //it really is a cubic
	{
		double f, g, h;
		
		f=((3.0*c/a)-(b*b/(a*a)))/3.0;
		//cout << "f=" << f << "\n";
		
		g=((2.0*b*b*b/(a*a*a))-(9.0*b*c/(a*a))+(27.0*d/a))/27.0;
		//cout << "g=" << g << "\n";
		
		h=(g*g/4.0)+(f*f*f/27.0);
		//cout << "h=" << h << "\n";
		
		if (f==0 && g==0 && h==0)
		{
			//cout << "f, g and h are all 0\nall 3 roots are real and the same\n";
			
			double o;
			
			o=-cbrt(d/a);
			//cout << "o=" << o << "\n";
			
			answer[rootsFound]=o;
			rootsFound++;
			//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
		}
		else if (h<=0) //all three roots are real
		{
			double i, j, k, l, m, n, p;
			
			//cout << "h<=0, there will be three real roots\n";
			
			i=sqrt((g*g/4)-h);
			//cout << "i=" << i << "\n";
			
			j=cbrt(i);
			//cout << "j=" << j << "\n";
			
			k=acos(-g/(2.0*i));
			//cout << "k=" << k << "\n";
			
			l=-j;
			//cout << "l=" << l << "\n";
			
			m=cos(k/3.0);
			//cout << "m=" << m << "\n";
			
			n=sqrt(3)*sin(k/3);
			//cout << "n=" << n << "\n";
			
			p=-(b/(3.0*a));
			//cout << "p=" << p << "\n";
			
			answer[rootsFound]=2*j*cos(k/3.0)-(b/(3.0*a));
			rootsFound++;
			//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			
			answer[rootsFound]=l*(m+n)+p;
			rootsFound++;
			//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			
			answer[rootsFound]=l*(m-n)+p;
			rootsFound++;
			//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
			
		}
		else //there is only 1 real root
		{
			double r, s, t, u;
			
			//cout << "h>0, there will be only one real root\n";
			
			r=-(g/2.0)+sqrt(h);
			//cout << "r=" << r << "\n";
			
			s=cbrt(r);
			//cout << "s=" << s << "\n";
			
			t=-(g/2.0)-sqrt(h);
			//cout << "t=" << t << "\n";
			
			u=cbrt(t);
			//cout << "u=" << u << "\n";
			
			answer[rootsFound]=(s+u)-(b/(3.0*a));
			rootsFound++;
			//cout << "answer #" << rootsFound << " is " << answer[rootsFound-1] << "\n";
		}
	}
	
	return rootsFound;
}

}

