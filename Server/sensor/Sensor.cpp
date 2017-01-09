#include <Debug.hpp>
#include "Sensor.hpp"

Sensor::~Sensor()
{
	DEBUG_MSG("Sensor::~Sensor");
}

Sensor::Sensor(
	SensorType type, SensorUnit unit, 
	SensorPlacement placement, size_t num_values, 
	double min_value, double max_value, const Position& position)

	: type(type), unit(unit), 
	placement(placement), num_values(num_values), 
	position(position), min_value(min_value), max_value(max_value)
{
	DEBUG_MSG("Sensor::Sensor(" 
		<< SensorTypeStrings.left.at(type) << ", " 
		<< SensorUnitStrings.left.at(unit) << ", " 
		<< SensorPlacementStrings.left.at(placement) << ", " 
		<< "num_values: " << num_values << ", "
		<< "min_value: " << min_value << ", "
		<< "max_value: " << max_value << ", "
		<< "position: {" << position.x << ", " << position.y << ", " << position.z << "}"
		<< ")");
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