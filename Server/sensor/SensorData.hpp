#pragma once

#include "JSONable.hpp"
#include "Device.hpp"

class SensorData : public JSONable
{
public:
	using sensors_container_t = std::vector<size_t>;
	using sensors_list_t = std::map<SensorType, sensors_container_t>;
private:
	Device* setup;
	sensors_list_t request_sensors;
public:
	SensorData(Device* setup);

	virtual std::string GetRequestJson() const;
	virtual std::string GetResponseJson() const;
	virtual void ParseRequestJson(const std::string& _json);
	virtual void ParseResponseJson(const std::string& json);
};