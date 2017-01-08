#pragma once
#include <SharedMemoryQueue.hpp>
#include "Device.hpp"

class Processor
{
private:
	SharedMemoryQueue in_queue;
	SharedMemoryQueue out_queue;
	Device device;
public:
	Processor();
	~Processor();

	void Run();
};