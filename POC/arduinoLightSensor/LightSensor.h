#ifndef LightSensor_h
#define LightSensor_h

#include<arduino.h>
#include<wire.h>

class LightSensor
{
public:
  LightSensor();
  void requestData();
  uint16_t readData();

private:
  int address;
  char buff[2];
}

#endif
