#include <stdexcept>
#include <json-develop/src/json.hpp>
#include "SensorData.hxx"

using json = nlohmann::json;

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
	const static json j
	{
		{ "GetSensorData", {} }
	};
	const static std::string request_text(j.dump());

	return request_text;
}

std::string SensorData::GetResponseJson() const
{
	return "";
}

void SensorData::ParseRequestJson(const std::string& _json)
{
	const json j = json::parse(_json.c_str());

	auto sensor_data = j.find("GetSensorData");
	if (sensor_data != j.end())
	{
		auto sens_arr = SensorTypeStrings.left;
		for(auto& sens_entry: sens_arr)
		{
			auto found_sensor_array = sensor_data->find(sens_entry.second);
			if (found_sensor_array != sensor_data->end())
			{
				request_sensors[sens_entry.first] = found_sensor_array->get<std::vector<size_t>>();
			}
		}
	}
}

void SensorData::ParseResponseJson(const std::string& json)
{
	// TODO: finish this function to be able to construct SensorData object completely from a JSON formatted string
}