#include "sensors/Light/LightSensor.h"
#include "Measurement.hpp"
#include "IMeasurementSink.hpp"

LightSensor::LightSensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int index)
:
  ISensor(iMeasurementSink, targetInterval, type, index)
 ,sink(iMeasurementSink)
,interval(targetInterval)
,type(type)
,index(index)
{
  Wire.begin();
  address = 0x23;
  readDelay = 150;
  reading = false;
  time=millis()-interval;
}

void LightSensor::run()
{
  if(!reading && millis()>time+interval)
  {
    requestData();
    time = millis();
    return;
  }
  else if(reading && millis()>time+readDelay)
  {
    uint16_t LUX = readData();
    if(LUX==60000)
      return;
    //Measurement LuxMeas = Measurement(*this, type, index, LUX);
    Measurement LuxMeas = Measurement(LUX, type, index);
    sink.sendMeasurement(LuxMeas);
  }
}

void LightSensor::setTargetInterval(int targetInterval)
{
  interval = targetInterval;
}

int LightSensor::getTargetInterval()
{
  return interval;
}

void LightSensor::setType(char* newType)
{
  type = newType;
}

char* LightSensor::getType()
{
  return type;
}

void LightSensor::setIndex(int newIndex)
{
  index = newIndex;
}

int LightSensor::getIndex()
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
uint16_t LightSensor::readData() //max waarde van de sensor is 54612. 60000 is error waarde
{
  uint16_t val = 0;
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  reading = false;
  while (Wire.available())
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
    return 60000;
  }
}
