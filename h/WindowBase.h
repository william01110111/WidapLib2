
#pragma once

#include "Drawable.h"
#include "../h/Error.h"
#include <string>
using std::string;

namespace widap
{

class WindowBase : public Drawable
{
public:
	
	WindowBase();
	virtual ~WindowBase();
	
	V2u getDim() {return dim;}
	
	char nextKey();	//get the next key that was pressed
		//0 is returned once when the end of the list is reached, then it starts over; you can cycle through as many times as you want
		//if a cycle goes by without calling this then the key presses of that cycle are NOT saved
	
	char lastKey(); //returns the most recent key pressed or 0 if no key was pressed last cycle
	
	//get if the modifiers are down
	bool shiftDwn() {return shiftDwnBool;};
	bool ctrlDwn() {return ctrlDwnBool;};
	bool altDwn() {return altDwnBool;};
	bool superDwn() {return superDwnBool;};
	
	//mouse location relative to the bottom left corner
	V2i mouseLoc() {return mouseLocation;}
	
	//how much the mouse has moved
	V2i mouseDlta() {return mouseLocDlta;}
	
	//if the buttons have been clicked last cycle
	bool lClick() {return mouseLClick;}
	bool rClick() {return mouseRClick;}
	bool mClick() {return mouseMClick;}
	
	//get if the buttons were down last time updateInput() was called
	bool lDwn() {return mouseLDwn;}
	bool rDwn() {return mouseRDwn;}
	bool mDwn() {return mouseMDwn;}
	
	//get the mouse scroll as a number, 0 is no scroll, + is up, negative is down
	int scroll() {return mouseScroll;}
	
	//return if this window has focus
	bool hasFocus() {return windowHasFocus;}
	
	//return if this window is open
	bool isOpen() {return windowIsOpen;}
	
	//retrieve the name of the window
	string getName() {return name;}
	
	//open the window, if dimensions are (0, 0) it will be full screen, (0, 1) is maximized 
	virtual void open(V2u dimIn, string nameIn)=0;
	
	//display any changes to the window
	virtual void refreshDisplay()=0;
	
	//update the input
	virtual void updateInput()=0;
	
	//close the window
	virtual void close()=0;
	
protected:
	
	//zeros out vars
	void resetVars();
	
	string name;
	V2u dim; //the dimensions of the window
	
	V2i mouseLocation; //the location of the mouse
	V2i mouseLocDlta; //how much the mouse has moved
	bool mouseLClick, mouseRClick, mouseMClick; //if left, right or middle clicks have happened last cycle
	bool mouseLDwn, mouseRDwn, mouseMDwn; //if these buttons are down
	int mouseScroll; //can be positive, negative or 0, how much the scroll wheel has moved
	
	bool shiftDwnBool, ctrlDwnBool, altDwnBool, superDwnBool;
	
	static const int MAX_KEY_PRESSES=256; //the most key presses there can be in a single cycle
	char keyPresses[MAX_KEY_PRESSES]; //a list of key presses, 256 is the max number there can be in a single cycle
	int keyPressNum; //how long the above list is
	int keyPressListPos; //cycles between 0 and keyPressNum as nextKey is called
	
	bool windowHasFocus;
	bool windowIsOpen;
	
	Error err; //the object for reporting errors
};

}

