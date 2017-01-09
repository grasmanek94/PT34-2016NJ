#include "LightSensor.h"
#include "Measurement"

LightSensor::LightSensor(IMeasurementSink &IMesurementSink, int tagetInterval, char* type, int index)
:sink(MesurementSink)
,intercal(targetInterval)
,type(type)
,index(index)
{
  Wire.begin();
  address = 0x23;
  readDelay = 150;
  reading = false;
}

void LightSensor::run()
{
  if(!reading && millis()>time+interval)
  {
    requestData();
    time = millis();
    return;
  }
  elseif(reading && millis()>time+readDelay)
  {
    uint16_t LUX = readData();
    Measurement LuxMeas = Measurement(*this, type, index, LUX)
    sink->send(LuxMeas)
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

void setType(char* newType)
{
  type = newType;
}

char* getType()
{
  return type;
}

void setIndex(int newIndex)
{
  index = newIndex;
}

int getIndex()
{
  return index;
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
    reading = false;
    return val;
  }
  else
  {
    return -1;
  }
}
