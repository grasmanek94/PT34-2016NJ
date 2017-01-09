#include "WeightSensor.hpp"
#include <Arduino.h>

WeightSensor::WeightSensor(IMeasurementSink &s, int t, char* T, int i, int p, int p2) 
              : ISensor(s, t, T, i), sink(s), targetInterval(t), type(T), index(i), pin(p), pin2(p2), scale(p, p2)
{
  scale.set_scale(calibration_factor);
}

WeightSensor::~WeightSensor(){}

void WeightSensor::run()
{
	int temp = (int) scale.get_units();
	Measurement ms = Measurement(temp, type, index);
  sink.sendMeasurement(ms);
}

int WeightSensor::getPin()
{
	return pin;
}

int WeightSensor::getPin2()
{
  return pin2;
}

void WeightSensor::Reset()
{
  scale.tare();
}

char* WeightSensor::getType()
{
  return type;
}

void WeightSensor::setType(char* keyword)
{
  type = keyword;
}

int WeightSensor::getIndex()
{
  return index;
}

void WeightSensor::setIndex(int index)
{
  this->index = index;
}


