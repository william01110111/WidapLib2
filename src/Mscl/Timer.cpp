#include "../../h/Mscl/Timer.h"
#include <thread>

namespace widap
{

Timer::Timer()
{
	reset();
}

double Timer::check()
{
	return (std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now()-baseTime)).count();
}

void Timer::waitUntil(double time, bool resetAfter)
{
	std::this_thread::sleep_for(std::chrono::microseconds((int)((time-(std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now()-baseTime)).count())*1000000)));
	
	if (resetAfter)
		reset();
}

void Timer::waitFor(double duration)
{
	std::this_thread::sleep_for(std::chrono::microseconds((int)(duration*1000000)));
}

void Timer::reset()
{
	baseTime=std::chrono::high_resolution_clock::now();
}

}

