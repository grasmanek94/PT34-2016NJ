#include <cstring>
#include <iostream>
#include <memory>
#include "SharedMemoryQueueMessage.hpp"

SharedMemoryQueueMessage::SharedMemoryQueueMessage()
{
	memset(string_data, 0, max_data_size_bytes_for_QueueItem);
}

SharedMemoryQueueMessage::SharedMemoryQueueMessage(const std::string& message)
{
	Set(message);
}

void SharedMemoryQueueMessage::Set(const std::string& message)
{
	if (message.size() >= max_data_size_bytes_for_QueueItem)
	{
		throw std::out_of_range("size of input message too big");
	}
	memcpy(string_data, message.c_str(), message.size());
	string_data[message.size()] = 0;
}

std::string SharedMemoryQueueMessage::Get() const
{
	return std::string(string_data);
}
