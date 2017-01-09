#include <Debug.hpp>
#include "FirmwareInfo.hpp"
#include "ExecCommand.hpp"

FirmwareInfo::FirmwareInfo()
{
	DEBUG_MSG("FirmwareInfo::FirmwareInfo");
}

FirmwareInfo::~FirmwareInfo()
{
	DEBUG_MSG("FirmwareInfo::~FirmwareInfo");
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

std::string FirmwareInfo::GetSerial() const
{
	// make this so the first time the address is returned it's stored on a file somewhere, then from that moment read from that file.
	return
#ifdef WIN32
		exec("getmac /FO LIST");
#else
		// should change this so it opens the dir and loops it, because there exists some small possibility that some systems don't have eth0
		// for our purposes though, eth0 is always available on the rpi.
		exec("cat /sys/class/net/eth0/address");
#endif
}
