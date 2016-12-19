
#include <cstring>

#include "SharedMemoryQueueMessage.hpp"
#include "RawQueue.hpp"

RawQueue::RawQueue()
{
	memset(this, 0, sizeof(RawQueue));
}

size_t RawQueue::Count() const
{
	return count;
}

bool RawQueue::Push(SharedMemoryQueueMessage* item)
{
	if (Count() == max_items_for_RawQueue)
	{
		return false;
	}

	memcpy((void*)&items[pushed], item, sizeof(SharedMemoryQueueMessage));

	++count;
	if (++pushed == max_items_for_RawQueue)
	{
		pushed = 0;
	}
	return true;
}

bool RawQueue::Pop(SharedMemoryQueueMessage* item)
{
	if (Count() == 0)
	{
		return false;
	}

	memcpy(item, (void*)&items[popped], sizeof(SharedMemoryQueueMessage));

	--count;
	if (++popped == max_items_for_RawQueue)
	{
		popped = 0;
	}
	return true;
}

size_t RawQueue::GetSizeBytes()
{
	return sizeof(RawQueue);
}

size_t RawQueue::MaxCount()
{
	return max_items_for_RawQueue;
}

size_t RawQueue::MaxBytesPerElem()
{
	return max_data_size_bytes_for_QueueItem;
}