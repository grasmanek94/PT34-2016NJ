#ifndef IPCQUEUE_H
#define IPCQUEUE_H

#include <semaphore.h>
#include <string>
#include "SharedMemoryQueueMessage.hpp"
#include "RawQueue.hpp"

class SharedMemoryQueue
{
private:
	RawQueue* queue_shared_memory;
	sem_t* queue_operation_semaphore;
	sem_t* memory_prepare_semaphore;
	sem_t* elem_count_semaphore;
	int shm_fd;
	std::string queue_name;
	int deletion_fd_protection;

	bool Wait();
	bool Post();
	bool TryWait();

public:
	SharedMemoryQueue(const std::string& queue_name);
	~SharedMemoryQueue();

	bool Push(SharedMemoryQueueMessage* item);
	bool Pop(SharedMemoryQueueMessage* item);

	// nonblocking functions
	bool TryPush(SharedMemoryQueueMessage* item);
	bool TryPop(SharedMemoryQueueMessage* item);


	size_t Count() const;
};

#endif