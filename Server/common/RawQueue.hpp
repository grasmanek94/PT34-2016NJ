#ifndef RAWQUEUE_H
#define RAWQUEUE_H

#include "SharedMemoryQueueMessage.hpp"

static const size_t max_items_for_RawQueue = 256;

class RawQueue
{
private:
	size_t count;
	size_t pushed;
	size_t popped;
	SharedMemoryQueueMessage items[max_items_for_RawQueue];

public:
	RawQueue();
	size_t Count() const;
	bool Push(SharedMemoryQueueMessage* item);
	bool Pop(SharedMemoryQueueMessage* item);
	static size_t GetSizeBytes();
	static size_t MaxCount();
	static size_t MaxBytesPerElem();
};

#endif