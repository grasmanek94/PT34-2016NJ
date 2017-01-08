#pragma once
#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::system_clock> start;
public:
	Timer();

	double ElapsedMilliseconds();

	void Start();
	void Restart();
};