#include <iostream>

#include <string>
#include <new>
#include <semaphore.h>
#include <pthread.h>

#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>

#include "Debug.hpp"
#include "SharedMemoryHelper.hpp"
#include "SharedMemoryQueueMessage.hpp"
#include "RawQueue.hpp"
#include "SharedMemoryQueue.hpp"

bool SharedMemoryQueue::Wait()
{
	//DEBUG_MSG("SharedMemoryQueue::Wait");
	return sem_wait(queue_operation_semaphore) == 0;
}

bool SharedMemoryQueue::Post()
{
	//DEBUG_MSG("SharedMemoryQueue::Post");
	return sem_post(queue_operation_semaphore) == 0;
}

bool SharedMemoryQueue::TryWait()
{
	//DEBUG_MSG("SharedMemoryQueue::TryWait");
	return sem_trywait(queue_operation_semaphore) == 0;
}

SharedMemoryQueue::SharedMemoryQueue(const std::string& queue_name)
	:	queue_shared_memory(NULL),
		queue_operation_semaphore(SEM_FAILED),
		memory_prepare_semaphore(SEM_FAILED),
		shm_fd(-1),
		queue_name(queue_name),
		deletion_fd_protection(-1)
{
	DEBUG_MSG("SharedMemoryQueue::SharedMemoryQueue:" << queue_name);
	deletion_fd_protection = open(("/tmp/deletion_fd_protection.ipc_lockcheck." + queue_name).c_str(), O_CREAT | O_RDWR, 0666);
	if (deletion_fd_protection == -1)
	{
		throw std::exception(/*"Cannot access critical lock file"*/);
	}

	if (flock(deletion_fd_protection, LOCK_EX | LOCK_NB) == 0)
	{
		//we have the only and only lock now so this below should generrally NOT be able to fail
		//flock(deletion_fd_protection, LOCK_UN);//door dit te uncommenten is de race conditie weg en zou de code alsnog moeten werken |>> TESTED schijnt te werken
		if (flock(deletion_fd_protection, LOCK_SH | LOCK_NB) != 0)
		{
			throw std::exception(/*"Cannot access critical lock file"*/);
		}

		unlink(queue_name.c_str());
		sem_unlink(queue_name.c_str());
		sem_unlink(("SHM_PROT_" + queue_name).c_str());
		sem_unlink(("ITEM_COUNTER_" + queue_name).c_str());
	}
	else
	{
		if (flock(deletion_fd_protection, LOCK_SH | LOCK_NB) != 0)
		{
			throw std::exception(/*"Cannot access critical lock file"*/);
		}
	}

	shared_memory_helper::PrepSem("SHM_PROT_" + queue_name, &memory_prepare_semaphore, 1);
	shared_memory_helper::PrepSem(queue_name, &queue_operation_semaphore, 1);

	sem_wait(memory_prepare_semaphore);

	queue_shared_memory = shared_memory_helper::shm_create<RawQueue*>(queue_name, RawQueue::GetSizeBytes(), shm_fd);
	if (queue_shared_memory)
	{
		// use C++98 placement new to call constructor when new shared memory region has been created
		new (queue_shared_memory) RawQueue();
	}
	else
	{
		queue_shared_memory = shared_memory_helper::shm_open<RawQueue*>(queue_name, shm_fd);
		if (!queue_shared_memory)
		{
			throw std::exception(/*"Cannot access shared memory"*/);
		}
	}

	sem_post(memory_prepare_semaphore);
}

bool SharedMemoryQueue::Push(SharedMemoryQueueMessage* item)
{
	if (queue_shared_memory->Count() == queue_shared_memory->MaxCount())
	{
		//DEBUG_MSG("SharedMemoryQueue::Push:Full");
		return false;
	}
	//DEBUG_MSG("SharedMemoryQueue::Push:Wait");
	Wait();
	bool ret_val = queue_shared_memory->Push(item);
	Post();
	//DEBUG_MSG("SharedMemoryQueue::Push:Post:" << ret_val);
	return ret_val;
}

bool SharedMemoryQueue::Pop(SharedMemoryQueueMessage* item)
{
	if (queue_shared_memory->Count() == 0)
	{
		//DEBUG_MSG("SharedMemoryQueue::Pop:empty");
		return false;
	}
	//DEBUG_MSG("SharedMemoryQueue::Pop:Wait");
	Wait();
	bool ret_val = queue_shared_memory->Pop(item);
	Post();
	//DEBUG_MSG("SharedMemoryQueue::Pop:Post:" << ret_val);
	return ret_val;
}

bool SharedMemoryQueue::TryPush(SharedMemoryQueueMessage* item)
{
	if (queue_shared_memory->Count() == queue_shared_memory->MaxCount() || !TryWait())
	{
		//DEBUG_MSG("SharedMemoryQueue::TryPush:Full||!TryWait:" << (queue_shared_memory->Count() == queue_shared_memory->MaxCount()));
		return false;
	}
	bool ret_val = queue_shared_memory->Push(item);
	Post();
	//DEBUG_MSG("SharedMemoryQueue::TryPush:Post:" << ret_val);
	return ret_val;
}

bool SharedMemoryQueue::TryPop(SharedMemoryQueueMessage* item)
{
	if (queue_shared_memory->Count() == 0 || !TryWait())
	{
		//DEBUG_MSG("SharedMemoryQueue::TryPop:Empty||!TryWait:" << (queue_shared_memory->Count() == 0));
		return false;
	}
	bool ret_val = queue_shared_memory->Pop(item);
	Post();
	//DEBUG_MSG("SharedMemoryQueue::TryPop:Post:" << ret_val);
	return ret_val;
}

size_t SharedMemoryQueue::Count() const
{
	return queue_shared_memory->Count();
}

void SharedMemoryQueue::Clear()
{
	DEBUG_MSG("SharedMemoryQueue::Clear");
	if (queue_shared_memory->Count() == 0)
	{
		return;
	}
	Wait();
	queue_shared_memory->Clear();
	Post();
}

SharedMemoryQueue::~SharedMemoryQueue()
{
	DEBUG_MSG("SharedMemoryQueue::~SharedMemoryQueue");
	sem_close(queue_operation_semaphore);
	sem_close(memory_prepare_semaphore);
	close(shm_fd);

	if (deletion_fd_protection != -1)
	{
		flock(deletion_fd_protection, LOCK_UN); // release shared lock
		close(deletion_fd_protection);
	}
}
