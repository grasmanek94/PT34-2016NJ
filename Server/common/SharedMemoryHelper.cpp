#include <stdexcept>
#include <string>
#include <semaphore.h>

#include "SharedMemoryHelper.hpp"

namespace shared_memory_helper
{
	void PrepSem(const std::string& name, sem_t** semaphore, int initial)
	{
		*semaphore = sem_open(name.c_str(), O_CREAT | O_EXCL, 0666, initial);

		if (*semaphore == SEM_FAILED)
		{
			*semaphore = sem_open(name.c_str(), 0);
			if (*semaphore == SEM_FAILED)
			{
				throw std::runtime_error("Cannot access semaphore");
			}
		}
	}
}