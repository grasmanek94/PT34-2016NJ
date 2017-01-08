#include "Timer.hpp"

Timer::Timer()
{
	start = std::chrono::system_clock::now();
}

double Timer::ElapsedMilliseconds()
{
	std::chrono::milliseconds duration = 
		std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now() - start);

	return duration.count();
}

void Timer::Start()
{
	Restart();
}

void Timer::Restart()
{
	start = std::chrono::system_clock::now();
}