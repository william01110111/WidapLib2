
#include "../../h/UI/ButtonViewUI.h"
#include "../../h/UI/ThemeUI.h"

namespace widap
{

ButtonViewUI::ButtonViewUI()
{
	
}

void ButtonViewUI::draw()
{
	surface->rect(low, hgh, clicked?themeUI.buttonBkndSelect:themeUI.buttonBkndUnselect);
	surface->text(text, V2d(low.x, hgh.y), hgh.y-low.y, themeUI.buttonText);
}

void ButtonViewUI::update()
{
	if (input->mouseLoc().isInRect(low, hgh) && input->lClick())
	{
		clicked=true;
	}
	else
	{
		clicked=false;
	}
}

}

