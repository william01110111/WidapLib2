#pragma once

#include <chrono>

namespace widap
{

class Timer
{
public:
	Timer();
	
	//get the current time
	double get();
	
	//wait until the given time after the last time the clock was reset
	//(or when the object was created if it has never been reset)
	//useful for always waiting the same abount of time every frame
	void waitUntil(double time, bool resetAfter=true);
	
	//reset the 'base' time to the current time
	void reset();
	
	//wait for the specified time; static so it doesn't mess with the internal vars
	static void waitFor(double duration);
	
protected:
	
	std::chrono::high_resolution_clock::time_point baseTime;
};

}

