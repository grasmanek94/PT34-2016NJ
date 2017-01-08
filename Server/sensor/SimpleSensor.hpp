#pragma once
#include <vector>
#include "Sensor.hpp"

class SimpleSensor : public Sensor
{
private:
	std::vector<double> values;
public:
	SimpleSensor(SensorType type, SensorUnit unit, SensorPlacement placement, size_t num_values, double min_value, double max_value, const Position& position);
	virtual ~SimpleSensor();

	virtual double GetValue(size_t i = 0) const;
	virtual void SetValue(double value, size_t i = 0);
};