#include "WeightSensor.h"

WeightSensor weight("gewichtssensor", 3, 2);
void setup()
{
	weight.calibrate();
	Serial.begin(9600);
}

void loop()
{
	Serial.print("Reading: ");
	Serial.print(weight.getMeasurementData(), DEC);
	Serial.print(" kg");
	Serial.println();
}
