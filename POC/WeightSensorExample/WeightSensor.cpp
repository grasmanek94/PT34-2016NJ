#include "WeightSensor.hpp"

WeightSensor(IMeasurementSink &s, int t, char* T, int i, int p, int p2)
{
  &sink = &s;
  targetInterval = t;
  type = T;
  index = i;
  pin = p;
	pin2 = p2;
	scale = HX711(pin, pin2);
  scale.set_scale(calibration_factor);
}

~WeightSensor(){}

int WeightSensor::run()
{
	int temp = (int) scale.get_units();
	Measurement ms = Measurement(*this, type, index, temp);
  s->send(ms);
}

int[] WeightSensor::getPins()
{
  int pins[2] = {pin, pin2};
	return pins;
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
  this.index = index;
}


