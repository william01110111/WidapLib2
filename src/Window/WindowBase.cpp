#include "../../h/Window/WindowBase.h"

namespace widap
{

WindowBase::WindowBase()
{
	resetVars();
}

void WindowBase::resetVars()
{
	InputSource::resetVars();
	
	name="[unnamed window]";
	dim.zero();
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

}

