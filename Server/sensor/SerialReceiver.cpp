#include <stdexcept>
#include "SerialReceiver.hpp"

SerialReceiver::SerialReceiver(Device* setup)
	: setup(setup)
{
	if (setup == NULL)
	{
		throw std::runtime_error("setup == NULL");
	}
}

void SerialReceiver::Update()
{

}
