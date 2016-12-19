#pragma once

#include "Sensor.hpp"

class SerialConnectionSensor : public Sensor
{
public:
	SerialConnectionSensor();
	SerialConnectionSensor(SensorType type, SensorUnit unit, SensorPlacement placement, size_t num_values, double min_value, double max_value, const Position& position);
	virtual ~SerialConnectionSensor();

	virtual double GetValue(size_t i = 0) const;
};