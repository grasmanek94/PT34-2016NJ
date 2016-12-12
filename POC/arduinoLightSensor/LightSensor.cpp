#include "LightSensor.h"

LightSensor::LightSensor()
{
  Wire.begin();
  address = 0x23;
}

void LightSensor::requestData()
{
  Wire.beginTransmission(address);
Wire.write(0x10);//1lx reolution 120ms
Wire.endTransmission();
}
//delay hier
uint16_t LightSensor::readData()
{
  char buff[2];
  uint16_t val = 0;
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) //
  {
    buff[i] = Wire.read(); // receive one byte
    i++;
  }
  Wire.endTransmission();
  if (i == 2)
  {
    val = ((buff[0] << 8) | buff[1]) / 1.2;
    return val;
  }
  else
  {
    return -1;
  }
}
