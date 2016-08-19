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
	
	void setText(string textIn) {text=textIn;}
	string getText() {return text;}
	
	bool isClicked() {return clicked;}
	
private:
	string text;
	bool clicked;
};

}

