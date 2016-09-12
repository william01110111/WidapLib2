
#include "../../h/Window/InputSource.h"

namespace widap
{

InputSource::InputSource()
{
	resetVars();
}

void InputSource::resetVars()
{
	mouse=Mouse();
	shiftDwnBool=0;
	ctrlDwnBool=0;
	altDwnBool=0;
	superDwnBool=0;
	keyPressNum=0;
	keyPressListPos=0;
}

//set everything on a mouse button, should only be called exactly per cycle per button
void InputSource::setMouseButton(Mouse::Button * btn, bool isDownIn)
{
	if (btn->_justDown)
		btn->_justDown=false;
	
	if (btn->_justUp)
		btn->_justUp=false;
	
	if (isDownIn!=btn->_isDown)
	{
		btn->_isDown=isDownIn;
		
		if (isDownIn)
			btn->_justDown=true;
		else
			btn->_justUp=true;
	}
}

//set the mouse position and delta, should be called exactly once per cycle
void InputSource::setMousePos(V2d posIn)
{
	mouse._delta=posIn-mouse._pos;
	mouse._pos=posIn;
}

//set the scroll, should be called exactly once per cycle
void InputSource::setMouseScroll(double scrollIn)
{
	mouse._scroll=scrollIn;
}

char InputSource::nextKey()
{
	if (keyPressListPos<keyPressNum)
	{
		++keyPressListPos;
		return keyPresses[keyPressListPos-1];
	}
	else
	{
		keyPressListPos=0;
		return 0;
	}
}

char InputSource::lastKey()
{
	if (keyPressNum)
	{
		return keyPresses[keyPressNum-1];
	}
	else
	{
		return 0;
	}
}

}


