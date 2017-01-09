#include "SerialSender.hpp"
#include "sensors/DummySensor.hpp"
#include "sensors/Light/LightSensor.h"
#include "WeightSensor.hpp"

SerialSender serialSender(0);
//DummySensor dummySensor(serialSender, 1000, "12", 132);
//LightSensor lightSensor(serialSender, 1000, "lux", 1);
WeightSensor weightSensor(serialSender, 1000, "weight", 1, 2, 3);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
    //dummySensor.run();
    //lightSensor.run();
    Serial.println("bloep");
    weightSensor.run();
    Serial.println("bliep");
}
