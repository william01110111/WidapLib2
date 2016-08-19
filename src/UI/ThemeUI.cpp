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
	buttonText=clr(64, 255, 64, 255);
}

ThemeUI themeUI;

}

