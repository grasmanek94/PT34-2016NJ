#include <stdexcept>
#include <Debug.hpp>
#include "SerialReceiver.hpp"

SerialReceiver::SerialReceiver(Device* setup)
	: setup(setup)
{
	DEBUG_MSG("SerialReceiver::SerialReceiver");
	if (setup == NULL)
	{
		throw std::runtime_error("setup == NULL");
	}
}

void SerialReceiver::Update()
{

}
