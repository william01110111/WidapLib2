
#pragma once

#include "../Math/Vector2D.h"

namespace widap
{

class InputSource
{
public:
	
	InputSource();
	virtual ~InputSource() {}
	
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
	
	//update the input
	virtual void updateInput()=0;
	
	virtual V2u getDim()=0;
	
	virtual double getDltaTime()=0;
	
protected:
	
	//zeros out vars
	void resetVars();
	
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
};

}

