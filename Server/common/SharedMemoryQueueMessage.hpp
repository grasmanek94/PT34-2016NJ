#ifndef QUEUEITEM_H
#define QUEUEITEM_H

#include <string>

static const size_t max_data_size_bytes_for_QueueItem = 16384;

class SharedMemoryQueueMessage
{
private:
	char string_data[max_data_size_bytes_for_QueueItem];
public:
	
	SharedMemoryQueueMessage();
	SharedMemoryQueueMessage(const std::string& message);
	void Set(const std::string& message);
	std::string Get() const;
};

#endif