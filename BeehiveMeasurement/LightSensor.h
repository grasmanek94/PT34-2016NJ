#ifndef LightSensor_h
#define LightSensor_h

#include <Arduino.h>
#include <Wire.h>
#include"IMeasurementSink.hpp"
#include "Measurement.hpp"
#include "ISensor.hpp"

class LightSensor : public ISensor
{
public:
  LightSensor(IMeasurementSink &iMeasurementSink, int tagetInterval, char* type, int index);
  void run();
  void init();
  void setTargetInterval(int targetInterval);
  int getTargetInterval();
  void setType(char* newType);
  char* getType();
  void setIndex(int newIndex);
  int getIndex();

private:
  void requestData();
  uint16_t readData();

  IMeasurementSink& sink;
  int interval;
  char* type;
  int index;

  int address;
  int readDelay;
  bool reading;
  unsigned long time;
};

#endif
