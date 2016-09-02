#pragma once

#include "ViewUI.h"
#include <string>

namespace widap
{

class ButtonViewUI: public ViewUI
{
public:
	
	ButtonViewUI();
	ButtonViewUI(string textIn) {ButtonViewUI(); setText(textIn);}
	
	void draw();
	void update();
	
	void setText(string textIn);
	string getText() {return text;}
	
	V2d calcDim();
	
	bool isClicked() {return clicked;}
	
private:
	string text;
	bool clicked;
};

}

