#include <unordered_map>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "DeviceSetup.hxx"

using json = nlohmann::json;

DeviceSetup::DeviceSetup()
{

}

DeviceSetup::DeviceSetup(const std::string& serial, size_t capabilities, std::initializer_list<Sensor*> sensors_list)
	: serial(serial), capabilities(capabilities)
{
	for (auto &sensor : sensors_list)
	{
		sensors[sensor->GetSensorType()].push_back(sensor);
	}
}

DeviceSetup::~DeviceSetup()
{
	CleanSensors();
}

std::string DeviceSetup::GetRequestJson() const
{
	const static json j
	{
		{ "GetDeviceSetup", {} }
	};
	const static std::string request_text(j.dump());

	return request_text;
}

void DeviceSetup::ParseRequestJson(const std::string& json)
{

}

std::string DeviceSetup::GetResponseJson() const
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

void DeviceSetup::CleanSensors()
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

Sensor* DeviceSetup::GetSensor(SensorType type, size_t index) const
{
	auto sensor_vec = sensors.find(type);

	if (sensor_vec == sensors.end() || sensor_vec->second.size() >= index)
	{
		return NULL;
	}

	return sensor_vec->second[index];
}

void DeviceSetup::ParseResponseJson(const std::string& _json)
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

		auto devices_found = device_setup->find("devices");
		sensors.clear();
		if (devices_found != device_setup->end())
		{
			serial = serial_found->get<std::string>();
		}
		else
		{
			serial = "UNKNOWN";
		}
	}
}

void DeviceSetup::SetSerial(const std::string& _serial)
{
	serial = _serial;
}

std::string DeviceSetup::GetSerial() const
{
	return serial;
}

bool DeviceSetup::AddSensor(Sensor* sensor)
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

void DeviceSetup::AddCapability(size_t capability)
{
	capabilities |= capability;
}

void DeviceSetup::RemoveCapability(size_t capability)
{
	capabilities &= ~(capability);
}

bool DeviceSetup::HasCapability(size_t capability) const
{
	return (capabilities & capability) != 0;
}

size_t DeviceSetup::GetCapabilities() const
{
	return (size_t)capabilities;
}