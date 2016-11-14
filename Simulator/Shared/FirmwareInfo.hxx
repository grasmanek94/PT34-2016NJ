#pragma once
#include <string>

class FirmwareInfo
{
public:
	FirmwareInfo();
	~FirmwareInfo();

	std::string GetOSInfo() const;
	std::string GetMeasurementInfo() const;
};