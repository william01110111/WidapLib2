
#pragma once

#include "ViewUI.h"
#include <string>

namespace widap
{

class LabelViewUI: public ViewUI
{
public:
	
	ThemeUI::Label theme=getThemeUI().label;
	
	LabelViewUI();
	LabelViewUI(const string& textIn) {LabelViewUI(); setText(textIn);}
	
	void draw();
	
	void setText(const string& textIn);
	string getText() {return text;}
	
	//0 is body, 1 is biggest heading, 3 is smallest heading, others are invalid
	void setStyle(int in);
	int getStyle() {return style;}
	
	V2d calcDim();
	
private:
	
	int style=0;
	string text;
};

}


