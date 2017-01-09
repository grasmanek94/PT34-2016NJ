#include "BeehiveMeasurementUnit.hpp" 

#include "SerialSender.hpp"
#include "sensors/DummySensor.hpp"


SerialSender serialSender(0);
DummySensor dummySensor(serialSender, 1000, "12", 132);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
    dummySensor.run();
}
