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
	scale=2;
	
	container.bknd=clr(20, 20, 20, 255);
	
	stack.outerBuffer=V2d(8, 8)*scale;
	stack.innerBuffer=8*scale;
	
	label.text[0]=TextStyle(20*scale, false, Clr(255, 255, 255), 1.0);
	label.text[1]=TextStyle(42*scale, true, Clr(0, 128, 255), 1.0);
	label.text[2]=TextStyle(36*scale, true, Clr(64, 192, 255), 1.0);
	label.text[3]=TextStyle(24*scale, true, Clr(255, 255, 255), 1.0);
	
	button.bkndUnselect=ClrRGBA(0, 60, 92, 255);
	button.bkndSelect=ClrRGBA(24, 53, 172, 255);
	button.textUnselect=TextStyle(26*scale, false, Clr(255, 255, 255), 1.0);
	button.textSelect=TextStyle(button.textUnselect.height, true, Clr(230, 230, 230), 1.0);
	button.buffer=V2d(8, 2)*scale;
}

}

