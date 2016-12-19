#pragma once

#include <json/json.hpp>

class JSONable
{
public:
	virtual std::string GetRequestJson() const = 0;
	virtual std::string GetResponseJson() const = 0;
	virtual void ParseRequestJson(const std::string& json) = 0;
	virtual void ParseResponseJson(const std::string& json) = 0;
};