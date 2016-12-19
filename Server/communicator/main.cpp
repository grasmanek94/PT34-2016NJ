#include "Communicator.hpp"

int main()
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

	return 0;
}