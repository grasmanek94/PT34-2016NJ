#include <stdexcept>
#include <Debug.hpp>
#include "SimpleSensor.hpp"

SimpleSensor::SimpleSensor(SensorType type, SensorUnit unit, SensorPlacement placement, size_t num_values, double min_value, double max_value, const Position& position)
	: Sensor(type,unit,placement,num_values,min_value,max_value,position)
{
	DEBUG_MSG("SimpleSensor::SimpleSensor");
	values.resize(num_values);
}

SimpleSensor::~SimpleSensor()
{
	DEBUG_MSG("SimpleSensor::~SimpleSensor");
}

double SimpleSensor::GetValue(size_t i) const
{
	if (values.size() <= i)
	{
		throw std::out_of_range("i");
	}
	return values[i];
}

void SimpleSensor::SetValue(double value, size_t i)
{
	if (values.size() <= i)
	{
		throw std::out_of_range("i");
	}
	values[i] = value;
}
