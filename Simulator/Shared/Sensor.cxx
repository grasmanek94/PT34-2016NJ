#include "Sensor.hxx"

Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

Sensor::Sensor(
	SensorType type, SensorUnit unit, 
	SensorPlacement placement, size_t num_values, 
	double min_value, double max_value, const Position& position)

	: type(type), unit(unit), 
	placement(placement), num_values(num_values), 
	min_value(min_value), max_value(max_value), position(position)
{

}

SensorType Sensor::GetSensorType() const
{
	return type;
}

SensorUnit Sensor::GetSensorUnit() const
{
	return unit;
}

SensorPlacement Sensor::GetSensorPlacement() const
{
	return placement;
}

size_t Sensor::NumValues() const
{
	return num_values;
}

Position Sensor::GetPosition() const
{
	return position;
}

double Sensor::GetMinValue() const
{
	return min_value;
}

double Sensor::GetMaxValue() const
{
	return max_value;
}