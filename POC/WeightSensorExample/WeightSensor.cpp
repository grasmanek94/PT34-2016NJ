#include "WeightSensor.h"

WeightSensor::WeightSensor(String k, int p, int p2) : Sensor(k,p)
{
	pin2 = p2;
	scale = HX711(Sensor::getPin(), pin2);
}

int WeightSensor::getMeasurementData()
{
	int temp = (int) scale.get_units();
	return temp;
}

int WeightSensor::getPin2()
{
	return pin2;
}

void WeightSensor::calibrate()
{
	Serial.begin(9600);
	Serial.println("Weight Sensor calibration started");
	Serial.println("Remove all weight");
	Serial.println("After readings begin, place known weight");
	Serial.println("Press + or a to increase calibration factor");
	Serial.println("Press - or z to decrease calibration factor");
	Serial.println("Press y to end calibration");
	scale.set_scale();
	scale.tare(); //Reset the scale to 0

	long zero_factor = scale.read_average(); //Get a baseline reading
	Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
	Serial.println(zero_factor);

	while(1)
	{
	  	scale.set_scale(calibration_factor); //Adjust to this calibration factor

	  	Serial.print("Reading: ");
	  	Serial.print(scale.get_units(), 1);
		Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
		Serial.print(" calibration_factor: ");
		Serial.print(calibration_factor);
		Serial.println();

		if(Serial.available())
		{
			char temp = Serial.read();
			if(temp == '+' || temp == 'a')
				calibration_factor += 10;
			else if(temp == '-' || temp == 'z')
				calibration_factor -= 10;
			else if(temp == 'y')
			{
				break;
			}
		}
	}
	Serial.end();
}
