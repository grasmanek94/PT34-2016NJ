#include <thread>
#include <csignal>
#include <iostream>
#include <Debug.hpp>
#include "Communicator.hpp"

volatile extern sig_atomic_t done;

int main()
{
	DEBUG_MSG("main");
	while (!done)
	{
		try
		{
			DEBUG_MSG("Initializing Communicator");
			Communicator communicator;
			DEBUG_MSG("Running Communicator");
			communicator.Run();
		}
		catch (websocketpp::exception const & e)
		{
			std::cout << "WebSocket exception occurred: " << e.what() << std::endl;
		}
		catch (std::exception const & e)
		{
			std::cout << "unknown exception occurred: " << e.what() << std::endl;
		}
		DEBUG_MSG("crash'd, restarting");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}