#include <thread>
#include <csignal>
#include <iostream>
#include "Communicator.hpp"

volatile extern sig_atomic_t done;

int main()
{
	while (!done)
	{
		try
		{
			Communicator communicator;
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
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}