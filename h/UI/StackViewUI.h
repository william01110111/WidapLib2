
#pragma once

#include "ContainerViewUI.h"

namespace widap
{

class StackViewUI: public ContainerViewUI
{
public:
	
	ThemeUI::Stack theme=getThemeUI().stack;
	
	StackViewUI();
	
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
	
	V2d calcDim();
	
protected:
	
	void setChildRects();
	
private:
	
	bool h=false; //if the stack should be horizontal
	bool b=true; //if the direction of the stack should be backwords
	Align minorAlign=LEADING, majorAlign=TRAILING;
	
	//get the maJor and miNor components based on if the stack is horizontal
	
	template <typename T>
	inline T mj(const V2<T>& in);
	
	template <typename T>
	inline T mn(const V2<T>& in);
};

}


