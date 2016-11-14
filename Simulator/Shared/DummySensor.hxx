#pragma once

#include "Sensor.hxx"

class DummySensor : public Sensor
{
public:
	DummySensor();
	DummySensor(SensorType type, SensorUnit unit, SensorPlacement placement, size_t num_values, double min_value, double max_value, const Position& position);
	virtual ~DummySensor();

	virtual double GetValue(size_t i = 0) const;
};