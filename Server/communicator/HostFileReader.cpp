#include <Debug.hpp>
#include "HostFileReader.hpp"

HostFileReader::HostFileReader(const std::string& file)
	: host("ws://localhost:9002")
{
	DEBUG_MSG("HostFileReader::HostFileReader: " << host);
	std::ifstream t(file);
	std::string temp((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	if (temp.size() != 0)
	{
		host = temp;
		DEBUG_MSG("HostFileReader::HostUpdate: " << host);
	}
}

HostFileReader::~HostFileReader()
{
	DEBUG_MSG("HostFileReader::~HostFileReader");
}

std::string HostFileReader::GetHost() const
{
	DEBUG_MSG("HostFileReader::GetHost");
	return host;
}