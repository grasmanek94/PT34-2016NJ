#pragma once

#include "JSONable.hxx"
#include "DeviceSetup.hxx"

class SensorData : public JSONable
{
public:
	using sensors_container_t = std::vector<size_t>;
	using sensors_list_t = std::map<SensorType, sensors_container_t>;
private:
	DeviceSetup* setup;
	sensors_list_t request_sensors;
public:
	SensorData(DeviceSetup* setup);

	virtual std::string GetRequestJson() const;
	virtual std::string GetResponseJson() const;
	virtual void ParseRequestJson(const std::string& json);
	virtual void ParseResponseJson(const std::string& json);
};