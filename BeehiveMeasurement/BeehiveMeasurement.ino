#include "SerialSender.hpp"
#include "sensors/DummySensor.hpp"
#include "LightSensor.h"
#include "WeightSensor.hpp"
#include "HumiditySensor.hpp"
#include "TemperatureSensor.hpp"
#include "PressureSensor.hpp"


static const int interval = 1000;

SerialSender serialSender(0);
DummySensor dummySensor(serialSender, interval, "12", 132);
LightSensor lightSensor(serialSender, interval, "lux", 1);
WeightSensor weightSensor(serialSender, interval, "Weight", 1, 2, 3);
HumiditySensor humiditySensor(serialSender, interval, "Temperature", 0);
TemperatureSensor temperatureSensor(serialSender, interval, "Temperature", 0);
PressureSensor pressureSensor(serialSender, interval, "Pressure", 0);

void setup()
{
  Serial.begin(115200);
  weightSensor.reset();
}

void loop()
{
    dummySensor.run();
    lightSensor.run();
    weightSensor.run();
    humiditySensor.run();
    temperatureSensor.run();
    pressureSensor.run();
}
