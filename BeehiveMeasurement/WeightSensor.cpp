#include "WeightSensor.hpp"

WeightSensor::WeightSensor(IMeasurementSink &s, int t, char* T, int i, int p, int p2) 
              : ISensor(s, t, T, i), sink(s), targetInterval(t), type(T), index(i), pin(p), pin2(p2), calibration_factor(-43800), timer(t, true)
{
}

WeightSensor::~WeightSensor(){}

void WeightSensor::init()
{
  scale = HX711(pin,pin2);
  scale.set_scale(calibration_factor);
  timer.start(); 
  reset();
}

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


