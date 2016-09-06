#pragma once

#include "../Graphics/Color.h"
#include "../Graphics/TextBase.h"

namespace widap
{

class ThemeUI
{
public:
	ThemeUI();
	
	void theme0();
	
	ClrRGBA containerViewBknd;
	
	ClrRGBA buttonBkndUnselect, buttonBkndSelect;
	TextStyle buttonTextUnselect, buttonTextSelect;
};

extern ThemeUI themeUI;

}

