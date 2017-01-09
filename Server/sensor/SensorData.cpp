#include <stdexcept>
#include <map>
#include <string>
#include <vector>
#include <limits>
#include <json/json.hpp>
#include <Debug.hpp>
#include "SensorData.hpp"

using json = nlohmann::json;

SensorData::SensorData(Device* setup)
	: setup(setup)
{
	DEBUG_MSG("SensorData::SensorData");
	if (setup == NULL)
	{
		throw std::runtime_error("setup == NULL");
	}
}

std::string SensorData::GetRequestJson() const
{
	DEBUG_MSG("SensorData::GetRequestJson");
	const static json j
	{
		{ "GetSensorData", {} }
	};
	const static std::string request_text(j.dump());

	return request_text;
}

std::string SensorData::GetResponseJson() const
{
	DEBUG_MSG("SensorData::GetResponseJson");
	// TODO: add errors here or to parse request
	std::map <std::string, json> sensor_data;

	for (auto& sens_entry : request_sensors)
	{
		auto& mapped_json = sensor_data[SensorTypeStrings.left.at(sens_entry.first)];

		bool all_sensors = sens_entry.second.size() == 0;

		if (!all_sensors)
		{
			for (auto& sens_number : sens_entry.second)
			{
				Sensor* sensor = setup->GetSensor(sens_entry.first, sens_number);

				if (sensor != NULL)
				{
					mapped_json.push_back({ sens_number, sensor->GetValue() });
				}
				else
				{
					mapped_json.push_back({ sens_number, -std::numeric_limits<double>::infinity() });
				}
			}
		}
		else
		{
			for (size_t i = 0, j = setup->GetSensorCount(sens_entry.first); i < j; ++i)
			{
				Sensor* sensor = setup->GetSensor(sens_entry.first, i);

				if (sensor != NULL)
				{
					mapped_json.push_back({ i, sensor->GetValue() });
				}
				else
				{
					mapped_json.push_back({ i, -std::numeric_limits<double>::infinity() });
				}
			}
		}
	}

	json j;

	j.push_back({ "GetSensorData", sensor_data });

	return j.dump();
}

//if empty json in ParseRequest then everything is returned
void SensorData::ParseRequestJson(const std::string& _json)
{
	DEBUG_MSG("SensorData::ParseRequestJson: " << _json);
	const json j = json::parse(_json.c_str());
	request_sensors.clear();

	auto sensor_data = j.find("GetSensorData");
	if (sensor_data != j.end())
	{
		auto sens_arr = SensorTypeStrings.left;
		for (auto& sens_entry : sens_arr)
		{
			auto found_sensor_array = sensor_data->find(sens_entry.second);
			if (found_sensor_array != sensor_data->end())
			{
				request_sensors[sens_entry.first] = found_sensor_array->get<std::vector<size_t>>();
			}
		}
	}

	if (request_sensors.empty())
	{
		DEBUG_MSG("SensorData::ParseRequestJson:AllSensors");
		request_sensors[SensorTypeTemperature] = std::vector<size_t>();
		request_sensors[SensorTypeSound] = std::vector<size_t>();
		request_sensors[SensorTypeWeight] = std::vector<size_t>();
		request_sensors[SensorTypeHumidity] = std::vector<size_t>();
		request_sensors[SensorTypePressure] = std::vector<size_t>();
		request_sensors[SensorTypeLightIntensity] = std::vector<size_t>();
	}
}

void SensorData::ParseResponseJson(const std::string& json)
{
	DEBUG_MSG("SensorData::ParseResponseJson: " << json);
	// TODO: finish this function to be able to construct SensorData object completely from a JSON formatted string
}