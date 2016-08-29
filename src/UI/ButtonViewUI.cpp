
#include "../../h/UI/ButtonViewUI.h"
#include "../../h/UI/ThemeUI.h"

namespace widap
{

ButtonViewUI::ButtonViewUI()
{
	
}

void ButtonViewUI::draw()
{
	V2d low=getLow(), hgh=getHgh();
	
	surface->rect(low, hgh, clicked?themeUI.buttonBkndSelect:themeUI.buttonBkndUnselect);
	surface->text()->setStyle(-1, themeUI.buttonText, 1, false);
	surface->text()->setPos(low, hgh, TextBase::CENTER_X, TextBase::CENTER_Y, TextBase::SHRINK_TO_BOUNDS);
	surface->text()->draw(text);
}

void ButtonViewUI::update()
{
	V2d low=getLow(), hgh=getHgh();
	
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

