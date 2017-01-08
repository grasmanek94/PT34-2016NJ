#include "SimpleSensor.hpp"

SimpleSensor::SimpleSensor()
{

}

SimpleSensor::SimpleSensor(SensorType type, SensorUnit unit, SensorPlacement placement, size_t num_values, double min_value, double max_value, const Position& position)
	: Sensor(type,unit,placement,num_values,min_value,max_value,position)
{

}

SimpleSensor::~SimpleSensor()
{

}

double SimpleSensor::GetValue(size_t i) const
{
	return GetMinValue() + ((double)(rand() % (int)(GetMaxValue() - GetMinValue())));
}
