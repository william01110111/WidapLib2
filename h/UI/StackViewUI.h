
#pragma once

#include "ContainerViewUI.h"

namespace widap
{

class StackViewUI: public ContainerViewUI
{
public:
	
	void addChild(ViewUI * childIn) {addChildToList(childIn);}
	void removeChild(ViewUI * childIn) {removeChildFromList(childIn);}
	
	enum Align {LEADING, TRAILING, CENTER, FILL, SPACE};
	
	void setLoyout(Align majorIn=TRAILING, Align minorIn=LEADING, bool horizontal=false, bool backwords=false)
	{
		h=horizontal;
		b=h?backwords:!backwords;
		minorAlign=minorIn;
		majorAlign=majorIn;
		setChildRects();
	}
	void setAlign() { setChildRects();}
	void setBuffer(V2d outer, double inner) {outerBuffer=outer; innerBuffer=inner; setChildRects();}
	
	V2d calcDim();
	
protected:
	
	void setChildRects();
	
private:
	
	bool h=false; //if the stack should be horizontal
	bool b=true; //if the direction of the stack should be backwords
	Align minorAlign=LEADING, majorAlign=TRAILING;
	V2d outerBuffer={12, 12}; //the buffer between items and the outer box
	double innerBuffer=12; //the buffer between elements
	
	//get the maJor and miNor components based on if the stack is horizontal
	
	template <typename T>
	inline T mj(const V2<T>& in);
	
	template <typename T>
	inline T mn(const V2<T>& in);
};

}


