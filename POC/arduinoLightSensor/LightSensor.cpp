#include "LightSensor.h"

LightSensor::LightSensor(&IMesurementSink MesurementSink , int tagetInterval)
:sink(MesurementSink)
{
  Wire.begin();
  placement = "buiten";
  position = "bovenop";
  address = 0x23;
  readDelay = 150;
  reading = false;
  setTargetInterval(targetInterval);
}

void LightSensor::run()
{
  if(!reading && millis()>time+interval)
  {
    requestData();
    time = millis();
  }
  elseif(reading && millis()>time+readDelay)
  {
    uint16_t LUX = readData();

  }
}

void LightSensor::setTargetInterval(int targetInterval)
{
  if(targetInterval>readDelay)
  {
    interval = targetInterval;
  }
}

int LightSensorgetTargetInterval()
{
  return interval;
}

String LightSensorgetPlacement()
{
  return placement;
}

String LightSensorgetPosition()
{
  return position;
}

void LightSensor::requestData()
{
  reading = true;
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}
//delay hier
uint16_t LightSensor::readData()
{
  uint16_t val = 0;
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) //
  {
    val<<=8;
    val += Wire.read();
    i++;
  }
  Wire.endTransmission();
  if (i == 2)
  {
    val /= 1.2;
    return val;
  }
  else
  {
    return -1;
  }
  reading = false;
}
