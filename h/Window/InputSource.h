
#pragma once

#include "../Math/Vector2D.h"

namespace widap
{

class InputSource
{
public:
	
	class Mouse
	{
	public:
		
		class Button
		{
		public:
			inline bool isDown() {return _isDown;}
			inline bool isUp() {return !_isDown;}
			inline bool justDown() {return _justDown;}
			inline bool justUp() {return _justUp;}
			
		protected:
			bool _isDown=false, _justDown=false, _justUp=false;
			
			friend class Mouse;
			friend class InputSource;
		};
		
		inline V2d pos() {return _pos;}
		inline V2d delta() {return _delta;}
		inline double scroll() {return _scroll;}
		
		inline bool isDown() {return left._isDown;}
		inline bool isUp() {return !left._isDown;}
		inline bool justDown() {return left._justDown;}
		inline bool justUp() {return left._justUp;}
		
		inline operator const Button&() {return left;}
		inline operator V2d() {return _pos;}
		
		Button left, middle, right;
		
	protected:
		
		V2d _pos;
		V2d _delta;
		double _scroll=0;
		
		friend class InputSource;
	};
	
	InputSource();
	virtual ~InputSource() {}
	
	Mouse mouse;
	
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
	inline V2i mouseLoc() {return mouse._pos;}
	
	//how much the mouse has moved
	inline V2i mouseDlta() {return mouse._delta;}
	
	//if the buttons have been clicked last cycle
	inline bool lClick() {return mouse.left._justDown;}
	inline bool rClick() {return mouse.right._justDown;}
	inline bool mClick() {return mouse.middle._justDown;}
	
	//get if the buttons were down last time updateInput() was called
	bool lDwn() {return mouse.left._isDown;}
	bool rDwn() {return mouse.right._isDown;}
	bool mDwn() {return mouse.middle._isDown;}
	
	//get the mouse scroll as a number, 0 is no scroll, + is up, negative is down
	int scroll() {return mouse._scroll;}
	
	//update the input
	virtual void updateInput()=0;
	
	virtual V2u getDim()=0;
	
	virtual double getDltaTime()=0;
	
protected:
	
	//zeros out vars
	void resetVars();
	
	/*V2i mouseLocation; //the location of the mouse
	V2i mouseLocDlta; //how much the mouse has moved
	bool mouseLClick, mouseRClick, mouseMClick; //if left, right or middle clicks have happened last cycle
	bool mouseLDwn, mouseRDwn, mouseMDwn; //if these buttons are down
	int mouseScroll; //can be positive, negative or 0, how much the scroll wheel has moved
	*/
	
	//set everything on a mouse button, should only be called exactly per cycle per button
	void setMouseButton(Mouse::Button * btn, bool isDownIn);
	
	//set the mouse position and delta, should be called exactly once per cycle
	void setMousePos(V2d posIn);
	
	//set the scroll, should be called exactly once per cycle
	void setMouseScroll(double scrollIn);
	
	bool shiftDwnBool, ctrlDwnBool, altDwnBool, superDwnBool;
	
	static const int MAX_KEY_PRESSES=256; //the most key presses there can be in a single cycle
	char keyPresses[MAX_KEY_PRESSES]; //a list of key presses, 256 is the max number there can be in a single cycle
	int keyPressNum; //how long the above list is
	int keyPressListPos; //cycles between 0 and keyPressNum as nextKey is called
};

}

