#pragma once

#include "../Graphics/Color.h"

namespace widap
{

class ThemeUI
{
public:
	ThemeUI();
	
	void theme0();
	
	ClrRGBA buttonBkndUnselect, buttonBkndSelect, buttonText;
};

extern ThemeUI themeUI;

}

