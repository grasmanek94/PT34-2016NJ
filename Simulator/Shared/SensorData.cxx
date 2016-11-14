#include <stdexcept>
#include "SensorData.hxx"

SensorData::SensorData(DeviceSetup* setup)
	: setup(setup)
{
	if (setup == NULL)
	{
		throw std::runtime_error("setup == NULL");
	}
}

std::string SensorData::GetRequestJson() const
{
	return "";
}

std::string SensorData::GetResponseJson() const
{
	return "";
}

void SensorData::ParseRequestJson(const std::string& json)
{

}

void SensorData::ParseResponseJson(const std::string& json)
{

}