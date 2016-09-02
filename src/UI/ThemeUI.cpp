#include "../../h/UI/ThemeUI.h"

namespace widap
{

ThemeUI::ThemeUI()
{
	theme0();
}

void ThemeUI::theme0()
{
	buttonBkndUnselect=clr(32, 32, 32, 128);
	buttonBkndSelect=clr(64, 64, 64, 128);
	buttonTextUnselect=TextStyle(36, false, Clr(0, 255, 0), 1.0);
	buttonTextSelect=TextStyle(36, true, Clr(255, 255, 255), 1.0);
}

ThemeUI themeUI;

}

