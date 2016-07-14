#include "../h/WindowBase.h"

namespace widap
{

WindowBase::WindowBase()
{
	resetVars();
}

WindowBase::~WindowBase()
{
	
}

void WindowBase::resetVars()
{
	name="[unnamed window]";
	dim.zero();
	mouseLocation.zero();
	mouseLocDlta.zero();
	mouseLClick=0;
	mouseRClick=0;
	mouseMClick=0;
	mouseLDwn=0;
	mouseRDwn=0;
	mouseMDwn=0;
	mouseScroll=0;
	shiftDwnBool=0;
	ctrlDwnBool=0;
	altDwnBool=0;
	superDwnBool=0;
	keyPressNum=0;
	keyPressListPos=0;
	frameTime=1.0/60.0;
	windowHasFocus=0;
	windowIsOpen=0;
}

bool WindowBase::nextFrame()
{
	refreshDisplay();
	timer.waitUntil(frameTime);
	updateInput();
	return windowIsOpen;
}

char WindowBase::nextKey()
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

char WindowBase::lastKey()
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

