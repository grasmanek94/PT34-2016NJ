#include <thread>
#include <csignal>
#include <iostream>
#include "Processor.hpp"
volatile extern sig_atomic_t done = 0;

int main()
{
	while (!done)
	{
		try
		{
			Processor processor;
			processor.Run();
		}
		catch (std::exception const & e)
		{
			std::cout << "unknown exception occurred: " << e.what() << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}