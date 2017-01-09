#pragma once
#include "Device.hpp"

class SerialReceiver
{
private:
	Device* setup;
public:
	SerialReceiver(Device* setup);
	void Update();
};