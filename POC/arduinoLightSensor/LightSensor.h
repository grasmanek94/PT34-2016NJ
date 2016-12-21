#ifndef LightSensor_h
#define LightSensor_h

#include<arduino.h>
#include"wire.h"

class LightSensor:ISensor
{
public:
  LightSensor(&IMesurementSink, int tagetInterval);
  void run();
  void setTargetInterval(int targetInterval);
  int getTargetInterval();
  String getPlacement();
  String getPosition();

private:
  void requestData();
  uint16_t readData();

  IMesurementSink sink;
  int interval;
  string placement;
  string position;
  int address;

  int readDelay;
  bool reading;
  unsigned long time;
};

#endif
