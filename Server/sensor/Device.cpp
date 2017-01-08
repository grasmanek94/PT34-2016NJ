#include <unordered_map>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "Device.hpp"

using json = nlohmann::json;

Device::Device()
{

}

Device::Device(size_t capabilities, std::initializer_list<Sensor*> sensors_list)
	: serial(fwinfo.GetSerial()), capabilities(capabilities)
{
	for (auto &sensor : sensors_list)
	{
		sensors[sensor->GetSensorType()].push_back(sensor);
	}
}

Device::~Device()
{
	CleanSensors();
}

std::string Device::GetRequestJson() const
{
	const static json j
	{
		{ "GetDeviceSetup", {} }
	};
	const static std::string request_text(j.dump());

	return request_text;
}

void Device::ParseRequestJson(const std::string& _json)
{
	const json j = json::parse(_json.c_str());
	//cleanup

	auto device_setup = j.find("GetDeviceSetup");
	if (device_setup != j.end())
	{
		// process stuff
	}
}

std::string Device::GetResponseJson() const
{
	space_info si = space(".");

	json j
	{
		{ "GetDeviceSetup",
			{
				{"serial", serial},
				{"firmware", {
					{"server",{
						{"os", fwinfo.GetOSInfo()},
						{"free", si.available / (1024 * 1024) }}},
					{"measurement",{
						{"version", fwinfo.GetMeasurementInfo() }}
					}
				}}
			}
		}
	};

	std::unordered_map<std::string, json> c_umap{};

	for (auto& sensor_type : sensors)
	{
		if (sensor_type.second.size() > 0)
		{
			c_umap[SensorTypeStrings.left.at(sensor_type.first)] = json
			{
				{"amount", sensor_type.second.size() },
				{"sensors", {}}
			};

			for (size_t i = 0, j = sensor_type.second.size(); i < j; ++i)
			{
				auto sensors_json = c_umap[SensorTypeStrings.left.at(sensor_type.first)].find("sensors");
				Sensor* sensor_info = sensor_type.second[i];
				Position pos(sensor_info->GetPosition());
				json sensor_info_json
				{
					{ std::to_string(i), 
						{
							{ "min", sensor_info->GetMinValue() },
							{ "max", sensor_info->GetMaxValue() },
							{ "unit", SensorUnitStrings.left.at(sensor_info->GetSensorUnit()) },
							{ "placement", SensorPlacementStrings.left.at(sensor_info->GetSensorPlacement()) },
							{ "position", { pos.x, pos.y, pos.z } },
						}
					}
				};

				sensors_json->push_back(sensor_info_json);
			}
		}
	}

	j.find("GetDeviceSetup")->push_back({ "devices", c_umap });

	std::vector<std::string> capabilities;

	for (size_t i = 1; i < DevCapabilities_MAX; i <<= 1)
	{
		if (HasCapability(i))
		{
			capabilities.push_back(DevCapabilitiesStrings.left.at((DevCapabilities)i));
		}
	}

	if (capabilities.size() == 0)
	{
		capabilities.push_back(DevCapabilitiesStrings.left.at(DevCapabilities_None));
	}

	j.find("GetDeviceSetup")->push_back({ "capabilities", capabilities });
	j.find("GetDeviceSetup")->push_back({ "protocol", protocol_revision });

	return j.dump();
}

void Device::CleanSensors()
{
	for (auto& sensor_type : sensors)
	{
		for (size_t i = 0, j = sensor_type.second.size(); i < j; ++i)
		{
			delete sensor_type.second[i];
			sensor_type.second[i] = NULL;
		}
	}
	sensors.clear();
}

Sensor* Device::GetSensor(SensorType type, size_t index) const
{
	auto sensor_vec = sensors.find(type);

	if (sensor_vec == sensors.end() || sensor_vec->second.size() <= index)
	{
		return NULL;
	}

	return sensor_vec->second[index];
}

size_t Device::GetSensorCount(SensorType type) const
{
	auto sensor_vec = sensors.find(type);

	if (sensor_vec == sensors.end())
	{
		return 0;
	}

	return sensor_vec->second.size();
}

void Device::ParseResponseJson(const std::string& _json)
{
	const json j = json::parse(_json.c_str());
	auto device_setup = j.find("GetDeviceSetup");
	if (device_setup != j.end())
	{
		auto serial_found = device_setup->find("serial");
		if (serial_found != device_setup->end())
		{
			serial = serial_found->get<std::string>();
		}
		else
		{
			serial = "UNKNOWN";
		}

		// TODO: finish this function to be able to construct Device object completely from a JSON formatted string
		// ON SECOND THOUGHT: We never use this function, when testing is going to be needed this function needs to be finished
		auto devices_found = device_setup->find("devices");
		sensors.clear();
		if (devices_found != device_setup->end())
		{
			
		}
		else
		{
			
		}
	}
}

std::string Device::GetSerial() const
{
	return serial;
}

bool Device::AddSensor(Sensor* sensor)
{
	if (sensor == NULL)
	{
		return false;
	}

	for (auto &s : sensors[sensor->GetSensorType()])
	{
		if (s == sensor)
		{
			return false;
		}
	}

	sensors[sensor->GetSensorType()].push_back(sensor);
	return true;
}

void Device::AddCapability(size_t capability)
{
	capabilities |= capability;
}

void Device::RemoveCapability(size_t capability)
{
	capabilities &= ~(capability);
}

bool Device::HasCapability(size_t capability) const
{
	return (capabilities & capability) != 0;
}

size_t Device::GetCapabilities() const
{
	return (size_t)capabilities;
}