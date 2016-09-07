
#include "../../h/UI/LabelViewUI.h"
#include "../../h/UI/ThemeUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

LabelViewUI::LabelViewUI()
{
	
}

void LabelViewUI::setText(const string& textIn)
{
	text=textIn;
	calcDim();
}

V2d LabelViewUI::calcDim()
{	
	if (surface)
	{
		return surface->text()->getBounds(text, themeUI.labelText[style].height);
	}
	else
		return V2d();
}

void LabelViewUI::setStyle(int in)
{
	if (in<0 || in>3)
	{
		err << "bad style number of " << in << " sent to LabelViewUI" << err;
		style=0;
		return;
	}
	
	style=in;
	calcAndSetDim();
}

void LabelViewUI::draw()
{
	if (!surface)
	{
		err << "called LabelViewUI::draw() called with null surface" << err;
		return;
	}
	
	V2d low=getLow(), hgh=getHgh();
	
	surface->text()->setStyle(themeUI.labelText[style]);
	surface->text()->setPos(low, hgh, TextBase::CENTER_X, TextBase::CENTER_Y, TextBase::SHRINK_TO_BOUNDS);
	surface->text()->draw(text);
}

}

