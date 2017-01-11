#include "SerialSender.hpp"
#include "sensors/DummySensor.hpp"
#include "LightSensor.h"
#include "WeightSensor.hpp"
#include "HumiditySensor.hpp"
#include "TemperatureSensor.hpp"
#include "PressureSensor.hpp"


static const int interval = 1000;
static const uint8_t debugPin = 13;


SerialSender serialSender(0);
//DummySensor dummySensor(serialSender, interval, "12", 132);
LightSensor lightSensor(serialSender, interval, "light-intensity", 0);
WeightSensor weightSensor(serialSender, interval, "weight", 0, 3, 4);
HumiditySensor humiditySensor(serialSender, interval, "humidity", 0);
TemperatureSensor temperatureSensor(serialSender, interval, "temperature", 0);
PressureSensor pressureSensor(serialSender, interval, "pressure", 0);

void setup()
{
  pinMode(debugPin, OUTPUT);
  digitalWrite(debugPin, LOW);
  Serial.begin(115200);
  //dummySensor.init();
  lightSensor.init();
  weightSensor.init();
  humiditySensor.init();
  temperatureSensor.init();
  pressureSensor.init();
  digitalWrite(debugPin, HIGH);
}

void loop()
{
  //dummySensor.run();
  lightSensor.run();
  weightSensor.run();
  humiditySensor.run();
  temperatureSensor.run();
  pressureSensor.run();
}
