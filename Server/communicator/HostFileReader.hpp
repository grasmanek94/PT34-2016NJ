#pragma once
#include <string>
#include <fstream>
#include <streambuf>

class HostFileReader
{
private:
	std::string host;
public:
	HostFileReader(const std::string& file = "host.txt");
	~HostFileReader();

	std::string GetHost() const;
};