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
    if(LUX==60000)
      return;
    Measurement LuxMeas = Measurement(*this, type, index, LUX);
    sink->send(LuxMeas);
  }
}

void LightSensor::setTargetInterval(int targetInterval)
{
  interval = targetInterval;
}

int LightSensor::LightSensorgetTargetInterval()
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
