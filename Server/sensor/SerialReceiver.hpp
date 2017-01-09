#pragma once
#include <thread>
#include <vector>
#include <string>
#include <SharedMemoryQueue.hpp>
#include "Device.hpp"

class SerialReceiver
{
private:
	Device* setup;
	SharedMemoryQueue msg_queue;
	int serial_fd;
	int serial_buffer_pos;

	std::thread async_reader;
	char message_buffer[256];
	char serial_buffer[16384];

	void ReceiverThread();
	void set_blocking(int fd, int should_block);
	int set_interface_attribs(int fd, int speed, int parity);

public:
	SerialReceiver(Device* setup);
	~SerialReceiver();
	void Update();
};