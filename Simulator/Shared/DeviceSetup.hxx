#pragma once

#include <string>
#include <map>
#include <initializer_list>
#include <boost/bimap.hpp>
#include <boost/assign.hpp>

#include "JSONable.hxx"
#include "Sensor.hxx"
#include "FirmwareInfo.hxx"

enum DevCapabilities
{
	DevCapabilities_None = 0,
	DevCapabilities_ethernet10m = 1 << 0,
	DevCapabilities_ethernet100m = 1 << 1,
	DevCapabilities_ethernet1000m = 1 << 2,
	DevCapabilities_ethernet10gbps = 1 << 3,
	DevCapabilities_3g = 1 << 4,
	DevCapabilities_4g = 1 << 5,
	DevCapabilities_wifi24ghz80211b = 1 << 6,
	DevCapabilities_wifi24ghz80211g = 1 << 7,
	DevCapabilities_wifi24ghz80211n = 1 << 8,
	DevCapabilities_wifi50ghz80211a = 1 << 9,
	DevCapabilities_wifi50ghz80211 = 1 << 10,
	DevCapabilities_wifi50ghz80211j = 1 << 11,
	DevCapabilities_wifi50ghz80211n = 1 << 12,
	DevCapabilities_wifi50ghz80211ac = 1 << 13,
	DevCapabilities_bluetooth20 = 1 << 14,
	DevCapabilities_bluetooth21 = 1 << 15,
	DevCapabilities_bluetooth30 = 1 << 16,
	DevCapabilities_bluetooth31 = 1 << 17,
	DevCapabilities_bluetooth40 = 1 << 18,
	DevCapabilities_bluetooth41 = 1 << 19,
	DevCapabilities_bluetooth42 = 1 << 20,
	DevCapabilities_bluetooth5 = 1 << 21,
	DevCapabilities_MAX = 1 << 22
};

typedef boost::bimap<DevCapabilities, std::string> DevCapabilitiesStringType;
const static DevCapabilitiesStringType DevCapabilitiesStrings = boost::assign::list_of< DevCapabilitiesStringType::relation >
	(DevCapabilities_None, "none")
	(DevCapabilities_ethernet10m, "eth10m")
	(DevCapabilities_ethernet100m, "eth100m")
	(DevCapabilities_ethernet1000m, "eth1000m")
	(DevCapabilities_ethernet10gbps, "eth10gbps")
	(DevCapabilities_3g, "3g")
	(DevCapabilities_4g, "4g")
	(DevCapabilities_wifi24ghz80211b, "wifi24ghz80211b")
	(DevCapabilities_wifi24ghz80211g, "wifi24ghz80211g")
	(DevCapabilities_wifi24ghz80211n, "wifi24ghz80211n")
	(DevCapabilities_wifi50ghz80211a, "wifi50ghz80211a")
	(DevCapabilities_wifi50ghz80211, "wifi50ghz80211")
	(DevCapabilities_wifi50ghz80211j, "wifi50ghz80211j")
	(DevCapabilities_wifi50ghz80211n, "wifi50ghz80211n")
	(DevCapabilities_wifi50ghz80211ac, "wifi50ghz80211ac")
	(DevCapabilities_bluetooth20, "bluetooth20")
	(DevCapabilities_bluetooth21, "bluetooth21")
	(DevCapabilities_bluetooth30, "bluetooth30")
	(DevCapabilities_bluetooth31, "bluetooth31")
	(DevCapabilities_bluetooth40, "bluetooth40")
	(DevCapabilities_bluetooth41, "bluetooth41")
	(DevCapabilities_bluetooth42, "bluetooth42")
	(DevCapabilities_bluetooth5, "bluetooth50");

class DeviceSetup : public JSONable
{
public:
	using sensors_container_t = std::vector<Sensor*>;
	using sensors_list_t = std::map<SensorType, sensors_container_t>;
private:
	std::string serial;
	sensors_list_t sensors;
	size_t capabilities;
	const static size_t protocol_revision = 2;
	FirmwareInfo fwinfo;
public:
	DeviceSetup();
	DeviceSetup(const std::string& _serial, size_t capabilities, std::initializer_list<Sensor*> sensors = {});
	~DeviceSetup();

	void SetSerial(const std::string& _serial);
	std::string GetSerial() const;

	bool AddSensor(Sensor* sensor);

	void AddCapability(size_t capability);
	void RemoveCapability(size_t capability);
	bool HasCapability(size_t capability) const;
	size_t GetCapabilities() const;

	void CleanSensors();
	Sensor* GetSensor(SensorType type, size_t index = 0) const;

	virtual std::string GetRequestJson() const;
	virtual std::string GetResponseJson() const;
	virtual void ParseRequestJson(const std::string& json);
	virtual void ParseResponseJson(const std::string& json);
};