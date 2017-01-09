#include "PressureSensor.hpp"
#include "Measurement.hpp"

PressureSensor::PressureSensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int index)
  : ISensor(iMeasurementSink, targetInterval, type, index)
  , interval(targetInterval)
  , lastmillis(0)
  , s(iMeasurementSink)
  , index(index)
  , type(type)
  , Press(0)
{

}

void PressureSensor::init() {

}

void PressureSensor::run() {
  if (millis() - lastmillis >= interval) 
  {
    SFE_BMP180 Sensor;
    double p, t;

    if (Sensor.begin()) {
      Press = Sensor.getPressure(p, t);
      Measurement ms(Press, type, index);
      s.sendMeasurement(ms);
      lastmillis = millis();
    }
  }
}

void PressureSensor::SetTargetInterval(int targetInterval) {
  if (targetInterval > 0) {
    interval = targetInterval;
  }
}

int PressureSensor::getTargetInterval() {
  return interval;
}

char* PressureSensor::getType() {
  return type;
}

int PressureSensor::getIndex() {
  return index;

}

void PressureSensor::setIndex(int Index) {
  if (Index > 0) {
    index = Index;
  }
}
