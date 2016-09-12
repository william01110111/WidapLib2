#pragma once

#include "../Graphics/Color.h"
#include "../Graphics/TextBase.h"

namespace widap
{

struct ThemeUI
{
public:
	
	struct Container
	{
		ClrRGBA bknd;
		
	} container;
	
	struct Stack
	{
		V2d outerBuffer;
		double innerBuffer;
		
	} stack;
	
	struct Label
	{
		TextStyle text[4];
		
	} label;
	
	struct Button
	{
		ClrRGBA bkndUnselect, bkndSelect;
		TextStyle textUnselect, textSelect;
		V2d buffer;
		
	} button;
	
	ThemeUI();
};

ThemeUI & getThemeUI();

}

