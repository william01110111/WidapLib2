
#include "../../h/Window/InputSource.h"

namespace widap
{

InputSource::InputSource()
{
	resetVars();
}

void InputSource::resetVars()
{
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


