#include "SerialSender.hpp"
#include "sensors/DummySensor.hpp"
#include "sensors/Light/LightSensor.h"

SerialSender serialSender(0);
DummySensor dummySensor(serialSender, 1000, "12", 132);
LightSensor lightSensor(serialSender, 1000, "lux", 1);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
    //dummySensor.run();
    lightSensor.run();
}
