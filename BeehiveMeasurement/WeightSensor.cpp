#include "WeightSensor.hpp"

WeightSensor::WeightSensor(IMeasurementSink &s, int t, char* T, int i, int p, int p2) 
              : ISensor(s, t, T, i), sink(s), targetInterval(t), type(T), index(i), pin(p), pin2(p2), scale(p, p2), timer(t, true)
{
  scale.set_scale(calibration_factor);
  timer.start();
}

WeightSensor::~WeightSensor(){}

void WeightSensor::run()
{
  if(timer.isElapsed())
  {
    int temp = (int) scale.get_units();
    Measurement ms = Measurement(temp, type, index);
    sink.sendMeasurement(ms); 
  }
}

int WeightSensor::getPin()
{
	return pin;
}

int WeightSensor::getPin2()
{
  return pin2;
}

void WeightSensor::reset()
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


