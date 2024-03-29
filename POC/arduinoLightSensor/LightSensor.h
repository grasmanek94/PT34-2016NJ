#ifndef LightSensor_h
#define LightSensor_h

#include<arduino.h>
#include"wire.h"
#include"iMeasurementSink.h"
#include"Measurement"

class LightSensor:ISensor
{
public:
  LightSensor(IMeasurementSink &IMesurementSink, int tagetInterval, char* type, int index);
  void run();
  void setTargetInterval(int targetInterval);
  int getTargetInterval();
  void setType(char* newType);
  char* getType();
  void setIndex(int newIndex);
  int getIndex();

private:
  void requestData();
  uint16_t readData();

  IMesurementSink* sink;
  int interval;
  char* type;
  int index;

  int address;
  int readDelay;
  bool reading;
  unsigned long time;
};

#endif
