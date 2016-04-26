
#pragma once

///you must put the following lines into linker options to use sfml window
/*

-lsfml-graphics
-lsfml-window
-lsfml-system

*/

#include "WindowBase.h"
#include <SFML/Graphics.hpp>

namespace widap
{

class WindowSFML : public WindowBase
{
public:
	WindowSFML(); //constructor
	~WindowSFML(); //destructor
	
	sf::RenderWindow * getWindowObj() {return &windowObj;}
	
	
	///from WindowBase
	
	//open the window with the given dimensions and name
	void open(V2u dimIn, string name);
	
	//close the window
	void close();
	
	//refresh the window
	void refreshDisplay();
	
	//get any new input
	void updateInput();
	
	
	///from Drawable
	
	USING_DRAWABLE;
	
	//V2u getDim(); //no need, implemented in WindowBase
	
	//sets the value of a single pixel to the predefined drawing color
	void set(int x, int y);
	
	//set the draw color with a void pointer that is assumed to be of correct type
	void setDrawClr(void * clrIn);
	
	//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
	void setDrawClr(int clrIn);
	
	//set the draw color with a ClrRGBA pointer
	void setDrawClr(ClrRGBA * clrIn);

	//set the draw color with a ClrRGBA value
	void setDrawClr(ClrRGBA clrIn);
	
	//set the draw color with a ClrBGR pointer
	void setDrawClr(ClrBGR * clrIn);
	
	//set the draw color with a ClrBGR value
	void setDrawClr(ClrBGR clrIn);
	
	//fills the Drawable with the predefined color
	virtual void clear();
	
	//draw a rectangle with the preset draw color
	void rect(V2d low, V2d hgh);
	
	//draw a circle with the preset draw color
	void circle(V2d center, double radius);
	
	//draw a line
	void line(V2d start, V2d end);
	
private:
	
	//return the draw color and alpha as a sfml color
	sf::Color sfmlDrawClr();
	
	sf::RenderWindow windowObj;
	
	static bool firstInstance;
	static sf::Font font;
	static char key2char[127];
	
	ClrBGR drawClr;
	ClrRGBA * data;
	sf::Texture texture;
	
	//fixes things when the window is resized
	void hasBeenResized();
};

}

