
#pragma once

#include "../Graphics/Surface.h"
#include "InputSource.h"
#include "../Mscl/Error.h"
#include "../Mscl/Timer.h"
#include <string>
using std::string;

namespace widap
{

class WindowBase : public Surface, public InputSource
{
public:
	
	WindowBase();
	virtual ~WindowBase() {}
	
	V2u getDim() {return dim;}
	
	//return if this window has focus
	bool hasFocus() {return windowHasFocus;}
	
	//return if this window is open
	bool isOpen() {return windowIsOpen;}
	
	//retrieve the name of the window
	string getName() {return name;}
	
	//set the frame time both in delay per frame and FPS
	void setFrameTime(double frameTimeIn) {frameTime=frameTimeIn;}
	void setFPS(double fpsIn) {frameTime=1.0/fpsIn;}
	
	//open the window, if dimensions are (0, 0) it will be full screen, (0, 1) is maximized 
	virtual void open(V2u dimIn, string nameIn)=0;
	void openFullScreen(string nameIn) {open({0, 0}, nameIn);}
	void openMaximized(string nameIn) {open({0, 1}, nameIn);}
	
	//display any changes to the window
	virtual void refreshDisplay()=0;
	
	//display the frame, wait until the frame time is done then update input and return if the window is still open
	bool nextFrame();
	
	//close the window
	virtual void close()=0;
	
protected:
	
	//zeros out vars
	void resetVars();
	
	string name;
	//V2u dim; //the dimensions of the window
	
	bool windowHasFocus;
	bool windowIsOpen;
	
	double frameTime;
	Timer timer;
	
	V2u dim;
	
	Error err; //the object for reporting errors
};

}

