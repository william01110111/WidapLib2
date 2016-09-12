#pragma once

#include "ViewUI.h"
#include <string>

#include <functional>
using std::function;

namespace widap
{

class ButtonViewUI: public ViewUI
{
public:
	
	ThemeUI::Button theme=getThemeUI().button;
	
	ButtonViewUI();
	ButtonViewUI(const string& textIn) {ButtonViewUI(); setText(textIn);}
	
	void draw();
	void update();
	
	void setText(const string& textIn);
	string getText() {return text;}
	
	void setClickAction(function<void ()> in) {clickAction=in;}
	
	V2d calcDim();
	
	bool isClicked() {return clicked;}
	
private:
	string text;
	bool clicked;
	
	function<void ()> clickAction;
};

}

