#include "../../h/UI/ThemeUI.h"
#include <iostream>

namespace widap
{

ThemeUI & getThemeUI()
{
	static ThemeUI theme;
	
	return theme;
}

ThemeUI::ThemeUI()
{
	container.bknd=clr(64, 64, 64, 255);
	
	stack.outerBuffer=V2d(8, 8);
	stack.innerBuffer=8;
	
	label.text[0]=TextStyle(18, false, Clr(255, 255, 255), 1.0);
	label.text[1]=TextStyle(42, true, Clr(0, 128, 255), 1.0);
	label.text[2]=TextStyle(36, true, Clr(128, 0, 255), 1.0);
	label.text[3]=TextStyle(24, true, Clr(255, 0, 255), 1.0);
	
	button.bkndUnselect=ClrRGBA(32, 32, 32, 128);
	button.bkndSelect=ClrRGBA(64, 64, 64, 128);
	button.textUnselect=TextStyle(20, false, Clr(0, 255, 0), 1.0);
	button.textSelect=TextStyle(button.textUnselect.height, true, Clr(255, 255, 255), 1.0);
	button.buffer=V2d(8, 2);
}

}

