#include "HostFileReader.hxx"

HostFileReader::HostFileReader(const std::string& file)
	: host("ws://localhost:9002")
{
	std::ifstream t(file);
	std::string temp((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	if (temp.size() != 0)
	{
		host = temp;
	}
}

HostFileReader::~HostFileReader()
{

}

std::string HostFileReader::GetHost() const
{
	return host;
}