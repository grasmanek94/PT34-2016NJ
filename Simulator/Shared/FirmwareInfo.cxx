#include "FirmwareInfo.hxx"
#include "ExecCommand.hxx"

FirmwareInfo::FirmwareInfo()
{

}

FirmwareInfo::~FirmwareInfo()
{

}

std::string FirmwareInfo::GetOSInfo() const
{
	return
#ifdef WIN32
		exec("ver && wmic OS get OSArchitecture");
#else
		exec("uname -a");
#endif
}

std::string FirmwareInfo::GetMeasurementInfo() const
{
	return "Simulator Revision 1";
}
