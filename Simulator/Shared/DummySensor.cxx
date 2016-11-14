#include "DummySensor.hxx"

DummySensor::DummySensor()
{

}

DummySensor::DummySensor(SensorType type, SensorUnit unit, SensorPlacement placement, size_t num_values, double min_value, double max_value, const Position& position)
	: Sensor(type,unit,placement,num_values,min_value,max_value,position)
{

}

DummySensor::~DummySensor()
{

}

double DummySensor::GetValue(size_t i) const
{
	return GetMinValue() + ((double)(rand() % (int)(GetMaxValue() - GetMinValue())));
}
