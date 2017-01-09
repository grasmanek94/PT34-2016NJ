#pragma once
#include <SharedMemoryQueue.hpp>
#include "Device.hpp"
#include "SerialReceiver.hpp"

class Processor
{
private:
	SharedMemoryQueue in_queue;
	SharedMemoryQueue out_queue;
	Device device;
	SerialReceiver* receiver;
public:
	Processor();
	~Processor();

	void Run();
};